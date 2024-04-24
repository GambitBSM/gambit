! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_H0_Inert2
Use Model_Data_Inert2 
Use Kinematics 
Use OneLoopDecay_H0_Inert2 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_H0(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,              & 
& MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,               & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Ye,Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,            & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hh,              & 
& cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0VZVZ1,cplA0cHpVPVWp1,cplA0cHpVWp,cplA0cHpVWpVZ1,     & 
& cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1,cplA0H0hh,cplA0H0hhhh1,              & 
& cplA0H0VZ,cplA0hhHpcHp1,cplA0HpcHp,cplA0HpcVWp,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,          & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcHpL,cplcFeFvcHpR,       & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,         & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcHpVPVWp,cplcHpVWpVZ,             & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplG0cHpVPVWp1,cplG0cHpVWp,cplG0cHpVWpVZ1,cplG0G0H0H01,      & 
& cplG0G0hh,cplG0G0HpcHp1,cplG0H0H0,cplG0H0H0hh1,cplG0H0HpcHp1,cplG0hhVZ,cplG0HpcVWp,    & 
& cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWp,cplH0cHpVWpVZ1,               & 
& cplH0H0cVWpVWp1,cplH0H0H0H01,cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0VZVZ1,        & 
& cplH0hhHpcHp1,cplH0HpcHp,cplH0HpcVWp,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplhhcHpVPVWp1,     & 
& cplhhcHpVWp,cplhhcHpVWpVZ1,cplhhcVWpVWp,cplhhhhhh,cplhhhhHpcHp1,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhVZVZ,cplHpcHpcVWpVWp1,cplHpcHpVP,       & 
& cplHpcHpVPVP1,cplHpcHpVPVZ1,cplHpcHpVZ,cplHpcHpVZVZ1,cplHpcVWpVP,cplHpcVWpVZ,          & 
& cplHpHpcHpcHp1,ctcplA0G0H0,ctcplA0H0hh,ctcplA0H0VZ,ctcplG0H0H0,ctcplH0H0hh,            & 
& ctcplH0HpcHp,ctcplH0HpcVWp,GcplcHpVPVWp,GcplH0HpcHp,GcplHpcVWpVP,GosZcplcHpVPVWp,      & 
& GosZcplH0HpcHp,GosZcplHpcVWpVP,GZcplcHpVPVWp,GZcplH0HpcHp,GZcplHpcVWpVP,               & 
& ZcplA0G0H0,ZcplA0H0hh,ZcplA0H0VZ,ZcplG0H0H0,ZcplH0H0hh,ZcplH0HpcHp,ZcplH0HpcVWp,       & 
& ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LH0)

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

Complex(dp),Intent(in) :: cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hh,cplA0A0hhhh1,              & 
& cplA0A0HpcHp1(2,2),cplA0A0VZVZ1,cplA0cHpVPVWp1(2),cplA0cHpVWp(2),cplA0cHpVWpVZ1(2),    & 
& cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),cplA0H0hh,cplA0H0hhhh1,         & 
& cplA0H0VZ,cplA0hhHpcHp1(2,2),cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0HpcVWpVP1(2),         & 
& cplA0HpcVWpVZ1(2),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),          & 
& cplcFdFucVWpR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),         & 
& cplcFeFvcVWpR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),            & 
& cplcFuFdVWpR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFvFeVWpL(3,3),             & 
& cplcFvFeVWpR(3,3),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,             & 
& cplG0cHpVPVWp1(2),cplG0cHpVWp(2),cplG0cHpVWpVZ1(2),cplG0G0H0H01,cplG0G0hh,             & 
& cplG0G0HpcHp1(2,2),cplG0H0H0,cplG0H0H0hh1,cplG0H0HpcHp1(2,2),cplG0hhVZ,cplG0HpcVWp(2), & 
& cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplH0cHpVPVWp1(2),cplH0cHpVWp(2),cplH0cHpVWpVZ1(2),& 
& cplH0H0cVWpVWp1,cplH0H0H0H01,cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),cplH0H0VZVZ1,   & 
& cplH0hhHpcHp1(2,2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2), & 
& cplhhcHpVPVWp1(2),cplhhcHpVWp(2),cplhhcHpVWpVZ1(2),cplhhcVWpVWp,cplhhhhhh,             & 
& cplhhhhHpcHp1(2,2),cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2), & 
& cplhhVZVZ,cplHpcHpcVWpVWp1(2,2),cplHpcHpVP(2,2),cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2), & 
& cplHpcHpVZ(2,2),cplHpcHpVZVZ1(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2),cplHpHpcHpcHp1(2,2,2,2),& 
& ctcplA0G0H0,ctcplA0H0hh,ctcplA0H0VZ,ctcplG0H0H0,ctcplH0H0hh,ctcplH0HpcHp(2,2),         & 
& ctcplH0HpcVWp(2),GcplcHpVPVWp(2),GcplH0HpcHp(2,2),GcplHpcVWpVP(2),GosZcplcHpVPVWp(2),  & 
& GosZcplH0HpcHp(2,2),GosZcplHpcVWpVP(2),GZcplcHpVPVWp(2),GZcplH0HpcHp(2,2),             & 
& GZcplHpcVWpVP(2),ZcplA0G0H0,ZcplA0H0hh,ZcplA0H0VZ,ZcplG0H0H0,ZcplH0H0hh,               & 
& ZcplH0HpcHp(2,2),ZcplH0HpcVWp(2)

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
Real(dp), Intent(out) :: gP1LH0(1,54) 
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
Real(dp) :: MRPH0TohhA0,MRGH0TohhA0, MRPZH0TohhA0,MRGZH0TohhA0 
Real(dp) :: MVPH0TohhA0 
Real(dp) :: RMsqTreeH0TohhA0,RMsqWaveH0TohhA0,RMsqVertexH0TohhA0 
Complex(dp) :: AmpTreeH0TohhA0,AmpWaveH0TohhA0=(0._dp,0._dp),AmpVertexH0TohhA0& 
 & ,AmpVertexIRosH0TohhA0,AmpVertexIRdrH0TohhA0, AmpSumH0TohhA0, AmpSum2H0TohhA0 
Complex(dp) :: AmpTreeZH0TohhA0,AmpWaveZH0TohhA0,AmpVertexZH0TohhA0 
Real(dp) :: AmpSqH0TohhA0,  AmpSqTreeH0TohhA0 
Real(dp) :: MRPH0ToA0VZ,MRGH0ToA0VZ, MRPZH0ToA0VZ,MRGZH0ToA0VZ 
Real(dp) :: MVPH0ToA0VZ 
Real(dp) :: RMsqTreeH0ToA0VZ,RMsqWaveH0ToA0VZ,RMsqVertexH0ToA0VZ 
Complex(dp) :: AmpTreeH0ToA0VZ(2),AmpWaveH0ToA0VZ(2)=(0._dp,0._dp),AmpVertexH0ToA0VZ(2)& 
 & ,AmpVertexIRosH0ToA0VZ(2),AmpVertexIRdrH0ToA0VZ(2), AmpSumH0ToA0VZ(2), AmpSum2H0ToA0VZ(2) 
Complex(dp) :: AmpTreeZH0ToA0VZ(2),AmpWaveZH0ToA0VZ(2),AmpVertexZH0ToA0VZ(2) 
Real(dp) :: AmpSqH0ToA0VZ,  AmpSqTreeH0ToA0VZ 
Real(dp) :: MRPH0TohhH0,MRGH0TohhH0, MRPZH0TohhH0,MRGZH0TohhH0 
Real(dp) :: MVPH0TohhH0 
Real(dp) :: RMsqTreeH0TohhH0,RMsqWaveH0TohhH0,RMsqVertexH0TohhH0 
Complex(dp) :: AmpTreeH0TohhH0,AmpWaveH0TohhH0=(0._dp,0._dp),AmpVertexH0TohhH0& 
 & ,AmpVertexIRosH0TohhH0,AmpVertexIRdrH0TohhH0, AmpSumH0TohhH0, AmpSum2H0TohhH0 
Complex(dp) :: AmpTreeZH0TohhH0,AmpWaveZH0TohhH0,AmpVertexZH0TohhH0 
Real(dp) :: AmpSqH0TohhH0,  AmpSqTreeH0TohhH0 
Real(dp) :: MRPH0TocHpHp(2,2),MRGH0TocHpHp(2,2), MRPZH0TocHpHp(2,2),MRGZH0TocHpHp(2,2) 
Real(dp) :: MVPH0TocHpHp(2,2) 
Real(dp) :: RMsqTreeH0TocHpHp(2,2),RMsqWaveH0TocHpHp(2,2),RMsqVertexH0TocHpHp(2,2) 
Complex(dp) :: AmpTreeH0TocHpHp(2,2),AmpWaveH0TocHpHp(2,2)=(0._dp,0._dp),AmpVertexH0TocHpHp(2,2)& 
 & ,AmpVertexIRosH0TocHpHp(2,2),AmpVertexIRdrH0TocHpHp(2,2), AmpSumH0TocHpHp(2,2), AmpSum2H0TocHpHp(2,2) 
Complex(dp) :: AmpTreeZH0TocHpHp(2,2),AmpWaveZH0TocHpHp(2,2),AmpVertexZH0TocHpHp(2,2) 
Real(dp) :: AmpSqH0TocHpHp(2,2),  AmpSqTreeH0TocHpHp(2,2) 
Real(dp) :: MRPH0ToHpcVWp(2),MRGH0ToHpcVWp(2), MRPZH0ToHpcVWp(2),MRGZH0ToHpcVWp(2) 
Real(dp) :: MVPH0ToHpcVWp(2) 
Real(dp) :: RMsqTreeH0ToHpcVWp(2),RMsqWaveH0ToHpcVWp(2),RMsqVertexH0ToHpcVWp(2) 
Complex(dp) :: AmpTreeH0ToHpcVWp(2,2),AmpWaveH0ToHpcVWp(2,2)=(0._dp,0._dp),AmpVertexH0ToHpcVWp(2,2)& 
 & ,AmpVertexIRosH0ToHpcVWp(2,2),AmpVertexIRdrH0ToHpcVWp(2,2), AmpSumH0ToHpcVWp(2,2), AmpSum2H0ToHpcVWp(2,2) 
Complex(dp) :: AmpTreeZH0ToHpcVWp(2,2),AmpWaveZH0ToHpcVWp(2,2),AmpVertexZH0ToHpcVWp(2,2) 
Real(dp) :: AmpSqH0ToHpcVWp(2),  AmpSqTreeH0ToHpcVWp(2) 
Real(dp) :: MRPH0ToA0A0,MRGH0ToA0A0, MRPZH0ToA0A0,MRGZH0ToA0A0 
Real(dp) :: MVPH0ToA0A0 
Real(dp) :: RMsqTreeH0ToA0A0,RMsqWaveH0ToA0A0,RMsqVertexH0ToA0A0 
Complex(dp) :: AmpTreeH0ToA0A0,AmpWaveH0ToA0A0=(0._dp,0._dp),AmpVertexH0ToA0A0& 
 & ,AmpVertexIRosH0ToA0A0,AmpVertexIRdrH0ToA0A0, AmpSumH0ToA0A0, AmpSum2H0ToA0A0 
