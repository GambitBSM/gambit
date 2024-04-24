! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_A0_Inert2
Use Model_Data_Inert2 
Use Kinematics 
Use OneLoopDecay_A0_Inert2 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_A0(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,              & 
& MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,               & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Ye,Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,            & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0A0A0A01,cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,        & 
& cplA0A0H0H01,cplA0A0hh,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0VZVZ1,cplA0cHpVPVWp1,         & 
& cplA0cHpVWp,cplA0cHpVWpVZ1,cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1,          & 
& cplA0H0hh,cplA0H0hhhh1,cplA0H0VZ,cplA0hhHpcHp1,cplA0HpcHp,cplA0HpcVWp,cplA0HpcVWpVP1,  & 
& cplA0HpcVWpVZ1,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcHpL,     & 
& cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,         & 
& cplcFuFdVWpR,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcHpVPVWp,            & 
& cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplG0cHpVPVWp1,cplG0cHpVWp,cplG0cHpVWpVZ1,       & 
& cplG0G0H0H01,cplG0G0hh,cplG0G0HpcHp1,cplG0H0H0,cplG0H0H0hh1,cplG0H0HpcHp1,             & 
& cplG0hhVZ,cplG0HpcVWp,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWp,        & 
& cplH0cHpVWpVZ1,cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0VZVZ1,cplH0hhHpcHp1,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWp,       & 
& cplhhcHpVWpVZ1,cplhhcVWpVWp,cplhhhhhh,cplhhhhHpcHp1,cplhhHpcHp,cplhhHpcVWp,            & 
& cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhVZVZ,cplHpcHpcVWpVWp1,cplHpcHpVP,cplHpcHpVPVP1,     & 
& cplHpcHpVPVZ1,cplHpcHpVZ,cplHpcHpVZVZ1,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp1,         & 
& ctcplA0A0G0,ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0H0VZ,ctcplA0HpcHp,              & 
& ctcplA0HpcVWp,GcplA0HpcHp,GcplcHpVPVWp,GcplHpcVWpVP,GosZcplA0HpcHp,GosZcplcHpVPVWp,    & 
& GosZcplHpcVWpVP,GZcplA0HpcHp,GZcplcHpVPVWp,GZcplHpcVWpVP,ZcplA0A0G0,ZcplA0A0hh,        & 
& ZcplA0G0H0,ZcplA0H0hh,ZcplA0H0VZ,ZcplA0HpcHp,ZcplA0HpcVWp,ZRUZP,ZRUZDL,ZRUZDR,         & 
& ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LA0)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(in) :: v

Real(dp),Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(in) :: dg1,dg2,dg3,dMHD2,dMHU2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp),Intent(in) :: dYe(3,3),dYd(3,3),dYu(3,3),dlam5,dlam1,dlam4,dlam3,dlam2,dZDL(3,3),dZDR(3,3),         & 
& dZUL(3,3),dZUR(3,3),dZEL(3,3),dZER(3,3)

Complex(dp),Intent(in) :: cplA0A0A0A01,cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,        & 
& cplA0A0hh,cplA0A0hhhh1,cplA0A0HpcHp1(2,2),cplA0A0VZVZ1,cplA0cHpVPVWp1(2),              & 
& cplA0cHpVWp(2),cplA0cHpVWpVZ1(2),cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),& 
& cplA0H0hh,cplA0H0hhhh1,cplA0H0VZ,cplA0hhHpcHp1(2,2),cplA0HpcHp(2,2),cplA0HpcVWp(2),    & 
& cplA0HpcVWpVP1(2),cplA0HpcVWpVZ1(2),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),           & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),         & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),           & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),             & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVWp,        & 
& cplcVWpVWpVZ,cplG0cHpVPVWp1(2),cplG0cHpVWp(2),cplG0cHpVWpVZ1(2),cplG0G0H0H01,          & 
& cplG0G0hh,cplG0G0HpcHp1(2,2),cplG0H0H0,cplG0H0H0hh1,cplG0H0HpcHp1(2,2),cplG0hhVZ,      & 
& cplG0HpcVWp(2),cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplH0cHpVPVWp1(2),cplH0cHpVWp(2),   & 
& cplH0cHpVWpVZ1(2),cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),cplH0H0VZVZ1,              & 
& cplH0hhHpcHp1(2,2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2), & 
& cplhhcHpVPVWp1(2),cplhhcHpVWp(2),cplhhcHpVWpVZ1(2),cplhhcVWpVWp,cplhhhhhh,             & 
& cplhhhhHpcHp1(2,2),cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2), & 
& cplhhVZVZ,cplHpcHpcVWpVWp1(2,2),cplHpcHpVP(2,2),cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2), & 
& cplHpcHpVZ(2,2),cplHpcHpVZVZ1(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2),cplHpHpcHpcHp1(2,2,2,2),& 
& ctcplA0A0G0,ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0H0VZ,ctcplA0HpcHp(2,2),         & 
& ctcplA0HpcVWp(2),GcplA0HpcHp(2,2),GcplcHpVPVWp(2),GcplHpcVWpVP(2),GosZcplA0HpcHp(2,2), & 
& GosZcplcHpVPVWp(2),GosZcplHpcVWpVP(2),GZcplA0HpcHp(2,2),GZcplcHpVPVWp(2),              & 
& GZcplHpcVWpVP(2),ZcplA0A0G0,ZcplA0A0hh,ZcplA0G0H0,ZcplA0H0hh,ZcplA0H0VZ,               & 
& ZcplA0HpcHp(2,2),ZcplA0HpcVWp(2)

Real(dp), Intent(in) :: em, gs 
Complex(dp),Intent(in) :: ZfVG,ZfvL(3,3),ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp(2,2),ZfDL(3,3),               & 
& ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfEL(3,3),ZfER(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MHpOS(2),MHp2OS(2),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),          & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS(2,2)

Complex(dp),Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Complex(dp),Intent(in) :: ZRUZP(2,2),ZRUZDL(3,3),ZRUZDR(3,3),ZRUZUL(3,3),ZRUZUR(3,3),ZRUZEL(3,3),               & 
& ZRUZER(3,3)

Real(dp), Intent(in) :: MLambda, deltaM 
Real(dp), Intent(out) :: gP1LA0(1,54) 
Integer, Intent(out) :: kont 
Real(dp) :: MVG,MVP,MVG2,MVP2, helfactor, phasespacefactor 
Integer :: i1,i2,i3,i4, isave, gt1, gt2, gt3 

Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUZDLc(3, 3) 
Complex(dp) :: ZRUZDRc(3, 3) 
Complex(dp) :: ZRUZULc(3, 3) 
Complex(dp) :: ZRUZURc(3, 3) 
Complex(dp) :: ZRUZELc(3, 3) 
Complex(dp) :: ZRUZERc(3, 3) 
Real(dp) :: MRPA0TohhA0,MRGA0TohhA0, MRPZA0TohhA0,MRGZA0TohhA0 
Real(dp) :: MVPA0TohhA0 
Real(dp) :: RMsqTreeA0TohhA0,RMsqWaveA0TohhA0,RMsqVertexA0TohhA0 
Complex(dp) :: AmpTreeA0TohhA0,AmpWaveA0TohhA0=(0._dp,0._dp),AmpVertexA0TohhA0& 
 & ,AmpVertexIRosA0TohhA0,AmpVertexIRdrA0TohhA0, AmpSumA0TohhA0, AmpSum2A0TohhA0 
Complex(dp) :: AmpTreeZA0TohhA0,AmpWaveZA0TohhA0,AmpVertexZA0TohhA0 
Real(dp) :: AmpSqA0TohhA0,  AmpSqTreeA0TohhA0 
Real(dp) :: MRPA0TohhH0,MRGA0TohhH0, MRPZA0TohhH0,MRGZA0TohhH0 
Real(dp) :: MVPA0TohhH0 
Real(dp) :: RMsqTreeA0TohhH0,RMsqWaveA0TohhH0,RMsqVertexA0TohhH0 
Complex(dp) :: AmpTreeA0TohhH0,AmpWaveA0TohhH0=(0._dp,0._dp),AmpVertexA0TohhH0& 
 & ,AmpVertexIRosA0TohhH0,AmpVertexIRdrA0TohhH0, AmpSumA0TohhH0, AmpSum2A0TohhH0 
Complex(dp) :: AmpTreeZA0TohhH0,AmpWaveZA0TohhH0,AmpVertexZA0TohhH0 
Real(dp) :: AmpSqA0TohhH0,  AmpSqTreeA0TohhH0 
Real(dp) :: MRPA0ToH0VZ,MRGA0ToH0VZ, MRPZA0ToH0VZ,MRGZA0ToH0VZ 
Real(dp) :: MVPA0ToH0VZ 
Real(dp) :: RMsqTreeA0ToH0VZ,RMsqWaveA0ToH0VZ,RMsqVertexA0ToH0VZ 
Complex(dp) :: AmpTreeA0ToH0VZ(2),AmpWaveA0ToH0VZ(2)=(0._dp,0._dp),AmpVertexA0ToH0VZ(2)& 
 & ,AmpVertexIRosA0ToH0VZ(2),AmpVertexIRdrA0ToH0VZ(2), AmpSumA0ToH0VZ(2), AmpSum2A0ToH0VZ(2) 
Complex(dp) :: AmpTreeZA0ToH0VZ(2),AmpWaveZA0ToH0VZ(2),AmpVertexZA0ToH0VZ(2) 
Real(dp) :: AmpSqA0ToH0VZ,  AmpSqTreeA0ToH0VZ 
Real(dp) :: MRPA0TocHpHp(2,2),MRGA0TocHpHp(2,2), MRPZA0TocHpHp(2,2),MRGZA0TocHpHp(2,2) 
Real(dp) :: MVPA0TocHpHp(2,2) 
Real(dp) :: RMsqTreeA0TocHpHp(2,2),RMsqWaveA0TocHpHp(2,2),RMsqVertexA0TocHpHp(2,2) 
Complex(dp) :: AmpTreeA0TocHpHp(2,2),AmpWaveA0TocHpHp(2,2)=(0._dp,0._dp),AmpVertexA0TocHpHp(2,2)& 
 & ,AmpVertexIRosA0TocHpHp(2,2),AmpVertexIRdrA0TocHpHp(2,2), AmpSumA0TocHpHp(2,2), AmpSum2A0TocHpHp(2,2) 
Complex(dp) :: AmpTreeZA0TocHpHp(2,2),AmpWaveZA0TocHpHp(2,2),AmpVertexZA0TocHpHp(2,2) 
Real(dp) :: AmpSqA0TocHpHp(2,2),  AmpSqTreeA0TocHpHp(2,2) 
Real(dp) :: MRPA0ToHpcVWp(2),MRGA0ToHpcVWp(2), MRPZA0ToHpcVWp(2),MRGZA0ToHpcVWp(2) 
Real(dp) :: MVPA0ToHpcVWp(2) 
Real(dp) :: RMsqTreeA0ToHpcVWp(2),RMsqWaveA0ToHpcVWp(2),RMsqVertexA0ToHpcVWp(2) 
Complex(dp) :: AmpTreeA0ToHpcVWp(2,2),AmpWaveA0ToHpcVWp(2,2)=(0._dp,0._dp),AmpVertexA0ToHpcVWp(2,2)& 
 & ,AmpVertexIRosA0ToHpcVWp(2,2),AmpVertexIRdrA0ToHpcVWp(2,2), AmpSumA0ToHpcVWp(2,2), AmpSum2A0ToHpcVWp(2,2) 
