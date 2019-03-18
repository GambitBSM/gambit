*     Two-loop strong corrections to the Higgs mass matrices with Dirac Gauginos
*
*     code written by Mark Goodsell (goodsell@lpthe.jussieu.fr)
*     Adapted from Pietro Slavich's routines in arXiv:0907.4682
*     See arXiv:xxxx.xxxx
*
*     Latest modifications on 18/11/2014
*
*************************************************************************


      subroutine effpotasat(lp,mt,mg1,mg2,R112,R122,md32,T1,T2,st,ct,
     $     O1,O2,sO,cO,q2,tanb,vv,ls,lt,mu,vs,vt,as,
     $     DMS,DMP,tad) 

      implicit none

      integer i,j,lp
      double precision mt,mg1,mg2,R112,R122,md32,T1,T2,st,ct,
     $     O1,O2,sO,cO,q2,tanb,vv,ls,lt,mu,vs,vt,as,
     $     DMS(0:3,0:3),DMP(0:3,0:3),tad(0:3)
      double precision c2t,s2t,c2O,s2O,At,mut,Xt,ht,sbe,pi,k
      double precision F1t,F2t,F3t,Ft,Fphi,FG


      f3t = 0d0
      ft = 0d0
      f2t = 0d0
      f1t = 0d0
      fphi = 0d0
c      fg = 0d0

      pi = 4d0*atan(1.d0)

      if(lp.eq.1) then
         k = 3d0/(16d0*Pi**2)   ! one-loop factor
      elseif(lp.eq.2) then
c         k = as/(16d0*Pi**3)    ! two-loop factor
         k = as/(64d0*Pi**3)    ! two-loop factor, taking into account the factor of four between me and pietro
      else
         k = 0d0
      endif



      s2t = 2d0*ct*st
      c2t = ct**2 - st**2

c      s2O = 2d0*cO*sO
c      c2O = cO**2 - sO**2

c     Correct some errors in earlier versions, blimey what a fool ...
      s2O = sO**2
      c2O = cO**2

      mut = mu+ls*vs+lt*vt
     
      Xt = (T1-T2)*s2t/2d0/mt    
      At = Xt + mut/tanb         

      sbe = dsin(datan(tanb))
c      cbe = sbe/tanb

      ht = mt/vv/sbe            ! v ~ 174
 


      if(lp.eq.1) then          !the usual one-loop functions
         
         Ft = T1*(log(T1/q2)-1)-T2*(log(T2/q2)-1)
         
         F1t = log(T1*T2/mt**4)
         
         F2t = log(T1/T2)
         
         F3t = 2-(T1+T2)/(T1-T2)*log(T1/T2)

         Fphi = 0d0

c        FA = Ft
  
      elseif(lp.eq.2) then
         
 
         call makefuncsDNM(mt,mg1,mg2,R112,R122,T1,T2,s2t,c2t,
     $     O1,O2,s2O,c2O,md32,q2,tanb,At,mu,F1t,F2t,F3t,Ft,Fphi,FG)

      endif

      
c     now build up the results

c     SCALAR ******************************************

      DMS(0,0) = .5d0*ht**2*mut**2*s2t**2*F3t
     $     + ht**2*tanb*mut*At/(T1-T2)*Ft

      DMS(0,1) = - ht**2*mut*mt*s2t*F2t - .5d0*ht**2*At*mut*s2t**2*F3t
     $     - ht**2*mut*At/(T1-T2)*Ft

      DMS(0,2) = .5d0*ht*ls*mut*mt*s2t**2/tanb*F3t
     $     - ht*ls*mt*(At - 2*mut/tanb)/(T1-T2)*Ft

      DMS(1,1) = 2d0*ht**2*mt**2*F1t + 2d0*ht**2*At*mt*s2t*F2t
     $     + .5d0*ht**2*At**2*s2t**2*F3t
     $     + ht**2/tanb*mut*At/(T1-T2)*Ft
      
      DMS(1,2) = -.5d0*ht*ls*At*mt*s2t**2/tanb*F3t
     $     - ht*ls*mt**2*s2t/tanb*F2t - ht*ls*mt*At/(T1-T2)/tanb*Ft

      DMS(2,2) = .5d0*ls**2*s2t**2*mt**2/tanb**2*F3t
c     $     +l**2*mt**2/tanb*At/mu/(T1-T2)*Ft
     $     +ls*mt**2/vs/tanb/(T1-T2)*(At-(mu+vt*lt)/tanb)*Ft
      
      DMS(2,1) = DMS(1,2)
      DMS(1,0) = DMS(0,1)
      DMS(2,0) = DMS(0,2)

      DMS(0,3) = .5d0*ht*lt*mut*mt*s2t**2/tanb*F3t-mt*ht*lt/(T1-T2)
     $     *(At-2*mut/tanb)*Ft

      DMS(1,3) =  -.5d0*ht*lt*At*mt*s2t**2/tanb*F3t
     $     - ht*lt*mt**2*s2t/tanb*F2t 
     $     -At*ht*mt*lt/tanb/(T1-T2)*Ft

      DMS(2,3) = .5d0*ls*lt*s2t**2*mt**2/tanb**2*F3t
     $     +ls*lt*mt**2/tanb**2/(T1-T2)*Ft

      DMS(3,3) = .5d0*lt**2*s2t**2*mt**2/tanb**2*F3t
     $     +lt*mt**2/vt/tanb/(T1-T2)*(At-(mu+vs*ls)/tanb)*Ft

      DMS(3,0) = DMS(0,3)
      DMS(3,1) = DMS(1,3)
      DMS(3,2) = DMS(2,3)

      


      do i=0,3
         do j=0,3
            DMS(i,j) = k*DMS(i,j)
         enddo
      enddo

c     PSEUDOSCALAR ******************************************

      DMP(0,0) = ht**2*mut*At/(T1-T2)*Ft*tanb 
     $     +mut**2*ht**2*tanb*Fphi

      DMP(0,1) = ht**2*mut*At/(T1-T2)*Ft
     $     +mut**2*ht**2*Fphi

      DMP(0,2) = ls*ht*mt*At/(T1-T2)*Ft
     $     +mt*mut*ht*ls*Fphi

      DMP(1,1) = ht**2*mut*At/(T1-T2)*Ft/tanb
     $     +mut**2*ht**2/tanb*Fphi      

      DMP(1,2) = ls*ht*mt*At/(T1-T2)*Ft/tanb
     $     +mt*mut*ht*ls/tanb*Fphi
      
      DMP(2,2) = ls/vs*mt**2*(At-(mu+vt*lt)/tanb)/(T1-T2)*Ft/tanb
     $     +mt**2*ls**2/tanb*Fphi

      DMP(1,0) = DMP(0,1)
      DMP(2,0) = DMP(0,2)
      DMP(2,1) = DMP(1,2)

      DMP(0,3) = lt*ht*mt*At/(T1-T2)*Ft
     $     +mt*mut*ht*lt*Fphi

      DMP(1,3) = lt*ht*mt*At/(T1-T2)*Ft/tanb
     $     +mt*mut*ht*lt/tanb*Fphi

      DMP(2,3) = mt**2*ls*lt/(T1-T2)/(tanb**2)*Ft
     $     +mt**2*ls*lt/tanb*Fphi

      DMP(3,3) = lt/vt*mt**2*(At-(mu+vs*ls)/tanb)/(T1-T2)*Ft/tanb
     $     +mt**2*lt**2/tanb*Fphi

      DMP(3,0) = DMP(0,3)
      DMP(3,1) = DMP(1,3)
      DMP(3,2) = DMP(2,3)

      do i=0,3
         do j=0,3
            DMP(i,j) = k*DMP(i,j)
         enddo
      enddo

