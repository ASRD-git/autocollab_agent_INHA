from lib_qcf.base           import *

class ComTransmiter(Node):

    def __init__(self, shared_memory : SharedMemory):

        self.shared_memory = shared_memory

        super().__init__(f'agent_{self.shared_memory.id}_tx')
        
        self.intern_state_pub    = self.create_publisher(AgentInternalState,        f'intern_{self.shared_memory.id}_state', 10)
        self.mission_phase_pub   = self.create_publisher(String,                    'mission_phase',  10)
        self.activation_pub      = self.create_publisher(Bool,                      f'activation',   10)

        threading.Thread(target=self.intern_state_pub_loop).start()
        threading.Thread(target=self.mission_phase_pub_loop).start()
        threading.Thread(target=self.activation_pub_loop).start()


    def intern_state_pub_loop(self):
        self.run_until_activation(self.publish_intern_state, 1e-5)

    def mission_phase_pub_loop(self):
        self.run_until_activation(self.publish_mission_phase, 1e-5)

    def activation_pub_loop(self):
        self.run_until_activation(self.publish_activation, 1e-5)

    def run_until_activation(self, task, loop_period):
        while self.shared_memory.flag_is_running:
            task()
            time.sleep(loop_period)


    def publish_intern_state(self):
        msg                   = AgentInternalState()
        msg.position          = self.shared_memory.position_crazyflie
        msg.velocity          = self.shared_memory.velocity_crazyflie

        self.intern_state_pub.publish(msg)


    def publish_mission_phase(self):
        msg                   = String()
        msg.data              = f"{self.shared_memory.id},{self.shared_memory.mission_phase}"

        self.mission_phase_pub.publish(msg)


    def publish_activation(self):
        msg                   = Bool()
        msg.data              = self.shared_memory.flag_is_activated
        
        self.activation_pub.publish(msg)