Complex(dp) :: AmpTreeZA0ToHpcVWp(2,2),AmpWaveZA0ToHpcVWp(2,2),AmpVertexZA0ToHpcVWp(2,2) 
Real(dp) :: AmpSqA0ToHpcVWp(2),  AmpSqTreeA0ToHpcVWp(2) 
Real(dp) :: MRPA0ToA0A0,MRGA0ToA0A0, MRPZA0ToA0A0,MRGZA0ToA0A0 
Real(dp) :: MVPA0ToA0A0 
Real(dp) :: RMsqTreeA0ToA0A0,RMsqWaveA0ToA0A0,RMsqVertexA0ToA0A0 
Complex(dp) :: AmpTreeA0ToA0A0,AmpWaveA0ToA0A0=(0._dp,0._dp),AmpVertexA0ToA0A0& 
 & ,AmpVertexIRosA0ToA0A0,AmpVertexIRdrA0ToA0A0, AmpSumA0ToA0A0, AmpSum2A0ToA0A0 
Complex(dp) :: AmpTreeZA0ToA0A0,AmpWaveZA0ToA0A0,AmpVertexZA0ToA0A0 
Real(dp) :: AmpSqA0ToA0A0,  AmpSqTreeA0ToA0A0 
Real(dp) :: MRPA0ToA0H0,MRGA0ToA0H0, MRPZA0ToA0H0,MRGZA0ToA0H0 
Real(dp) :: MVPA0ToA0H0 
Real(dp) :: RMsqTreeA0ToA0H0,RMsqWaveA0ToA0H0,RMsqVertexA0ToA0H0 
Complex(dp) :: AmpTreeA0ToA0H0,AmpWaveA0ToA0H0=(0._dp,0._dp),AmpVertexA0ToA0H0& 
 & ,AmpVertexIRosA0ToA0H0,AmpVertexIRdrA0ToA0H0, AmpSumA0ToA0H0, AmpSum2A0ToA0H0 
Complex(dp) :: AmpTreeZA0ToA0H0,AmpWaveZA0ToA0H0,AmpVertexZA0ToA0H0 
Real(dp) :: AmpSqA0ToA0H0,  AmpSqTreeA0ToA0H0 
Real(dp) :: MRPA0ToA0VP,MRGA0ToA0VP, MRPZA0ToA0VP,MRGZA0ToA0VP 
Real(dp) :: MVPA0ToA0VP 
Real(dp) :: RMsqTreeA0ToA0VP,RMsqWaveA0ToA0VP,RMsqVertexA0ToA0VP 
Complex(dp) :: AmpTreeA0ToA0VP(2),AmpWaveA0ToA0VP(2)=(0._dp,0._dp),AmpVertexA0ToA0VP(2)& 
 & ,AmpVertexIRosA0ToA0VP(2),AmpVertexIRdrA0ToA0VP(2), AmpSumA0ToA0VP(2), AmpSum2A0ToA0VP(2) 
Complex(dp) :: AmpTreeZA0ToA0VP(2),AmpWaveZA0ToA0VP(2),AmpVertexZA0ToA0VP(2) 
Real(dp) :: AmpSqA0ToA0VP,  AmpSqTreeA0ToA0VP 
Real(dp) :: MRPA0ToA0VZ,MRGA0ToA0VZ, MRPZA0ToA0VZ,MRGZA0ToA0VZ 
Real(dp) :: MVPA0ToA0VZ 
Real(dp) :: RMsqTreeA0ToA0VZ,RMsqWaveA0ToA0VZ,RMsqVertexA0ToA0VZ 
Complex(dp) :: AmpTreeA0ToA0VZ(2),AmpWaveA0ToA0VZ(2)=(0._dp,0._dp),AmpVertexA0ToA0VZ(2)& 
 & ,AmpVertexIRosA0ToA0VZ(2),AmpVertexIRdrA0ToA0VZ(2), AmpSumA0ToA0VZ(2), AmpSum2A0ToA0VZ(2) 
Complex(dp) :: AmpTreeZA0ToA0VZ(2),AmpWaveZA0ToA0VZ(2),AmpVertexZA0ToA0VZ(2) 
Real(dp) :: AmpSqA0ToA0VZ,  AmpSqTreeA0ToA0VZ 
Real(dp) :: MRPA0ToFdcFd(3,3),MRGA0ToFdcFd(3,3), MRPZA0ToFdcFd(3,3),MRGZA0ToFdcFd(3,3) 
Real(dp) :: MVPA0ToFdcFd(3,3) 
Real(dp) :: RMsqTreeA0ToFdcFd(3,3),RMsqWaveA0ToFdcFd(3,3),RMsqVertexA0ToFdcFd(3,3) 
Complex(dp) :: AmpTreeA0ToFdcFd(2,3,3),AmpWaveA0ToFdcFd(2,3,3)=(0._dp,0._dp),AmpVertexA0ToFdcFd(2,3,3)& 
 & ,AmpVertexIRosA0ToFdcFd(2,3,3),AmpVertexIRdrA0ToFdcFd(2,3,3), AmpSumA0ToFdcFd(2,3,3), AmpSum2A0ToFdcFd(2,3,3) 
Complex(dp) :: AmpTreeZA0ToFdcFd(2,3,3),AmpWaveZA0ToFdcFd(2,3,3),AmpVertexZA0ToFdcFd(2,3,3) 
Real(dp) :: AmpSqA0ToFdcFd(3,3),  AmpSqTreeA0ToFdcFd(3,3) 
Real(dp) :: MRPA0ToFecFe(3,3),MRGA0ToFecFe(3,3), MRPZA0ToFecFe(3,3),MRGZA0ToFecFe(3,3) 
Real(dp) :: MVPA0ToFecFe(3,3) 
Real(dp) :: RMsqTreeA0ToFecFe(3,3),RMsqWaveA0ToFecFe(3,3),RMsqVertexA0ToFecFe(3,3) 
Complex(dp) :: AmpTreeA0ToFecFe(2,3,3),AmpWaveA0ToFecFe(2,3,3)=(0._dp,0._dp),AmpVertexA0ToFecFe(2,3,3)& 
 & ,AmpVertexIRosA0ToFecFe(2,3,3),AmpVertexIRdrA0ToFecFe(2,3,3), AmpSumA0ToFecFe(2,3,3), AmpSum2A0ToFecFe(2,3,3) 
Complex(dp) :: AmpTreeZA0ToFecFe(2,3,3),AmpWaveZA0ToFecFe(2,3,3),AmpVertexZA0ToFecFe(2,3,3) 
Real(dp) :: AmpSqA0ToFecFe(3,3),  AmpSqTreeA0ToFecFe(3,3) 
Real(dp) :: MRPA0ToFucFu(3,3),MRGA0ToFucFu(3,3), MRPZA0ToFucFu(3,3),MRGZA0ToFucFu(3,3) 
Real(dp) :: MVPA0ToFucFu(3,3) 
Real(dp) :: RMsqTreeA0ToFucFu(3,3),RMsqWaveA0ToFucFu(3,3),RMsqVertexA0ToFucFu(3,3) 
Complex(dp) :: AmpTreeA0ToFucFu(2,3,3),AmpWaveA0ToFucFu(2,3,3)=(0._dp,0._dp),AmpVertexA0ToFucFu(2,3,3)& 
 & ,AmpVertexIRosA0ToFucFu(2,3,3),AmpVertexIRdrA0ToFucFu(2,3,3), AmpSumA0ToFucFu(2,3,3), AmpSum2A0ToFucFu(2,3,3) 
Complex(dp) :: AmpTreeZA0ToFucFu(2,3,3),AmpWaveZA0ToFucFu(2,3,3),AmpVertexZA0ToFucFu(2,3,3) 
Real(dp) :: AmpSqA0ToFucFu(3,3),  AmpSqTreeA0ToFucFu(3,3) 
Real(dp) :: MRPA0ToFvcFv(3,3),MRGA0ToFvcFv(3,3), MRPZA0ToFvcFv(3,3),MRGZA0ToFvcFv(3,3) 
Real(dp) :: MVPA0ToFvcFv(3,3) 
Real(dp) :: RMsqTreeA0ToFvcFv(3,3),RMsqWaveA0ToFvcFv(3,3),RMsqVertexA0ToFvcFv(3,3) 
Complex(dp) :: AmpTreeA0ToFvcFv(2,3,3),AmpWaveA0ToFvcFv(2,3,3)=(0._dp,0._dp),AmpVertexA0ToFvcFv(2,3,3)& 
 & ,AmpVertexIRosA0ToFvcFv(2,3,3),AmpVertexIRdrA0ToFvcFv(2,3,3), AmpSumA0ToFvcFv(2,3,3), AmpSum2A0ToFvcFv(2,3,3) 
Complex(dp) :: AmpTreeZA0ToFvcFv(2,3,3),AmpWaveZA0ToFvcFv(2,3,3),AmpVertexZA0ToFvcFv(2,3,3) 
Real(dp) :: AmpSqA0ToFvcFv(3,3),  AmpSqTreeA0ToFvcFv(3,3) 
Real(dp) :: MRPA0ToH0H0,MRGA0ToH0H0, MRPZA0ToH0H0,MRGZA0ToH0H0 
Real(dp) :: MVPA0ToH0H0 
Real(dp) :: RMsqTreeA0ToH0H0,RMsqWaveA0ToH0H0,RMsqVertexA0ToH0H0 
Complex(dp) :: AmpTreeA0ToH0H0,AmpWaveA0ToH0H0=(0._dp,0._dp),AmpVertexA0ToH0H0& 
 & ,AmpVertexIRosA0ToH0H0,AmpVertexIRdrA0ToH0H0, AmpSumA0ToH0H0, AmpSum2A0ToH0H0 
Complex(dp) :: AmpTreeZA0ToH0H0,AmpWaveZA0ToH0H0,AmpVertexZA0ToH0H0 
Real(dp) :: AmpSqA0ToH0H0,  AmpSqTreeA0ToH0H0 
Real(dp) :: MRPA0ToH0VP,MRGA0ToH0VP, MRPZA0ToH0VP,MRGZA0ToH0VP 
Real(dp) :: MVPA0ToH0VP 
Real(dp) :: RMsqTreeA0ToH0VP,RMsqWaveA0ToH0VP,RMsqVertexA0ToH0VP 
Complex(dp) :: AmpTreeA0ToH0VP(2),AmpWaveA0ToH0VP(2)=(0._dp,0._dp),AmpVertexA0ToH0VP(2)& 
 & ,AmpVertexIRosA0ToH0VP(2),AmpVertexIRdrA0ToH0VP(2), AmpSumA0ToH0VP(2), AmpSum2A0ToH0VP(2) 
Complex(dp) :: AmpTreeZA0ToH0VP(2),AmpWaveZA0ToH0VP(2),AmpVertexZA0ToH0VP(2) 
Real(dp) :: AmpSqA0ToH0VP,  AmpSqTreeA0ToH0VP 
Real(dp) :: MRPA0Tohhhh,MRGA0Tohhhh, MRPZA0Tohhhh,MRGZA0Tohhhh 
Real(dp) :: MVPA0Tohhhh 
Real(dp) :: RMsqTreeA0Tohhhh,RMsqWaveA0Tohhhh,RMsqVertexA0Tohhhh 
Complex(dp) :: AmpTreeA0Tohhhh,AmpWaveA0Tohhhh=(0._dp,0._dp),AmpVertexA0Tohhhh& 
 & ,AmpVertexIRosA0Tohhhh,AmpVertexIRdrA0Tohhhh, AmpSumA0Tohhhh, AmpSum2A0Tohhhh 