c     TADPOLE ******************************************

      tad(0) = -s2t*ht*mut/sqrt(2d0)*Ft
      tad(1) = sqrt(2d0)*ht*mt*FG+s2t*At*ht/sqrt(2d0)*Ft
      tad(2) = -s2t*ls*mt/tanb/sqrt(2d0)*Ft
      tad(3) = -s2t*lt*mt/tanb/sqrt(2d0)*Ft

c      write(*,*) "Tad: ",tad

      do i=0,3
         tad(i) = k*tad(i)
         enddo

c     ******************************************



      return
      end



      

*
***********************************************************************
*



      
      subroutine makefuncsDNM(mt,mg1,mg2,R112,R122,T1,T2,s2t,c2t,
     $     O1,O2,s2O,c2O,md32,q2,tanb,At,mu,F1t,F2t,F3t,Ft,Fphi,FG)

      implicit none

      double precision mt,mg1,mg2,R112,R122,T1,T2,s2t,c2t,
     $     O1,O2,s2O,c2O,md32,q2,tanb,At,mu,F1t,F2t,F3t,Ft,Fphi,FG
      
      double precision Dt,DT1,DT2,Dc2t,DT1T1,DT2T2,Dtt,Dc2tc2t,
     $     DT1t,DT2t,DT1T2,Dtc2t,DT1c2t,DT2c2t,Dcptmptt


      call makederivDNM(mt,mg1,mg2,R112,R122,T1,T2,s2t,c2t,
     $     O1,O2,s2O,c2O,md32,q2,
     $     Dt,DT1,DT2,DT1T1,DT1t,DT2t,DT1c2t,DT1T2,DT2T2,DT2c2t,
     $     Dtt,Dc2t,Dc2tc2t,Dtc2t,Dcptmptt)







      F1t = Dtt + DT1T1 + DT2T2 + 2d0*(DT1t + DT2t + DT1T2)

      F2t = DT1T1 - DT2T2 + DT1t - DT2t
     $     -4d0*c2t**2/(T1-T2)*(Dtc2t + DT1c2t + DT2c2t)
      
      F3t = DT1T1 + DT2T2 - 2d0*DT1T2
     $     - 2d0/(T1-T2)*(DT1-DT2)
     $     + 16d0*c2t**2/(T1-T2)**2*(c2t**2*Dc2tc2t + 2d0*Dc2t)
     $     -8d0*c2t**2/(T1-T2)*(DT1c2t-DT2c2t)

      Ft = DT1 - DT2 - 4d0*c2t**2/(T1-T2)*Dc2t      
      
c      FA = Ft - 2*mu/tanb/At/(T1-T2)/s2t**2*Dcptmptt

      Fphi = -2/tanb/((T1-T2)**2)/(s2t**2)*Dcptmptt

      FG = Dt + DT1 + DT2
      


      return
      end






*
***********************************************************************
*
      subroutine makederivDNM(mt,mg1,mg2,R112,R122,T1,T2,s2t,c2t,
     $     O1,O2,s2O,c2O,md32,q,
     $     Dt,DT1,DT2,DT1T1,DT1t,DT2t,DT1c2t,DT1T2,DT2T2,DT2c2t,
     $     Dtt,Dc2t,Dc2tc2t,Dtc2t,Dcptmptt)

      implicit none

      double precision mt,mg1,mg2,R112,R122,T1,T2,s2t,c2t,
     $     O1,O2,s2O,c2O,md32,q,
     $     Dt,DT1,DT2,DT1T1,DT1t,DT2t,DT1c2t,DT1T2,DT2T2,DT2c2t,
     $     Dtt,Dc2t,Dc2tc2t,Dtc2t,Dcptmptt
      
c      double precision deltNM,phiNM,II,JJ

      double precision t,g,Logt,Logg,logg1,logg2,LogT1,LogT2,LogO1,LogO2
      
