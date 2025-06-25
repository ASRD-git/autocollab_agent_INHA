from lib_qcf.base           import *

class ComReciever(Node):

    def __init__(self, shared_memory : SharedMemory):

        self.shared_memory = shared_memory

        super().__init__(f'agent_{self.shared_memory.id}_rx')

        self.intern_setpoint_sub = self.create_subscription(AgentInternalSetpoint,  f'intern_{self.shared_memory.id}_setpoint', self.intern_setpoint_callback, 10)
        self.mission_phase_sub   = self.create_subscription(String,                 'mission_phase',   self.mission_phase_callback, 10)
        self.qtm_pos_sub         = self.create_subscription(RigidBodies,            'rigid_bodies',    self.qtm_pos_callback,       10) 

        threading.Thread(target=self.sub_lifecycle_loop).start()


    def sub_lifecycle_loop(self):
        self.run_until_activation(1e-5)


    def run_until_activation(self, loop_period):
        try:
            while self.shared_memory.flag_is_running and rclpy.ok(): rclpy.spin_once(self, timeout_sec=loop_period)
        except   KeyboardInterrupt:  pass
        finally:                     self.destroy_node()

        
    def intern_setpoint_callback(self, msg : AgentInternalState):
        self.shared_memory.velocity_setpoint[0] = msg.velocity_setpoint[0]
        self.shared_memory.velocity_setpoint[1] = msg.velocity_setpoint[1]
        self.shared_memory.velocity_setpoint[2] = msg.velocity_setpoint[2]

        
    def mission_phase_callback(self, msg : String):
        msg = msg.data.split(",")
        
        id    = int(msg[0])
        phase = int(msg[1])

        if   phase == 1: self.shared_memory.flag_is_ready_to_flight[id] = True
        elif phase == 2: self.shared_memory.flag_is_arrived_to_init_point[id] = True
        elif phase == 3: self.shared_memory.flag_is_arrived_to_dest_point[id] = True
        elif phase == 4: self.shared_memory.flag_is_running = False


    def qtm_pos_callback(self, msg : RigidBodies):
        rigid_bodies = msg.rigidbodies
        rigid_body   = rigid_bodies[self.shared_memory.id] 

        position = rigid_body.pose.position
        attitude = rigid_body.pose.orientation

        self.shared_memory.position_qualisys[0] = position.x
        self.shared_memory.position_qualisys[1] = position.y
        self.shared_memory.position_qualisys[2] = position.z

        self.shared_memory.attitude_qualisys[0] = attitude.x
        self.shared_memory.attitude_qualisys[1] = attitude.y
        self.shared_memory.attitude_qualisys[2] = attitude.z
        self.shared_memory.attitude_qualisys[3] = attitude.w

        self.shared_memory.flag_is_qtm_available = True