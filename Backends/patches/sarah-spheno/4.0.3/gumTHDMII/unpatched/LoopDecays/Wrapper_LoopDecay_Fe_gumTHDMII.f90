! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Fe_gumTHDMII
Use Model_Data_gumTHDMII 
Use Kinematics 
Use OneLoopDecay_Fe_gumTHDMII 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Fe(MhhOS,Mhh2OS,MAhOS,MAh2OS,MHmOS,MHm2OS,MFdOS,              & 
& MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS,ZAOS,ZPOS,           & 
& ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,               & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,              & 
& ZP,ZW,ZZ,alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,            & 
& m222,vd,vu,dg1,dg2,dg3,dm122,dYu,dYd,dYe,dlam5,dm112,dm222,dlam1,dlam4,dlam3,          & 
& dlam2,dvd,dvu,dZH,dZA,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,          & 
& ZfVG,ZfvL,ZfVP,ZfVZ,ZfVWm,Zfhh,ZfAh,ZfHm,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,ZfVPVZ,         & 
& ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,     & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFeFehhL,ctcplcFeFehhR,ctcplcFeFeVPL,     & 
& ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFeFvHmL,ctcplcFeFvHmR,ctcplcFeFvVWmL,  & 
& ctcplcFeFvVWmR,GcplcFeFvHmL,GcplcFeFvHmR,GcplcHmVPVWm,GcplHmcVWmVP,GosZcplcFeFvHmL,    & 
& GosZcplcFeFvHmR,GosZcplcHmVPVWm,GosZcplHmcVWmVP,GZcplcFeFvHmL,GZcplcFeFvHmR,           & 
& GZcplcHmVPVWm,GZcplHmcVWmVP,ZcplcFeFeAhL,ZcplcFeFeAhR,ZcplcFeFehhL,ZcplcFeFehhR,       & 
& ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFeFeVZL,ZcplcFeFeVZR,ZcplcFeFvHmL,ZcplcFeFvHmR,         & 
& ZcplcFeFvVWmL,ZcplcFeFvVWmR,ZcplcFvFecHmL,ZcplcFvFecHmR,ZcplcFvFecVWmL,ZcplcFvFecVWmR, & 
& ZcplcHmVPVWm,ZcplcVWmVPVWm,ZcplHmcHmVP,ZcplHmcVWmVP,ZRUZH,ZRUZA,ZRUZP,ZRUVd,           & 
& ZRUUd,ZRUVu,ZRUUu,ZRUVe,ZRUUe,MLambda,em,gs,deltaM,kont,gP1LFe)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Real(dp),Intent(in) :: vd,vu

Real(dp),Intent(in) :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),               & 
& alphaH,betaH

Complex(dp),Intent(in) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Real(dp),Intent(in) :: dg1,dg2,dg3,dvd,dvu,dZH(2,2),dZA(2,2),dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp),Intent(in) :: dm122,dYu(3,3),dYd(3,3),dYe(3,3),dlam5,dm112,dm222,dlam1,dlam4,dlam3,dlam2,           & 
& dZDL(3,3),dZDR(3,3),dZUL(3,3),dZUR(3,3),dZEL(3,3),dZER(3,3)

Complex(dp),Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhcHmVWm(2,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),   & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),              & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),               & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),               & 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),           & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplcHmVPVWm(2),cplcHmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm(2,2),              & 
& cplhhcVWmVWm(2),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhVZVZ(2),      & 
& cplHmcHmVP(2,2),cplHmcHmVZ(2,2),cplHmcVWmVP(2),cplHmcVWmVZ(2),ctcplcFeFeAhL(3,3,2),    & 
& ctcplcFeFeAhR(3,3,2),ctcplcFeFehhL(3,3,2),ctcplcFeFehhR(3,3,2),ctcplcFeFeVPL(3,3),     & 
& ctcplcFeFeVPR(3,3),ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),ctcplcFeFvHmL(3,3,2),         & 
& ctcplcFeFvHmR(3,3,2),ctcplcFeFvVWmL(3,3),ctcplcFeFvVWmR(3,3),GcplcFeFvHmL(3,3,2),      & 
& GcplcFeFvHmR(3,3,2),GcplcHmVPVWm(2),GcplHmcVWmVP(2),GosZcplcFeFvHmL(3,3,2),            & 
& GosZcplcFeFvHmR(3,3,2),GosZcplcHmVPVWm(2),GosZcplHmcVWmVP(2),GZcplcFeFvHmL(3,3,2),     & 
& GZcplcFeFvHmR(3,3,2),GZcplcHmVPVWm(2),GZcplHmcVWmVP(2),ZcplcFeFeAhL(3,3,2),            & 
& ZcplcFeFeAhR(3,3,2),ZcplcFeFehhL(3,3,2),ZcplcFeFehhR(3,3,2),ZcplcFeFeVPL(3,3),         & 
& ZcplcFeFeVPR(3,3),ZcplcFeFeVZL(3,3),ZcplcFeFeVZR(3,3),ZcplcFeFvHmL(3,3,2),             & 
& ZcplcFeFvHmR(3,3,2),ZcplcFeFvVWmL(3,3),ZcplcFeFvVWmR(3,3),ZcplcFvFecHmL(3,3,2),        & 
& ZcplcFvFecHmR(3,3,2),ZcplcFvFecVWmL(3,3),ZcplcFvFecVWmR(3,3),ZcplcHmVPVWm(2),          & 
& ZcplcVWmVPVWm,ZcplHmcHmVP(2,2),ZcplHmcVWmVP(2)