c      double precision mg1,mg2,g1,g2,R112,R122,s2O,c2O,md32,O1,O2
      double precision g1,g2

      double precision II,JJ,II0,deltNM,phiNM

      double precision II0_t,II0_T1, II0_T2
      double precision II_T1_T1_O1,II_T1_T1_O2,II_T1_T2_O1,II_T1_T2_O2,
     $     II_T2_T2_O1,II_T2_T2_O2,
     $     JJ_T1_T1,JJ_T1_T2,JJ_T2_T2,II_T1_g1_t,II_T1_g2_t,
     $     II_T2_g1_t,II_T2_g2_t
      double precision phi_T1_T1_O1,phi_T1_T2_O1,phi_T2_T2_O1,
     $     phi_T1_T1_O2,phi_T1_T2_O2,phi_T2_T2_O2
      
      double precision phi_T1_g1_t,phi_T1_g2_t,phi_T2_g1_t,
     $     phi_T2_g2_t

      double precision delta_T1_g1_t,delta_T1_g2_t,delta_T2_g1_t,
     $     delta_T2_g2_t
      double precision delta_T1_T1_O1,delta_T1_T2_O1,delta_T2_T2_O1,
     $     delta_T1_T1_O2,delta_T1_T2_O2,delta_T2_T2_O2
      

      t = mt**2


      g1 = mg1**2
      g2 = mg2**2



      
      Logt = Log(t/q)
      Logg1 = Log(g1/q)
      Logg2 = Log(g2/q)
      LogT1 = Log(T1/q)
      LogT2 = Log(T2/q)      
      LogO1 = Log(O1/q)
      LogO2 = Log(O2/q) 
      
      II0_t = II0(q,t)
      II0_T1 = II0(q,T1)
      II0_T2 = II0(q,T2)
      II_T1_T1_O1 = II(q,T1,T1,O1)
      II_T1_T1_O2 = II(q,T1,T1,O2)
      II_T1_T2_O1 = II(q,T1,T2,O1)
      II_T1_T2_O2 = II(q,T1,T2,O2)
      II_T2_T2_O1 = II(q,T2,T2,O1)
      II_T2_T2_O2 = II(q,T2,T2,O2)
      JJ_T1_T1 = JJ(q,T1,T1)
      JJ_T1_T2 = JJ(q,T1,T2) 
      JJ_T2_T2 = JJ(q,T2,T2)
      II_T1_g1_t = II(q,T1,g1,t)
      II_T1_g2_t = II(q,T1,g2,t)
      II_T2_g1_t = II(q,T2,g1,t)
      II_T2_g2_t = II(q,T2,g2,t)
      phi_T1_T1_O1 = phiNM(T1,T1,O1)
      phi_T1_T2_O1 = phiNM(T1,T2,O1)
      phi_T2_T2_O1 = phiNM(T2,T2,O1)
      phi_T1_T1_O2 = phiNM(T1,T1,O2) 
      phi_T1_T2_O2 = phiNM(T1,T2,O2)
      phi_T2_T2_O2 = phiNM(T2,T2,O2)

      phi_T1_g1_t = phiNM(T1,g1,t)
      phi_T1_g2_t = phiNM(T1,g2,t)
      phi_T2_g1_t = phiNM(T2,g1,t)
      phi_T2_g2_t = phiNM(T2,g2,t)


      delta_T1_g1_t = deltNM(T1,g1,t)
      delta_T1_g2_t = deltNM(T1,g2,t)
      delta_T2_g1_t = deltNM(T2,g1,t)
      delta_T2_g2_t = deltNM(T2,g2,t)

      delta_T1_T1_O1 = deltNM(T1,T1,O1)
      delta_T1_T2_O1 = deltNM(T1,T2,O1)
      delta_T2_T2_O1 = deltNM(T2,T2,O1)
      delta_T1_T1_O2 = deltNM(T1,T1,O2)
      delta_T1_T2_O2 = deltNM(T1,T2,O2)
      delta_T2_T2_O2 = deltNM(T2,T2,O2)


       Dt = 
     $16*(t - II0_t - 3*t*logt + 2*t*logt**2) + (4*(Abs(R112)*(2*t*II_
     $T1_g1_t - t*(logt*(-2*t - (g1 - t + T1)*logg1 + (g1 + t + T1)*log
     $T1) - (g1 + t - T1)*(-1 + logg1*logT1)) + (g1**2 - (t - T1)**2)*p
     $hi_T1_g1_t) - 2*mg1*R112*s2t*mt*(II_T1_g1_t - t*(1 - logg1*logT1 
     $+ logt*(-2 + logg1 + logT1)) + (g1 - t + T1)*phi_T1_g1_t)))/t + (
     $4*(Abs(R122)*(2*t*II_T1_g2_t - t*(logt*(-2*t - (g2 - t + T1)*logg
     $2 + (g2 + t + T1)*logT1) - (g2 + t - T1)*(-1 + logg2*logT1)) + (g
     $2**2 - (t - T1)**2)*phi_T1_g2_t) - 2*mg2*R122*s2t*mt*(II_T1_g2_t 
     $- t*(1 - logg2*logT1 + logt*(-2 + logg2 + logT1)) + (g2 - t + T1)
     $*phi_T1_g2_t)))/t + 8*((mg1*R112*s2t*II_T2_g1_t)/mt + (Abs(R112)*
     $(2*t*II_T2_g1_t - t*(logt*(-2*t - (g1 - t + T2)*logg1 + (g1 + t +
     $ T2)*logT2) - (g1 + t - T2)*(-1 + logg1*logT2)) + (g1**2 - (t - T
     $2)**2)*phi_T2_g1_t))/(2.*t) + (mg1*R112*s2t*(-(t*(1 - logg1*logT2
     $ + logt*(-2 + logg1 + logT2))) + (g1 - t + T2)*phi_T2_g1_t))/mt) 
     $+ 8*((mg2*R122*s2t*II_T2_g2_t)/mt + (Abs(R122)*(2*t*II_T2_g2_t - 
     $t*(logt*(-2*t - (g2 - t + T2)*logg2 + (g2 + t + T2)*logT2) - (g2 
     $+ t - T2)*(-1 + logg2*logT2)) + (g2**2 - (t - T2)**2)*phi_T2_g2_t
     $))/(2.*t) + (mg2*R122*s2t*(-(t*(1 - logg2*logT2 + logt*(-2 + logg
     $2 + logT2))) + (g2 - t + T2)*phi_T2_g2_t))/mt)

       Dc2t = 
     $(8*mg1*R112*mt*II_T1_g1_t)/s2t + (8*mg2*R122*mt*II_T1_g2_t)/s2t 
     $- 8*md32*(c2O*II_T1_T1_O1 + s2O*II_T1_T1_O2 - c2O*II_T1_T2_O1 - s
     $2O*II_T1_T2_O2) - (8*mg1*R112*mt*II_T2_g1_t)/s2t - (8*mg2*R122*mt
     $*II_T2_g2_t)/s2t + 8*md32*(c2O*II_T1_T2_O1 + s2O*II_T1_T2_O2 - c2
     $O*II_T2_T2_O1 - s2O*II_T2_T2_O2) + 2*(JJ_T1_T1 - JJ_T1_T2) - 2*JJ
     $_T1_T2 + 2*JJ_T2_T2

       Dc2tc2t = 
     $(4*mg1*R112*mt*II_T1_g1_t)/s2t**3 + (4*mg2*R122*mt*II_T1_g2_t)/s
     $2t**3 - (4*mg1*R112*mt*II_T2_g1_t)/s2t**3 - (4*mg2*R122*mt*II_T2_
     $g2_t)/s2t**3

       Dcptmptt = 
     $-16*mg1*R112*s2t*mt*II_T1_g1_t - 16*mg2*R122*s2t*mt*II_T1_g2_t +
     $ 16*mg1*R112*s2t*mt*II_T2_g1_t + 16*mg2*R122*s2t*mt*II_T2_g2_t

       DT1 = 
     $4*(2*II0_T1 - 2*T1*(-1 + logT1)**2 + (1 + c2t**2)*T1*(-1 + logT1
     $)*logT1 - ((-1 + c2t**2)*T2*logT1*(-1 + logT2))/2.) - 2*(-1 + c2t
     $**2)*T2*logT1*(-1 + logT2) + 8*(-((mg1*R112*s2t*(t*(-1 + logg1*(l
     $ogt - logT1) - (-2 + logt)*logT1) + (g1 + t - T1)*phi_T1_g1_t))/m
     $t) + Abs(R112)*(-II_T1_g1_t - g1*(-1 + logg1)*logT1 - t*(-1 + log
     $t)*logT1 + ((g1 + t - T1)*(t*(-1 + logg1*(logt - logT1) - (-2 + l
     $ogt)*logT1) + (g1 + t - T1)*phi_T1_g1_t))/(2.*t))) + 8*(-((mg2*R1
     $22*s2t*(t*(-1 + logg2*(logt - logT1) - (-2 + logt)*logT1) + (g2 +
     $ t - T1)*phi_T1_g2_t))/mt) + Abs(R122)*(-II_T1_g2_t - g2*(-1 + lo
     $gg2)*logT1 - t*(-1 + logt)*logT1 + ((g2 + t - T1)*(t*(-1 + logg2*
     $(logt - logT1) - (-2 + logt)*logT1) + (g2 + t - T1)*phi_T1_g2_t))
     $/(2.*t))) - (4*(-1 + c2t**2)*md32*(-(c2O*O2*(O1 - T1 + T2)*phi_T1
     $_T2_O1) + O1*(O2*(c2O + s2O + logT1*(c2O*logO1 + s2O*logO2 + (c2O
     $ + s2O)*(-2 + logT2)) - c2O*logO1*logT2 - s2O*logO2*logT2) - s2O*
     $(O2 - T1 + T2)*phi_T1_T2_O2)))/(O1*O2) - 8*md32*(-(c2t**2*((c2O +
     $ s2O)*(-1 + logT1)**2 - c2O*phi_T1_T1_O1 - s2O*phi_T1_T1_O2)) + (
     $(-1 + c2t**2)*(-(c2O*O2*(O1 - T1 + T2)*phi_T1_T2_O1) + O1*(O2*(c2
     $O + s2O + logT1*(c2O*logO1 + s2O*logO2 + (c2O + s2O)*(-2 + logT2)
     $) - c2O*logO1*logT2 - s2O*logO2*logT2) - s2O*(O2 - T1 + T2)*phi_T
     $1_T2_O2)))/(2.*O1*O2))

       DT2 = 
     $-2*(-1 + c2t**2)*T1*(-1 + logT1)*logT2 + 4*(2*II0_T2 - 2*T2*(-1 
     $+ logT2)**2 - ((-1 + c2t**2)*T1*(-1 + logT1)*logT2)/2. + (1 + c2t
     $**2)*T2*(-1 + logT2)*logT2) + (4*(-1 + c2t**2)*md32*(c2O*O2*(O1 +
     $ T1 - T2)*phi_T1_T2_O1 + O1*(O2*(c2O*logO1*(logT1 - logT2) + s2O*
     $logO2*(logT1 - logT2) - (c2O + s2O)*(1 + (-2 + logT1)*logT2)) + s
     $2O*(O2 + T1 - T2)*phi_T1_T2_O2)))/(O1*O2) + 8*((mg1*R112*s2t*(t*(
     $-1 + logg1*(logt - logT2) - (-2 + logt)*logT2) + (g1 + t - T2)*ph
     $i_T2_g1_t))/mt + Abs(R112)*(-II_T2_g1_t - g1*(-1 + logg1)*logT2 -
     $ t*(-1 + logt)*logT2 + ((g1 + t - T2)*(t*(-1 + logg1*(logt - logT
     $2) - (-2 + logt)*logT2) + (g1 + t - T2)*phi_T2_g1_t))/(2.*t))) + 
     $8*((mg2*R122*s2t*(t*(-1 + logg2*(logt - logT2) - (-2 + logt)*logT
     $2) + (g2 + t - T2)*phi_T2_g2_t))/mt + Abs(R122)*(-II_T2_g2_t - g2
     $*(-1 + logg2)*logT2 - t*(-1 + logt)*logT2 + ((g2 + t - T2)*(t*(-1
     $ + logg2*(logt - logT2) - (-2 + logt)*logT2) + (g2 + t - T2)*phi_
     $T2_g2_t))/(2.*t))) - 8*md32*(-((-1 + c2t**2)*(c2O*O2*(O1 + T1 - T
     $2)*phi_T1_T2_O1 + O1*(O2*(c2O*logO1*(logT1 - logT2) + s2O*logO2*(
     $logT1 - logT2) - (c2O + s2O)*(1 + (-2 + logT1)*logT2)) + s2O*(O2 
     $+ T1 - T2)*phi_T1_T2_O2)))/(2.*O1*O2) - c2t**2*((c2O + s2O)*(-1 +
     $ logT2)**2 - c2O*phi_T2_T2_O1 - s2O*phi_T2_T2_O2))

       DT1T1 = 
     $(-2*(-1 + c2t**2)*T2*(-1 + logT2))/T1 + (2*(-2*T1 - 2*c2t**2*T1 
     $- T2 + c2t**2*T2 + 2*(5 + c2t**2)*T1*logT1 + 2*(-3 + c2t**2)*T1*l
     $ogT1**2 + (T2 - c2t**2*T2)*logT2))/T1 + 8*((mg1*R112*s2t*(delta_T
     $1_g1_t*(t*(-2 + logg1 + logt) + T1*phi_T1_g1_t) + (g1 + t - T1)*(
     $t*((g1 - t + T1)*logg1 + (-g1 + t + T1)*logt - 2*T1*logT1) + T1*(
     $-g1 - t + T1)*phi_T1_g1_t)))/(mt*T1*delta_T1_g1_t) + Abs(R112)*(1
     $ + (g1 - g1*logg1)/T1 - logg1*logt + (t - t*logt)/T1 + (-2 + logg
     $1 + logt)*logT1 - ((g1 + t - T1)*phi_T1_g1_t)/t - ((g1 + t - T1)*
     $(delta_T1_g1_t*(t*(-2 + logg1 + logt) + T1*phi_T1_g1_t) + (g1 + t
     $ - T1)*(t*((g1 - t + T1)*logg1 + (-g1 + t + T1)*logt - 2*T1*logT1
     $) + T1*(-g1 - t + T1)*phi_T1_g1_t)))/(2.*t*T1*delta_T1_g1_t))) + 
     $8*((mg2*R122*s2t*(delta_T1_g2_t*(t*(-2 + logg2 + logt) + T1*phi_T
     $1_g2_t) + (g2 + t - T1)*(t*((g2 - t + T1)*logg2 + (-g2 + t + T1)*
     $logt - 2*T1*logT1) + T1*(-g2 - t + T1)*phi_T1_g2_t)))/(mt*T1*delt
     $a_T1_g2_t) + Abs(R122)*(1 + (g2 - g2*logg2)/T1 - logg2*logt + (t 
     $- t*logt)/T1 + (-2 + logg2 + logt)*logT1 - ((g2 + t - T1)*phi_T1_
     $g2_t)/t - ((g2 + t - T1)*(delta_T1_g2_t*(t*(-2 + logg2 + logt) + 
     $T1*phi_T1_g2_t) + (g2 + t - T1)*(t*((g2 - t + T1)*logg2 + (-g2 + 
     $t + T1)*logt - 2*T1*logT1) + T1*(-g2 - t + T1)*phi_T1_g2_t)))/(2.
     $*t*T1*delta_T1_g2_t))) - (4*(1 - c2t**2)*md32*((c2O*(-(delta_T1_T
     $2_O1*(O1*(-2 + logO1 + logT2) + T1*phi_T1_T2_O1)) - (O1 - T1 + T2
     $)*(O1*((O1 + T1 - T2)*logO1 - 2*T1*logT1 + (-O1 + T1 + T2)*logT2)
     $ + T1*(-O1 + T1 - T2)*phi_T1_T2_O1)))/(O1*delta_T1_T2_O1) + (s2O*
     $(-(delta_T1_T2_O2*(O2*(-2 + logO2 + logT2) + T1*phi_T1_T2_O2)) - 
     $(O2 - T1 + T2)*(O2*((O2 + T1 - T2)*logO2 - 2*T1*logT1 + (-O2 + T1
     $ + T2)*logT2) + T1*(-O2 + T1 - T2)*phi_T1_T2_O2)))/(O2*delta_T1_T
     $2_O2)))/T1 - (4*md32*((4*c2t**2*(c2O*O1*delta_T1_T1_O2*(O1*(-logO
     $1 + logT1) + T1*phi_T1_T1_O1) + delta_T1_T1_O1*(-((c2O + s2O)*del
     $ta_T1_T1_O2*(-1 + logT1)) + O2*s2O*(-(O2*logO2) + O2*logT1 + T1*p
     $hi_T1_T1_O2))))/(delta_T1_T1_O1*delta_T1_T1_O2) + (1 - c2t**2)*((
     $c2O*(-(delta_T1_T2_O1*(O1*(-2 + logO1 + logT2) + T1*phi_T1_T2_O1)
     $) - (O1 - T1 + T2)*(O1*((O1 + T1 - T2)*logO1 - 2*T1*logT1 + (-O1 
     $+ T1 + T2)*logT2) + T1*(-O1 + T1 - T2)*phi_T1_T2_O1)))/(O1*delta_
     $T1_T2_O1) + (s2O*(-(delta_T1_T2_O2*(O2*(-2 + logO2 + logT2) + T1*
     $phi_T1_T2_O2)) - (O2 - T1 + T2)*(O2*((O2 + T1 - T2)*logO2 - 2*T1*
     $logT1 + (-O2 + T1 + T2)*logT2) + T1*(-O2 + T1 - T2)*phi_T1_T2_O2)
     $))/(O2*delta_T1_T2_O2))))/T1

       DT1T2 = 
     $-4*(-1 + c2t**2)*logT1*logT2 + (8*(1 - c2t**2)*md32*((c2O*(-(del
     $ta_T1_T2_O1*(O1*(logO1 - logT1) + T2*phi_T1_T2_O1)) + (O1 - T1 + 
     $T2)*(O1*((O1 - T1 + T2)*logO1 + (-O1 + T1 + T2)*logT1 - 2*T2*logT
     $2) + T2*(-O1 - T1 + T2)*phi_T1_T2_O1)))/(O1*delta_T1_T2_O1) + (s2
     $O*(-(delta_T1_T2_O2*(O2*(logO2 - logT1) + T2*phi_T1_T2_O2)) + (O2
     $ - T1 + T2)*(O2*((O2 - T1 + T2)*logO2 + (-O2 + T1 + T2)*logT1 - 2
     $*T2*logT2) + T2*(-O2 - T1 + T2)*phi_T1_T2_O2)))/(O2*delta_T1_T2_O
     $2)))/T2

       DT2T2 = 
     $(-2*(-1 + c2t**2)*T1*(-1 + logT1))/T2 - (2*(T1 - c2t**2*T1 + 2*T
     $2 + 2*c2t**2*T2 + (-1 + c2t**2)*T1*logT1 - 2*(5 + c2t**2)*T2*logT
     $2 - 2*(-3 + c2t**2)*T2*logT2**2))/T2 - (4*(1 - c2t**2)*md32*((c2O
     $*(-(delta_T1_T2_O1*(O1*(-2 + logO1 + logT1) + T2*phi_T1_T2_O1)) -
     $ (O1 + T1 - T2)*(O1*((O1 - T1 + T2)*logO1 + (-O1 + T1 + T2)*logT1
     $ - 2*T2*logT2) + T2*(-O1 - T1 + T2)*phi_T1_T2_O1)))/(O1*delta_T1_
     $T2_O1) + (s2O*(-(delta_T1_T2_O2*(O2*(-2 + logO2 + logT1) + T2*phi
     $_T1_T2_O2)) - (O2 + T1 - T2)*(O2*((O2 - T1 + T2)*logO2 + (-O2 + T
     $1 + T2)*logT1 - 2*T2*logT2) + T2*(-O2 - T1 + T2)*phi_T1_T2_O2)))/
     $(O2*delta_T1_T2_O2)))/T2 + 8*(-((mg1*R112*s2t*(delta_T2_g1_t*(t*(
     $-2 + logg1 + logt) + T2*phi_T2_g1_t) + (g1 + t - T2)*(t*((g1 - t 
     $+ T2)*logg1 + (-g1 + t + T2)*logt - 2*T2*logT2) + T2*(-g1 - t + T
     $2)*phi_T2_g1_t)))/(mt*T2*delta_T2_g1_t)) + Abs(R112)*(1 + (g1 - g
     $1*logg1)/T2 - logg1*logt + (t - t*logt)/T2 + (-2 + logg1 + logt)*
     $logT2 - ((g1 + t - T2)*phi_T2_g1_t)/t - ((g1 + t - T2)*(delta_T2_
     $g1_t*(t*(-2 + logg1 + logt) + T2*phi_T2_g1_t) + (g1 + t - T2)*(t*
     $((g1 - t + T2)*logg1 + (-g1 + t + T2)*logt - 2*T2*logT2) + T2*(-g
     $1 - t + T2)*phi_T2_g1_t)))/(2.*t*T2*delta_T2_g1_t))) + 8*(-((mg2*
     $R122*s2t*(delta_T2_g2_t*(t*(-2 + logg2 + logt) + T2*phi_T2_g2_t) 
     $+ (g2 + t - T2)*(t*((g2 - t + T2)*logg2 + (-g2 + t + T2)*logt - 2
     $*T2*logT2) + T2*(-g2 - t + T2)*phi_T2_g2_t)))/(mt*T2*delta_T2_g2_
     $t)) + Abs(R122)*(1 + (g2 - g2*logg2)/T2 - logg2*logt + (t - t*log
     $t)/T2 + (-2 + logg2 + logt)*logT2 - ((g2 + t - T2)*phi_T2_g2_t)/t
     $ - ((g2 + t - T2)*(delta_T2_g2_t*(t*(-2 + logg2 + logt) + T2*phi_
     $T2_g2_t) + (g2 + t - T2)*(t*((g2 - t + T2)*logg2 + (-g2 + t + T2)
     $*logt - 2*T2*logT2) + T2*(-g2 - t + T2)*phi_T2_g2_t)))/(2.*t*T2*d
     $elta_T2_g2_t))) - (4*md32*((1 - c2t**2)*((c2O*(-(delta_T1_T2_O1*(
     $O1*(-2 + logO1 + logT1) + T2*phi_T1_T2_O1)) - (O1 + T1 - T2)*(O1*
     $((O1 - T1 + T2)*logO1 + (-O1 + T1 + T2)*logT1 - 2*T2*logT2) + T2*
     $(-O1 - T1 + T2)*phi_T1_T2_O1)))/(O1*delta_T1_T2_O1) + (s2O*(-(del
     $ta_T1_T2_O2*(O2*(-2 + logO2 + logT1) + T2*phi_T1_T2_O2)) - (O2 + 
     $T1 - T2)*(O2*((O2 - T1 + T2)*logO2 + (-O2 + T1 + T2)*logT1 - 2*T2
     $*logT2) + T2*(-O2 - T1 + T2)*phi_T1_T2_O2)))/(O2*delta_T1_T2_O2))
     $ + (4*c2t**2*(c2O*O1*delta_T2_T2_O2*(O1*(-logO1 + logT2) + T2*phi
     $_T2_T2_O1) + delta_T2_T2_O1*(-((c2O + s2O)*delta_T2_T2_O2*(-1 + l
     $ogT2)) + O2*s2O*(-(O2*logO2) + O2*logT2 + T2*phi_T2_T2_O2))))/(de
     $lta_T2_T2_O1*delta_T2_T2_O2)))/T2

       DT1c2t = 
     $-2*T2*logT1*(-1 + logT2) + 2*logT1*(-2*T1 + T2 + 2*T1*logT1 - T2
     $*logT2) + (4*mg1*R112*(t*(-1 + logg1*(logt - logT1) - (-2 + logt)
     $*logT1) + (g1 + t - T1)*phi_T1_g1_t))/(s2t*mt) + (4*mg2*R122*(t*(
     $-1 + logg2*(logt - logT1) - (-2 + logt)*logT1) + (g2 + t - T1)*ph
     $i_T1_g2_t))/(s2t*mt) - 4*md32*(-2*c2O*((-1 + logT1)**2 - phi_T1_T
     $1_O1) - 2*s2O*((-1 + logT1)**2 - phi_T1_T1_O2) + (c2O*(O1*(1 - lo
     $gO1*logT2 + logT1*(-2 + logO1 + logT2)) - (O1 - T1 + T2)*phi_T1_T
     $2_O1))/O1 + (s2O*(O2*(1 - logO2*logT2 + logT1*(-2 + logO2 + logT2
     $)) - (O2 - T1 + T2)*phi_T1_T2_O2))/O2) - (4*md32*(-(c2O*O2*(O1 - 
     $T1 + T2)*phi_T1_T2_O1) + O1*(O2*(c2O + s2O + logT1*(c2O*logO1 + s
     $2O*logO2 + (c2O + s2O)*(-2 + logT2)) - c2O*logO1*logT2 - s2O*logO
     $2*logT2) - s2O*(O2 - T1 + T2)*phi_T1_T2_O2)))/(O1*O2)

       DT2c2t = 
     $-2*T1*(-1 + logT1)*logT2 + 4*(-(T1*(-1 + logT1)*logT2)/2. + T2*(
     $-1 + logT2)*logT2) + (4*md32*(c2O*O2*(O1 + T1 - T2)*phi_T1_T2_O1 
     $+ O1*(O2*(c2O*logO1*(logT1 - logT2) + s2O*logO2*(logT1 - logT2) -
     $ (c2O + s2O)*(1 + (-2 + logT1)*logT2)) + s2O*(O2 + T1 - T2)*phi_T
     $1_T2_O2)))/(O1*O2) - (4*mg1*R112*(t*(-1 + logg1*(logt - logT2) - 
     $(-2 + logt)*logT2) + (g1 + t - T2)*phi_T2_g1_t))/(s2t*mt) - (4*mg
     $2*R122*(t*(-1 + logg2*(logt - logT2) - (-2 + logt)*logT2) + (g2 +
     $ t - T2)*phi_T2_g2_t))/(s2t*mt) + (4*md32*(c2O*O2*(O1 + T1 - T2)*
     $phi_T1_T2_O1 + O1*(s2O*(O2 + T1 - T2)*phi_T1_T2_O2 + O2*(c2O + s2
     $O + c2O*logO1*logT1 + s2O*logO2*logT1 - 2*c2O*logT2 - 2*s2O*logT2
     $ - c2O*logO1*logT2 - s2O*logO2*logT2 - c2O*logT1*logT2 - s2O*logT
     $1*logT2 + 2*c2O*logT2**2 + 2*s2O*logT2**2 - 2*c2O*phi_T2_T2_O1 - 
     $2*s2O*phi_T2_T2_O2))))/(O1*O2)

       DT1t = 
     $4*(-((mg1*R112*s2t*(t*(-1 + logg1*(logt - logT1) - (-2 + logt)*l
     $ogT1) + (g1 + t - T1)*phi_T1_g1_t))/t**1.5) - (2*mg1*R112*s2t*(de
     $lta_T1_g1_t*(t*(logg1 - logT1) + (-g1 + T1)*phi_T1_g1_t) + (g1 + 
     $t - T1)*(-(t*((g1 + t - T1)*logg1 - 2*t*logt + (-g1 + t + T1)*log
     $T1)) + (g1**2 + T1*(-t + T1) - g1*(t + 2*T1))*phi_T1_g1_t)))/(t**
     $1.5*delta_T1_g1_t) + Abs(R112)*(logg1*logt - 2*logT1 - logg1*logT
     $1 - 2*(-1 + logt)*logT1 - (-2 + logg1 + logt)*logT1 + logt*(-2 + 
     $logg1 + logT1) + ((g1 + t - T1)*phi_T1_g1_t)/t - ((g1 - t + T1)*p
     $hi_T1_g1_t)/t + ((g1 + t - T1)*(delta_T1_g1_t*(t*(logg1 - logT1) 
     $+ (-g1 + T1)*phi_T1_g1_t) + (g1 + t - T1)*(-(t*((g1 + t - T1)*log
     $g1 - 2*t*logt + (-g1 + t + T1)*logT1)) + (g1**2 + T1*(-t + T1) - 
     $g1*(t + 2*T1))*phi_T1_g1_t)))/(t**2*delta_T1_g1_t))) + 4*(-((mg2*
     $R122*s2t*(t*(-1 + logg2*(logt - logT1) - (-2 + logt)*logT1) + (g2
     $ + t - T1)*phi_T1_g2_t))/t**1.5) - (2*mg2*R122*s2t*(delta_T1_g2_t
     $*(t*(logg2 - logT1) + (-g2 + T1)*phi_T1_g2_t) + (g2 + t - T1)*(-(
     $t*((g2 + t - T1)*logg2 - 2*t*logt + (-g2 + t + T1)*logT1)) + (g2*
     $*2 + T1*(-t + T1) - g2*(t + 2*T1))*phi_T1_g2_t)))/(t**1.5*delta_T
     $1_g2_t) + Abs(R122)*(logg2*logt - 2*logT1 - logg2*logT1 - 2*(-1 +
     $ logt)*logT1 - (-2 + logg2 + logt)*logT1 + logt*(-2 + logg2 + log
     $T1) + ((g2 + t - T1)*phi_T1_g2_t)/t - ((g2 - t + T1)*phi_T1_g2_t)
     $/t + ((g2 + t - T1)*(delta_T1_g2_t*(t*(logg2 - logT1) + (-g2 + T1
     $)*phi_T1_g2_t) + (g2 + t - T1)*(-(t*((g2 + t - T1)*logg2 - 2*t*lo
     $gt + (-g2 + t + T1)*logT1)) + (g2**2 + T1*(-t + T1) - g2*(t + 2*T
     $1))*phi_T1_g2_t)))/(t**2*delta_T1_g2_t)))

       DT2t = 
     $4*((mg1*R112*s2t*(t*(-1 + logg1*(logt - logT2) - (-2 + logt)*log
     $T2) + (g1 + t - T2)*phi_T2_g1_t))/t**1.5 + (2*mg1*R112*s2t*(delta
     $_T2_g1_t*(t*(logg1 - logT2) + (-g1 + T2)*phi_T2_g1_t) + (g1 + t -
     $ T2)*(-(t*((g1 + t - T2)*logg1 - 2*t*logt + (-g1 + t + T2)*logT2)
     $) + (g1**2 + T2*(-t + T2) - g1*(t + 2*T2))*phi_T2_g1_t)))/(t**1.5
     $*delta_T2_g1_t) + Abs(R112)*(logg1*logt - 2*logT2 - logg1*logT2 -
     $ 2*(-1 + logt)*logT2 - (-2 + logg1 + logt)*logT2 + logt*(-2 + log
     $g1 + logT2) + ((g1 + t - T2)*phi_T2_g1_t)/t - ((g1 - t + T2)*phi_
     $T2_g1_t)/t + ((g1 + t - T2)*(delta_T2_g1_t*(t*(logg1 - logT2) + (
     $-g1 + T2)*phi_T2_g1_t) + (g1 + t - T2)*(-(t*((g1 + t - T2)*logg1 
     $- 2*t*logt + (-g1 + t + T2)*logT2)) + (g1**2 + T2*(-t + T2) - g1*
     $(t + 2*T2))*phi_T2_g1_t)))/(t**2*delta_T2_g1_t))) + 4*((mg2*R122*
     $s2t*(t*(-1 + logg2*(logt - logT2) - (-2 + logt)*logT2) + (g2 + t 
     $- T2)*phi_T2_g2_t))/t**1.5 + (2*mg2*R122*s2t*(delta_T2_g2_t*(t*(l
     $ogg2 - logT2) + (-g2 + T2)*phi_T2_g2_t) + (g2 + t - T2)*(-(t*((g2
     $ + t - T2)*logg2 - 2*t*logt + (-g2 + t + T2)*logT2)) + (g2**2 + T
     $2*(-t + T2) - g2*(t + 2*T2))*phi_T2_g2_t)))/(t**1.5*delta_T2_g2_t
     $) + Abs(R122)*(logg2*logt - 2*logT2 - logg2*logT2 - 2*(-1 + logt)
     $*logT2 - (-2 + logg2 + logt)*logT2 + logt*(-2 + logg2 + logT2) + 
     $((g2 + t - T2)*phi_T2_g2_t)/t - ((g2 - t + T2)*phi_T2_g2_t)/t + (
     $(g2 + t - T2)*(delta_T2_g2_t*(t*(logg2 - logT2) + (-g2 + T2)*phi_
     $T2_g2_t) + (g2 + t - T2)*(-(t*((g2 + t - T2)*logg2 - 2*t*logt + (
     $-g2 + t + T2)*logT2)) + (g2**2 + T2*(-t + T2) - g2*(t + 2*T2))*ph
     $i_T2_g2_t)))/(t**2*delta_T2_g2_t)))

       Dtt = 
     $16*(-1 - logt + 3*logt**2) + 8*((mg1*R112*s2t*II_T1_g1_t)/(2.*t*
     $*1.5) - (mg1*R112*s2t*(-(t*(1 - logg1*logT1 + logt*(-2 + logg1 + 
     $logT1))) + (g1 - t + T1)*phi_T1_g1_t))/t**1.5 - (mg1*R112*s2t*(-(
     $delta_T1_g1_t*(t*(-2 + logg1 + logT1) + (g1 + T1)*phi_T1_g1_t)) +
     $ (g1 - t + T1)*(-(t*((g1 + t - T1)*logg1 - 2*t*logt + (-g1 + t + 
     $T1)*logT1)) + (g1**2 + T1*(-t + T1) - g1*(t + 2*T1))*phi_T1_g1_t)
     $))/(t**1.5*delta_T1_g1_t) + Abs(R112)*(-1 + (g1*(-1 + logg1))/t +
     $ logg1*logT1 - logt*(-2 + logg1 + logT1) + (T1 - T1*logT1)/t + ((
     $g1 - t + T1)*phi_T1_g1_t)/t + ((g1 + t - T1)*(-(delta_T1_g1_t*(t*
     $(-2 + logg1 + logT1) + (g1 + T1)*phi_T1_g1_t)) + (g1 - t + T1)*(-
     $(t*((g1 + t - T1)*logg1 - 2*t*logt + (-g1 + t + T1)*logT1)) + (g1
     $**2 + T1*(-t + T1) - g1*(t + 2*T1))*phi_T1_g1_t)))/(2.*t**2*delta
     $_T1_g1_t))) + 8*((mg2*R122*s2t*II_T1_g2_t)/(2.*t**1.5) - (mg2*R12
     $2*s2t*(-(t*(1 - logg2*logT1 + logt*(-2 + logg2 + logT1))) + (g2 -
     $ t + T1)*phi_T1_g2_t))/t**1.5 - (mg2*R122*s2t*(-(delta_T1_g2_t*(t
     $*(-2 + logg2 + logT1) + (g2 + T1)*phi_T1_g2_t)) + (g2 - t + T1)*(
     $-(t*((g2 + t - T1)*logg2 - 2*t*logt + (-g2 + t + T1)*logT1)) + (g
     $2**2 + T1*(-t + T1) - g2*(t + 2*T1))*phi_T1_g2_t)))/(t**1.5*delta
     $_T1_g2_t) + Abs(R122)*(-1 + (g2*(-1 + logg2))/t + logg2*logT1 - l
     $ogt*(-2 + logg2 + logT1) + (T1 - T1*logT1)/t + ((g2 - t + T1)*phi
     $_T1_g2_t)/t + ((g2 + t - T1)*(-(delta_T1_g2_t*(t*(-2 + logg2 + lo
     $gT1) + (g2 + T1)*phi_T1_g2_t)) + (g2 - t + T1)*(-(t*((g2 + t - T1
     $)*logg2 - 2*t*logt + (-g2 + t + T1)*logT1)) + (g2**2 + T1*(-t + T
     $1) - g2*(t + 2*T1))*phi_T1_g2_t)))/(2.*t**2*delta_T1_g2_t))) + 8*
     $(-(mg1*R112*s2t*II_T2_g1_t)/(2.*t**1.5) + (mg1*R112*s2t*(-(t*(1 -
     $ logg1*logT2 + logt*(-2 + logg1 + logT2))) + (g1 - t + T2)*phi_T2
     $_g1_t))/t**1.5 + (mg1*R112*s2t*(-(delta_T2_g1_t*(t*(-2 + logg1 + 
     $logT2) + (g1 + T2)*phi_T2_g1_t)) + (g1 - t + T2)*(-(t*((g1 + t - 
     $T2)*logg1 - 2*t*logt + (-g1 + t + T2)*logT2)) + (g1**2 + T2*(-t +
     $ T2) - g1*(t + 2*T2))*phi_T2_g1_t)))/(t**1.5*delta_T2_g1_t) + Abs
     $(R112)*(-1 + (g1*(-1 + logg1))/t + logg1*logT2 - logt*(-2 + logg1
     $ + logT2) + (T2 - T2*logT2)/t + ((g1 - t + T2)*phi_T2_g1_t)/t + (
     $(g1 + t - T2)*(-(delta_T2_g1_t*(t*(-2 + logg1 + logT2) + (g1 + T2
     $)*phi_T2_g1_t)) + (g1 - t + T2)*(-(t*((g1 + t - T2)*logg1 - 2*t*l
     $ogt + (-g1 + t + T2)*logT2)) + (g1**2 + T2*(-t + T2) - g1*(t + 2*
     $T2))*phi_T2_g1_t)))/(2.*t**2*delta_T2_g1_t))) + 8*(-(mg2*R122*s2t
     $*II_T2_g2_t)/(2.*t**1.5) + (mg2*R122*s2t*(-(t*(1 - logg2*logT2 + 
     $logt*(-2 + logg2 + logT2))) + (g2 - t + T2)*phi_T2_g2_t))/t**1.5 
     $+ (mg2*R122*s2t*(-(delta_T2_g2_t*(t*(-2 + logg2 + logT2) + (g2 + 
     $T2)*phi_T2_g2_t)) + (g2 - t + T2)*(-(t*((g2 + t - T2)*logg2 - 2*t
     $*logt + (-g2 + t + T2)*logT2)) + (g2**2 + T2*(-t + T2) - g2*(t + 
     $2*T2))*phi_T2_g2_t)))/(t**1.5*delta_T2_g2_t) + Abs(R122)*(-1 + (g
     $2*(-1 + logg2))/t + logg2*logT2 - logt*(-2 + logg2 + logT2) + (T2
     $ - T2*logT2)/t + ((g2 - t + T2)*phi_T2_g2_t)/t + ((g2 + t - T2)*(
     $-(delta_T2_g2_t*(t*(-2 + logg2 + logT2) + (g2 + T2)*phi_T2_g2_t))
     $ + (g2 - t + T2)*(-(t*((g2 + t - T2)*logg2 - 2*t*logt + (-g2 + t 
     $+ T2)*logT2)) + (g2**2 + T2*(-t + T2) - g2*(t + 2*T2))*phi_T2_g2_
     $t)))/(2.*t**2*delta_T2_g2_t)))

       Dtc2t = 
     $(4*mg1*R112*(II_T1_g1_t - t*(1 - logg1*logT1 + logt*(-2 + logg1 
     $+ logT1)) + (g1 - t + T1)*phi_T1_g1_t))/(s2t*mt) + (4*mg2*R122*(I
     $I_T1_g2_t - t*(1 - logg2*logT1 + logt*(-2 + logg2 + logT1)) + (g2
     $ - t + T1)*phi_T1_g2_t))/(s2t*mt) - (4*mg1*R112*(II_T2_g1_t - t*(
     $1 - logg1*logT2 + logt*(-2 + logg1 + logT2)) + (g1 - t + T2)*phi_
     $T2_g1_t))/(s2t*mt) - (4*mg2*R122*(II_T2_g2_t - t*(1 - logg2*logT2
     $ + logt*(-2 + logg2 + logT2)) + (g2 - t + T2)*phi_T2_g2_t))/(s2t*
     $mt)

      return
      end
