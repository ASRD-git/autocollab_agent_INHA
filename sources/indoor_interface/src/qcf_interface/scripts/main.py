#!/usr/bin/env python3
import json
import sys
import time
import numpy        as np
import numpy.linalg as nl
sys.dont_write_bytecode = True
from   lib_qcf import QCF


def _arg_parser_whoami():
    _args = sys.argv[1:]
    if "-id" in _args: return int(_args[_args.index("-id") +1])

def _arg_parser_config():
    _args = sys.argv[1:]
    if "-config" in _args: return _args[_args.index("-config") +1]

def _load_config():
    with open(_arg_parser_config()) as _config: return json.load(_config) 


if __name__ == '__main__':
    # Sequance 0 : connection ####################################################################
    qcf = QCF(_arg_parser_whoami(), _load_config())

    # Sequance 1 : wait for others connection ####################################################
    while not all(qcf.shared_memory.flag_is_ready_to_flight):
        if not qcf.shared_memory.flag_is_running: sys.exit(0)
        time.sleep(1e-1)


    # Sequance 2    : Go to initial position #####################################################
    # Sequance 2.1  : takeoff
    hover_alt = qcf.shared_memory.id*0.1 + 0.3

    qcf.controller.set_hover_alt(hover_alt)
    qcf.controller.takeoff()

    while not abs(qcf.shared_memory.position_qualisys[2] - hover_alt) < 0.05:
        if not qcf.shared_memory.flag_is_running: sys.exit(0)
        time.sleep(1e-1)


    # Sequance 2.2  : Go to initial position
    qcf.controller.set_position(px=qcf.shared_memory.init_position[0],
                                py=qcf.shared_memory.init_position[1],
                                pz=hover_alt)
    
    while not nl.norm(qcf.shared_memory.init_position[:2] - qcf.shared_memory.position_qualisys[:2]) < 0.05:
        if not qcf.shared_memory.flag_is_running: sys.exit(0)
        time.sleep(1e-1)

    qcf.shared_memory.mission_phase = 2

    # Sequance 2.3  : Wait for others initial position arrival
    while not all(qcf.shared_memory.flag_is_arrived_to_init_point):
        if not qcf.shared_memory.flag_is_running: sys.exit(0)
        time.sleep(1e-1)

    qcf.shared_memory.flag_is_activated = True

    # Sequance 3    : Mission start ##############################################################    
    qcf.shared_memory.control_mode      = 2

    # Sequance 3.1  : Wait for destination arrival
    while not nl.norm(qcf.shared_memory.dest_position[:2] - qcf.shared_memory.position_qualisys[:2]) < 0.05:
        if not qcf.shared_memory.flag_is_running: sys.exit(0)
        time.sleep(1e-1)


    qcf.controller.land()

    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

    qcf.close()

