#!/usr/bin/python3
from lib_gzros2.base           import *



class PX4Agent:

    def __init__(self, id : int, shared_memory : SharedMemory):

        self.id             = id
        self.shared_memory  = shared_memory

        self.system         = System(port=shared_memory.list_mavsdk_port[id])

        self.cmd_type       = 0

    
    async def connect(self):
        id       = self.id
        udp_port = self.shared_memory.list_udp_port[id]

        print(f"### Agent {id} ###")
        print(f"connecting to {udp_port}..")

        await self.system.connect(system_address=udp_port)
            
        print(f"connected to {udp_port}     \n")

        self.shared_memory.list_flag__is_conncected[id] = True
    

    async def offboard_start(self):
        id       = self.id

        await self.system.offboard.set_position_ned(
            PositionNedYaw(0.0, 0.0, 0.0, 0.0))
        
        await self.system.offboard.set_velocity_ned(
            VelocityNedYaw(0.0, 0.0, 0.0, 0.0))

        try:
            await self.system.offboard.start()
            print(f"Agent.{id} : Offboard Start")

            return True

        except OffboardError as error:

            print(f"Agent.{id} : Offboard failed : \
                {error._result.result}")

            return False


    async def telem_loop(self):
        id       = self.id

        while not self.shared_memory.list_flag__is_conncected[id]:    await asyncio.sleep(0.1)

        async for pos_ned in self.system.telemetry.position_velocity_ned():
            
            self.shared_memory.list_position[id][0] =  pos_ned.position.east_m    +   self.shared_memory.list_home_position[id][0]
            self.shared_memory.list_position[id][1] =  pos_ned.position.north_m   +   self.shared_memory.list_home_position[id][1]
            self.shared_memory.list_position[id][2] = -pos_ned.position.down_m    +   self.shared_memory.list_home_position[id][2]
            self.shared_memory.list_velocity[id][0] =  pos_ned.velocity.east_m_s
            self.shared_memory.list_velocity[id][1] =  pos_ned.velocity.north_m_s
            self.shared_memory.list_velocity[id][2] = -pos_ned.velocity.down_m_s
            await asyncio.sleep(0.001)


    async def cntrl_loop(self):
        id       = self.id

        while not self.shared_memory.list_flag__is_conncected[id]:    await asyncio.sleep(0.1)

        print(f"Agent.{id} : control start")

        await self.system.action.arm()        

        await self.offboard_start()

        while self.shared_memory.list_flag__is_conncected[id]:  

            if   self.shared_memory.list_control_mode[id] == 0:
                await asyncio.sleep(0.001)

            elif self.shared_memory.list_control_mode[id] == 1:
                await self.system.offboard.set_position_ned(
                    PositionNedYaw( self.shared_memory.list_position_setpoint[id][1]   -   self.shared_memory.list_home_position[id][1],
                                    self.shared_memory.list_position_setpoint[id][0]   -   self.shared_memory.list_home_position[id][0],
                                   -self.shared_memory.list_position_setpoint[id][2],
                                    0.0))
                self.shared_memory.list_control_mode[id] = 0

            elif self.shared_memory.list_control_mode[id] == 2:
                await self.system.offboard.set_velocity_ned(
                    VelocityNedYaw( self.shared_memory.list_velocity_setpoint[id][1],
                                    self.shared_memory.list_velocity_setpoint[id][0],
                                   -self.shared_memory.list_velocity_setpoint[id][2],
                                    0.0))
                self.shared_memory.list_control_mode[id] = 0

    