*
**********************************************************************
*

      double precision function JJ(q,m1,m2) 
      
      implicit none
      double precision q,m1,m2

      JJ = m1*m2*(Log(m1/q)-1)*(Log(m2/q)-1)

      return
      end

*
**********************************************************************
*

      double precision function II(q,m1,m2,m3) 
      
      implicit none
      double precision q,m1,m2,m3,deltNM,phiNM

      II = (m1-m2-m3)/2d0*Log(m2/q)*Log(m3/q)
     $     +(m2-m1-m3)/2d0*Log(m1/q)*Log(m3/q)
     $     +(m3-m1-m2)/2d0*Log(m1/q)*Log(m2/q)
     $     +2*m1*log(m1/q)+2*m2*Log(m2/q)+2*m3*Log(m3/q)
     $     -2.5d0*(m1+m2+m3)-deltNM(m1,m2,m3)/2d0/m3*phiNM(m1,m2,m3)

      return
      end



*
**********************************************************************
*

c     From S. Martin arXiv:hep-ph/0307101, Eq. (6.8)

      double precision function II0(q,m1) 
      
      implicit none
      double precision q,m1

      II0 = m1*(-Log(m1/q)**2+4d0*Log(m1/q)-5d0)

      return
      end 

 

*
**********************************************************************
*