Complex(dp) :: AmpTreeZH0ToA0A0,AmpWaveZH0ToA0A0,AmpVertexZH0ToA0A0 
Real(dp) :: AmpSqH0ToA0A0,  AmpSqTreeH0ToA0A0 
Real(dp) :: MRPH0ToA0H0,MRGH0ToA0H0, MRPZH0ToA0H0,MRGZH0ToA0H0 
Real(dp) :: MVPH0ToA0H0 
Real(dp) :: RMsqTreeH0ToA0H0,RMsqWaveH0ToA0H0,RMsqVertexH0ToA0H0 
Complex(dp) :: AmpTreeH0ToA0H0,AmpWaveH0ToA0H0=(0._dp,0._dp),AmpVertexH0ToA0H0& 
 & ,AmpVertexIRosH0ToA0H0,AmpVertexIRdrH0ToA0H0, AmpSumH0ToA0H0, AmpSum2H0ToA0H0 
Complex(dp) :: AmpTreeZH0ToA0H0,AmpWaveZH0ToA0H0,AmpVertexZH0ToA0H0 
Real(dp) :: AmpSqH0ToA0H0,  AmpSqTreeH0ToA0H0 
Real(dp) :: MRPH0ToA0VP,MRGH0ToA0VP, MRPZH0ToA0VP,MRGZH0ToA0VP 
Real(dp) :: MVPH0ToA0VP 
Real(dp) :: RMsqTreeH0ToA0VP,RMsqWaveH0ToA0VP,RMsqVertexH0ToA0VP 
Complex(dp) :: AmpTreeH0ToA0VP(2),AmpWaveH0ToA0VP(2)=(0._dp,0._dp),AmpVertexH0ToA0VP(2)& 
 & ,AmpVertexIRosH0ToA0VP(2),AmpVertexIRdrH0ToA0VP(2), AmpSumH0ToA0VP(2), AmpSum2H0ToA0VP(2) 
Complex(dp) :: AmpTreeZH0ToA0VP(2),AmpWaveZH0ToA0VP(2),AmpVertexZH0ToA0VP(2) 
Real(dp) :: AmpSqH0ToA0VP,  AmpSqTreeH0ToA0VP 
Real(dp) :: MRPH0ToFdcFd(3,3),MRGH0ToFdcFd(3,3), MRPZH0ToFdcFd(3,3),MRGZH0ToFdcFd(3,3) 
Real(dp) :: MVPH0ToFdcFd(3,3) 
Real(dp) :: RMsqTreeH0ToFdcFd(3,3),RMsqWaveH0ToFdcFd(3,3),RMsqVertexH0ToFdcFd(3,3) 
Complex(dp) :: AmpTreeH0ToFdcFd(2,3,3),AmpWaveH0ToFdcFd(2,3,3)=(0._dp,0._dp),AmpVertexH0ToFdcFd(2,3,3)& 
 & ,AmpVertexIRosH0ToFdcFd(2,3,3),AmpVertexIRdrH0ToFdcFd(2,3,3), AmpSumH0ToFdcFd(2,3,3), AmpSum2H0ToFdcFd(2,3,3) 
Complex(dp) :: AmpTreeZH0ToFdcFd(2,3,3),AmpWaveZH0ToFdcFd(2,3,3),AmpVertexZH0ToFdcFd(2,3,3) 
Real(dp) :: AmpSqH0ToFdcFd(3,3),  AmpSqTreeH0ToFdcFd(3,3) 
Real(dp) :: MRPH0ToFecFe(3,3),MRGH0ToFecFe(3,3), MRPZH0ToFecFe(3,3),MRGZH0ToFecFe(3,3) 
Real(dp) :: MVPH0ToFecFe(3,3) 
Real(dp) :: RMsqTreeH0ToFecFe(3,3),RMsqWaveH0ToFecFe(3,3),RMsqVertexH0ToFecFe(3,3) 
Complex(dp) :: AmpTreeH0ToFecFe(2,3,3),AmpWaveH0ToFecFe(2,3,3)=(0._dp,0._dp),AmpVertexH0ToFecFe(2,3,3)& 
 & ,AmpVertexIRosH0ToFecFe(2,3,3),AmpVertexIRdrH0ToFecFe(2,3,3), AmpSumH0ToFecFe(2,3,3), AmpSum2H0ToFecFe(2,3,3) 
Complex(dp) :: AmpTreeZH0ToFecFe(2,3,3),AmpWaveZH0ToFecFe(2,3,3),AmpVertexZH0ToFecFe(2,3,3) 
Real(dp) :: AmpSqH0ToFecFe(3,3),  AmpSqTreeH0ToFecFe(3,3) 
Real(dp) :: MRPH0ToFucFu(3,3),MRGH0ToFucFu(3,3), MRPZH0ToFucFu(3,3),MRGZH0ToFucFu(3,3) 
Real(dp) :: MVPH0ToFucFu(3,3) 
Real(dp) :: RMsqTreeH0ToFucFu(3,3),RMsqWaveH0ToFucFu(3,3),RMsqVertexH0ToFucFu(3,3) 
Complex(dp) :: AmpTreeH0ToFucFu(2,3,3),AmpWaveH0ToFucFu(2,3,3)=(0._dp,0._dp),AmpVertexH0ToFucFu(2,3,3)& 
 & ,AmpVertexIRosH0ToFucFu(2,3,3),AmpVertexIRdrH0ToFucFu(2,3,3), AmpSumH0ToFucFu(2,3,3), AmpSum2H0ToFucFu(2,3,3) 
Complex(dp) :: AmpTreeZH0ToFucFu(2,3,3),AmpWaveZH0ToFucFu(2,3,3),AmpVertexZH0ToFucFu(2,3,3) 
Real(dp) :: AmpSqH0ToFucFu(3,3),  AmpSqTreeH0ToFucFu(3,3) 
Real(dp) :: MRPH0ToFvcFv(3,3),MRGH0ToFvcFv(3,3), MRPZH0ToFvcFv(3,3),MRGZH0ToFvcFv(3,3) 
Real(dp) :: MVPH0ToFvcFv(3,3) 
Real(dp) :: RMsqTreeH0ToFvcFv(3,3),RMsqWaveH0ToFvcFv(3,3),RMsqVertexH0ToFvcFv(3,3) 
Complex(dp) :: AmpTreeH0ToFvcFv(2,3,3),AmpWaveH0ToFvcFv(2,3,3)=(0._dp,0._dp),AmpVertexH0ToFvcFv(2,3,3)& 
 & ,AmpVertexIRosH0ToFvcFv(2,3,3),AmpVertexIRdrH0ToFvcFv(2,3,3), AmpSumH0ToFvcFv(2,3,3), AmpSum2H0ToFvcFv(2,3,3) 
Complex(dp) :: AmpTreeZH0ToFvcFv(2,3,3),AmpWaveZH0ToFvcFv(2,3,3),AmpVertexZH0ToFvcFv(2,3,3) 
Real(dp) :: AmpSqH0ToFvcFv(3,3),  AmpSqTreeH0ToFvcFv(3,3) 
Real(dp) :: MRPH0ToH0H0,MRGH0ToH0H0, MRPZH0ToH0H0,MRGZH0ToH0H0 
Real(dp) :: MVPH0ToH0H0 
Real(dp) :: RMsqTreeH0ToH0H0,RMsqWaveH0ToH0H0,RMsqVertexH0ToH0H0 
Complex(dp) :: AmpTreeH0ToH0H0,AmpWaveH0ToH0H0=(0._dp,0._dp),AmpVertexH0ToH0H0& 
 & ,AmpVertexIRosH0ToH0H0,AmpVertexIRdrH0ToH0H0, AmpSumH0ToH0H0, AmpSum2H0ToH0H0 
Complex(dp) :: AmpTreeZH0ToH0H0,AmpWaveZH0ToH0H0,AmpVertexZH0ToH0H0 
Real(dp) :: AmpSqH0ToH0H0,  AmpSqTreeH0ToH0H0 
Real(dp) :: MRPH0ToH0VP,MRGH0ToH0VP, MRPZH0ToH0VP,MRGZH0ToH0VP 
Real(dp) :: MVPH0ToH0VP 
Real(dp) :: RMsqTreeH0ToH0VP,RMsqWaveH0ToH0VP,RMsqVertexH0ToH0VP 
Complex(dp) :: AmpTreeH0ToH0VP(2),AmpWaveH0ToH0VP(2)=(0._dp,0._dp),AmpVertexH0ToH0VP(2)& 
 & ,AmpVertexIRosH0ToH0VP(2),AmpVertexIRdrH0ToH0VP(2), AmpSumH0ToH0VP(2), AmpSum2H0ToH0VP(2) 
Complex(dp) :: AmpTreeZH0ToH0VP(2),AmpWaveZH0ToH0VP(2),AmpVertexZH0ToH0VP(2) 
Real(dp) :: AmpSqH0ToH0VP,  AmpSqTreeH0ToH0VP 
Real(dp) :: MRPH0ToH0VZ,MRGH0ToH0VZ, MRPZH0ToH0VZ,MRGZH0ToH0VZ 
Real(dp) :: MVPH0ToH0VZ 
Real(dp) :: RMsqTreeH0ToH0VZ,RMsqWaveH0ToH0VZ,RMsqVertexH0ToH0VZ 
Complex(dp) :: AmpTreeH0ToH0VZ(2),AmpWaveH0ToH0VZ(2)=(0._dp,0._dp),AmpVertexH0ToH0VZ(2)& 
 & ,AmpVertexIRosH0ToH0VZ(2),AmpVertexIRdrH0ToH0VZ(2), AmpSumH0ToH0VZ(2), AmpSum2H0ToH0VZ(2) 
Complex(dp) :: AmpTreeZH0ToH0VZ(2),AmpWaveZH0ToH0VZ(2),AmpVertexZH0ToH0VZ(2) 
Real(dp) :: AmpSqH0ToH0VZ,  AmpSqTreeH0ToH0VZ 
Real(dp) :: MRPH0Tohhhh,MRGH0Tohhhh, MRPZH0Tohhhh,MRGZH0Tohhhh 
Real(dp) :: MVPH0Tohhhh 
Real(dp) :: RMsqTreeH0Tohhhh,RMsqWaveH0Tohhhh,RMsqVertexH0Tohhhh 
Complex(dp) :: AmpTreeH0Tohhhh,AmpWaveH0Tohhhh=(0._dp,0._dp),AmpVertexH0Tohhhh& 
 & ,AmpVertexIRosH0Tohhhh,AmpVertexIRdrH0Tohhhh, AmpSumH0Tohhhh, AmpSum2H0Tohhhh 
Complex(dp) :: AmpTreeZH0Tohhhh,AmpWaveZH0Tohhhh,AmpVertexZH0Tohhhh 
Real(dp) :: AmpSqH0Tohhhh,  AmpSqTreeH0Tohhhh 
Real(dp) :: MRPH0TohhVP,MRGH0TohhVP, MRPZH0TohhVP,MRGZH0TohhVP 
Real(dp) :: MVPH0TohhVP 
Real(dp) :: RMsqTreeH0TohhVP,RMsqWaveH0TohhVP,RMsqVertexH0TohhVP 
Complex(dp) :: AmpTreeH0TohhVP(2),AmpWaveH0TohhVP(2)=(0._dp,0._dp),AmpVertexH0TohhVP(2)& 
 & ,AmpVertexIRosH0TohhVP(2),AmpVertexIRdrH0TohhVP(2), AmpSumH0TohhVP(2), AmpSum2H0TohhVP(2) 
