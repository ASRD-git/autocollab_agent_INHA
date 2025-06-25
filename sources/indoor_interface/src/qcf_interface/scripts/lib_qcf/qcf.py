from lib_qcf.base           import *
from lib_qcf.cf_interface   import CFInterface
from lib_qcf.com_reciever   import ComReciever
from lib_qcf.com_transmiter import ComTransmiter

class QCF:

    def __init__(self, whoami, config):

        self.shared_memory  = SharedMemory(whoami, config)

        rclpy.init()
        signal.signal(signal.SIGINT, self._signal_handler)
        
        self.shared_memory.flag_is_running = True

        self.com_reciever   = ComReciever   (self.shared_memory)
        self.com_transmiter = ComTransmiter (self.shared_memory)
        self.controller     = CFInterface   (self.shared_memory)

        self.wait_for_ready()


    def _signal_handler(self, sig, frame):
        print("Signal interrupt")
        self.close()


    def wait_for_ready(self):
        while not self.shared_memory.mission_phase == 1:
            if not self.shared_memory.flag_is_running: return
            time.sleep(1e-3)


    def close(self):
        self.shared_memory.flag_is_running    = False
        self.controller.close()
        
        if rclpy.ok(): 
            print("shutting down rclpy")
            rclpy.shutdown()
