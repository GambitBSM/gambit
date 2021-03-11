      PROGRAM MAIN

*  Program to compute the NMSSM Higgs masses, couplings and
*  Branching ratios, with experimental and theoretical constraints
*
*   On input:      
*
*      tan(beta) at the scale MZ, lambda at the scale Q2
*      m0, M1/2, A0 at the scale MGUT      
*      non-universal parameters are allowed in the Higgs/gaugino sector
*
*   On output:
*
*      PAR(1) = lambda
*      PAR(2) = kappa
*      PAR(3) = tan(beta)
*      PAR(4) = mu (effective mu term = lambda*s)
*      PAR(5) = Alambda
*      PAR(6) = Akappa
*      PAR(7) = mQ3**2
*      PAR(8) = mU3**2
*      PAR(9) = mD3**2
*      PAR(10) = mL3**2
*      PAR(11) = mE3**2
*      PAR(12) = AU3
*      PAR(13) = AD3
*      PAR(14) = AE3
*      PAR(15) = mQ2**2
*      PAR(16) = mU2**2
*      PAR(17) = mD2**2
*      PAR(18) = mL2**2
*      PAR(19) = mE2**2
*      PAR(20) = M1
*      PAR(21) = M2
*      PAR(22) = M3
*      PAR(23) = MA (diagonal doublet CP-odd mass matrix element)
*      PAR(24) = MP (diagonal singlet CP-odd mass matrix element)
*      PAR(25) = AE2
*
*      All these parameters are assumed to be defined in DRbar at the scale
*      Q2 which is either user defined or computed as (2*mQ2+mU2+mD2)/4QSTSB=SQRT(PAR(7)*PAR(8))QSTSB=SQRT(PAR(7)*PAR(8))
*
*      SMASS(1-3): CP-even masses (ordered)
*
*      SCOMP(1-3,1-3): Mixing angles: if HB(I) are the bare states,
*        HB(I) = Re(H1), Re(H2), Re(S), and HM(I) are the mass eigenstates, 
*        the convention is HB(I) = SUM_(J=1,3) SCOMP(J,I)*HM(J)
*        which is equivalent to HM(I) = SUM_(J=1,3) SCOMP(I,J)*HB(J)
*
*      AMASS(1-2): CP-odd masses (ordered)
*
*      PCOMP(1-2,1-2): Mixing angles: if AB(I) are the bare states,
*        AB(I) = Im(H1), Im(H2), Im(S), and AM(I) are the mass eigenstates, 
*        the convention is 
*        AM(I) = PCOMP(I,1)*(COSBETA*AB(1)+SINBETA*AB(2))
*              + PCOMP(I,2)*AB(3)
*
*      CMASS: Charged Higgs mass
*
*      CU,CD,CV,CJ,CG(i) Reduced couplings of h1,h2,h3 (i=1,2,3) or
*                        a1,a2 (i=4,5) to up type fermions, down type
*                        fermions, gauge bosons, gluons and photons
*                        Note: CV(4)=CV(5)=0
*
*      WIDTH(i) Total decay width of h1,h2,h3,a1,a2 (i=1..5)
*               with the following branching ratios:
*      BRJJ(i) h1,h2,h3,a1,a2 -> gluon gluon
*      BRMM(i)        "       -> mu mu
*      BRLL(i)        "       -> tau tau
*      BRSS(i)        "       -> ss
*      BRCC(i)        "       -> cc
*      BRBB(i)        "       -> bb
*      BRTT(i)        "       -> tt
*      BRWW(i)        "       -> WW (BRWW(4)=BRWW(5)=0)
*      BRZZ(i)        "       -> ZZ (BRZZ(4)=BRZZ(5)=0)
*      BRGG(i)        "       -> gamma gamma
*      BRZG(i)        "       -> Z gamma
*      BRHIGGS(i)   (i=1..5)  -> other Higgses, including:
*        BRHAA(i,j)   hi      -> a1a1, a1a2, a2a2 (i=1..3, j=1..3)
*        BRHCHC(i)    hi      -> h+h- (i=1..3)
*        BRHAZ(i,j)   hi      -> Zaj  (i=1..3)
*        BRHCW(i)  h1,h2,h3   -> h+W- (i=1..3), a1,a2 -> h+W- (i=4,5)
*        BRHHH(i)     h2      -> h1h1, h3-> h1h1, h1h2, h2h2 (i=1..4)
*        BRAHA(i)     a2      -> a1hi (i=1..3)
*        BRAHZ(i,j)   ai      -> Zhj  (i=1,2, j=1..3)
*      BRSUSY(i)    (i=1..5)  -> susy particles, including:
*        BRNEU(i,j,k)         -> neutralinos j,k (i=1..5, j,k=1..5)
*        BRCHA(i,j)           -> charginos 11, 12, 22 (i=1..5, j=1..3)
*        BRHSQ(i,j)   hi      -> uLuL, uRuR, dLdL, dRdR, t1t1, t2t2,
*                                t1t2, b1b1, b2b2, b1b2 (i=1..3, j=1..10)
*        BRASQ(i,j)   ai      -> t1t2, b1b2 (i=1,2, j=1,2)
*        BRHSL(i,j)   hi      -> lLlL, lRlR, nLnL, l1l1, l2l2, l1l2,
*                                ntnt (i=1..3, j=1..7)
*        BRASL(i)     ai      -> l1l2 (i=1,2)
*
*      HCWIDTH  Total decay width of the charged Higgs
*               with the following branching ratios:
*      HCBRM         h+ -> mu nu_mu
*      HCBRL         "  -> tau nu_tau
*      HCBRSU        "  -> s u
*      HCBRBU        "  -> b u
*      HCBRSC        "  -> s c
*      HCBRBC        "  -> b c
*      HCBRBT        "  -> b t
*      HCBRWHT       "  -> neutral Higgs W+, including:
*        HCBRWH(i)   "  -> H1W+, H2W+, h3W+, a1W+, a2W+ (i=1..5)
*      HCBRSUSY      "  -> susy particles,including
*        HCBRNC(i,j) "  -> neutralino i chargino j (i=1..5, j=1,2)
*        HCBRSQ(i)   "  -> uLdL, t1b1, t1b2, t2b1, t2b2 (i=1..5)
*        HCBRSL(i)   "  -> lLnL, t1nt, t2nt (i=1..3)
*
*      MNEU(i)   Mass of neutralino chi_i (i=1,5, ordered in mass)
*      NEU(i,j)  chi_i components of bino, wino, higgsino u&d, singlino 
*                (i,j=1..5)
*
*      MCHA(i)       Chargino masses
*      U(i,j),V(i,j) Chargino mixing matrices
*
*  ERRORS: IFAIL = 0..16
*
*  IFAIL = 0         OK
*          1,3,5,7   m_h1^2 < 0
*          2,3,6,7   m_a1^2 < 0
*          4,5,6,7   m_h+^2 < 0
*          8         m_sfermion^2 < 0
*          9         l, tan(beta) or mu = 0
*          10        Violation of phenomenological constraint(s)
*          11,12,13  Problem in integration of RGEs
*          14,15     Convergence problem
*          16        No electroweak symmetry breaking
*
*  Phenomenological constraints:
*
*      PROB(I)  = 0, I = 1..49: OK
*            
*      PROB(1) =/= 0   chargino too light
*      PROB(2) =/= 0   excluded by Z -> neutralinos
*      PROB(3) =/= 0   charged Higgs too light
*      PROB(4) =/= 0   excluded by ee -> hZ 
*      PROB(5) =/= 0   excluded by ee -> hZ, h -> bb
*      PROB(6) =/= 0   excluded by ee -> hZ, h -> tautau
*      PROB(7) =/= 0   excluded by ee -> hZ, h -> invisible 
*      PROB(8) =/= 0   excluded by ee -> hZ, h -> 2jets
*      PROB(9) =/= 0   excluded by ee -> hZ, h -> 2photons
*      PROB(10) =/= 0  excluded by ee -> hZ, h -> AA -> 4bs
*      PROB(11) =/= 0  excluded by ee -> hZ, h -> AA -> 4taus
*      PROB(12) =/= 0  excluded by ee -> hZ, h -> AA -> 2bs 2taus
*      PROB(13) =/= 0  excluded by Z -> hA (Z width)
*      PROB(14) =/= 0  excluded by ee -> hA -> 4bs
*      PROB(15) =/= 0  excluded by ee -> hA -> 4taus
*      PROB(16) =/= 0  excluded by ee -> hA -> 2bs 2taus
*      PROB(17) =/= 0  excluded by ee -> hA -> AAA -> 6bs
*      PROB(18) =/= 0  excluded by ee -> hA -> AAA -> 6taus
*      PROB(19) =/= 0  excluded by ee -> Zh -> ZAA -> Z + light pairs
*      PROB(20) =/= 0  excluded by stop -> b l sneutrino
*      PROB(21) =/= 0  excluded by stop -> neutralino c
*      PROB(22) =/= 0  excluded by sbottom -> neutralino b
*      PROB(23) =/= 0  squark/gluino too light
*      PROB(24) =/= 0  selectron/smuon too light
*      PROB(25) =/= 0  stau too light
*      PROB(26) =/= 0  lightest neutralino is not LSP or < 511 keV
*      PROB(27) =/= 0  Landau Pole in l, k, ht, hb below MGUT
*      PROB(28) =/= 0  unphysical global minimum
*      PROB(29) =/= 0  Higgs soft masses >> Msusy
*      PROB(30) =/= 0  excluded by WMAP (checked only if OMGFLAG>=1)
*      PROB(31) =/= 0  excluded by Xenon100 (checked only if OMGFLAG=2 or 4)
*      PROB(32) =/= 0  b->s gamma more than 2 sigma away
*      PROB(33) =/= 0  Delta M_s more than 2 sigma away
*      PROB(34) =/= 0  Delta M_d more than 2 sigma away
*      PROB(35) =/= 0  B_s->mu+mu- more than 2 sigma away
*      PROB(36) =/= 0  B+-> tau+nu_tau more than 2 sigma away
*      PROB(37) =/= 0  (g-2)_muon more than 2 sigma away
*      PROB(38) =/= 0  excluded by Upsilon(1S) -> A gamma
*      PROB(39) =/= 0  excluded by eta_b(1S) mass measurement
*      PROB(40) =/= 0  BR(B-->X_s mu+ mu-) more than 2 sigma away
*      PROB(41) =/= 0  excluded by ee -> hZ, h -> AA -> 4taus (new ALEPH analysis)
*      PROB(42) =/= 0  excluded by top -> b H+, H+ -> c s (CDF, D0)
*      PROB(43) =/= 0  excluded by top -> b H+, H+ -> tau nu_tau (D0)
*      PROB(44) =/= 0  excluded by top -> b H+, H+ -> W+ A1, A1 -> 2taus (CDF)
*      PROB(45) =/= 0  excluded by t -> bH+ (LHC)
*      PROB(46) =/= 0  No Higgs in the MHmin-MHmax GeV range
*      PROB(47) =/= 0  chi2gam > chi2max
*      PROB(48) =/= 0  chi2bb > chi2max
*      PROB(49) =/= 0  chi2zz > chi2max
*
************************************************************************

      IMPLICIT NONE

      INTEGER NPROB,NPAR
      PARAMETER (NPROB=49,NPAR=25)
      INTEGER IFAIL,I,ITER,ITERMU,Q2FIX,IM
      INTEGER MUFLAG,SFFLAG,OMGFLAG,MAFLAG
      INTEGER M1FLAG,M2FLAG,M3FLAG,MHDFLAG
      INTEGER MHUFLAG,MSFLAG,AKFLAG,ALFLAG

      DOUBLE PRECISION PAR(NPAR),PROB(NPROB),CHECK,GUTEST,DELMB
      DOUBLE PRECISION DETM,R,K,MUM,MDM,MSM,MUT,MDT,MST,Q2,Q2MIN
      DOUBLE PRECISION M0,M12,A0,SIGMU,MUFAIL,MUSTEP,MUINIT
      DOUBLE PRECISION M1INP,M2INP,M3INP,MHDINP,MHUINP,ALINP,AKINP
      DOUBLE PRECISION XIFINP,XISINP,MUPINP,MSPINP,MSINP,M3HINP
      DOUBLE PRECISION M1GUT,M2GUT,M3GUT,ALGUT,AKGUT,ATGUT,ABGUT
      DOUBLE PRECISION ATAUGUT,AMUGUT,MHUGUT,MHDGUT,MSGUT,MQ3GUT
      DOUBLE PRECISION MU3GUT,MD3GUT,MQGUT,MUGUT,MDGUT,ML3GUT
      DOUBLE PRECISION ME3GUT,MLGUT,MEGUT
      DOUBLE PRECISION XIFGUT,XISGUT,MUPGUT,MSPGUT,M3HGUT

      COMMON/SIGMU/SIGMU
      COMMON/SOFTGUT/M0,M12,A0
      COMMON/INPPAR/M1INP,M2INP,M3INP,MHDINP,MHUINP,ALINP,AKINP,
     . XIFINP,XISINP,MUPINP,MSPINP,MSINP,M3HINP
      COMMON/GUTPAR/M1GUT,M2GUT,M3GUT,ALGUT,AKGUT,ATGUT,ABGUT,
     . ATAUGUT,AMUGUT,MHUGUT,MHDGUT,MSGUT,MQ3GUT,MU3GUT,MD3GUT,
     . MQGUT,MUGUT,MDGUT,ML3GUT,ME3GUT,MLGUT,MEGUT
      COMMON/GUTEXT/XIFGUT,XISGUT,MUPGUT,MSPGUT,M3HGUT
      COMMON/RENSCALE/Q2
      COMMON/Q2FIX/Q2MIN,Q2FIX
      COMMON/DELMB/DELMB
      COMMON/DETM/DETM
      COMMON/MUFAIL/MUFAIL
      COMMON/FLAGS/OMGFLAG,MAFLAG
      COMMON/MSAVE/MUM,MDM,MSM,MUT,MDT,MST,IM
      COMMON/SCANFLAGS/M1FLAG,M2FLAG,M3FLAG,MHDFLAG,MHUFLAG,
     . MSFLAG,AKFLAG,ALFLAG

*   I/O files

      OPEN(15,FILE='inp', STATUS= 'UNKNOWN')
      OPEN(17,FILE='spectr', STATUS= 'UNKNOWN') 
      OPEN(18,FILE='decay', STATUS= 'UNKNOWN') 
      OPEN(19,FILE='omega', STATUS= 'UNKNOWN')

*   Initialization

      CALL INITIALIZE()

*   Reading of the input parameters

      CALL INPUT(PAR,NPAR)
      
!      WRITE(0,*)"MAFLAG=",MAFLAG
!      WRITE(0,*)"M0 =",M0
!      IF(M1FLAG*M2FLAG*M3FLAG.EQ.0)WRITE(0,*)"M12 =",M12
!      WRITE(0,*)"TANB =",PAR(3)
!      IF(MAFLAG.NE.-5)WRITE(0,*)"SIGMU =",SIGMU
!      WRITE(0,*)"A0 =",A0
!      IF(M1FLAG.EQ.1)WRITE(0,*)"M1 =",M1INP
!      IF(M2FLAG.EQ.1)WRITE(0,*)"M2 =",M2INP
!      IF(M3FLAG.EQ.1)WRITE(0,*)"M3 =",M3INP
!      IF(MHUFLAG.EQ.1 .AND. MAFLAG.NE.-5)WRITE(0,*)"MHU =",MHUINP
!      IF(MHDFLAG.EQ.1 .AND. MAFLAG.NE.-5)WRITE(0,*)"MHD =",MHDINP
!      IF(MAFLAG.EQ.-2 .OR. MAFLAG.EQ.-4)WRITE(0,*)"MS =",MSINP
!      WRITE(0,*)"LAMBDA =",PAR(1)
!      IF(MAFLAG.EQ.-3 .OR. MAFLAG.EQ.-4 .OR. MAFLAG.EQ.-5)
!     . WRITE(0,*)"KAPPA =",PAR(2)
!      IF(ALFLAG.EQ.1)WRITE(0,*)"AL =",ALINP
!      IF(AKFLAG.EQ.1)WRITE(0,*)"AK =",AKINP
!      IF(MAFLAG.EQ.-5)WRITE(0,*)"MUEFF =",PAR(4)
!      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-2)WRITE(0,*)"XIF =",XIFINP
!      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-3)WRITE(0,*)"XIS =",XISINP
!      WRITE(0,*)"MUP =",MUPINP
!      WRITE(0,*)"MSP =",MSPINP
!      WRITE(0,*)"M3H =",M3HINP
!      WRITE(0,*)""

*   Initialization of PROB

      DO I=1,NPROB
       PROB(I)=0d0
      ENDDO      

*   Initialization of algorithm parameters

      SFFLAG=0
      MUINIT=SIGMU*DSQRT(PAR(3)*Q2MIN)
      MUSTEP=SIGMU*10d0
 1    MUINIT=MUINIT+MUSTEP
      MUFAIL=MUINIT-2d0*MUSTEP
      MUFLAG=0
      MUT=0d0
      MDT=0d0
      MST=0d0
      IM=0

*   Guess parameters at Q2/MGUT

      IF(Q2FIX.EQ.0)THEN
       Q2=MAX(M0**2+4d0*M12**2,Q2MIN)
      ENDIF
      R=(1d0+PAR(3)**2)/(1.29d0*PAR(3)**2)
      K=(1d0-R)*(A0-2.24d0*M12)**2+7.84d0*M12**2
      PAR(5)=ALINP-R/2d0*(A0-2.24d0*M12)-.59d0*M12
      PAR(6)=AKINP
      PAR(7)=(1d0-R/2d0)*M0**2+7.02d0*M12**2-R/6d0*K
      PAR(8)=(1d0-R)*M0**2+6.6d0*M12**2-R/3d0*K
      PAR(9)=M0**2+6.55d0*M12**2
      PAR(10)=M0**2+.52d0*M12**2
      PAR(11)=M0**2+.15d0*M12**2
      PAR(12)=A0-R*(A0-2.24d0*M12)-3.97d0*M12
      PAR(13)=A0-R/6d0*(A0-2.24d0*M12)-3.93d0*M12
      PAR(14)=A0-.69d0*M12
      PAR(15)=M0**2+7.02d0*M12**2
      PAR(16)=M0**2+6.6d0*M12**2
      PAR(17)=M0**2+6.55d0*M12**2
      PAR(18)=M0**2+.52d0*M12**2
      PAR(19)=M0**2+.15d0*M12**2
      PAR(20)=.4d0*M1INP
      PAR(21)=.8d0*M2INP
      PAR(22)=2.4d0*M3INP
      PAR(23)=DSQRT(Q2)
      PAR(24)=DSQRT(Q2)
      PAR(25)=A0-.69d0*M12
      DELMB=.1d0
      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-2)THEN
       PAR(2)=PAR(1)/5d0
      ELSE
       XIFGUT=0d0
      ENDIF
      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-3)THEN
       MSM=Q2
      ELSE
       XISGUT=0d0
      ENDIF
      IF(MAFLAG.EQ.-5)THEN
       MUM=10d0*M0**2
       MDM=M0**2
       MSM=Q2
      ELSE
       PAR(4)=MUINIT
      ENDIF
      IFAIL=0

!      WRITE(0,*)"New try"
!      WRITE(0,*)""
!      WRITE(0,*)"M1 =",PAR(20)
!      WRITE(0,*)"M2 =",PAR(21)
!      WRITE(0,*)"M3 =",PAR(22)
!      WRITE(0,*)"AL =",PAR(5)
!      WRITE(0,*)"AK =",PAR(6)
!      WRITE(0,*)"ATOP =",PAR(12)
!      WRITE(0,*)"ABOT =",PAR(13)
!      WRITE(0,*)"ATAU =",PAR(14)
!      WRITE(0,*)"AMUON =",PAR(25)
!      WRITE(0,*)"MQ3 =",PAR(7)
!      WRITE(0,*)"MU3 =",PAR(8)
!      WRITE(0,*)"MD3 =",PAR(9)
!      WRITE(0,*)"MQ =",PAR(15)
!      WRITE(0,*)"MU =",PAR(16)
!      WRITE(0,*)"MD =",PAR(17)
!      WRITE(0,*)"ML3 =",PAR(10)
!      WRITE(0,*)"ME3 =",PAR(11)
!      WRITE(0,*)"ML =",PAR(18)
!      WRITE(0,*)"ME =",PAR(19)
!      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-2)THEN
!       WRITE(0,*)"K =",PAR(2)
!      ELSE
!      WRITE(0,*)"XIF =",XIFGUT
!       ENDIF
!      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-3)THEN
!       WRITE(0,*)"MS =",MSM
!      ELSE
!       WRITE(0,*)"XIS =",XISGUT
!      ENDIF
!      IF(MAFLAG.EQ.-5)THEN
!       WRITE(0,*)"MHU =",MUM
!       WRITE(0,*)"MHD =",MDM
!       WRITE(0,*)"MS =",MSM
!      ELSE
!       WRITE(0,*)"MU =",PAR(4)
!      ENDIF
!      WRITE(0,*)""

