from lib_macspos.base           import *
from lib_macspos.trajec_handler import *

class MACSPOSSolver:

    def __init__(self, shared_memory : SharedMemory):   
        
        self.shared_memory = shared_memory

        threading.Thread(target=self.macspos_solver_loop).start()


    def macspos_solver_loop(self):
        self.wait_for_start()
        self.wait_for_activation()
        self.run_until_activation(self.task, self.shared_memory.MINIMUM_LOOP_PERIOD_S, self.init_task)
        # self.terminate()


    def wait_for_start(self):
        while not self.shared_memory.flag__is_running:
            if self.shared_memory.flag__is_killed: return
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def wait_for_activation(self):
        while not (self.shared_memory.flag__is_activated and all(self.shared_memory.list_flag)):
            if not self.shared_memory.flag__is_running: return
            time.sleep(self.shared_memory.MINIMUM_LOOP_PERIOD_S)


    def terminate(self):
        if rclpy.ok(): rclpy.shutdown()
        sys.exit(0)


    def run_until_activation(self, task, loop_period, init_task = None):
        if init_task is not None: init_task()
        while self.shared_memory.flag__is_running and self.shared_memory.flag__is_activated and not self.shared_memory.flag__is_arrived:
            task()
            time.sleep(loop_period)


    def init_task(self):
        self._replaned_time = time.time()
        self._tracking_time = self.shared_memory.SOLUTION_UPDATE_PERIOD_S + self._replaned_time


    def task(self):

        if self._tracking_time >= self.shared_memory.SOLUTION_UPDATE_PERIOD_S + self._replaned_time and not self.shared_memory.flag__is_arrived:

            self.shared_memory.flag__is_solving = True

            list_traj_trimmed = copy.deepcopy(self.shared_memory.trajectory_trimmed)
            list_traj_refined, list_cp, list_sl = self._refine_trajec(list_traj_trimmed)

            status, velocity_profile = self._solve(list_traj_refined, list_cp, list_sl)

            if status == "converged":
                id            = self.shared_memory.id
                self.shared_memory.trajectory_refined[id]   = list_traj_refined[id]
                self.shared_memory.velocity_profile         = velocity_profile     
                self.shared_memory.ongoing_waypoint_refined = 1
            
            self.shared_memory.flag__is_solving = False
            self.shared_memory.solver_status    = status

            self._replaned_time = time.time()
            self._tracking_time = time.time()

        else: 

            self._tracking_time = time.time()


    def _refine_trajec(self, list_traj : typing.List[typing.List[Waypoint]]):
        
        list_cp = []

        for i in range(self.shared_memory.NUM_AGENTS):
            for j in range(i+1,self.shared_memory.NUM_AGENTS):
                traji = list_traj[i]
                trajj = list_traj[j]

                _list_cp, traji, trajj = self._insert_intersection(traji, trajj)

                list_cp += _list_cp
                list_traj[i] = traji
                list_traj[j] = trajj

        list_traj = self._seperate_segments(list_traj)

        list_sl = [0]*self.shared_memory.NUM_AGENTS


        for id, traj in enumerate(list_traj):
            for idx, wp in enumerate(traj): wp.idx = idx
            list_sl[id] = segment_lengths_from_trajectory(traj)

        return list_traj, list_cp, list_sl


    def _solve(self, list_traj : typing.List[typing.List[Waypoint]], list_cp : typing.List[typing.List[Waypoint]], list_sl : typing.List[np.ndarray]):
        
        K      = self.shared_memory.NUM_AGENTS
        Nvec   = np.array([len(traj) for traj in list_traj], dtype=int)
        N      = np.sum   (Nvec)
        Ncum   = np.cumsum(Nvec)
        Nmax   = np.max   (Nvec)
        Nc     = len(list_cp)

        q      = np.zeros(( N   ,   1 ))
        Q      = np.zeros(( 0   ,   N ))
        Qv     = np.zeros(( 0   ,   N ))
        S1     = np.zeros(( N-K ,   N ))
        S2     = np.zeros(( Nc  ,   N ))
        S3     = np.zeros(( K   ,   N ))
        S4     = np.zeros(( K   ,   N ))
        d      = np.zeros(( N-K ,   1 ))
        t_s    = np.zeros(( Nc  ,   1 ))
        t_init = np.zeros(( K   ,   1 ))
        v_init = np.zeros(( K   ,   1 ))

        t0     = np.zeros(( N   ,   1 ))

        flag__is_v_init_given = False

        for i in range(K):

            # v = nl.norm(self.shared_memory.list_velocity[i])

            # if not self.shared_memory.MINIMUM_SPEED_MS <= v <= self.shared_memory.MAXIMUM_SPEED_MS: flag__is_v_init_given = False

            # t_init[i]                                                       = self.shared_memory.list_timestamp[i]
            q [Ncum[i]-1]                                                   = 1
            d [Ncum[i]-Nvec[i]-i:Ncum[i]-1-i, 0                         ]   = list_sl[i]
            S1[Ncum[i]-Nvec[i]-i:Ncum[i]-1-i, Ncum[i]-Nvec[i]:Ncum[i]-1 ]   = np.diag(-np.ones(Nvec[i]-1))
            S1[Ncum[i]-Nvec[i]-i:Ncum[i]-1-i, Ncum[i]-Nvec[i]+1:Ncum[i] ]  += np.diag(np.ones(Nvec[i]-1))
            S3[i                            , Ncum[i]-Nvec[i]           ]   = 1
            # S4[i                            , Ncum[i]-Nvec[i]           ]   = -1
            # S4[i                            , Ncum[i]-Nvec[i]+1         ]   = 1
            
            # Qv_                                                             = np.zeros((Nvec[i]-2, N)) 
            # Qv_[:                           ,Ncum[i]-Nvec[i]  :Ncum[i]-2]  -= np.diag(list_sl[i][1:])
            # Qv_[:                           ,Ncum[i]-Nvec[i]+1:Ncum[i]-1]  += np.diag(list_sl[i][:-1] + list_sl[i][1:])
            # Qv_[:                           ,Ncum[i]-Nvec[i]+2:Ncum[i]  ]  -= np.diag(list_sl[i][:-1])
            # Qv                                                              = np.vstack((Qv, Qv_))

            for j in range(i+1,K):
            
                Qi                                                          = np.zeros(N)
                Qi[Ncum[i]-1                                        ]       = 1
                Qi[Ncum[j]-1                                        ]       = -1
                Q                                                           = np.vstack((Q, Qi))

            if flag__is_v_init_given:                
                t0[Ncum[i]-Nvec[i]+1:Ncum[i], 0] = np.cumsum(list_sl[i]) / nl.norm(self.shared_memory.list_velocity[i])
                v_init[i] = list_sl[i][0] / nl.norm(self.shared_memory.list_velocity[i])
            else:
                t0[Ncum[i]-Nvec[i]+1:Ncum[i], 0] = np.cumsum(list_sl[i]) / self.shared_memory.MAXIMUM_SPEED_MS

        for i in range(Nc):

            S2[i, Ncum[list_cp[i][0].id]-Nvec[list_cp[i][0].id]+list_cp[i][0].idx] = 1
            S2[i, Ncum[list_cp[i][1].id]-Nvec[list_cp[i][1].id]+list_cp[i][1].idx] = -1
            t_s[i] = min(self.shared_memory.SAFETY_DISTANCE_M/(self.shared_memory.MINIMUM_SPEED_MS * np.sin(list_cp[i][2] )),\
                         self.shared_memory.SAFETY_DISTANCE_M/(self.shared_memory.MINIMUM_SPEED_MS * np.sin(np.deg2rad(30))))

        # t_init = t_init - cutoff_timestamp(time.time())
        t_init[self.shared_memory.id] = 0

        # P = 0.1*Qv.T@Qv + 0.9*q @ q.T + 0*Q.T @ Q
        P = Q.T @ Q                               ## log1,2
        # P = 5*Qv.T@Qv + 10*q @ q.T + 5*Q.T @ Q        ## log3
        # P = 0*Qv.T@Qv + 100*q @ q.T + 0*Q.T @ Q          ## log4
        

        # q = np.zeros_like(q)

        if flag__is_v_init_given:
            A = np.vstack((S1, S2, S3, S4))
            U = np.vstack(( np.eye(N-K), np.zeros((Nc+2*K,N-K)) ))
            M = np.vstack(( np.zeros((N-K,Nc)), np.eye(Nc), np.zeros((2*K,Nc)) ))
            b = np.vstack(( np.zeros((N-K+Nc,1)), t_init, v_init ))

            self.t_c   = t0
            self.x_c   = S1@self.t_c
            self.y_c   = np.zeros(( Nc      , 1 ))
            self.w_c   = np.zeros(( N+Nc+K  , 1 ))


        else:

            A = np.vstack((S1, S2, S3))
            U = np.vstack(( np.eye(N-K), np.zeros((Nc+K,N-K)) ))
            M = np.vstack(( np.zeros((N-K,Nc)), np.eye(Nc), np.zeros((K,Nc)) ))
            b = np.vstack(( np.zeros((N-K+Nc,1)), t_init))

            self.t_c   = t0
            self.x_c   = S1@self.t_c
            self.y_c   = np.zeros(( Nc   , 1 ))
            self.w_c   = np.zeros(( N+Nc , 1 ))


        R    = P + (self.shared_memory.SOLVER_STEP_SIZE/2)*A.T@A
        Rinv = nl.inv(R)

        self.t_p   = self.t_c.copy()
        self.x_p   = self.x_c.copy()
        self.y_p   = self.y_c.copy()
        self.w_p   = self.w_c.copy()

        self.pr_list = np.zeros(self.shared_memory.SOLVER_MAXIMUM_ITERATIONS)
        self.dr_list = np.zeros(self.shared_memory.SOLVER_MAXIMUM_ITERATIONS)

        iterations = 0
        status = "not converged"

        for i in range(1,self.shared_memory.SOLVER_MAXIMUM_ITERATIONS):

            point2 = time.time()

            self._update_t(A, Rinv,  U,  M,  b,  q,  Ncum,  Nvec,  K  )
            self._update_x(S1, d,  N,  K                              )
            self._update_y(S2, t_s,N,  Nc, K                          )
            self._update_w(A,  U,  M,  b                              )

            pr   = nl.norm(A@self.t_c - U@self.x_c - M@self.y_c - b)
            dr   = nl.norm(self.w_c - self.w_p)

            self.pr_list[i] = pr
            self.dr_list[i] = dr

            if pr < 0.1 and abs(self.pr_list[i-1]-self.pr_list[i])/(self.pr_list[i-1]+1e-8) < self.shared_memory.SOLVER_TOLERANCE:
                
                status = "converged"
                iterations += 1
                break

            iterations += 1

            # print(f"{i}'th iteration : {pr}", end="\r")

        print(f"{i}'th iteration : {pr}")
        print(A@self.t_c - U@self.x_c - M@self.y_c - b)

        self.pr_list = self.pr_list[1:iterations+1]
        self.dr_list = self.dr_list[1:iterations+1]

        # print(f"Agent #{self.shared_memory.id} || status : {status}, iterations : {iterations}, time : {round(end-start,4)}s")

        id     = self.shared_memory.id
        topt   = self.x_c[Ncum[id]-Nvec[id]-id:Ncum[id]-1-id,0]
        seglen = list_sl[id]
        velocity_profile = seglen / topt

        return status, velocity_profile


    def _seperate_segments(self, list_traj : typing.List[typing.List[Waypoint]]):
    
        for traj in list_traj:

            id = traj[0].id
            for n in range(len(traj)-1,0,-1):
                d = nl.norm(np.array(traj[n-1].location) - np.array(traj[n].location))
                Nnwp = int(d/self.shared_memory.SEGMENT_INTERVAL_M) - 1
                alphalist = np.linspace(0,1,Nnwp+2)[1:-1]

                new_traj = [Waypoint(id=id, idx=-1, location=(1-alpha)*traj[n-1].location + alpha*traj[n].location, is_virtual=True) for alpha in alphalist]
                traj[n:n]= new_traj

        return list_traj

    def _find_intersection(self,p11 : np.ndarray, p12 : np.ndarray, p21 : np.ndarray, p22 : np.ndarray):
        if np.cross(p12-p11, p22-p21) == 0:   return False, None, None
        
        else:
            t1 = np.cross(p21-p11, p22-p21) / np.cross(p12-p11, p22-p21)
            t2 = np.cross(p21-p11, p12-p11) / np.cross(p12-p11, p22-p21)
            ang = np.arccos((p12-p11) @ (p22-p21) / nl.norm(p12-p11) / nl.norm(p22-p21))
            
        if 0 <= t1 <= 1 and 0 <= t2 <= 1:     return True,  p11 + t1*(p12-p11), ang
        else:                                 return False, None, None

    def _insert_intersection(self, traj1 : typing.List[Waypoint], traj2 : typing.List[Waypoint]):
        
        list_cp = []

        N1 = len(traj1)
        N2 = len(traj2)

        for n in range(N1-1, 0, -1):
            for m in range(N2-1, 0, -1):

                wp11 = traj1[n-1]
                wp21 = traj2[m-1]
                wp12 = traj1[n]
                wp22 = traj2[m]

                intersect, location, angle = self._find_intersection(wp11.location, wp12.location, wp21.location, wp22.location)

                if intersect:
                    cp1 = Waypoint(id=wp11.id,location=location,idx=0,is_virtual=True)
                    cp2 = Waypoint(id=wp21.id,location=location,idx=0,is_virtual=True)
                    insertion = [True, True]

                    if wp12==cp1:
                        cp1           = wp12
                        insertion[0]  = False

                    if wp11==cp1:
                        cp1           = wp11
                        insertion[0]  = False

                    if wp22==cp2:
                        cp2           = wp22
                        insertion[1]  = False

                    if wp21==cp2:
                        cp2           = wp21
                        insertion[1]  = False

                    if insertion[0]: traj1.insert(n, cp1)
                    if insertion[1]: traj2.insert(m, cp2)

                    list_cp.append([cp1, cp2, angle])
        return list_cp, traj1, traj2

    def _calc_cost(self, A, P, U, M, b, q):

        t = self.t_p
        x = self.x_p
        y = self.y_p

        Jp = t.T@P@t + q.T@t

        rp = A@t - U@x - M@y - b

        t = self.t_c
        x = self.x_c
        y = self.y_c

        Jc = t.T@P@t + q.T@t
        rc = A@t - U@x - M@y - b

        return Jp,rp, Jc, rc

    def _update_t(self, A, Rinv, U, M, b, q, Ncum, Nvec, K):

        x   = self.x_p
        y   = self.y_p
        w   = self.w_p

        b   = 0.5 * (q + self.shared_memory.SOLVER_STEP_SIZE*A.T@( -U@x - M@y - b + w ))

        self.t_p[:] = self.t_c[:]
        self.t_c = -Rinv @ b

        self.t_c[[Ncum[i] - Nvec[i] for i in range(K)],0] = 0


    def _update_x(self, S1, d, N, K):

        t   = self.t_c
        w   = self.w_p

        x   = S1@t + w[:N-K]

        if self.shared_memory.MINIMUM_SPEED_MS == 0:
    
            under = x < d/self.shared_memory.MAXIMUM_SPEED_MS
    
            x[under] = d[under]/self.shared_memory.MAXIMUM_SPEED_MS
    
        else:

            under = x < d/self.shared_memory.MAXIMUM_SPEED_MS
            over  = x > d/self.shared_memory.MINIMUM_SPEED_MS

            x[under] = d[under]/self.shared_memory.MAXIMUM_SPEED_MS
            x[over ] = d[over ]/self.shared_memory.MINIMUM_SPEED_MS

        self.x_p[:] = self.x_c[:]
        self.x_c = x


    def _update_y(self, S2, t_s, N, Nc, K):

        t   = self.t_c
        w   = self.w_p

        y   = S2@t + w[N-K:N-K+Nc]

        under = np.where((-t_s < y) & (y < 0))[0]
        over  = np.where((0 < y) & (y < t_s))[0]

        y[under] = -t_s[under]
        y[over ] = t_s[over]

        self.y_p[:] = self.y_c[:]
        self.y_c = y


    def _update_w(self, A, U, M, b):

        t   = self.t_c
        x   = self.x_c
        y   = self.y_c

        w   = self.w_p

        w   = w + A@t - U@x - M@y - b

        self.w_p[:] = self.w_c[:]
        self.w_c = w
        