c     Defined in Eq. (D3) of Degrassi & Slavich 

      double precision function LL(q,m1,m2,m3) 
      
      implicit none
      double precision q,m1,m2,m3,JJ,II
      
      LL = JJ(q,m2,m3)-JJ(q,m1,m2)-JJ(q,m1,m3)-(m1-m2-m3)*II(q,m1,m2,m3)
      
      return
      end



*
**********************************************************************
*

      function phiNM(x,y,z)

c     from Davydychev and Tausk, Nucl. Phys. B397 (1993) 23

      implicit none
      double precision x,y,z,phiNM,pphiNM,myphiNM
      
      pphiNM = 0.d0
      if(x.le.z.and.y.le.z) then
         pphiNM = myphiNM(x,y,z)
      elseif(z.le.x.and.y.le.x) then
         pphiNM = z/x*myphiNM(z,y,x)
      elseif(z.le.y.and.x.le.y) then
         pphiNM = z/y*myphiNM(z,x,y)
      endif

      phiNM = pphiNM
      
      end
      
      function myphiNM(x,y,z)
      
      implicit none

      double precision x,y,z,myphiNM
      double precision u,v
      double precision Pi,SLLi2
      double complex clam,cxp,cxm,SLCLI2,ccphiNM

      parameter (pi = 3.1415926535897932384626433832795029D0)