*   Check for singular parameters l, tan(beta), mu

      IF(PAR(1)*PAR(3)*PAR(4).EQ.0d0)THEN
       IFAIL=9
       GOTO 11
      ENDIF

*   Guess for GUT scale and GUT couplings

      CALL RGES(PAR,PROB,IFAIL)
      IF(IFAIL.NE.0.OR.PROB(27).NE.0d0)THEN
!       WRITE(0,*)"RGE integration problem 1"
       IF(DABS(MUINIT).LT.100d0 .AND. DABS(MUSTEP).GT.1.D-1
     .    .AND. MAFLAG.NE.-5)THEN
        IF(SFFLAG.EQ.1)MUSTEP=MUSTEP/2d0
        GOTO 1
       ELSE
!        WRITE(0,*)"Exit (IFAIL=11)"
!        WRITE(0,*)""
!        WRITE(0,*)""
        IFAIL=11
        GOTO 11
       ENDIF
      ENDIF

*   External loop to compute the soft parameters at Q2

      ITER=0
 21   ITER=ITER+1
!      WRITE(0,*)"ITER =",ITER
!      WRITE(0,*)""
!      WRITE(0,*)""

      CALL RGESINV(PAR,IFAIL)
      IF(IFAIL.NE.0)THEN
!       WRITE(0,*)"RGE integration problem 2"
       IF(DABS(MUINIT).LT.100d0 .AND. DABS(MUSTEP).GT.1.D-1
     .    .AND. MAFLAG.NE.-5)THEN
        IF(SFFLAG.EQ.1)MUSTEP=MUSTEP/2d0
        GOTO 1
       ELSE
!        WRITE(0,*)"Exit (IFAIL=13)"
!        WRITE(0,*)""
!        WRITE(0,*)""
        IFAIL=13
        GOTO 11
       ENDIF
      ENDIF

*   Internal loop to compute ((k or XiF) and (mS or XiS) and mu)
*   or (mHu and mHd and mS), no iteration for the latter case

      ITERMU=0
 22   ITERMU=ITERMU+1
!      WRITE(0,*)"ITERMU =",ITERMU
!      WRITE(0,*)""
!      WRITE(0,*)""

      CALL RUNPAR(PAR)

      CALL MSFERM(PAR,IFAIL,0)
      IF(IFAIL.NE.0)THEN
!       WRITE(0,*)"Negative sfermion mass squared"
       IF(MAFLAG.NE.-5)THEN
        IF(DABS(MUINIT).GT.30d0)THEN
         SFFLAG=1
         MUINIT=MUINIT-2d0*MUSTEP
         GOTO 1
        ELSE
!         WRITE(0,*)"Exit (IFAIL=8)"
!         WRITE(0,*)""
!         WRITE(0,*)""
         IFAIL=8
         GOTO 11
        ENDIF
       ENDIF
      ENDIF

      CALL MINIMIZE(PAR,CHECK)
      IF(ITER.GT.10.AND.DETM.GE.0d0)MUFLAG=1

      IF(CHECK.GT.1.D-12.AND.ITERMU.LT.10) GOTO 22
      IF(CHECK.GT.1.D-9.AND.ITERMU.LT.100) GOTO 22
      IF(CHECK.GT.1.D-6)THEN
       IFAIL=14
       GOTO 11
      ENDIF
      
      CALL RGES(PAR,PROB,IFAIL)
      IF(IFAIL.NE.0.OR.PROB(27).NE.0d0)THEN
!       WRITE(0,*)"RGE integration problem 3"
       IF(DABS(MUINIT).LT.100d0 .AND. DABS(MUSTEP).GT.1.D-1
     .    .AND. MAFLAG.NE.-5)THEN
        IF(SFFLAG.EQ.1)MUSTEP=MUSTEP/2d0
        GOTO 1
       ELSE
!     WRITE(0,*)"Exit (IFAIL=11)"
!     WRITE(0,*)""
!     WRITE(0,*)""
          IFAIL=11
        GOTO 11
       ENDIF
      ENDIF

      CALL RGESUNI(PAR,IFAIL,GUTEST)
      IF(IFAIL.NE.0)THEN
!       WRITE(0,*)"RGE integration problem 4"
       IF(DABS(MUINIT).LT.100d0 .AND. DABS(MUSTEP).GT.1.D-1
     .    .AND. MAFLAG.NE.-5)THEN
        IF(SFFLAG.EQ.1)MUSTEP=MUSTEP/2d0
        GOTO 1
       ELSE
!        WRITE(0,*)"Exit (IFAIL=12)"
!        WRITE(0,*)""
!        WRITE(0,*)""
        IFAIL=12
        GOTO 11
       ENDIF
      ENDIF

      IF(GUTEST.GT.1.D-12.AND.ITER.LT.10) GOTO 21
      IF(GUTEST.GT.1.D-9.AND.ITER.LT.100) GOTO 21
      IF(GUTEST.GT.1.D-6.AND.ITER.LT.1000) GOTO 21
      IF(GUTEST.GT.1.D-3)THEN
!       WRITE(0,*)"No convergence"
       IF(DABS(MUSTEP).GT.1.D-1 .AND. MAFLAG.NE.-5)THEN
        MUSTEP=MUSTEP/2d0
        MUFAIL=MUFAIL+MUSTEP
        MUFLAG=0
        MUT=0d0
        MDT=0d0
        MST=0d0
        IM=0
        ITER=0
!        WRITE(0,*)"New try"
!        WRITE(0,*)"MUFAIL =",MUFAIL
!        WRITE(0,*)""
!        WRITE(0,*)""
        GOTO 21
       ELSE
!        WRITE(0,*)"Exit (IFAIL=15)"
!        WRITE(0,*)""
!        WRITE(0,*)""
        IFAIL=15
        GOTO 11
       ENDIF
      ENDIF

*   Check if correct EWSB

      IF(DETM.LE.0d0 .AND. MAFLAG.NE.-5)THEN
!       WRITE(0,*)"Convergence in a false minimum"
       IF(MUFLAG.EQ.1 .AND. DABS(MUSTEP).GT.1.D-1)THEN
        MUSTEP=MUSTEP/2d0
        MUFAIL=MUFAIL+MUSTEP
        MUFLAG=0
        MUT=0d0
        MDT=0d0
        MST=0d0
        IM=0
        ITER=0
!        WRITE(0,*)"New try"
!        WRITE(0,*)"MUFAIL =",MUFAIL
!        WRITE(0,*)""
!        WRITE(0,*)""
        GOTO 21
       ELSEIF(MUFLAG.EQ.0 .AND. DABS(MUSTEP).LT.DABS(MUFAIL))THEN
        MUFAIL=MUFAIL-MUSTEP
        MUFLAG=0
        MUT=0d0
        MDT=0d0
        MST=0d0
        IM=0
        ITER=0
!        WRITE(0,*)"New try"
!        WRITE(0,*)"MUFAIL =",MUFAIL
!        WRITE(0,*)""
!        WRITE(0,*)""
        GOTO 21
       ELSEIF(DETM.LT.0d0)THEN
!        WRITE(0,*)"Exit (IFAIL=16)"
!        WRITE(0,*)""
!        WRITE(0,*)""
        IFAIL=16
        GOTO 11
       ENDIF
      ENDIF

*   Computation of sfermion masses

      CALL MSFERM(PAR,IFAIL,1)
      IF(IFAIL.NE.0)GOTO 11
      
*   Computation of Higgs masses

      CALL MHIGGS(PAR,IFAIL)
      IF(IFAIL.NE.0)GOTO 11

*   Computation of gluino mass

      CALL GLUINO(PAR)      
      
*   Computation of chargino masses

      CALL CHARGINO(PAR)

*   Computation of neutralino masses

      CALL NEUTRALINO(PAR)
      
*   Computation of Higgs + top branching ratios

      CALL DECAY(PAR)
      CALL TDECAY(PAR)

*   Exp. constraints

      CALL SUBEXP(PAR,PROB)

*   b -> s gamma + B physics

      CALL BSG(PAR,PROB)
      
*   Anom. magn. moment of the Muon

      CALL MAGNMU(PAR,PROB)

*   Global minimum?

      CALL CHECKMIN(PROB)

*   Relic density

      CALL RELDEN(PAR,PROB)

*   Check for problems

      DO I=1,NPROB
       IF(PROB(I).NE.0d0)IFAIL=10
      ENDDO

*   Computation of the fine-tuning
      
      CALL FTPAR(PAR,1)

*   Sparticle decays

      CALL NMSDECAY(PAR)

*   Recording of the results

11    CALL OUTPUT(PAR,PROB,IFAIL)

      END


      SUBROUTINE INPUT(PAR,NPAR)
      
*******************************************************************
*   This subroutine reads SM and NMSSM parameters from input file   .
*******************************************************************

      IMPLICIT NONE

      CHARACTER CHINL*120,CHBLCK*60,CHDUM*120

      INTEGER I,NLINE,INL,ICH,IX,IVAL,Q2FIX
      INTEGER N0,NLOOP,NBER,NPAR,ERR,NMSFLAG,GMUFLAG,HFLAG
      INTEGER M1FLAG,M2FLAG,M3FLAG,MHDFLAG,MHUFLAG
      INTEGER MSFLAG,AKFLAG,ALFLAG,OMGFLAG,MAFLAG,PFLAG

      DOUBLE PRECISION PAR(*),VAL
      DOUBLE PRECISION ACC,XITLA,XLAMBDA,MC0,MB0,MT0
      DOUBLE PRECISION ALSMZ,ALEMMZ,GF,g1,g2,S2TW
      DOUBLE PRECISION MSB,MS,MC,MB,MBP,MT,MTAU,MMUON,MZ,MW
      DOUBLE PRECISION VUS,VCB,VUB,Q2,Q2MIN
      DOUBLE PRECISION M0,M12,A0,SIGMU
      DOUBLE PRECISION M1INP,M2INP,M3INP,MHDINP,MHUINP,ALINP,AKINP
      DOUBLE PRECISION XIFINP,XISINP,MUPINP,MSPINP,MSINP,M3HINP

      COMMON/GAUGE/ALSMZ,ALEMMZ,GF,g1,g2,S2TW
      COMMON/SMSPEC/MS,MC,MB,MBP,MT,MTAU,MMUON,MZ,MW
      COMMON/CKM/VUS,VCB,VUB
      COMMON/ALS/XLAMBDA,MC0,MB0,MT0,N0
      COMMON/RENSCALE/Q2
      COMMON/SOFTGUT/M0,M12,A0
      COMMON/SIGMU/SIGMU
      COMMON/INPPAR/M1INP,M2INP,M3INP,MHDINP,MHUINP,ALINP,AKINP,
     . XIFINP,XISINP,MUPINP,MSPINP,MSINP,M3HINP
      COMMON/Q2FIX/Q2MIN,Q2FIX
      COMMON/SCANFLAGS/M1FLAG,M2FLAG,M3FLAG,MHDFLAG,MHUFLAG,
     . MSFLAG,AKFLAG,ALFLAG
      COMMON/FLAGS/OMGFLAG,MAFLAG
      COMMON/PFLAG/PFLAG
      COMMON/NMSFLAG/NMSFLAG
      COMMON/GMUFLAG/GMUFLAG,HFLAG

*   INITIALIZATION OF THE SUSY PARAMETERS
      DO I=1,NPAR
       PAR(I)=0d0
      ENDDO
      PAR(1)=1d99
      PAR(2)=1d99
      PAR(3)=1d99
      PAR(4)=1d99
      SIGMU=1d99
      M0=1d99
      M12=1d99
      A0=1d99
      M1INP=1d99
      M2INP=1d99
      M3INP=1d99
      MHDINP=1d99
      MHUINP=1d99
      MSINP=1d99
      ALINP=1d99
      AKINP=1d99
      XIFINP=1d99
      XISINP=1d99
      MUPINP=0d0
      MSPINP=0d0
      M3HINP=0d0

*   DEFAULT VALUE FOR FLAGS
      OMGFLAG=0
      PFLAG=0
      NMSFLAG=0
      M1FLAG=0
      M2FLAG=0
      M3FLAG=0
      MHDFLAG=0
      MHUFLAG=0
      MSFLAG=1
      ALFLAG=0
      AKFLAG=0
      HFLAG=0

*   DEFAULT VALUE FOR THE RENSCALE Q2
      Q2=0d0
      
*   INITIALIZE READ LOOP
      NLINE=0
      CHBLCK=' '
      
*   START TO READ NEW LINE INTO CHINL
 21   CHINL=' '
 
*   LINE NUMBER
      NLINE=NLINE+1
      READ(15,'(A120)',END=29,ERR=999) CHINL
     
*   CHECK FOR EMPTY OR COMMENT LINES
      IF(CHINL.EQ.' '.OR.CHINL(1:1).EQ.'#'
     .  .OR.CHINL(1:1).EQ.'*') GOTO 21
      
*   FORCE UPPER CASE LETTERS IN CHINL (AS REQUIRED BELOW)
      INL=0
 22   INL=INL+1
      IF(CHINL(INL:INL).NE.'#')THEN
       DO ICH=97,122
        IF(CHINL(INL:INL).EQ.CHAR(ICH)) CHINL(INL:INL)=CHAR(ICH-32)
       ENDDO
       IF(INL.LT.120) GOTO 22
      ENDIF
      
*   CHECK FOR BLOCK STATEMENT
      IF(CHINL(1:1).EQ.'B')THEN
       READ(CHINL,'(A6,A)',ERR=999) CHDUM,CHBLCK
       GOTO 21
      ENDIF

*   CHECK FOR NMSSM MODEL IN MODSEL
*   IF THE RELIC DENSITY SHOULD BE COMPUTED
*   THE BLOCK MODSEL MUST CONTAIN THE LINE "  9     1    "
      IF(CHBLCK(1:6).EQ.'MODSEL')THEN
       READ(CHINL,*,ERR=999) IX,IVAL
       IF(IX.EQ.8) PFLAG=IVAL
       IF(IX.EQ.9) OMGFLAG=IVAL
       IF(IX.EQ.13) NMSFLAG=IVAL

*   READ SMINPUTS
      ELSEIF(CHBLCK(1:8).EQ.'SMINPUTS')THEN
       READ(CHINL,*,ERR=999) IX,VAL
       IF(IX.EQ.2) GF=VAL
       IF(IX.EQ.3) ALSMZ=VAL
       IF(IX.EQ.4) MZ=VAL
       IF(IX.EQ.5) MB=VAL
       IF(IX.EQ.6) MT=VAL
       IF(IX.EQ.7) MTAU=VAL
      
*   READ GUT PARAMETERS, SIGMU, Q2 AND TANBETA
      ELSEIF(CHBLCK(1:6).EQ.'MINPAR')THEN
       READ(CHINL,*,ERR=999) IX,VAL
       IF(IX.EQ.0) Q2=VAL**2
       IF(IX.EQ.1) M0=VAL
       IF(IX.EQ.2) M12=VAL
       IF(IX.EQ.3) PAR(3)=VAL
       IF(IX.EQ.4) SIGMU=VAL
       IF(IX.EQ.5) A0=VAL
      
*   READ EXTPAR
      ELSEIF(CHBLCK(1:6).EQ.'EXTPAR')THEN
       READ(CHINL,*,ERR=999) IX,VAL
       IF(IX.EQ.1) M1INP=VAL
       IF(IX.EQ.2) M2INP=VAL
       IF(IX.EQ.3) M3INP=VAL
       IF(IX.EQ.21) MHDINP=VAL
       IF(IX.EQ.22) MHUINP=VAL
       IF(IX.EQ.61) PAR(1)=VAL
       IF(IX.EQ.62) PAR(2)=VAL
       IF(IX.EQ.63) ALINP=VAL
       IF(IX.EQ.64) AKINP=VAL
       IF(IX.EQ.65) PAR(4)=VAL
       IF(IX.EQ.66) XIFINP=VAL
       IF(IX.EQ.67) XISINP=VAL
       IF(IX.EQ.68) MUPINP=VAL
       IF(IX.EQ.69) MSPINP=VAL
       IF(IX.EQ.70) MSINP=VAL
       IF(IX.EQ.72) M3HINP=VAL

      ENDIF
      
      GOTO 21

*   END OF READING FROM INPUT FILE

*   Check for errors

 29   ERR=0
      
      IF(M0.EQ.1d99)THEN
       WRITE(0,1)"M0 MUST BE GIVEN IN BLOCK MINPAR"
       ERR=1
      ENDIF
      IF(A0.EQ.1d99)THEN
       WRITE(0,1)"A0 MUST BE GIVEN IN BLOCK MINPAR"
       ERR=1
      ENDIF
      IF(PAR(1).EQ.1d99)THEN
       WRITE(0,1)"LAMBDA MUST BE GIVEN IN BLOCK EXTPAR"
       ERR=1
      ENDIF
      IF(PAR(3).EQ.1d99)THEN
       WRITE(0,1)"TANB MUST BE GIVEN IN BLOCK MINPAR"
       ERR=1
      ENDIF
      IF(DABS(SIGMU).NE.1d0 .AND. PAR(4).EQ.1d99)THEN
       WRITE(0,1)"SIGMU IS EITHER 1 OR -1 IN BLOCK MINPAR"
       ERR=1
      ENDIF
      IF(SIGMU.NE.1d99 .AND. PAR(4).NE.1d99)THEN
       WRITE(0,1)"BOTH MUEFF AND SIGMU CANNOT BE GIVEN"
       ERR=1
      ENDIF
      IF(PAR(4).NE.1d99)THEN
       IF(MHUINP.NE.1d99)THEN
        WRITE(0,1)"BOTH MUEFF AND MHU^2 CANNOT BE GIVEN IN BLOCK EXTPAR"
        ERR=1
       ENDIF
       IF(MHDINP.NE.1d99)THEN
        WRITE(0,1)"BOTH MUEFF AND MHD^2 CANNOT BE GIVEN IN BLOCK EXTPAR"
        ERR=1
       ENDIF
       IF(MSINP.NE.1d99)THEN
        WRITE(0,1)"BOTH MUEFF AND MS^2 CANNOT BE GIVEN IN BLOCK EXTPAR"
        ERR=1
       ENDIF
      ELSE
       IF(XIFINP.NE.1d99 .AND. PAR(2).NE.1d99)THEN
        WRITE(0,1)"BOTH XIF AND KAPPA CANNOT BE GIVEN IN BLOCK EXTPAR"
        ERR=1
       ENDIF
       IF(XISINP.NE.1d99 .AND. MSINP.NE.1d99)THEN
        WRITE(0,1)"BOTH XIS AND MS^2 CANNOT BE GIVEN IN BLOCK EXTPAR"
        ERR=1
       ENDIF
      ENDIF

*   Set default values

      IF(PAR(4).NE.1d99)THEN
       IF(PAR(2).EQ.1d99 )PAR(2)=0d0
       IF(XIFINP.EQ.1d99)XIFINP=0d0
       IF(XISINP.EQ.1d99)XISINP=0d0
      ELSE
       IF(PAR(2).EQ.1d99 .AND. XIFINP.EQ.1d99)XIFINP=0d0
       IF(MSINP.EQ.1d99 .AND. XISINP.EQ.1d99)XISINP=0d0
      ENDIF

      IF(PAR(2).EQ.0d0)THEN
       IF(AKINP.NE.0d0 .AND. AKINP.NE.1d99)THEN
        WRITE(0,1)"WARNING KAPPA=0 => AKAPPA=0"
       ENDIF
       AKINP=0d0
      ENDIF