Complex(dp) :: AmpTreeZA0Tohhhh,AmpWaveZA0Tohhhh,AmpVertexZA0Tohhhh 
Real(dp) :: AmpSqA0Tohhhh,  AmpSqTreeA0Tohhhh 
Real(dp) :: MRPA0TohhVP,MRGA0TohhVP, MRPZA0TohhVP,MRGZA0TohhVP 
Real(dp) :: MVPA0TohhVP 
Real(dp) :: RMsqTreeA0TohhVP,RMsqWaveA0TohhVP,RMsqVertexA0TohhVP 
Complex(dp) :: AmpTreeA0TohhVP(2),AmpWaveA0TohhVP(2)=(0._dp,0._dp),AmpVertexA0TohhVP(2)& 
 & ,AmpVertexIRosA0TohhVP(2),AmpVertexIRdrA0TohhVP(2), AmpSumA0TohhVP(2), AmpSum2A0TohhVP(2) 
Complex(dp) :: AmpTreeZA0TohhVP(2),AmpWaveZA0TohhVP(2),AmpVertexZA0TohhVP(2) 
Real(dp) :: AmpSqA0TohhVP,  AmpSqTreeA0TohhVP 
Real(dp) :: MRPA0TohhVZ,MRGA0TohhVZ, MRPZA0TohhVZ,MRGZA0TohhVZ 
Real(dp) :: MVPA0TohhVZ 
Real(dp) :: RMsqTreeA0TohhVZ,RMsqWaveA0TohhVZ,RMsqVertexA0TohhVZ 
Complex(dp) :: AmpTreeA0TohhVZ(2),AmpWaveA0TohhVZ(2)=(0._dp,0._dp),AmpVertexA0TohhVZ(2)& 
 & ,AmpVertexIRosA0TohhVZ(2),AmpVertexIRdrA0TohhVZ(2), AmpSumA0TohhVZ(2), AmpSum2A0TohhVZ(2) 
Complex(dp) :: AmpTreeZA0TohhVZ(2),AmpWaveZA0TohhVZ(2),AmpVertexZA0TohhVZ(2) 
Real(dp) :: AmpSqA0TohhVZ,  AmpSqTreeA0TohhVZ 
Real(dp) :: MRPA0ToVPVP,MRGA0ToVPVP, MRPZA0ToVPVP,MRGZA0ToVPVP 
Real(dp) :: MVPA0ToVPVP 
Real(dp) :: RMsqTreeA0ToVPVP,RMsqWaveA0ToVPVP,RMsqVertexA0ToVPVP 
Complex(dp) :: AmpTreeA0ToVPVP(2),AmpWaveA0ToVPVP(2)=(0._dp,0._dp),AmpVertexA0ToVPVP(2)& 
 & ,AmpVertexIRosA0ToVPVP(2),AmpVertexIRdrA0ToVPVP(2), AmpSumA0ToVPVP(2), AmpSum2A0ToVPVP(2) 
Complex(dp) :: AmpTreeZA0ToVPVP(2),AmpWaveZA0ToVPVP(2),AmpVertexZA0ToVPVP(2) 
Real(dp) :: AmpSqA0ToVPVP,  AmpSqTreeA0ToVPVP 
Real(dp) :: MRPA0ToVPVZ,MRGA0ToVPVZ, MRPZA0ToVPVZ,MRGZA0ToVPVZ 
Real(dp) :: MVPA0ToVPVZ 
Real(dp) :: RMsqTreeA0ToVPVZ,RMsqWaveA0ToVPVZ,RMsqVertexA0ToVPVZ 
Complex(dp) :: AmpTreeA0ToVPVZ(2),AmpWaveA0ToVPVZ(2)=(0._dp,0._dp),AmpVertexA0ToVPVZ(2)& 
 & ,AmpVertexIRosA0ToVPVZ(2),AmpVertexIRdrA0ToVPVZ(2), AmpSumA0ToVPVZ(2), AmpSum2A0ToVPVZ(2) 
Complex(dp) :: AmpTreeZA0ToVPVZ(2),AmpWaveZA0ToVPVZ(2),AmpVertexZA0ToVPVZ(2) 
Real(dp) :: AmpSqA0ToVPVZ,  AmpSqTreeA0ToVPVZ 
Real(dp) :: MRPA0ToVWpcVWp,MRGA0ToVWpcVWp, MRPZA0ToVWpcVWp,MRGZA0ToVWpcVWp 
Real(dp) :: MVPA0ToVWpcVWp 
Real(dp) :: RMsqTreeA0ToVWpcVWp,RMsqWaveA0ToVWpcVWp,RMsqVertexA0ToVWpcVWp 
Complex(dp) :: AmpTreeA0ToVWpcVWp(2),AmpWaveA0ToVWpcVWp(2)=(0._dp,0._dp),AmpVertexA0ToVWpcVWp(2)& 
 & ,AmpVertexIRosA0ToVWpcVWp(2),AmpVertexIRdrA0ToVWpcVWp(2), AmpSumA0ToVWpcVWp(2), AmpSum2A0ToVWpcVWp(2) 
Complex(dp) :: AmpTreeZA0ToVWpcVWp(2),AmpWaveZA0ToVWpcVWp(2),AmpVertexZA0ToVWpcVWp(2) 
Real(dp) :: AmpSqA0ToVWpcVWp,  AmpSqTreeA0ToVWpcVWp 
Real(dp) :: MRPA0ToVZVZ,MRGA0ToVZVZ, MRPZA0ToVZVZ,MRGZA0ToVZVZ 
Real(dp) :: MVPA0ToVZVZ 
Real(dp) :: RMsqTreeA0ToVZVZ,RMsqWaveA0ToVZVZ,RMsqVertexA0ToVZVZ 
Complex(dp) :: AmpTreeA0ToVZVZ(2),AmpWaveA0ToVZVZ(2)=(0._dp,0._dp),AmpVertexA0ToVZVZ(2)& 
 & ,AmpVertexIRosA0ToVZVZ(2),AmpVertexIRdrA0ToVZVZ(2), AmpSumA0ToVZVZ(2), AmpSum2A0ToVZVZ(2) 
Complex(dp) :: AmpTreeZA0ToVZVZ(2),AmpWaveZA0ToVZVZ(2),AmpVertexZA0ToVZVZ(2) 
Real(dp) :: AmpSqA0ToVZVZ,  AmpSqTreeA0ToVZVZ 
Write(*,*) "Calculating one-loop decays of A0 " 
kont = 0 
MVG = MLambda 
MVP = MLambda 
MVG2 = MLambda**2 
MVP2 = MLambda**2 

ZRUZPc = Conjg(ZRUZP)
ZRUZDLc = Conjg(ZRUZDL)
ZRUZDRc = Conjg(ZRUZDR)
ZRUZULc = Conjg(ZRUZUL)
ZRUZURc = Conjg(ZRUZUR)
ZRUZELc = Conjg(ZRUZEL)
ZRUZERc = Conjg(ZRUZER)

 ! Counter 
isave = 1 

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh A0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_A0TohhA0(cplA0A0hh,MA0,Mhh,MA02,Mhh2,AmpTreeA0TohhA0)

  Else 
