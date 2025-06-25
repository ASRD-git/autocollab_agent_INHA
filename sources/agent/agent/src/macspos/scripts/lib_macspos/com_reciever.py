from lib_macspos.base           import *

class ComReciever(Node):

    def __init__(self, shared_memory : SharedMemory):

        self.shared_memory = shared_memory

        super().__init__(f'agent_{self.shared_memory.id}_rx')

        qos_prof = QoSProfile(
            depth=10,
            reliability = ReliabilityPolicy.RELIABLE, 
            durability = DurabilityPolicy.VOLATILE
        )

        self.extern_state_sub = self.create_subscription(AgentExternalState, f'extern_state',                         self.extern_state_callback, 10)
        self.intern_state_sub = self.create_subscription(AgentInternalState, f'intern_{self.shared_memory.id}_state', self.intern_state_callback, 10)
        self.activation_sub   = self.create_subscription(Bool,               f'activation',                           self.activation_callback,   10)

        threading.Thread(target=self.sub_lifecycle_loop).start()


    def sub_lifecycle_loop(self):
        self.wait_for_start()
        self.run_until_activation(None, self.shared_memory.EXTERN_ROSPUB_LOOP_PERIOD_S)
        print("sub terminated")
        # self.terminate()


    def wait_for_start(self):
        while not self.shared_memory.flag__is_running:
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def run_until_activation(self, task, loop_period, init_task = None):
        if init_task is not None: init_task()
        try:

            while self.shared_memory.flag__is_running and rclpy.ok():
                rclpy.spin_once(self, timeout_sec=loop_period)

        except   KeyboardInterrupt:  pass
        finally:                     self.destroy_node()


    def terminate(self):
        if rclpy.ok(): rclpy.shutdown()
        sys.exit(0)


    def extern_state_callback(self, msg : AgentExternalState):
        agent_id                                       = msg.id
        self.shared_memory.list_position    [agent_id] = np.array(msg.position)
        self.shared_memory.list_velocity    [agent_id] = np.array(msg.velocity)
        self.shared_memory.list_ongoing     [agent_id] = msg.ongoing
        self.shared_memory.list_timestamp   [agent_id] = msg.timestamp
        self.shared_memory.list_flag        [agent_id] = True


    def intern_state_callback(self, msg : AgentInternalState):
        self.shared_memory.position                    = np.array(msg.position)
        self.shared_memory.velocity                    = np.array(msg.velocity)
        # print("InternStateCallback ", msg.position)

        
    def activation_callback(self, msg : Bool):
        self.shared_memory.flag__is_activated = msg.data
