from lib_macspos.base           import *

class ComTransmiter(Node):

    def __init__(self, shared_memory : SharedMemory):

        self.shared_memory = shared_memory

        super().__init__(f'agent_{self.shared_memory.id}_tx')

        self.extern_state_pub    = self.create_publisher(AgentExternalState,    f'extern_state',                            10)
        self.intern_setpoint_pub = self.create_publisher(AgentInternalSetpoint, f'intern_{self.shared_memory.id}_setpoint', 10)
        # self.traj_v_pub          = self.create_publisher(Float32MultiArray,     f'intern_{self.shared_memory.id}_trajectory', 10)
        # self.traj_c_pub          = self.create_publisher(Float32MultiArray,     f'intern_{self.shared_memory.id}_trajectory_c', 10)

        threading.Thread(target=self.extern_state_pub_loop).start()
        threading.Thread(target=self.intern_setpoint_pub_loop).start()


    def extern_state_pub_loop(self):
        self.wait_for_start_extern_state_pub_loop()
        self.run_until_activation(self.publish_extern_state, self.shared_memory.EXTERN_ROSPUB_LOOP_PERIOD_S)
        # self.terminate()

    def intern_setpoint_pub_loop(self):
        self.wait_for_start_intern_setpoint_pub_loop()
        self.run_until_activation(self.publish_intern_setpoint, self.shared_memory.INTERN_ROSPUB_LOOP_PERIOD_S)
        # self.terminate()

    def terminate(self):
        if rclpy.ok(): rclpy.shutdown()
        sys.exit(0)


    def wait_for_start_extern_state_pub_loop(self):
        while not self.shared_memory.flag__is_running:
            if self.shared_memory.flag__is_killed: return
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def wait_for_start_intern_setpoint_pub_loop(self):
        while not (self.shared_memory.flag__is_running and self.shared_memory.solver_status == "converged"):
            if self.shared_memory.flag__is_killed: return
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def run_until_activation(self, task, loop_period, init_task = None):
        if init_task is not None: init_task()
        while self.shared_memory.flag__is_running:
            task()
            time.sleep(loop_period)


    def publish_extern_state(self):
        msg           = AgentExternalState()
        msg.id        = self.shared_memory.id
        msg.position  = self.shared_memory.position
        msg.velocity  = self.shared_memory.velocity
        msg.ongoing   = self.shared_memory.ongoing_waypoint
        msg.timestamp = cutoff_timestamp(time.time())

        self.extern_state_pub.publish(msg)


    def publish_intern_setpoint(self):
        msg                   = AgentInternalSetpoint()
        msg.control_mode      = 2
        msg.position_setpoint = self.shared_memory.position_setpoint
        msg.velocity_setpoint = self.shared_memory.velocity_setpoint

        self.intern_setpoint_pub.publish(msg)

        # self.publish_intern_trajectory()
        # self.publish_intern_trajectory_c()


    # def publish_intern_trajectory(self):
    #     msg                   = Float32MultiArray()
    #     msg.data              = array_from_trajectory(self.shared_memory.trajectory_refined[self.shared_memory.id]).flatten().tolist()
        
    #     self.traj_v_pub.publish(msg)


    # def publish_intern_trajectory_c(self):
    #     msg                   = Float32MultiArray()
    #     msg.data              = array_from_trajectory(self.shared_memory.trajectory_trimmed[self.shared_memory.id]).flatten().tolist()
        
    #     self.traj_c_pub.publish(msg)