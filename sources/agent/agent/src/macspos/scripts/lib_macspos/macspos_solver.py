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
            list_traj_refined, wps_list = self._refine_trajec(list_traj_trimmed)

            status, velocity_profile = self._solve(wps_list)

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
        
        list_traj = self._seperate_segments(list_traj)

        wps_list = [0]*self.shared_memory.NUM_AGENTS

        for id, traj in enumerate(list_traj): wps_list[id] = array_from_trajectory(traj)

        return list_traj, wps_list


    def _solve(self, wps_list : typing.List[np.ndarray]):

        s = time.time()
        
        self.wps_list = wps_list

        self.vmin, self.vmax = self.shared_memory.MINIMUM_SPEED_MS, self.shared_memory.MAXIMUM_SPEED_MS
        self.d_s      = self.shared_memory.SAFETY_DISTANCE_M

        self.K    = self.shared_memory.NUM_AGENTS
        self.Ni   = [wps.shape[0] for wps in wps_list]
        self.Ni0  = np.array([0,*np.cumsum(self.Ni)])
        self.N    = np.sum(self.Ni)

        self.d_list  = [0]*self.K
        self.t0_list = [0]*self.K
        self.v0_list = [0]*self.K 

        self.rho    = 1000
        self.Niter  = 100
        self.crit   = 1e-2
        self.traj_res = 50

        self.get_d_list()
        self.get_coeffmtx()

        ### solve 

        self.t_c   = self.tinit.copy()
        self.x_c   = self.S1@self.t_c
        self.u_c   = np.zeros((self.A.shape[0],1))

        self.t_p   = self.t_c.copy()
        self.x_p   = self.x_c.copy()
        self.u_p   = self.u_c.copy()

        pr_list = np.zeros(self.Niter)
        dr_list = np.zeros(self.Niter)

        iterations = 0
        status = "not converged"

        for i in range(1,self.Niter):

            self._update_t()
            self._update_x()
            self._update_u()

            pr   = nl.norm(self.A@self.t_c - self.U@self.x_c - self.b)
            dr   = nl.norm(self.u_c-self.u_p)

            pr_list[i] = pr
            dr_list[i] = dr

            # print(f"{i}/{self.Niter} | {pr}", end="\r")

            # print(f"iter     : {i}")
            # print(f"update t : {t2-t1:.5f}s")
            # print(f"update x : {t3-t2:.5f}s")
            # print(f"update u : {t4-t3:.5f}s")

            if pr_list[i] < self.crit:
                status = "converged"
                break

            iterations += 1
        
        print(f"iter : {i} | status : {status} | residual : {pr:.3f} | runtime : {time.time()-s:.2f}s")

        id     = self.shared_memory.id
        topt   = self.x_c[self.Ni0[id]-id:self.Ni0[id]+self.Ni[id]-id-1,0]
        seglen = self.d_list[id]
        velocity_profile = seglen / topt

        print(velocity_profile)

        return status, velocity_profile
    

    def get_d_list(self):
        for i in range(self.K): self.d_list[i] = np.linalg.norm(self.wps_list[i][1:] - self.wps_list[i][:-1], axis=1)


    def get_coeffmtx(self):
        K       = self.K
        N       = self.N
        Ni      = self.Ni
        Ni0     = self.Ni0

        self.q  = np.zeros((N,1))
        self.Q  = np.zeros((N-2*K,N))
        self.Qv = np.zeros((0,N))
        self.S1 = np.zeros((N-K,N))   # v const
        self.S2 = np.zeros((K,N))     # t0 const
        self.S3 = np.zeros((K,N))     # v0 const

        self.t0 = np.zeros((K,1))
        self.v0 = np.zeros((K,1))

        self.d = np.zeros((N-K,1))

        self.tinit = np.zeros((self.N,1))

        for i in range(K):
            self.q[Ni0[i]] = 1
            self.S1[Ni0[i]-i:Ni0[i]+Ni[i]-i-1, Ni0[i]:Ni0[i]+Ni[i]-1] = np.diag(-np.ones(Ni[i]-1))
            self.S1[Ni0[i]-i:Ni0[i]+Ni[i]-i-1, Ni0[i]+1:Ni0[i]+Ni[i]] += np.diag(np.ones(Ni[i]-1))
            self.S2[i, Ni0[i]] = 1
            self.S3[i, Ni0[i]]   = -1
            self.S3[i, Ni0[i]+1] = 1

            self.t0[i] = self.t0_list[i]
            # self.v0[i] = self.d_list[i][0] / self.t0_list[i]

            self.d[Ni0[i]-i:Ni0[i]+Ni[i]-i-1,0] = self.d_list[i]

            self.tinit[self.Ni0[i],0] = self.t0_list[i]
            self.tinit[self.Ni0[i]+1:self.Ni0[i]+self.Ni[i],0] = self.d_list[i]/self.vmax + self.t0_list[i]

        # self.A = np.vstack((self.S1, self.S2, self.S3))
        # self.U = np.vstack(( np.eye(N-K),         np.zeros((K,N-K)),     np.zeros((K,N-K)) ))
        # self.b = np.vstack(( np.zeros((N-K,1)), self.t0, self.v0 ))

        self.A = np.vstack(( self.S1,
                            self.S2))
        self.U = np.vstack(( np.eye(N-K),
                            np.zeros((K,N-K))))
        self.b = np.vstack(( np.zeros((N-K,1)),
                            self.t0))

        self.P = self.q@self.q.T
        self.Rinv = nl.inv(self.P + (self.rho/2)*self.A.T@self.A)


    def _update_t(self):

        x   = self.x_p
        u   = self.u_p

        b   = 0.5 * (self.q + self.rho*self.A.T@( -self.U@x - self.b + u ))

        self.t_p[:] = self.t_c[:]
        self.t_c = -self.Rinv @ b
        self.t_c = self.proj(self.t_c)


    def _update_x(self):

        t   = self.t_c
        u   = self.u_p

        x   = self.S1@t + u[:self.N-self.K]

        under = x < self.d/self.vmax
        over  = x > self.d/self.vmin

        x[under] = self.d[under]/self.vmax
        x[over ] = self.d[over ]/self.vmin

        self.x_p[:] = self.x_c[:]
        self.x_c = x


    def _update_u(self):

        t   = self.t_c
        x   = self.x_c
        u   = self.u_p

        u   = u + self.A@t - self.U@x - self.b

        self.u_p[:] = self.u_c[:]
        self.u_c = u


    def _calc_trajectory(self):
        t_max  = np.max(self.t_c)
        t_list = np.linspace(0,t_max, self.traj_res)
        p_list = np.zeros((self.K, 2, self.traj_res))

        for i in range(self.K):
            wps = self.wps_list[i]
            Ni  = wps.shape[0]
            ti  = self.t_c[self.Ni0[i]:self.Ni0[i]+self.Ni[i]]
            ti_list = np.clip(t_list, np.min(ti), np.max(ti))

            for n in range(self.Ni[i]-1):
                t1, t2 = self.t_c[self.Ni0[i]+n], self.t_c[self.Ni0[i]+n+1]
                p1, p2 = wps[n], wps[n+1]
                v      = (p2-p1)/(t2-t1) if t2-t1>0 else (p2-p1)/nl.norm(p2-p1)*self.vmax

                idx_seg = np.logical_and(ti_list>=t1, ti_list<=t2)
                t_seg   = ti_list[idx_seg]
                p_list[i, :, idx_seg] = p1[None,:] + v[None,:]*(t_seg[:,None] - t1)

        return p_list, t_list


    def _get_collision_segments(self, p_list, t_list):
        seg_col = np.zeros((0,4), dtype=int)
        p_col   = np.zeros((0,4,2))
        t_col   = np.zeros((0,4))
        t_lims  = np.zeros((0,4))

        for i in range(self.K):
            ti = self.t_c[self.Ni0[i]:self.Ni0[i]+self.Ni[i]]
            for j in range(i+1,self.K):
                tj = self.t_c[self.Ni0[j]:self.Ni0[j]+self.Ni[j]]

                d = nl.norm(p_list[i]-p_list[j], axis=0)

                idx_col    = (d<=self.d_s).astype(int)
                idx_col    = idx_col[1:]-idx_col[:-1]
                idx_col_lb = np.where(idx_col==1)[0]
                t_col_lb   = t_list[np.where(idx_col==1)[0]]
                t_col_ub   = t_list[np.where(idx_col==-1)[0]]

                seg_col_ij = np.zeros((t_col_lb.shape[0],4), dtype=int)
                p_col_ij   = np.zeros((t_col_lb.shape[0],4,2))
                t_col_ij   = np.zeros((t_col_lb.shape[0],4))
                t_lims_ij  = np.zeros((t_col_lb.shape[0],4))

                k = 0

                for _ in range(t_col_lb.shape[0]):

                    try:
                        n_l = np.where(ti<=t_col_lb[k])[0][-1]
                        n_u = np.where(ti>=t_col_ub[k])[0][0]
                        m_l = np.where(tj<=t_col_lb[k])[0][-1]
                        m_u = np.where(tj>=t_col_ub[k])[0][0]
                    except:
                        continue

                    n = int((n_l+n_u)/2)
                    m = int((m_l+m_u)/2)

                    seg_col_ij[k,0] = i
                    seg_col_ij[k,1] = j
                    seg_col_ij[k,2] = n
                    seg_col_ij[k,3] = m
                    p_col_ij[k,0,:] = self.wps_list[i][n]
                    p_col_ij[k,1,:] = self.wps_list[i][n+1]
                    p_col_ij[k,2,:] = self.wps_list[j][m]
                    p_col_ij[k,3,:] = self.wps_list[j][m+1]
                    t_col_ij[k,0]   = self.t_c[self.Ni0[i]+n,0]
                    t_col_ij[k,1]   = self.t_c[self.Ni0[i]+n+1,0]
                    t_col_ij[k,2]   = self.t_c[self.Ni0[j]+m,0]
                    t_col_ij[k,3]   = self.t_c[self.Ni0[j]+m+1,0]
                    t_lims_ij[k,0]  = self.t_c[self.Ni0[i]+n-1,0]+self.d_list[i][n-1]/self.vmax if n!=0            else -np.inf
                    t_lims_ij[k,1]  = self.t_c[self.Ni0[i]+n+2,0]-self.d_list[i][n+1]/self.vmax if n+2!=self.Ni[i] else np.inf
                    t_lims_ij[k,2]  = self.t_c[self.Ni0[j]+m-1,0]+self.d_list[j][m-1]/self.vmax if m!=0            else -np.inf
                    t_lims_ij[k,3]  = self.t_c[self.Ni0[j]+m+2,0]-self.d_list[j][m+1]/self.vmax if m+2!=self.Ni[j] else np.inf

                    k+=1

                seg_col = np.concatenate((seg_col, seg_col_ij[:k]))
                p_col   = np.concatenate((p_col, p_col_ij[:k]))
                t_col   = np.concatenate((t_col, t_col_ij[:k]))
                t_lims  = np.concatenate((t_lims, t_lims_ij[:k]))

        return seg_col, p_col, t_col, t_lims


    def _calc_dmin(self, p, t):

        dpi = p[:,1,:] - p[:,0,:]
        dti = t[:,1] - t[:,0]
        dpj = p[:,3,:] - p[:,2,:]
        dtj = t[:,3] - t[:,2]

        neg_dti = dti<=0
        neg_dtj = dtj<=0

        if any(neg_dti):
            dti[neg_dti] = nl.norm(dpi, axis=1)[neg_dti]/self.vmax
        if any(neg_dtj):
            dtj[neg_dtj] = nl.norm(dpj, axis=1)[neg_dtj]/self.vmax

        v1_i = dpi/dti[:,None]
        v1_j = dpj/dtj[:,None]

        a = v1_i - v1_j
        b = p[:,0,:] - p[:,2,:] + v1_j*t[:,2,None] - v1_i*t[:,0,None] # N x 2 x 1

        tmin = - np.sum(a * b, axis=1) / nl.norm(a, axis=1)**2
        dmin = nl.norm( a*tmin[:,None]+b, axis=1)

        return dmin


    def _calc_ddmindx(self,p,x,tper=0.01):
        N = x.shape[0]

        dx    = np.zeros((N*4,4))
        dp    = np.zeros((N*4,4,2))
        dmin0 = np.zeros((N*4,1))

        dmin = self._calc_dmin(p,x)

        for i in range(N):
            dp[4*i:4*i+4]  = p[i]
            dx[4*i:4*i+4]  = x[i]
            dx[4*i:4*i+4] += tper*np.eye(4)
            dmin0[4*i:4*i+4] = dmin[i]

        ddmindx = (self._calc_dmin(dp,dx).reshape(-1,1) - dmin0.reshape(-1,1))/tper
        ddmindx = ddmindx.reshape(N,4)
        return dmin, ddmindx


    def proj(self, t):
        p_list, t_list = self._calc_trajectory()

        _seg_col, _p, _t, _t_lims = self._get_collision_segments(p_list, t_list)
        Nc = _seg_col.shape[0]

        if Nc == 0: return t

        _x = _t.copy()
        e_c, e_p = 1,1


        for iter in range(100):

            t1 = time.time()
            dmin, ddmindx = self._calc_ddmindx(_p, _x, 0.01)
            t2 = time.time()

            de    = 0*nl.norm(_x - _t, axis=1)**2 + dmin - self.d_s

            JTJ = sl.block_diag(*[ddmindx[k].reshape(-1,1) @ ddmindx[k].reshape(1,-1) for k in range(Nc)])
            JTf = np.block([ddmindx[k].reshape(1,-1)*de[k] for k in range(Nc)]).T

            _x = _x - nl.solve(1e-8*np.eye(4*Nc)+JTJ,JTf).reshape(Nc,4)
            t3 = time.time()

            _x[:,0:2] = np.clip(_x[:,0:2],_t_lims[:,0,None],_t_lims[:,1,None])
            _x[:,2:4] = np.clip(_x[:,2:4],_t_lims[:,2,None],_t_lims[:,3,None])

            e_c = nl.norm(de)
            if e_c < 1e-2: break
            e_p = e_c

        # print(f"iter     : {iter}")
        # print(f"1 : {(t2-t1)*iter:.5f}s")
        # print(f"2 : {(t3-t2)*iter:.5f}s")
        # print(_seg_col)
        # print(_p)
        # print(_t)

        t_proj = t.copy()
        for k,seg in enumerate(_seg_col):
            i,j,n,m = seg
            t_proj[self.Ni0[i]+n]   = _x[k,0]
            t_proj[self.Ni0[i]+n+1] = _x[k,1]
            t_proj[self.Ni0[j]+m]   = _x[k,2]
            t_proj[self.Ni0[j]+m+1] = _x[k,3]

        return t_proj


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
