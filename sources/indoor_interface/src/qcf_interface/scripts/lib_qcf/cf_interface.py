from lib_qcf.base import *
period_in_ms = 10


class CFInterface:

    def __init__(self, shared_memory : SharedMemory):

        self.shared_memory = shared_memory

        # Crazyflie driver initialize
        cflib.crtp.init_drivers()                                           

        uri = uri_helper.uri_from_env(default=shared_memory.uri)

        self.scf            = SyncCrazyflie(
                                                link_uri= uri,
                                                cf      = Crazyflie(rw_cache='./cache')
                                            )
        self.cf             = self.scf.cf

        # Initialize
        self.open_scf_link()
        # if not self.shared_memory.flag_is_running: self.close()

        self.wait_for_param_update()
        # if not self.shared_memory.flag_is_running: self.close()

        self.activate_cf_measurement_reciever()
        # if not self.shared_memory.flag_is_running: self.close()

        self.wait_for_qtm()
        # if not self.shared_memory.flag_is_running: self.close()

        self.extpos_loop = threading.Thread(target=self.send_qtmpos).start()
        # if not self.shared_memory.flag_is_running: self.close()

        # Preflight sequance
        self.activate_kalman()
        # if not self.shared_memory.flag_is_running: self.close()

        self.initialize_kalman_filter()
        # if not self.shared_memory.flag_is_running: self.close()
        
        self.check_state()
        # if not self.shared_memory.flag_is_running: self.close()

        self.shared_memory.mission_phase = 1

        # Mission start
        threading.Thread(target=self.run).start()


    def run(self):

        while self.shared_memory.flag_is_running:

            if   self.shared_memory.control_mode == 0:
                pass
            
            elif self.shared_memory.control_mode == 1:
                self.cf.commander.send_position_setpoint(self.shared_memory.position_setpoint[0],
                                                         self.shared_memory.position_setpoint[1],
                                                         self.shared_memory.position_setpoint[2],
                                                         0)

            elif self.shared_memory.control_mode == 2:
                self.cf.commander.send_hover_setpoint(   self.shared_memory.velocity_setpoint[0],
                                                         self.shared_memory.velocity_setpoint[1],
                                                         0,
                                                         self.shared_memory.hover_alt)

            elif self.shared_memory.control_mode == 3:
                self.shared_memory.control_mode = 0
                self.land()

            time.sleep(1e-3)



    def set_position(self,px,py,pz):
        self.shared_memory.control_mode = 1
        self.shared_memory.position_setpoint[0] = px
        self.shared_memory.position_setpoint[1] = py
        self.shared_memory.position_setpoint[2] = pz


    def set_velocity(self,vx,vy,vz):
        self.shared_memory.control_mode = 2
        self.shared_memory.velocity_setpoint[0] = vx
        self.shared_memory.velocity_setpoint[1] = vy
        self.shared_memory.velocity_setpoint[2] = vz


    def set_hover_alt(self,alt):
        self.shared_memory.hover_alt = alt


    def takeoff(self):
        self.set_position(  self.shared_memory.position_qualisys[0],
                            self.shared_memory.position_qualisys[1],
                            self.shared_memory.hover_alt           )
        time.sleep(2)

    
    def land(self):
        self.set_position(  self.shared_memory.position_qualisys[0],
                            self.shared_memory.position_qualisys[1],
                            0.1                                    )

        time.sleep(2)


    def close(self):
        self.scf.close_link()
        sys.exit(0)

    
    def send_qtmpos(self):
        while self.shared_memory.flag_is_running:
            self.cf.extpos.send_extpose(self.shared_memory.position_qualisys[0], 
                                        self.shared_memory.position_qualisys[1], 
                                        self.shared_memory.position_qualisys[2], 
                                        self.shared_memory.attitude_qualisys[0],
                                        self.shared_memory.attitude_qualisys[1],
                                        self.shared_memory.attitude_qualisys[2],
                                        self.shared_memory.attitude_qualisys[3])
            time.sleep(1e-5)        


    def open_scf_link(self):
        # Open Link
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : SyncCrazyflie opened {NML}",                    "< CFInterface >"))
        self.scf.open_link()


    def wait_for_param_update(self):
        # Wait for param update
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Waiting for parameters to be updated {NML}",    "< CFInterface >"))
        while not self.cf.param.is_updated:
            if not self.shared_memory.flag_is_running: return
            time.sleep(1e-3)
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : parameters updated {NML}",                      "< CFInterface >"))


    def activate_cf_measurement_reciever(self):
        # Activate cf measurement reciever
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Crazyflie sensor reciever activated {NML}",     "< CFInterface >"))
        self.start_get_position()
        self.start_get_velocity()


    def start_get_position(self, period_in_ms=period_in_ms):
        log_conf = LogConfig(name="position", period_in_ms=period_in_ms)
        log_conf.add_variable('kalman.stateX', 'FP16')      # m
        log_conf.add_variable('kalman.stateY', 'FP16')      # m
        log_conf.add_variable('kalman.stateZ', 'FP16')      # m
        # log_conf.add_variable('stateEstimate.x', 'FP16')      # m
        # log_conf.add_variable('stateEstimate.y', 'FP16')      # m
        # log_conf.add_variable('stateEstimate.z', 'FP16')      # m

        self.cf.log.add_config(log_conf)
        log_conf.data_received_cb.add_callback(self.position_callback)
        log_conf.start()


    def start_get_velocity(self, period_in_ms=period_in_ms):
        log_conf = LogConfig(name="velocity", period_in_ms=period_in_ms)
        log_conf.add_variable('stateEstimate.vx', 'FP16')
        log_conf.add_variable('stateEstimate.vy', 'FP16')
        log_conf.add_variable('stateEstimate.vz', 'FP16')

        self.cf.log.add_config(log_conf)
        log_conf.data_received_cb.add_callback(self.velocity_callback)
        log_conf.start()
 

    def position_callback(self, timestamp, data, logconf):
        self.shared_memory.position_crazyflie[0] = data['kalman.stateX']
        self.shared_memory.position_crazyflie[1] = data['kalman.stateY']
        self.shared_memory.position_crazyflie[2] = data['kalman.stateZ']
        # self.shared_memory.position_crazyflie[0] = data['stateEstimate.x']
        # self.shared_memory.position_crazyflie[1] = data['stateEstimate.y']
        # self.shared_memory.position_crazyflie[2] = data['stateEstimate.z']
        

    def velocity_callback(self, timestamp, data, logconf):
        self.shared_memory.velocity_crazyflie[0] = data['stateEstimate.vx']
        self.shared_memory.velocity_crazyflie[1] = data['stateEstimate.vy']
        self.shared_memory.velocity_crazyflie[2] = data['stateEstimate.vz']


    def wait_for_qtm(self):
        # Wait for param update
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Waiting for Qualisys {NML}",                    "< CFInterface >"))
        timeout = 5
        t       = time.time()
        while not self.shared_memory.flag_is_qtm_available:
            if time.time()-t > timeout:
                print("{:.<60}{:.>20}".format(f"{RED}Agent #{self.shared_memory.id} : Qualisys not available {NML}",                  "< CFInterface >"))
                self.close()
                return
            
            if not self.shared_memory.flag_is_running: return
            time.sleep(1e-3)
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Qualisys available {NML}",                      "< CFInterface >"))


    def activate_kalman(self):
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Kalman filter activated {NML}",                 "< CFInterface >"))
        # switch to Kalman filter
        self.cf.param.set_value('stabilizer.estimator', '2')
        self.cf.param.set_value('locSrv.extQuatStdDev', 0.06)

        # enable high level commander
        self.cf.param.set_value('commander.enHighLevel', '1')

        # prepare for motor shut-off
        self.cf.param.set_value('motorPowerSet.enable', '0')
        self.cf.param.set_value('motorPowerSet.m1', '0')
        self.cf.param.set_value('motorPowerSet.m2', '0')
        self.cf.param.set_value('motorPowerSet.m3', '0')
        self.cf.param.set_value('motorPowerSet.m4', '0')        

        self.wait_for_param_update()


    def initialize_kalman_filter(self):
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Waiting for kalman filter to converge {NML}",   "< CFInterface >"))
        
        self.cf.param.set_value('kalman.resetEstimation', '1')
        time.sleep(0.1)
        self.cf.param.set_value('kalman.resetEstimation', '0')
    
        log_config = LogConfig(name='Kalman Variance', period_in_ms=500)
        log_config.add_variable('kalman.varPX', 'float')
        log_config.add_variable('kalman.varPY', 'float')
        log_config.add_variable('kalman.varPZ', 'float')

        var_y_history = [1000] * 10
        var_x_history = [1000] * 10
        var_z_history = [1000] * 10

        threshold = 0.001

        with SyncLogger(self.scf, log_config) as logger:
            for log_entry in logger:
                data = log_entry[1]

                var_x_history.append(data['kalman.varPX'])
                var_x_history.pop(0)
                var_y_history.append(data['kalman.varPY'])
                var_y_history.pop(0)
                var_z_history.append(data['kalman.varPZ'])
                var_z_history.pop(0)

                min_x = min(var_x_history)
                max_x = max(var_x_history)
                min_y = min(var_y_history)
                max_y = max(var_y_history)
                min_z = min(var_z_history)
                max_z = max(var_z_history)

                if not self.shared_memory.flag_is_running: return

                if (max_x - min_x) < threshold and (
                        max_y - min_y) < threshold and (
                        max_z - min_z) < threshold:
                    
                    print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Kalman filter converged {NML}",                 "< CFInterface >"))

                    break
                
                time.sleep(1e-5)


    def check_state(self):
        print("{:.<60}{:.>20}".format(f"{NML}Agent #{self.shared_memory.id} : Checking state before flight {NML}",            "< CFInterface >"))
        log_config = LogConfig(name='State', period_in_ms=500)
        log_config.add_variable('stabilizer.roll', 'float')
        log_config.add_variable('stabilizer.pitch', 'float')
        log_config.add_variable('stabilizer.yaw', 'float')

        with SyncLogger(self.scf, log_config) as sync_logger:
            for log_entry in sync_logger:
                log_data = log_entry[1]
                roll    = log_data['stabilizer.roll']
                pitch   = log_data['stabilizer.pitch']
                yaw     = log_data['stabilizer.yaw']

                euler_checks = [('roll', roll, 5), ('pitch', pitch, 5)]
                
                if not self.shared_memory.flag_is_running: return
                
                for name, val, val_max in euler_checks:
                    if abs(val) > val_max:
                        print("{:.<60}{:.>20}".format(f"{RED}Agent #{self.shared_memory.id} : Too much {name}( {val:10.4f} deg ), Aborted {NML}",   "< CFInterface >"))
                        return

                print("{:.<60}{:.>20}".format(f"{GRN}Agent #{self.shared_memory.id} : Preflight sequance done. Ready to fly {NML}",   "< CFInterface >"))
                return