*   Set MAFLAG, SCANFLAGS

      IF(PAR(4).NE.1d99)THEN
       MAFLAG=-5
       MHDFLAG=1
       MHUFLAG=1
      ELSE
       MAFLAG=-1
       IF(PAR(2).NE.1d99)MAFLAG=MAFLAG-2
       IF(MSINP.NE.1d99)MAFLAG=MAFLAG-1
       IF(MHDINP.EQ.1d99)THEN
        MHDINP=M0**2
       ELSE
        MHDFLAG=1
       ENDIF
       IF(MHUINP.EQ.1d99)THEN
        MHUINP=M0**2
       ELSE
        MHUFLAG=1
       ENDIF
       IF(MAFLAG.EQ.-2 .OR. MAFLAG.EQ.-4)THEN
        IF(MSINP.EQ.M0**2)MSFLAG=0
       ENDIF
      ENDIF

      IF(M1INP.EQ.1d99)THEN
       M1INP=M12
      ELSE
       M1FLAG=1
      ENDIF
      IF(M2INP.EQ.1d99)THEN
       M2INP=M12
      ELSE
       M2FLAG=1
      ENDIF
      IF(M3INP.EQ.1d99)THEN
       M3INP=M12
      ELSE
       M3FLAG=1
      ENDIF
      IF(ALINP.EQ.1d99)THEN
       ALINP=A0
      ELSE
       ALFLAG=1
      ENDIF
      IF(AKINP.EQ.1d99)THEN
       AKINP=A0
      ELSE
       AKFLAG=1
      ENDIF

      IF(M1FLAG*M2FLAG*M3FLAG.EQ.0)THEN
       IF(M12.EQ.1d99)THEN
        WRITE(0,1)"M12 MUST BE GIVEN IN BLOCK MINPAR"
        ERR=1
       ENDIF
      ELSE
       IF(M12.NE.1d99)WRITE(0,1)"WARNING: M12 IS NOT USED"
      ENDIF

*   Stop if error

      IF(ERR.EQ.1)THEN
       WRITE(0,1)"ERROR IN INPUT FILE"
       STOP 1
      ENDIF

*   Set Q2MIN, Q2FIX:      

      Q2MIN=100d0**2
      Q2FIX=1
      IF(Q2.LE.Q2MIN)THEN
       Q2FIX=0
      ENDIF

*   Initialization for ALPHAS and RUNM (as in hdecay)
*   The bottom quark pole mass MBP is set in INIT and can be changed
*   only there (changing its running mass MB above has no effect
*   on MBP, since one would have to compute alpha_s(MB) first)

      MSB=MS
      MC0=MC
      MB0=MBP
      MT0=MT
      N0=5
      NLOOP=2
      NBER=18
      ACC=1.D-8
      XLAMBDA=XITLA(NLOOP,ALSMZ,ACC)
      CALL ALSINI(ACC)
      CALL BERNINI(NBER)
      
*   g1,g2  and sin(theta)^2 in the on-shell scheme in terms of
*   GF, MZ(pole) and MW(pole)

      g2=4d0*DSQRT(2d0)*GF*MW**2
      g1=4d0*DSQRT(2d0)*GF*(MZ**2-MW**2)
      S2TW=1d0-(MW/MZ)**2
      
      RETURN

 999  WRITE(0,1)"READ ERROR ON LINE:", NLINE
!      WRITE(0,*)CHINL(1:80)
      STOP 1

 1    FORMAT(A)

      END


      SUBROUTINE OUTPUT(PAR,PROB,IFAIL)

