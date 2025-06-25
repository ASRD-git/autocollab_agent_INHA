import os
import sys
import json
import time
import signal
import typing
import copy
import threading
import logging

import numpy                as np
import numpy.linalg         as nl

# Crazyflie library
import  cflib.crtp
from    cflib.crazyflie                 import Crazyflie
from    cflib.crazyflie.log             import LogConfig
from    cflib.crazyflie.mem             import MemoryElement
from    cflib.crazyflie.mem             import Poly4D
from    cflib.crazyflie.syncCrazyflie   import SyncCrazyflie
from    cflib.crazyflie.syncLogger      import SyncLogger
from    cflib.crazyflie.swarm           import Swarm
from    cflib.utils                     import uri_helper

# ROS2 library
import rclpy
from   rclpy.node                       import Node
from   rclpy.qos                        import QoSProfile, ReliabilityPolicy, DurabilityPolicy
from   std_msgs.msg                     import Bool, Float32MultiArray, String
from   macspos_msgs.msg                 import AgentExternalState, AgentInternalState, AgentInternalSetpoint
from   mocap4r2_msgs.msg                import RigidBodies

UP = lambda x : f"\033[{x}A"
CLR = "\033[K"
RED = "\033[31m"
GRN = "\033[32m"
YEL = "\033[33m"
GRY = "\033[8m"
NML = "\033[0m"

class SharedMemory:
    def __init__(self, whoami, config):
        self.id         = whoami
        self.num_agents = config['NUM_AGENTS']
        self.uri        = config['CRAZYFLIE']['URI_ADDRESS']
        self.body_name  = config['CRAZYFLIE']['BODY_NAME'  ]
        self.traj_list  = config['TRAJECTORY']

        self.init_position = None
        self.dest_position = None

        self.position_qualisys  = np.zeros(3, dtype=np.float32)
        self.velocity_qualisys  = np.zeros(3, dtype=np.float32)
        self.attitude_qualisys  = np.zeros(4, dtype=np.float32)

        self.position_crazyflie = np.zeros(3, dtype=np.float32)
        self.velocity_crazyflie = np.zeros(3, dtype=np.float32)

        self.position_setpoint  = np.zeros(3, dtype=np.float32)
        self.velocity_setpoint  = np.zeros(3, dtype=np.float32)

        self.hover_alt = None

        self.mission_phase = 0
        self.control_mode  = 0
        self.control_mode_desc =    { 
                                    0   :   "hold",
                                    1   :   "position",
                                    2   :   "velocity",
                                    3   :   "land"
                                    }
        
        self.flag_is_running                = False
        self.flag_is_logging                = False
        self.flag_is_activated              = False
        self.flag_is_qtm_available          = False
        self.flag_is_ready_to_flight        = [False]*self.num_agents
        self.flag_is_arrived_to_init_point  = [False]*self.num_agents
        self.flag_is_arrived_to_dest_point  = [False]*self.num_agents

        self.initialize()


    def initialize(self):

        traj  = self.traj_list[str(self.id)]
        self.init_position = np.array(traj[0])
        self.dest_position = np.array(traj[-1])