c     auxiliary variables

      u = x/z
      v = y/z
      
      if(u.le.1d-8) then
         
         if(v.ne.1d0) then
            myphiNM = (log(u)*log(v)+2d0*SLLi2(1d0-v))/(1d0-v)
         else
            myphiNM = 2d0-log(u)
         endif

      elseif(v.le.1d-8) then

         if(u.ne.1d0) then
            myphiNM = (log(v)*log(u)+2d0*SLLi2(1d0-u))/(1d0-u)
         else
            myphiNM = 2d0-log(v)
         endif

      else
         
         if((1d0-u-v)**2.ge.4d0*u*v) then         
            clam = DCMPLX(sqrt((1d0-u-v)**2 - 4d0*u*v),0d0)
         else
            clam = DCMPLX(0d0,sqrt(4d0*u*v - (1d0-u-v)**2))
         endif
         
         cxp = (1d0+(u-v)-clam)/2d0
         cxm = (1d0-(u-v)-clam)/2d0
         
c     phiNM function from eq. (A4)
            
         ccphiNM = (2d0*log(cxp)*log(cxm) - log(u)*log(v) - 
     &        2d0*(SLCLI2(cxp) + SLCLI2(cxm)) + Pi**2/3d0)/clam
         myphiNM = DBLE(ccphiNM)
                     
      endif
      
      return
      end