Complex(dp) :: AmpTreeZH0TohhVP(2),AmpWaveZH0TohhVP(2),AmpVertexZH0TohhVP(2) 
Real(dp) :: AmpSqH0TohhVP,  AmpSqTreeH0TohhVP 
Real(dp) :: MRPH0TohhVZ,MRGH0TohhVZ, MRPZH0TohhVZ,MRGZH0TohhVZ 
Real(dp) :: MVPH0TohhVZ 
Real(dp) :: RMsqTreeH0TohhVZ,RMsqWaveH0TohhVZ,RMsqVertexH0TohhVZ 
Complex(dp) :: AmpTreeH0TohhVZ(2),AmpWaveH0TohhVZ(2)=(0._dp,0._dp),AmpVertexH0TohhVZ(2)& 
 & ,AmpVertexIRosH0TohhVZ(2),AmpVertexIRdrH0TohhVZ(2), AmpSumH0TohhVZ(2), AmpSum2H0TohhVZ(2) 
Complex(dp) :: AmpTreeZH0TohhVZ(2),AmpWaveZH0TohhVZ(2),AmpVertexZH0TohhVZ(2) 
Real(dp) :: AmpSqH0TohhVZ,  AmpSqTreeH0TohhVZ 
Real(dp) :: MRPH0ToVPVP,MRGH0ToVPVP, MRPZH0ToVPVP,MRGZH0ToVPVP 
Real(dp) :: MVPH0ToVPVP 
Real(dp) :: RMsqTreeH0ToVPVP,RMsqWaveH0ToVPVP,RMsqVertexH0ToVPVP 
Complex(dp) :: AmpTreeH0ToVPVP(2),AmpWaveH0ToVPVP(2)=(0._dp,0._dp),AmpVertexH0ToVPVP(2)& 
 & ,AmpVertexIRosH0ToVPVP(2),AmpVertexIRdrH0ToVPVP(2), AmpSumH0ToVPVP(2), AmpSum2H0ToVPVP(2) 
Complex(dp) :: AmpTreeZH0ToVPVP(2),AmpWaveZH0ToVPVP(2),AmpVertexZH0ToVPVP(2) 
Real(dp) :: AmpSqH0ToVPVP,  AmpSqTreeH0ToVPVP 
Real(dp) :: MRPH0ToVPVZ,MRGH0ToVPVZ, MRPZH0ToVPVZ,MRGZH0ToVPVZ 
Real(dp) :: MVPH0ToVPVZ 
Real(dp) :: RMsqTreeH0ToVPVZ,RMsqWaveH0ToVPVZ,RMsqVertexH0ToVPVZ 
Complex(dp) :: AmpTreeH0ToVPVZ(2),AmpWaveH0ToVPVZ(2)=(0._dp,0._dp),AmpVertexH0ToVPVZ(2)& 
 & ,AmpVertexIRosH0ToVPVZ(2),AmpVertexIRdrH0ToVPVZ(2), AmpSumH0ToVPVZ(2), AmpSum2H0ToVPVZ(2) 
Complex(dp) :: AmpTreeZH0ToVPVZ(2),AmpWaveZH0ToVPVZ(2),AmpVertexZH0ToVPVZ(2) 
Real(dp) :: AmpSqH0ToVPVZ,  AmpSqTreeH0ToVPVZ 
Real(dp) :: MRPH0ToVWpcVWp,MRGH0ToVWpcVWp, MRPZH0ToVWpcVWp,MRGZH0ToVWpcVWp 
Real(dp) :: MVPH0ToVWpcVWp 
Real(dp) :: RMsqTreeH0ToVWpcVWp,RMsqWaveH0ToVWpcVWp,RMsqVertexH0ToVWpcVWp 
Complex(dp) :: AmpTreeH0ToVWpcVWp(2),AmpWaveH0ToVWpcVWp(2)=(0._dp,0._dp),AmpVertexH0ToVWpcVWp(2)& 
 & ,AmpVertexIRosH0ToVWpcVWp(2),AmpVertexIRdrH0ToVWpcVWp(2), AmpSumH0ToVWpcVWp(2), AmpSum2H0ToVWpcVWp(2) 
Complex(dp) :: AmpTreeZH0ToVWpcVWp(2),AmpWaveZH0ToVWpcVWp(2),AmpVertexZH0ToVWpcVWp(2) 
Real(dp) :: AmpSqH0ToVWpcVWp,  AmpSqTreeH0ToVWpcVWp 
Real(dp) :: MRPH0ToVZVZ,MRGH0ToVZVZ, MRPZH0ToVZVZ,MRGZH0ToVZVZ 
Real(dp) :: MVPH0ToVZVZ 
Real(dp) :: RMsqTreeH0ToVZVZ,RMsqWaveH0ToVZVZ,RMsqVertexH0ToVZVZ 
Complex(dp) :: AmpTreeH0ToVZVZ(2),AmpWaveH0ToVZVZ(2)=(0._dp,0._dp),AmpVertexH0ToVZVZ(2)& 
 & ,AmpVertexIRosH0ToVZVZ(2),AmpVertexIRdrH0ToVZVZ(2), AmpSumH0ToVZVZ(2), AmpSum2H0ToVZVZ(2) 
Complex(dp) :: AmpTreeZH0ToVZVZ(2),AmpWaveZH0ToVZVZ(2),AmpVertexZH0ToVZVZ(2) 
Real(dp) :: AmpSqH0ToVZVZ,  AmpSqTreeH0ToVZVZ 
Write(*,*) "Calculating one-loop decays of H0 " 
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
Call Amplitude_Tree_Inert2_H0TohhA0(cplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,             & 
& AmpTreeH0TohhA0)

  Else 
