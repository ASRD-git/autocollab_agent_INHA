from lib_macspos.base           import *
from lib_macspos.com_reciever   import ComReciever
from lib_macspos.com_transmiter import ComTransmiter
from lib_macspos.trajec_handler import TrajecHandler
from lib_macspos.macspos_solver import MACSPOSSolver


class MACSPOS:

    def __init__(self, whoami, params, config):
        
        self.shared_memory  = SharedMemory  (whoami, params, config)

        rclpy.init()
        signal.signal(signal.SIGINT, self._signal_handler)
        
        self.com_reciever   = ComReciever   (self.shared_memory)
        self.com_transmiter = ComTransmiter (self.shared_memory)
        self.trajec_handler = TrajecHandler (self.shared_memory)
        self.macspos_solver = MACSPOSSolver (self.shared_memory)

        self.run()


    def _signal_handler(self, sig, frame):
        self.shared_memory.flag__is_killed    = True   
        self.shared_memory.flag__is_running   = False
        self.shared_memory.flag__is_activated = False


    def run(self):
        self.shared_memory.flag__is_running   = True

        # os.system("clear")
        
        while self.shared_memory.flag__is_running:
            
            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("ID",str(self.shared_memory.id)))
            
            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("POSITION","[{:^5}{:^5}{:^5}]".format(\
            #         f"{self.shared_memory.position[0] : .2f}", \
            #         f"{self.shared_memory.position[1] : .2f}", \
            #         f"{self.shared_memory.position[2] : .2f}")))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("VELOCITY","[{:^5}{:^5}{:^5}]".format(\
            #         f"{self.shared_memory.velocity[0] : .2f}", \
            #         f"{self.shared_memory.velocity[1] : .2f}", \
            #         f"{self.shared_memory.velocity[2] : .2f}")))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("VELOCITY SETPOINT","[{:^5}{:^5}{:^5}]".format(\
            #         f"{self.shared_memory.velocity_setpoint[0] : .2f}", \
            #         f"{self.shared_memory.velocity_setpoint[1] : .2f}", \
            #         f"{self.shared_memory.velocity_setpoint[2] : .2f}")))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("ONGOING",str(self.shared_memory.ongoing_waypoint)))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("ONGOING VIRTUAL",str(self.shared_memory.ongoing_waypoint_refined)))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # _list_on_going = ("{:^5}"*self.shared_memory.NUM_AGENTS).format(*str(self.shared_memory.list_ongoing)[1:-1].split(","))

            # print("|{:<20}|{:^50}|".format("LIST ONGOING",_list_on_going))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # _list_flag = ("{:^5}"*self.shared_memory.NUM_AGENTS).format(*str(self.shared_memory.list_flag).split(","))

            # print("|{:<20}|{:^50}|".format("LIST FLAGS",_list_flag))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("SOLVER RUNNING",str(self.shared_memory.flag__is_solving)))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # print("|{:<20}|{:^50}|".format("SOLVER STATUS",self.shared_memory.solver_status))

            # print("+{:-<20}+{:-<50}+".format("",""))

            # clear_lines(23)
                        
            time.sleep(0.01)

        # os.system("clear")

        if rclpy.ok(): 
            print("shutting down rclpy")
            rclpy.shutdown()