*
***********************************************************************
*

      function SLLi2(x)

      implicit none

      double complex SLCLI2,z
      double precision x,SLLi2

      z = DCMPLX(x,0d0)
      SLLi2 = DBLE(SLCLI2(z))

      return
      end

*
***********************************************************************
*

      DOUBLE COMPLEX FUNCTION SLCLI2(Z)

c     just call the Dilog routine
      
      DOUBLE COMPLEX Z,Dilog

      SLCLI2 = Dilog(Z)

      return
      end

*
**********************************************************************
*
* Dilog.F
* complex dilogarithm
* this file is part of FeynHiggs
* last modified 20 Oct 05 th


      double complex function Dilog(z)
      implicit none
      double complex z
      
      double complex Dilogsum
      external Dilogsum
      
      double precision absz, abs1z
      double complex t, mlogz
      
      double precision pi, zeta2
      parameter (pi = 3.1415926535897932384626433832795029D0)
      parameter (zeta2 = pi*pi/6D0)
      
      absz = abs(z)
      if( absz .lt. 1D-20 ) then
         Dilog = -log(1 - z)
         return
      endif
      
      abs1z = abs(1 - z)
        if( abs1z .lt. 1D-20 ) then
           Dilog = zeta2
           return
        endif
        
        if( DBLE(z) .gt. .5D0 ) then
           mlogz = -log(z)
           t = zeta2 + mlogz*log(1 - z)
           if( abs1z .gt. 1 ) then
              Dilog = Dilogsum(log(1 - 1/z)) + zeta2 +
     $             .5D0*log(z - 1)**2 + t
           else
            Dilog = -Dilogsum(mlogz) + t
         endif
      else
         if( absz .gt. 1 ) then
            Dilog = -Dilogsum(-log(1 - 1/z)) - zeta2 - .5D0*log(-z)**2
         else
            Dilog = Dilogsum(-log(1 - z))
         endif
      endif
      end
      

