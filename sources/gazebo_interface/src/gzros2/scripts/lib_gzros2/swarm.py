#!/usr/bin/python3
from lib_gzros2.base           import *
from lib_gzros2.agent          import *


class PX4Swarm:

    def __init__(self, agents : typing.List[PX4Agent], shared_memory : SharedMemory):

        self.agents = agents
        self.shared_memory = shared_memory        
    
    async def connect_all(self, loop : asyncio.AbstractEventLoop):

        print("### PX4 Swarm ###")
        print("connecting to all agents..\n")

        for agent in self.agents: 
            connect = loop.create_task(agent.connect())
            await connect


    def run(self):

        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)

        loop.create_task(self.connect_all(loop))

        telem = [loop.create_task(agent.telem_loop()) for agent in self.agents]

        for agent in self.agents: loop.create_task(agent.cntrl_loop())

        loop.run_until_complete(asyncio.gather(*telem))