Real(dp), Intent(in) :: em, gs 
Complex(dp),Intent(in) :: ZfVG,ZfvL(3,3),ZfVP,ZfVZ,ZfVWm,Zfhh(2,2),ZfAh(2,2),ZfHm(2,2),ZfDL(3,3),               & 
& ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfEL(3,3),ZfER(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MhhOS(2),Mhh2OS(2),MAhOS(2),MAh2OS(2),MHmOS(2),MHm2OS(2),MFdOS(3),MFd2OS(3),          & 
& MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(2,2),           & 
& ZAOS(2,2),ZPOS(2,2)

Complex(dp),Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Complex(dp),Intent(in) :: ZRUZH(2,2),ZRUZA(2,2),ZRUZP(2,2),ZRUVd(3,3),ZRUUd(3,3),ZRUVu(3,3),ZRUUu(3,3),         & 
& ZRUVe(3,3),ZRUUe(3,3)

Real(dp), Intent(in) :: MLambda, deltaM 
Real(dp), Intent(out) :: gP1LFe(3,21) 
Integer, Intent(out) :: kont 
Real(dp) :: MVG,MVP,MVG2,MVP2, helfactor, phasespacefactor 
Integer :: i1,i2,i3,i4, isave, gt1, gt2, gt3 

Complex(dp) :: ZRUZHc(2, 2) 
Complex(dp) :: ZRUZAc(2, 2) 
Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUVdc(3, 3) 
Complex(dp) :: ZRUUdc(3, 3) 
Complex(dp) :: ZRUVuc(3, 3) 
Complex(dp) :: ZRUUuc(3, 3) 
Complex(dp) :: ZRUVec(3, 3) 
Complex(dp) :: ZRUUec(3, 3) 
Real(dp) :: MRPFeToFeAh(3,3,2),MRGFeToFeAh(3,3,2), MRPZFeToFeAh(3,3,2),MRGZFeToFeAh(3,3,2) 
Real(dp) :: MVPFeToFeAh(3,3,2) 
Real(dp) :: RMsqTreeFeToFeAh(3,3,2),RMsqWaveFeToFeAh(3,3,2),RMsqVertexFeToFeAh(3,3,2) 
Complex(dp) :: AmpTreeFeToFeAh(2,3,3,2),AmpWaveFeToFeAh(2,3,3,2)=(0._dp,0._dp),AmpVertexFeToFeAh(2,3,3,2)& 
 & ,AmpVertexIRosFeToFeAh(2,3,3,2),AmpVertexIRdrFeToFeAh(2,3,3,2), AmpSumFeToFeAh(2,3,3,2), AmpSum2FeToFeAh(2,3,3,2) 
Complex(dp) :: AmpTreeZFeToFeAh(2,3,3,2),AmpWaveZFeToFeAh(2,3,3,2),AmpVertexZFeToFeAh(2,3,3,2) 
Real(dp) :: AmpSqFeToFeAh(3,3,2),  AmpSqTreeFeToFeAh(3,3,2) 
Real(dp) :: MRPFeToFehh(3,3,2),MRGFeToFehh(3,3,2), MRPZFeToFehh(3,3,2),MRGZFeToFehh(3,3,2) 
Real(dp) :: MVPFeToFehh(3,3,2) 
Real(dp) :: RMsqTreeFeToFehh(3,3,2),RMsqWaveFeToFehh(3,3,2),RMsqVertexFeToFehh(3,3,2) 
Complex(dp) :: AmpTreeFeToFehh(2,3,3,2),AmpWaveFeToFehh(2,3,3,2)=(0._dp,0._dp),AmpVertexFeToFehh(2,3,3,2)& 
 & ,AmpVertexIRosFeToFehh(2,3,3,2),AmpVertexIRdrFeToFehh(2,3,3,2), AmpSumFeToFehh(2,3,3,2), AmpSum2FeToFehh(2,3,3,2) 
Complex(dp) :: AmpTreeZFeToFehh(2,3,3,2),AmpWaveZFeToFehh(2,3,3,2),AmpVertexZFeToFehh(2,3,3,2) 
Real(dp) :: AmpSqFeToFehh(3,3,2),  AmpSqTreeFeToFehh(3,3,2) 
Real(dp) :: MRPFeToFeVZ(3,3),MRGFeToFeVZ(3,3), MRPZFeToFeVZ(3,3),MRGZFeToFeVZ(3,3) 
Real(dp) :: MVPFeToFeVZ(3,3) 
Real(dp) :: RMsqTreeFeToFeVZ(3,3),RMsqWaveFeToFeVZ(3,3),RMsqVertexFeToFeVZ(3,3) 
Complex(dp) :: AmpTreeFeToFeVZ(4,3,3),AmpWaveFeToFeVZ(4,3,3)=(0._dp,0._dp),AmpVertexFeToFeVZ(4,3,3)& 
 & ,AmpVertexIRosFeToFeVZ(4,3,3),AmpVertexIRdrFeToFeVZ(4,3,3), AmpSumFeToFeVZ(4,3,3), AmpSum2FeToFeVZ(4,3,3) 
Complex(dp) :: AmpTreeZFeToFeVZ(4,3,3),AmpWaveZFeToFeVZ(4,3,3),AmpVertexZFeToFeVZ(4,3,3) 
Real(dp) :: AmpSqFeToFeVZ(3,3),  AmpSqTreeFeToFeVZ(3,3) 
Real(dp) :: MRPFeToFvHm(3,3,2),MRGFeToFvHm(3,3,2), MRPZFeToFvHm(3,3,2),MRGZFeToFvHm(3,3,2) 
Real(dp) :: MVPFeToFvHm(3,3,2) 
Real(dp) :: RMsqTreeFeToFvHm(3,3,2),RMsqWaveFeToFvHm(3,3,2),RMsqVertexFeToFvHm(3,3,2) 
Complex(dp) :: AmpTreeFeToFvHm(2,3,3,2),AmpWaveFeToFvHm(2,3,3,2)=(0._dp,0._dp),AmpVertexFeToFvHm(2,3,3,2)& 
 & ,AmpVertexIRosFeToFvHm(2,3,3,2),AmpVertexIRdrFeToFvHm(2,3,3,2), AmpSumFeToFvHm(2,3,3,2), AmpSum2FeToFvHm(2,3,3,2) 
Complex(dp) :: AmpTreeZFeToFvHm(2,3,3,2),AmpWaveZFeToFvHm(2,3,3,2),AmpVertexZFeToFvHm(2,3,3,2) 
Real(dp) :: AmpSqFeToFvHm(3,3,2),  AmpSqTreeFeToFvHm(3,3,2) 
Real(dp) :: MRPFeToFvVWm(3,3),MRGFeToFvVWm(3,3), MRPZFeToFvVWm(3,3),MRGZFeToFvVWm(3,3) 
Real(dp) :: MVPFeToFvVWm(3,3) 
Real(dp) :: RMsqTreeFeToFvVWm(3,3),RMsqWaveFeToFvVWm(3,3),RMsqVertexFeToFvVWm(3,3) 
Complex(dp) :: AmpTreeFeToFvVWm(4,3,3),AmpWaveFeToFvVWm(4,3,3)=(0._dp,0._dp),AmpVertexFeToFvVWm(4,3,3)& 
 & ,AmpVertexIRosFeToFvVWm(4,3,3),AmpVertexIRdrFeToFvVWm(4,3,3), AmpSumFeToFvVWm(4,3,3), AmpSum2FeToFvVWm(4,3,3) 
Complex(dp) :: AmpTreeZFeToFvVWm(4,3,3),AmpWaveZFeToFvVWm(4,3,3),AmpVertexZFeToFvVWm(4,3,3) 
Real(dp) :: AmpSqFeToFvVWm(3,3),  AmpSqTreeFeToFvVWm(3,3) 
Real(dp) :: MRPFeToFeVP(3,3),MRGFeToFeVP(3,3), MRPZFeToFeVP(3,3),MRGZFeToFeVP(3,3) 
Real(dp) :: MVPFeToFeVP(3,3) 
Real(dp) :: RMsqTreeFeToFeVP(3,3),RMsqWaveFeToFeVP(3,3),RMsqVertexFeToFeVP(3,3) 
Complex(dp) :: AmpTreeFeToFeVP(4,3,3),AmpWaveFeToFeVP(4,3,3)=(0._dp,0._dp),AmpVertexFeToFeVP(4,3,3)& 
 & ,AmpVertexIRosFeToFeVP(4,3,3),AmpVertexIRdrFeToFeVP(4,3,3), AmpSumFeToFeVP(4,3,3), AmpSum2FeToFeVP(4,3,3) 
Complex(dp) :: AmpTreeZFeToFeVP(4,3,3),AmpWaveZFeToFeVP(4,3,3),AmpVertexZFeToFeVP(4,3,3) 
Real(dp) :: AmpSqFeToFeVP(3,3),  AmpSqTreeFeToFeVP(3,3) 
Write(*,*) "Calculating one-loop decays of Fe " 
kont = 0 
MVG = MLambda 
MVP = MLambda 
MVG2 = MLambda**2 
MVP2 = MLambda**2 

ZRUZHc = Conjg(ZRUZH)
ZRUZAc = Conjg(ZRUZA)
ZRUZPc = Conjg(ZRUZP)
ZRUVdc = Conjg(ZRUVd)
ZRUUdc = Conjg(ZRUUd)
ZRUVuc = Conjg(ZRUVu)
ZRUUuc = Conjg(ZRUUu)
ZRUVec = Conjg(ZRUVe)
ZRUUec = Conjg(ZRUUe)

 ! Counter 
isave = 1 

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fe Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FeToFeAh(cplcFeFeAhL,cplcFeFeAhR,MAh,MFe,               & 
& MAh2,MFe2,AmpTreeFeToFeAh)

  Else 
Call Amplitude_Tree_gumTHDMII_FeToFeAh(ZcplcFeFeAhL,ZcplcFeFeAhR,MAh,MFe,             & 
& MAh2,MFe2,AmpTreeFeToFeAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FeToFeAh(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,             & 
& MAhOS,MFeOS,MRPFeToFeAh,MRGFeToFeAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFeAh(MLambda,em,gs,ZcplcFeFeAhL,ZcplcFeFeAhR,           & 
& MAhOS,MFeOS,MRPFeToFeAh,MRGFeToFeAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FeToFeAh(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,             & 
& MAh,MFe,MRPFeToFeAh,MRGFeToFeAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFeAh(MLambda,em,gs,ZcplcFeFeAhL,ZcplcFeFeAhR,           & 
& MAh,MFe,MRPFeToFeAh,MRGFeToFeAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FeToFeAh(cplcFeFeAhL,cplcFeFeAhR,ctcplcFeFeAhL,         & 
& ctcplcFeFeAhR,MAh,MAh2,MFe,MFe2,ZfAh,ZfEL,ZfER,AmpWaveFeToFeAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FeToFeAh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,MAh2,           & 
& MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexFeToFeAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeAh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,       & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexIRdrFeToFeAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeAh(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,      & 
& ZcplcFeFeAhL,ZcplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,      & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosFeToFeAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeAh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,ZcplcFeFeAhL,ZcplcFeFeAhR,     & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexIRosFeToFeAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeAh(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,      & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosFeToFeAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeAh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,       & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexIRosFeToFeAh)

 End if 
 End if 
AmpVertexFeToFeAh = AmpVertexFeToFeAh -  AmpVertexIRdrFeToFeAh! +  AmpVertexIRosFeToFeAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFeToFeAh=0._dp 
AmpVertexZFeToFeAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFeAh(1,gt2,:,:) = AmpWaveZFeToFeAh(1,gt2,:,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFeAh(1,gt1,:,:) 
AmpVertexZFeToFeAh(1,gt2,:,:)= AmpVertexZFeToFeAh(1,gt2,:,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFeAh(1,gt1,:,:) 
AmpWaveZFeToFeAh(2,gt2,:,:) = AmpWaveZFeToFeAh(2,gt2,:,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFeAh(2,gt1,:,:) 
AmpVertexZFeToFeAh(2,gt2,:,:)= AmpVertexZFeToFeAh(2,gt2,:,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFeAh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFeToFeAh=AmpWaveZFeToFeAh 
AmpVertexFeToFeAh= AmpVertexZFeToFeAh
! Final State 1 
AmpWaveZFeToFeAh=0._dp 
AmpVertexZFeToFeAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFeAh(1,:,gt2,:) = AmpWaveZFeToFeAh(1,:,gt2,:)+ZRUVe(gt2,gt1)*AmpWaveFeToFeAh(1,:,gt1,:) 
AmpVertexZFeToFeAh(1,:,gt2,:)= AmpVertexZFeToFeAh(1,:,gt2,:)+ZRUVe(gt2,gt1)*AmpVertexFeToFeAh(1,:,gt1,:) 
AmpWaveZFeToFeAh(2,:,gt2,:) = AmpWaveZFeToFeAh(2,:,gt2,:)+ZRUUec(gt2,gt1)*AmpWaveFeToFeAh(2,:,gt1,:) 
AmpVertexZFeToFeAh(2,:,gt2,:)= AmpVertexZFeToFeAh(2,:,gt2,:)+ZRUUec(gt2,gt1)*AmpVertexFeToFeAh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFeToFeAh=AmpWaveZFeToFeAh 
AmpVertexFeToFeAh= AmpVertexZFeToFeAh
! Final State 2 
AmpWaveZFeToFeAh=0._dp 
AmpVertexZFeToFeAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFeToFeAh(:,:,:,gt2) = AmpWaveZFeToFeAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveFeToFeAh(:,:,:,gt1) 
AmpVertexZFeToFeAh(:,:,:,gt2)= AmpVertexZFeToFeAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexFeToFeAh(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFeToFeAh=AmpWaveZFeToFeAh 
AmpVertexFeToFeAh= AmpVertexZFeToFeAh
End if
If (ShiftIRdiv) Then 
AmpVertexFeToFeAh = AmpVertexFeToFeAh  +  AmpVertexIRosFeToFeAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fe->Fe Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFeToFeAh = AmpTreeFeToFeAh 
 AmpSum2FeToFeAh = AmpTreeFeToFeAh + 2._dp*AmpWaveFeToFeAh + 2._dp*AmpVertexFeToFeAh  
Else 
 AmpSumFeToFeAh = AmpTreeFeToFeAh + AmpWaveFeToFeAh + AmpVertexFeToFeAh
 AmpSum2FeToFeAh = AmpTreeFeToFeAh + AmpWaveFeToFeAh + AmpVertexFeToFeAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFeToFeAh = AmpTreeFeToFeAh
 AmpSum2FeToFeAh = AmpTreeFeToFeAh 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFeOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFe(gt1)).gt.(Abs(MFe(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FeToFeAh = AmpTreeFeToFeAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),MAh(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFeToFeAh(gt1, gt2, gt3) 
  AmpSum2FeToFeAh = 2._dp*AmpWaveFeToFeAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),MAh(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFeToFeAh(gt1, gt2, gt3) 
  AmpSum2FeToFeAh = 2._dp*AmpVertexFeToFeAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),MAh(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFeToFeAh(gt1, gt2, gt3) 
  AmpSum2FeToFeAh = AmpTreeFeToFeAh + 2._dp*AmpWaveFeToFeAh + 2._dp*AmpVertexFeToFeAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),MAh(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFeToFeAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FeToFeAh = AmpTreeFeToFeAh
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
  AmpSqTreeFeToFeAh(gt1, gt2, gt3) = AmpSqFeToFeAh(gt1, gt2, gt3)  
  AmpSum2FeToFeAh = + 2._dp*AmpWaveFeToFeAh + 2._dp*AmpVertexFeToFeAh
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
  AmpSqFeToFeAh(gt1, gt2, gt3) = AmpSqFeToFeAh(gt1, gt2, gt3) + AmpSqTreeFeToFeAh(gt1, gt2, gt3)  
Else  
  AmpSum2FeToFeAh = AmpTreeFeToFeAh
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),MAh(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
  AmpSqTreeFeToFeAh(gt1, gt2, gt3) = AmpSqFeToFeAh(gt1, gt2, gt3)  
  AmpSum2FeToFeAh = + 2._dp*AmpWaveFeToFeAh + 2._dp*AmpVertexFeToFeAh
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),MAh(gt3),AmpSumFeToFeAh(:,gt1, gt2, gt3),AmpSum2FeToFeAh(:,gt1, gt2, gt3),AmpSqFeToFeAh(gt1, gt2, gt3)) 
  AmpSqFeToFeAh(gt1, gt2, gt3) = AmpSqFeToFeAh(gt1, gt2, gt3) + AmpSqTreeFeToFeAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFeToFeAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFeToFeAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFe(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFeOS(gt1),MFeOS(gt2),MAhOS(gt3),helfactor*AmpSqFeToFeAh(gt1, gt2, gt3))
Else 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFe(gt1),MFe(gt2),MAh(gt3),helfactor*AmpSqFeToFeAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPFeToFeAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFeToFeAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFe(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFeToFeAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFeToFeAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFeToFeAh(gt1, gt2, gt3) + MRGFeToFeAh(gt1, gt2, gt3)) 
  gP1LFe(gt1,i4) = gP1LFe(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFeToFeAh(gt1, gt2, gt3) + MRGFeToFeAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFe(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fe hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FeToFehh(cplcFeFehhL,cplcFeFehhR,MFe,Mhh,               & 
& MFe2,Mhh2,AmpTreeFeToFehh)

  Else 
Call Amplitude_Tree_gumTHDMII_FeToFehh(ZcplcFeFehhL,ZcplcFeFehhR,MFe,Mhh,             & 
& MFe2,Mhh2,AmpTreeFeToFehh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FeToFehh(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,             & 
& MFeOS,MhhOS,MRPFeToFehh,MRGFeToFehh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFehh(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,           & 
& MFeOS,MhhOS,MRPFeToFehh,MRGFeToFehh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FeToFehh(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,             & 
& MFe,Mhh,MRPFeToFehh,MRGFeToFehh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFehh(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,           & 
& MFe,Mhh,MRPFeToFehh,MRGFeToFehh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FeToFehh(cplcFeFehhL,cplcFeFehhR,ctcplcFeFehhL,         & 
& ctcplcFeFehhR,MFe,MFe2,Mhh,Mhh2,ZfEL,ZfER,Zfhh,AmpWaveFeToFehh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FeToFehh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,MAh2,           & 
& MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,            & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexFeToFehh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFehh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRdrFeToFehh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFehh(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplcFeFeAhL,    & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,ZcplcFeFehhL,ZcplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,    & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFeToFehh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFehh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,ZcplcFeFehhL,ZcplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,         & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,    & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFeToFehh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFehh(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplcFeFeAhL,    & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,       & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,    & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFeToFehh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFehh(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRosFeToFehh)

 End if 
 End if 
AmpVertexFeToFehh = AmpVertexFeToFehh -  AmpVertexIRdrFeToFehh! +  AmpVertexIRosFeToFehh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFeToFehh=0._dp 
AmpVertexZFeToFehh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFehh(1,gt2,:,:) = AmpWaveZFeToFehh(1,gt2,:,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFehh(1,gt1,:,:) 
AmpVertexZFeToFehh(1,gt2,:,:)= AmpVertexZFeToFehh(1,gt2,:,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFehh(1,gt1,:,:) 
AmpWaveZFeToFehh(2,gt2,:,:) = AmpWaveZFeToFehh(2,gt2,:,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFehh(2,gt1,:,:) 
AmpVertexZFeToFehh(2,gt2,:,:)= AmpVertexZFeToFehh(2,gt2,:,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFehh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFeToFehh=AmpWaveZFeToFehh 
AmpVertexFeToFehh= AmpVertexZFeToFehh
! Final State 1 
AmpWaveZFeToFehh=0._dp 
AmpVertexZFeToFehh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFehh(1,:,gt2,:) = AmpWaveZFeToFehh(1,:,gt2,:)+ZRUVe(gt2,gt1)*AmpWaveFeToFehh(1,:,gt1,:) 
AmpVertexZFeToFehh(1,:,gt2,:)= AmpVertexZFeToFehh(1,:,gt2,:)+ZRUVe(gt2,gt1)*AmpVertexFeToFehh(1,:,gt1,:) 
AmpWaveZFeToFehh(2,:,gt2,:) = AmpWaveZFeToFehh(2,:,gt2,:)+ZRUUec(gt2,gt1)*AmpWaveFeToFehh(2,:,gt1,:) 
AmpVertexZFeToFehh(2,:,gt2,:)= AmpVertexZFeToFehh(2,:,gt2,:)+ZRUUec(gt2,gt1)*AmpVertexFeToFehh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFeToFehh=AmpWaveZFeToFehh 
AmpVertexFeToFehh= AmpVertexZFeToFehh
! Final State 2 
AmpWaveZFeToFehh=0._dp 
AmpVertexZFeToFehh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFeToFehh(:,:,:,gt2) = AmpWaveZFeToFehh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveFeToFehh(:,:,:,gt1) 
AmpVertexZFeToFehh(:,:,:,gt2)= AmpVertexZFeToFehh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexFeToFehh(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFeToFehh=AmpWaveZFeToFehh 
AmpVertexFeToFehh= AmpVertexZFeToFehh
End if
If (ShiftIRdiv) Then 
AmpVertexFeToFehh = AmpVertexFeToFehh  +  AmpVertexIRosFeToFehh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fe->Fe hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFeToFehh = AmpTreeFeToFehh 
 AmpSum2FeToFehh = AmpTreeFeToFehh + 2._dp*AmpWaveFeToFehh + 2._dp*AmpVertexFeToFehh  
Else 
 AmpSumFeToFehh = AmpTreeFeToFehh + AmpWaveFeToFehh + AmpVertexFeToFehh
 AmpSum2FeToFehh = AmpTreeFeToFehh + AmpWaveFeToFehh + AmpVertexFeToFehh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFeToFehh = AmpTreeFeToFehh
 AmpSum2FeToFehh = AmpTreeFeToFehh 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MFeOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFe(gt1)).gt.(Abs(MFe(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FeToFehh = AmpTreeFeToFehh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),Mhh(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFeToFehh(gt1, gt2, gt3) 
  AmpSum2FeToFehh = 2._dp*AmpWaveFeToFehh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),Mhh(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFeToFehh(gt1, gt2, gt3) 
  AmpSum2FeToFehh = 2._dp*AmpVertexFeToFehh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),Mhh(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFeToFehh(gt1, gt2, gt3) 
  AmpSum2FeToFehh = AmpTreeFeToFehh + 2._dp*AmpWaveFeToFehh + 2._dp*AmpVertexFeToFehh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),Mhh(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFeToFehh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FeToFehh = AmpTreeFeToFehh
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
  AmpSqTreeFeToFehh(gt1, gt2, gt3) = AmpSqFeToFehh(gt1, gt2, gt3)  
  AmpSum2FeToFehh = + 2._dp*AmpWaveFeToFehh + 2._dp*AmpVertexFeToFehh
  Call SquareAmp_FtoFS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
  AmpSqFeToFehh(gt1, gt2, gt3) = AmpSqFeToFehh(gt1, gt2, gt3) + AmpSqTreeFeToFehh(gt1, gt2, gt3)  
Else  
  AmpSum2FeToFehh = AmpTreeFeToFehh
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),Mhh(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
  AmpSqTreeFeToFehh(gt1, gt2, gt3) = AmpSqFeToFehh(gt1, gt2, gt3)  
  AmpSum2FeToFehh = + 2._dp*AmpWaveFeToFehh + 2._dp*AmpVertexFeToFehh
  Call SquareAmp_FtoFS(MFe(gt1),MFe(gt2),Mhh(gt3),AmpSumFeToFehh(:,gt1, gt2, gt3),AmpSum2FeToFehh(:,gt1, gt2, gt3),AmpSqFeToFehh(gt1, gt2, gt3)) 
  AmpSqFeToFehh(gt1, gt2, gt3) = AmpSqFeToFehh(gt1, gt2, gt3) + AmpSqTreeFeToFehh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFeToFehh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFeToFehh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFe(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFeOS(gt1),MFeOS(gt2),MhhOS(gt3),helfactor*AmpSqFeToFehh(gt1, gt2, gt3))
Else 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFe(gt1),MFe(gt2),Mhh(gt3),helfactor*AmpSqFeToFehh(gt1, gt2, gt3))
End if 
If ((Abs(MRPFeToFehh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFeToFehh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFe(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFeToFehh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFeToFehh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFeToFehh(gt1, gt2, gt3) + MRGFeToFehh(gt1, gt2, gt3)) 
  gP1LFe(gt1,i4) = gP1LFe(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFeToFehh(gt1, gt2, gt3) + MRGFeToFehh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFe(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fe VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FeToFeVZ(cplcFeFeVZL,cplcFeFeVZR,MFe,MVZ,               & 
& MFe2,MVZ2,AmpTreeFeToFeVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_FeToFeVZ(ZcplcFeFeVZL,ZcplcFeFeVZR,MFe,MVZ,             & 
& MFe2,MVZ2,AmpTreeFeToFeVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FeToFeVZ(MLambda,em,gs,cplcFeFeVZL,cplcFeFeVZR,             & 
& MFeOS,MVZOS,MRPFeToFeVZ,MRGFeToFeVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFeVZ(MLambda,em,gs,ZcplcFeFeVZL,ZcplcFeFeVZR,           & 
& MFeOS,MVZOS,MRPFeToFeVZ,MRGFeToFeVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FeToFeVZ(MLambda,em,gs,cplcFeFeVZL,cplcFeFeVZR,             & 
& MFe,MVZ,MRPFeToFeVZ,MRGFeToFeVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFeVZ(MLambda,em,gs,ZcplcFeFeVZL,ZcplcFeFeVZR,           & 
& MFe,MVZ,MRPFeToFeVZ,MRGFeToFeVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FeToFeVZ(cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,           & 
& cplcFeFeVZR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,MFe,               & 
& MFe2,MVP,MVP2,MVZ,MVZ2,ZfEL,ZfER,ZfVPVZ,ZfVZ,AmpWaveFeToFeVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FeToFeVZ(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,MAh2,           & 
& MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhhhVZ,cplcFeFehhL,          & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexFeToFeVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeVZ(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhhhVZ,cplcFeFehhL,     & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexIRdrFeToFeVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeVZ(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,ZcplcFeFeVZL,    & 
& ZcplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,        & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhVZVZ,               & 
& cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFeToFeVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeVZ(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhhhVZ,cplcFeFehhL,     & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,ZcplcFeFeVZL,ZcplcFeFeVZR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexIRosFeToFeVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeVZ(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,     & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,         & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhVZVZ,               & 
& cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFeToFeVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFeVZ(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhhhVZ,cplcFeFehhL,     & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexIRosFeToFeVZ)

 End if 
 End if 
AmpVertexFeToFeVZ = AmpVertexFeToFeVZ -  AmpVertexIRdrFeToFeVZ! +  AmpVertexIRosFeToFeVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFeToFeVZ=0._dp 
AmpVertexZFeToFeVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFeVZ(1,gt2,:) = AmpWaveZFeToFeVZ(1,gt2,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFeVZ(1,gt1,:) 
AmpVertexZFeToFeVZ(1,gt2,:)= AmpVertexZFeToFeVZ(1,gt2,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFeVZ(1,gt1,:) 
AmpWaveZFeToFeVZ(2,gt2,:) = AmpWaveZFeToFeVZ(2,gt2,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFeVZ(2,gt1,:) 
AmpVertexZFeToFeVZ(2,gt2,:)= AmpVertexZFeToFeVZ(2,gt2,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFeVZ(2,gt1,:) 
AmpWaveZFeToFeVZ(3,gt2,:) = AmpWaveZFeToFeVZ(3,gt2,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFeVZ(3,gt1,:) 
AmpVertexZFeToFeVZ(3,gt2,:)= AmpVertexZFeToFeVZ(3,gt2,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFeVZ(3,gt1,:) 
AmpWaveZFeToFeVZ(4,gt2,:) = AmpWaveZFeToFeVZ(4,gt2,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFeVZ(4,gt1,:) 
AmpVertexZFeToFeVZ(4,gt2,:)= AmpVertexZFeToFeVZ(4,gt2,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFeVZ(4,gt1,:) 
 End Do 
End Do 
AmpWaveFeToFeVZ=AmpWaveZFeToFeVZ 
AmpVertexFeToFeVZ= AmpVertexZFeToFeVZ
! Final State 1 
AmpWaveZFeToFeVZ=0._dp 
AmpVertexZFeToFeVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFeVZ(1,:,gt2) = AmpWaveZFeToFeVZ(1,:,gt2)+ZRUVe(gt2,gt1)*AmpWaveFeToFeVZ(1,:,gt1) 
AmpVertexZFeToFeVZ(1,:,gt2)= AmpVertexZFeToFeVZ(1,:,gt2)+ZRUVe(gt2,gt1)*AmpVertexFeToFeVZ(1,:,gt1) 
AmpWaveZFeToFeVZ(2,:,gt2) = AmpWaveZFeToFeVZ(2,:,gt2)+ZRUUec(gt2,gt1)*AmpWaveFeToFeVZ(2,:,gt1) 
AmpVertexZFeToFeVZ(2,:,gt2)= AmpVertexZFeToFeVZ(2,:,gt2)+ZRUUec(gt2,gt1)*AmpVertexFeToFeVZ(2,:,gt1) 
AmpWaveZFeToFeVZ(3,:,gt2) = AmpWaveZFeToFeVZ(3,:,gt2)+ZRUVe(gt2,gt1)*AmpWaveFeToFeVZ(3,:,gt1) 
AmpVertexZFeToFeVZ(3,:,gt2)= AmpVertexZFeToFeVZ(3,:,gt2)+ZRUVe(gt2,gt1)*AmpVertexFeToFeVZ(3,:,gt1) 
AmpWaveZFeToFeVZ(4,:,gt2) = AmpWaveZFeToFeVZ(4,:,gt2)+ZRUUec(gt2,gt1)*AmpWaveFeToFeVZ(4,:,gt1) 
AmpVertexZFeToFeVZ(4,:,gt2)= AmpVertexZFeToFeVZ(4,:,gt2)+ZRUUec(gt2,gt1)*AmpVertexFeToFeVZ(4,:,gt1) 
 End Do 
End Do 
AmpWaveFeToFeVZ=AmpWaveZFeToFeVZ 
AmpVertexFeToFeVZ= AmpVertexZFeToFeVZ
End if
If (ShiftIRdiv) Then 
AmpVertexFeToFeVZ = AmpVertexFeToFeVZ  +  AmpVertexIRosFeToFeVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fe->Fe VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFeToFeVZ = AmpTreeFeToFeVZ 
 AmpSum2FeToFeVZ = AmpTreeFeToFeVZ + 2._dp*AmpWaveFeToFeVZ + 2._dp*AmpVertexFeToFeVZ  
Else 
 AmpSumFeToFeVZ = AmpTreeFeToFeVZ + AmpWaveFeToFeVZ + AmpVertexFeToFeVZ
 AmpSum2FeToFeVZ = AmpTreeFeToFeVZ + AmpWaveFeToFeVZ + AmpVertexFeToFeVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFeToFeVZ = AmpTreeFeToFeVZ
 AmpSum2FeToFeVZ = AmpTreeFeToFeVZ 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFeOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MFe(gt1)).gt.(Abs(MFe(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FeToFeVZ = AmpTreeFeToFeVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),MVZOS,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVZ,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFeToFeVZ(gt1, gt2) 
  AmpSum2FeToFeVZ = 2._dp*AmpWaveFeToFeVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),MVZOS,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVZ,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFeToFeVZ(gt1, gt2) 
  AmpSum2FeToFeVZ = 2._dp*AmpVertexFeToFeVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),MVZOS,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVZ,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFeToFeVZ(gt1, gt2) 
  AmpSum2FeToFeVZ = AmpTreeFeToFeVZ + 2._dp*AmpWaveFeToFeVZ + 2._dp*AmpVertexFeToFeVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),MVZOS,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVZ,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFeToFeVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FeToFeVZ = AmpTreeFeToFeVZ
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),MVZOS,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
  AmpSqTreeFeToFeVZ(gt1, gt2) = AmpSqFeToFeVZ(gt1, gt2)  
  AmpSum2FeToFeVZ = + 2._dp*AmpWaveFeToFeVZ + 2._dp*AmpVertexFeToFeVZ
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),MVZOS,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
  AmpSqFeToFeVZ(gt1, gt2) = AmpSqFeToFeVZ(gt1, gt2) + AmpSqTreeFeToFeVZ(gt1, gt2)  
Else  
  AmpSum2FeToFeVZ = AmpTreeFeToFeVZ
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVZ,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
  AmpSqTreeFeToFeVZ(gt1, gt2) = AmpSqFeToFeVZ(gt1, gt2)  
  AmpSum2FeToFeVZ = + 2._dp*AmpWaveFeToFeVZ + 2._dp*AmpVertexFeToFeVZ
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVZ,AmpSumFeToFeVZ(:,gt1, gt2),AmpSum2FeToFeVZ(:,gt1, gt2),AmpSqFeToFeVZ(gt1, gt2)) 
  AmpSqFeToFeVZ(gt1, gt2) = AmpSqFeToFeVZ(gt1, gt2) + AmpSqTreeFeToFeVZ(gt1, gt2)  
End if  
Else  
  AmpSqFeToFeVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFeToFeVZ(gt1, gt2).eq.0._dp) Then 
  gP1LFe(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFeOS(gt1),MFeOS(gt2),MVZOS,helfactor*AmpSqFeToFeVZ(gt1, gt2))
Else 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFe(gt1),MFe(gt2),MVZ,helfactor*AmpSqFeToFeVZ(gt1, gt2))
End if 
If ((Abs(MRPFeToFeVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFeToFeVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFe(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFeToFeVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFeToFeVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFeToFeVZ(gt1, gt2) + MRGFeToFeVZ(gt1, gt2)) 
  gP1LFe(gt1,i4) = gP1LFe(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFeToFeVZ(gt1, gt2) + MRGFeToFeVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFe(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fv Hm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FeToFvHm(cplcFeFvHmL,cplcFeFvHmR,MFe,MHm,               & 
& MFe2,MHm2,AmpTreeFeToFvHm)

  Else 
Call Amplitude_Tree_gumTHDMII_FeToFvHm(ZcplcFeFvHmL,ZcplcFeFvHmR,MFe,MHm,             & 
& MFe2,MHm2,AmpTreeFeToFvHm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FeToFvHm(MLambda,em,gs,cplcFeFvHmL,cplcFeFvHmR,             & 
& MFeOS,MHmOS,MRPFeToFvHm,MRGFeToFvHm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFvHm(MLambda,em,gs,ZcplcFeFvHmL,ZcplcFeFvHmR,           & 
& MFeOS,MHmOS,MRPFeToFvHm,MRGFeToFvHm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FeToFvHm(MLambda,em,gs,cplcFeFvHmL,cplcFeFvHmR,             & 
& MFe,MHm,MRPFeToFvHm,MRGFeToFvHm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFvHm(MLambda,em,gs,ZcplcFeFvHmL,ZcplcFeFvHmR,           & 
& MFe,MHm,MRPFeToFvHm,MRGFeToFvHm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FeToFvHm(cplcFeFvHmL,cplcFeFvHmR,ctcplcFeFvHmL,         & 
& ctcplcFeFvHmR,MFe,MFe2,MHm,MHm2,ZfEL,ZfER,ZfHm,ZfvL,AmpWaveFeToFvHm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FeToFvHm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,MAh2,           & 
& MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexFeToFvHm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvHm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexIRdrFeToFvHm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvHm(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFeFeVZL,cplcFeFeVZR,ZcplcFeFvHmL,ZcplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFvFvVZL,cplcFvFvVZR,cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,      & 
& cplHmcVWmVZ,AmpVertexIRosFeToFvHm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvHm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& ZcplcFeFvHmL,ZcplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,           & 
& cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexIRosFeToFvHm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvHm(MAhOS,MFeOS,MhhOS,MHmOS,MVP,              & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFvVZL,cplcFvFvVZR,cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,      & 
& cplHmcVWmVZ,AmpVertexIRosFeToFvHm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvHm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,             & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexIRosFeToFvHm)

 End if 
 End if 
AmpVertexFeToFvHm = AmpVertexFeToFvHm -  AmpVertexIRdrFeToFvHm! +  AmpVertexIRosFeToFvHm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFeToFvHm=0._dp 
AmpVertexZFeToFvHm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFvHm(1,gt2,:,:) = AmpWaveZFeToFvHm(1,gt2,:,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFvHm(1,gt1,:,:) 
AmpVertexZFeToFvHm(1,gt2,:,:)= AmpVertexZFeToFvHm(1,gt2,:,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFvHm(1,gt1,:,:) 
AmpWaveZFeToFvHm(2,gt2,:,:) = AmpWaveZFeToFvHm(2,gt2,:,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFvHm(2,gt1,:,:) 
AmpVertexZFeToFvHm(2,gt2,:,:)= AmpVertexZFeToFvHm(2,gt2,:,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFvHm(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFeToFvHm=AmpWaveZFeToFvHm 
AmpVertexFeToFvHm= AmpVertexZFeToFvHm
! Final State 2 
AmpWaveZFeToFvHm=0._dp 
AmpVertexZFeToFvHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFeToFvHm(:,:,:,gt2) = AmpWaveZFeToFvHm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveFeToFvHm(:,:,:,gt1) 
AmpVertexZFeToFvHm(:,:,:,gt2)= AmpVertexZFeToFvHm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexFeToFvHm(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFeToFvHm=AmpWaveZFeToFvHm 
AmpVertexFeToFvHm= AmpVertexZFeToFvHm
End if
If (ShiftIRdiv) Then 
AmpVertexFeToFvHm = AmpVertexFeToFvHm  +  AmpVertexIRosFeToFvHm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fe->Fv Hm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFeToFvHm = AmpTreeFeToFvHm 
 AmpSum2FeToFvHm = AmpTreeFeToFvHm + 2._dp*AmpWaveFeToFvHm + 2._dp*AmpVertexFeToFvHm  
Else 
 AmpSumFeToFvHm = AmpTreeFeToFvHm + AmpWaveFeToFvHm + AmpVertexFeToFvHm
 AmpSum2FeToFvHm = AmpTreeFeToFvHm + AmpWaveFeToFvHm + AmpVertexFeToFvHm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFeToFvHm = AmpTreeFeToFvHm
 AmpSum2FeToFvHm = AmpTreeFeToFvHm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFeOS(gt1)).gt.(Abs(0.)+Abs(MHmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFe(gt1)).gt.(Abs(0._dp)+Abs(MHm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FeToFvHm = AmpTreeFeToFvHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),0._dp,MHmOS(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),0._dp,MHm(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFeToFvHm(gt1, gt2, gt3) 
  AmpSum2FeToFvHm = 2._dp*AmpWaveFeToFvHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),0._dp,MHmOS(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),0._dp,MHm(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFeToFvHm(gt1, gt2, gt3) 
  AmpSum2FeToFvHm = 2._dp*AmpVertexFeToFvHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),0._dp,MHmOS(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),0._dp,MHm(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFeToFvHm(gt1, gt2, gt3) 
  AmpSum2FeToFvHm = AmpTreeFeToFvHm + 2._dp*AmpWaveFeToFvHm + 2._dp*AmpVertexFeToFvHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFeOS(gt1),0._dp,MHmOS(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFe(gt1),0._dp,MHm(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFeToFvHm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FeToFvHm = AmpTreeFeToFvHm
  Call SquareAmp_FtoFS(MFeOS(gt1),0._dp,MHmOS(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
  AmpSqTreeFeToFvHm(gt1, gt2, gt3) = AmpSqFeToFvHm(gt1, gt2, gt3)  
  AmpSum2FeToFvHm = + 2._dp*AmpWaveFeToFvHm + 2._dp*AmpVertexFeToFvHm
  Call SquareAmp_FtoFS(MFeOS(gt1),0._dp,MHmOS(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
  AmpSqFeToFvHm(gt1, gt2, gt3) = AmpSqFeToFvHm(gt1, gt2, gt3) + AmpSqTreeFeToFvHm(gt1, gt2, gt3)  
Else  
  AmpSum2FeToFvHm = AmpTreeFeToFvHm
  Call SquareAmp_FtoFS(MFe(gt1),0._dp,MHm(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
  AmpSqTreeFeToFvHm(gt1, gt2, gt3) = AmpSqFeToFvHm(gt1, gt2, gt3)  
  AmpSum2FeToFvHm = + 2._dp*AmpWaveFeToFvHm + 2._dp*AmpVertexFeToFvHm
  Call SquareAmp_FtoFS(MFe(gt1),0._dp,MHm(gt3),AmpSumFeToFvHm(:,gt1, gt2, gt3),AmpSum2FeToFvHm(:,gt1, gt2, gt3),AmpSqFeToFvHm(gt1, gt2, gt3)) 
  AmpSqFeToFvHm(gt1, gt2, gt3) = AmpSqFeToFvHm(gt1, gt2, gt3) + AmpSqTreeFeToFvHm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFeToFvHm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFeToFvHm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFe(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFeOS(gt1),0._dp,MHmOS(gt3),helfactor*AmpSqFeToFvHm(gt1, gt2, gt3))
Else 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFe(gt1),0._dp,MHm(gt3),helfactor*AmpSqFeToFvHm(gt1, gt2, gt3))
End if 
If ((Abs(MRPFeToFvHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFeToFvHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFe(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFeToFvHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFeToFvHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFeToFvHm(gt1, gt2, gt3) + MRGFeToFvHm(gt1, gt2, gt3)) 
  gP1LFe(gt1,i4) = gP1LFe(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFeToFvHm(gt1, gt2, gt3) + MRGFeToFvHm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFe(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fv VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FeToFvVWm(cplcFeFvVWmL,cplcFeFvVWmR,MFe,MVWm,           & 
& MFe2,MVWm2,AmpTreeFeToFvVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_FeToFvVWm(ZcplcFeFvVWmL,ZcplcFeFvVWmR,MFe,              & 
& MVWm,MFe2,MVWm2,AmpTreeFeToFvVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FeToFvVWm(MLambda,em,gs,cplcFeFvVWmL,cplcFeFvVWmR,          & 
& MFeOS,MVWmOS,MRPFeToFvVWm,MRGFeToFvVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFvVWm(MLambda,em,gs,ZcplcFeFvVWmL,ZcplcFeFvVWmR,        & 
& MFeOS,MVWmOS,MRPFeToFvVWm,MRGFeToFvVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FeToFvVWm(MLambda,em,gs,cplcFeFvVWmL,cplcFeFvVWmR,          & 
& MFe,MVWm,MRPFeToFvVWm,MRGFeToFvVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FeToFvVWm(MLambda,em,gs,ZcplcFeFvVWmL,ZcplcFeFvVWmR,        & 
& MFe,MVWm,MRPFeToFvVWm,MRGFeToFvVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FeToFvVWm(cplcFeFvVWmL,cplcFeFvVWmR,ctcplcFeFvVWmL,     & 
& ctcplcFeFvVWmR,MFe,MFe2,MVWm,MVWm2,ZfEL,ZfER,ZfvL,ZfVWm,AmpWaveFeToFvVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FeToFvVWm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,               & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhcHmVWm,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplhhcHmVWm,cplhhcVWmVWm,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,            & 
& AmpVertexFeToFvVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvVWm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhcHmVWm,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplhhcHmVWm,cplhhcVWmVWm,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,            & 
& AmpVertexIRdrFeToFvVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvVWm(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,GosZcplcFeFvHmL,GosZcplcFeFvHmR,ZcplcFeFvVWmL,ZcplcFeFvVWmR,   & 
& cplcFvFvVZL,cplcFvFvVZR,cplhhcHmVWm,cplhhcVWmVWm,GosZcplcHmVPVWm,cplcVWmVPVWm,         & 
& cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFeToFvVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvVWm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhcHmVWm,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& GZcplcFeFvHmL,GZcplcFeFvHmR,ZcplcFeFvVWmL,ZcplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplhhcHmVWm,cplhhcVWmVWm,GZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,          & 
& AmpVertexIRosFeToFvVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvVWm(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,GcplcFeFvHmL,GcplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFvFvVZL,cplcFvFvVZR,cplhhcHmVWm,cplhhcVWmVWm,GcplcHmVPVWm,cplcVWmVPVWm,            & 
& cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFeToFvVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FeToFvVWm(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhcHmVWm,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplhhcHmVWm,cplhhcVWmVWm,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,            & 
& AmpVertexIRosFeToFvVWm)

 End if 
 End if 
AmpVertexFeToFvVWm = AmpVertexFeToFvVWm -  AmpVertexIRdrFeToFvVWm! +  AmpVertexIRosFeToFvVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFeToFvVWm=0._dp 
AmpVertexZFeToFvVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFeToFvVWm(1,gt2,:) = AmpWaveZFeToFvVWm(1,gt2,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFvVWm(1,gt1,:) 
AmpVertexZFeToFvVWm(1,gt2,:)= AmpVertexZFeToFvVWm(1,gt2,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFvVWm(1,gt1,:) 
AmpWaveZFeToFvVWm(2,gt2,:) = AmpWaveZFeToFvVWm(2,gt2,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFvVWm(2,gt1,:) 
AmpVertexZFeToFvVWm(2,gt2,:)= AmpVertexZFeToFvVWm(2,gt2,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFvVWm(2,gt1,:) 
AmpWaveZFeToFvVWm(3,gt2,:) = AmpWaveZFeToFvVWm(3,gt2,:)+ZRUVec(gt2,gt1)*AmpWaveFeToFvVWm(3,gt1,:) 
AmpVertexZFeToFvVWm(3,gt2,:)= AmpVertexZFeToFvVWm(3,gt2,:) + ZRUVec(gt2,gt1)*AmpVertexFeToFvVWm(3,gt1,:) 
AmpWaveZFeToFvVWm(4,gt2,:) = AmpWaveZFeToFvVWm(4,gt2,:)+ZRUUe(gt2,gt1)*AmpWaveFeToFvVWm(4,gt1,:) 
AmpVertexZFeToFvVWm(4,gt2,:)= AmpVertexZFeToFvVWm(4,gt2,:) + ZRUUe(gt2,gt1)*AmpVertexFeToFvVWm(4,gt1,:) 
 End Do 
End Do 
AmpWaveFeToFvVWm=AmpWaveZFeToFvVWm 
AmpVertexFeToFvVWm= AmpVertexZFeToFvVWm
End if
If (ShiftIRdiv) Then 
AmpVertexFeToFvVWm = AmpVertexFeToFvVWm  +  AmpVertexIRosFeToFvVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fe->Fv VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFeToFvVWm = AmpTreeFeToFvVWm 
 AmpSum2FeToFvVWm = AmpTreeFeToFvVWm + 2._dp*AmpWaveFeToFvVWm + 2._dp*AmpVertexFeToFvVWm  
Else 
 AmpSumFeToFvVWm = AmpTreeFeToFvVWm + AmpWaveFeToFvVWm + AmpVertexFeToFvVWm
 AmpSum2FeToFvVWm = AmpTreeFeToFvVWm + AmpWaveFeToFvVWm + AmpVertexFeToFvVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFeToFvVWm = AmpTreeFeToFvVWm
 AmpSum2FeToFvVWm = AmpTreeFeToFvVWm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFeOS(gt1)).gt.(Abs(0.)+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MFe(gt1)).gt.(Abs(0._dp)+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FeToFvVWm = AmpTreeFeToFvVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),0._dp,MVWmOS,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),0._dp,MVWm,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFeToFvVWm(gt1, gt2) 
  AmpSum2FeToFvVWm = 2._dp*AmpWaveFeToFvVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),0._dp,MVWmOS,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),0._dp,MVWm,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFeToFvVWm(gt1, gt2) 
  AmpSum2FeToFvVWm = 2._dp*AmpVertexFeToFvVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),0._dp,MVWmOS,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),0._dp,MVWm,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFeToFvVWm(gt1, gt2) 
  AmpSum2FeToFvVWm = AmpTreeFeToFvVWm + 2._dp*AmpWaveFeToFvVWm + 2._dp*AmpVertexFeToFvVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),0._dp,MVWmOS,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),0._dp,MVWm,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFeToFvVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FeToFvVWm = AmpTreeFeToFvVWm
  Call SquareAmp_FtoFV(MFeOS(gt1),0._dp,MVWmOS,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
  AmpSqTreeFeToFvVWm(gt1, gt2) = AmpSqFeToFvVWm(gt1, gt2)  
  AmpSum2FeToFvVWm = + 2._dp*AmpWaveFeToFvVWm + 2._dp*AmpVertexFeToFvVWm
  Call SquareAmp_FtoFV(MFeOS(gt1),0._dp,MVWmOS,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
  AmpSqFeToFvVWm(gt1, gt2) = AmpSqFeToFvVWm(gt1, gt2) + AmpSqTreeFeToFvVWm(gt1, gt2)  
Else  
  AmpSum2FeToFvVWm = AmpTreeFeToFvVWm
  Call SquareAmp_FtoFV(MFe(gt1),0._dp,MVWm,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
  AmpSqTreeFeToFvVWm(gt1, gt2) = AmpSqFeToFvVWm(gt1, gt2)  
  AmpSum2FeToFvVWm = + 2._dp*AmpWaveFeToFvVWm + 2._dp*AmpVertexFeToFvVWm
  Call SquareAmp_FtoFV(MFe(gt1),0._dp,MVWm,AmpSumFeToFvVWm(:,gt1, gt2),AmpSum2FeToFvVWm(:,gt1, gt2),AmpSqFeToFvVWm(gt1, gt2)) 
  AmpSqFeToFvVWm(gt1, gt2) = AmpSqFeToFvVWm(gt1, gt2) + AmpSqTreeFeToFvVWm(gt1, gt2)  
End if  
Else  
  AmpSqFeToFvVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFeToFvVWm(gt1, gt2).eq.0._dp) Then 
  gP1LFe(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFeOS(gt1),0._dp,MVWmOS,helfactor*AmpSqFeToFvVWm(gt1, gt2))
Else 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFe(gt1),0._dp,MVWm,helfactor*AmpSqFeToFvVWm(gt1, gt2))
End if 
If ((Abs(MRPFeToFvVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFeToFvVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFe(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFeToFvVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFeToFvVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFeToFvVWm(gt1, gt2) + MRGFeToFvVWm(gt1, gt2)) 
  gP1LFe(gt1,i4) = gP1LFe(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFeToFvVWm(gt1, gt2) + MRGFeToFvVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFe(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End If 
!---------------- 
! Fe VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_FeToFeVP(ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFeFeVZL,        & 
& ZcplcFeFeVZR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,MFeOS,            & 
& MFe2OS,MVP,MVP2,ZfEL,ZfER,ZfVP,ZfVZVP,AmpWaveFeToFeVP)

 Else 
Call Amplitude_WAVE_gumTHDMII_FeToFeVP(cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,           & 
& cplcFeFeVZR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,MFeOS,             & 
& MFe2OS,MVP,MVP2,ZfEL,ZfER,ZfVP,ZfVZVP,AmpWaveFeToFeVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_FeToFeVP(MAhOS,MFeOS,MhhOS,MHmOS,MVP,MVWmOS,          & 
& MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,ZcplcFeFeAhL,ZcplcFeFeAhR,       & 
& ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFeFeVZL,ZcplcFeFeVZR,         & 
& ZcplcFvFecHmL,ZcplcFvFecHmR,ZcplcFvFecVWmL,ZcplcFvFecVWmR,ZcplcFeFvHmL,ZcplcFeFvHmR,   & 
& ZcplcFeFvVWmL,ZcplcFeFvVWmR,ZcplHmcHmVP,ZcplHmcVWmVP,ZcplcHmVPVWm,ZcplcVWmVPVWm,       & 
& AmpVertexFeToFeVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_FeToFeVP(MAhOS,MFeOS,MhhOS,MHmOS,MVP,MVWmOS,          & 
& MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,cplcFeFeAhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,             & 
& AmpVertexFeToFeVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FeToFeVP(cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,           & 
& cplcFeFeVZR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,MFe,               & 
& MFe2,MVP,MVP2,ZfEL,ZfER,ZfVP,ZfVZVP,AmpWaveFeToFeVP)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FeToFeVP(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,MAh2,           & 
& MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,AmpVertexFeToFeVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fe->Fe VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFeToFeVP = 0._dp 
 AmpSum2FeToFeVP = 0._dp  
Else 
 AmpSumFeToFeVP = AmpVertexFeToFeVP + AmpWaveFeToFeVP
 AmpSum2FeToFeVP = AmpVertexFeToFeVP + AmpWaveFeToFeVP 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFeOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MFe(gt1)).gt.(Abs(MFe(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFeOS(gt1),MFeOS(gt2),0._dp,AmpSumFeToFeVP(:,gt1, gt2),AmpSum2FeToFeVP(:,gt1, gt2),AmpSqFeToFeVP(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFe(gt1),MFe(gt2),MVP,AmpSumFeToFeVP(:,gt1, gt2),AmpSum2FeToFeVP(:,gt1, gt2),AmpSqFeToFeVP(gt1, gt2)) 
End if  
Else  
  AmpSqFeToFeVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFeToFeVP(gt1, gt2).eq.0._dp) Then 
  gP1LFe(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFeOS(gt1),MFeOS(gt2),0._dp,helfactor*AmpSqFeToFeVP(gt1, gt2))
Else 
  gP1LFe(gt1,i4) = 1._dp*GammaTPS(MFe(gt1),MFe(gt2),MVP,helfactor*AmpSqFeToFeVP(gt1, gt2))
End if 
If ((Abs(MRPFeToFeVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFeToFeVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFe(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End Subroutine OneLoopDecay_Fe

End Module Wrapper_OneLoopDecay_Fe_gumTHDMII