************************************************************************

      double complex function Dilogsum(w)
      implicit none
      double complex w
      
      double complex u, t
      integer k
      
      double precision b2, b4, b6, b8, b10, b12, b14
      double precision b16, b18, b20, b22
      parameter (b2 = 1/6D0)
      parameter (b4 = -1/30D0)
      parameter (b6 = 1/42D0)
      parameter (b8 = -1/30D0)
      parameter (b10 = 5/66D0)
      parameter (b12 = -691/2730D0)
      parameter (b14 = 7/6D0)
      parameter (b16 = -3617/510D0)
      parameter (b18 = 43867/798D0)
      parameter (b20 = -174611/330D0)
      parameter (b22 = 854513/138D0)
      
      double precision bernoulliB(11)
      data bernoulliB /b2, b4, b6, b8, b10, b12, b14,
     &     b16, b18, b20, b22/
      
      Dilogsum = w*(1 - .25D0*w)
      if( abs(w) .lt. 1D-10 ) return
      
      u = w
      do k = 1, 11
         u = u*w**2/DBLE(2*k*(2*k + 1))
         t = u*bernoulliB(k)
         Dilogsum = Dilogsum + t
         if( abs(t) .lt. 1D-16*abs(Dilogsum) ) return
      enddo

      end
      
      function deltNM(x,y,z)
      double precision deltNM,x,y,z

      deltNM = x**2+y**2+z**2 -2*(x*y+x*z+y*z)

      return
      end

c     
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c

      subroutine swap12NM(M)

      implicit none 
      double precision M(3,3),temp

      temp = M(1,1)
      M(1,1) = M(2,2)
      M(2,2) = temp

      temp = M(1,3)
      M(1,3) = M(2,3)
      M(2,3) = temp

      temp = M(3,1)
      M(3,1) = M(3,2)
      M(3,2) = temp

      return
      end