Call Amplitude_Tree_Inert2_H0TohhA0(ZcplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,            & 
& AmpTreeH0TohhA0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_H0TohhA0(MLambda,em,gs,cplA0H0hh,MA0OS,MH0OS,MhhOS,            & 
& MRPH0TohhA0,MRGH0TohhA0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_H0TohhA0(MLambda,em,gs,ZcplA0H0hh,MA0OS,MH0OS,MhhOS,           & 
& MRPH0TohhA0,MRGH0TohhA0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_H0TohhA0(MLambda,em,gs,cplA0H0hh,MA0,MH0,Mhh,MRPH0TohhA0,      & 
& MRGH0TohhA0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_H0TohhA0(MLambda,em,gs,ZcplA0H0hh,MA0,MH0,Mhh,MRPH0TohhA0,     & 
& MRGH0TohhA0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_H0TohhA0(cplA0H0hh,ctcplA0H0hh,MA0,MA02,MH0,               & 
& MH02,Mhh,Mhh2,ZfA0,ZfH0,Zfhh,AmpWaveH0TohhA0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexH0TohhA0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_H0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRdrH0TohhA0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhA0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,ZcplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,   & 
& cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,        & 
& cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRosH0TohhA0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,ZcplA0H0hh,               & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,         & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,          & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,       & 
& AmpVertexIRosH0TohhA0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhA0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,   & 
& cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,        & 
& cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRosH0TohhA0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRosH0TohhA0)

 End if 
 End if 
AmpVertexH0TohhA0 = AmpVertexH0TohhA0 -  AmpVertexIRdrH0TohhA0! +  AmpVertexIRosH0TohhA0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexH0TohhA0 = AmpVertexH0TohhA0  +  AmpVertexIRosH0TohhA0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->hh A0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumH0TohhA0 = AmpTreeH0TohhA0 
 AmpSum2H0TohhA0 = AmpTreeH0TohhA0 + 2._dp*AmpWaveH0TohhA0 + 2._dp*AmpVertexH0TohhA0  
Else 
 AmpSumH0TohhA0 = AmpTreeH0TohhA0 + AmpWaveH0TohhA0 + AmpVertexH0TohhA0
 AmpSum2H0TohhA0 = AmpTreeH0TohhA0 + AmpWaveH0TohhA0 + AmpVertexH0TohhA0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0TohhA0 = AmpTreeH0TohhA0
 AmpSum2H0TohhA0 = AmpTreeH0TohhA0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MhhOS)+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(Mhh)+Abs(MA0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2H0TohhA0 = AmpTreeH0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MA0OS,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MA0,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqH0TohhA0 
  AmpSum2H0TohhA0 = 2._dp*AmpWaveH0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MA0OS,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MA0,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqH0TohhA0 
  AmpSum2H0TohhA0 = 2._dp*AmpVertexH0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MA0OS,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MA0,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqH0TohhA0 
  AmpSum2H0TohhA0 = AmpTreeH0TohhA0 + 2._dp*AmpWaveH0TohhA0 + 2._dp*AmpVertexH0TohhA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MA0OS,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MA0,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqH0TohhA0 
 End if 
If (OSkinematics) Then 
  AmpSum2H0TohhA0 = AmpTreeH0TohhA0
  Call SquareAmp_StoSS(MH0OS,MhhOS,MA0OS,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
  AmpSqTreeH0TohhA0 = AmpSqH0TohhA0  
  AmpSum2H0TohhA0 = + 2._dp*AmpWaveH0TohhA0 + 2._dp*AmpVertexH0TohhA0
  Call SquareAmp_StoSS(MH0OS,MhhOS,MA0OS,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
  AmpSqH0TohhA0 = AmpSqH0TohhA0 + AmpSqTreeH0TohhA0  
Else  
  AmpSum2H0TohhA0 = AmpTreeH0TohhA0
  Call SquareAmp_StoSS(MH0,Mhh,MA0,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
  AmpSqTreeH0TohhA0 = AmpSqH0TohhA0  
  AmpSum2H0TohhA0 = + 2._dp*AmpWaveH0TohhA0 + 2._dp*AmpVertexH0TohhA0
  Call SquareAmp_StoSS(MH0,Mhh,MA0,AmpSumH0TohhA0,AmpSum2H0TohhA0,AmpSqH0TohhA0) 
  AmpSqH0TohhA0 = AmpSqH0TohhA0 + AmpSqTreeH0TohhA0  
End if  
Else  
  AmpSqH0TohhA0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0TohhA0.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MhhOS,MA0OS,helfactor*AmpSqH0TohhA0)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,Mhh,MA0,helfactor*AmpSqH0TohhA0)
End if 
If ((Abs(MRPH0TohhA0).gt.1.0E-20_dp).or.(Abs(MRGH0TohhA0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPH0TohhA0).gt.1.0E-20_dp).or.(Abs(MRGH0TohhA0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPH0TohhA0 + MRGH0TohhA0) 
  gP1LH0(gt1,i4) = gP1LH0(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPH0TohhA0 + MRGH0TohhA0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LH0(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! A0 VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_H0ToA0VZ(cplA0H0VZ,MA0,MH0,MVZ,MA02,MH02,MVZ2,             & 
& AmpTreeH0ToA0VZ)

  Else 
Call Amplitude_Tree_Inert2_H0ToA0VZ(ZcplA0H0VZ,MA0,MH0,MVZ,MA02,MH02,MVZ2,            & 
& AmpTreeH0ToA0VZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_H0ToA0VZ(MLambda,em,gs,cplA0H0VZ,MA0OS,MH0OS,MVZOS,            & 
& MRPH0ToA0VZ,MRGH0ToA0VZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_H0ToA0VZ(MLambda,em,gs,ZcplA0H0VZ,MA0OS,MH0OS,MVZOS,           & 
& MRPH0ToA0VZ,MRGH0ToA0VZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_H0ToA0VZ(MLambda,em,gs,cplA0H0VZ,MA0,MH0,MVZ,MRPH0ToA0VZ,      & 
& MRGH0ToA0VZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_H0ToA0VZ(MLambda,em,gs,ZcplA0H0VZ,MA0,MH0,MVZ,MRPH0ToA0VZ,     & 
& MRGH0ToA0VZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_H0ToA0VZ(cplA0H0VZ,ctcplA0H0VZ,MA0,MA02,MH0,               & 
& MH02,MVZ,MVZ2,ZfA0,ZfH0,ZfVZ,AmpWaveH0ToA0VZ)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexH0ToA0VZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_H0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexIRdrH0ToA0VZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToA0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,ZcplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,            & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplA0HpcVWpVZ1,           & 
& cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,AmpVertexIRosH0ToA0VZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,ZcplA0H0VZ,     & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexIRosH0ToA0VZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToA0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,            & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplA0HpcVWpVZ1,           & 
& cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,AmpVertexIRosH0ToA0VZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,           & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1, & 
& AmpVertexIRosH0ToA0VZ)

 End if 
 End if 
AmpVertexH0ToA0VZ = AmpVertexH0ToA0VZ -  AmpVertexIRdrH0ToA0VZ! +  AmpVertexIRosH0ToA0VZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexH0ToA0VZ = AmpVertexH0ToA0VZ  +  AmpVertexIRosH0ToA0VZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->A0 VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumH0ToA0VZ = AmpTreeH0ToA0VZ 
 AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ + 2._dp*AmpWaveH0ToA0VZ + 2._dp*AmpVertexH0ToA0VZ  
Else 
 AmpSumH0ToA0VZ = AmpTreeH0ToA0VZ + AmpWaveH0ToA0VZ + AmpVertexH0ToA0VZ
 AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ + AmpWaveH0ToA0VZ + AmpVertexH0ToA0VZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToA0VZ = AmpTreeH0ToA0VZ
 AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MA0OS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MA0)+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MA0OS,MVZOS,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
Else  
  Call SquareAmp_StoSV(MH0,MA0,MVZ,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqH0ToA0VZ 
  AmpSum2H0ToA0VZ = 2._dp*AmpWaveH0ToA0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MA0OS,MVZOS,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
Else  
  Call SquareAmp_StoSV(MH0,MA0,MVZ,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqH0ToA0VZ 
  AmpSum2H0ToA0VZ = 2._dp*AmpVertexH0ToA0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MA0OS,MVZOS,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
Else  
  Call SquareAmp_StoSV(MH0,MA0,MVZ,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqH0ToA0VZ 
  AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ + 2._dp*AmpWaveH0ToA0VZ + 2._dp*AmpVertexH0ToA0VZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MA0OS,MVZOS,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
Else  
  Call SquareAmp_StoSV(MH0,MA0,MVZ,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqH0ToA0VZ 
 End if 
If (OSkinematics) Then 
  AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ
  Call SquareAmp_StoSV(MH0OS,MA0OS,MVZOS,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
  AmpSqTreeH0ToA0VZ = AmpSqH0ToA0VZ  
  AmpSum2H0ToA0VZ = + 2._dp*AmpWaveH0ToA0VZ + 2._dp*AmpVertexH0ToA0VZ
  Call SquareAmp_StoSV(MH0OS,MA0OS,MVZOS,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
  AmpSqH0ToA0VZ = AmpSqH0ToA0VZ + AmpSqTreeH0ToA0VZ  
Else  
  AmpSum2H0ToA0VZ = AmpTreeH0ToA0VZ
  Call SquareAmp_StoSV(MH0,MA0,MVZ,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
  AmpSqTreeH0ToA0VZ = AmpSqH0ToA0VZ  
  AmpSum2H0ToA0VZ = + 2._dp*AmpWaveH0ToA0VZ + 2._dp*AmpVertexH0ToA0VZ
  Call SquareAmp_StoSV(MH0,MA0,MVZ,AmpSumH0ToA0VZ(:),AmpSum2H0ToA0VZ(:),AmpSqH0ToA0VZ) 
  AmpSqH0ToA0VZ = AmpSqH0ToA0VZ + AmpSqTreeH0ToA0VZ  
End if  
Else  
  AmpSqH0ToA0VZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToA0VZ.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MA0OS,MVZOS,helfactor*AmpSqH0ToA0VZ)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MA0,MVZ,helfactor*AmpSqH0ToA0VZ)
End if 
If ((Abs(MRPH0ToA0VZ).gt.1.0E-20_dp).or.(Abs(MRGH0ToA0VZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPH0ToA0VZ).gt.1.0E-20_dp).or.(Abs(MRGH0ToA0VZ).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPH0ToA0VZ + MRGH0ToA0VZ) 
  gP1LH0(gt1,i4) = gP1LH0(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPH0ToA0VZ + MRGH0ToA0VZ)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LH0(gt1,i4) 
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
Call Amplitude_Tree_Inert2_H0TohhH0(cplH0H0hh,MH0,Mhh,MH02,Mhh2,AmpTreeH0TohhH0)

  Else 
Call Amplitude_Tree_Inert2_H0TohhH0(ZcplH0H0hh,MH0,Mhh,MH02,Mhh2,AmpTreeH0TohhH0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_H0TohhH0(MLambda,em,gs,cplH0H0hh,MH0OS,MhhOS,MRPH0TohhH0,      & 
& MRGH0TohhH0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_H0TohhH0(MLambda,em,gs,ZcplH0H0hh,MH0OS,MhhOS,MRPH0TohhH0,     & 
& MRGH0TohhH0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_H0TohhH0(MLambda,em,gs,cplH0H0hh,MH0,Mhh,MRPH0TohhH0,          & 
& MRGH0TohhH0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_H0TohhH0(MLambda,em,gs,ZcplH0H0hh,MH0,Mhh,MRPH0TohhH0,         & 
& MRGH0TohhH0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_H0TohhH0(cplH0H0hh,ctcplH0H0hh,MH0,MH02,Mhh,               & 
& Mhh2,ZfH0,Zfhh,AmpWaveH0TohhH0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexH0TohhH0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_H0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexIRdrH0TohhH0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhH0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,              & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,cplG0H0H0,cplG0hhVZ,ZcplH0H0hh,cplH0HpcHp,     & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,     & 
& cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,            & 
& cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,    & 
& AmpVertexIRosH0TohhH0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,ZcplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,           & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexIRosH0TohhH0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhH0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,              & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,      & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,     & 
& cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,            & 
& cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,    & 
& AmpVertexIRosH0TohhH0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexIRosH0TohhH0)

 End if 
 End if 
AmpVertexH0TohhH0 = AmpVertexH0TohhH0 -  AmpVertexIRdrH0TohhH0! +  AmpVertexIRosH0TohhH0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexH0TohhH0 = AmpVertexH0TohhH0  +  AmpVertexIRosH0TohhH0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->hh H0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumH0TohhH0 = AmpTreeH0TohhH0 
 AmpSum2H0TohhH0 = AmpTreeH0TohhH0 + 2._dp*AmpWaveH0TohhH0 + 2._dp*AmpVertexH0TohhH0  
Else 
 AmpSumH0TohhH0 = AmpTreeH0TohhH0 + AmpWaveH0TohhH0 + AmpVertexH0TohhH0
 AmpSum2H0TohhH0 = AmpTreeH0TohhH0 + AmpWaveH0TohhH0 + AmpVertexH0TohhH0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0TohhH0 = AmpTreeH0TohhH0
 AmpSum2H0TohhH0 = AmpTreeH0TohhH0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MhhOS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(Mhh)+Abs(MH0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2H0TohhH0 = AmpTreeH0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MH0OS,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MH0,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqH0TohhH0 
  AmpSum2H0TohhH0 = 2._dp*AmpWaveH0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MH0OS,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MH0,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqH0TohhH0 
  AmpSum2H0TohhH0 = 2._dp*AmpVertexH0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MH0OS,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MH0,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqH0TohhH0 
  AmpSum2H0TohhH0 = AmpTreeH0TohhH0 + 2._dp*AmpWaveH0TohhH0 + 2._dp*AmpVertexH0TohhH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MH0OS,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,MH0,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqH0TohhH0 
 End if 
If (OSkinematics) Then 
  AmpSum2H0TohhH0 = AmpTreeH0TohhH0
  Call SquareAmp_StoSS(MH0OS,MhhOS,MH0OS,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
  AmpSqTreeH0TohhH0 = AmpSqH0TohhH0  
  AmpSum2H0TohhH0 = + 2._dp*AmpWaveH0TohhH0 + 2._dp*AmpVertexH0TohhH0
  Call SquareAmp_StoSS(MH0OS,MhhOS,MH0OS,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
  AmpSqH0TohhH0 = AmpSqH0TohhH0 + AmpSqTreeH0TohhH0  
Else  
  AmpSum2H0TohhH0 = AmpTreeH0TohhH0
  Call SquareAmp_StoSS(MH0,Mhh,MH0,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
  AmpSqTreeH0TohhH0 = AmpSqH0TohhH0  
  AmpSum2H0TohhH0 = + 2._dp*AmpWaveH0TohhH0 + 2._dp*AmpVertexH0TohhH0
  Call SquareAmp_StoSS(MH0,Mhh,MH0,AmpSumH0TohhH0,AmpSum2H0TohhH0,AmpSqH0TohhH0) 
  AmpSqH0TohhH0 = AmpSqH0TohhH0 + AmpSqTreeH0TohhH0  
End if  
Else  
  AmpSqH0TohhH0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0TohhH0.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MhhOS,MH0OS,helfactor*AmpSqH0TohhH0)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,Mhh,MH0,helfactor*AmpSqH0TohhH0)
End if 
If ((Abs(MRPH0TohhH0).gt.1.0E-20_dp).or.(Abs(MRGH0TohhH0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPH0TohhH0).gt.1.0E-20_dp).or.(Abs(MRGH0TohhH0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPH0TohhH0 + MRGH0TohhH0) 
  gP1LH0(gt1,i4) = gP1LH0(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPH0TohhH0 + MRGH0TohhH0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LH0(gt1,i4) 
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
Call Amplitude_Tree_Inert2_H0TocHpHp(cplH0HpcHp,MH0,MHp,MH02,MHp2,AmpTreeH0TocHpHp)

  Else 
Call Amplitude_Tree_Inert2_H0TocHpHp(ZcplH0HpcHp,MH0,MHp,MH02,MHp2,AmpTreeH0TocHpHp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_H0TocHpHp(MLambda,em,gs,cplH0HpcHp,MH0OS,MHpOS,MRPH0TocHpHp,   & 
& MRGH0TocHpHp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_H0TocHpHp(MLambda,em,gs,ZcplH0HpcHp,MH0OS,MHpOS,               & 
& MRPH0TocHpHp,MRGH0TocHpHp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_H0TocHpHp(MLambda,em,gs,cplH0HpcHp,MH0,MHp,MRPH0TocHpHp,       & 
& MRGH0TocHpHp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_H0TocHpHp(MLambda,em,gs,ZcplH0HpcHp,MH0,MHp,MRPH0TocHpHp,      & 
& MRGH0TocHpHp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_H0TocHpHp(cplH0HpcHp,ctcplH0HpcHp,MH0,MH02,MHp,            & 
& MHp2,ZfH0,ZfHp,AmpWaveH0TocHpHp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,              & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,            & 
& cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,               & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexH0TocHpHp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_H0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,              & 
& cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1, & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexIRdrH0TocHpHp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TocHpHp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,ZcplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,      & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,     & 
& cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,            & 
& AmpVertexIRosH0TocHpHp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,        & 
& ZcplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,     & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,              & 
& cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1, & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexIRosH0TocHpHp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TocHpHp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,       & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,     & 
& cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,            & 
& AmpVertexIRosH0TocHpHp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,              & 
& cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1, & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexIRosH0TocHpHp)

 End if 
 End if 
AmpVertexH0TocHpHp = AmpVertexH0TocHpHp -  AmpVertexIRdrH0TocHpHp! +  AmpVertexIRosH0TocHpHp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZH0TocHpHp=0._dp 
AmpVertexZH0TocHpHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZH0TocHpHp(gt2,:) = AmpWaveZH0TocHpHp(gt2,:)+ZRUZP(gt2,gt1)*AmpWaveH0TocHpHp(gt1,:) 
AmpVertexZH0TocHpHp(gt2,:)= AmpVertexZH0TocHpHp(gt2,:)+ZRUZP(gt2,gt1)*AmpVertexH0TocHpHp(gt1,:) 
 End Do 
End Do 
AmpWaveH0TocHpHp=AmpWaveZH0TocHpHp 
AmpVertexH0TocHpHp= AmpVertexZH0TocHpHp
! Final State 2 
AmpWaveZH0TocHpHp=0._dp 
AmpVertexZH0TocHpHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZH0TocHpHp(:,gt2) = AmpWaveZH0TocHpHp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveH0TocHpHp(:,gt1) 
AmpVertexZH0TocHpHp(:,gt2)= AmpVertexZH0TocHpHp(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexH0TocHpHp(:,gt1) 
 End Do 
End Do 
AmpWaveH0TocHpHp=AmpWaveZH0TocHpHp 
AmpVertexH0TocHpHp= AmpVertexZH0TocHpHp
End if
If (ShiftIRdiv) Then 
AmpVertexH0TocHpHp = AmpVertexH0TocHpHp  +  AmpVertexIRosH0TocHpHp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->conj[Hp] Hp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumH0TocHpHp = AmpTreeH0TocHpHp 
 AmpSum2H0TocHpHp = AmpTreeH0TocHpHp + 2._dp*AmpWaveH0TocHpHp + 2._dp*AmpVertexH0TocHpHp  
Else 
 AmpSumH0TocHpHp = AmpTreeH0TocHpHp + AmpWaveH0TocHpHp + AmpVertexH0TocHpHp
 AmpSum2H0TocHpHp = AmpTreeH0TocHpHp + AmpWaveH0TocHpHp + AmpVertexH0TocHpHp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0TocHpHp = AmpTreeH0TocHpHp
 AmpSum2H0TocHpHp = AmpTreeH0TocHpHp 
End if 
gt1=1 
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MHpOS(gt2))+Abs(MHpOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MHp(gt2))+Abs(MHp(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2H0TocHpHp = AmpTreeH0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MHpOS(gt2),MHpOS(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MH0,MHp(gt2),MHp(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqH0TocHpHp(gt2, gt3) 
  AmpSum2H0TocHpHp = 2._dp*AmpWaveH0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MHpOS(gt2),MHpOS(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MH0,MHp(gt2),MHp(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqH0TocHpHp(gt2, gt3) 
  AmpSum2H0TocHpHp = 2._dp*AmpVertexH0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MHpOS(gt2),MHpOS(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MH0,MHp(gt2),MHp(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqH0TocHpHp(gt2, gt3) 
  AmpSum2H0TocHpHp = AmpTreeH0TocHpHp + 2._dp*AmpWaveH0TocHpHp + 2._dp*AmpVertexH0TocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MHpOS(gt2),MHpOS(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MH0,MHp(gt2),MHp(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqH0TocHpHp(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2H0TocHpHp = AmpTreeH0TocHpHp
  Call SquareAmp_StoSS(MH0OS,MHpOS(gt2),MHpOS(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
  AmpSqTreeH0TocHpHp(gt2, gt3) = AmpSqH0TocHpHp(gt2, gt3)  
  AmpSum2H0TocHpHp = + 2._dp*AmpWaveH0TocHpHp + 2._dp*AmpVertexH0TocHpHp
  Call SquareAmp_StoSS(MH0OS,MHpOS(gt2),MHpOS(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
  AmpSqH0TocHpHp(gt2, gt3) = AmpSqH0TocHpHp(gt2, gt3) + AmpSqTreeH0TocHpHp(gt2, gt3)  
Else  
  AmpSum2H0TocHpHp = AmpTreeH0TocHpHp
  Call SquareAmp_StoSS(MH0,MHp(gt2),MHp(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
  AmpSqTreeH0TocHpHp(gt2, gt3) = AmpSqH0TocHpHp(gt2, gt3)  
  AmpSum2H0TocHpHp = + 2._dp*AmpWaveH0TocHpHp + 2._dp*AmpVertexH0TocHpHp
  Call SquareAmp_StoSS(MH0,MHp(gt2),MHp(gt3),AmpSumH0TocHpHp(gt2, gt3),AmpSum2H0TocHpHp(gt2, gt3),AmpSqH0TocHpHp(gt2, gt3)) 
  AmpSqH0TocHpHp(gt2, gt3) = AmpSqH0TocHpHp(gt2, gt3) + AmpSqTreeH0TocHpHp(gt2, gt3)  
End if  
Else  
  AmpSqH0TocHpHp(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0TocHpHp(gt2, gt3).eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MHpOS(gt2),MHpOS(gt3),helfactor*AmpSqH0TocHpHp(gt2, gt3))
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MHp(gt2),MHp(gt3),helfactor*AmpSqH0TocHpHp(gt2, gt3))
End if 
If ((Abs(MRPH0TocHpHp(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGH0TocHpHp(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPH0TocHpHp(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGH0TocHpHp(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPH0TocHpHp(gt2, gt3) + MRGH0TocHpHp(gt2, gt3)) 
  gP1LH0(gt1,i4) = gP1LH0(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPH0TocHpHp(gt2, gt3) + MRGH0TocHpHp(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LH0(gt1,i4) 
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
Call Amplitude_Tree_Inert2_H0ToHpcVWp(cplH0HpcVWp,MH0,MHp,MVWp,MH02,MHp2,             & 
& MVWp2,AmpTreeH0ToHpcVWp)

  Else 
Call Amplitude_Tree_Inert2_H0ToHpcVWp(ZcplH0HpcVWp,MH0,MHp,MVWp,MH02,MHp2,            & 
& MVWp2,AmpTreeH0ToHpcVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_H0ToHpcVWp(MLambda,em,gs,cplH0HpcVWp,MH0OS,MHpOS,              & 
& MVWpOS,MRPH0ToHpcVWp,MRGH0ToHpcVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_H0ToHpcVWp(MLambda,em,gs,ZcplH0HpcVWp,MH0OS,MHpOS,             & 
& MVWpOS,MRPH0ToHpcVWp,MRGH0ToHpcVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_H0ToHpcVWp(MLambda,em,gs,cplH0HpcVWp,MH0,MHp,MVWp,             & 
& MRPH0ToHpcVWp,MRGH0ToHpcVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_H0ToHpcVWp(MLambda,em,gs,ZcplH0HpcVWp,MH0,MHp,MVWp,            & 
& MRPH0ToHpcVWp,MRGH0ToHpcVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_H0ToHpcVWp(cplH0HpcVWp,ctcplH0HpcVWp,MH0,MH02,             & 
& MHp,MHp2,MVWp,MVWp2,ZfH0,ZfHp,ZfVWp,AmpWaveH0ToHpcVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0HpcVWp,cplG0H0H0,cplG0HpcVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,        & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,     & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplH0H0cVWpVWp1,cplH0HpcVWpVP1,               & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexH0ToHpcVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_H0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplG0H0H0,cplG0HpcVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplH0H0cVWpVWp1,cplH0HpcVWpVP1,   & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRdrH0ToHpcVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToHpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,             & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplG0H0H0,cplG0HpcVWp,            & 
& cplH0H0hh,GosZcplH0HpcHp,ZcplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcVWpVWp,cplHpcHpVP,GosZcplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplH0H0cVWpVWp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,             & 
& cplHpcHpcVWpVWp1,AmpVertexIRosH0ToHpcVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplG0H0H0,cplG0HpcVWp,cplH0H0hh,GZcplH0HpcHp,ZcplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,GZcplHpcVWpVP,              & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplH0H0cVWpVWp1,       & 
& cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosH0ToHpcVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToHpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,             & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplG0H0H0,cplG0HpcVWp,            & 
& cplH0H0hh,GcplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,     & 
& cplHpcHpVP,GcplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,              & 
& cplA0HpcVWpVZ1,cplH0H0cVWpVWp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRosH0ToHpcVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_H0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplG0H0H0,cplG0HpcVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplH0H0cVWpVWp1,cplH0HpcVWpVP1,   & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosH0ToHpcVWp)

 End if 
 End if 
AmpVertexH0ToHpcVWp = AmpVertexH0ToHpcVWp -  AmpVertexIRdrH0ToHpcVWp! +  AmpVertexIRosH0ToHpcVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZH0ToHpcVWp=0._dp 
AmpVertexZH0ToHpcVWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZH0ToHpcVWp(:,gt2) = AmpWaveZH0ToHpcVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveH0ToHpcVWp(:,gt1) 
AmpVertexZH0ToHpcVWp(:,gt2)= AmpVertexZH0ToHpcVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexH0ToHpcVWp(:,gt1) 
 End Do 
End Do 
AmpWaveH0ToHpcVWp=AmpWaveZH0ToHpcVWp 
AmpVertexH0ToHpcVWp= AmpVertexZH0ToHpcVWp
End if
If (ShiftIRdiv) Then 
AmpVertexH0ToHpcVWp = AmpVertexH0ToHpcVWp  +  AmpVertexIRosH0ToHpcVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->Hp conj[VWp] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumH0ToHpcVWp = AmpTreeH0ToHpcVWp 
 AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp + 2._dp*AmpWaveH0ToHpcVWp + 2._dp*AmpVertexH0ToHpcVWp  
Else 
 AmpSumH0ToHpcVWp = AmpTreeH0ToHpcVWp + AmpWaveH0ToHpcVWp + AmpVertexH0ToHpcVWp
 AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp + AmpWaveH0ToHpcVWp + AmpVertexH0ToHpcVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToHpcVWp = AmpTreeH0ToHpcVWp
 AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp 
End if 
gt1=1 
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MHpOS(gt2))+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MHp(gt2))+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2 
  AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MHpOS(gt2),MVWpOS,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MH0,MHp(gt2),MVWp,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqH0ToHpcVWp(gt2) 
  AmpSum2H0ToHpcVWp = 2._dp*AmpWaveH0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MHpOS(gt2),MVWpOS,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MH0,MHp(gt2),MVWp,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqH0ToHpcVWp(gt2) 
  AmpSum2H0ToHpcVWp = 2._dp*AmpVertexH0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MHpOS(gt2),MVWpOS,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MH0,MHp(gt2),MVWp,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqH0ToHpcVWp(gt2) 
  AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp + 2._dp*AmpWaveH0ToHpcVWp + 2._dp*AmpVertexH0ToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MHpOS(gt2),MVWpOS,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(MH0,MHp(gt2),MVWp,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqH0ToHpcVWp(gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp
  Call SquareAmp_StoSV(MH0OS,MHpOS(gt2),MVWpOS,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
  AmpSqTreeH0ToHpcVWp(gt2) = AmpSqH0ToHpcVWp(gt2)  
  AmpSum2H0ToHpcVWp = + 2._dp*AmpWaveH0ToHpcVWp + 2._dp*AmpVertexH0ToHpcVWp
  Call SquareAmp_StoSV(MH0OS,MHpOS(gt2),MVWpOS,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
  AmpSqH0ToHpcVWp(gt2) = AmpSqH0ToHpcVWp(gt2) + AmpSqTreeH0ToHpcVWp(gt2)  
Else  
  AmpSum2H0ToHpcVWp = AmpTreeH0ToHpcVWp
  Call SquareAmp_StoSV(MH0,MHp(gt2),MVWp,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
  AmpSqTreeH0ToHpcVWp(gt2) = AmpSqH0ToHpcVWp(gt2)  
  AmpSum2H0ToHpcVWp = + 2._dp*AmpWaveH0ToHpcVWp + 2._dp*AmpVertexH0ToHpcVWp
  Call SquareAmp_StoSV(MH0,MHp(gt2),MVWp,AmpSumH0ToHpcVWp(:,gt2),AmpSum2H0ToHpcVWp(:,gt2),AmpSqH0ToHpcVWp(gt2)) 
  AmpSqH0ToHpcVWp(gt2) = AmpSqH0ToHpcVWp(gt2) + AmpSqTreeH0ToHpcVWp(gt2)  
End if  
Else  
  AmpSqH0ToHpcVWp(gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToHpcVWp(gt2).eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 2._dp*GammaTPS(MH0OS,MHpOS(gt2),MVWpOS,helfactor*AmpSqH0ToHpcVWp(gt2))
Else 
  gP1LH0(gt1,i4) = 2._dp*GammaTPS(MH0,MHp(gt2),MVWp,helfactor*AmpSqH0ToHpcVWp(gt2))
End if 
If ((Abs(MRPH0ToHpcVWp(gt2)).gt.1.0E-20_dp).or.(Abs(MRGH0ToHpcVWp(gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPH0ToHpcVWp(gt2)).gt.1.0E-20_dp).or.(Abs(MRGH0ToHpcVWp(gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPH0ToHpcVWp(gt2) + MRGH0ToHpcVWp(gt2)) 
  gP1LH0(gt1,i4) = gP1LH0(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPH0ToHpcVWp(gt2) + MRGH0ToHpcVWp(gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToA0A0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplA0A0HpcHp1,AmpVertexH0ToA0A0)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToA0A0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplA0A0HpcHp1,AmpVertexH0ToA0A0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToA0A0(MA0,MH0,MHp,MVWp,MA02,MH02,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplA0A0HpcHp1,   & 
& AmpVertexH0ToA0A0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->A0 A0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToA0A0 = 0._dp 
 AmpSum2H0ToA0A0 = 0._dp  
Else 
 AmpSumH0ToA0A0 = AmpVertexH0ToA0A0 + AmpWaveH0ToA0A0
 AmpSum2H0ToA0A0 = AmpVertexH0ToA0A0 + AmpWaveH0ToA0A0 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MA0OS)+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MA0)+Abs(MA0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MA0OS,MA0OS,AmpSumH0ToA0A0,AmpSum2H0ToA0A0,AmpSqH0ToA0A0) 
Else  
  Call SquareAmp_StoSS(MH0,MA0,MA0,AmpSumH0ToA0A0,AmpSum2H0ToA0A0,AmpSqH0ToA0A0) 
End if  
Else  
  AmpSqH0ToA0A0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToA0A0.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp/2._dp*GammaTPS(MH0OS,MA0OS,MA0OS,helfactor*AmpSqH0ToA0A0)
Else 
  gP1LH0(gt1,i4) = 1._dp/2._dp*GammaTPS(MH0,MA0,MA0,helfactor*AmpSqH0ToA0A0)
End if 
If ((Abs(MRPH0ToA0A0).gt.1.0E-20_dp).or.(Abs(MRGH0ToA0A0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToA0H0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexH0ToA0H0)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToA0H0(MA0OS,MH0OS,MHpOS,MVWpOS,MA02OS,MH02OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexH0ToA0H0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToA0H0(MA0,MH0,MHp,MVWp,MA02,MH02,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplH0H0HpcHp1,   & 
& AmpVertexH0ToA0H0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->A0 H0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToA0H0 = 0._dp 
 AmpSum2H0ToA0H0 = 0._dp  
Else 
 AmpSumH0ToA0H0 = AmpVertexH0ToA0H0 + AmpWaveH0ToA0H0
 AmpSum2H0ToA0H0 = AmpVertexH0ToA0H0 + AmpWaveH0ToA0H0 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MA0OS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MA0)+Abs(MH0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MA0OS,MH0OS,AmpSumH0ToA0H0,AmpSum2H0ToA0H0,AmpSqH0ToA0H0) 
Else  
  Call SquareAmp_StoSS(MH0,MA0,MH0,AmpSumH0ToA0H0,AmpSum2H0ToA0H0,AmpSqH0ToA0H0) 
End if  
Else  
  AmpSqH0ToA0H0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToA0H0.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MA0OS,MH0OS,helfactor*AmpSqH0ToA0H0)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MA0,MH0,helfactor*AmpSqH0ToA0H0)
End if 
If ((Abs(MRPH0ToA0H0).gt.1.0E-20_dp).or.(Abs(MRGH0ToA0H0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! A0 VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_H0ToA0VP(cplA0H0VZ,ctcplA0H0VZ,MA0OS,MA02OS,               & 
& MH0OS,MH02OS,MVP,MVP2,MVZOS,MVZ2OS,ZfA0,ZfH0,ZfVP,ZfVZVP,AmpWaveH0ToA0VP)

 Else 
Call Amplitude_WAVE_Inert2_H0ToA0VP(cplA0H0VZ,ctcplA0H0VZ,MA0OS,MA02OS,               & 
& MH0OS,MH02OS,MVP,MVP2,MVZOS,MVZ2OS,ZfA0,ZfH0,ZfVP,ZfVZVP,AmpWaveH0ToA0VP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_H0ToA0VP(MA0OS,MH0OS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& MH02OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,              & 
& cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,               & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexH0ToA0VP)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToA0VP(MA0OS,MH0OS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& MH02OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,              & 
& cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,               & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexH0ToA0VP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_H0ToA0VP(cplA0H0VZ,ctcplA0H0VZ,MA0,MA02,MH0,               & 
& MH02,MVP,MVP2,MVZ,MVZ2,ZfA0,ZfH0,ZfVP,ZfVZVP,AmpWaveH0ToA0VP)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToA0VP(MA0,MH0,MHp,MVP,MVWp,MA02,MH02,MHp2,            & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,      & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,         & 
& cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexH0ToA0VP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->A0 VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToA0VP = 0._dp 
 AmpSum2H0ToA0VP = 0._dp  
Else 
 AmpSumH0ToA0VP = AmpVertexH0ToA0VP + AmpWaveH0ToA0VP
 AmpSum2H0ToA0VP = AmpVertexH0ToA0VP + AmpWaveH0ToA0VP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MA0OS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MA0)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MA0OS,0._dp,AmpSumH0ToA0VP(:),AmpSum2H0ToA0VP(:),AmpSqH0ToA0VP) 
Else  
  Call SquareAmp_StoSV(MH0,MA0,MVP,AmpSumH0ToA0VP(:),AmpSum2H0ToA0VP(:),AmpSqH0ToA0VP) 
End if  
Else  
  AmpSqH0ToA0VP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToA0VP.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MA0OS,0._dp,helfactor*AmpSqH0ToA0VP)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MA0,MVP,helfactor*AmpSqH0ToA0VP)
End if 
If ((Abs(MRPH0ToA0VP).gt.1.0E-20_dp).or.(Abs(MRGH0ToA0VP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToFdcFd(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,         & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,        & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFdcFd)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToFdcFd(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,         & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,        & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFdcFd)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToFdcFd(MFd,MFu,MH0,MHp,MVWp,MFd2,MFu2,MH02,           & 
& MHp2,MVWp2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,             & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,           & 
& AmpVertexH0ToFdcFd)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->Fd bar[Fd] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToFdcFd = 0._dp 
 AmpSum2H0ToFdcFd = 0._dp  
Else 
 AmpSumH0ToFdcFd = AmpVertexH0ToFdcFd + AmpWaveH0ToFdcFd
 AmpSum2H0ToFdcFd = AmpVertexH0ToFdcFd + AmpWaveH0ToFdcFd 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MFdOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MFd(gt2))+Abs(MFd(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MH0OS,MFdOS(gt2),MFdOS(gt3),AmpSumH0ToFdcFd(:,gt2, gt3),AmpSum2H0ToFdcFd(:,gt2, gt3),AmpSqH0ToFdcFd(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MH0,MFd(gt2),MFd(gt3),AmpSumH0ToFdcFd(:,gt2, gt3),AmpSum2H0ToFdcFd(:,gt2, gt3),AmpSqH0ToFdcFd(gt2, gt3)) 
End if  
Else  
  AmpSqH0ToFdcFd(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqH0ToFdcFd(gt2, gt3).eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 3._dp*GammaTPS(MH0OS,MFdOS(gt2),MFdOS(gt3),helfactor*AmpSqH0ToFdcFd(gt2, gt3))
Else 
  gP1LH0(gt1,i4) = 3._dp*GammaTPS(MH0,MFd(gt2),MFd(gt3),helfactor*AmpSqH0ToFdcFd(gt2, gt3))
End if 
If ((Abs(MRPH0ToFdcFd(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGH0ToFdcFd(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToFecFe(MFeOS,MH0OS,MHpOS,MVWpOS,MFe2OS,               & 
& MH02OS,MHp2OS,MVWp2OS,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFecFe)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToFecFe(MFeOS,MH0OS,MHpOS,MVWpOS,MFe2OS,               & 
& MH02OS,MHp2OS,MVWp2OS,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFecFe)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToFecFe(MFe,MH0,MHp,MVWp,MFe2,MH02,MHp2,               & 
& MVWp2,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,     & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,AmpVertexH0ToFecFe)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->Fe bar[Fe] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToFecFe = 0._dp 
 AmpSum2H0ToFecFe = 0._dp  
Else 
 AmpSumH0ToFecFe = AmpVertexH0ToFecFe + AmpWaveH0ToFecFe
 AmpSum2H0ToFecFe = AmpVertexH0ToFecFe + AmpWaveH0ToFecFe 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MFeOS(gt2))+Abs(MFeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MFe(gt2))+Abs(MFe(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MH0OS,MFeOS(gt2),MFeOS(gt3),AmpSumH0ToFecFe(:,gt2, gt3),AmpSum2H0ToFecFe(:,gt2, gt3),AmpSqH0ToFecFe(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MH0,MFe(gt2),MFe(gt3),AmpSumH0ToFecFe(:,gt2, gt3),AmpSum2H0ToFecFe(:,gt2, gt3),AmpSqH0ToFecFe(gt2, gt3)) 
End if  
Else  
  AmpSqH0ToFecFe(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqH0ToFecFe(gt2, gt3).eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MFeOS(gt2),MFeOS(gt3),helfactor*AmpSqH0ToFecFe(gt2, gt3))
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MFe(gt2),MFe(gt3),helfactor*AmpSqH0ToFecFe(gt2, gt3))
End if 
If ((Abs(MRPH0ToFecFe(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGH0ToFecFe(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToFucFu(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,         & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,        & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFucFu)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToFucFu(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,         & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,        & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFucFu)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToFucFu(MFd,MFu,MH0,MHp,MVWp,MFd2,MFu2,MH02,           & 
& MHp2,MVWp2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,             & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,           & 
& AmpVertexH0ToFucFu)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->Fu bar[Fu] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToFucFu = 0._dp 
 AmpSum2H0ToFucFu = 0._dp  
Else 
 AmpSumH0ToFucFu = AmpVertexH0ToFucFu + AmpWaveH0ToFucFu
 AmpSum2H0ToFucFu = AmpVertexH0ToFucFu + AmpWaveH0ToFucFu 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MFuOS(gt2))+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MFu(gt2))+Abs(MFu(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MH0OS,MFuOS(gt2),MFuOS(gt3),AmpSumH0ToFucFu(:,gt2, gt3),AmpSum2H0ToFucFu(:,gt2, gt3),AmpSqH0ToFucFu(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MH0,MFu(gt2),MFu(gt3),AmpSumH0ToFucFu(:,gt2, gt3),AmpSum2H0ToFucFu(:,gt2, gt3),AmpSqH0ToFucFu(gt2, gt3)) 
End if  
Else  
  AmpSqH0ToFucFu(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqH0ToFucFu(gt2, gt3).eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 3._dp*GammaTPS(MH0OS,MFuOS(gt2),MFuOS(gt3),helfactor*AmpSqH0ToFucFu(gt2, gt3))
Else 
  gP1LH0(gt1,i4) = 3._dp*GammaTPS(MH0,MFu(gt2),MFu(gt3),helfactor*AmpSqH0ToFucFu(gt2, gt3))
End if 
If ((Abs(MRPH0ToFucFu(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGH0ToFucFu(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToFvcFv(MFeOS,MH0OS,MHpOS,MVWpOS,MFe2OS,               & 
& MH02OS,MHp2OS,MVWp2OS,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFvcFv)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToFvcFv(MFeOS,MH0OS,MHpOS,MVWpOS,MFe2OS,               & 
& MH02OS,MHp2OS,MVWp2OS,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexH0ToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToFvcFv(MFe,MH0,MHp,MVWp,MFe2,MH02,MHp2,               & 
& MVWp2,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,     & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,AmpVertexH0ToFvcFv)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->Fv bar[Fv] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToFvcFv = 0._dp 
 AmpSum2H0ToFvcFv = 0._dp  
Else 
 AmpSumH0ToFvcFv = AmpVertexH0ToFvcFv + AmpWaveH0ToFvcFv
 AmpSum2H0ToFvcFv = AmpVertexH0ToFvcFv + AmpWaveH0ToFvcFv 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(0._dp)+Abs(0._dp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MH0OS,0._dp,0._dp,AmpSumH0ToFvcFv(:,gt2, gt3),AmpSum2H0ToFvcFv(:,gt2, gt3),AmpSqH0ToFvcFv(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MH0,0._dp,0._dp,AmpSumH0ToFvcFv(:,gt2, gt3),AmpSum2H0ToFvcFv(:,gt2, gt3),AmpSqH0ToFvcFv(gt2, gt3)) 
End if  
Else  
  AmpSqH0ToFvcFv(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqH0ToFvcFv(gt2, gt3).eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,0._dp,0._dp,helfactor*AmpSqH0ToFvcFv(gt2, gt3))
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,0._dp,0._dp,helfactor*AmpSqH0ToFvcFv(gt2, gt3))
End if 
If ((Abs(MRPH0ToFvcFv(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGH0ToFvcFv(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToH0H0(MH0OS,MHpOS,MVWpOS,MH02OS,MHp2OS,               & 
& MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexH0ToH0H0)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToH0H0(MH0OS,MHpOS,MVWpOS,MH02OS,MHp2OS,               & 
& MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexH0ToH0H0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToH0H0(MH0,MHp,MVWp,MH02,MHp2,MVWp2,cplH0HpcHp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplH0H0HpcHp1,AmpVertexH0ToH0H0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->H0 H0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToH0H0 = 0._dp 
 AmpSum2H0ToH0H0 = 0._dp  
Else 
 AmpSumH0ToH0H0 = AmpVertexH0ToH0H0 + AmpWaveH0ToH0H0
 AmpSum2H0ToH0H0 = AmpVertexH0ToH0H0 + AmpWaveH0ToH0H0 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MH0OS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MH0)+Abs(MH0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MH0OS,MH0OS,AmpSumH0ToH0H0,AmpSum2H0ToH0H0,AmpSqH0ToH0H0) 
Else  
  Call SquareAmp_StoSS(MH0,MH0,MH0,AmpSumH0ToH0H0,AmpSum2H0ToH0H0,AmpSqH0ToH0H0) 
End if  
Else  
  AmpSqH0ToH0H0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToH0H0.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp/2._dp*GammaTPS(MH0OS,MH0OS,MH0OS,helfactor*AmpSqH0ToH0H0)
Else 
  gP1LH0(gt1,i4) = 1._dp/2._dp*GammaTPS(MH0,MH0,MH0,helfactor*AmpSqH0ToH0H0)
End if 
If ((Abs(MRPH0ToH0H0).gt.1.0E-20_dp).or.(Abs(MRGH0ToH0H0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! H0 VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_H0ToH0VP(MH0OS,MHpOS,MVP,MVWpOS,MH02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexH0ToH0VP)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToH0VP(MH0OS,MHpOS,MVP,MVWpOS,MH02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexH0ToH0VP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToH0VP(MH0,MHp,MVP,MVWp,MH02,MHp2,MVP2,MVWp2,          & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,    & 
& cplH0HpcVWpVP1,cplH0cHpVPVWp1,AmpVertexH0ToH0VP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->H0 VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToH0VP = 0._dp 
 AmpSum2H0ToH0VP = 0._dp  
Else 
 AmpSumH0ToH0VP = AmpVertexH0ToH0VP + AmpWaveH0ToH0VP
 AmpSum2H0ToH0VP = AmpVertexH0ToH0VP + AmpWaveH0ToH0VP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MH0OS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MH0)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MH0OS,0._dp,AmpSumH0ToH0VP(:),AmpSum2H0ToH0VP(:),AmpSqH0ToH0VP) 
Else  
  Call SquareAmp_StoSV(MH0,MH0,MVP,AmpSumH0ToH0VP(:),AmpSum2H0ToH0VP(:),AmpSqH0ToH0VP) 
End if  
Else  
  AmpSqH0ToH0VP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToH0VP.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MH0OS,0._dp,helfactor*AmpSqH0ToH0VP)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MH0,MVP,helfactor*AmpSqH0ToH0VP)
End if 
If ((Abs(MRPH0ToH0VP).gt.1.0E-20_dp).or.(Abs(MRGH0ToH0VP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! H0 VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_H0ToH0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,MVWpOS,           & 
& MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,              & 
& cplH0cHpVWpVZ1,AmpVertexH0ToH0VZ)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToH0VZ(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,MVWpOS,           & 
& MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,              & 
& cplH0cHpVWpVZ1,AmpVertexH0ToH0VZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplG0hhVZ,      & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,         & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,AmpVertexH0ToH0VZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->H0 VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToH0VZ = 0._dp 
 AmpSum2H0ToH0VZ = 0._dp  
Else 
 AmpSumH0ToH0VZ = AmpVertexH0ToH0VZ + AmpWaveH0ToH0VZ
 AmpSum2H0ToH0VZ = AmpVertexH0ToH0VZ + AmpWaveH0ToH0VZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MH0OS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MH0)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MH0OS,MVZOS,AmpSumH0ToH0VZ(:),AmpSum2H0ToH0VZ(:),AmpSqH0ToH0VZ) 
Else  
  Call SquareAmp_StoSV(MH0,MH0,MVZ,AmpSumH0ToH0VZ(:),AmpSum2H0ToH0VZ(:),AmpSqH0ToH0VZ) 
End if  
Else  
  AmpSqH0ToH0VZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToH0VZ.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MH0OS,MVZOS,helfactor*AmpSqH0ToH0VZ)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MH0,MVZ,helfactor*AmpSqH0ToH0VZ)
End if 
If ((Abs(MRPH0ToH0VZ).gt.1.0E-20_dp).or.(Abs(MRGH0ToH0VZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0Tohhhh(MH0OS,MhhOS,MHpOS,MVWpOS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplH0hhHpcHp1,cplhhhhHpcHp1,AmpVertexH0Tohhhh)

 Else 
Call Amplitude_VERTEX_Inert2_H0Tohhhh(MH0OS,MhhOS,MHpOS,MVWpOS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplH0hhHpcHp1,cplhhhhHpcHp1,AmpVertexH0Tohhhh)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0Tohhhh(MH0,Mhh,MHp,MVWp,MH02,Mhh2,MHp2,MVWp2,          & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,    & 
& cplH0hhHpcHp1,cplhhhhHpcHp1,AmpVertexH0Tohhhh)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->hh hh -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0Tohhhh = 0._dp 
 AmpSum2H0Tohhhh = 0._dp  
Else 
 AmpSumH0Tohhhh = AmpVertexH0Tohhhh + AmpWaveH0Tohhhh
 AmpSum2H0Tohhhh = AmpVertexH0Tohhhh + AmpWaveH0Tohhhh 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MhhOS)+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(Mhh)+Abs(Mhh))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MH0OS,MhhOS,MhhOS,AmpSumH0Tohhhh,AmpSum2H0Tohhhh,AmpSqH0Tohhhh) 
Else  
  Call SquareAmp_StoSS(MH0,Mhh,Mhh,AmpSumH0Tohhhh,AmpSum2H0Tohhhh,AmpSqH0Tohhhh) 
End if  
Else  
  AmpSqH0Tohhhh = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0Tohhhh.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp/2._dp*GammaTPS(MH0OS,MhhOS,MhhOS,helfactor*AmpSqH0Tohhhh)
Else 
  gP1LH0(gt1,i4) = 1._dp/2._dp*GammaTPS(MH0,Mhh,Mhh,helfactor*AmpSqH0Tohhhh)
End if 
If ((Abs(MRPH0Tohhhh).gt.1.0E-20_dp).or.(Abs(MRGH0Tohhhh).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0TohhVP(MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MH02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexH0TohhVP)

 Else 
Call Amplitude_VERTEX_Inert2_H0TohhVP(MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MH02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexH0TohhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0TohhVP(MH0,Mhh,MHp,MVP,MVWp,MH02,Mhh2,MHp2,            & 
& MVP2,MVWp2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplH0HpcVWpVP1,           & 
& cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,AmpVertexH0TohhVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->hh VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0TohhVP = 0._dp 
 AmpSum2H0TohhVP = 0._dp  
Else 
 AmpSumH0TohhVP = AmpVertexH0TohhVP + AmpWaveH0TohhVP
 AmpSum2H0TohhVP = AmpVertexH0TohhVP + AmpWaveH0TohhVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MhhOS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(Mhh)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MhhOS,0._dp,AmpSumH0TohhVP(:),AmpSum2H0TohhVP(:),AmpSqH0TohhVP) 
Else  
  Call SquareAmp_StoSV(MH0,Mhh,MVP,AmpSumH0TohhVP(:),AmpSum2H0TohhVP(:),AmpSqH0TohhVP) 
End if  
Else  
  AmpSqH0TohhVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0TohhVP.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MhhOS,0._dp,helfactor*AmpSqH0TohhVP)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,Mhh,MVP,helfactor*AmpSqH0TohhVP)
End if 
If ((Abs(MRPH0TohhVP).gt.1.0E-20_dp).or.(Abs(MRGH0TohhVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0TohhVZ(MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexH0TohhVZ)

 Else 
Call Amplitude_VERTEX_Inert2_H0TohhVZ(MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexH0TohhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0TohhVZ(MH0,Mhh,MHp,MVWp,MVZ,MH02,Mhh2,MHp2,            & 
& MVWp2,MVZ2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,           & 
& cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexH0TohhVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->hh VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0TohhVZ = 0._dp 
 AmpSum2H0TohhVZ = 0._dp  
Else 
 AmpSumH0TohhVZ = AmpVertexH0TohhVZ + AmpWaveH0TohhVZ
 AmpSum2H0TohhVZ = AmpVertexH0TohhVZ + AmpWaveH0TohhVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MhhOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(Mhh)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MH0OS,MhhOS,MVZOS,AmpSumH0TohhVZ(:),AmpSum2H0TohhVZ(:),AmpSqH0TohhVZ) 
Else  
  Call SquareAmp_StoSV(MH0,Mhh,MVZ,AmpSumH0TohhVZ(:),AmpSum2H0TohhVZ(:),AmpSqH0TohhVZ) 
End if  
Else  
  AmpSqH0TohhVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0TohhVZ.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MhhOS,MVZOS,helfactor*AmpSqH0TohhVZ)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,Mhh,MVZ,helfactor*AmpSqH0TohhVZ)
End if 
If ((Abs(MRPH0TohhVZ).gt.1.0E-20_dp).or.(Abs(MRGH0TohhVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToVPVP(MH0OS,MHpOS,MVP,MVWpOS,MH02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplHpcHpVPVP1,AmpVertexH0ToVPVP)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToVPVP(MH0OS,MHpOS,MVP,MVWpOS,MH02OS,MHp2OS,           & 
& MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplHpcHpVPVP1,AmpVertexH0ToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToVPVP(MH0,MHp,MVP,MVWp,MH02,MHp2,MVP2,MVWp2,          & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,    & 
& cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplHpcHpVPVP1,AmpVertexH0ToVPVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->VP VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToVPVP = 0._dp 
 AmpSum2H0ToVPVP = 0._dp  
Else 
 AmpSumH0ToVPVP = AmpVertexH0ToVPVP + AmpWaveH0ToVPVP
 AmpSum2H0ToVPVP = AmpVertexH0ToVPVP + AmpWaveH0ToVPVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MVP)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MH0OS,0._dp,0._dp,AmpSumH0ToVPVP(:),AmpSum2H0ToVPVP(:),AmpSqH0ToVPVP) 
Else  
  Call SquareAmp_StoVV(MH0,MVP,MVP,AmpSumH0ToVPVP(:),AmpSum2H0ToVPVP(:),AmpSqH0ToVPVP) 
End if  
Else  
  AmpSqH0ToVPVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToVPVP.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,0._dp,0._dp,helfactor*AmpSqH0ToVPVP)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MVP,MVP,helfactor*AmpSqH0ToVPVP)
End if 
If ((Abs(MRPH0ToVPVP).gt.1.0E-20_dp).or.(Abs(MRGH0ToVPVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToVPVZ(MH0OS,MHpOS,MVP,MVWpOS,MVZOS,MH02OS,            & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,              & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,              & 
& cplHpcHpVPVZ1,AmpVertexH0ToVPVZ)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToVPVZ(MH0OS,MHpOS,MVP,MVWpOS,MVZOS,MH02OS,            & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,              & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,              & 
& cplHpcHpVPVZ1,AmpVertexH0ToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToVPVZ(MH0,MHp,MVP,MVWp,MVZ,MH02,MHp2,MVP2,            & 
& MVWp2,MVZ2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVP1,          & 
& cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpcHpVPVZ1,AmpVertexH0ToVPVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->VP VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToVPVZ = 0._dp 
 AmpSum2H0ToVPVZ = 0._dp  
Else 
 AmpSumH0ToVPVZ = AmpVertexH0ToVPVZ + AmpWaveH0ToVPVZ
 AmpSum2H0ToVPVZ = AmpVertexH0ToVPVZ + AmpWaveH0ToVPVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(0.)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MVP)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MH0OS,0._dp,MVZOS,AmpSumH0ToVPVZ(:),AmpSum2H0ToVPVZ(:),AmpSqH0ToVPVZ) 
Else  
  Call SquareAmp_StoVV(MH0,MVP,MVZ,AmpSumH0ToVPVZ(:),AmpSum2H0ToVPVZ(:),AmpSqH0ToVPVZ) 
End if  
Else  
  AmpSqH0ToVPVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToVPVZ.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 2._dp*GammaTPS(MH0OS,0._dp,MVZOS,helfactor*AmpSqH0ToVPVZ)
Else 
  gP1LH0(gt1,i4) = 2._dp*GammaTPS(MH0,MVP,MVZ,helfactor*AmpSqH0ToVPVZ)
End if 
If ((Abs(MRPH0ToVPVZ).gt.1.0E-20_dp).or.(Abs(MRGH0ToVPVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToVWpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,           & 
& cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,             & 
& cplcVWpVWpVZ,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,              & 
& cplHpcHpcVWpVWp1,AmpVertexH0ToVWpcVWp)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToVWpcVWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,           & 
& cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,             & 
& cplcVWpVWpVZ,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,              & 
& cplHpcHpcVWpVWp1,AmpVertexH0ToVWpcVWp)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToVWpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcVWp,    & 
& cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,        & 
& cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,              & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,       & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexH0ToVWpcVWp)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->VWp conj[VWp] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToVWpcVWp = 0._dp 
 AmpSum2H0ToVWpcVWp = 0._dp  
Else 
 AmpSumH0ToVWpcVWp = AmpVertexH0ToVWpcVWp + AmpWaveH0ToVWpcVWp
 AmpSum2H0ToVWpcVWp = AmpVertexH0ToVWpcVWp + AmpWaveH0ToVWpcVWp 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MVWpOS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MVWp)+Abs(MVWp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MH0OS,MVWpOS,MVWpOS,AmpSumH0ToVWpcVWp(:),AmpSum2H0ToVWpcVWp(:),AmpSqH0ToVWpcVWp) 
Else  
  Call SquareAmp_StoVV(MH0,MVWp,MVWp,AmpSumH0ToVWpcVWp(:),AmpSum2H0ToVWpcVWp(:),AmpSqH0ToVWpcVWp) 
End if  
Else  
  AmpSqH0ToVWpcVWp = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToVWpcVWp.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 2._dp*GammaTPS(MH0OS,MVWpOS,MVWpOS,helfactor*AmpSqH0ToVWpcVWp)
Else 
  gP1LH0(gt1,i4) = 2._dp*GammaTPS(MH0,MVWp,MVWp,helfactor*AmpSqH0ToVWpcVWp)
End if 
If ((Abs(MRPH0ToVWpcVWp).gt.1.0E-20_dp).or.(Abs(MRGH0ToVWpcVWp).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
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
Call Amplitude_VERTEX_Inert2_H0ToVZVZ(MH0OS,MHpOS,MVWpOS,MVZOS,MH02OS,MHp2OS,         & 
& MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplHpcHpVZVZ1,AmpVertexH0ToVZVZ)

 Else 
Call Amplitude_VERTEX_Inert2_H0ToVZVZ(MH0OS,MHpOS,MVWpOS,MVZOS,MH02OS,MHp2OS,         & 
& MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplHpcHpVZVZ1,AmpVertexH0ToVZVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_H0ToVZVZ(MH0,MHp,MVWp,MVZ,MH02,MHp2,MVWp2,               & 
& MVZ2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,            & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplHpcHpVZVZ1,AmpVertexH0ToVZVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ H0->VZ VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumH0ToVZVZ = 0._dp 
 AmpSum2H0ToVZVZ = 0._dp  
Else 
 AmpSumH0ToVZVZ = AmpVertexH0ToVZVZ + AmpWaveH0ToVZVZ
 AmpSum2H0ToVZVZ = AmpVertexH0ToVZVZ + AmpWaveH0ToVZVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MH0OS).gt.(Abs(MVZOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MH0).gt.(Abs(MVZ)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MH0OS,MVZOS,MVZOS,AmpSumH0ToVZVZ(:),AmpSum2H0ToVZVZ(:),AmpSqH0ToVZVZ) 
Else  
  Call SquareAmp_StoVV(MH0,MVZ,MVZ,AmpSumH0ToVZVZ(:),AmpSum2H0ToVZVZ(:),AmpSqH0ToVZVZ) 
End if  
Else  
  AmpSqH0ToVZVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqH0ToVZVZ.eq.0._dp) Then 
  gP1LH0(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0OS,MVZOS,MVZOS,helfactor*AmpSqH0ToVZVZ)
Else 
  gP1LH0(gt1,i4) = 1._dp*GammaTPS(MH0,MVZ,MVZ,helfactor*AmpSqH0ToVZVZ)
End if 
If ((Abs(MRPH0ToVZVZ).gt.1.0E-20_dp).or.(Abs(MRGH0ToVZVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LH0(gt1,i4) 
End if 
i4=i4+1

isave = i4 
End Subroutine OneLoopDecay_H0

End Module Wrapper_OneLoopDecay_H0_Inert2