*********************************************************************      
*   Subroutine writing all the results in the the output files.
*********************************************************************      
 
      IMPLICIT NONE

      INTEGER I,NBIN,IFAIL,Q2FIX
      INTEGER M1FLAG,M2FLAG,M3FLAG,MHDFLAG,MHUFLAG,MSFLAG
      INTEGER AKFLAG,ALFLAG,NMSFLAG,OMGFLAG,MAFLAG,PFLAG
      INTEGER NSUSY,NGUT,NMES
      PARAMETER (NSUSY=14,NGUT=21,NMES=15)

      DOUBLE PRECISION PAR(*),PROB(*),SIG(3,8)
      DOUBLE PRECISION SMASS(3),AMASS(2),CMASS,SCOMP(3,3),PCOMP(2,2)
      DOUBLE PRECISION MGL,MCHA(2),U(2,2),V(2,2),MNEU(5),NEU(5,5)
      DOUBLE PRECISION BRJJ(5),BRMM(5),BRLL(5),BRSS(5),BRCC(5)
      DOUBLE PRECISION BRBB(5),BRTT(5),BRWW(3),BRZZ(3),BRGG(5)
      DOUBLE PRECISION BRZG(5),BRHHH(4),BRHAA(3,3),BRHCHC(3)
      DOUBLE PRECISION BRHAZ(3,2),BRAHA(3),BRAHZ(2,3),BRHCW(5)
      DOUBLE PRECISION BRHIGGS(5),BRNEU(5,5,5),BRCHA(5,3)
      DOUBLE PRECISION BRHSQ(3,10),BRHSL(3,7),BRASQ(2,2),BRASL(2)
      DOUBLE PRECISION BRSUSY(5),WIDTH(5)
      DOUBLE PRECISION HCBRM,HCBRL,HCBRSU,HCBRBU,HCBRSC,HCBRBC
      DOUBLE PRECISION HCBRBT,HCBRWH(5),HCBRWHT,HCBRNC(5,2)
      DOUBLE PRECISION HCBRSQ(5),HCBRSL(3),HCBRSUSY,HCWIDTH
      DOUBLE PRECISION CU(5),CD(5),CV(3),CJ(5),CG(5)
      DOUBLE PRECISION ALSMZ,ALEMMZ,GF,g1,g2,S2TW
      DOUBLE PRECISION MS,MC,MB,MBP,MT,MTAU,MMUON,MZ,MW
      DOUBLE PRECISION VUS,VCB,VUB,TANB,SINB,COSB
      DOUBLE PRECISION MUR,MUL,MDR,MDL,MLR,MLL,MNL
      DOUBLE PRECISION MST1,MST2,MSB1,MSB2,MSL1,MSL2,MSNT
      DOUBLE PRECISION CST,CSB,CSL,MSMU1,MSMU2,MSMUNT,CSMU
      DOUBLE PRECISION SST,SSB,SSL,Q2,Q2MIN,SSMU
      DOUBLE PRECISION MGUT,g1s,g2s,g3s,HTOPS,HBOTS,HTAUS
      DOUBLE PRECISION MHUS,MHDS,MSS
      DOUBLE PRECISION G1GUT,G2GUT,G3GUT,LGUT,KGUT,HTOPGUT
      DOUBLE PRECISION HBOTGUT,HTAUGUT,M1GUT,M2GUT,M3GUT,ALGUT,AKGUT
      DOUBLE PRECISION ATGUT,ABGUT,ATAUGUT,AMUGUT,MHUGUT,MHDGUT,MSGUT
      DOUBLE PRECISION MQ3GUT,MU3GUT,MD3GUT,MQGUT,MUGUT,MDGUT,ML3GUT
      DOUBLE PRECISION ME3GUT,MLGUT,MEGUT,M0,M12,A0,SIGMU
      DOUBLE PRECISION M1INP,M2INP,M3INP,MHDINP,MHUINP,ALINP,AKINP
      DOUBLE PRECISION XIFINP,XISINP,MUPINP,MSPINP,MSINP,M3HINP
      DOUBLE PRECISION XIFGUT,XISGUT,MUPGUT,MSPGUT,M3HGUT
      DOUBLE PRECISION XIFSUSY,XISSUSY,MUPSUSY,MSPSUSY,M3HSUSY
      DOUBLE PRECISION OMG,OMGMIN,OMGMAX,LOAMASS
      DOUBLE PRECISION Xf,sigmaV,x(100),dNdx(100),EMIN
      DOUBLE PRECISION sigmaPiN,sigmaS,csPsi,csNsi,csPsd,csNsd
      DOUBLE PRECISION MHUQ,MHDQ,MSQ,LQ,KQ,ALQ,AKQ,MUQ,NUQ
      DOUBLE PRECISION ZHU,ZHD,ZS,H1Q,H2Q,TANBQ,QSTSB
      DOUBLE PRECISION BRSG,BRSGmax,BRSGmin,DMd,DMdmin,DMdmax,DMs,
     . DMsmax,DMsmin,BRBMUMU,BRBMUMUmax,BRBMUMUmin,BRBtaunu,
     . BRBtaunumax,BRBtaunumin
      DOUBLE PRECISION delmagmu,damumin,damumax,amuthmax,amuthmin
      DOUBLE PRECISION brtopbw,brtopbh,brtopneutrstop(5,2),toptot
      DOUBLE PRECISION FTSUSY(NSUSY+2),FTGUT(NGUT+2),FTMES(NMES+2)
      DOUBLE PRECISION DELMB,PX,PA(6),PB(2),PL(7),PK(8),MH(3),MMH(3)
      DOUBLE PRECISION DMH(3),MA(2),MMA(2),DMA(2),MHC,MMHC,DMHC
      DOUBLE PRECISION MHmin,MHmax,chi2max,chi2gam,chi2bb,chi2zz
      DOUBLE PRECISION XENON100,PRINTCHANNELS,omg_

      DOUBLE PRECISION HUQ,HDQ,MTQ,MBQ
      DOUBLE PRECISION G1Q,G2Q,GQ,ALSQ
      DOUBLE PRECISION MQ3P,MU3P,MD3P,ATP,ABP

      COMMON/PFLAG/PFLAG
      COMMON/NMSFLAG/NMSFLAG
      COMMON/FLAGS/OMGFLAG,MAFLAG
      COMMON/SCANFLAGS/M1FLAG,M2FLAG,M3FLAG,MHDFLAG,MHUFLAG,
     . MSFLAG,AKFLAG,ALFLAG
      COMMON/SIGMU/SIGMU
      COMMON/SOFTGUT/M0,M12,A0
      COMMON/INPPAR/M1INP,M2INP,M3INP,MHDINP,MHUINP,ALINP,AKINP,
     . XIFINP,XISINP,MUPINP,MSPINP,MSINP,M3HINP
      COMMON/BRN/BRJJ,BRMM,BRLL,BRSS,BRCC,BRBB,BRTT,BRWW,BRZZ,
     . BRGG,BRZG,BRHHH,BRHAA,BRHCHC,BRHAZ,BRAHA,BRAHZ,
     . BRHCW,BRHIGGS,BRNEU,BRCHA,BRHSQ,BRHSL,BRASQ,BRASL,
     . BRSUSY,WIDTH
      COMMON/BRC/HCBRM,HCBRL,HCBRSU,HCBRBU,HCBRSC,HCBRBC,
     . HCBRBT,HCBRWH,HCBRWHT,HCBRNC,HCBRSQ,HCBRSL,
     . HCBRSUSY,HCWIDTH
      COMMON/BRSG/BRSG,BRSGmax,BRSGmin,DMd,DMdmin,DMdmax,DMs,
     . DMsmax,DMsmin,BRBMUMU,BRBMUMUmax,BRBMUMUmin,BRBtaunu,
     . BRBtaunumax,BRBtaunumin
      COMMON/MAGMU/delmagmu,damumin,damumax,amuthmax,amuthmin
      COMMON/BR_top2body/brtopbw,brtopbh,brtopneutrstop
      COMMON/topwidth/toptot
      COMMON/REDCOUP/CU,CD,CV,CJ,CG
      COMMON/HIGGSPEC/SMASS,SCOMP,AMASS,PCOMP,CMASS
      COMMON/SUSYSPEC/MGL,MCHA,U,V,MNEU,NEU
      COMMON/GAUGE/ALSMZ,ALEMMZ,GF,g1,g2,S2TW
      COMMON/SMSPEC/MS,MC,MB,MBP,MT,MTAU,MMUON,MZ,MW
      COMMON/CKM/VUS,VCB,VUB
      COMMON/SFSPEC/MUR,MUL,MDR,MDL,MLR,MLL,MNL,
     . MST1,MST2,MSB1,MSB2,MSL1,MSL2,MSNT,
     . CST,CSB,CSL,MSMU1,MSMU2,MSMUNT,CSMU
      COMMON/Q2FIX/Q2MIN,Q2FIX
      COMMON/RENSCALE/Q2
      COMMON/STSBSCALE/QSTSB
      COMMON/MGUT/MGUT
      COMMON/SUSYCOUP/g1s,g2s,g3s,HTOPS,HBOTS,HTAUS
      COMMON/SUSYMH/MHUS,MHDS,MSS
      COMMON/QMHIGGS/MHUQ,MHDQ,MSQ
      COMMON/QHIGGS/ZHU,ZHD,ZS,H1Q,H2Q,TANBQ
      COMMON/QQUARK/HUQ,HDQ,MTQ,MBQ
      COMMON/QPAR/LQ,KQ,ALQ,AKQ,MUQ,NUQ
      COMMON/GUTCOUP/G1GUT,G2GUT,G3GUT,LGUT,KGUT,HTOPGUT,
     . HBOTGUT,HTAUGUT
      COMMON/GUTPAR/M1GUT,M2GUT,M3GUT,ALGUT,AKGUT,ATGUT,ABGUT,
     . ATAUGUT,AMUGUT,MHUGUT,MHDGUT,MSGUT,MQ3GUT,MU3GUT,MD3GUT,
     . MQGUT,MUGUT,MDGUT,ML3GUT,ME3GUT,MLGUT,MEGUT
      COMMON/GUTEXT/XIFGUT,XISGUT,MUPGUT,MSPGUT,M3HGUT
      COMMON/SUSYEXT/XIFSUSY,XISSUSY,MUPSUSY,MSPSUSY,M3HSUSY
      COMMON/MICROMG/OMG,OMGMIN,OMGMAX,Xf,sigmaV,x,dNdx,EMIN,NBIN
      COMMON/MICROMG2/sigmaPiN,sigmaS,csPsi,csNsi,csPsd,csNsd
      COMMON/FINETUN/FTSUSY,FTGUT,FTMES
      COMMON/EFFHIGM/MH,MMH,DMH,MA,MMA,DMA,MHC,MMHC,DMHC
      COMMON/EFFCOUP/PX,PA,PB,PL,PK
      COMMON/DELMB/DELMB
      COMMON/LHCSIG/SIG
      COMMON/HIGGSFIT/MHmin,MHmax,chi2max,chi2gam,chi2bb,chi2zz
      COMMON/QGAUGE/G1Q,G2Q,GQ,ALSQ
      COMMON/RADCOR2/MQ3P,MU3P,MD3P,ATP,ABP

      TANB=PAR(3)
      COSB=1d0/DSQRT(1d0+TANB**2)
      SINB=TANB*COSB

      WRITE(17,899) "# NMSSMTools OUTPUT IN SLHA FORMAT"
      WRITE(17,899) "# Info about spectrum calculator"
      WRITE(17,899) "BLOCK SPINFO   # Program information"
      WRITE(17,900) 1,"NMSSMTools # Spectrum calculator"
      WRITE(17,900) 2,"4.1.1      # Version number"

      IF(PROB(1).NE.0d0)
     . WRITE(17,900) 3,"# Chargino too light"
      IF(PROB(2).NE.0d0)
     . WRITE(17,900) 3,"# Neutralinos too light"
      IF(PROB(3).NE.0d0)
     . WRITE(17,900) 3,"# Charged Higgs too light"
      IF(PROB(4).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, ind. of h decay"
      IF(PROB(5).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> bb"
      IF(PROB(6).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> tautau"
      IF(PROB(7).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> invisible"
      IF(PROB(8).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> 2jets"
      IF(PROB(9).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> 2photons"
      IF(PROB(10).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> AA -> 4bs"
      IF(PROB(11).NE.0d0 .OR. PROB(41).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> AA -> 4taus"
      IF(PROB(12).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> AA -> 2bs 2taus"
      IF(PROB(19).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hZ, h -> AA,A -> light pair"
      IF(PROB(13).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> Z -> hA (Z width)"
      IF(PROB(14).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hA -> 4bs"
      IF(PROB(15).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hA -> 4taus"
      IF(PROB(16).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hA -> 2bs 2taus"
      IF(PROB(17).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hA -> AAA -> 6bs"
      IF(PROB(18).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by ee -> hA -> AAA -> 6taus"
      IF(PROB(20).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by stop -> b l sneutrino"
      IF(PROB(21).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by stop -> neutralino c"
      IF(PROB(22).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by sbottom -> neutralino b"
      IF(PROB(23).NE.0d0)
     . WRITE(17,900) 3,"# Squark/gluino too light"
      IF(PROB(24).NE.0d0)
     . WRITE(17,900) 3,"# Selectron/smuon too light"
      IF(PROB(25).NE.0d0)
     . WRITE(17,900) 3,"# Stau too light"
      IF(PROB(26).GT.0d0)
     . WRITE(17,900) 3,"# Lightest neutralino is not the LSP"
      IF(PROB(26).LT.0d0)
     . WRITE(17,900) 3,"# Mass of the lightest neutralino < 511 keV"
      IF(PROB(27).NE.0d0)
     . WRITE(17,900) 3,"# Landau Pole below MGUT"
      IF(PROB(28).NE.0d0)
     . WRITE(17,900) 3,"# Unphysical global minimum"
      IF(PROB(29).NE.0d0)
     . WRITE(17,900) 3,"# Higgs soft masses >> Msusy"
      IF(PROB(30).GT.0d0)WRITE(17,900) 3,
     . "# Relic density too large (WMAP)"
      IF(PROB(30).LT.0d0.AND.PROB(30).NE.-1d0)
     . WRITE(17,900) 3,"# Relic density too small (WMAP)"
      IF(PROB(30).EQ.-1d0)
     . WRITE(17,900) 3,"# Problem in micrOMEGAs"
      IF(PROB(31).NE.0d0)WRITE(17,900) 3,
     . "# Excluded by Xenon100"
      IF(PROB(32).NE.0d0)
     . WRITE(17,900) 3,"# b -> s gamma more than 2 sigma away"
      IF(PROB(33).NE.0d0)
     . WRITE(17,900) 3,"# Delta M_s more than 2 sigma away"
      IF(PROB(34).NE.0d0)
     . WRITE(17,900) 3,"# Delta M_d more than 2 sigma away"
      IF(PROB(35).NE.0d0)
     . WRITE(17,900) 3,"# B_s -> mu+ mu- more than 2 sigma away"
      IF(PROB(36).NE.0d0)
     . WRITE(17,900) 3,"# B+ -> tau nu_tau more than 2 sigma away"
      IF(PROB(37).NE.0d0)
     . WRITE(17,900) 3,"# Muon magn. mom. more than 2 sigma away"
      IF(PROB(38).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by Upsilon(1S) -> A gamma (CLEO)"
      IF(PROB(38).LT.0d0)
     . WRITE(17,900) 3,"# (but A width> 10 MeV)"
      IF(PROB(39).NE.0d0)
     . WRITE(17,900) 3,
     . "# Excluded etab(1S) mass difference (BABAR - theory)"
       IF(PROB(40).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by BR(B -> X_s mu +mu-)"
       IF(PROB(42).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by top -> b H+, H+ -> c s"
       IF(PROB(43).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by top -> b H+, H+ -> tau nu_tau"
       IF(PROB(44).NE.0d0)
     . WRITE(17,900) 3,
     . "# Excluded by top -> b H+, H+ -> W+ A1, A1 -> 2taus"
       IF(PROB(45).NE.0d0)
     . WRITE(17,900) 3,"# Excluded by t -> bH+ (LHC)"
       IF(PROB(46).NE.0d0)
     . WRITE(17,918) 3,"# No Higgs in the",MHMIN,MHMAX," GeV mass range"
       IF(PROB(47).NE.0d0)
     . WRITE(17,919) 3,"# chi2(H->gg) > ",chi2MAX
       IF(PROB(48).NE.0d0)
     . WRITE(17,919) 3,"# chi2(H->bb) > ",chi2MAX
       IF(PROB(49).NE.0d0)
     . WRITE(17,919) 3,"# chi2(H->ZZ) > ",chi2MAX

      IF(IFAIL.EQ.1.OR.IFAIL.EQ.3.OR.IFAIL.EQ.5.OR.IFAIL.EQ.7)
     . WRITE(17,900) 4,"# M_H1^2<1"
      IF(IFAIL.EQ.2.OR.IFAIL.EQ.3.OR.IFAIL.EQ.6.OR.IFAIL.EQ.7)
     . WRITE(17,900) 4,"# M_A1^2<1"
      IF(IFAIL.EQ.4.OR.IFAIL.EQ.5.OR.IFAIL.EQ.6.OR.IFAIL.EQ.7)
     . WRITE(17,900) 4,"# M_HC^2<1"
      IF(IFAIL.EQ.8)
     . WRITE(17,900) 4,"# Negative sfermion mass squared"
      IF(IFAIL.EQ.9)
     . WRITE(17,900) 4,"# Disallowed parameters: lambda or tan(beta)=0"
      IF(IFAIL.EQ.11)
     . WRITE(17,900) 4,"# Integration problem in RGES"
      IF(IFAIL.EQ.12)
     . WRITE(17,900) 4,"# Integration problem in RGESUNI"
      IF(IFAIL.EQ.13)
     . WRITE(17,900) 4,"# Integration problem in RGESINV"
      IF(IFAIL.EQ.14.OR.IFAIL.EQ.15)
     . WRITE(17,900) 4,"# Convergence Problem"
      IF(IFAIL.EQ.16)
     . WRITE(17,900) 4,"# No electroweak symmetry breaking"

      WRITE(17,899) "# Input parameters"
      WRITE(17,899) "BLOCK MODSEL"
      WRITE(17,921) 3,1,"NMSSM particle content"
      WRITE(17,921) 1,1,"IMOD"
      WRITE(17,921) 10,0,"ISCAN"
      WRITE(17,921) 9,OMGFLAG,"Call micrOmegas"
      WRITE(17,921) 8,PFLAG,"Precision for Higgs masses"
      WRITE(17,921) 13,NMSFLAG,"Sparticle decays via NMSDECAY"

      WRITE(17,899) "BLOCK SMINPUTS"
      WRITE(17,901) 1,1d0/ALEMMZ,"ALPHA_EM^-1(MZ)"
      WRITE(17,901) 2,GF,"GF"
      WRITE(17,901) 3,ALSMZ,"ALPHA_S(MZ)"
      WRITE(17,901) 4,MZ,"MZ"
      WRITE(17,901) 5,MB,"MB(MB)"
      WRITE(17,901) 6,MT,"MTOP (POLE MASS)"
      WRITE(17,901) 7,MTAU,"MTAU"
      WRITE(17,899) "# SMINPUTS Beyond SLHA:"
      WRITE(17,906) "MW:",MW
      WRITE(17,906) "MS:",MS
      WRITE(17,906) "MC:",MC
      WRITE(17,906) "VUS:",VUS
      WRITE(17,906) "VCB:",VCB
      WRITE(17,906) "VUB:",VUB
      
      WRITE(17,899) "BLOCK MINPAR"
      IF(Q2FIX.EQ.1)WRITE(17,901) 0,DSQRT(Q2),"REN. SCALE"
      WRITE(17,901) 1,M0,"M0(MGUT)"
      WRITE(17,901) 2,M12,"M12(MGUT)"
      WRITE(17,901) 3,TANB,"TANBETA(MZ)"
      IF(MAFLAG.NE.-5)THEN
       WRITE(17,901) 4,SIGMU,"SIGMU"
      ELSE
       WRITE(17,920) 4,SIGMU,"SIGMU"
      ENDIF
      WRITE(17,901) 5,A0,"A0(MGUT)"

      WRITE(17,899) "BLOCK EXTPAR"       
      IF(M1FLAG.EQ.1)WRITE(17,901) 1,M1INP,"M1 AT THE GUT SCALE"
      IF(M2FLAG.EQ.1)WRITE(17,901) 2,M2INP,"M2 AT THE GUT SCALE"
      IF(M3FLAG.EQ.1)WRITE(17,901) 3,M3INP,"M3 AT THE GUT SCALE"
      IF(MHDFLAG.EQ.1)THEN
       IF(MAFLAG.NE.-5)THEN
        WRITE(17,901) 21,MHDINP,"MHD^2 AT THE GUT SCALE"
       ELSE
        WRITE(17,920) 21,MHDGUT,"MHD^2 AT THE GUT SCALE"
       ENDIF
      ENDIF
      IF(MHUFLAG.EQ.1)THEN
       IF(MAFLAG.NE.-5)THEN
        WRITE(17,901) 22,MHUINP,"MHU^2 AT THE GUT SCALE"      
       ELSE
        WRITE(17,920) 22,MHUGUT,"MHU^2 AT THE GUT SCALE"      
       ENDIF
      ENDIF
      WRITE(17,901) 61,PAR(1),"LAMBDA AT THE SUSY SCALE"
      IF(MAFLAG.EQ.-3 .OR. MAFLAG.EQ.-4 .OR. MAFLAG.EQ.-5)THEN
        WRITE(17,901) 62,PAR(2),"KAPPA AT THE SUSY SCALE"
      ELSE
        WRITE(17,920) 62,PAR(2),"KAPPA AT THE SUSY SCALE"
      ENDIF
      IF(ALFLAG.EQ.1)WRITE(17,901) 63,ALINP,"ALAMBDA AT THE GUT SCALE"
      IF(AKFLAG.EQ.1)WRITE(17,901) 64,AKINP,"AKAPPA AT THE GUT SCALE"
      IF(MAFLAG.EQ.-5)THEN
       WRITE(17,901) 65,PAR(4),"MUEFF AT THE SUSY SCALE"
      ELSE
       WRITE(17,920) 65,PAR(4),"MUEFF AT THE SUSY SCALE"
      ENDIF
      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-2 .OR.MAFLAG.EQ.-5)THEN
       IF(XIFINP.NE.0d0)
     .  WRITE(17,901) 66,XIFINP,"XIF AT THE GUT SCALE"
      ELSE
       WRITE(17,920) 66,XIFGUT,"XIF AT THE GUT SCALE"
      ENDIF
      IF(MAFLAG.EQ.-1 .OR. MAFLAG.EQ.-3 .OR.MAFLAG.EQ.-5)THEN
       IF(XISINP.NE.0d0)
     .  WRITE(17,901) 67,XISINP,"XIS AT THE GUT SCALE"
      ELSE
       WRITE(17,920) 67,XISGUT,"XIS AT THE GUT SCALE"
      ENDIF
      IF(MUPINP.NE.0d0)
     .  WRITE(17,901) 68,MUPINP,"MU' AT THE GUT SCALE "
      IF(MSPINP.NE.0d0)
     .  WRITE(17,901) 69,MSPINP,"MS'^2 AT THE GUT SCALE "
      IF(MAFLAG.EQ.-2 .OR. MAFLAG.EQ.-4)THEN
       WRITE(17,901) 70,MSINP,"MS^2 AT THE GUT SCALE"
      ELSE
       WRITE(17,920) 70,MSGUT,"MS^2 AT THE GUT SCALE"
      ENDIF
      IF(M3HINP.NE.0d0)
     .  WRITE(17,901) 72,M3HINP,"M3H^2 AT THE GUT SCALE "

      IF(IFAIL.NE.0.AND.IFAIL.NE.10) GOTO 1
      
      WRITE(17,899) "# "
      WRITE(17,899) "BLOCK MASS   # Mass spectrum "
      WRITE(17,899) "#  PDG Code     mass             particle "
      WRITE(17,902) 25,SMASS(1),"lightest neutral scalar"
      WRITE(17,902) 35,SMASS(2),"second neutral scalar"
      WRITE(17,902) 45,SMASS(3),"third neutral scalar"
      WRITE(17,902) 36,AMASS(1),"lightest pseudoscalar"
      WRITE(17,902) 46,AMASS(2),"second pseudoscalar"
      WRITE(17,902) 37,CMASS,"charged Higgs"
      WRITE(17,902) 1000001,MDL," ~d_L"
      WRITE(17,902) 2000001,MDR," ~d_R"
      WRITE(17,902) 1000002,MUL," ~u_L"
      WRITE(17,902) 2000002,MUR," ~u_R"       
      WRITE(17,902) 1000003,MDL," ~s_L"
      WRITE(17,902) 2000003,MDR," ~s_R"       
      WRITE(17,902) 1000004,MUL," ~c_L"
      WRITE(17,902) 2000004,MUR," ~c_R"       
      WRITE(17,902) 1000005,MSB1," ~b_1"
      WRITE(17,902) 2000005,MSB2," ~b_2"       
      WRITE(17,902) 1000006,MST1," ~t_1"
      WRITE(17,902) 2000006,MST2," ~t_2"       
      WRITE(17,902) 1000011,MLL," ~e_L"
      WRITE(17,902) 2000011,MLR," ~e_R"
      WRITE(17,902) 1000012,MNL," ~nue_L"
      WRITE(17,902) 1000013,MSMU1," ~mu_L"
      WRITE(17,902) 2000013,MSMU2," ~mu_R"
      WRITE(17,902) 1000014,MSMUNT," ~numu_L"
      WRITE(17,902) 1000015,MSL1," ~tau_1"
      WRITE(17,902) 2000015,MSL2," ~tau_2"
      WRITE(17,902) 1000016,MSNT," ~nutau_L"
      WRITE(17,902) 1000021,MGL," ~g"
      WRITE(17,902) 1000022,MNEU(1),"neutralino(1)"
      WRITE(17,902) 1000023,MNEU(2),"neutralino(2)"
      WRITE(17,902) 1000025,MNEU(3),"neutralino(3)"
      WRITE(17,902) 1000035,MNEU(4),"neutralino(4)"
      WRITE(17,902) 1000045,MNEU(5),"neutralino(5)"
      WRITE(17,902) 1000024,MCHA(1),"chargino(1)"
      WRITE(17,902) 1000037,MCHA(2),"chargino(2)"
      
      WRITE(17,899) "# " 
      WRITE(17,899) "# Low energy observables"
      WRITE(17,899) "BLOCK LOWEN"
      WRITE(17,899)
     .   "# Exp. 2 Sigma: 3.04E-4 < BR(b -> s gamma) < 4.06E-4:"
      WRITE(17,901) 1,BRSG,"BR(b -> s gamma)"
      WRITE(17,901) 11,BRSGMAX,"(BR(b -> s gamma)+Theor.Err.)"
      WRITE(17,901) 12,BRSGMIN,"(BR(b -> s gamma)-Theor.Err.)"
      WRITE(17,899) "# Exp. 2 Sigma: 4.99E-1 < Delta M_d < 5.15E-1:"
      WRITE(17,901) 2,DMD,"Delta M_d in ps^-1"
      WRITE(17,901) 21,DMdmax,"Delta M_d +Theor.Err."
      WRITE(17,901) 22,DMdmin,"Delta M_d -Theor.Err."
      WRITE(17,899) 
     .   "# Exp. 2 Sigma: 1.7633E+1 < Delta Ms < 1.7805E+1:"
      WRITE(17,901) 3,DMS,"Delta M_s in ps^-1"
      WRITE(17,901) 31,DMsmax,"Delta M_s +Theor.Err."
      WRITE(17,901) 32,DMsmin,"Delta M_s -Theor.Err."
      WRITE(17,899) "# Exp. 2 Sigma: 2.0E-9 < BR(Bs->mu+mu-) < 4.7E-9:"
      WRITE(17,901) 4,BRBMUMU,"BR(Bs -> mu+mu-)"
      WRITE(17,901) 41,BRBMUMUmax,"BR(Bs -> mu+mu-)+Theor.Err."
      WRITE(17,901) 42,BRBMUMUmin,"BR(Bs -> mu+mu-)-Theor.Err."
      WRITE(17,899) 
     .   "# Exp. 2 Sigma: 1.07E-4 < BR(B+ > tau+ + nu_tau) < 2.27E-4:"
      WRITE(17,901) 5,BRBtaunu,"BR(B+ -> tau+ + nu_tau)"
      WRITE(17,901) 51,BRBtaunumax,
     .   "BR(B+ -> tau+ + nu_tau) + Theor.Err."
      WRITE(17,901) 52,BRBtaunumin,
     .   "BR(B+ -> tau+ + nu_tau) - Theor.Err."
      WRITE(17,899) "# " 
      WRITE(17,899) "# BSM contr. to the muon anomalous magn. moment:"
      WRITE(17,901) 6,delmagmu,"Del_a_mu"
      WRITE(17,901) 61,amuthmax,"Del_a_mu + Theor.Err."
      WRITE(17,901) 62,amuthmin,"Del_a_mu - Theor.Err."
      WRITE(17,907) "# Minimal Exp.-SM (2 sigma):",damumin
      WRITE(17,907) "# Maximal Exp.-SM (2 sigma):",damumax
     
      IF(OMGFLAG.NE.0)THEN
	WRITE(17,899) "# " 
	WRITE(17,911)
     .   "# Omega h^2 (allowed:",OMGMIN," < Omega h^2 <",OMGMAX,"):"
	IF(OMG.EQ.0d0)THEN
	  WRITE(17,899) "# Cannot compute Omega h^2 (mLSP < 1 GeV)"
	ELSEIF(OMG.EQ.-1d0)THEN
	  WRITE(17,899) 
     .      "# Lightest neutralino is not the LSP in micrOMEGAs"
	ELSEIF(OMG.EQ.-2d0)THEN
	  WRITE(17,899) "# Problem in micrOMEGAs"
	ELSE
	  WRITE(17,901) 10,OMG,"Omega h^2"
	  omg_=printChannels(Xf,1.D-3,1.D-4,1,17)
	ENDIF
      ENDIF
      IF(OMGFLAG.EQ.2 .OR. OMGFLAG.EQ.4)THEN
	WRITE(17,907)"# sigma(p)_SI (allowed: sigma_p^SI < ",
     .   XENON100(DABS(MNEU(1))),"):"
	WRITE(17,901) 20,CSPSI,"sigma_p^SI"
	WRITE(17,915)"# values used for sigma_piN,sigma_S",
     .  " (strange content of the proton)"
	WRITE(17,901) 30,sigmapiN,"sigma_piN"
	WRITE(17,901) 40,sigmaS,"sigma_S"
      ENDIF
!      IF(OMGFLAG.NE.0)CALL printRelDen(PROB,17)
     
      WRITE(17,899) "# "
      WRITE(17,907) "BLOCK HMIX Q=",DSQRT(QSTSB),
     .    " # (STOP/SBOTTOM MASSES)"
      WRITE(17,901) 1,MUQ,"MUEFF"
      WRITE(17,901) 2,TANBQ,"TAN(BETA)"
      WRITE(17,901) 3,DSQRT(2d0*(H1Q**2+H2Q**2)),"V(Q)"
      WRITE(17,901) 4,PAR(23)**2,"MA^2"      
      WRITE(17,901) 5,PAR(24)**2,"MP^2"      
      
      WRITE(17,899) "# "
      WRITE(17,907) "BLOCK HMIXATQSTSB Q=",DSQRT(QSTSB),
     .    " # (STOP/SBOTTOM MASSES)"
      WRITE(17,901) 1,MUQ,"MUEFF"
      WRITE(17,901) 2,TANBQ,"TAN(BETA)"
      WRITE(17,901) 3,DSQRT(2d0*(H1Q**2+H2Q**2)),"V(Q)"
      WRITE(17,901) 4,PAR(23)**2,"MA^2"      

      WRITE(17,899) "# "
      WRITE(17,899) "# 3*3 Higgs mixing"
      WRITE(17,899) "BLOCK NMHMIX"
      WRITE(17,903) 1,1,SCOMP(1,2),"S_(1,1)"
      WRITE(17,903) 1,2,SCOMP(1,1),"S_(1,2)"
      WRITE(17,903) 1,3,SCOMP(1,3),"S_(1,3)"
      WRITE(17,903) 2,1,SCOMP(2,2),"S_(2,1)"
      WRITE(17,903) 2,2,SCOMP(2,1),"S_(2,2)"
      WRITE(17,903) 2,3,SCOMP(2,3),"S_(2,3)"
      WRITE(17,903) 3,1,SCOMP(3,2),"S_(3,1)"
      WRITE(17,903) 3,2,SCOMP(3,1),"S_(3,2)"
      WRITE(17,903) 3,3,SCOMP(3,3),"S_(3,3)"

      WRITE(17,899) "# "      
      WRITE(17,899) "# 3*3 Pseudoscalar Higgs mixing"
      WRITE(17,899) "BLOCK NMAMIX"
      WRITE(17,903) 1,1,SINB*PCOMP(1,1),"P_(1,1)"
      WRITE(17,903) 1,2,COSB*PCOMP(1,1),"P_(1,2)"
      WRITE(17,903) 1,3,PCOMP(1,2),"P_(1,3)"
      WRITE(17,903) 2,1,SINB*PCOMP(2,1),"P_(2,1)"
      WRITE(17,903) 2,2,COSB*PCOMP(2,1),"P_(2,2)"
      WRITE(17,903) 2,3,PCOMP(2,2),"P_(2,3)"
                  
      SST=DSQRT(1-CST**2)
      SSB=DSQRT(1-CSB**2)
      SSL=DSQRT(1-CSL**2)
      SSL=DSQRT(1-CSMU**2)

      WRITE(17,899) "# "
      WRITE(17,899) "# 3rd generation sfermion mixing"
      WRITE(17,899) "BLOCK STOPMIX  # Stop mixing matrix"
      WRITE(17,903) 1,1,CST,"Rst_(1,1)"
      WRITE(17,903) 1,2,SST,"Rst_(1,2)"
      WRITE(17,903) 2,1,-SST,"Rst_(2,1)"
      WRITE(17,903) 2,2,CST,"Rst_(2,2)"
      WRITE(17,899) "BLOCK SBOTMIX  # Sbottom mixing matrix"
      WRITE(17,903) 1,1,CSB,"Rsb_(1,1)"
      WRITE(17,903) 1,2,SSB,"Rsb_(1,2)"
      WRITE(17,903) 2,1,-SSB,"Rsb_(2,1)"
      WRITE(17,903) 2,2,CSB,"Rsb_(2,2)"
      WRITE(17,899) "BLOCK STAUMIX  # Stau mixing matrix"
      WRITE(17,903) 1,1,CSL,"Rsl_(1,1)"
      WRITE(17,903) 1,2,SSL,"Rsl_(1,2)"
      WRITE(17,903) 2,1,-SSL,"Rsl_(2,1)"
      WRITE(17,903) 2,2,CSL,"Rsl_(2,2)"
      WRITE(17,899) "BLOCK SMUMIX  # Smuon mixing matrix"
      WRITE(17,903) 1,1,CSMU,"Rsmu_(1,1)"
      WRITE(17,903) 1,2,SSMU,"Rsmu_(1,2)"
      WRITE(17,903) 2,1,-SSMU,"Rsmu_(2,1)"
      WRITE(17,903) 2,2,CSMU,"Rsmu_(2,2)"

      WRITE(17,899) "# "
      WRITE(17,899) "# Gaugino-Higgsino mixing"
      WRITE(17,899) "BLOCK NMNMIX  # 5*5 Neutralino Mixing Matrix"
      WRITE(17,903) 1,1,NEU(1,1),"N_(1,1)"
      WRITE(17,903) 1,2,NEU(1,2),"N_(1,2)"
      WRITE(17,903) 1,3,NEU(1,4),"N_(1,3)"
      WRITE(17,903) 1,4,NEU(1,3),"N_(1,4)"
      WRITE(17,903) 1,5,NEU(1,5),"N_(1,5)"
      WRITE(17,903) 2,1,NEU(2,1),"N_(2,1)"
      WRITE(17,903) 2,2,NEU(2,2),"N_(2,2)"
      WRITE(17,903) 2,3,NEU(2,4),"N_(2,3)"
      WRITE(17,903) 2,4,NEU(2,3),"N_(2,4)"
      WRITE(17,903) 2,5,NEU(2,5),"N_(2,5)"
      WRITE(17,903) 3,1,NEU(3,1),"N_(3,1)"
      WRITE(17,903) 3,2,NEU(3,2),"N_(3,2)"
      WRITE(17,903) 3,3,NEU(3,4),"N_(3,3)"
      WRITE(17,903) 3,4,NEU(3,3),"N_(3,4)"
      WRITE(17,903) 3,5,NEU(3,5),"N_(3,5)"
      WRITE(17,903) 4,1,NEU(4,1),"N_(4,1)"
      WRITE(17,903) 4,2,NEU(4,2),"N_(4,2)"
      WRITE(17,903) 4,3,NEU(4,4),"N_(4,3)"
      WRITE(17,903) 4,4,NEU(4,3),"N_(4,4)"
      WRITE(17,903) 4,5,NEU(4,5),"N_(4,5)"
      WRITE(17,903) 5,1,NEU(5,1),"N_(5,1)"
      WRITE(17,903) 5,2,NEU(5,2),"N_(5,2)"
      WRITE(17,903) 5,3,NEU(5,4),"N_(5,3)"
      WRITE(17,903) 5,4,NEU(5,3),"N_(5,4)"
      WRITE(17,903) 5,5,NEU(5,5),"N_(5,5)"

      WRITE(17,899) "# "
      WRITE(17,899) "BLOCK UMIX  # Chargino U Mixing Matrix"
      WRITE(17,903) 1,1,U(1,1),"U_(1,1)"
      WRITE(17,903) 1,2,U(1,2),"U_(1,2)"
      WRITE(17,903) 2,1,U(2,1),"U_(2,1)"
      WRITE(17,903) 2,2,U(2,2),"U_(2,2)"

      WRITE(17,899) "# "
      WRITE(17,899) "BLOCK VMIX  # Chargino V Mixing Matrix"
      WRITE(17,903) 1,1,V(1,1),"V_(1,1)"
      WRITE(17,903) 1,2,V(1,2),"V_(1,2)"
      WRITE(17,903) 2,1,V(2,1),"V_(2,1)"
      WRITE(17,903) 2,2,V(2,2),"V_(2,2)"

      WRITE(17,899) "# "
      WRITE(17,899) "# Higgs reduced couplings"
      WRITE(17,899) "# (as compared to a SM Higgs with same mass)"
      WRITE(17,899) "BLOCK REDCOUP"
      WRITE(17,899) "# H1"
      WRITE(17,903) 1,1,CU(1),"U-type fermions"
      WRITE(17,903) 1,2,CD(1),"D-type fermions"
      WRITE(17,903) 1,3,CV(1),"W,Z bosons"
      WRITE(17,903) 1,4,CJ(1),"Gluons"
      WRITE(17,903) 1,5,CG(1),"Photons"
      WRITE(17,899) "# H2"
      WRITE(17,903) 2,1,CU(2),"U-type fermions"
      WRITE(17,903) 2,2,CD(2),"D-type fermions"
      WRITE(17,903) 2,3,CV(2),"W,Z bosons"
      WRITE(17,903) 2,4,CJ(2),"Gluons"
      WRITE(17,903) 2,5,CG(2),"Photons"
      WRITE(17,899) "# H3"
      WRITE(17,903) 3,1,CU(3),"U-type fermions"
      WRITE(17,903) 3,2,CD(3),"D-type fermions"
      WRITE(17,903) 3,3,CV(3),"W,Z bosons"
      WRITE(17,903) 3,4,CJ(3),"Gluons"
      WRITE(17,903) 3,5,CG(3),"Photons"
      WRITE(17,899) "# A1"
      WRITE(17,903) 4,1,CU(4),"U-type fermions"
      WRITE(17,903) 4,2,CD(4),"D-type fermions"
      WRITE(17,903) 4,3,0.,"W,Z bosons"
      WRITE(17,903) 4,4,CJ(4),"Gluons"
      WRITE(17,903) 4,5,CG(4),"Photons"
      WRITE(17,899) "# A2"
      WRITE(17,903) 5,1,CU(5),"U-type fermions"
      WRITE(17,903) 5,2,CD(5),"D-type fermions"
      WRITE(17,903) 5,3,0.,"W,Z bosons"
      WRITE(17,903) 5,4,CJ(5),"Gluons"
      WRITE(17,903) 5,5,CG(5),"Photons"

      WRITE(17,899) "# "
      WRITE(17,899) "# GAUGE AND YUKAWA COUPLINGS AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK GAUGEATQ2=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,901) 1,DSQRT(G1S),"g1(Q,DR_bar)"
      WRITE(17,901) 2,DSQRT(G2S),"g2(Q,DR_bar)"
      WRITE(17,901) 3,DSQRT(G3S),"g3(Q,DR_bar)"

      WRITE(17,907) "BLOCK YUATQ2=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,HTOPS,"HTOP(Q,DR_bar)"
      WRITE(17,907) "BLOCK YDATQ2=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,HBOTS,"HBOT(Q,DR_bar)"
      WRITE(17,907) "BLOCK YEATQ2=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,HTAUS,"HTAU(Q,DR_bar)"

      WRITE(17,899) "# "
      WRITE(17,899) "# GAUGE AND YUKAWA COUPLINGS AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK GAUGEATQSTSB=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,901) 1,DSQRT(G1Q),"g1(Q,DR_bar)"
      WRITE(17,901) 2,DSQRT(G2Q),"g2(Q,DR_bar)"
     

      WRITE(17,907) "BLOCK YUATQSTSB=",DSQRT(QSTSB)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,HUQ,"HTOP(Q,DR_bar)"
      WRITE(17,907) "BLOCK YDATQSTSB=",DSQRT(QSTSB)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,HDQ,"HBOT(Q,DR_bar)"
     

      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT TRILINEAR COUPLINGS AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK AUATQ2 Q=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,PAR(12),"ATOP"
      WRITE(17,907) "BLOCK ADATQ2 Q=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,903) 3,3,PAR(13),"ABOT"
      WRITE(17,907) "BLOCK AEATQ2 Q=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,903) 2,2,PAR(25),"AMUON"
      WRITE(17,903) 3,3,PAR(14),"ATAU"

      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT TRILINEAR COUPLINGS AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK AUATQSTSB Q=",DSQRT(QSTSB)," # (STSB SCALE)"
      WRITE(17,903) 3,3,ATP,"# ATOP"
      WRITE(17,907) "BLOCK ADATQSTSB Q=",DSQRT(QSTSB)," # (STSB SCALE)"
      WRITE(17,903) 3,3,ABP,"# ABOT"
      

      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT MASSES AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK MSOFT Q=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,901) 1,PAR(20),"M1"
      WRITE(17,901) 2,PAR(21),"M2"
      WRITE(17,901) 3,PAR(22),"M3"
      WRITE(17,901) 21,MHDS,"M_HD^2"
      WRITE(17,901) 22,MHUS,"M_HU^2"
      WRITE(17,901) 31,PAR(18)/DSQRT(DABS(PAR(18))),"M_eL"
      WRITE(17,901) 32,PAR(18)/DSQRT(DABS(PAR(18))),"M_muL"
      WRITE(17,901) 33,PAR(10)/DSQRT(DABS(PAR(10))),"M_tauL"
      WRITE(17,901) 34,PAR(19)/DSQRT(DABS(PAR(19))),"M_eR"
      WRITE(17,901) 35,PAR(19)/DSQRT(DABS(PAR(19))),"M_muR"
      WRITE(17,901) 36,PAR(11)/DSQRT(DABS(PAR(11))),"M_tauR"
      WRITE(17,901) 41,PAR(15)/DSQRT(DABS(PAR(15))),"M_q1L"
      WRITE(17,901) 42,PAR(15)/DSQRT(DABS(PAR(15))),"M_q2L"
      WRITE(17,901) 43,PAR(7)/DSQRT(DABS(PAR(7))),"M_q3L"
      WRITE(17,901) 44,PAR(16)/DSQRT(DABS(PAR(16))),"M_uR"
      WRITE(17,901) 45,PAR(16)/DSQRT(DABS(PAR(16))),"M_cR"
      WRITE(17,901) 46,PAR(8)/DSQRT(DABS(PAR(8))),"M_tR"
      WRITE(17,901) 47,PAR(17)/DSQRT(DABS(PAR(17))),"M_dR"
      WRITE(17,901) 48,PAR(17)/DSQRT(DABS(PAR(17))),"M_sR"
      WRITE(17,901) 49,PAR(9)/DSQRT(DABS(PAR(9))),"M_bR"
      

      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT MASSES AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK MSOFTATQ2 Q=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,901) 1,PAR(20),"M1"
      WRITE(17,901) 2,PAR(21),"M2"
      WRITE(17,901) 3,PAR(22),"M3"
      WRITE(17,901) 21,MHDS,"M_HD^2"
      WRITE(17,901) 22,MHUS,"M_HU^2"
      WRITE(17,901) 31,PAR(18)/DSQRT(DABS(PAR(18))),"M_eL"
      WRITE(17,901) 32,PAR(18)/DSQRT(DABS(PAR(18))),"M_muL"
      WRITE(17,901) 33,PAR(10)/DSQRT(DABS(PAR(10))),"M_tauL"
      WRITE(17,901) 34,PAR(19)/DSQRT(DABS(PAR(19))),"M_eR"
      WRITE(17,901) 35,PAR(19)/DSQRT(DABS(PAR(19))),"M_muR"
      WRITE(17,901) 36,PAR(11)/DSQRT(DABS(PAR(11))),"M_tauR"
      WRITE(17,901) 41,PAR(15)/DSQRT(DABS(PAR(15))),"M_q1L"
      WRITE(17,901) 42,PAR(15)/DSQRT(DABS(PAR(15))),"M_q2L"
      WRITE(17,901) 43,PAR(7)/DSQRT(DABS(PAR(7))),"M_q3L"
      WRITE(17,901) 44,PAR(16)/DSQRT(DABS(PAR(16))),"M_uR"
      WRITE(17,901) 45,PAR(16)/DSQRT(DABS(PAR(16))),"M_cR"
      WRITE(17,901) 46,PAR(8)/DSQRT(DABS(PAR(8))),"M_tR"
      WRITE(17,901) 47,PAR(17)/DSQRT(DABS(PAR(17))),"M_dR"
      WRITE(17,901) 48,PAR(17)/DSQRT(DABS(PAR(17))),"M_sR"
      WRITE(17,901) 49,PAR(9)/DSQRT(DABS(PAR(9))),"M_bR"
      
      
      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT MASSES AT THE SUSY SCALE"
      WRITE(17,907) "BLOCK MSOFTATQSTSB Q=",DSQRT(QSTSB)
      WRITE(17,901) 43,MQ3P/DSQRT(DABS(MQ3P)),"M_q3L"
      WRITE(17,901) 46,MU3P/DSQRT(DABS(MU3P)),"M_tR"
      WRITE(17,901) 49,MD3P/DSQRT(DABS(MD3P)),"M_bR"
      


      WRITE(17,899) "# "
      WRITE(17,899) "# NMSSM SPECIFIC PARAMETERS THE SUSY SCALE"
      WRITE(17,907) "BLOCK NMSSMRUNATQ2 Q=",DSQRT(Q2)," # (SUSY SCALE)"
      WRITE(17,901) 1,PAR(1),"LAMBDA(Q,DR_bar)"
      WRITE(17,901) 2,PAR(2),"KAPPA(Q,DR_bar)"
      WRITE(17,901) 3,PAR(5),"ALAMBDA"
      WRITE(17,901) 4,PAR(6),"AKAPPA"
      WRITE(17,901) 5,PAR(4),"MUEFF"
      WRITE(17,901) 6,XIFSUSY,"XIF"
      WRITE(17,901) 7,XISSUSY,"XIS"
      WRITE(17,901) 8,MUPSUSY,"MU'"
      WRITE(17,901) 9,MSPSUSY,"MS'^2"
      WRITE(17,901) 10,MSS,"MS^2"
      WRITE(17,901) 12,M3HSUSY,"M3H^2"
      WRITE(17,899) "# NMSSM SPECIFIC PARAMETERS THE QSTSB SCALE"
      WRITE(17,907) "BLOCK NMSSMRUNATQSTSB Q=",DSQRT(QSTSB)
      WRITE(17,901) 1,LQ,"LAMBDA(Q,DR_bar)"
      WRITE(17,901) 2,KQ,"KAPPA(Q,DR_bar)"
      WRITE(17,901) 3,ALQ,"ALAMBDA"
      WRITE(17,901) 4,AKQ,"AKAPPA"
      WRITE(17,901) 5,MUQ,"MUEFF"
     

      WRITE(17,899) "# "
      WRITE(17,899) "# GAUGE AND YUKAWA COUPLINGS AT THE GUT SCALE"
      WRITE(17,907) "BLOCK GAUGE Q=",MGUT," # (GUT SCALE)"
      WRITE(17,901) 1,DSQRT(5d0/3d0*G1GUT),
     .        "g1(MGUT,DR_bar), GUT normalization"
      WRITE(17,901) 2,DSQRT(G2GUT),"g2(MGUT,DR_bar)"
      WRITE(17,901) 3,DSQRT(G3GUT),"g3(MGUT,DR_bar)"
      WRITE(17,907) "BLOCK YU Q=",MGUT," # (GUT SCALE)"
      WRITE(17,903) 3,3,HTOPGUT/DSQRT(DABS(HTOPGUT)),
     .            "HTOP(MGUT,DR_bar)"
      WRITE(17,907) "BLOCK YD Q=",MGUT," # (GUT SCALE)"
      WRITE(17,903) 3,3,HBOTGUT/DSQRT(DABS(HBOTGUT)),
     .            "HBOT(MGUT,DR_bar)"
      WRITE(17,907) "BLOCK YE Q=",MGUT," # (GUT SCALE)"
      WRITE(17,903) 3,3,HTAUGUT/DSQRT(DABS(HTAUGUT)),
     .        "HTAU(MGUT,DR_bar)"

      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT TRILINEAR COUPLINGS AT THE GUT SCALE"       
      WRITE(17,907) "BLOCK AU Q=",MGUT," # (GUT SCALE)"
      WRITE(17,903) 3,3,ATGUT,"ATOP"
      WRITE(17,907) "BLOCK AD Q=",MGUT," # (GUT SCALE)"
      WRITE(17,903) 3,3,ABGUT,"ABOT"
      WRITE(17,907) "BLOCK AE Q=",MGUT," # (GUT SCALE)"
      WRITE(17,903) 2,2,AMUGUT,"AMUON"
      WRITE(17,903) 3,3,ATAUGUT,"ATAU"

      WRITE(17,899) "# "
      WRITE(17,899) "# SOFT MASSES SQUARED AT THE GUT SCALE"
      WRITE(17,907) "BLOCK MSOFT Q=",MGUT," # (GUT SCALE)"
      WRITE(17,901) 1,M1GUT,"M1"
      WRITE(17,901) 2,M2GUT,"M2"
      WRITE(17,901) 3,M3GUT,"M3"
      WRITE(17,901) 21,MHDGUT,"M_HD^2"
      WRITE(17,901) 22,MHUGUT,"M_HU^2"
      WRITE(17,901) 31,MLGUT/DSQRT(DABS(MLGUT)),"M_eL"
      WRITE(17,901) 32,MLGUT/DSQRT(DABS(MLGUT)),"M_muL"
      WRITE(17,901) 33,ML3GUT/DSQRT(DABS(ML3GUT)),"M_tauL"
      WRITE(17,901) 34,MEGUT/DSQRT(DABS(MEGUT)),"M_eR"
      WRITE(17,901) 35,MEGUT/DSQRT(DABS(MEGUT)),"M_muR"
      WRITE(17,901) 36,ME3GUT/DSQRT(DABS(ME3GUT)),"M_tauR"
      WRITE(17,901) 41,MQGUT/DSQRT(DABS(MQGUT)),"M_q1L"
      WRITE(17,901) 42,MQGUT/DSQRT(DABS(MQGUT)),"M_q2L"
      WRITE(17,901) 43,MQ3GUT/DSQRT(DABS(MQ3GUT)),"M_q3L"
      WRITE(17,901) 44,MUGUT/DSQRT(DABS(MUGUT)),"M_uR"
      WRITE(17,901) 45,MUGUT/DSQRT(DABS(MUGUT)),"M_cR"
      WRITE(17,901) 46,MU3GUT/DSQRT(DABS(MU3GUT)),"M_tR"
      WRITE(17,901) 47,MDGUT/DSQRT(DABS(MDGUT)),"M_dR"
      WRITE(17,901) 48,MDGUT/DSQRT(DABS(MDGUT)),"M_sR"
      WRITE(17,901) 49,MD3GUT/DSQRT(DABS(MD3GUT)),"M_bR"

      WRITE(17,899) "# "
      WRITE(17,899) "# NMSSM SPECIFIC PARAMETERS AT THE GUT SCALE"
      WRITE(17,907) "BLOCK NMSSMRUN Q=",MGUT," # (GUT SCALE)"
      WRITE(17,901) 1,LGUT/DSQRT(DABS(LGUT)),"LAMBDA(MGUT,DR_bar)"
      WRITE(17,901) 2,KGUT,"KAPPA(MGUT,DR_bar)"
      WRITE(17,901) 3,ALGUT,"ALAMBDA"
      WRITE(17,901) 4,AKGUT,"AKAPPA"
      WRITE(17,901) 6,XIFGUT,"XIF"
      WRITE(17,901) 7,XISGUT,"XIS"
      WRITE(17,901) 8,MUPGUT,"MU'"
      WRITE(17,901) 9,MSPGUT,"MS'^2"
      WRITE(17,901) 10,MSGUT,"MS^2"
      WRITE(17,901) 12,M3HGUT,"M3H^2"

      WRITE(17,899) "# "
      WRITE(17,899) "# FINE-TUNING parameter d(ln Mz^2)/d(ln PG^2)"
      WRITE(17,899) "# BLOCK FINETUNING"
      WRITE(17,901) 1,FTGUT(1),"PG=MHU"
      WRITE(17,901) 2,FTGUT(2),"PG=MHD"
      WRITE(17,901) 3,FTGUT(3),"PG=MS"
      WRITE(17,901) 4,FTGUT(4),"PG=M0"
      WRITE(17,901) 5,FTGUT(5),"PG=M1"
      WRITE(17,901) 6,FTGUT(6),"PG=M2"
      WRITE(17,901) 7,FTGUT(7),"PG=M3"
      WRITE(17,901) 8,FTGUT(8),"PG=M12"
      WRITE(17,901) 9,FTGUT(9),"PG=ALAMBDA"
      WRITE(17,901) 10,FTGUT(10),"PG=AKAPPA"
      WRITE(17,901) 11,FTGUT(11),"PG=A0"
      WRITE(17,901) 12,FTGUT(12),"PG=XIF"
      WRITE(17,901) 13,FTGUT(13),"PG=XIS"
      WRITE(17,901) 14,FTGUT(14),"PG=MUP"
      WRITE(17,901) 15,FTGUT(15),"PG=MSP"
      WRITE(17,901) 16,FTGUT(16),"PG=M3H"
      WRITE(17,901) 17,FTGUT(17),"PG=LAMBDA"
      WRITE(17,901) 18,FTGUT(18),"PG=KAPPA"
      WRITE(17,901) 19,FTGUT(19),"PG=HTOP"
      WRITE(17,901) 20,FTGUT(20),"PG=G0"
      WRITE(17,901) 21,FTGUT(21),"PG=MGUT"
      WRITE(17,901) 22,FTGUT(22),"MAX"
      WRITE(17,914) 23,INT(FTGUT(23)),"IMAX"

      WRITE(17,899) "# "
      WRITE(17,899) "# REDUCED CROSS SECTIONS AT LHC"
      WRITE(17,899) "BLOCK LHCCROSSSECTIONS"
      WRITE(17,901) 11,SIG(1,1),"VBF/VH -> H1 -> tautau"
      WRITE(17,901) 12,SIG(1,2),"ggF -> H1 -> tautau"
      WRITE(17,901) 13,SIG(1,3),"VBF/VH -> H1 -> bb"
      WRITE(17,901) 14,SIG(1,4),"ttH -> H1 -> bb"
      WRITE(17,901) 15,SIG(1,5),"VBF/VH -> H1 -> ZZ/WW"
      WRITE(17,901) 16,SIG(1,6),"ggF -> H1 -> ZZ/WW"
      WRITE(17,901) 17,SIG(1,7),"VBF/VH -> H1 -> gammagamma"
      WRITE(17,901) 18,SIG(1,8),"ggF -> H1 -> gammagamma"
      WRITE(17,901) 21,SIG(2,1),"VBF/VH -> H2 -> tautau"
      WRITE(17,901) 22,SIG(2,2),"ggF -> H2 -> tautau"
      WRITE(17,901) 23,SIG(2,3),"VBF/VH -> H2 -> bb"
      WRITE(17,901) 24,SIG(2,4),"ttH -> H2 -> bb"
      WRITE(17,901) 25,SIG(2,5),"VBF/VH -> H2 -> ZZ/WW"
      WRITE(17,901) 26,SIG(2,6),"ggF -> H2 -> ZZ/WW"
      WRITE(17,901) 27,SIG(2,7),"VBF/VH -> H2 -> gammagamma"
      WRITE(17,901) 28,SIG(2,8),"ggF -> H2 -> gammagamma"
      WRITE(17,901) 31,SIG(3,1),"VBF/VH -> H3 -> tautau"
      WRITE(17,901) 32,SIG(3,2),"ggF -> H3 -> tautau"
      WRITE(17,901) 33,SIG(3,3),"VBF/VH -> H3 -> bb"
      WRITE(17,901) 34,SIG(3,4),"ttH -> H3 -> bb"
      WRITE(17,901) 35,SIG(3,5),"VBF/VH -> H3 -> ZZ/WW"
      WRITE(17,901) 36,SIG(3,6),"ggF -> H3 -> ZZ/WW"
      WRITE(17,901) 37,SIG(3,7),"VBF/VH -> H3 -> gammagamma"
      WRITE(17,901) 38,SIG(3,8),"ggF -> H3 -> gammagamma"

      WRITE(17,899) "# "
      WRITE(17,899) "# CHI^2 FOR HIGGS COUPLINGS"
      WRITE(17,899) "BLOCK LHCFIT"
      WRITE(17,901) 1,chi2gam,"Hgammagamma"
      WRITE(17,901) 2,chi2bb,"Hff"
      WRITE(17,901) 3,chi2zz,"HVV"

      WRITE(17,899) "# "
      WRITE(17,899)
     . "# PARAMETERS OF THE EFFECTIVE LAGRANGIAN IN THE HIGGS SECTOR"
      WRITE(17,899) "BLOCK  EFFECTIVE_COUPLINGS"
      WRITE(17,917)," X",PX
      DO I=1,6
      WRITE(17,916)," A",I,PA(I)
      ENDDO
      DO I=1,2
       WRITE(17,916)," B",I,PB(I)
      ENDDO
      DO I=1,7
       WRITE(17,916)," L",I,PL(I)
      ENDDO
      DO I=1,8
       WRITE(17,916)," K",I,PK(I)
      ENDDO
      WRITE(17,917)," DELMB",DELMB
      WRITE(17,917)," XVEV", MUQ/LQ*DSQRT(ZS)

 1    WRITE(18,899) "# HIGGS + TOP BRANCHING RATIOS IN SLHA FORMAT"
      WRITE(18,899) "# Info about decay package"
      WRITE(18,899) "BLOCK DCINFO   # Program information"
      WRITE(18,900) 1,"NMSSMTools # Decay package"
      WRITE(18,900) 2,"4.1.1      # Version number"

      IF(IFAIL.NE.0.AND.IFAIL.NE.10) GOTO 2

      WRITE(18,899) "#           PDG          Width"
      WRITE(18,904) 25,WIDTH(1),"Lightest neutral Higgs scalar"
      IF(BRJJ(1).GT.0d0)
     .  WRITE(18,905) BRJJ(1),2,21,21,"BR(H_1 -> gluon gluon)"
      IF(BRMM(1).GT.0d0)
     .  WRITE(18,905) BRMM(1),2,13,-13,"BR(H_1 -> muon muon)"
      IF(BRLL(1).GT.0d0)
     .  WRITE(18,905) BRLL(1),2,15,-15,"BR(H_1 -> tau tau)"
      IF(BRSS(1).GT.0d0)
     .  WRITE(18,905) BRSS(1),2,3,-3,"BR(H_1 -> s sbar)"
      IF(BRCC(1).GT.0d0)
     .  WRITE(18,905) BRCC(1),2,4,-4,"BR(H_1 -> c cbar)"
      IF(BRBB(1).GT.0d0)
     .  WRITE(18,905) BRBB(1),2,5,-5,"BR(H_1 -> b bbar)"
      IF(BRTT(1).GT.0d0)
     .  WRITE(18,905) BRTT(1),2,6,-6,"BR(H_1 -> t tbar)"
      IF(BRWW(1).GT.0d0)
     .  WRITE(18,905) BRWW(1),2,24,-24,"BR(H_1 -> W+ W-)"
      IF(BRZZ(1).GT.0d0)
     .  WRITE(18,905) BRZZ(1),2,23,23,"BR(H_1 -> Z Z)"
      IF(BRGG(1).GT.0d0)
     .  WRITE(18,905) BRGG(1),2,22,22,"BR(H_1 -> gamma gamma)"
      IF(BRZG(1).GT.0d0)
     .  WRITE(18,905) BRZG(1),2,23,22,"BR(H_1 -> Z gamma)"
      IF(BRHAA(1,1).GT.0d0)
     .  WRITE(18,905) BRHAA(1,1),2,36,36,"BR(H_1 -> A_1 A_1)"
      IF(BRHAA(1,2).GT.0d0)
     .  WRITE(18,905) BRHAA(1,2),2,36,46,"BR(H_1 -> A_1 A_2)"
      IF(BRHAA(1,3).GT.0d0)
     .  WRITE(18,905) BRHAA(1,3),2,46,46,"BR(H_1 -> A_2 A_2)"
      IF(BRHAZ(1,1).GT.0d0)
     .  WRITE(18,905) BRHAZ(1,1),2,23,36,"BR(H_1 -> A_1 Z)"
      IF(BRNEU(1,1,1).GT.0d0)
     .  WRITE(18,905) BRNEU(1,1,1),2,1000022,1000022,
     .    "BR(H_1 -> neu_1 neu_1)"
      IF(BRNEU(1,1,2).GT.0d0)
     .  WRITE(18,905) BRNEU(1,1,2),2,1000022,1000023,
     .    "BR(H_1 -> neu_1 neu_2)"
      IF(BRNEU(1,1,3).GT.0d0)
     .  WRITE(18,905) BRNEU(1,1,3),2,1000022,1000025,
     .    "BR(H_1 -> neu_1 neu_3)"
      IF(BRNEU(1,1,4).GT.0d0)
     .  WRITE(18,905) BRNEU(1,1,4),2,1000022,1000035,
     .    "BR(H_1 -> neu_1 neu_4)"
      IF(BRNEU(1,1,5).GT.0d0)
     .  WRITE(18,905) BRNEU(1,1,5),2,1000022,1000045,
     .    "BR(H_1 -> neu_1 neu_5)"
      IF(BRNEU(1,2,2).GT.0d0)
     .  WRITE(18,905) BRNEU(1,2,2),2,1000023,1000023,
     .    "BR(H_1 -> neu_2 neu_2)"
      IF(BRNEU(1,2,3).GT.0d0)
     .  WRITE(18,905) BRNEU(1,2,3),2,1000023,1000025,
     .    "BR(H_1 -> neu_2 neu_3)"
      IF(BRNEU(1,2,4).GT.0d0)
     .  WRITE(18,905) BRNEU(1,2,4),2,1000023,1000035,
     .    "BR(H_1 -> neu_2 neu_4)"
      IF(BRNEU(1,2,5).GT.0d0)
     .  WRITE(18,905) BRNEU(1,2,5),2,1000023,1000045,
     .    "BR(H_1 -> neu_2 neu_5)"
      IF(BRNEU(1,3,3).GT.0d0)
     .  WRITE(18,905) BRNEU(1,3,3),2,1000025,1000025,
     .    "BR(H_1 -> neu_3 neu_3)"
      IF(BRNEU(1,3,4).GT.0d0)
     .  WRITE(18,905) BRNEU(1,3,4),2,1000025,1000035,
     .    "BR(H_1 -> neu_3 neu_4)"
      IF(BRNEU(1,3,5).GT.0d0)
     .  WRITE(18,905) BRNEU(1,3,5),2,1000025,1000045,
     .    "BR(H_1 -> neu_3 neu_5)"
      IF(BRNEU(1,4,4).GT.0d0)
     .  WRITE(18,905) BRNEU(1,4,4),2,1000035,1000035,
     .    "BR(H_1 -> neu_4 neu_4)"
      IF(BRNEU(1,4,5).GT.0d0)
     .  WRITE(18,905) BRNEU(1,4,5),2,1000035,1000045,
     .    "BR(H_1 -> neu_4 neu_5)"
      IF(BRNEU(1,5,5).GT.0d0)
     .  WRITE(18,905) BRNEU(1,5,5),2,1000045,1000045,
     .    "BR(H_1 -> neu_5 neu_5)"
      IF(BRCHA(1,1).GT.0d0)
     .  WRITE(18,905) BRCHA(1,1),2,1000024,-1000024,
     .    "BR(H_1 -> cha_1 cha_1bar)"
      IF(BRCHA(1,2).GT.0d0)
     .  WRITE(18,905) BRCHA(1,2),2,1000024,-1000037,
     .    "BR(H_1 -> cha_1 cha_2bar)"
      IF(BRCHA(1,2).GT.0d0)
     .  WRITE(18,905) BRCHA(1,2),2,1000037,-1000024,
     .    "BR(H_1 -> cha_2 cha_1bar)"
      IF(BRCHA(1,3).GT.0d0)
     .  WRITE(18,905) BRCHA(1,3),2,1000037,-1000037,
     .    "BR(H_1 -> cha_2 cha_2bar)"
      IF(BRHSQ(1,1).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,1),2,1000002,-1000002,
     .    "BR(H_1 -> ~u_L ~ubar_L)"
      IF(BRHSQ(1,1).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,1),2,1000004,-1000004,
     .    "BR(H_1 -> ~c_L ~cbar_L)"
      IF(BRHSQ(1,2).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,2),2,2000002,-2000002,
     .    "BR(H_1 -> ~u_R ~ubar_R)"
      IF(BRHSQ(1,2).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,2),2,2000004,-2000004,
     .    "BR(H_1 -> ~c_R ~cbar_R)"
      IF(BRHSQ(1,3).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,3),2,1000001,-1000001,
     .    "BR(H_1 -> ~d_L ~dbar_L)"
      IF(BRHSQ(1,3).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,3),2,1000003,-1000003,
     .    "BR(H_1 -> ~s_L ~sbar_L)"
      IF(BRHSQ(1,4).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,4),2,2000001,-2000001,
     .    "BR(H_1 -> ~d_R ~dbar_R)"
      IF(BRHSQ(1,4).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,4),2,2000003,-2000003,
     .    "BR(H_1 -> ~s_R ~sbar_R)"
      IF(BRHSQ(1,5).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,5),2,1000006,-1000006,
     .    "BR(H_1 -> ~t_1 ~tbar_1)"
      IF(BRHSQ(1,6).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,6),2,2000006,-2000006,
     .    "BR(H_1 -> ~t_2 ~tbar_2)"
      IF(BRHSQ(1,7).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,7),2,1000006,-2000006,
     .    "BR(H_1 -> ~t_1 ~tbar_2)"
      IF(BRHSQ(1,7).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,7),2,2000006,-1000006,
     .    "BR(H_1 -> ~t_2 ~tbar_1)"
      IF(BRHSQ(1,8).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,8),2,1000005,-1000005,
     .    "BR(H_1 -> ~b_1 ~bbar_1)"
      IF(BRHSQ(1,9).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,9),2,2000005,-2000005,
     .    "BR(H_1 -> ~b_2 ~bbar_2)"
      IF(BRHSQ(1,10).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,10),2,1000005,-2000005,
     .    "BR(H_1 -> ~b_1 ~bbar_2)"
      IF(BRHSQ(1,10).GT.0d0)
     .  WRITE(18,905) BRHSQ(1,10),2,2000005,-1000005,
     .    "BR(H_1 -> ~b_2 ~bbar_1)"
      IF(BRHSL(1,1).GT.0d0)
     .  WRITE(18,905) BRHSL(1,1),2,1000011,-1000011,
     .    "BR(H_1 -> ~e_L ~ebar_L)"
      IF(BRHSL(1,1).GT.0d0)
     .  WRITE(18,905) BRHSL(1,1),2,1000013,-1000013,
     .    "BR(H_1 -> ~mu_L ~mubar_L)"
      IF(BRHSL(1,2).GT.0d0)
     .  WRITE(18,905) BRHSL(1,2),2,2000011,-2000011,
     .    "BR(H_1 -> ~e_R ~ebar_R)"
      IF(BRHSL(1,2).GT.0d0)
     .  WRITE(18,905) BRHSL(1,2),2,2000013,-2000013,
     .    "BR(H_1 -> ~mu_R ~mubarRL)"
      IF(BRHSL(1,3).GT.0d0)
     .  WRITE(18,905) BRHSL(1,3),2,1000012,-1000012,
     .    "BR(H_1 -> ~nu_e_L ~nu_ebar_L)"
      IF(BRHSL(1,3).GT.0d0)
     .  WRITE(18,905) BRHSL(1,3),2,1000014,-1000014,
     .    "BR(H_1 -> ~nu_mu_L ~nu_mubar_L)"
      IF(BRHSL(1,4).GT.0d0)
     .  WRITE(18,905) BRHSL(1,4),2,1000015,-1000015,
     .    "BR(H_1 -> ~tau_1 ~taubar_1)"
      IF(BRHSL(1,5).GT.0d0)
     .  WRITE(18,905) BRHSL(1,5),2,2000015,-2000015,
     .    "BR(H_1 -> ~tau_2 ~taubar_2)"
      IF(BRHSL(1,6).GT.0d0)
     .  WRITE(18,905) BRHSL(1,6),2,1000015,-2000015,
     .    "BR(H_1 -> ~tau_1 ~taubar_2)"
      IF(BRHSL(1,6).GT.0d0)
     .  WRITE(18,905) BRHSL(1,6),2,2000015,-1000015,
     .    "BR(H_1 -> ~tau_2 ~taubar_1)"
      IF(BRHSL(1,7).GT.0d0)
     .  WRITE(18,905) BRHSL(1,7),2,1000016,-1000016,
     .    "BR(H_1 -> ~nu_tau_L ~nu_taubar_L)"
      
      WRITE(18,904) 35,WIDTH(2),"2nd neutral Higgs scalar"
      IF(BRJJ(2).GT.0d0)
     .  WRITE(18,905) BRJJ(2),2,21,21,"BR(H_2 -> gluon gluon)"
      IF(BRMM(2).GT.0d0)
     .  WRITE(18,905) BRMM(2),2,13,-13,"BR(H_2 -> muon muon)"
      IF(BRLL(2).GT.0d0)
     .  WRITE(18,905) BRLL(2),2,15,-15,"BR(H_2 -> tau tau)"
      IF(BRSS(2).GT.0d0)
     .  WRITE(18,905) BRSS(2),2,3,-3,"BR(H_2 -> s sbar)"
      IF(BRCC(2).GT.0d0)
     .  WRITE(18,905) BRCC(2),2,4,-4,"BR(H_2 -> c cbar)"
      IF(BRBB(2).GT.0d0)
     .  WRITE(18,905) BRBB(2),2,5,-5,"BR(H_2 -> b bbar)"
      IF(BRTT(2).GT.0d0)
     .  WRITE(18,905) BRTT(2),2,6,-6,"BR(H_2 -> t tbar)"
      IF(BRWW(2).GT.0d0)
     .  WRITE(18,905) BRWW(2),2,24,-24,"BR(H_2 -> W+ W-)"
      IF(BRZZ(2).GT.0d0)
     .  WRITE(18,905) BRZZ(2),2,23,23,"BR(H_2 -> Z Z)"
      IF(BRGG(2).GT.0d0)
     .  WRITE(18,905) BRGG(2),2,22,22,"BR(H_2 -> gamma gamma)"
      IF(BRZG(2).GT.0d0)
     .  WRITE(18,905) BRZG(2),2,23,22,"BR(H_2 -> Z gamma)"
      IF(BRHHH(1).GT.0d0)
     .  WRITE(18,905) BRHHH(1),2,25,25,"BR(H_2 -> H_1 H_1)"
      IF(BRHAA(2,1).GT.0d0)
     .  WRITE(18,905) BRHAA(2,1),2,36,36,"BR(H_2 -> A_1 A_1)"
      IF(BRHAA(2,2).GT.0d0)
     .  WRITE(18,905) BRHAA(2,2),2,36,46,"BR(H_2 -> A_1 A_2)"
      IF(BRHAA(2,3).GT.0d0)
     .  WRITE(18,905) BRHAA(2,3),2,46,46,"BR(H_2 -> A_2 A_2)"
      IF(BRHAZ(2,1).GT.0d0)
     .  WRITE(18,905) BRHAZ(2,1),2,23,36,"BR(H_2 -> A_1 Z)"
      IF(BRNEU(2,1,1).GT.0d0)
     .  WRITE(18,905) BRNEU(2,1,1),2,1000022,1000022,
     .    "BR(H_2 -> neu_1 neu_1)"
      IF(BRNEU(2,1,2).GT.0d0)
     .  WRITE(18,905) BRNEU(2,1,2),2,1000022,1000023,
     .    "BR(H_2 -> neu_1 neu_2)"
      IF(BRNEU(2,1,3).GT.0d0)
     .  WRITE(18,905) BRNEU(2,1,3),2,1000022,1000025,
     .    "BR(H_2 -> neu_1 neu_3)"
      IF(BRNEU(2,1,4).GT.0d0)
     .  WRITE(18,905) BRNEU(2,1,4),2,1000022,1000035,
     .    "BR(H_2 -> neu_1 neu_4)"
      IF(BRNEU(2,1,5).GT.0d0)
     .  WRITE(18,905) BRNEU(2,1,5),2,1000022,1000045,
     .    "BR(H_2 -> neu_1 neu_5)"
      IF(BRNEU(2,2,2).GT.0d0)
     .  WRITE(18,905) BRNEU(2,2,2),2,1000023,1000023,
     .    "BR(H_2 -> neu_2 neu_2)"
      IF(BRNEU(2,2,3).GT.0d0)
     .  WRITE(18,905) BRNEU(2,2,3),2,1000023,1000025,
     .    "BR(H_2 -> neu_2 neu_3)"
      IF(BRNEU(2,2,4).GT.0d0)
     .  WRITE(18,905) BRNEU(2,2,4),2,1000023,1000035,
     .    "BR(H_2 -> neu_2 neu_4)"
      IF(BRNEU(2,2,5).GT.0d0)
     .  WRITE(18,905) BRNEU(2,2,5),2,1000023,1000045,
     .    "BR(H_2 -> neu_2 neu_5)"
      IF(BRNEU(2,3,3).GT.0d0)
     .  WRITE(18,905) BRNEU(2,3,3),2,1000025,1000025,
     .    "BR(H_2 -> neu_3 neu_3)"
      IF(BRNEU(2,3,4).GT.0d0)
     .  WRITE(18,905) BRNEU(2,3,4),2,1000025,1000035,
     .    "BR(H_2 -> neu_3 neu_4)"
      IF(BRNEU(2,3,5).GT.0d0)
     .  WRITE(18,905) BRNEU(2,3,5),2,1000025,1000045,
     .    "BR(H_2 -> neu_3 neu_5)"
      IF(BRNEU(2,4,4).GT.0d0)
     .  WRITE(18,905) BRNEU(2,4,4),2,1000035,1000035,
     .    "BR(H_2 -> neu_4 neu_4)"
      IF(BRNEU(2,4,5).GT.0d0)
     .  WRITE(18,905) BRNEU(2,4,5),2,1000035,1000045,
     .    "BR(H_2 -> neu_4 neu_5)"
      IF(BRNEU(2,5,5).GT.0d0)
     .  WRITE(18,905) BRNEU(2,5,5),2,1000045,1000045,
     .    "BR(H_2 -> neu_5 neu_5)"
      IF(BRCHA(2,1).GT.0d0)
     .  WRITE(18,905) BRCHA(2,1),2,1000024,-1000024,
     .    "BR(H_2 -> cha_1 cha_1bar)"
      IF(BRCHA(2,2).GT.0d0)
     .  WRITE(18,905) BRCHA(2,2),2,1000024,-1000037,
     .    "BR(H_2 -> cha_1 cha_2bar)"
      IF(BRCHA(2,2).GT.0d0)
     .  WRITE(18,905) BRCHA(2,2),2,1000037,-1000024,
     .    "BR(H_2 -> cha_2 cha_1bar)"
      IF(BRCHA(2,3).GT.0d0)
     .  WRITE(18,905) BRCHA(2,3),2,1000037,-1000037,
     .    "BR(H_2 -> cha_2 cha_2bar)"
      IF(BRHSQ(2,1).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,1),2,1000002,-1000002,
     .    "BR(H_2 -> ~u_L ~ubar_L)"
      IF(BRHSQ(2,1).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,1),2,1000004,-1000004,
     .    "BR(H_2 -> ~c_L ~cbar_L)"
      IF(BRHSQ(2,2).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,2),2,2000002,-2000002,
     .    "BR(H_2 -> ~u_R ~ubar_R)"
      IF(BRHSQ(2,2).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,2),2,2000004,-2000004,
     .    "BR(H_2 -> ~c_R ~cbar_R)"
      IF(BRHSQ(2,3).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,3),2,1000001,-1000001,
     .    "BR(H_2 -> ~d_L ~dbar_L)"
      IF(BRHSQ(2,3).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,3),2,1000003,-1000003,
     .    "BR(H_2 -> ~s_L ~sbar_L)"
      IF(BRHSQ(2,4).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,4),2,2000001,-2000001,
     .    "BR(H_2 -> ~d_R ~dbar_R)"
      IF(BRHSQ(2,4).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,4),2,2000003,-2000003,
     .    "BR(H_2 -> ~s_R ~sbar_R)"
      IF(BRHSQ(2,5).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,5),2,1000006,-1000006,
     .    "BR(H_2 -> ~t_1 ~tbar_1)"
      IF(BRHSQ(2,6).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,6),2,2000006,-2000006,
     .    "BR(H_2 -> ~t_2 ~tbar_2)"
      IF(BRHSQ(2,7).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,7),2,1000006,-2000006,
     .    "BR(H_2 -> ~t_1 ~tbar_2)"
      IF(BRHSQ(2,7).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,7),2,2000006,-1000006,
     .    "BR(H_2 -> ~t_2 ~tbar_1)"
      IF(BRHSQ(2,8).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,8),2,1000005,-1000005,
     .    "BR(H_2 -> ~b_1 ~bbar_1)"
      IF(BRHSQ(2,9).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,9),2,2000005,-2000005,
     .    "BR(H_2 -> ~b_2 ~bbar_2)"
      IF(BRHSQ(2,10).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,10),2,1000005,-2000005,
     .    "BR(H_2 -> ~b_1 ~bbar_2)"
      IF(BRHSQ(2,10).GT.0d0)
     .  WRITE(18,905) BRHSQ(2,10),2,2000005,-1000005,
     .    "BR(H_2 -> ~b_2 ~bbar_1)"
      IF(BRHSL(2,1).GT.0d0)
     .  WRITE(18,905) BRHSL(2,1),2,1000011,-1000011,
     .    "BR(H_2 -> ~e_L ~ebar_L)"
      IF(BRHSL(2,1).GT.0d0)
     .  WRITE(18,905) BRHSL(2,1),2,1000013,-1000013,
     .    "BR(H_2 -> ~mu_L ~mubar_L)"
      IF(BRHSL(2,2).GT.0d0)
     .  WRITE(18,905) BRHSL(2,2),2,2000011,-2000011,
     .    "BR(H_2 -> ~e_R ~ebar_R)"
      IF(BRHSL(2,2).GT.0d0)
     .  WRITE(18,905) BRHSL(2,2),2,2000013,-2000013,
     .    "BR(H_2 -> ~mu_R ~mubarRL)"
      IF(BRHSL(2,3).GT.0d0)
     .  WRITE(18,905) BRHSL(2,3),2,1000012,-1000012,
     .    "BR(H_2 -> ~nu_e_L ~nu_ebar_L)"
      IF(BRHSL(2,3).GT.0d0)
     .  WRITE(18,905) BRHSL(2,3),2,1000014,-1000014,
     .    "BR(H_2 -> ~nu_mu_L ~nu_mubar_L)"
      IF(BRHSL(2,4).GT.0d0)
     .  WRITE(18,905) BRHSL(2,4),2,1000015,-1000015,
     .    "BR(H_2 -> ~tau_1 ~taubar_1)"
      IF(BRHSL(2,5).GT.0d0)
     .  WRITE(18,905) BRHSL(2,5),2,2000015,-2000015,
     .    "BR(H_2 -> ~tau_2 ~taubar_2)"
      IF(BRHSL(2,6).GT.0d0)
     .  WRITE(18,905) BRHSL(2,6),2,1000015,-2000015,
     .    "BR(H_2 -> ~tau_1 ~taubar_2)"
      IF(BRHSL(2,6).GT.0d0)
     .  WRITE(18,905) BRHSL(2,6),2,2000015,-1000015,
     .    "BR(H_2 -> ~tau_2 ~taubar_1)"
      IF(BRHSL(2,7).GT.0d0)
     .  WRITE(18,905) BRHSL(2,7),2,1000016,-1000016,
     .    "BR(H_2 -> ~nu_tau_L ~nu_taubar_L)"

      WRITE(18,904) 45,WIDTH(3),"3rd neutral Higgs scalar"
      IF(BRJJ(3).GT.0d0)
     .  WRITE(18,905) BRJJ(3),2,21,21,"BR(H_3 -> gluon gluon)"
      IF(BRMM(3).GT.0d0)
     .  WRITE(18,905) BRMM(3),2,13,-13,"BR(H_3 -> muon muon)"
      IF(BRLL(3).GT.0d0)
     .  WRITE(18,905) BRLL(3),2,15,-15,"BR(H_3 -> tau tau)"
      IF(BRSS(3).GT.0d0)
     .  WRITE(18,905) BRSS(3),2,3,-3,"BR(H_3 -> s sbar)"
      IF(BRCC(3).GT.0d0)
     .  WRITE(18,905) BRCC(3),2,4,-4,"BR(H_3 -> c cbar)"
      IF(BRBB(3).GT.0d0)
     .  WRITE(18,905) BRBB(3),2,5,-5,"BR(H_3 -> b bbar)"
      IF(BRTT(3).GT.0d0)
     .  WRITE(18,905) BRTT(3),2,6,-6,"BR(H_3 -> t tbar)"
      IF(BRWW(3).GT.0d0)
     .  WRITE(18,905) BRWW(3),2,24,-24,"BR(H_3 -> W+ W-)"
      IF(BRZZ(3).GT.0d0)
     .  WRITE(18,905) BRZZ(3),2,23,23,"BR(H_3 -> Z Z)"
      IF(BRGG(3).GT.0d0)
     .  WRITE(18,905) BRGG(3),2,22,22,"BR(H_3 -> gamma gamma)"
      IF(BRZG(3).GT.0d0)
     .  WRITE(18,905) BRZG(3),2,23,22,"BR(H_3 -> Z gamma)"
      IF(BRHHH(2).GT.0d0)
     .  WRITE(18,905) BRHHH(2),2,25,25,"BR(H_3 -> H_1 H_1)"
      IF(BRHHH(3).GT.0d0)
     .  WRITE(18,905) BRHHH(3),2,25,35,"BR(H_3 -> H_1 H_2)"
      IF(BRHHH(4).GT.0d0)
     .  WRITE(18,905) BRHHH(4),2,35,35,"BR(H_3 -> H_2 H_2)"
      IF(BRHAA(3,1).GT.0d0)
     .  WRITE(18,905) BRHAA(3,1),2,36,36,"BR(H_3 -> A_1 A_1)"
      IF(BRHAA(3,2).GT.0d0)
     .  WRITE(18,905) BRHAA(3,2),2,36,46,"BR(H_3 -> A_1 A_2)"
      IF(BRHAA(3,3).GT.0d0)
     .  WRITE(18,905) BRHAA(3,3),2,46,46,"BR(H_3 -> A_2 A_2)"
      IF(BRHAZ(3,1).GT.0d0)
     .  WRITE(18,905) BRHAZ(3,1),2,23,36,"BR(H_3 -> A_1 Z)"
      IF(BRHAZ(3,2).GT.0d0)
     .  WRITE(18,905) BRHAZ(3,2),2,23,46,"BR(H_3 -> A_2 Z)"
      IF(BRHCHC(3).GT.0d0)
     .  WRITE(18,905) BRHCHC(3),2,37,-37,"BR(H_3 -> H+ H-)"
      IF(BRHCW(3).GT.0d0)
     .  WRITE(18,905) BRHCW(3),2,24,-37,"BR(H_3 -> W+ H-)"
      IF(BRNEU(3,1,1).GT.0d0)
     .  WRITE(18,905) BRNEU(3,1,1),2,1000022,1000022,
     .    "BR(H_3 -> neu_1 neu_1)"
      IF(BRNEU(3,1,2).GT.0d0)
     .  WRITE(18,905) BRNEU(3,1,2),2,1000022,1000023,
     .    "BR(H_3 -> neu_1 neu_2)"
      IF(BRNEU(3,1,3).GT.0d0)
     .  WRITE(18,905) BRNEU(3,1,3),2,1000022,1000025,
     .    "BR(H_3 -> neu_1 neu_3)"
      IF(BRNEU(3,1,4).GT.0d0)
     .  WRITE(18,905) BRNEU(3,1,4),2,1000022,1000035,
     .    "BR(H_3 -> neu_1 neu_4)"
      IF(BRNEU(3,1,5).GT.0d0)
     .  WRITE(18,905) BRNEU(3,1,5),2,1000022,1000045,
     .    "BR(H_3 -> neu_1 neu_5)"
      IF(BRNEU(3,2,2).GT.0d0)
     .  WRITE(18,905) BRNEU(3,2,2),2,1000023,1000023,
     .    "BR(H_3 -> neu_2 neu_2)"
      IF(BRNEU(3,2,3).GT.0d0)
     .  WRITE(18,905) BRNEU(3,2,3),2,1000023,1000025,
     .    "BR(H_3 -> neu_2 neu_3)"
      IF(BRNEU(3,2,4).GT.0d0)
     .  WRITE(18,905) BRNEU(3,2,4),2,1000023,1000035,
     .    "BR(H_3 -> neu_2 neu_4)"
      IF(BRNEU(3,2,5).GT.0d0)
     .  WRITE(18,905) BRNEU(3,2,5),2,1000023,1000045,
     .    "BR(H_3 -> neu_2 neu_5)"
      IF(BRNEU(3,3,3).GT.0d0)
     .  WRITE(18,905) BRNEU(3,3,3),2,1000025,1000025,
     .    "BR(H_3 -> neu_3 neu_3)"
      IF(BRNEU(3,3,4).GT.0d0)
     .  WRITE(18,905) BRNEU(3,3,4),2,1000025,1000035,
     .    "BR(H_3 -> neu_3 neu_4)"
      IF(BRNEU(3,3,5).GT.0d0)
     .  WRITE(18,905) BRNEU(3,3,5),2,1000025,1000045,
     .    "BR(H_3 -> neu_3 neu_5)"
      IF(BRNEU(3,4,4).GT.0d0)
     .  WRITE(18,905) BRNEU(3,4,4),2,1000035,1000035,
     .    "BR(H_3 -> neu_4 neu_4)"
      IF(BRNEU(3,4,5).GT.0d0)
     .  WRITE(18,905) BRNEU(3,4,5),2,1000035,1000045,
     .    "BR(H_3 -> neu_4 neu_5)"
      IF(BRNEU(3,5,5).GT.0d0)
     .  WRITE(18,905) BRNEU(3,5,5),2,1000045,1000045,
     .    "BR(H_3 -> neu_5 neu_5)"
      IF(BRCHA(3,1).GT.0d0)
     .  WRITE(18,905) BRCHA(3,1),2,1000024,-1000024,
     .    "BR(H_3 -> cha_1 cha_1bar)"
      IF(BRCHA(3,2).GT.0d0)
     .  WRITE(18,905) BRCHA(3,2),2,1000024,-1000037,
     .    "BR(H_3 -> cha_1 cha_2bar)"
      IF(BRCHA(3,2).GT.0d0)
     .  WRITE(18,905) BRCHA(3,2),2,1000037,-1000024,
     .    "BR(H_3 -> cha_2 cha_1bar)"
      IF(BRCHA(3,3).GT.0d0)
     .  WRITE(18,905) BRCHA(3,3),2,1000037,-1000037,
     .    "BR(H_3 -> cha_2 cha_2bar)"
      IF(BRHSQ(3,1).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,1),2,1000002,-1000002,
     .    "BR(H_3 -> ~u_L ~ubar_L)"
      IF(BRHSQ(3,1).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,1),2,1000004,-1000004,
     .    "BR(H_3 -> ~c_L ~cbar_L)"
      IF(BRHSQ(3,2).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,2),2,2000002,-2000002,
     .    "BR(H_3 -> ~u_R ~ubar_R)"
      IF(BRHSQ(3,2).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,2),2,2000004,-2000004,
     .    "BR(H_3 -> ~c_R ~cbar_R)"
      IF(BRHSQ(3,3).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,3),2,1000001,-1000001,
     .    "BR(H_3 -> ~d_L ~dbar_L)"
      IF(BRHSQ(3,3).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,3),2,1000003,-1000003,
     .    "BR(H_3 -> ~s_L ~sbar_L)"
      IF(BRHSQ(3,4).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,4),2,2000001,-2000001,
     .    "BR(H_3 -> ~d_R ~dbar_R)"
      IF(BRHSQ(3,4).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,4),2,2000003,-2000003,
     .    "BR(H_3 -> ~s_R ~sbar_R)"
      IF(BRHSQ(3,5).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,5),2,1000006,-1000006,
     .    "BR(H_3 -> ~t_1 ~tbar_1)"
      IF(BRHSQ(3,6).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,6),2,2000006,-2000006,
     .    "BR(H_3 -> ~t_2 ~tbar_2)"
      IF(BRHSQ(3,7).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,7),2,1000006,-2000006,
     .    "BR(H_3 -> ~t_1 ~tbar_2)"
      IF(BRHSQ(3,7).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,7),2,2000006,-1000006,
     .    "BR(H_3 -> ~t_2 ~tbar_1)"
      IF(BRHSQ(3,8).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,8),2,1000005,-1000005,
     .    "BR(H_3 -> ~b_1 ~bbar_1)"
      IF(BRHSQ(3,9).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,9),2,2000005,-2000005,
     .    "BR(H_3 -> ~b_2 ~bbar_2)"
      IF(BRHSQ(3,10).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,10),2,1000005,-2000005,
     .    "BR(H_3 -> ~b_1 ~bbar_2)"
      IF(BRHSQ(3,10).GT.0d0)
     .  WRITE(18,905) BRHSQ(3,10),2,2000005,-1000005,
     .    "BR(H_3 -> ~b_2 ~bbar_1)"
      IF(BRHSL(3,1).GT.0d0)
     .  WRITE(18,905) BRHSL(3,1),2,1000011,-1000011,
     .    "BR(H_3 -> ~e_L ~ebar_L)"
      IF(BRHSL(3,1).GT.0d0)
     .  WRITE(18,905) BRHSL(3,1),2,1000013,-1000013,
     .    "BR(H_3 -> ~mu_L ~mubar_L)"
      IF(BRHSL(3,2).GT.0d0)
     .  WRITE(18,905) BRHSL(3,2),2,2000011,-2000011,
     .    "BR(H_3 -> ~e_R ~ebar_R)"
      IF(BRHSL(3,2).GT.0d0)
     .  WRITE(18,905) BRHSL(3,2),2,2000013,-2000013,
     .    "BR(H_3 -> ~mu_R ~mubarRL)"
      IF(BRHSL(3,3).GT.0d0)
     .  WRITE(18,905) BRHSL(3,3),2,1000012,-1000012,
     .    "BR(H_3 -> ~nu_e_L ~nu_ebar_L)"
      IF(BRHSL(3,3).GT.0d0)
     .  WRITE(18,905) BRHSL(3,3),2,1000014,-1000014,
     .    "BR(H_3 -> ~nu_mu_L ~nu_mubar_L)"
      IF(BRHSL(3,4).GT.0d0)
     .  WRITE(18,905) BRHSL(3,4),2,1000015,-1000015,
     .    "BR(H_3 -> ~tau_1 ~taubar_1)"
      IF(BRHSL(3,5).GT.0d0)
     .  WRITE(18,905) BRHSL(3,5),2,2000015,-2000015,
     .    "BR(H_3 -> ~tau_2 ~taubar_2)"
      IF(BRHSL(3,6).GT.0d0)
     .  WRITE(18,905) BRHSL(3,6),2,1000015,-2000015,
     .    "BR(H_3 -> ~tau_1 ~taubar_2)"
      IF(BRHSL(3,6).GT.0d0)
     .  WRITE(18,905) BRHSL(3,6),2,2000015,-1000015,
     .    "BR(H_3 -> ~tau_2 ~taubar_1)"
      IF(BRHSL(3,7).GT.0d0)
     .  WRITE(18,905) BRHSL(3,7),2,1000016,-1000016,
     .    "BR(H_3 -> ~nu_tau_L ~nu_taubar_L)"

      WRITE(18,904) 36,WIDTH(4),"Lightest pseudoscalar"
      IF(BRJJ(4).GT.0d0)
     .  WRITE(18,905) BRJJ(4),2,21,21,"BR(A_1 -> gluon gluon)"
      IF(BRMM(4).GT.0d0)
     .  WRITE(18,905) BRMM(4),2,13,-13,"BR(A_1 -> muon muon)"
      IF(BRLL(4).GT.0d0)
     .  WRITE(18,905) BRLL(4),2,15,-15,"BR(A_1 -> tau tau)"
      IF(BRSS(4).GT.0d0)
     .  WRITE(18,905) BRSS(4),2,3,-3,"BR(A_1 -> s sbar)"
      IF(BRCC(4).GT.0d0)
     .  WRITE(18,905) BRCC(4),2,4,-4,"BR(A_1 -> c cbar)"
      IF(BRBB(4).GT.0d0)
     .  WRITE(18,905) BRBB(4),2,5,-5,"BR(A_1 -> b bbar)"
      IF(BRTT(4).GT.0d0)
     .  WRITE(18,905) BRTT(4),2,6,-6,"BR(A_1 -> t tbar)"
      IF(BRGG(4).GT.0d0)
     .  WRITE(18,905) BRGG(4),2,22,22,"BR(A_1 -> gamma gamma)"
      IF(BRZG(4).GT.0d0)
     .  WRITE(18,905) BRZG(4),2,23,22,"BR(A_1 -> Z gamma)"
      IF(BRAHZ(1,1).GT.0d0)
     .  WRITE(18,905) BRAHZ(1,1),2,23,25,"BR(A_1 -> Z H_1)"
      IF(BRAHZ(1,2).GT.0d0)
     .  WRITE(18,905) BRAHZ(1,2),2,23,35,"BR(A_1 -> Z H_2)"
      IF(BRNEU(4,1,1).GT.0d0)
     .  WRITE(18,905) BRNEU(4,1,1),2,1000022,1000022,
     .    "BR(A_1 -> neu_1 neu_1)"
      IF(BRNEU(4,1,2).GT.0d0)
     .  WRITE(18,905) BRNEU(4,1,2),2,1000022,1000023,
     .    "BR(A_1 -> neu_1 neu_2)"
      IF(BRNEU(4,1,3).GT.0d0)
     .  WRITE(18,905) BRNEU(4,1,3),2,1000022,1000025,
     .    "BR(A_1 -> neu_1 neu_3)"
      IF(BRNEU(4,1,4).GT.0d0)
     .  WRITE(18,905) BRNEU(4,1,4),2,1000022,1000035,
     .    "BR(A_1 -> neu_1 neu_4)"
      IF(BRNEU(4,1,5).GT.0d0)
     .  WRITE(18,905) BRNEU(4,1,5),2,1000022,1000045,
     .    "BR(A_1 -> neu_1 neu_5)"
      IF(BRNEU(4,2,2).GT.0d0)
     .  WRITE(18,905) BRNEU(4,2,2),2,1000023,1000023,
     .    "BR(A_1 -> neu_2 neu_2)"
      IF(BRNEU(4,2,3).GT.0d0)
     .  WRITE(18,905) BRNEU(4,2,3),2,1000023,1000025,
     .    "BR(A_1 -> neu_2 neu_3)"
      IF(BRNEU(4,2,4).GT.0d0)
     .  WRITE(18,905) BRNEU(4,2,4),2,1000023,1000035,
     .    "BR(A_1 -> neu_2 neu_4)"
      IF(BRNEU(4,2,5).GT.0d0)
     .  WRITE(18,905) BRNEU(4,2,5),2,1000023,1000045,
     .    "BR(A_1 -> neu_2 neu_5)"
      IF(BRNEU(4,3,3).GT.0d0)
     .  WRITE(18,905) BRNEU(4,3,3),2,1000025,1000025,
     .    "BR(A_1 -> neu_3 neu_3)"
      IF(BRNEU(4,3,4).GT.0d0)
     .  WRITE(18,905) BRNEU(4,3,4),2,1000025,1000035,
     .    "BR(A_1 -> neu_3 neu_4)"
      IF(BRNEU(4,3,5).GT.0d0)
     .  WRITE(18,905) BRNEU(4,3,5),2,1000025,1000045,
     .    "BR(A_1 -> neu_3 neu_5)"
      IF(BRNEU(4,4,4).GT.0d0)
     .  WRITE(18,905) BRNEU(4,4,4),2,1000035,1000035,
     .    "BR(A_1 -> neu_4 neu_4)"
      IF(BRNEU(4,4,5).GT.0d0)
     .  WRITE(18,905) BRNEU(4,4,5),2,1000035,1000045,
     .    "BR(A_1 -> neu_4 neu_5)"
      IF(BRNEU(4,5,5).GT.0d0)
     .  WRITE(18,905) BRNEU(4,5,5),2,1000045,1000045,
     .    "BR(A_1 -> neu_5 neu_5)"
      IF(BRCHA(4,1).GT.0d0)
     .  WRITE(18,905) BRCHA(4,1),2,1000024,-1000024,
     .    "BR(A_1 -> cha_1 cha_1bar)"
      IF(BRCHA(4,2).GT.0d0)
     .  WRITE(18,905) BRCHA(4,2),2,1000024,-1000037,
     .    "BR(A_1 -> cha_1 cha_2bar)"
      IF(BRCHA(4,2).GT.0d0)
     .  WRITE(18,905) BRCHA(4,2),2,1000037,-1000024,
     .    "BR(A_1 -> cha_2 cha_1bar)"
      IF(BRCHA(4,3).GT.0d0)
     .  WRITE(18,905) BRCHA(4,3),2,1000037,-1000037,
     .    "BR(A_1 -> cha_2 cha_2bar)"
      IF(BRASQ(1,1).GT.0d0)
     .  WRITE(18,905) BRASQ(1,1),2,1000006,-2000006,
     .    "BR(A_1 -> ~t_1 ~tbar_2)"
      IF(BRASQ(1,1).GT.0d0)
     .  WRITE(18,905) BRASQ(1,1),2,2000006,-1000006,
     .    "BR(A_1 -> ~t_2 ~tbar_1)"
      IF(BRASQ(1,2).GT.0d0)
     .  WRITE(18,905) BRASQ(1,2),2,1000005,-2000005,
     .    "BR(A_1 -> ~b_1 ~bbar_2)"
      IF(BRASQ(1,2).GT.0d0)
     .  WRITE(18,905) BRASQ(1,2),2,2000005,-1000005,
     .    "BR(A_1 -> ~b_2 ~bbar_1)"
      IF(BRASL(1).GT.0d0)
     .  WRITE(18,905) BRASL(1),2,1000015,-2000015,
     .    "BR(A_1 -> ~tau_1 ~taubar_2)"
      IF(BRASL(1).GT.0d0)
     .  WRITE(18,905) BRASL(1),2,2000015,-1000015,
     .    "BR(A_1 -> ~tau_2 ~taubar_1)"

      WRITE(18,904) 46,WIDTH(5),"2nd pseudoscalar"
      IF(BRJJ(5).GT.0d0)
     .  WRITE(18,905) BRJJ(5),2,21,21,"BR(A_2 -> gluon gluon)"
      IF(BRMM(5).GT.0d0)
     .  WRITE(18,905) BRMM(5),2,13,-13,"BR(A_2 -> muon muon)"
      IF(BRLL(5).GT.0d0)
     .  WRITE(18,905) BRLL(5),2,15,-15,"BR(A_2 -> tau tau)"
      IF(BRSS(5).GT.0d0)
     .  WRITE(18,905) BRSS(5),2,3,-3,"BR(A_2 -> s sbar)"
      IF(BRCC(5).GT.0d0)
     .  WRITE(18,905) BRCC(5),2,4,-4,"BR(A_2 -> c cbar)"
      IF(BRBB(5).GT.0d0)
     .  WRITE(18,905) BRBB(5),2,5,-5,"BR(A_2 -> b bbar)"
      IF(BRTT(5).GT.0d0)
     .  WRITE(18,905) BRTT(5),2,6,-6,"BR(A_2 -> t tbar)"
      IF(BRGG(5).GT.0d0)
     .  WRITE(18,905) BRGG(5),2,22,22,"BR(A_2 -> gamma gamma)"
      IF(BRZG(5).GT.0d0)
     .  WRITE(18,905) BRZG(5),2,23,22,"BR(A_2 -> Z gamma)"
      IF(BRAHA(1).GT.0d0)
     .  WRITE(18,905) BRAHA(1),2,36,25,"BR(A_2 -> A_1 H_1)"
      IF(BRAHA(2).GT.0d0)
     .  WRITE(18,905) BRAHA(2),2,36,35,"BR(A_2 -> A_1 H_2)"
      IF(BRAHA(3).GT.0d0)
     .  WRITE(18,905) BRAHA(3),2,36,45,"BR(A_2 -> A_1 H_3)"
      IF(BRAHZ(2,1).GT.0d0)
     .  WRITE(18,905) BRAHZ(2,1),2,23,25,"BR(A_2 -> Z H_1)"
      IF(BRAHZ(2,2).GT.0d0)
     .  WRITE(18,905) BRAHZ(2,2),2,23,35,"BR(A_2 -> Z H_2)"
      IF(BRHCW(5).GT.0d0)
     .  WRITE(18,905) BRHCW(5),2,24,-37,"BR(A_2 -> W+ H-)"
      IF(BRNEU(5,1,1).GT.0d0)
     .  WRITE(18,905) BRNEU(5,1,1),2,1000022,1000022,
     .    "BR(A_2 -> neu_1 neu_1)"
      IF(BRNEU(5,1,2).GT.0d0)
     .  WRITE(18,905) BRNEU(5,1,2),2,1000022,1000023,
     .    "BR(A_2 -> neu_1 neu_2)"
      IF(BRNEU(5,1,3).GT.0d0)
     .  WRITE(18,905) BRNEU(5,1,3),2,1000022,1000025,
     .    "BR(A_2 -> neu_1 neu_3)"
      IF(BRNEU(5,1,4).GT.0d0)
     .  WRITE(18,905) BRNEU(5,1,4),2,1000022,1000035,
     .    "BR(A_2 -> neu_1 neu_4)"
      IF(BRNEU(5,1,5).GT.0d0)
     .  WRITE(18,905) BRNEU(5,1,5),2,1000022,1000045,
     .    "BR(A_2 -> neu_1 neu_5)"
      IF(BRNEU(5,2,2).GT.0d0)
     .  WRITE(18,905) BRNEU(5,2,2),2,1000023,1000023,
     .    "BR(A_2 -> neu_2 neu_2)"
      IF(BRNEU(5,2,3).GT.0d0)
     .  WRITE(18,905) BRNEU(5,2,3),2,1000023,1000025,
     .    "BR(A_2 -> neu_2 neu_3)"
      IF(BRNEU(5,2,4).GT.0d0)
     .  WRITE(18,905) BRNEU(5,2,4),2,1000023,1000035,
     .    "BR(A_2 -> neu_2 neu_4)"
      IF(BRNEU(5,2,5).GT.0d0)
     .  WRITE(18,905) BRNEU(5,2,5),2,1000023,1000045,
     .    "BR(A_2 -> neu_2 neu_5)"
      IF(BRNEU(5,3,3).GT.0d0)
     .  WRITE(18,905) BRNEU(5,3,3),2,1000025,1000025,
     .    "BR(A_2 -> neu_3 neu_3)"
      IF(BRNEU(5,3,4).GT.0d0)
     .  WRITE(18,905) BRNEU(5,3,4),2,1000025,1000035,
     .    "BR(A_2 -> neu_3 neu_4)"
      IF(BRNEU(5,3,5).GT.0d0)
     .  WRITE(18,905) BRNEU(5,3,5),2,1000025,1000045,
     .    "BR(A_2 -> neu_3 neu_5)"
      IF(BRNEU(5,4,4).GT.0d0)
     .  WRITE(18,905) BRNEU(5,4,4),2,1000035,1000035,
     .    "BR(A_2 -> neu_4 neu_4)"
      IF(BRNEU(5,4,5).GT.0d0)
     .  WRITE(18,905) BRNEU(5,4,5),2,1000035,1000045,
     .    "BR(A_2 -> neu_4 neu_5)"
      IF(BRNEU(5,5,5).GT.0d0)
     .  WRITE(18,905) BRNEU(5,5,5),2,1000045,1000045,
     .    "BR(A_2 -> neu_5 neu_5)"
      IF(BRCHA(5,1).GT.0d0)
     .  WRITE(18,905) BRCHA(5,1),2,1000024,-1000024,
     .    "BR(A_2 -> cha_1 cha_1bar)"
      IF(BRCHA(5,2).GT.0d0)
     .  WRITE(18,905) BRCHA(5,2),2,1000024,-1000037,
     .    "BR(A_2 -> cha_1 cha_2bar)"
      IF(BRCHA(5,2).GT.0d0)
     .  WRITE(18,905) BRCHA(5,2),2,1000037,-1000024,
     .    "BR(A_2 -> cha_2 cha_1bar)"
      IF(BRCHA(5,3).GT.0d0)
     .  WRITE(18,905) BRCHA(5,3),2,1000037,-1000037,
     .    "BR(A_2 -> cha_2 cha_2bar)"
      IF(BRASQ(2,1).GT.0d0)
     .  WRITE(18,905) BRASQ(2,1),2,1000006,-2000006,
     .    "BR(A_2 -> ~t_1 ~tbar_2)"
      IF(BRASQ(2,1).GT.0d0)
     .  WRITE(18,905) BRASQ(2,1),2,2000006,-1000006,
     .    "BR(A_2 -> ~t_2 ~tbar_1)"
      IF(BRASQ(2,2).GT.0d0)
     .  WRITE(18,905) BRASQ(2,2),2,1000005,-2000005,
     .    "BR(A_2 -> ~b_1 ~bbar_2)"
      IF(BRASQ(2,2).GT.0d0)
     .  WRITE(18,905) BRASQ(2,2),2,2000005,-1000005,
     .    "BR(A_2 -> ~b_2 ~bbar_1)"
      IF(BRASL(2).GT.0d0)
     .  WRITE(18,905) BRASL(2),2,1000015,-2000015,
     .    "BR(A_2 -> ~tau_1 ~taubar_2)"
      IF(BRASL(2).GT.0d0)
     .  WRITE(18,905) BRASL(2),2,2000015,-1000015,
     .    "BR(A_2 -> ~tau_2 ~taubar_1)"

      WRITE(18,904) 37,HCWIDTH,"Charged Higgs"
      IF(HCBRM.GT.0d0)
     .  WRITE(18,905) HCBRM,2,-13,14,"BR(H+ -> muon nu_muon)"
      IF(HCBRL.GT.0d0)
     .  WRITE(18,905) HCBRL,2,-15,16,"BR(H+ -> tau nu_tau)"
      IF(HCBRSU.GT.0d0)
     .  WRITE(18,905) HCBRSU,2,2,-3,"BR(H+ -> u sbar)"
      IF(HCBRSC.GT.0d0)
     .  WRITE(18,905) HCBRSC,2,4,-3,"BR(H+ -> c sbar)"
      IF(HCBRBU.GT.0d0)
     .  WRITE(18,905) HCBRBU,2,2,-5,"BR(H+ -> u bbar)"
      IF(HCBRBC.GT.0d0)
     .  WRITE(18,905) HCBRBC,2,4,-5,"BR(H+ -> c bbar)"
      IF(HCBRBT.GT.0d0)
     .  WRITE(18,905) HCBRBT,2,6,-5,"BR(H+ -> t bbar)"
      IF(HCBRWH(1).GT.0d0)
     .  WRITE(18,905) HCBRWH(1),2,24,25,"BR(H+ -> W+ H_1)"
      IF(HCBRWH(2).GT.0d0)
     .  WRITE(18,905) HCBRWH(2),2,24,35,"BR(H+ -> W+ H_2)"
      IF(HCBRWH(4).GT.0d0)
     .  WRITE(18,905) HCBRWH(4),2,24,36,"BR(H+ -> W+ A_1)"
      IF(HCBRNC(1,1).GT.0d0)
     .  WRITE(18,905) HCBRNC(1,1),2,1000024,1000022,
     .    "BR(H+ -> cha_1 neu_1)"
      IF(HCBRNC(2,1).GT.0d0)
     .  WRITE(18,905) HCBRNC(2,1),2,1000024,1000023,
     .    "BR(H+ -> cha_1 neu_2)"
      IF(HCBRNC(3,1).GT.0d0)
     .  WRITE(18,905) HCBRNC(3,1),2,1000024,1000025,
     .    "BR(H+ -> cha_1 neu_3)"
      IF(HCBRNC(4,1).GT.0d0)
     .  WRITE(18,905) HCBRNC(4,1),2,1000024,1000035,
     .    "BR(H+ -> cha_1 neu_4)"
      IF(HCBRNC(5,1).GT.0d0)
     .  WRITE(18,905) HCBRNC(5,1),2,1000024,1000045,
     .    "BR(H+ -> cha_1 neu_5)"
      IF(HCBRNC(1,2).GT.0d0)
     .  WRITE(18,905) HCBRNC(1,2),2,1000037,1000022,
     .    "BR(H+ -> cha_2 neu_1)"
      IF(HCBRNC(2,2).GT.0d0)
     .  WRITE(18,905) HCBRNC(2,2),2,1000037,1000023,
     .    "BR(H+ -> cha_2 neu_2)"
      IF(HCBRNC(3,2).GT.0d0)
     .  WRITE(18,905) HCBRNC(3,2),2,1000037,1000025,
     .    "BR(H+ -> cha_2 neu_3)"
      IF(HCBRNC(4,2).GT.0d0)
     .  WRITE(18,905) HCBRNC(4,2),2,1000037,1000035,
     .    "BR(H+ -> cha_2 neu_4)"
      IF(HCBRNC(5,2).GT.0d0)
     .  WRITE(18,905) HCBRNC(5,2),2,1000037,1000045,
     .    "BR(H+ -> cha_2 neu_5)"
      IF(HCBRSQ(1).GT.0d0)
     .  WRITE(18,905) HCBRSQ(1),2,1000002,-1000001,
     .    "BR(H+ -> ~u_L ~dbar_L)"
      IF(HCBRSQ(1).GT.0d0)
     .  WRITE(18,905) HCBRSQ(1),2,1000004,-1000003,
     .    "BR(H+ -> ~c_L ~sbar_L)"
      IF(HCBRSQ(2).GT.0d0)
     .  WRITE(18,905) HCBRSQ(2),2,1000006,-1000005,
     .    "BR(H+ -> ~t_1 ~bbar_1)"
      IF(HCBRSQ(3).GT.0d0)
     .  WRITE(18,905) HCBRSQ(3),2,1000006,-2000005,
     .    "BR(H+ -> ~t_1 ~bbar_2)"
      IF(HCBRSQ(4).GT.0d0)
     .  WRITE(18,905) HCBRSQ(4),2,2000006,-1000005,
     .    "BR(H+ -> ~t_2 ~bbar_1)"
      IF(HCBRSQ(5).GT.0d0)
     .  WRITE(18,905) HCBRSQ(5),2,2000006,-2000005,
     .    "BR(H+ -> ~t_2 ~bbar_2)"
      IF(HCBRSL(1).GT.0d0)
     .  WRITE(18,905) HCBRSL(1),2,1000012,-1000011,
     .    "BR(H+ -> ~nu_e_L ~ebar_L)"
      IF(HCBRSL(1).GT.0d0)
     .  WRITE(18,905) HCBRSL(1),2,1000014,-1000013,
     .    "BR(H+ -> ~nu_mu_L ~mubar_L)"
      IF(HCBRSL(2).GT.0d0)
     .  WRITE(18,905) HCBRSL(2),2,1000016,-1000015,
     .    "BR(H+ -> ~nu_tau_L ~taubar_1)"
      IF(HCBRSL(3).GT.0d0)
     .  WRITE(18,905) HCBRSL(3),2,1000016,-2000015,
     .    "BR(H+ -> ~nu_tau_L ~taubar_2)"

      WRITE(18,904) 6,toptot,'Top Quark'
      IF(brtopbw.ne.0.D0)
     .  WRITE(18,905) brtopbw,2,5,24,'BR(t ->  b    W+)'
      IF(brtopbh.ne.0.D0)
     .  WRITE(18,905) brtopbh,2,5,37,'BR(t ->  b    H+)'
      IF(brtopneutrstop(1,1).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(1,1),2,1000006,1000022,
     . 'BR(t -> ~t_1 ~chi_10)'
      IF(brtopneutrstop(2,1).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(2,1),2,1000006,1000023,
     . 'BR(t -> ~t_1 ~chi_20)'
      IF(brtopneutrstop(3,1).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(3,1),2,1000006,1000025,
     . 'BR(t -> ~t_1 ~chi_30)'
      IF(brtopneutrstop(4,1).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(4,1),2,1000006,1000025,
     . 'BR(t -> ~t_1 ~chi_40)'
      IF(brtopneutrstop(5,1).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(5,1),2,1000006,1000025,
     . 'BR(t -> ~t_1 ~chi_50)'
      IF(brtopneutrstop(1,2).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(1,2),2,2000006,1000022,
     . 'BR(t -> ~t_2 ~chi_10)'
      IF(brtopneutrstop(2,2).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(2,2),2,2000006,1000023,
     . 'BR(t -> ~t_2 ~chi_20)'
      IF(brtopneutrstop(3,2).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(3,2),2,2000006,1000025,
     .'BR(t -> ~t_2 ~chi_30)'
      IF(brtopneutrstop(4,2).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(4,2),2,2000006,1000025,
     . 'BR(t -> ~t_2 ~chi_40)'
      IF(brtopneutrstop(5,2).ne.0.D0)
     .  WRITE(18,905) brtopneutrstop(5,2),2,2000006,1000025,
     . 'BR(t -> ~t_2 ~chi_50)'

      IF(NMSFLAG.NE.0)CALL NS_OUTPUT

 2    IF(OMGFLAG.EQ.0) RETURN
      WRITE(19,899) "# RELIC DENSITY CALCULATED BY MICROMEGAS"
      WRITE(19,899) "#"
      WRITE(19,899) "BLOCK RDINFO   # Program information"
      WRITE(19,900) 1,"MicrOmegas # Dark matter package"
      WRITE(19,900) 2,"4.1.1      # Version number"
      IF(PROB(30).GT.0d0)WRITE(19,900) 3,
     . "# Relic density too large (WMAP)"
      IF(PROB(30).LT.0d0.AND.PROB(30).NE.-1d0.AND.PROB(30).NE.-2d0)
     . WRITE(19,900) 3,"# Relic density too small (WMAP)"
      IF(PROB(31).NE.0d0)WRITE(19,900) 3,
     . "# Excluded by Xenon100"
      IF(IFAIL.EQ.0.OR.IFAIL.GE.10)THEN
        IF(OMGFLAG.NE.0)CALL printRelDen(PROB,19) 
      ELSE
        WRITE(19,900) 4,"# Cannot compute Omega h^2 (0<IFAIL<10)"
      ENDIF

 899  FORMAT(A)
 900  FORMAT(1X,I5,3X,A)
 901  FORMAT(1X,I5,3X,1P,E32.16,0P,3X,'#',1X,A)
 902  FORMAT(1X,I9,3X,1P,E32.16,0P,3X,'#',1X,A)
 903  FORMAT(1X,I2,1X,I2,3X,1P,E32.16,0P,3X,'#',1X,A)
 904  FORMAT('DECAY',1X,I9,3X,1P,E32.16,0P,3X,'#',1X,A)
 905  FORMAT(3X,1P,E32.16,0P,3X,I2,3X,I9,1X,I9,1X,2X,'#',1X,A)
 906  FORMAT('#',1X,A,3X,E32.16)
 907  FORMAT(A,1P,E32.16,A)
 908  FORMAT(2E32.16)
 909  FORMAT(8X,A,12X,A)
 910  FORMAT(E32.16,3X,A)
 911  FORMAT(A,F6.3,A,F6.3,A)
 913  FORMAT(2X,I4,I4,10X,A)
 914  FORMAT(1X,I5,3X,1P,I16,0P,3X,'#',1X,A)
 915  FORMAT(A,A)
 916  FORMAT(A,I1,4E32.16)
 917  FORMAT(A,4E32.16)
 918  FORMAT(1X,I5,3X,A,F6.1,'-',F5.1,A)
 919  FORMAT(1X,I5,3X,A,F6.2)
 920  FORMAT('#',0P,I5,3X,1P,E32.16,0P,3X,'#',1X,A)
 921  FORMAT(1X,I2,1X,I2,3X,'#',1X,A)

      END
