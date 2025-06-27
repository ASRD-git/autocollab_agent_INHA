import os
import sys
import json
import time
import signal
import copy
import threading
import asyncio
import typing

import numpy                as np
import numpy.linalg         as nl

import rclpy
from   rclpy.node           import Node
from   rclpy.qos            import QoSProfile
from   std_msgs.msg         import Bool, Float32MultiArray
from   macspos_msgs.msg     import AgentExternalState, AgentInternalState, AgentInternalSetpoint

from   mavsdk             import System
from   mavsdk.offboard    import OffboardError, VelocityNedYaw, PositionNedYaw



UP = lambda x : f"\033[{x}A"
CLR = "\033[K"

class SharedMemory:

    def __init__(self, params, config):

        self.NUM_AGENTS                  = config['NUM_AGENTS'                  ]
        self.trajectory_original         = config['TRAJECTORY'                  ]
        self.list_home_position          = config['HOME_POSITIONS'              ]

        self.EXTERN_ROSPUB_LOOP_PERIOD_S = params['EXTERN_ROSPUB_LOOP_PERIOD_S' ]
        self.INTERN_ROSPUB_LOOP_PERIOD_S = params['INTERN_ROSPUB_LOOP_PERIOD_S' ]
        self.MINIMUM_LOOP_PERIOD_S       = params['MINIMUM_LOOP_PERIOD_S'       ]

        self.list_udp_port               = None
        self.list_mavsdk_port            = None
        self.list_init_position          = None
        self.list_dest_position          = None
        self.list_position               = None
        self.list_velocity               = None
        self.list_position_setpoint      = None
        self.list_velocity_setpoint      = None
        self.list_control_mode           = None
        self.list_flag__is_conncected    = None
        self.flag__is_activated          = False
        self.flag__is_running            = False

        self._initialize()


    def _initialize(self):
            
        self.list_udp_port               = [None ]*self.NUM_AGENTS
        self.list_mavsdk_port            = [None ]*self.NUM_AGENTS
        self.list_position               = [None ]*self.NUM_AGENTS
        self.list_velocity               = [None ]*self.NUM_AGENTS
        self.list_position_setpoint      = [None ]*self.NUM_AGENTS
        self.list_velocity_setpoint      = [None ]*self.NUM_AGENTS
        self.list_init_position          = [None ]*self.NUM_AGENTS
        self.list_dest_position          = [None ]*self.NUM_AGENTS
        self.list_flag__is_conncected    = [False]*self.NUM_AGENTS
        self.list_control_mode           = [  0  ]*self.NUM_AGENTS

        for i in range(self.NUM_AGENTS):
            self.list_udp_port         [i] = "udp://:1454" + str(i)
            self.list_mavsdk_port      [i] = 50040 + (i)
            self.list_position         [i] = np.zeros(3, dtype=np.float32)
            self.list_velocity         [i] = np.zeros(3, dtype=np.float32)
            self.list_position_setpoint[i] = np.zeros(3, dtype=np.float32)
            self.list_velocity_setpoint[i] = np.zeros(3, dtype=np.float32)
            self.list_init_position    [i] = np.array(self.trajectory_original[str(i)][0])
            self.list_dest_position    [i] = np.array(self.trajectory_original[str(i)][-1])
            self.list_home_position    [i] = np.array(self.list_home_position[str(i)])


def cutoff_timestamp(timestamp : float, max_digits : int = 2):
    return timestamp - int(timestamp // 100)*100