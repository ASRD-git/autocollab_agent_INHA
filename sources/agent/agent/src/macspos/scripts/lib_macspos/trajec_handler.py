from lib_macspos.base           import *
from lib_macspos.macspos_solver import *

class TrajecHandler:

    def __init__(self, shared_memory : SharedMemory):
        
        self.shared_memory = shared_memory

        threading.Thread(target=self.trajec_handler_loop).start()


    def trajec_handler_loop(self):
        self.wait_for_start()
        self.wait_for_activation()
        self.run_until_activation(self.task, self.shared_memory.MINIMUM_LOOP_PERIOD_S)
        # self.terminate()

    def wait_for_start(self):
        while not self.shared_memory.flag__is_running:
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def wait_for_activation(self):
        while not (self.shared_memory.flag__is_activated and all(self.shared_memory.list_flag)):
            if not self.shared_memory.flag__is_killed: return
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def wait_for_start(self):
        while not self.shared_memory.flag__is_running:
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def run_until_activation(self, task, loop_period, init_task = None):
        if init_task is not None: init_task()
        while self.shared_memory.flag__is_running:
            task()
            time.sleep(loop_period)


    def terminate(self):
        if rclpy.ok(): rclpy.shutdown()
        sys.exit(0)


    def task(self):

        if self._is_arrived(): self._action_arrived()

        if not self.shared_memory.flag__is_solving:
            self._update_self_trajec()
            self._update_other_trajec()
            self._update_self_vel_setpoint()


    def _update_self_trajec(self):
        id     = self.shared_memory.id
        pos    = self.shared_memory.position[:2]
        vel    = self.shared_memory.velocity[:2]
        traj_o = self.shared_memory.trajectory_original[id]
        traj_r = self.shared_memory.trajectory_refined [id]
        og_i_o = self.shared_memory.ongoing_waypoint
        og_i_r = self.shared_memory.ongoing_waypoint_refined
        
        og_wp_o  = traj_o[og_i_o]
        og_wp_r  = traj_r[og_i_r]
        og_pos_o = og_wp_o.location
        og_pos_r = og_wp_r.location
        l_pos = pos + vel * self.shared_memory.LOOKAHEAD_HORIZON_S

        if self._is_passed(l_pos, og_pos_o, pos, vel): self.shared_memory.ongoing_waypoint         += 1
        if self._is_passed(l_pos, og_pos_r, pos, vel): self.shared_memory.ongoing_waypoint_refined += 1
            
        traj_t    = traj_o[self.shared_memory.ongoing_waypoint-1:]
        traj_t[0] = Waypoint(id=id, idx=0, location=pos, is_virtual=False)

        self.shared_memory.list_ongoing[id]       = self.shared_memory.ongoing_waypoint
        self.shared_memory.trajectory_trimmed[id] = traj_t


    def _update_other_trajec(self):
        for id in range(self.shared_memory.NUM_AGENTS):
            if id == self.shared_memory.id: continue

            pos       = self.shared_memory.list_position[id][:2]
            traj_o    = self.shared_memory.trajectory_original[id]
            og_i_o    = self.shared_memory.list_ongoing[id]
            
            traj_t    = traj_o[og_i_o-1:]    
            traj_t[0] = Waypoint(id=id, idx=0, location=pos, is_virtual=False)
            self.shared_memory.trajectory_trimmed[id] = traj_t


    def _update_self_vel_setpoint(self):
        id       = self.shared_memory.id
        pos      = self.shared_memory.position[:2]
        vprf     = self.shared_memory.velocity_profile
        traj_r   = self.shared_memory.trajectory_refined[id]
        og_i_r   = self.shared_memory.ongoing_waypoint_refined

        if len(traj_r) == og_i_r:
            self._action_arrived()
            return
        
        og_pos_r = traj_r[og_i_r].location
        
        if len(self.shared_memory.velocity_profile) == 0: vcmd = np.zeros(3, dtype=np.float32)
        else:
            _vcmd = vprf[og_i_r-1]
            _vdir = og_pos_r - pos
            _vmag = nl.norm(_vdir)
            _vdir = _vdir / _vmag if _vmag > 0 else np.zeros(3)
            vcmd = _vcmd * _vdir

        self.shared_memory.velocity_setpoint = np.array([vcmd[0], vcmd[1], 0], dtype=np.float32)


    def _is_passed(self, lookahead_pos, ongoing_pos, pos, vel):
        return  ((ongoing_pos - lookahead_pos) @ vel < 0) and (nl.norm(pos - ongoing_pos) < self.shared_memory.TRAJEC_PASS_THRESHOLD_M)


    def _is_arrived(self):
        id       = self.shared_memory.id
        pos      = self.shared_memory.position[:2]
        traj_o   = self.shared_memory.trajectory_original[id]

        dest_pos = traj_o[-1].location

        return nl.norm(pos - dest_pos) < 5e-2


    def _action_arrived(self):
        self.shared_memory.flag__is_arrived  = True
        self.shared_memory.velocity_setpoint = np.zeros(3, dtype=np.float32)
        time.sleep(1)
        self.shared_memory.flag__is_running  = False