import os
import sys
import json
import time
import signal
import typing
import copy
import threading

import numpy                as np
import numpy.linalg         as nl

import scipy                as sp
import scipy.linalg         as sl

import rclpy
from   rclpy.node           import Node
from   rclpy.qos            import QoSProfile, ReliabilityPolicy, DurabilityPolicy
from   std_msgs.msg         import Bool, Float32MultiArray
from   macspos_msgs.msg     import AgentExternalState, AgentInternalState, AgentInternalSetpoint
from   mocap4r2_msgs.msg    import RigidBodies

UP = lambda x : f"\033[{x}A"
CLR = "\033[K"

class SharedMemory:

    def __init__(self, whoami, params, config):

        self.id                          = whoami
        self.NUM_AGENTS                  = config['NUM_AGENTS'                  ]
        self.trajectory_original         = config['TRAJECTORY'                  ]

        self.EXTERN_ROSPUB_LOOP_PERIOD_S = params['EXTERN_ROSPUB_LOOP_PERIOD_S' ]
        self.INTERN_ROSPUB_LOOP_PERIOD_S = params['INTERN_ROSPUB_LOOP_PERIOD_S' ]
        self.SOLUTION_UPDATE_PERIOD_S    = params['SOLUTION_UPDATE_PERIOD_S'    ]
        self.MINIMUM_LOOP_PERIOD_S       = params['MINIMUM_LOOP_PERIOD_S'       ]

        self.MINIMUM_SPEED_MS            = params['MINIMUM_SPEED_MS'            ]
        self.MAXIMUM_SPEED_MS            = params['MAXIMUM_SPEED_MS'            ]
        self.SAFETY_DISTANCE_M           = params['SAFETY_DISTANCE_M'           ]
        self.LOOKAHEAD_HORIZON_S         = params['LOOKAHEAD_HORIZON_S'         ]
        self.TRAJEC_PASS_THRESHOLD_M     = params['TRAJEC_PASS_THRESHOLD_M'     ]

        self.SOLVER_MAXIMUM_ITERATIONS   = params['SOLVER_MAXIMUM_ITERATIONS'   ]
        self.SOLVER_TOLERANCE            = params['SOLVER_TOLERANCE'            ]
        self.SOLVER_STEP_SIZE            = params['SOLVER_STEP_SIZE'            ]
        self.SEGMENT_INTERVAL_M          = params['SEGMENT_INTERVAL_M'          ]

        self.position                    = None
        self.velocity                    = None
        self.position_setpoint           = None
        self.velocity_setpoint           = None
        self.velocity_profile            = None

        self.ongoing_waypoint            = None
        self.ongoing_waypoint_refined    = None
        self.trajectory_trimmed          = None
        self.trajectory_refined          = None

        self.list_position               = None
        self.list_velocity               = None
        self.list_ongoing                = None
        self.list_timestamp              = None
        self.list_flag                   = False

        self.solver_status               = "not converged"

        self.flag__is_running            = False
        self.flag__is_activated          = False
        self.flag__is_solving            = False
        self.flag__is_killed             = False
        self.flag__is_arrived            = False

        self._initialize()


    def _initialize(self):
            
        self.trajectory_original         = [trajectory_from_array(i, self.trajectory_original[str(i)]) for i in range(self.NUM_AGENTS)]
        self.trajectory_trimmed          = self.trajectory_original.copy()
        self.trajectory_refined          = self.trajectory_original.copy()
        
        self.position                    = np.zeros(3, dtype=np.float32)
        self.velocity                    = np.zeros(3, dtype=np.float32)
        self.position_setpoint           = np.zeros(3, dtype=np.float32)
        self.velocity_setpoint           = np.zeros(3, dtype=np.float32)
        self.velocity_profile            = []

        self.ongoing_waypoint            = 1
        self.ongoing_waypoint_refined    = 1


        self.list_position               = [None ]*self.NUM_AGENTS
        self.list_velocity               = [None ]*self.NUM_AGENTS
        self.list_ongoing                = [None ]*self.NUM_AGENTS
        self.list_timestamp              = [None ]*self.NUM_AGENTS
        self.list_flag                   = [False]*self.NUM_AGENTS

        self.position[:2]                = self.trajectory_original[self.id][0].location

        for i in range(self.NUM_AGENTS):
            self.list_position [i]       = np.zeros(3, dtype=np.float32)
            self.list_velocity [i]       = np.zeros(3, dtype=np.float32)
            self.list_ongoing  [i]       = 1
            self.list_timestamp[i]       = 0


class Waypoint:

    def __init__(self, id : int, idx : int, location : np.ndarray, is_virtual=False):

        self.id         = id
        self.idx        = idx
        self.location   = location
        self.is_virtual = is_virtual

        if type(location) == list: self.location = np.array(location)

    def __str__(self):
        return 'Waypoint || ID : {:<5} | INDEX : {:<5} | LOCATION : [{:^5}, {:^5}]'.format(self.id, self.idx, round(self.location[0],2), round(self.location[1],2))
    
    def __eq__(self, other : "Waypoint"):  
        return     all(self.location == other.location)

    def __ne__(self, other : "Waypoint"):  
        return not all(self.location == other.location)


def trajectory_from_array(id : int, traj_array : np.ndarray):
    return [Waypoint(id=id,idx=i,location=traj_array[i]) for i in range(len(traj_array))]

def array_from_trajectory(traj : typing.List[Waypoint]):
    return np.array([wp.location for wp in traj], dtype=np.float32)

def segment_lengths_from_trajectory(traj : typing.List[Waypoint]):
    return np.array([nl.norm(traj[i].location - traj[i+1].location) for i in range(len(traj)-1)])

def cutoff_timestamp(timestamp : float, max_digits : int = 2):
    return timestamp - int(timestamp // 100)*100

def clear_lines(linenum):
    for _ in range(linenum): print(CLR+UP(1)+CLR,end="")

def vector_3d_to_2d(v):
    return np.array([v[0], v[1]])

def vector_2d_to_3d(v):
    return np.array([v[0], v[1], 0])

def seperate_segments(list_traj : typing.List[typing.List[Waypoint]], interval : float):
    for traj in list_traj:
        id = traj[0].id
        for n in range(len(traj)-1,0,-1):
            d = nl.norm(np.array(traj[n-1].location) - np.array(traj[n].location))
            Nnwp = int(d/interval) - 1
            alphalist = np.linspace(0,1,Nnwp+2)[1:-1]

            new_traj = [Waypoint(id=id, idx=-1, location=(1-alpha)*traj[n-1].location + alpha*traj[n].location, is_virtual=True) for alpha in alphalist]
            traj[n:n]= new_traj

    return list_traj