Call Amplitude_Tree_Inert2_A0TohhA0(ZcplA0A0hh,MA0,Mhh,MA02,Mhh2,AmpTreeA0TohhA0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_A0TohhA0(MLambda,em,gs,cplA0A0hh,MA0OS,MhhOS,MRPA0TohhA0,      & 
& MRGA0TohhA0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_A0TohhA0(MLambda,em,gs,ZcplA0A0hh,MA0OS,MhhOS,MRPA0TohhA0,     & 
& MRGA0TohhA0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_A0TohhA0(MLambda,em,gs,cplA0A0hh,MA0,Mhh,MRPA0TohhA0,          & 
& MRGA0TohhA0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_A0TohhA0(MLambda,em,gs,ZcplA0A0hh,MA0,Mhh,MRPA0TohhA0,         & 
& MRGA0TohhA0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_A0TohhA0(cplA0A0hh,ctcplA0A0hh,MA0,MA02,Mhh,               & 
& Mhh2,ZfA0,Zfhh,AmpWaveA0TohhA0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,     & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexA0TohhA0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_A0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,     & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexIRdrA0TohhA0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhA0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& ZcplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,            & 
& cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,     & 
& cplA0hhHpcHp1,AmpVertexIRosA0TohhA0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,ZcplA0A0hh,cplA0G0H0,cplA0H0hh,               & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,      & 
& cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,     & 
& cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexIRosA0TohhA0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhA0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,            & 
& cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,     & 
& cplA0hhHpcHp1,AmpVertexIRosA0TohhA0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,     & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexIRosA0TohhA0)

 End if 
 End if 
AmpVertexA0TohhA0 = AmpVertexA0TohhA0 -  AmpVertexIRdrA0TohhA0! +  AmpVertexIRosA0TohhA0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexA0TohhA0 = AmpVertexA0TohhA0  +  AmpVertexIRosA0TohhA0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->hh A0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumA0TohhA0 = AmpTreeA0TohhA0 
 AmpSum2A0TohhA0 = AmpTreeA0TohhA0 + 2._dp*AmpWaveA0TohhA0 + 2._dp*AmpVertexA0TohhA0  
Else 
 AmpSumA0TohhA0 = AmpTreeA0TohhA0 + AmpWaveA0TohhA0 + AmpVertexA0TohhA0
 AmpSum2A0TohhA0 = AmpTreeA0TohhA0 + AmpWaveA0TohhA0 + AmpVertexA0TohhA0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0TohhA0 = AmpTreeA0TohhA0
 AmpSum2A0TohhA0 = AmpTreeA0TohhA0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MhhOS)+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(Mhh)+Abs(MA0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2A0TohhA0 = AmpTreeA0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MA0OS,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MA0,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqA0TohhA0 
  AmpSum2A0TohhA0 = 2._dp*AmpWaveA0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MA0OS,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MA0,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqA0TohhA0 
  AmpSum2A0TohhA0 = 2._dp*AmpVertexA0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MA0OS,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MA0,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqA0TohhA0 
  AmpSum2A0TohhA0 = AmpTreeA0TohhA0 + 2._dp*AmpWaveA0TohhA0 + 2._dp*AmpVertexA0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MA0OS,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MA0,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqA0TohhA0 
 End if 
If (OSkinematics) Then 
  AmpSum2A0TohhA0 = AmpTreeA0TohhA0
  Call SquareAmp_StoSS(MA0OS,MhhOS,MA0OS,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
  AmpSqTreeA0TohhA0 = AmpSqA0TohhA0  
  AmpSum2A0TohhA0 = + 2._dp*AmpWaveA0TohhA0 + 2._dp*AmpVertexA0TohhA0
  Call SquareAmp_StoSS(MA0OS,MhhOS,MA0OS,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
  AmpSqA0TohhA0 = AmpSqA0TohhA0 + AmpSqTreeA0TohhA0  
Else  
  AmpSum2A0TohhA0 = AmpTreeA0TohhA0
  Call SquareAmp_StoSS(MA0,Mhh,MA0,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
  AmpSqTreeA0TohhA0 = AmpSqA0TohhA0  
  AmpSum2A0TohhA0 = + 2._dp*AmpWaveA0TohhA0 + 2._dp*AmpVertexA0TohhA0
  Call SquareAmp_StoSS(MA0,Mhh,MA0,AmpSumA0TohhA0,AmpSum2A0TohhA0,AmpSqA0TohhA0) 
  AmpSqA0TohhA0 = AmpSqA0TohhA0 + AmpSqTreeA0TohhA0  
End if  
Else  
  AmpSqA0TohhA0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0TohhA0.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MhhOS,MA0OS,helfactor*AmpSqA0TohhA0)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,Mhh,MA0,helfactor*AmpSqA0TohhA0)
End if 
If ((Abs(MRPA0TohhA0).gt.1.0E-20_dp).or.(Abs(MRGA0TohhA0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPA0TohhA0).gt.1.0E-20_dp).or.(Abs(MRGA0TohhA0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPA0TohhA0 + MRGA0TohhA0) 
  gP1LA0(gt1,i4) = gP1LA0(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPA0TohhA0 + MRGA0TohhA0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LA0(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh H0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_A0TohhH0(cplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,             & 
& AmpTreeA0TohhH0)

  Else 
Call Amplitude_Tree_Inert2_A0TohhH0(ZcplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,            & 
& AmpTreeA0TohhH0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_A0TohhH0(MLambda,em,gs,cplA0H0hh,MA0OS,MH0OS,MhhOS,            & 
& MRPA0TohhH0,MRGA0TohhH0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_A0TohhH0(MLambda,em,gs,ZcplA0H0hh,MA0OS,MH0OS,MhhOS,           & 
& MRPA0TohhH0,MRGA0TohhH0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_A0TohhH0(MLambda,em,gs,cplA0H0hh,MA0,MH0,Mhh,MRPA0TohhH0,      & 
& MRGA0TohhH0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_A0TohhH0(MLambda,em,gs,ZcplA0H0hh,MA0,MH0,Mhh,MRPA0TohhH0,     & 
& MRGA0TohhH0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_A0TohhH0(cplA0H0hh,ctcplA0H0hh,MA0,MA02,MH0,               & 
& MH02,Mhh,Mhh2,ZfA0,ZfH0,Zfhh,AmpWaveA0TohhH0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexA0TohhH0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_A0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRdrA0TohhH0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhH0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,ZcplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,   & 
& cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,        & 
& cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRosA0TohhH0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,ZcplA0H0hh,               & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,         & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,          & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,       & 
& AmpVertexIRosA0TohhH0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhH0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,   & 
& cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,        & 
& cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRosA0TohhH0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRosA0TohhH0)

 End if 
 End if 
AmpVertexA0TohhH0 = AmpVertexA0TohhH0 -  AmpVertexIRdrA0TohhH0! +  AmpVertexIRosA0TohhH0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexA0TohhH0 = AmpVertexA0TohhH0  +  AmpVertexIRosA0TohhH0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->hh H0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumA0TohhH0 = AmpTreeA0TohhH0 
 AmpSum2A0TohhH0 = AmpTreeA0TohhH0 + 2._dp*AmpWaveA0TohhH0 + 2._dp*AmpVertexA0TohhH0  
Else 
 AmpSumA0TohhH0 = AmpTreeA0TohhH0 + AmpWaveA0TohhH0 + AmpVertexA0TohhH0
 AmpSum2A0TohhH0 = AmpTreeA0TohhH0 + AmpWaveA0TohhH0 + AmpVertexA0TohhH0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0TohhH0 = AmpTreeA0TohhH0
 AmpSum2A0TohhH0 = AmpTreeA0TohhH0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MhhOS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(Mhh)+Abs(MH0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2A0TohhH0 = AmpTreeA0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MH0OS,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MH0,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqA0TohhH0 
  AmpSum2A0TohhH0 = 2._dp*AmpWaveA0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MH0OS,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MH0,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqA0TohhH0 
  AmpSum2A0TohhH0 = 2._dp*AmpVertexA0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MH0OS,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MH0,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqA0TohhH0 
  AmpSum2A0TohhH0 = AmpTreeA0TohhH0 + 2._dp*AmpWaveA0TohhH0 + 2._dp*AmpVertexA0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MH0OS,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,MH0,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqA0TohhH0 
 End if 
If (OSkinematics) Then 
  AmpSum2A0TohhH0 = AmpTreeA0TohhH0
  Call SquareAmp_StoSS(MA0OS,MhhOS,MH0OS,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
  AmpSqTreeA0TohhH0 = AmpSqA0TohhH0  
  AmpSum2A0TohhH0 = + 2._dp*AmpWaveA0TohhH0 + 2._dp*AmpVertexA0TohhH0
  Call SquareAmp_StoSS(MA0OS,MhhOS,MH0OS,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
  AmpSqA0TohhH0 = AmpSqA0TohhH0 + AmpSqTreeA0TohhH0  
Else  
  AmpSum2A0TohhH0 = AmpTreeA0TohhH0
  Call SquareAmp_StoSS(MA0,Mhh,MH0,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
  AmpSqTreeA0TohhH0 = AmpSqA0TohhH0  
  AmpSum2A0TohhH0 = + 2._dp*AmpWaveA0TohhH0 + 2._dp*AmpVertexA0TohhH0
  Call SquareAmp_StoSS(MA0,Mhh,MH0,AmpSumA0TohhH0,AmpSum2A0TohhH0,AmpSqA0TohhH0) 
  AmpSqA0TohhH0 = AmpSqA0TohhH0 + AmpSqTreeA0TohhH0  
End if  
Else  
  AmpSqA0TohhH0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0TohhH0.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MhhOS,MH0OS,helfactor*AmpSqA0TohhH0)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,Mhh,MH0,helfactor*AmpSqA0TohhH0)
End if 
If ((Abs(MRPA0TohhH0).gt.1.0E-20_dp).or.(Abs(MRGA0TohhH0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPA0TohhH0).gt.1.0E-20_dp).or.(Abs(MRGA0TohhH0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPA0TohhH0 + MRGA0TohhH0) 
  gP1LA0(gt1,i4) = gP1LA0(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPA0TohhH0 + MRGA0TohhH0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LA0(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! H0 VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_A0ToH0VZ(cplA0H0VZ,MA0,MH0,MVZ,MA02,MH02,MVZ2,             & 
& AmpTreeA0ToH0VZ)

  Else 
Call Amplitude_Tree_Inert2_A0ToH0VZ(ZcplA0H0VZ,MA0,MH0,MVZ,MA02,MH02,MVZ2,            & 
& AmpTreeA0ToH0VZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_A0ToH0VZ(MLambda,em,gs,cplA0H0VZ,MA0OS,MH0OS,MVZOS,            & 
& MRPA0ToH0VZ,MRGA0ToH0VZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_A0ToH0VZ(MLambda,em,gs,ZcplA0H0VZ,MA0OS,MH0OS,MVZOS,           & 
& MRPA0ToH0VZ,MRGA0ToH0VZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_A0ToH0VZ(MLambda,em,gs,cplA0H0VZ,MA0,MH0,MVZ,MRPA0ToH0VZ,      & 
& MRGA0ToH0VZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_A0ToH0VZ(MLambda,em,gs,ZcplA0H0VZ,MA0,MH0,MVZ,MRPA0ToH0VZ,     & 
& MRGA0ToH0VZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_A0ToH0VZ(cplA0H0VZ,ctcplA0H0VZ,MA0,MA02,MH0,               & 
& MH02,MVZ,MVZ2,ZfA0,ZfH0,ZfVZ,AmpWaveA0ToH0VZ)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexA0ToH0VZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_A0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexIRdrA0ToH0VZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToH0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,ZcplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,            & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplA0HpcVWpVZ1,           & 
& cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,AmpVertexIRosA0ToH0VZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,ZcplA0H0VZ,     & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexIRosA0ToH0VZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToH0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,            & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplA0HpcVWpVZ1,           & 
& cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,AmpVertexIRosA0ToH0VZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexIRosA0ToH0VZ)

 End if 
 End if 
AmpVertexA0ToH0VZ = AmpVertexA0ToH0VZ -  AmpVertexIRdrA0ToH0VZ! +  AmpVertexIRosA0ToH0VZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexA0ToH0VZ = AmpVertexA0ToH0VZ  +  AmpVertexIRosA0ToH0VZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->H0 VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumA0ToH0VZ = AmpTreeA0ToH0VZ 
 AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ + 2._dp*AmpWaveA0ToH0VZ + 2._dp*AmpVertexA0ToH0VZ  
Else 
 AmpSumA0ToH0VZ = AmpTreeA0ToH0VZ + AmpWaveA0ToH0VZ + AmpVertexA0ToH0VZ
 AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ + AmpWaveA0ToH0VZ + AmpVertexA0ToH0VZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToH0VZ = AmpTreeA0ToH0VZ
 AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MH0OS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MH0)+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MH0OS,MVZOS,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
Else  
  Call SquareAmp_StoSV(MA0,MH0,MVZ,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqA0ToH0VZ 
  AmpSum2A0ToH0VZ = 2._dp*AmpWaveA0ToH0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MH0OS,MVZOS,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
Else  
  Call SquareAmp_StoSV(MA0,MH0,MVZ,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqA0ToH0VZ 
  AmpSum2A0ToH0VZ = 2._dp*AmpVertexA0ToH0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MH0OS,MVZOS,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
Else  
  Call SquareAmp_StoSV(MA0,MH0,MVZ,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqA0ToH0VZ 
  AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ + 2._dp*AmpWaveA0ToH0VZ + 2._dp*AmpVertexA0ToH0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MH0OS,MVZOS,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
Else  
  Call SquareAmp_StoSV(MA0,MH0,MVZ,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqA0ToH0VZ 
 End if 
If (OSkinematics) Then 
  AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ
  Call SquareAmp_StoSV(MA0OS,MH0OS,MVZOS,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
  AmpSqTreeA0ToH0VZ = AmpSqA0ToH0VZ  
  AmpSum2A0ToH0VZ = + 2._dp*AmpWaveA0ToH0VZ + 2._dp*AmpVertexA0ToH0VZ
  Call SquareAmp_StoSV(MA0OS,MH0OS,MVZOS,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
  AmpSqA0ToH0VZ = AmpSqA0ToH0VZ + AmpSqTreeA0ToH0VZ  
Else  
  AmpSum2A0ToH0VZ = AmpTreeA0ToH0VZ
  Call SquareAmp_StoSV(MA0,MH0,MVZ,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
  AmpSqTreeA0ToH0VZ = AmpSqA0ToH0VZ  
  AmpSum2A0ToH0VZ = + 2._dp*AmpWaveA0ToH0VZ + 2._dp*AmpVertexA0ToH0VZ
  Call SquareAmp_StoSV(MA0,MH0,MVZ,AmpSumA0ToH0VZ(:),AmpSum2A0ToH0VZ(:),AmpSqA0ToH0VZ) 
  AmpSqA0ToH0VZ = AmpSqA0ToH0VZ + AmpSqTreeA0ToH0VZ  
End if  
Else  
  AmpSqA0ToH0VZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToH0VZ.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MH0OS,MVZOS,helfactor*AmpSqA0ToH0VZ)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MH0,MVZ,helfactor*AmpSqA0ToH0VZ)
End if 
If ((Abs(MRPA0ToH0VZ).gt.1.0E-20_dp).or.(Abs(MRGA0ToH0VZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPA0ToH0VZ).gt.1.0E-20_dp).or.(Abs(MRGA0ToH0VZ).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPA0ToH0VZ + MRGA0ToH0VZ) 
  gP1LA0(gt1,i4) = gP1LA0(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPA0ToH0VZ + MRGA0ToH0VZ)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LA0(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Conjg(Hp) Hp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_A0TocHpHp(cplA0HpcHp,MA0,MHp,MA02,MHp2,AmpTreeA0TocHpHp)

  Else 
Call Amplitude_Tree_Inert2_A0TocHpHp(ZcplA0HpcHp,MA0,MHp,MA02,MHp2,AmpTreeA0TocHpHp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_A0TocHpHp(MLambda,em,gs,cplA0HpcHp,MA0OS,MHpOS,MRPA0TocHpHp,   & 
& MRGA0TocHpHp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_A0TocHpHp(MLambda,em,gs,ZcplA0HpcHp,MA0OS,MHpOS,               & 
& MRPA0TocHpHp,MRGA0TocHpHp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_A0TocHpHp(MLambda,em,gs,cplA0HpcHp,MA0,MHp,MRPA0TocHpHp,       & 
& MRGA0TocHpHp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_A0TocHpHp(MLambda,em,gs,ZcplA0HpcHp,MA0,MHp,MRPA0TocHpHp,      & 
& MRGA0TocHpHp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_A0TocHpHp(cplA0HpcHp,ctcplA0HpcHp,MA0,MA02,MHp,            & 
& MHp2,ZfA0,ZfHp,AmpWaveA0TocHpHp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,              & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,       & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,            & 
& cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,             & 
& cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexA0TocHpHp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_A0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,              & 
& cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,              & 
& cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexIRdrA0TocHpHp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TocHpHp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,ZcplA0HpcHp,cplA0HpcVWp,             & 
& cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,              & 
& AmpVertexIRosA0TocHpHp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,ZcplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,       & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,              & 
& cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,              & 
& cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexIRosA0TocHpHp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TocHpHp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,              & 
& cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,              & 
& AmpVertexIRosA0TocHpHp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,              & 
& cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,              & 
& cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexIRosA0TocHpHp)

 End if 
 End if 
AmpVertexA0TocHpHp = AmpVertexA0TocHpHp -  AmpVertexIRdrA0TocHpHp! +  AmpVertexIRosA0TocHpHp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZA0TocHpHp=0._dp 
AmpVertexZA0TocHpHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZA0TocHpHp(gt2,:) = AmpWaveZA0TocHpHp(gt2,:)+ZRUZP(gt2,gt1)*AmpWaveA0TocHpHp(gt1,:) 
AmpVertexZA0TocHpHp(gt2,:)= AmpVertexZA0TocHpHp(gt2,:)+ZRUZP(gt2,gt1)*AmpVertexA0TocHpHp(gt1,:) 
 End Do 
End Do 
AmpWaveA0TocHpHp=AmpWaveZA0TocHpHp 
AmpVertexA0TocHpHp= AmpVertexZA0TocHpHp
! Final State 2 
AmpWaveZA0TocHpHp=0._dp 
AmpVertexZA0TocHpHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZA0TocHpHp(:,gt2) = AmpWaveZA0TocHpHp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveA0TocHpHp(:,gt1) 
AmpVertexZA0TocHpHp(:,gt2)= AmpVertexZA0TocHpHp(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexA0TocHpHp(:,gt1) 
 End Do 
End Do 
AmpWaveA0TocHpHp=AmpWaveZA0TocHpHp 
AmpVertexA0TocHpHp= AmpVertexZA0TocHpHp
End if
If (ShiftIRdiv) Then 
AmpVertexA0TocHpHp = AmpVertexA0TocHpHp  +  AmpVertexIRosA0TocHpHp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->conj[Hp] Hp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumA0TocHpHp = AmpTreeA0TocHpHp 
 AmpSum2A0TocHpHp = AmpTreeA0TocHpHp + 2._dp*AmpWaveA0TocHpHp + 2._dp*AmpVertexA0TocHpHp  
Else 
 AmpSumA0TocHpHp = AmpTreeA0TocHpHp + AmpWaveA0TocHpHp + AmpVertexA0TocHpHp
 AmpSum2A0TocHpHp = AmpTreeA0TocHpHp + AmpWaveA0TocHpHp + AmpVertexA0TocHpHp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0TocHpHp = AmpTreeA0TocHpHp
 AmpSum2A0TocHpHp = AmpTreeA0TocHpHp 
End if 
gt1=1 
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MHpOS(gt2))+Abs(MHpOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MHp(gt2))+Abs(MHp(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2A0TocHpHp = AmpTreeA0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MHpOS(gt2),MHpOS(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MA0,MHp(gt2),MHp(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqA0TocHpHp(gt2, gt3) 
  AmpSum2A0TocHpHp = 2._dp*AmpWaveA0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MHpOS(gt2),MHpOS(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MA0,MHp(gt2),MHp(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqA0TocHpHp(gt2, gt3) 
  AmpSum2A0TocHpHp = 2._dp*AmpVertexA0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MHpOS(gt2),MHpOS(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MA0,MHp(gt2),MHp(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqA0TocHpHp(gt2, gt3) 
  AmpSum2A0TocHpHp = AmpTreeA0TocHpHp + 2._dp*AmpWaveA0TocHpHp + 2._dp*AmpVertexA0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MHpOS(gt2),MHpOS(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MA0,MHp(gt2),MHp(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqA0TocHpHp(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2A0TocHpHp = AmpTreeA0TocHpHp
  Call SquareAmp_StoSS(MA0OS,MHpOS(gt2),MHpOS(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
  AmpSqTreeA0TocHpHp(gt2, gt3) = AmpSqA0TocHpHp(gt2, gt3)  
  AmpSum2A0TocHpHp = + 2._dp*AmpWaveA0TocHpHp + 2._dp*AmpVertexA0TocHpHp
  Call SquareAmp_StoSS(MA0OS,MHpOS(gt2),MHpOS(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
  AmpSqA0TocHpHp(gt2, gt3) = AmpSqA0TocHpHp(gt2, gt3) + AmpSqTreeA0TocHpHp(gt2, gt3)  
Else  
  AmpSum2A0TocHpHp = AmpTreeA0TocHpHp
  Call SquareAmp_StoSS(MA0,MHp(gt2),MHp(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
  AmpSqTreeA0TocHpHp(gt2, gt3) = AmpSqA0TocHpHp(gt2, gt3)  
  AmpSum2A0TocHpHp = + 2._dp*AmpWaveA0TocHpHp + 2._dp*AmpVertexA0TocHpHp
  Call SquareAmp_StoSS(MA0,MHp(gt2),MHp(gt3),AmpSumA0TocHpHp(gt2, gt3),AmpSum2A0TocHpHp(gt2, gt3),AmpSqA0TocHpHp(gt2, gt3)) 
  AmpSqA0TocHpHp(gt2, gt3) = AmpSqA0TocHpHp(gt2, gt3) + AmpSqTreeA0TocHpHp(gt2, gt3)  
End if  
Else  
  AmpSqA0TocHpHp(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0TocHpHp(gt2, gt3).eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MHpOS(gt2),MHpOS(gt3),helfactor*AmpSqA0TocHpHp(gt2, gt3))
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MHp(gt2),MHp(gt3),helfactor*AmpSqA0TocHpHp(gt2, gt3))
End if 
If ((Abs(MRPA0TocHpHp(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGA0TocHpHp(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPA0TocHpHp(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGA0TocHpHp(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPA0TocHpHp(gt2, gt3) + MRGA0TocHpHp(gt2, gt3)) 
  gP1LA0(gt1,i4) = gP1LA0(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPA0TocHpHp(gt2, gt3) + MRGA0TocHpHp(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LA0(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Hp Conjg(VWp)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_A0ToHpcVWp(cplA0HpcVWp,MA0,MHp,MVWp,MA02,MHp2,             & 
& MVWp2,AmpTreeA0ToHpcVWp)

  Else 
Call Amplitude_Tree_Inert2_A0ToHpcVWp(ZcplA0HpcVWp,MA0,MHp,MVWp,MA02,MHp2,            & 
& MVWp2,AmpTreeA0ToHpcVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_A0ToHpcVWp(MLambda,em,gs,cplA0HpcVWp,MA0OS,MHpOS,              & 
& MVWpOS,MRPA0ToHpcVWp,MRGA0ToHpcVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_A0ToHpcVWp(MLambda,em,gs,ZcplA0HpcVWp,MA0OS,MHpOS,             & 
& MVWpOS,MRPA0ToHpcVWp,MRGA0ToHpcVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_A0ToHpcVWp(MLambda,em,gs,cplA0HpcVWp,MA0,MHp,MVWp,             & 
& MRPA0ToHpcVWp,MRGA0ToHpcVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_A0ToHpcVWp(MLambda,em,gs,ZcplA0HpcVWp,MA0,MHp,MVWp,            & 
& MRPA0ToHpcVWp,MRGA0ToHpcVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_A0ToHpcVWp(cplA0HpcVWp,ctcplA0HpcVWp,MA0,MA02,             & 
& MHp,MHp2,MVWp,MVWp2,ZfA0,ZfHp,ZfVWp,AmpWaveA0ToHpcVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,cplH0HpcVWp,       & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,     & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,               & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexA0ToHpcVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,         & 
& cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRdrA0ToHpcVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,             & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,GosZcplA0HpcHp,ZcplA0HpcVWp,         & 
& cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,    & 
& cplHpcHpVP,GosZcplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,           & 
& cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRosA0ToHpcVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,GZcplA0HpcHp,ZcplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,      & 
& cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,GZcplHpcVWpVP,              & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1,       & 
& cplA0HpcVWpVZ1,cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosA0ToHpcVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,             & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,GcplA0HpcHp,cplA0HpcVWp,             & 
& cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,    & 
& cplHpcHpVP,GcplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,              & 
& cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRosA0ToHpcVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,         & 
& cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosA0ToHpcVWp)

 End if 
 End if 
AmpVertexA0ToHpcVWp = AmpVertexA0ToHpcVWp -  AmpVertexIRdrA0ToHpcVWp! +  AmpVertexIRosA0ToHpcVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZA0ToHpcVWp=0._dp 
AmpVertexZA0ToHpcVWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZA0ToHpcVWp(:,gt2) = AmpWaveZA0ToHpcVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveA0ToHpcVWp(:,gt1) 
AmpVertexZA0ToHpcVWp(:,gt2)= AmpVertexZA0ToHpcVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexA0ToHpcVWp(:,gt1) 
 End Do 
End Do 
AmpWaveA0ToHpcVWp=AmpWaveZA0ToHpcVWp 
AmpVertexA0ToHpcVWp= AmpVertexZA0ToHpcVWp
End if
If (ShiftIRdiv) Then 
AmpVertexA0ToHpcVWp = AmpVertexA0ToHpcVWp  +  AmpVertexIRosA0ToHpcVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->Hp conj[VWp] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumA0ToHpcVWp = AmpTreeA0ToHpcVWp 
 AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp + 2._dp*AmpWaveA0ToHpcVWp + 2._dp*AmpVertexA0ToHpcVWp  
Else 
 AmpSumA0ToHpcVWp = AmpTreeA0ToHpcVWp + AmpWaveA0ToHpcVWp + AmpVertexA0ToHpcVWp
 AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp + AmpWaveA0ToHpcVWp + AmpVertexA0ToHpcVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToHpcVWp = AmpTreeA0ToHpcVWp
 AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp 
End if 
gt1=1 
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MHpOS(gt2))+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MHp(gt2))+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2 
  AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MHpOS(gt2),MVWpOS,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MA0,MHp(gt2),MVWp,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqA0ToHpcVWp(gt2) 
  AmpSum2A0ToHpcVWp = 2._dp*AmpWaveA0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MHpOS(gt2),MVWpOS,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MA0,MHp(gt2),MVWp,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqA0ToHpcVWp(gt2) 
  AmpSum2A0ToHpcVWp = 2._dp*AmpVertexA0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MHpOS(gt2),MVWpOS,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MA0,MHp(gt2),MVWp,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqA0ToHpcVWp(gt2) 
  AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp + 2._dp*AmpWaveA0ToHpcVWp + 2._dp*AmpVertexA0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MHpOS(gt2),MVWpOS,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MA0,MHp(gt2),MVWp,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqA0ToHpcVWp(gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp
  Call SquareAmp_StoSV(MA0OS,MHpOS(gt2),MVWpOS,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
  AmpSqTreeA0ToHpcVWp(gt2) = AmpSqA0ToHpcVWp(gt2)  
  AmpSum2A0ToHpcVWp = + 2._dp*AmpWaveA0ToHpcVWp + 2._dp*AmpVertexA0ToHpcVWp
  Call SquareAmp_StoSV(MA0OS,MHpOS(gt2),MVWpOS,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
  AmpSqA0ToHpcVWp(gt2) = AmpSqA0ToHpcVWp(gt2) + AmpSqTreeA0ToHpcVWp(gt2)  
Else  
  AmpSum2A0ToHpcVWp = AmpTreeA0ToHpcVWp
  Call SquareAmp_StoSV(MA0,MHp(gt2),MVWp,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
  AmpSqTreeA0ToHpcVWp(gt2) = AmpSqA0ToHpcVWp(gt2)  
  AmpSum2A0ToHpcVWp = + 2._dp*AmpWaveA0ToHpcVWp + 2._dp*AmpVertexA0ToHpcVWp
  Call SquareAmp_StoSV(MA0,MHp(gt2),MVWp,AmpSumA0ToHpcVWp(:,gt2),AmpSum2A0ToHpcVWp(:,gt2),AmpSqA0ToHpcVWp(gt2)) 
  AmpSqA0ToHpcVWp(gt2) = AmpSqA0ToHpcVWp(gt2) + AmpSqTreeA0ToHpcVWp(gt2)  
End if  
Else  
  AmpSqA0ToHpcVWp(gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToHpcVWp(gt2).eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 2._dp*GammaTPS(MA0OS,MHpOS(gt2),MVWpOS,helfactor*AmpSqA0ToHpcVWp(gt2))
Else 
  gP1LA0(gt1,i4) = 2._dp*GammaTPS(MA0,MHp(gt2),MVWp,helfactor*AmpSqA0ToHpcVWp(gt2))
End if 
If ((Abs(MRPA0ToHpcVWp(gt2)).gt.1.0E-20_dp).or.(Abs(MRGA0ToHpcVWp(gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPA0ToHpcVWp(gt2)).gt.1.0E-20_dp).or.(Abs(MRGA0ToHpcVWp(gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPA0ToHpcVWp(gt2) + MRGA0ToHpcVWp(gt2)) 
  gP1LA0(gt1,i4) = gP1LA0(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPA0ToHpcVWp(gt2) + MRGA0ToHpcVWp(gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LA0(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
isave = i4 
End If 
!---------------- 
! A0 A0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToA0A0(MA0OS,MHpOS,MVWpOS,MA02OS,MHp2OS,               & 
& MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplA0A0HpcHp1,AmpVertexA0ToA0A0)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToA0A0(MA0OS,MHpOS,MVWpOS,MA02OS,MHp2OS,               & 
& MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplA0A0HpcHp1,AmpVertexA0ToA0A0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToA0A0(MA0,MHp,MVWp,MA02,MHp2,MVWp2,cplA0HpcHp,        & 
& cplA0HpcVWp,cplA0cHpVWp,cplA0A0HpcHp1,AmpVertexA0ToA0A0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->A0 A0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToA0A0 = 0._dp 
 AmpSum2A0ToA0A0 = 0._dp  
Else 
 AmpSumA0ToA0A0 = AmpVertexA0ToA0A0 + AmpWaveA0ToA0A0
 AmpSum2A0ToA0A0 = AmpVertexA0ToA0A0 + AmpWaveA0ToA0A0 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MA0OS)+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MA0)+Abs(MA0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MA0OS,MA0OS,AmpSumA0ToA0A0,AmpSum2A0ToA0A0,AmpSqA0ToA0A0) 
Else  
  Call SquareAmp_StoSS(MA0,MA0,MA0,AmpSumA0ToA0A0,AmpSum2A0ToA0A0,AmpSqA0ToA0A0) 
End if  
Else  
  AmpSqA0ToA0A0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToA0A0.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp/2._dp*GammaTPS(MA0OS,MA0OS,MA0OS,helfactor*AmpSqA0ToA0A0)
Else 
  gP1LA0(gt1,i4) = 1._dp/2._dp*GammaTPS(MA0,MA0,MA0,helfactor*AmpSqA0ToA0A0)
End if 
If ((Abs(MRPA0ToA0A0).gt.1.0E-20_dp).or.(Abs(MRGA0ToA0A0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! A0 H0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToA0H0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplA0A0HpcHp1,AmpVertexA0ToA0H0)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToA0H0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplA0A0HpcHp1,AmpVertexA0ToA0H0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToA0H0(MA0,MH0,MHp,MVWp,MA02,MH02,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplA0A0HpcHp1,   & 
& AmpVertexA0ToA0H0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->A0 H0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToA0H0 = 0._dp 
 AmpSum2A0ToA0H0 = 0._dp  
Else 
 AmpSumA0ToA0H0 = AmpVertexA0ToA0H0 + AmpWaveA0ToA0H0
 AmpSum2A0ToA0H0 = AmpVertexA0ToA0H0 + AmpWaveA0ToA0H0 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MA0OS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MA0)+Abs(MH0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MA0OS,MH0OS,AmpSumA0ToA0H0,AmpSum2A0ToA0H0,AmpSqA0ToA0H0) 
Else  
  Call SquareAmp_StoSS(MA0,MA0,MH0,AmpSumA0ToA0H0,AmpSum2A0ToA0H0,AmpSqA0ToA0H0) 
End if  
Else  
  AmpSqA0ToA0H0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToA0H0.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MA0OS,MH0OS,helfactor*AmpSqA0ToA0H0)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MA0,MH0,helfactor*AmpSqA0ToA0H0)
End if 
If ((Abs(MRPA0ToA0H0).gt.1.0E-20_dp).or.(Abs(MRGA0ToA0H0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! A0 VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToA0VP(MA0OS,MHpOS,MVP,MVWpOS,MA02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,AmpVertexA0ToA0VP)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToA0VP(MA0OS,MHpOS,MVP,MVWpOS,MA02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,AmpVertexA0ToA0VP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToA0VP(MA0,MHp,MVP,MVWp,MA02,MHp2,MVP2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,    & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,AmpVertexA0ToA0VP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->A0 VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToA0VP = 0._dp 
 AmpSum2A0ToA0VP = 0._dp  
Else 
 AmpSumA0ToA0VP = AmpVertexA0ToA0VP + AmpWaveA0ToA0VP
 AmpSum2A0ToA0VP = AmpVertexA0ToA0VP + AmpWaveA0ToA0VP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MA0OS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MA0)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MA0OS,0._dp,AmpSumA0ToA0VP(:),AmpSum2A0ToA0VP(:),AmpSqA0ToA0VP) 
Else  
  Call SquareAmp_StoSV(MA0,MA0,MVP,AmpSumA0ToA0VP(:),AmpSum2A0ToA0VP(:),AmpSqA0ToA0VP) 
End if  
Else  
  AmpSqA0ToA0VP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToA0VP.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MA0OS,0._dp,helfactor*AmpSqA0ToA0VP)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MA0,MVP,helfactor*AmpSqA0ToA0VP)
End if 
If ((Abs(MRPA0ToA0VP).gt.1.0E-20_dp).or.(Abs(MRGA0ToA0VP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! A0 VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToA0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,MVWpOS,           & 
& MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,cplA0A0hh,           & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,            & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,              & 
& cplA0cHpVWpVZ1,AmpVertexA0ToA0VZ)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToA0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,MVWpOS,           & 
& MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,cplA0A0hh,           & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,            & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,              & 
& cplA0cHpVWpVZ1,AmpVertexA0ToA0VZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,         & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,AmpVertexA0ToA0VZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->A0 VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToA0VZ = 0._dp 
 AmpSum2A0ToA0VZ = 0._dp  
Else 
 AmpSumA0ToA0VZ = AmpVertexA0ToA0VZ + AmpWaveA0ToA0VZ
 AmpSum2A0ToA0VZ = AmpVertexA0ToA0VZ + AmpWaveA0ToA0VZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MA0OS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MA0)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MA0OS,MVZOS,AmpSumA0ToA0VZ(:),AmpSum2A0ToA0VZ(:),AmpSqA0ToA0VZ) 
Else  
  Call SquareAmp_StoSV(MA0,MA0,MVZ,AmpSumA0ToA0VZ(:),AmpSum2A0ToA0VZ(:),AmpSqA0ToA0VZ) 
End if  
Else  
  AmpSqA0ToA0VZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToA0VZ.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MA0OS,MVZOS,helfactor*AmpSqA0ToA0VZ)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MA0,MVZ,helfactor*AmpSqA0ToA0VZ)
End if 
If ((Abs(MRPA0ToA0VZ).gt.1.0E-20_dp).or.(Abs(MRGA0ToA0VZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! Fd bar(Fd)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToFdcFd(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,         & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,           & 
& cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,         & 
& cplcFdFucVWpR,AmpVertexA0ToFdcFd)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToFdcFd(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,         & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,           & 
& cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,         & 
& cplcFdFucVWpR,AmpVertexA0ToFdcFd)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToFdcFd(MA0,MFd,MFu,MHp,MVWp,MA02,MFd2,MFu2,           & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,    & 
& cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,AmpVertexA0ToFdcFd)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->Fd bar[Fd] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToFdcFd = 0._dp 
 AmpSum2A0ToFdcFd = 0._dp  
Else 
 AmpSumA0ToFdcFd = AmpVertexA0ToFdcFd + AmpWaveA0ToFdcFd
 AmpSum2A0ToFdcFd = AmpVertexA0ToFdcFd + AmpWaveA0ToFdcFd 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MFdOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MFd(gt2))+Abs(MFd(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MA0OS,MFdOS(gt2),MFdOS(gt3),AmpSumA0ToFdcFd(:,gt2, gt3),AmpSum2A0ToFdcFd(:,gt2, gt3),AmpSqA0ToFdcFd(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MA0,MFd(gt2),MFd(gt3),AmpSumA0ToFdcFd(:,gt2, gt3),AmpSum2A0ToFdcFd(:,gt2, gt3),AmpSqA0ToFdcFd(gt2, gt3)) 
End if  
Else  
  AmpSqA0ToFdcFd(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqA0ToFdcFd(gt2, gt3).eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 3._dp*GammaTPS(MA0OS,MFdOS(gt2),MFdOS(gt3),helfactor*AmpSqA0ToFdcFd(gt2, gt3))
Else 
  gP1LA0(gt1,i4) = 3._dp*GammaTPS(MA0,MFd(gt2),MFd(gt3),helfactor*AmpSqA0ToFdcFd(gt2, gt3))
End if 
If ((Abs(MRPA0ToFdcFd(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGA0ToFdcFd(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

    End do
  End do
isave = i4 
!---------------- 
! Fe bar(Fe)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToFecFe(MA0OS,MFeOS,MHpOS,MVWpOS,MA02OS,               & 
& MFe2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,      & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& AmpVertexA0ToFecFe)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToFecFe(MA0OS,MFeOS,MHpOS,MVWpOS,MA02OS,               & 
& MFe2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,      & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& AmpVertexA0ToFecFe)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToFecFe(MA0,MFe,MHp,MVWp,MA02,MFe2,MHp2,               & 
& MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,         & 
& cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,AmpVertexA0ToFecFe)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->Fe bar[Fe] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToFecFe = 0._dp 
 AmpSum2A0ToFecFe = 0._dp  
Else 
 AmpSumA0ToFecFe = AmpVertexA0ToFecFe + AmpWaveA0ToFecFe
 AmpSum2A0ToFecFe = AmpVertexA0ToFecFe + AmpWaveA0ToFecFe 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MFeOS(gt2))+Abs(MFeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MFe(gt2))+Abs(MFe(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MA0OS,MFeOS(gt2),MFeOS(gt3),AmpSumA0ToFecFe(:,gt2, gt3),AmpSum2A0ToFecFe(:,gt2, gt3),AmpSqA0ToFecFe(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MA0,MFe(gt2),MFe(gt3),AmpSumA0ToFecFe(:,gt2, gt3),AmpSum2A0ToFecFe(:,gt2, gt3),AmpSqA0ToFecFe(gt2, gt3)) 
End if  
Else  
  AmpSqA0ToFecFe(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqA0ToFecFe(gt2, gt3).eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MFeOS(gt2),MFeOS(gt3),helfactor*AmpSqA0ToFecFe(gt2, gt3))
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MFe(gt2),MFe(gt3),helfactor*AmpSqA0ToFecFe(gt2, gt3))
End if 
If ((Abs(MRPA0ToFecFe(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGA0ToFecFe(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

    End do
  End do
isave = i4 
!---------------- 
! Fu bar(Fu)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToFucFu(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,         & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,           & 
& cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,         & 
& cplcFdFucVWpR,AmpVertexA0ToFucFu)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToFucFu(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,         & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,           & 
& cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,         & 
& cplcFdFucVWpR,AmpVertexA0ToFucFu)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToFucFu(MA0,MFd,MFu,MHp,MVWp,MA02,MFd2,MFu2,           & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,    & 
& cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,AmpVertexA0ToFucFu)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->Fu bar[Fu] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToFucFu = 0._dp 
 AmpSum2A0ToFucFu = 0._dp  
Else 
 AmpSumA0ToFucFu = AmpVertexA0ToFucFu + AmpWaveA0ToFucFu
 AmpSum2A0ToFucFu = AmpVertexA0ToFucFu + AmpWaveA0ToFucFu 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MFuOS(gt2))+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MFu(gt2))+Abs(MFu(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MA0OS,MFuOS(gt2),MFuOS(gt3),AmpSumA0ToFucFu(:,gt2, gt3),AmpSum2A0ToFucFu(:,gt2, gt3),AmpSqA0ToFucFu(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MA0,MFu(gt2),MFu(gt3),AmpSumA0ToFucFu(:,gt2, gt3),AmpSum2A0ToFucFu(:,gt2, gt3),AmpSqA0ToFucFu(gt2, gt3)) 
End if  
Else  
  AmpSqA0ToFucFu(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqA0ToFucFu(gt2, gt3).eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 3._dp*GammaTPS(MA0OS,MFuOS(gt2),MFuOS(gt3),helfactor*AmpSqA0ToFucFu(gt2, gt3))
Else 
  gP1LA0(gt1,i4) = 3._dp*GammaTPS(MA0,MFu(gt2),MFu(gt3),helfactor*AmpSqA0ToFucFu(gt2, gt3))
End if 
If ((Abs(MRPA0ToFucFu(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGA0ToFucFu(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

    End do
  End do
isave = i4 
!---------------- 
! Fv bar(Fv)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToFvcFv(MA0OS,MFeOS,MHpOS,MVWpOS,MA02OS,               & 
& MFe2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,      & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& AmpVertexA0ToFvcFv)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToFvcFv(MA0OS,MFeOS,MHpOS,MVWpOS,MA02OS,               & 
& MFe2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,      & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& AmpVertexA0ToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToFvcFv(MA0,MFe,MHp,MVWp,MA02,MFe2,MHp2,               & 
& MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,         & 
& cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,AmpVertexA0ToFvcFv)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->Fv bar[Fv] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToFvcFv = 0._dp 
 AmpSum2A0ToFvcFv = 0._dp  
Else 
 AmpSumA0ToFvcFv = AmpVertexA0ToFvcFv + AmpWaveA0ToFvcFv
 AmpSum2A0ToFvcFv = AmpVertexA0ToFvcFv + AmpWaveA0ToFvcFv 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(0._dp)+Abs(0._dp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MA0OS,0._dp,0._dp,AmpSumA0ToFvcFv(:,gt2, gt3),AmpSum2A0ToFvcFv(:,gt2, gt3),AmpSqA0ToFvcFv(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MA0,0._dp,0._dp,AmpSumA0ToFvcFv(:,gt2, gt3),AmpSum2A0ToFvcFv(:,gt2, gt3),AmpSqA0ToFvcFv(gt2, gt3)) 
End if  
Else  
  AmpSqA0ToFvcFv(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqA0ToFvcFv(gt2, gt3).eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,0._dp,0._dp,helfactor*AmpSqA0ToFvcFv(gt2, gt3))
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,0._dp,0._dp,helfactor*AmpSqA0ToFvcFv(gt2, gt3))
End if 
If ((Abs(MRPA0ToFvcFv(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGA0ToFvcFv(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

    End do
  End do
isave = i4 
!---------------- 
! H0 H0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToH0H0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexA0ToH0H0)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToH0H0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexA0ToH0H0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToH0H0(MA0,MH0,MHp,MVWp,MA02,MH02,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplH0H0HpcHp1,   & 
& AmpVertexA0ToH0H0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->H0 H0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToH0H0 = 0._dp 
 AmpSum2A0ToH0H0 = 0._dp  
Else 
 AmpSumA0ToH0H0 = AmpVertexA0ToH0H0 + AmpWaveA0ToH0H0
 AmpSum2A0ToH0H0 = AmpVertexA0ToH0H0 + AmpWaveA0ToH0H0 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MH0OS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MH0)+Abs(MH0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MH0OS,MH0OS,AmpSumA0ToH0H0,AmpSum2A0ToH0H0,AmpSqA0ToH0H0) 
Else  
  Call SquareAmp_StoSS(MA0,MH0,MH0,AmpSumA0ToH0H0,AmpSum2A0ToH0H0,AmpSqA0ToH0H0) 
End if  
Else  
  AmpSqA0ToH0H0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToH0H0.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp/2._dp*GammaTPS(MA0OS,MH0OS,MH0OS,helfactor*AmpSqA0ToH0H0)
Else 
  gP1LA0(gt1,i4) = 1._dp/2._dp*GammaTPS(MA0,MH0,MH0,helfactor*AmpSqA0ToH0H0)
End if 
If ((Abs(MRPA0ToH0H0).gt.1.0E-20_dp).or.(Abs(MRGA0ToH0H0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! H0 VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_A0ToH0VP(cplA0H0VZ,ctcplA0H0VZ,MA0OS,MA02OS,               & 
& MH0OS,MH02OS,MVP,MVP2,MVZOS,MVZ2OS,ZfA0,ZfH0,ZfVP,ZfVZVP,AmpWaveA0ToH0VP)

 Else 
Call Amplitude_WAVE_Inert2_A0ToH0VP(cplA0H0VZ,ctcplA0H0VZ,MA0OS,MA02OS,               & 
& MH0OS,MH02OS,MVP,MVP2,MVZOS,MVZ2OS,ZfA0,ZfH0,ZfVP,ZfVZVP,AmpWaveA0ToH0VP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToH0VP(MA0OS,MH0OS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& MH02OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,              & 
& cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,               & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexA0ToH0VP)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToH0VP(MA0OS,MH0OS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& MH02OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,              & 
& cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,               & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexA0ToH0VP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_A0ToH0VP(cplA0H0VZ,ctcplA0H0VZ,MA0,MA02,MH0,               & 
& MH02,MVP,MVP2,MVZ,MVZ2,ZfA0,ZfH0,ZfVP,ZfVZVP,AmpWaveA0ToH0VP)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToH0VP(MA0,MH0,MHp,MVP,MVWp,MA02,MH02,MHp2,            & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,      & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,         & 
& cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexA0ToH0VP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->H0 VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToH0VP = 0._dp 
 AmpSum2A0ToH0VP = 0._dp  
Else 
 AmpSumA0ToH0VP = AmpVertexA0ToH0VP + AmpWaveA0ToH0VP
 AmpSum2A0ToH0VP = AmpVertexA0ToH0VP + AmpWaveA0ToH0VP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MH0OS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MH0)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MH0OS,0._dp,AmpSumA0ToH0VP(:),AmpSum2A0ToH0VP(:),AmpSqA0ToH0VP) 
Else  
  Call SquareAmp_StoSV(MA0,MH0,MVP,AmpSumA0ToH0VP(:),AmpSum2A0ToH0VP(:),AmpSqA0ToH0VP) 
End if  
Else  
  AmpSqA0ToH0VP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToH0VP.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MH0OS,0._dp,helfactor*AmpSqA0ToH0VP)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MH0,MVP,helfactor*AmpSqA0ToH0VP)
End if 
If ((Abs(MRPA0ToH0VP).gt.1.0E-20_dp).or.(Abs(MRGA0ToH0VP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! hh hh
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0Tohhhh(MA0OS,MhhOS,MHpOS,MVWpOS,MA02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0hhHpcHp1,cplhhhhHpcHp1,AmpVertexA0Tohhhh)

 Else 
Call Amplitude_VERTEX_Inert2_A0Tohhhh(MA0OS,MhhOS,MHpOS,MVWpOS,MA02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0hhHpcHp1,cplhhhhHpcHp1,AmpVertexA0Tohhhh)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0Tohhhh(MA0,Mhh,MHp,MVWp,MA02,Mhh2,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,    & 
& cplA0hhHpcHp1,cplhhhhHpcHp1,AmpVertexA0Tohhhh)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->hh hh -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0Tohhhh = 0._dp 
 AmpSum2A0Tohhhh = 0._dp  
Else 
 AmpSumA0Tohhhh = AmpVertexA0Tohhhh + AmpWaveA0Tohhhh
 AmpSum2A0Tohhhh = AmpVertexA0Tohhhh + AmpWaveA0Tohhhh 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MhhOS)+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(Mhh)+Abs(Mhh))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MA0OS,MhhOS,MhhOS,AmpSumA0Tohhhh,AmpSum2A0Tohhhh,AmpSqA0Tohhhh) 
Else  
  Call SquareAmp_StoSS(MA0,Mhh,Mhh,AmpSumA0Tohhhh,AmpSum2A0Tohhhh,AmpSqA0Tohhhh) 
End if  
Else  
  AmpSqA0Tohhhh = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0Tohhhh.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp/2._dp*GammaTPS(MA0OS,MhhOS,MhhOS,helfactor*AmpSqA0Tohhhh)
Else 
  gP1LA0(gt1,i4) = 1._dp/2._dp*GammaTPS(MA0,Mhh,Mhh,helfactor*AmpSqA0Tohhhh)
End if 
If ((Abs(MRPA0Tohhhh).gt.1.0E-20_dp).or.(Abs(MRGA0Tohhhh).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! hh VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0TohhVP(MA0OS,MhhOS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexA0TohhVP)

 Else 
Call Amplitude_VERTEX_Inert2_A0TohhVP(MA0OS,MhhOS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexA0TohhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0TohhVP(MA0,Mhh,MHp,MVP,MVWp,MA02,Mhh2,MHp2,            & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,           & 
& cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,AmpVertexA0TohhVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->hh VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0TohhVP = 0._dp 
 AmpSum2A0TohhVP = 0._dp  
Else 
 AmpSumA0TohhVP = AmpVertexA0TohhVP + AmpWaveA0TohhVP
 AmpSum2A0TohhVP = AmpVertexA0TohhVP + AmpWaveA0TohhVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MhhOS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(Mhh)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MhhOS,0._dp,AmpSumA0TohhVP(:),AmpSum2A0TohhVP(:),AmpSqA0TohhVP) 
Else  
  Call SquareAmp_StoSV(MA0,Mhh,MVP,AmpSumA0TohhVP(:),AmpSum2A0TohhVP(:),AmpSqA0TohhVP) 
End if  
Else  
  AmpSqA0TohhVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0TohhVP.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MhhOS,0._dp,helfactor*AmpSqA0TohhVP)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,Mhh,MVP,helfactor*AmpSqA0TohhVP)
End if 
If ((Abs(MRPA0TohhVP).gt.1.0E-20_dp).or.(Abs(MRGA0TohhVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! hh VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0TohhVZ(MA0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexA0TohhVZ)

 Else 
Call Amplitude_VERTEX_Inert2_A0TohhVZ(MA0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexA0TohhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0TohhVZ(MA0,Mhh,MHp,MVWp,MVZ,MA02,Mhh2,MHp2,            & 
& MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,           & 
& cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexA0TohhVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->hh VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0TohhVZ = 0._dp 
 AmpSum2A0TohhVZ = 0._dp  
Else 
 AmpSumA0TohhVZ = AmpVertexA0TohhVZ + AmpWaveA0TohhVZ
 AmpSum2A0TohhVZ = AmpVertexA0TohhVZ + AmpWaveA0TohhVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MhhOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(Mhh)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MA0OS,MhhOS,MVZOS,AmpSumA0TohhVZ(:),AmpSum2A0TohhVZ(:),AmpSqA0TohhVZ) 
Else  
  Call SquareAmp_StoSV(MA0,Mhh,MVZ,AmpSumA0TohhVZ(:),AmpSum2A0TohhVZ(:),AmpSqA0TohhVZ) 
End if  
Else  
  AmpSqA0TohhVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0TohhVZ.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MhhOS,MVZOS,helfactor*AmpSqA0TohhVZ)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,Mhh,MVZ,helfactor*AmpSqA0TohhVZ)
End if 
If ((Abs(MRPA0TohhVZ).gt.1.0E-20_dp).or.(Abs(MRGA0TohhVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VP VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToVPVP(MA0OS,MHpOS,MVP,MVWpOS,MA02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplHpcHpVPVP1,AmpVertexA0ToVPVP)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToVPVP(MA0OS,MHpOS,MVP,MVWpOS,MA02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplHpcHpVPVP1,AmpVertexA0ToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToVPVP(MA0,MHp,MVP,MVWp,MA02,MHp2,MVP2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,    & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplHpcHpVPVP1,AmpVertexA0ToVPVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->VP VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToVPVP = 0._dp 
 AmpSum2A0ToVPVP = 0._dp  
Else 
 AmpSumA0ToVPVP = AmpVertexA0ToVPVP + AmpWaveA0ToVPVP
 AmpSum2A0ToVPVP = AmpVertexA0ToVPVP + AmpWaveA0ToVPVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MVP)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MA0OS,0._dp,0._dp,AmpSumA0ToVPVP(:),AmpSum2A0ToVPVP(:),AmpSqA0ToVPVP) 
Else  
  Call SquareAmp_StoVV(MA0,MVP,MVP,AmpSumA0ToVPVP(:),AmpSum2A0ToVPVP(:),AmpSqA0ToVPVP) 
End if  
Else  
  AmpSqA0ToVPVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToVPVP.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,0._dp,0._dp,helfactor*AmpSqA0ToVPVP)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MVP,MVP,helfactor*AmpSqA0ToVPVP)
End if 
If ((Abs(MRPA0ToVPVP).gt.1.0E-20_dp).or.(Abs(MRGA0ToVPVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VP VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToVPVZ(MA0OS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,            & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,              & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,              & 
& cplHpcHpVPVZ1,AmpVertexA0ToVPVZ)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToVPVZ(MA0OS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,            & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,              & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,              & 
& cplHpcHpVPVZ1,AmpVertexA0ToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToVPVZ(MA0,MHp,MVP,MVWp,MVZ,MA02,MHp2,MVP2,            & 
& MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVP1,          & 
& cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplHpcHpVPVZ1,AmpVertexA0ToVPVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->VP VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToVPVZ = 0._dp 
 AmpSum2A0ToVPVZ = 0._dp  
Else 
 AmpSumA0ToVPVZ = AmpVertexA0ToVPVZ + AmpWaveA0ToVPVZ
 AmpSum2A0ToVPVZ = AmpVertexA0ToVPVZ + AmpWaveA0ToVPVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(0.)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MVP)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MA0OS,0._dp,MVZOS,AmpSumA0ToVPVZ(:),AmpSum2A0ToVPVZ(:),AmpSqA0ToVPVZ) 
Else  
  Call SquareAmp_StoVV(MA0,MVP,MVZ,AmpSumA0ToVPVZ(:),AmpSum2A0ToVPVZ(:),AmpSqA0ToVPVZ) 
End if  
Else  
  AmpSqA0ToVPVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToVPVZ.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 2._dp*GammaTPS(MA0OS,0._dp,MVZOS,helfactor*AmpSqA0ToVPVZ)
Else 
  gP1LA0(gt1,i4) = 2._dp*GammaTPS(MA0,MVP,MVZ,helfactor*AmpSqA0ToVPVZ)
End if 
If ((Abs(MRPA0ToVPVZ).gt.1.0E-20_dp).or.(Abs(MRGA0ToVPVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VWp Conjg(VWp)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToVWpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,              & 
& cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,               & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,             & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,  & 
& cplHpcHpcVWpVWp1,AmpVertexA0ToVWpcVWp)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToVWpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,              & 
& cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,               & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,             & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,  & 
& cplHpcHpcVWpVWp1,AmpVertexA0ToVWpcVWp)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToVWpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,              & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,       & 
& cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexA0ToVWpcVWp)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->VWp conj[VWp] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToVWpcVWp = 0._dp 
 AmpSum2A0ToVWpcVWp = 0._dp  
Else 
 AmpSumA0ToVWpcVWp = AmpVertexA0ToVWpcVWp + AmpWaveA0ToVWpcVWp
 AmpSum2A0ToVWpcVWp = AmpVertexA0ToVWpcVWp + AmpWaveA0ToVWpcVWp 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MVWpOS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MVWp)+Abs(MVWp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MA0OS,MVWpOS,MVWpOS,AmpSumA0ToVWpcVWp(:),AmpSum2A0ToVWpcVWp(:),AmpSqA0ToVWpcVWp) 
Else  
  Call SquareAmp_StoVV(MA0,MVWp,MVWp,AmpSumA0ToVWpcVWp(:),AmpSum2A0ToVWpcVWp(:),AmpSqA0ToVWpcVWp) 
End if  
Else  
  AmpSqA0ToVWpcVWp = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToVWpcVWp.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 2._dp*GammaTPS(MA0OS,MVWpOS,MVWpOS,helfactor*AmpSqA0ToVWpcVWp)
Else 
  gP1LA0(gt1,i4) = 2._dp*GammaTPS(MA0,MVWp,MVWp,helfactor*AmpSqA0ToVWpcVWp)
End if 
If ((Abs(MRPA0ToVWpcVWp).gt.1.0E-20_dp).or.(Abs(MRGA0ToVWpcVWp).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VZ VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_A0ToVZVZ(MA0OS,MHpOS,MVWpOS,MVZOS,MA02OS,MHp2OS,         & 
& MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplHpcHpVZVZ1,AmpVertexA0ToVZVZ)

 Else 
Call Amplitude_VERTEX_Inert2_A0ToVZVZ(MA0OS,MHpOS,MVWpOS,MVZOS,MA02OS,MHp2OS,         & 
& MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplHpcHpVZVZ1,AmpVertexA0ToVZVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_A0ToVZVZ(MA0,MHp,MVWp,MVZ,MA02,MHp2,MVWp2,               & 
& MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,            & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplHpcHpVZVZ1,AmpVertexA0ToVZVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ A0->VZ VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumA0ToVZVZ = 0._dp 
 AmpSum2A0ToVZVZ = 0._dp  
Else 
 AmpSumA0ToVZVZ = AmpVertexA0ToVZVZ + AmpWaveA0ToVZVZ
 AmpSum2A0ToVZVZ = AmpVertexA0ToVZVZ + AmpWaveA0ToVZVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MA0OS).gt.(Abs(MVZOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MA0).gt.(Abs(MVZ)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MA0OS,MVZOS,MVZOS,AmpSumA0ToVZVZ(:),AmpSum2A0ToVZVZ(:),AmpSqA0ToVZVZ) 
Else  
  Call SquareAmp_StoVV(MA0,MVZ,MVZ,AmpSumA0ToVZVZ(:),AmpSum2A0ToVZVZ(:),AmpSqA0ToVZVZ) 
End if  
Else  
  AmpSqA0ToVZVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqA0ToVZVZ.eq.0._dp) Then 
  gP1LA0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0OS,MVZOS,MVZOS,helfactor*AmpSqA0ToVZVZ)
Else 
  gP1LA0(gt1,i4) = 1._dp*GammaTPS(MA0,MVZ,MVZ,helfactor*AmpSqA0ToVZVZ)
End if 
If ((Abs(MRPA0ToVZVZ).gt.1.0E-20_dp).or.(Abs(MRGA0ToVZVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LA0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
End Subroutine OneLoopDecay_A0

End Module Wrapper_OneLoopDecay_A0_Inert2
