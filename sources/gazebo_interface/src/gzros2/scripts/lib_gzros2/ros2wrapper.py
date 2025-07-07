from lib_gzros2.base           import *

class ROS2Wrapper:

    def __init__(self, shared_memory : SharedMemory):

        self.shared_memory = shared_memory
                

    def run_transmitter(self):

        transmitter = Node('sim_transmitter')

        list_intern_state_pub = [transmitter.create_publisher(AgentInternalState, f'intern_{id}_state', 10) for id in range(self.shared_memory.NUM_AGENTS)]
        activation_pub        = transmitter.create_publisher(Bool, 'activation', 10)

        while not all(self.shared_memory.list_flag__is_conncected): 
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)

        while all(self.shared_memory.list_flag__is_conncected):

            for id in range(self.shared_memory.NUM_AGENTS):

                msg = AgentInternalState()
                msg.position = self.shared_memory.list_position[id]
                msg.velocity = self.shared_memory.list_velocity[id]

                list_intern_state_pub[id].publish(msg)

            if self.shared_memory.flag__is_activated: activation_pub.publish(Bool(data=self.shared_memory.flag__is_activated))

            time.sleep(self.shared_memory.INTERN_ROSPUB_LOOP_PERIOD_S)

        transmitter.destroy_node()


    def run_receiver(self):

        receiver = Node('sim_receiver')

        list_intern_setpoint_sub     = [receiver.create_subscription(AgentInternalSetpoint, f'intern_{i}_setpoint', lambda msg, id=i: self.intern_setpoint_callback(msg, id), 10) for i in range(self.shared_memory.NUM_AGENTS)]

        while not all(self.shared_memory.list_flag__is_conncected): 
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)

        while all(self.shared_memory.list_flag__is_conncected) and rclpy.ok():
            rclpy.spin_once(receiver, timeout_sec=self.shared_memory.MINIMUM_LOOP_PERIOD_S)
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)

        receiver.destroy_node()


    def intern_setpoint_callback(self, msg : AgentInternalSetpoint, id : int):
        self.shared_memory.list_control_mode[id]      = msg.control_mode
        self.shared_memory.list_position_setpoint[id] = msg.position_setpoint
        self.shared_memory.list_velocity_setpoint[id] = msg.velocity_setpoint
