from lib_gzros2.base          import *
from lib_gzros2.ros2wrapper   import *
from lib_gzros2.agent         import *
from lib_gzros2.swarm         import *


class GZROS2:

    def __init__(self, params, config):
        
        self.shared_memory  = SharedMemory(params, config)

        self.agents      = [PX4Agent(id, self.shared_memory) for id in range(self.shared_memory.NUM_AGENTS)]
        self.swarm       = PX4Swarm(self.agents, self.shared_memory)
        self.ros2wrapper = ROS2Wrapper(self.shared_memory)

        rclpy.init()
        signal.signal(signal.SIGINT, self._signal_handler)

        threading.Thread(target=self.ros2wrapper.run_receiver).start()
        threading.Thread(target=self.ros2wrapper.run_transmitter).start()
        threading.Thread(target=self.swarm.run).start()

        self.maximum_runtime    = 60
        self.maximum_timesteps  = int(self.maximum_runtime / self.shared_memory.MINIMUM_LOOP_PERIOD_S)
        self.runtime            = 0

        self.log_position     = [0] * self.shared_memory.NUM_AGENTS
        self.log_velocity     = [0] * self.shared_memory.NUM_AGENTS
        self.log_velocity_cmd = [0] * self.shared_memory.NUM_AGENTS
        self.log_timesteps    = np.zeros(self.maximum_timesteps)

        for id in range(self.shared_memory.NUM_AGENTS):
            self.log_position[id]     = np.zeros((self.maximum_timesteps, 3))
            self.log_velocity[id]     = np.zeros((self.maximum_timesteps, 3))
            self.log_velocity_cmd[id] = np.zeros((self.maximum_timesteps, 3))
            

        self.run()


    def _signal_handler(self, sig, frame):
        self.shared_memory.flag__is_running         = False
        self.shared_memory.flag__is_activated       = False
        self.shared_memory.list_flag__is_conncected = [False]*self.shared_memory.NUM_AGENTS

        if rclpy.ok(): rclpy.shutdown()
        

    def run(self):

        print("Step 0 : wait for all agents to connect")

        while not all(self.shared_memory.list_flag__is_conncected): 
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)

        print("Step 0 : connected")

        self.shared_memory.flag__is_running = True

        ### Step 1 : go to initial position ###
        hover_alt = 5.0

        init_position = np.zeros((self.shared_memory.NUM_AGENTS,3))
        dest_position = np.zeros((self.shared_memory.NUM_AGENTS,3))

        for id in range(self.shared_memory.NUM_AGENTS):
            init_xy = self.shared_memory.list_init_position[id]
            dest_xy = self.shared_memory.list_dest_position[id]
            init_position[id] = [init_xy[0], init_xy[1], hover_alt]
            dest_position[id] = [dest_xy[0], dest_xy[1], hover_alt]
            
            self.set_position(id, init_position[id])

        print("Step 1 : go to initial position")

        while not all([nl.norm(self.shared_memory.list_position[id] - init_position[id])<0.2 for id in range(self.shared_memory.NUM_AGENTS)]):
            if not self.shared_memory.flag__is_running: return
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)

        self.shared_memory.flag__is_activated = True
        print("Step 1 : arrived to initial position")

        start = time.time()

        ### Step 2 : mission ###
        while not all([nl.norm(self.shared_memory.list_position[id] - dest_position[id])<0.2 for id in range(self.shared_memory.NUM_AGENTS)]):
            
            self.log_timesteps[self.runtime] = time.time() - start
            for id in range(self.shared_memory.NUM_AGENTS):
                self.log_position[id][self.runtime]     = self.shared_memory.list_position[id]
                self.log_velocity[id][self.runtime]     = self.shared_memory.list_velocity[id]
                self.log_velocity_cmd[id][self.runtime] = self.shared_memory.list_velocity_setpoint[id]

            
            self.runtime += 1

            if not self.shared_memory.flag__is_running: break
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)

        print("Step 2 : mission done")

        
        self.log_timesteps = self.log_timesteps[:self.runtime]

        for id in range(self.shared_memory.NUM_AGENTS):
            self.log_position[id]     = self.log_position[id][:self.runtime]
            self.log_velocity[id]     = self.log_velocity[id][:self.runtime]
            self.log_velocity_cmd[id] = self.log_velocity_cmd[id][:self.runtime]

        np.save("logs/log_timesteps.npy",    self.log_timesteps)
        np.save("logs/log_position.npy",     self.log_position)
        np.save("logs/log_velocity.npy",     self.log_velocity)
        np.save("logs/log_velocity_cmd.npy", self.log_velocity_cmd)
        print("Step 3 : logs saved")

    def set_hovering(self, id):
        self.shared_memory.list_control_mode[id]      = 0

    def set_position(self, id, position_setpoint):
        self.shared_memory.list_control_mode[id]      = 1
        self.shared_memory.list_position_setpoint[id] = position_setpoint

    def set_velocity(self, id, velocity_setpoint):
        self.shared_memory.list_control_mode[id]      = 2
        self.shared_memory.list_velocity_setpoint[id] = velocity_setpoint
