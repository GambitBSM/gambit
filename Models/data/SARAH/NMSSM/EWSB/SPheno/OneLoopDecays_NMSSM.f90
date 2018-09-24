! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:26 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecays_NMSSM 
Use Couplings_NMSSM 
Use CouplingsCT_NMSSM 
Use Model_Data_NMSSM 
Use LoopCouplings_NMSSM 
Use LoopMasses_NMSSM 
Use RGEs_NMSSM 
Use Tadpoles_NMSSM 
Use Kinematics 
Use CouplingsForDecays_NMSSM 
 
Use Wrapper_OneLoopDecay_Sd_NMSSM 
Use Wrapper_OneLoopDecay_Su_NMSSM 
Use Wrapper_OneLoopDecay_Se_NMSSM 
Use Wrapper_OneLoopDecay_Sv_NMSSM 
Use Wrapper_OneLoopDecay_hh_NMSSM 
Use Wrapper_OneLoopDecay_Ah_NMSSM 
Use Wrapper_OneLoopDecay_Hpm_NMSSM 
Use Wrapper_OneLoopDecay_Glu_NMSSM 
Use Wrapper_OneLoopDecay_Chi_NMSSM 
Use Wrapper_OneLoopDecay_Cha_NMSSM 
Use Wrapper_OneLoopDecay_Fu_NMSSM 

 
Contains 
 
Subroutine getZCouplings(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,Yd,Td,               & 
& ZD,Ye,Te,ZE,Yu,Tu,ZU,ZV,g3,TW,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,           & 
& cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,           & 
& cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,      & 
& cplSdcHpmcSu,cplSecHpmcSv,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhhhhhhh,cplAhhhHpmcHpm,        & 
& cplAhhhSdcSd,cplAhhhSecSe,cplAhhhSucSu,cplAhHpmSucSd,cplAhHpmSvcSe,cplAhSdcHpmcSu,     & 
& cplAhSecHpmcSv,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,      & 
& cplhhhhSvcSv,cplhhHpmSucSd,cplhhHpmSvcSe,cplhhSdcHpmcSu,cplhhSecHpmcSv,cplHpmHpmcHpmcHpm,& 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSdSvcSdcSv,cplSdSvcSecSu,cplSeSecSecSe,cplSeSucSdcSv,   & 
& cplSeSucSecSu,cplSeSvcSecSv,cplSuSucSucSu,cplSuSvcSucSv,cplSvSvcSvcSv,cplAhhhVZ,       & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,      & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,      & 
& cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhcVWmVWm,          & 
& cplAhAhVZVZ,cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,cplAhcHpmVWmVZ,               & 
& cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,cplhhcHpmVPVWm,               & 
& cplhhcHpmVWmVZ,cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,         & 
& cplSdcSdVGVG,cplSdcSdVGVP,cplSdcSdVGVZ,cplSdcSucVWmVG,cplSdcSdVPVP,cplSdcSdVPVZ,       & 
& cplSdcSucVWmVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,cplSdcSucVWmVZ,cplSecSeVPVP,               & 
& cplSecSeVPVZ,cplSecSvcVWmVP,cplSecSecVWmVWm,cplSecSeVZVZ,cplSecSvcVWmVZ,               & 
& cplSucSuVGVG,cplSucSuVGVP,cplSucSdVGVWm,cplSucSuVGVZ,cplSucSuVPVP,cplSucSdVPVWm,       & 
& cplSucSuVPVZ,cplSucSdVWmVZ,cplSucSucVWmVWm,cplSucSuVZVZ,cplSvcSeVPVWm,cplSvcSeVWmVZ,   & 
& cplSvcSvcVWmVWm,cplSvcSvVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,        & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,        & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,   & 
& cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,           & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,            & 
& cplGluGluVGR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,   & 
& cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,    & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3, & 
& cplcgGgGVG,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,               & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,       & 
& cplcgWpCgAcHpm,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,     & 
& cplcgWmgZHpm,cplcgWpCgZcHpm,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,           & 
& ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZcplAhAhAh,ZcplAhAhhh,           & 
& ZcplAhhhhh,ZcplAhHpmcHpm,ZcplAhSdcSd,ZcplAhSecSe,ZcplAhSucSu,Zcplhhhhhh,               & 
& ZcplhhHpmcHpm,ZcplhhSdcSd,ZcplhhSecSe,ZcplhhSucSu,ZcplhhSvcSv,ZcplHpmSucSd,            & 
& ZcplHpmSvcSe,ZcplSdcHpmcSu,ZcplSecHpmcSv,ZcplAhAhAhAh,ZcplAhAhAhhh,ZcplAhAhhhhh,       & 
& ZcplAhAhHpmcHpm,ZcplAhAhSdcSd,ZcplAhAhSecSe,ZcplAhAhSucSu,ZcplAhAhSvcSv,               & 
& ZcplAhhhhhhh,ZcplAhhhHpmcHpm,ZcplAhhhSdcSd,ZcplAhhhSecSe,ZcplAhhhSucSu,ZcplAhHpmSucSd, & 
& ZcplAhHpmSvcSe,ZcplAhSdcHpmcSu,ZcplAhSecHpmcSv,Zcplhhhhhhhh,ZcplhhhhHpmcHpm,           & 
& ZcplhhhhSdcSd,ZcplhhhhSecSe,ZcplhhhhSucSu,ZcplhhhhSvcSv,ZcplhhHpmSucSd,ZcplhhHpmSvcSe, & 
& ZcplhhSdcHpmcSu,ZcplhhSecHpmcSv,ZcplHpmHpmcHpmcHpm,ZcplHpmSdcHpmcSd,ZcplHpmSecHpmcSe,  & 
& ZcplHpmSucHpmcSu,ZcplHpmSvcHpmcSv,ZcplSdSdcSdcSd,ZcplSdSecSdcSe,ZcplSdSucSdcSu,        & 
& ZcplSdSvcSdcSv,ZcplSdSvcSecSu,ZcplSeSecSecSe,ZcplSeSucSdcSv,ZcplSeSucSecSu,            & 
& ZcplSeSvcSecSv,ZcplSuSucSucSu,ZcplSuSvcSucSv,ZcplSvSvcSvcSv,ZcplAhhhVZ,ZcplAhHpmcVWm,  & 
& ZcplAhcHpmVWm,ZcplhhHpmcVWm,ZcplhhcHpmVWm,ZcplHpmcHpmVP,ZcplHpmcHpmVZ,ZcplSdcSdVG,     & 
& ZcplSdcSdVP,ZcplSdcSdVZ,ZcplSdcSucVWm,ZcplSecSeVP,ZcplSecSeVZ,ZcplSecSvcVWm,           & 
& ZcplSucSuVG,ZcplSucSuVP,ZcplSucSdVWm,ZcplSucSuVZ,ZcplSvcSeVWm,ZcplSvcSvVZ,             & 
& ZcplhhcVWmVWm,ZcplhhVZVZ,ZcplHpmcVWmVP,ZcplHpmcVWmVZ,ZcplcHpmVPVWm,ZcplcHpmVWmVZ,      & 
& ZcplAhAhcVWmVWm,ZcplAhAhVZVZ,ZcplAhHpmcVWmVP,ZcplAhHpmcVWmVZ,ZcplAhcHpmVPVWm,          & 
& ZcplAhcHpmVWmVZ,ZcplhhhhcVWmVWm,ZcplhhhhVZVZ,ZcplhhHpmcVWmVP,ZcplhhHpmcVWmVZ,          & 
& ZcplhhcHpmVPVWm,ZcplhhcHpmVWmVZ,ZcplHpmcHpmVPVP,ZcplHpmcHpmVPVZ,ZcplHpmcHpmcVWmVWm,    & 
& ZcplHpmcHpmVZVZ,ZcplSdcSdVGVG,ZcplSdcSdVGVP,ZcplSdcSdVGVZ,ZcplSdcSucVWmVG,             & 
& ZcplSdcSdVPVP,ZcplSdcSdVPVZ,ZcplSdcSucVWmVP,ZcplSdcSdcVWmVWm,ZcplSdcSdVZVZ,            & 
& ZcplSdcSucVWmVZ,ZcplSecSeVPVP,ZcplSecSeVPVZ,ZcplSecSvcVWmVP,ZcplSecSecVWmVWm,          & 
& ZcplSecSeVZVZ,ZcplSecSvcVWmVZ,ZcplSucSuVGVG,ZcplSucSuVGVP,ZcplSucSdVGVWm,              & 
& ZcplSucSuVGVZ,ZcplSucSuVPVP,ZcplSucSdVPVWm,ZcplSucSuVPVZ,ZcplSucSdVWmVZ,               & 
& ZcplSucSucVWmVWm,ZcplSucSuVZVZ,ZcplSvcSeVPVWm,ZcplSvcSeVWmVZ,ZcplSvcSvcVWmVWm,         & 
& ZcplSvcSvVZVZ,ZcplVGVGVG,ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplcChaChaAhL,ZcplcChaChaAhR,    & 
& ZcplChiChiAhL,ZcplChiChiAhR,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFeFeAhL,ZcplcFeFeAhR,       & 
& ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplChaFucSdL,               & 
& ZcplChaFucSdR,ZcplChaFvcSeL,ZcplChaFvcSeR,ZcplcChaChahhL,ZcplcChaChahhR,               & 
& ZcplcFdChaSuL,ZcplcFdChaSuR,ZcplcFeChaSvL,ZcplcFeChaSvR,ZcplChiChihhL,ZcplChiChihhR,   & 
& ZcplChiFdcSdL,ZcplChiFdcSdR,ZcplChiFecSeL,ZcplChiFecSeR,ZcplChiFucSuL,ZcplChiFucSuR,   & 
& ZcplChiFvcSvL,ZcplChiFvcSvR,ZcplcChaChiHpmL,ZcplcChaChiHpmR,ZcplcFdChiSdL,             & 
& ZcplcFdChiSdR,ZcplcFeChiSeL,ZcplcFeChiSeR,ZcplcFuChiSuL,ZcplcFuChiSuR,ZcplcFvChiSvL,   & 
& ZcplcFvChiSvR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcChaFdcSuL,    & 
& ZcplcChaFdcSuR,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,ZcplcFeFehhL,ZcplcFeFehhR,ZcplcChaFecSvL, & 
& ZcplcChaFecSvR,ZcplcFvFecHpmL,ZcplcFvFecHpmR,ZcplGluFucSuL,ZcplGluFucSuR,              & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFuHpmL,ZcplcFdFuHpmR,ZcplcFeFvHpmL,ZcplcFeFvHpmR,     & 
& ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplcChacFuSdL,ZcplcChacFuSdR, & 
& ZcplcChacFvSeL,ZcplcChacFvSeR,ZcplChiChacVWmL,ZcplChiChacVWmR,ZcplcChaChaVPL,          & 
& ZcplcChaChaVPR,ZcplcChaChaVZL,ZcplcChaChaVZR,ZcplChiChiVZL,ZcplChiChiVZR,              & 
& ZcplcChaChiVWmL,ZcplcChaChiVWmR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,   & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFeFeVPL,ZcplcFeFeVPR,     & 
& ZcplcFeFeVZL,ZcplcFeFeVZR,ZcplcFvFecVWmL,ZcplcFvFecVWmR,ZcplcFuFuVGL,ZcplcFuFuVGR,     & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,       & 
& ZcplcFeFvVWmL,ZcplcFeFvVWmR,ZcplcFvFvVZL,ZcplcFvFvVZR,ZcplGluGluVGL,ZcplGluGluVGR,     & 
& ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,ZcplcVWmVPVPVWm1,ZcplcVWmVPVPVWm2,           & 
& ZcplcVWmVPVPVWm3,ZcplcVWmVPVWmVZ1,ZcplcVWmVPVWmVZ2,ZcplcVWmVPVWmVZ3,ZcplcVWmcVWmVWmVWm1,& 
& ZcplcVWmcVWmVWmVWm2,ZcplcVWmcVWmVWmVWm3,ZcplcVWmVWmVZVZ1,ZcplcVWmVWmVZVZ2,             & 
& ZcplcVWmVWmVZVZ3,ZcplcgGgGVG,ZcplcgWmgAVWm,ZcplcgWpCgAcVWm,ZcplcgWmgWmVP,              & 
& ZcplcgWmgWmVZ,ZcplcgAgWmcVWm,ZcplcgZgWmcVWm,ZcplcgWpCgWpCVP,ZcplcgAgWpCVWm,            & 
& ZcplcgZgWpCVWm,ZcplcgWpCgWpCVZ,ZcplcgWmgZVWm,ZcplcgWpCgZcVWm,ZcplcgWmgWmAh,            & 
& ZcplcgWpCgWpCAh,ZcplcgZgAhh,ZcplcgWmgAHpm,ZcplcgWpCgAcHpm,ZcplcgWmgWmhh,               & 
& ZcplcgZgWmcHpm,ZcplcgWpCgWpChh,ZcplcgZgWpCHpm,ZcplcgZgZhh,ZcplcgWmgZHpm,               & 
& ZcplcgWpCgZcHpm)

Implicit None

Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),g1,g2,ZH(3,3),ZP(2,2),g3,TW

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,Yd(3,3),Td(3,3),ZD(6,6),Ye(3,3),Te(3,3),ZE(6,6),Yu(3,3),              & 
& Tu(3,3),ZU(6,6),ZV(3,3),UM(2,2),UP(2,2),ZN(5,5),ZDL(3,3),ZDR(3,3),ZEL(3,3),            & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),pG

Complex(dp), Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplhhSvcSv(3,3,3),               & 
& cplHpmSucSd(2,6,6),cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),         & 
& cplAhAhAhAh(3,3,3,3),cplAhAhAhhh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),& 
& cplAhAhSdcSd(3,3,6,6),cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplAhAhSvcSv(3,3,3,3),& 
& cplAhhhhhhh(3,3,3,3),cplAhhhHpmcHpm(3,3,2,2),cplAhhhSdcSd(3,3,6,6),cplAhhhSecSe(3,3,6,6),& 
& cplAhhhSucSu(3,3,6,6),cplAhHpmSucSd(3,2,6,6),cplAhHpmSvcSe(3,2,3,6),cplAhSdcHpmcSu(3,6,2,6),& 
& cplAhSecHpmcSv(3,6,2,3),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),cplhhhhSdcSd(3,3,6,6),& 
& cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplhhhhSvcSv(3,3,3,3),cplhhHpmSucSd(3,2,6,6),& 
& cplhhHpmSvcSe(3,2,3,6),cplhhSdcHpmcSu(3,6,2,6),cplhhSecHpmcSv(3,6,2,3),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSdSvcSdcSv(6,3,6,3),cplSdSvcSecSu(6,3,6,6),cplSeSecSecSe(6,6,6,6),cplSeSucSdcSv(6,6,6,3),& 
& cplSeSucSecSu(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSuSvcSucSv(6,3,6,3),& 
& cplSvSvcSvcSv(3,3,3,3),cplAhhhVZ(3,3),cplAhHpmcVWm(3,2),cplAhcHpmVWm(3,2),             & 
& cplhhHpmcVWm(3,2),cplhhcHpmVWm(3,2),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),               & 
& cplSdcSdVG(6,6),cplSdcSdVP(6,6),cplSdcSdVZ(6,6),cplSdcSucVWm(6,6),cplSecSeVP(6,6),     & 
& cplSecSeVZ(6,6),cplSecSvcVWm(6,3),cplSucSuVG(6,6),cplSucSuVP(6,6),cplSucSdVWm(6,6),    & 
& cplSucSuVZ(6,6),cplSvcSeVWm(3,6),cplSvcSvVZ(3,3),cplhhcVWmVWm(3),cplhhVZVZ(3),         & 
& cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplAhAhcVWmVWm(3,3),   & 
& cplAhAhVZVZ(3,3),cplAhHpmcVWmVP(3,2),cplAhHpmcVWmVZ(3,2),cplAhcHpmVPVWm(3,2),          & 
& cplAhcHpmVWmVZ(3,2),cplhhhhcVWmVWm(3,3),cplhhhhVZVZ(3,3),cplhhHpmcVWmVP(3,2),          & 
& cplhhHpmcVWmVZ(3,2),cplhhcHpmVPVWm(3,2),cplhhcHpmVWmVZ(3,2),cplHpmcHpmVPVP(2,2),       & 
& cplHpmcHpmVPVZ(2,2),cplHpmcHpmcVWmVWm(2,2),cplHpmcHpmVZVZ(2,2),cplSdcSdVGVG(6,6),      & 
& cplSdcSdVGVP(6,6),cplSdcSdVGVZ(6,6),cplSdcSucVWmVG(6,6),cplSdcSdVPVP(6,6),             & 
& cplSdcSdVPVZ(6,6),cplSdcSucVWmVP(6,6),cplSdcSdcVWmVWm(6,6),cplSdcSdVZVZ(6,6),          & 
& cplSdcSucVWmVZ(6,6),cplSecSeVPVP(6,6),cplSecSeVPVZ(6,6),cplSecSvcVWmVP(6,3),           & 
& cplSecSecVWmVWm(6,6),cplSecSeVZVZ(6,6),cplSecSvcVWmVZ(6,3),cplSucSuVGVG(6,6),          & 
& cplSucSuVGVP(6,6),cplSucSdVGVWm(6,6),cplSucSuVGVZ(6,6),cplSucSuVPVP(6,6),              & 
& cplSucSdVPVWm(6,6),cplSucSuVPVZ(6,6),cplSucSdVWmVZ(6,6),cplSucSucVWmVWm(6,6),          & 
& cplSucSuVZVZ(6,6),cplSvcSeVPVWm(3,6),cplSvcSeVWmVZ(3,6),cplSvcSvcVWmVWm(3,3),          & 
& cplSvcSvVZVZ(3,3),cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL(2,2,3),            & 
& cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),       & 
& cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),           & 
& cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),    & 
& cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3)

Complex(dp), Intent(in) :: cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),      & 
& cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),       & 
& cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),       & 
& cplChiFucSuR(5,3,6),cplChiFvcSvL(5,3,3),cplChiFvcSvR(5,3,3),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplcFvChiSvL(3,5,3),       & 
& cplcFvChiSvR(3,5,3),cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),            & 
& cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),     & 
& cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),       & 
& cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),      & 
& cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),           & 
& cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),         & 
& cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),            & 
& cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),cplChiChacVWmL(5,2),    & 
& cplChiChacVWmR(5,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),          & 
& cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplcChaChiVWmL(2,5),            & 
& cplcChaChiVWmR(2,5),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecVWmL(3,3),& 
& cplcFvFecVWmR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),& 
& cplcFeFvVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplGluGluVGL,cplGluGluVGR,         & 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,& 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2, & 
& cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,         & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm, & 
& cplcgWmgWmAh(3),cplcgWpCgWpCAh(3),cplcgZgAhh(3),cplcgWmgAHpm(2),cplcgWpCgAcHpm(2),     & 
& cplcgWmgWmhh(3),cplcgZgWmcHpm(2),cplcgWpCgWpChh(3),cplcgZgWpCHpm(2),cplcgZgZhh(3),     & 
& cplcgWmgZHpm(2),cplcgWpCgZcHpm(2)

Complex(dp), Intent(in) :: ZRUZD(6,6),ZRUZV(3,3),ZRUZU(6,6),ZRUZE(6,6),ZRUZH(3,3),ZRUZA(3,3),ZRUZP(2,2),         & 
& ZRUZN(5,5),ZRUUM(2,2),ZRUUP(2,2),ZRUZEL(3,3),ZRUZER(3,3),ZRUZDL(3,3),ZRUZDR(3,3),      & 
& ZRUZUL(3,3),ZRUZUR(3,3)

Integer :: gt1, gt2
Complex(dp) :: TempcplAhAhAh(3,3,3),TempcplAhAhhh(3,3,3),TempcplAhhhhh(3,3,3),TempcplAhHpmcHpm(3,2,2),& 
& TempcplAhSdcSd(3,6,6),TempcplAhSecSe(3,6,6),TempcplAhSucSu(3,6,6),Tempcplhhhhhh(3,3,3),& 
& TempcplhhHpmcHpm(3,2,2),TempcplhhSdcSd(3,6,6),TempcplhhSecSe(3,6,6),TempcplhhSucSu(3,6,6),& 
& TempcplhhSvcSv(3,3,3),TempcplHpmSucSd(2,6,6),TempcplHpmSvcSe(2,3,6),TempcplSdcHpmcSu(6,2,6),& 
& TempcplSecHpmcSv(6,2,3),TempcplAhAhAhAh(3,3,3,3),TempcplAhAhAhhh(3,3,3,3),             & 
& TempcplAhAhhhhh(3,3,3,3),TempcplAhAhHpmcHpm(3,3,2,2),TempcplAhAhSdcSd(3,3,6,6),        & 
& TempcplAhAhSecSe(3,3,6,6),TempcplAhAhSucSu(3,3,6,6),TempcplAhAhSvcSv(3,3,3,3),         & 
& TempcplAhhhhhhh(3,3,3,3),TempcplAhhhHpmcHpm(3,3,2,2),TempcplAhhhSdcSd(3,3,6,6),        & 
& TempcplAhhhSecSe(3,3,6,6),TempcplAhhhSucSu(3,3,6,6),TempcplAhHpmSucSd(3,2,6,6),        & 
& TempcplAhHpmSvcSe(3,2,3,6),TempcplAhSdcHpmcSu(3,6,2,6),TempcplAhSecHpmcSv(3,6,2,3),    & 
& Tempcplhhhhhhhh(3,3,3,3),TempcplhhhhHpmcHpm(3,3,2,2),TempcplhhhhSdcSd(3,3,6,6),        & 
& TempcplhhhhSecSe(3,3,6,6),TempcplhhhhSucSu(3,3,6,6),TempcplhhhhSvcSv(3,3,3,3),         & 
& TempcplhhHpmSucSd(3,2,6,6),TempcplhhHpmSvcSe(3,2,3,6),TempcplhhSdcHpmcSu(3,6,2,6),     & 
& TempcplhhSecHpmcSv(3,6,2,3),TempcplHpmHpmcHpmcHpm(2,2,2,2),TempcplHpmSdcHpmcSd(2,6,2,6),& 
& TempcplHpmSecHpmcSe(2,6,2,6),TempcplHpmSucHpmcSu(2,6,2,6),TempcplHpmSvcHpmcSv(2,3,2,3),& 
& TempcplSdSdcSdcSd(6,6,6,6),TempcplSdSecSdcSe(6,6,6,6),TempcplSdSucSdcSu(6,6,6,6),      & 
& TempcplSdSvcSdcSv(6,3,6,3),TempcplSdSvcSecSu(6,3,6,6),TempcplSeSecSecSe(6,6,6,6),      & 
& TempcplSeSucSdcSv(6,6,6,3),TempcplSeSucSecSu(6,6,6,6),TempcplSeSvcSecSv(6,3,6,3),      & 
& TempcplSuSucSucSu(6,6,6,6),TempcplSuSvcSucSv(6,3,6,3),TempcplSvSvcSvcSv(3,3,3,3),      & 
& TempcplAhhhVZ(3,3),TempcplAhHpmcVWm(3,2),TempcplAhcHpmVWm(3,2),TempcplhhHpmcVWm(3,2),  & 
& TempcplhhcHpmVWm(3,2),TempcplHpmcHpmVP(2,2),TempcplHpmcHpmVZ(2,2),TempcplSdcSdVG(6,6), & 
& TempcplSdcSdVP(6,6),TempcplSdcSdVZ(6,6),TempcplSdcSucVWm(6,6),TempcplSecSeVP(6,6),     & 
& TempcplSecSeVZ(6,6),TempcplSecSvcVWm(6,3),TempcplSucSuVG(6,6),TempcplSucSuVP(6,6),     & 
& TempcplSucSdVWm(6,6),TempcplSucSuVZ(6,6),TempcplSvcSeVWm(3,6),TempcplSvcSvVZ(3,3),     & 
& TempcplhhcVWmVWm(3),TempcplhhVZVZ(3),TempcplHpmcVWmVP(2),TempcplHpmcVWmVZ(2),          & 
& TempcplcHpmVPVWm(2),TempcplcHpmVWmVZ(2),TempcplAhAhcVWmVWm(3,3),TempcplAhAhVZVZ(3,3),  & 
& TempcplAhHpmcVWmVP(3,2),TempcplAhHpmcVWmVZ(3,2),TempcplAhcHpmVPVWm(3,2),               & 
& TempcplAhcHpmVWmVZ(3,2),TempcplhhhhcVWmVWm(3,3),TempcplhhhhVZVZ(3,3),TempcplhhHpmcVWmVP(3,2),& 
& TempcplhhHpmcVWmVZ(3,2),TempcplhhcHpmVPVWm(3,2),TempcplhhcHpmVWmVZ(3,2),               & 
& TempcplHpmcHpmVPVP(2,2),TempcplHpmcHpmVPVZ(2,2),TempcplHpmcHpmcVWmVWm(2,2),            & 
& TempcplHpmcHpmVZVZ(2,2),TempcplSdcSdVGVG(6,6),TempcplSdcSdVGVP(6,6),TempcplSdcSdVGVZ(6,6),& 
& TempcplSdcSucVWmVG(6,6),TempcplSdcSdVPVP(6,6),TempcplSdcSdVPVZ(6,6),TempcplSdcSucVWmVP(6,6),& 
& TempcplSdcSdcVWmVWm(6,6),TempcplSdcSdVZVZ(6,6),TempcplSdcSucVWmVZ(6,6),TempcplSecSeVPVP(6,6),& 
& TempcplSecSeVPVZ(6,6),TempcplSecSvcVWmVP(6,3),TempcplSecSecVWmVWm(6,6),TempcplSecSeVZVZ(6,6),& 
& TempcplSecSvcVWmVZ(6,3),TempcplSucSuVGVG(6,6),TempcplSucSuVGVP(6,6),TempcplSucSdVGVWm(6,6),& 
& TempcplSucSuVGVZ(6,6),TempcplSucSuVPVP(6,6),TempcplSucSdVPVWm(6,6),TempcplSucSuVPVZ(6,6),& 
& TempcplSucSdVWmVZ(6,6),TempcplSucSucVWmVWm(6,6),TempcplSucSuVZVZ(6,6),TempcplSvcSeVPVWm(3,6)

Complex(dp) :: TempcplSvcSeVWmVZ(3,6),TempcplSvcSvcVWmVWm(3,3),TempcplSvcSvVZVZ(3,3),TempcplVGVGVG,   & 
& TempcplcVWmVPVWm,TempcplcVWmVWmVZ,TempcplcChaChaAhL(2,2,3),TempcplcChaChaAhR(2,2,3),   & 
& TempcplChiChiAhL(5,5,3),TempcplChiChiAhR(5,5,3),TempcplcFdFdAhL(3,3,3),TempcplcFdFdAhR(3,3,3),& 
& TempcplcFeFeAhL(3,3,3),TempcplcFeFeAhR(3,3,3),TempcplcFuFuAhL(3,3,3),TempcplcFuFuAhR(3,3,3),& 
& TempcplChiChacHpmL(5,2,2),TempcplChiChacHpmR(5,2,2),TempcplChaFucSdL(2,3,6),           & 
& TempcplChaFucSdR(2,3,6),TempcplChaFvcSeL(2,3,6),TempcplChaFvcSeR(2,3,6),               & 
& TempcplcChaChahhL(2,2,3),TempcplcChaChahhR(2,2,3),TempcplcFdChaSuL(3,2,6),             & 
& TempcplcFdChaSuR(3,2,6),TempcplcFeChaSvL(3,2,3),TempcplcFeChaSvR(3,2,3),               & 
& TempcplChiChihhL(5,5,3),TempcplChiChihhR(5,5,3),TempcplChiFdcSdL(5,3,6),               & 
& TempcplChiFdcSdR(5,3,6),TempcplChiFecSeL(5,3,6),TempcplChiFecSeR(5,3,6),               & 
& TempcplChiFucSuL(5,3,6),TempcplChiFucSuR(5,3,6),TempcplChiFvcSvL(5,3,3),               & 
& TempcplChiFvcSvR(5,3,3),TempcplcChaChiHpmL(2,5,2),TempcplcChaChiHpmR(2,5,2),           & 
& TempcplcFdChiSdL(3,5,6),TempcplcFdChiSdR(3,5,6),TempcplcFeChiSeL(3,5,6),               & 
& TempcplcFeChiSeR(3,5,6),TempcplcFuChiSuL(3,5,6),TempcplcFuChiSuR(3,5,6),               & 
& TempcplcFvChiSvL(3,5,3),TempcplcFvChiSvR(3,5,3),TempcplGluFdcSdL(3,6),TempcplGluFdcSdR(3,6),& 
& TempcplcFdFdhhL(3,3,3),TempcplcFdFdhhR(3,3,3),TempcplcChaFdcSuL(2,3,6),TempcplcChaFdcSuR(2,3,6),& 
& TempcplcFuFdcHpmL(3,3,2),TempcplcFuFdcHpmR(3,3,2),TempcplcFeFehhL(3,3,3),              & 
& TempcplcFeFehhR(3,3,3),TempcplcChaFecSvL(2,3,3),TempcplcChaFecSvR(2,3,3),              & 
& TempcplcFvFecHpmL(3,3,2),TempcplcFvFecHpmR(3,3,2),TempcplGluFucSuL(3,6),               & 
& TempcplGluFucSuR(3,6),TempcplcFuFuhhL(3,3,3),TempcplcFuFuhhR(3,3,3),TempcplcFdFuHpmL(3,3,2),& 
& TempcplcFdFuHpmR(3,3,2),TempcplcFeFvHpmL(3,3,2),TempcplcFeFvHpmR(3,3,2),               & 
& TempcplcFdGluSdL(3,6),TempcplcFdGluSdR(3,6),TempcplcFuGluSuL(3,6),TempcplcFuGluSuR(3,6),& 
& TempcplcChacFuSdL(2,3,6),TempcplcChacFuSdR(2,3,6),TempcplcChacFvSeL(2,3,6),            & 
& TempcplcChacFvSeR(2,3,6),TempcplChiChacVWmL(5,2),TempcplChiChacVWmR(5,2),              & 
& TempcplcChaChaVPL(2,2),TempcplcChaChaVPR(2,2),TempcplcChaChaVZL(2,2),TempcplcChaChaVZR(2,2),& 
& TempcplChiChiVZL(5,5),TempcplChiChiVZR(5,5),TempcplcChaChiVWmL(2,5),TempcplcChaChiVWmR(2,5),& 
& TempcplcFdFdVGL(3,3),TempcplcFdFdVGR(3,3),TempcplcFdFdVPL(3,3),TempcplcFdFdVPR(3,3),   & 
& TempcplcFdFdVZL(3,3),TempcplcFdFdVZR(3,3),TempcplcFuFdcVWmL(3,3),TempcplcFuFdcVWmR(3,3),& 
& TempcplcFeFeVPL(3,3),TempcplcFeFeVPR(3,3),TempcplcFeFeVZL(3,3),TempcplcFeFeVZR(3,3),   & 
& TempcplcFvFecVWmL(3,3),TempcplcFvFecVWmR(3,3),TempcplcFuFuVGL(3,3),TempcplcFuFuVGR(3,3),& 
& TempcplcFuFuVPL(3,3),TempcplcFuFuVPR(3,3),TempcplcFdFuVWmL(3,3),TempcplcFdFuVWmR(3,3), & 
& TempcplcFuFuVZL(3,3),TempcplcFuFuVZR(3,3),TempcplcFeFvVWmL(3,3),TempcplcFeFvVWmR(3,3), & 
& TempcplcFvFvVZL(3,3),TempcplcFvFvVZR(3,3),TempcplGluGluVGL,TempcplGluGluVGR,           & 
& TempcplVGVGVGVG1,TempcplVGVGVGVG2,TempcplVGVGVGVG3,TempcplcVWmVPVPVWm1,TempcplcVWmVPVPVWm2,& 
& TempcplcVWmVPVPVWm3,TempcplcVWmVPVWmVZ1,TempcplcVWmVPVWmVZ2,TempcplcVWmVPVWmVZ3,       & 
& TempcplcVWmcVWmVWmVWm1,TempcplcVWmcVWmVWmVWm2,TempcplcVWmcVWmVWmVWm3,TempcplcVWmVWmVZVZ1,& 
& TempcplcVWmVWmVZVZ2,TempcplcVWmVWmVZVZ3,TempcplcgGgGVG,TempcplcgWmgAVWm

Complex(dp) :: TempcplcgWpCgAcVWm,TempcplcgWmgWmVP,TempcplcgWmgWmVZ,TempcplcgAgWmcVWm,TempcplcgZgWmcVWm,& 
& TempcplcgWpCgWpCVP,TempcplcgAgWpCVWm,TempcplcgZgWpCVWm,TempcplcgWpCgWpCVZ,             & 
& TempcplcgWmgZVWm,TempcplcgWpCgZcVWm,TempcplcgWmgWmAh(3),TempcplcgWpCgWpCAh(3),         & 
& TempcplcgZgAhh(3),TempcplcgWmgAHpm(2),TempcplcgWpCgAcHpm(2),TempcplcgWmgWmhh(3),       & 
& TempcplcgZgWmcHpm(2),TempcplcgWpCgWpChh(3),TempcplcgZgWpCHpm(2),TempcplcgZgZhh(3),     & 
& TempcplcgWmgZHpm(2),TempcplcgWpCgZcHpm(2)

Complex(dp), Intent(out) :: ZcplAhAhAh(3,3,3),ZcplAhAhhh(3,3,3),ZcplAhhhhh(3,3,3),ZcplAhHpmcHpm(3,2,2),           & 
& ZcplAhSdcSd(3,6,6),ZcplAhSecSe(3,6,6),ZcplAhSucSu(3,6,6),Zcplhhhhhh(3,3,3),            & 
& ZcplhhHpmcHpm(3,2,2),ZcplhhSdcSd(3,6,6),ZcplhhSecSe(3,6,6),ZcplhhSucSu(3,6,6),         & 
& ZcplhhSvcSv(3,3,3),ZcplHpmSucSd(2,6,6),ZcplHpmSvcSe(2,3,6),ZcplSdcHpmcSu(6,2,6),       & 
& ZcplSecHpmcSv(6,2,3),ZcplAhAhAhAh(3,3,3,3),ZcplAhAhAhhh(3,3,3,3),ZcplAhAhhhhh(3,3,3,3),& 
& ZcplAhAhHpmcHpm(3,3,2,2),ZcplAhAhSdcSd(3,3,6,6),ZcplAhAhSecSe(3,3,6,6),ZcplAhAhSucSu(3,3,6,6),& 
& ZcplAhAhSvcSv(3,3,3,3),ZcplAhhhhhhh(3,3,3,3),ZcplAhhhHpmcHpm(3,3,2,2),ZcplAhhhSdcSd(3,3,6,6),& 
& ZcplAhhhSecSe(3,3,6,6),ZcplAhhhSucSu(3,3,6,6),ZcplAhHpmSucSd(3,2,6,6),ZcplAhHpmSvcSe(3,2,3,6),& 
& ZcplAhSdcHpmcSu(3,6,2,6),ZcplAhSecHpmcSv(3,6,2,3),Zcplhhhhhhhh(3,3,3,3),               & 
& ZcplhhhhHpmcHpm(3,3,2,2),ZcplhhhhSdcSd(3,3,6,6),ZcplhhhhSecSe(3,3,6,6),ZcplhhhhSucSu(3,3,6,6),& 
& ZcplhhhhSvcSv(3,3,3,3),ZcplhhHpmSucSd(3,2,6,6),ZcplhhHpmSvcSe(3,2,3,6),ZcplhhSdcHpmcSu(3,6,2,6),& 
& ZcplhhSecHpmcSv(3,6,2,3),ZcplHpmHpmcHpmcHpm(2,2,2,2),ZcplHpmSdcHpmcSd(2,6,2,6),        & 
& ZcplHpmSecHpmcSe(2,6,2,6),ZcplHpmSucHpmcSu(2,6,2,6),ZcplHpmSvcHpmcSv(2,3,2,3),         & 
& ZcplSdSdcSdcSd(6,6,6,6),ZcplSdSecSdcSe(6,6,6,6),ZcplSdSucSdcSu(6,6,6,6),               & 
& ZcplSdSvcSdcSv(6,3,6,3),ZcplSdSvcSecSu(6,3,6,6),ZcplSeSecSecSe(6,6,6,6),               & 
& ZcplSeSucSdcSv(6,6,6,3),ZcplSeSucSecSu(6,6,6,6),ZcplSeSvcSecSv(6,3,6,3),               & 
& ZcplSuSucSucSu(6,6,6,6),ZcplSuSvcSucSv(6,3,6,3),ZcplSvSvcSvcSv(3,3,3,3),               & 
& ZcplAhhhVZ(3,3),ZcplAhHpmcVWm(3,2),ZcplAhcHpmVWm(3,2),ZcplhhHpmcVWm(3,2),              & 
& ZcplhhcHpmVWm(3,2),ZcplHpmcHpmVP(2,2),ZcplHpmcHpmVZ(2,2),ZcplSdcSdVG(6,6),             & 
& ZcplSdcSdVP(6,6),ZcplSdcSdVZ(6,6),ZcplSdcSucVWm(6,6),ZcplSecSeVP(6,6),ZcplSecSeVZ(6,6),& 
& ZcplSecSvcVWm(6,3),ZcplSucSuVG(6,6),ZcplSucSuVP(6,6),ZcplSucSdVWm(6,6),ZcplSucSuVZ(6,6),& 
& ZcplSvcSeVWm(3,6),ZcplSvcSvVZ(3,3),ZcplhhcVWmVWm(3),ZcplhhVZVZ(3),ZcplHpmcVWmVP(2),    & 
& ZcplHpmcVWmVZ(2),ZcplcHpmVPVWm(2),ZcplcHpmVWmVZ(2),ZcplAhAhcVWmVWm(3,3),               & 
& ZcplAhAhVZVZ(3,3),ZcplAhHpmcVWmVP(3,2),ZcplAhHpmcVWmVZ(3,2),ZcplAhcHpmVPVWm(3,2),      & 
& ZcplAhcHpmVWmVZ(3,2),ZcplhhhhcVWmVWm(3,3),ZcplhhhhVZVZ(3,3),ZcplhhHpmcVWmVP(3,2),      & 
& ZcplhhHpmcVWmVZ(3,2),ZcplhhcHpmVPVWm(3,2),ZcplhhcHpmVWmVZ(3,2),ZcplHpmcHpmVPVP(2,2),   & 
& ZcplHpmcHpmVPVZ(2,2),ZcplHpmcHpmcVWmVWm(2,2),ZcplHpmcHpmVZVZ(2,2),ZcplSdcSdVGVG(6,6),  & 
& ZcplSdcSdVGVP(6,6),ZcplSdcSdVGVZ(6,6),ZcplSdcSucVWmVG(6,6),ZcplSdcSdVPVP(6,6),         & 
& ZcplSdcSdVPVZ(6,6),ZcplSdcSucVWmVP(6,6),ZcplSdcSdcVWmVWm(6,6),ZcplSdcSdVZVZ(6,6),      & 
& ZcplSdcSucVWmVZ(6,6),ZcplSecSeVPVP(6,6),ZcplSecSeVPVZ(6,6),ZcplSecSvcVWmVP(6,3),       & 
& ZcplSecSecVWmVWm(6,6),ZcplSecSeVZVZ(6,6),ZcplSecSvcVWmVZ(6,3),ZcplSucSuVGVG(6,6),      & 
& ZcplSucSuVGVP(6,6),ZcplSucSdVGVWm(6,6),ZcplSucSuVGVZ(6,6),ZcplSucSuVPVP(6,6),          & 
& ZcplSucSdVPVWm(6,6),ZcplSucSuVPVZ(6,6),ZcplSucSdVWmVZ(6,6),ZcplSucSucVWmVWm(6,6),      & 
& ZcplSucSuVZVZ(6,6),ZcplSvcSeVPVWm(3,6),ZcplSvcSeVWmVZ(3,6),ZcplSvcSvcVWmVWm(3,3),      & 
& ZcplSvcSvVZVZ(3,3),ZcplVGVGVG,ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplcChaChaAhL(2,2,3),       & 
& ZcplcChaChaAhR(2,2,3),ZcplChiChiAhL(5,5,3),ZcplChiChiAhR(5,5,3),ZcplcFdFdAhL(3,3,3),   & 
& ZcplcFdFdAhR(3,3,3),ZcplcFeFeAhL(3,3,3),ZcplcFeFeAhR(3,3,3),ZcplcFuFuAhL(3,3,3)

Complex(dp), Intent(out) :: ZcplcFuFuAhR(3,3,3),ZcplChiChacHpmL(5,2,2),ZcplChiChacHpmR(5,2,2),ZcplChaFucSdL(2,3,6),& 
& ZcplChaFucSdR(2,3,6),ZcplChaFvcSeL(2,3,6),ZcplChaFvcSeR(2,3,6),ZcplcChaChahhL(2,2,3),  & 
& ZcplcChaChahhR(2,2,3),ZcplcFdChaSuL(3,2,6),ZcplcFdChaSuR(3,2,6),ZcplcFeChaSvL(3,2,3),  & 
& ZcplcFeChaSvR(3,2,3),ZcplChiChihhL(5,5,3),ZcplChiChihhR(5,5,3),ZcplChiFdcSdL(5,3,6),   & 
& ZcplChiFdcSdR(5,3,6),ZcplChiFecSeL(5,3,6),ZcplChiFecSeR(5,3,6),ZcplChiFucSuL(5,3,6),   & 
& ZcplChiFucSuR(5,3,6),ZcplChiFvcSvL(5,3,3),ZcplChiFvcSvR(5,3,3),ZcplcChaChiHpmL(2,5,2), & 
& ZcplcChaChiHpmR(2,5,2),ZcplcFdChiSdL(3,5,6),ZcplcFdChiSdR(3,5,6),ZcplcFeChiSeL(3,5,6), & 
& ZcplcFeChiSeR(3,5,6),ZcplcFuChiSuL(3,5,6),ZcplcFuChiSuR(3,5,6),ZcplcFvChiSvL(3,5,3),   & 
& ZcplcFvChiSvR(3,5,3),ZcplGluFdcSdL(3,6),ZcplGluFdcSdR(3,6),ZcplcFdFdhhL(3,3,3),        & 
& ZcplcFdFdhhR(3,3,3),ZcplcChaFdcSuL(2,3,6),ZcplcChaFdcSuR(2,3,6),ZcplcFuFdcHpmL(3,3,2), & 
& ZcplcFuFdcHpmR(3,3,2),ZcplcFeFehhL(3,3,3),ZcplcFeFehhR(3,3,3),ZcplcChaFecSvL(2,3,3),   & 
& ZcplcChaFecSvR(2,3,3),ZcplcFvFecHpmL(3,3,2),ZcplcFvFecHpmR(3,3,2),ZcplGluFucSuL(3,6),  & 
& ZcplGluFucSuR(3,6),ZcplcFuFuhhL(3,3,3),ZcplcFuFuhhR(3,3,3),ZcplcFdFuHpmL(3,3,2),       & 
& ZcplcFdFuHpmR(3,3,2),ZcplcFeFvHpmL(3,3,2),ZcplcFeFvHpmR(3,3,2),ZcplcFdGluSdL(3,6),     & 
& ZcplcFdGluSdR(3,6),ZcplcFuGluSuL(3,6),ZcplcFuGluSuR(3,6),ZcplcChacFuSdL(2,3,6),        & 
& ZcplcChacFuSdR(2,3,6),ZcplcChacFvSeL(2,3,6),ZcplcChacFvSeR(2,3,6),ZcplChiChacVWmL(5,2),& 
& ZcplChiChacVWmR(5,2),ZcplcChaChaVPL(2,2),ZcplcChaChaVPR(2,2),ZcplcChaChaVZL(2,2),      & 
& ZcplcChaChaVZR(2,2),ZcplChiChiVZL(5,5),ZcplChiChiVZR(5,5),ZcplcChaChiVWmL(2,5),        & 
& ZcplcChaChiVWmR(2,5),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),ZcplcFdFdVPL(3,3),            & 
& ZcplcFdFdVPR(3,3),ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),ZcplcFuFdcVWmL(3,3),             & 
& ZcplcFuFdcVWmR(3,3),ZcplcFeFeVPL(3,3),ZcplcFeFeVPR(3,3),ZcplcFeFeVZL(3,3),             & 
& ZcplcFeFeVZR(3,3),ZcplcFvFecVWmL(3,3),ZcplcFvFecVWmR(3,3),ZcplcFuFuVGL(3,3),           & 
& ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),ZcplcFdFuVWmL(3,3),              & 
& ZcplcFdFuVWmR(3,3),ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcFeFvVWmL(3,3),             & 
& ZcplcFeFvVWmR(3,3),ZcplcFvFvVZL(3,3),ZcplcFvFvVZR(3,3),ZcplGluGluVGL,ZcplGluGluVGR,    & 
& ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,ZcplcVWmVPVPVWm1,ZcplcVWmVPVPVWm2,           & 
& ZcplcVWmVPVPVWm3,ZcplcVWmVPVWmVZ1,ZcplcVWmVPVWmVZ2,ZcplcVWmVPVWmVZ3,ZcplcVWmcVWmVWmVWm1,& 
& ZcplcVWmcVWmVWmVWm2,ZcplcVWmcVWmVWmVWm3,ZcplcVWmVWmVZVZ1,ZcplcVWmVWmVZVZ2,             & 
& ZcplcVWmVWmVZVZ3,ZcplcgGgGVG,ZcplcgWmgAVWm,ZcplcgWpCgAcVWm,ZcplcgWmgWmVP,              & 
& ZcplcgWmgWmVZ,ZcplcgAgWmcVWm,ZcplcgZgWmcVWm,ZcplcgWpCgWpCVP,ZcplcgAgWpCVWm,            & 
& ZcplcgZgWpCVWm,ZcplcgWpCgWpCVZ,ZcplcgWmgZVWm,ZcplcgWpCgZcVWm,ZcplcgWmgWmAh(3),         & 
& ZcplcgWpCgWpCAh(3),ZcplcgZgAhh(3),ZcplcgWmgAHpm(2),ZcplcgWpCgAcHpm(2),ZcplcgWmgWmhh(3),& 
& ZcplcgZgWmcHpm(2),ZcplcgWpCgWpChh(3),ZcplcgZgWpCHpm(2),ZcplcgZgZhh(3),ZcplcgWmgZHpm(2),& 
& ZcplcgWpCgZcHpm(2)

Complex(dp) :: ZRUZDc(6, 6) 
Complex(dp) :: ZRUZVc(3, 3) 
Complex(dp) :: ZRUZUc(6, 6) 
Complex(dp) :: ZRUZEc(6, 6) 
Complex(dp) :: ZRUZHc(3, 3) 
Complex(dp) :: ZRUZAc(3, 3) 
Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUZNc(5, 5) 
Complex(dp) :: ZRUUMc(2, 2) 
Complex(dp) :: ZRUUPc(2, 2) 
Complex(dp) :: ZRUZELc(3, 3) 
Complex(dp) :: ZRUZERc(3, 3) 
Complex(dp) :: ZRUZDLc(3, 3) 
Complex(dp) :: ZRUZDRc(3, 3) 
Complex(dp) :: ZRUZULc(3, 3) 
Complex(dp) :: ZRUZURc(3, 3) 
ZRUZDc = Conjg(ZRUZD)
ZRUZVc = Conjg(ZRUZV)
ZRUZUc = Conjg(ZRUZU)
ZRUZEc = Conjg(ZRUZE)
ZRUZHc = Conjg(ZRUZH)
ZRUZAc = Conjg(ZRUZA)
ZRUZPc = Conjg(ZRUZP)
ZRUZNc = Conjg(ZRUZN)
ZRUUMc = Conjg(ZRUUM)
ZRUUPc = Conjg(ZRUUP)
ZRUZELc = Conjg(ZRUZEL)
ZRUZERc = Conjg(ZRUZER)
ZRUZDLc = Conjg(ZRUZDL)
ZRUZDRc = Conjg(ZRUZDR)
ZRUZULc = Conjg(ZRUZUL)
ZRUZURc = Conjg(ZRUZUR)


 ! ## ZcplAhAhAh ## 
ZcplAhAhAh = 0._dp 
TempcplAhAhAh = cplAhAhAh 
Do gt1=1,3
  Do gt2=1,3
ZcplAhAhAh(gt2,:,:) = ZcplAhAhAh(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhAhAh(gt1,:,:) 
 End Do 
End Do 
TempcplAhAhAh = ZcplAhAhAh 
ZcplAhAhAh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhAhAh(:,gt2,:) = ZcplAhAhAh(:,gt2,:) + ZRUZA(gt2,gt1)*TempcplAhAhAh(:,gt1,:) 
 End Do 
End Do 
TempcplAhAhAh = ZcplAhAhAh 
ZcplAhAhAh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhAhAh(:,:,gt2) = ZcplAhAhAh(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplAhAhAh(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhAhhh ## 
ZcplAhAhhh = 0._dp 
TempcplAhAhhh = cplAhAhhh 
Do gt1=1,3
  Do gt2=1,3
ZcplAhAhhh(gt2,:,:) = ZcplAhAhhh(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhAhhh(gt1,:,:) 
 End Do 
End Do 
TempcplAhAhhh = ZcplAhAhhh 
ZcplAhAhhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhAhhh(:,gt2,:) = ZcplAhAhhh(:,gt2,:) + ZRUZA(gt2,gt1)*TempcplAhAhhh(:,gt1,:) 
 End Do 
End Do 
TempcplAhAhhh = ZcplAhAhhh 
ZcplAhAhhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhAhhh(:,:,gt2) = ZcplAhAhhh(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplAhAhhh(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhhhhh ## 
ZcplAhhhhh = 0._dp 
TempcplAhhhhh = cplAhhhhh 
Do gt1=1,3
  Do gt2=1,3
ZcplAhhhhh(gt2,:,:) = ZcplAhhhhh(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhhhhh(gt1,:,:) 
 End Do 
End Do 
TempcplAhhhhh = ZcplAhhhhh 
ZcplAhhhhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhhhhh(:,gt2,:) = ZcplAhhhhh(:,gt2,:) + ZRUZH(gt2,gt1)*TempcplAhhhhh(:,gt1,:) 
 End Do 
End Do 
TempcplAhhhhh = ZcplAhhhhh 
ZcplAhhhhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhhhhh(:,:,gt2) = ZcplAhhhhh(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplAhhhhh(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhHpmcHpm ## 
ZcplAhHpmcHpm = 0._dp 
TempcplAhHpmcHpm = cplAhHpmcHpm 
Do gt1=1,3
  Do gt2=1,3
ZcplAhHpmcHpm(gt2,:,:) = ZcplAhHpmcHpm(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhHpmcHpm(gt1,:,:) 
 End Do 
End Do 
TempcplAhHpmcHpm = ZcplAhHpmcHpm 
ZcplAhHpmcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplAhHpmcHpm(:,gt2,:) = ZcplAhHpmcHpm(:,gt2,:) + ZRUZP(gt2,gt1)*TempcplAhHpmcHpm(:,gt1,:) 
 End Do 
End Do 
TempcplAhHpmcHpm = ZcplAhHpmcHpm 
ZcplAhHpmcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplAhHpmcHpm(:,:,gt2) = ZcplAhHpmcHpm(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplAhHpmcHpm(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhSdcSd ## 
ZcplAhSdcSd = 0._dp 
TempcplAhSdcSd = cplAhSdcSd 
Do gt1=1,3
  Do gt2=1,3
ZcplAhSdcSd(gt2,:,:) = ZcplAhSdcSd(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhSdcSd(gt1,:,:) 
 End Do 
End Do 
TempcplAhSdcSd = ZcplAhSdcSd 
ZcplAhSdcSd = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplAhSdcSd(:,gt2,:) = ZcplAhSdcSd(:,gt2,:) + ZRUZD(gt2,gt1)*TempcplAhSdcSd(:,gt1,:) 
 End Do 
End Do 
TempcplAhSdcSd = ZcplAhSdcSd 
ZcplAhSdcSd = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplAhSdcSd(:,:,gt2) = ZcplAhSdcSd(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplAhSdcSd(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhSecSe ## 
ZcplAhSecSe = 0._dp 
TempcplAhSecSe = cplAhSecSe 
Do gt1=1,3
  Do gt2=1,3
ZcplAhSecSe(gt2,:,:) = ZcplAhSecSe(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhSecSe(gt1,:,:) 
 End Do 
End Do 
TempcplAhSecSe = ZcplAhSecSe 
ZcplAhSecSe = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplAhSecSe(:,gt2,:) = ZcplAhSecSe(:,gt2,:) + ZRUZE(gt2,gt1)*TempcplAhSecSe(:,gt1,:) 
 End Do 
End Do 
TempcplAhSecSe = ZcplAhSecSe 
ZcplAhSecSe = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplAhSecSe(:,:,gt2) = ZcplAhSecSe(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplAhSecSe(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhSucSu ## 
ZcplAhSucSu = 0._dp 
TempcplAhSucSu = cplAhSucSu 
Do gt1=1,3
  Do gt2=1,3
ZcplAhSucSu(gt2,:,:) = ZcplAhSucSu(gt2,:,:) + ZRUZA(gt2,gt1)*TempcplAhSucSu(gt1,:,:) 
 End Do 
End Do 
TempcplAhSucSu = ZcplAhSucSu 
ZcplAhSucSu = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplAhSucSu(:,gt2,:) = ZcplAhSucSu(:,gt2,:) + ZRUZU(gt2,gt1)*TempcplAhSucSu(:,gt1,:) 
 End Do 
End Do 
TempcplAhSucSu = ZcplAhSucSu 
ZcplAhSucSu = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplAhSucSu(:,:,gt2) = ZcplAhSucSu(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplAhSucSu(:,:,gt1) 
 End Do 
End Do 


 ! ## Zcplhhhhhh ## 
Zcplhhhhhh = 0._dp 
Tempcplhhhhhh = cplhhhhhh 
Do gt1=1,3
  Do gt2=1,3
Zcplhhhhhh(gt2,:,:) = Zcplhhhhhh(gt2,:,:) + ZRUZH(gt2,gt1)*Tempcplhhhhhh(gt1,:,:) 
 End Do 
End Do 
Tempcplhhhhhh = Zcplhhhhhh 
Zcplhhhhhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
Zcplhhhhhh(:,gt2,:) = Zcplhhhhhh(:,gt2,:) + ZRUZH(gt2,gt1)*Tempcplhhhhhh(:,gt1,:) 
 End Do 
End Do 
Tempcplhhhhhh = Zcplhhhhhh 
Zcplhhhhhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
Zcplhhhhhh(:,:,gt2) = Zcplhhhhhh(:,:,gt2) + ZRUZH(gt2,gt1)*Tempcplhhhhhh(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplhhHpmcHpm ## 
ZcplhhHpmcHpm = 0._dp 
TempcplhhHpmcHpm = cplhhHpmcHpm 
Do gt1=1,3
  Do gt2=1,3
ZcplhhHpmcHpm(gt2,:,:) = ZcplhhHpmcHpm(gt2,:,:) + ZRUZH(gt2,gt1)*TempcplhhHpmcHpm(gt1,:,:) 
 End Do 
End Do 
TempcplhhHpmcHpm = ZcplhhHpmcHpm 
ZcplhhHpmcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhHpmcHpm(:,gt2,:) = ZcplhhHpmcHpm(:,gt2,:) + ZRUZP(gt2,gt1)*TempcplhhHpmcHpm(:,gt1,:) 
 End Do 
End Do 
TempcplhhHpmcHpm = ZcplhhHpmcHpm 
ZcplhhHpmcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhHpmcHpm(:,:,gt2) = ZcplhhHpmcHpm(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplhhHpmcHpm(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplhhSdcSd ## 
ZcplhhSdcSd = 0._dp 
TempcplhhSdcSd = cplhhSdcSd 
Do gt1=1,3
  Do gt2=1,3
ZcplhhSdcSd(gt2,:,:) = ZcplhhSdcSd(gt2,:,:) + ZRUZH(gt2,gt1)*TempcplhhSdcSd(gt1,:,:) 
 End Do 
End Do 
TempcplhhSdcSd = ZcplhhSdcSd 
ZcplhhSdcSd = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplhhSdcSd(:,gt2,:) = ZcplhhSdcSd(:,gt2,:) + ZRUZD(gt2,gt1)*TempcplhhSdcSd(:,gt1,:) 
 End Do 
End Do 
TempcplhhSdcSd = ZcplhhSdcSd 
ZcplhhSdcSd = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplhhSdcSd(:,:,gt2) = ZcplhhSdcSd(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplhhSdcSd(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplhhSecSe ## 
ZcplhhSecSe = 0._dp 
TempcplhhSecSe = cplhhSecSe 
Do gt1=1,3
  Do gt2=1,3
ZcplhhSecSe(gt2,:,:) = ZcplhhSecSe(gt2,:,:) + ZRUZH(gt2,gt1)*TempcplhhSecSe(gt1,:,:) 
 End Do 
End Do 
TempcplhhSecSe = ZcplhhSecSe 
ZcplhhSecSe = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplhhSecSe(:,gt2,:) = ZcplhhSecSe(:,gt2,:) + ZRUZE(gt2,gt1)*TempcplhhSecSe(:,gt1,:) 
 End Do 
End Do 
TempcplhhSecSe = ZcplhhSecSe 
ZcplhhSecSe = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplhhSecSe(:,:,gt2) = ZcplhhSecSe(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplhhSecSe(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplhhSucSu ## 
ZcplhhSucSu = 0._dp 
TempcplhhSucSu = cplhhSucSu 
Do gt1=1,3
  Do gt2=1,3
ZcplhhSucSu(gt2,:,:) = ZcplhhSucSu(gt2,:,:) + ZRUZH(gt2,gt1)*TempcplhhSucSu(gt1,:,:) 
 End Do 
End Do 
TempcplhhSucSu = ZcplhhSucSu 
ZcplhhSucSu = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplhhSucSu(:,gt2,:) = ZcplhhSucSu(:,gt2,:) + ZRUZU(gt2,gt1)*TempcplhhSucSu(:,gt1,:) 
 End Do 
End Do 
TempcplhhSucSu = ZcplhhSucSu 
ZcplhhSucSu = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplhhSucSu(:,:,gt2) = ZcplhhSucSu(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplhhSucSu(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplhhSvcSv ## 
ZcplhhSvcSv = 0._dp 
TempcplhhSvcSv = cplhhSvcSv 
Do gt1=1,3
  Do gt2=1,3
ZcplhhSvcSv(gt2,:,:) = ZcplhhSvcSv(gt2,:,:) + ZRUZH(gt2,gt1)*TempcplhhSvcSv(gt1,:,:) 
 End Do 
End Do 
TempcplhhSvcSv = ZcplhhSvcSv 
ZcplhhSvcSv = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplhhSvcSv(:,gt2,:) = ZcplhhSvcSv(:,gt2,:) + ZRUZV(gt2,gt1)*TempcplhhSvcSv(:,gt1,:) 
 End Do 
End Do 
TempcplhhSvcSv = ZcplhhSvcSv 
ZcplhhSvcSv = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplhhSvcSv(:,:,gt2) = ZcplhhSvcSv(:,:,gt2) + ZRUZVc(gt2,gt1)*TempcplhhSvcSv(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplHpmSucSd ## 
ZcplHpmSucSd = 0._dp 
TempcplHpmSucSd = cplHpmSucSd 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmSucSd(gt2,:,:) = ZcplHpmSucSd(gt2,:,:) + ZRUZP(gt2,gt1)*TempcplHpmSucSd(gt1,:,:) 
 End Do 
End Do 
TempcplHpmSucSd = ZcplHpmSucSd 
ZcplHpmSucSd = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplHpmSucSd(:,gt2,:) = ZcplHpmSucSd(:,gt2,:) + ZRUZU(gt2,gt1)*TempcplHpmSucSd(:,gt1,:) 
 End Do 
End Do 
TempcplHpmSucSd = ZcplHpmSucSd 
ZcplHpmSucSd = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplHpmSucSd(:,:,gt2) = ZcplHpmSucSd(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplHpmSucSd(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplHpmSvcSe ## 
ZcplHpmSvcSe = 0._dp 
TempcplHpmSvcSe = cplHpmSvcSe 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmSvcSe(gt2,:,:) = ZcplHpmSvcSe(gt2,:,:) + ZRUZP(gt2,gt1)*TempcplHpmSvcSe(gt1,:,:) 
 End Do 
End Do 
TempcplHpmSvcSe = ZcplHpmSvcSe 
ZcplHpmSvcSe = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplHpmSvcSe(:,gt2,:) = ZcplHpmSvcSe(:,gt2,:) + ZRUZV(gt2,gt1)*TempcplHpmSvcSe(:,gt1,:) 
 End Do 
End Do 
TempcplHpmSvcSe = ZcplHpmSvcSe 
ZcplHpmSvcSe = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplHpmSvcSe(:,:,gt2) = ZcplHpmSvcSe(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplHpmSvcSe(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplSdcHpmcSu ## 
ZcplSdcHpmcSu = 0._dp 
TempcplSdcHpmcSu = cplSdcHpmcSu 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcHpmcSu(gt2,:,:) = ZcplSdcHpmcSu(gt2,:,:) + ZRUZD(gt2,gt1)*TempcplSdcHpmcSu(gt1,:,:) 
 End Do 
End Do 
TempcplSdcHpmcSu = ZcplSdcHpmcSu 
ZcplSdcHpmcSu = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplSdcHpmcSu(:,gt2,:) = ZcplSdcHpmcSu(:,gt2,:) + ZRUZP(gt2,gt1)*TempcplSdcHpmcSu(:,gt1,:) 
 End Do 
End Do 
TempcplSdcHpmcSu = ZcplSdcHpmcSu 
ZcplSdcHpmcSu = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcHpmcSu(:,:,gt2) = ZcplSdcHpmcSu(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplSdcHpmcSu(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplSecHpmcSv ## 
ZcplSecHpmcSv = 0._dp 
TempcplSecHpmcSv = cplSecHpmcSv 
Do gt1=1,6
  Do gt2=1,6
ZcplSecHpmcSv(gt2,:,:) = ZcplSecHpmcSv(gt2,:,:) + ZRUZE(gt2,gt1)*TempcplSecHpmcSv(gt1,:,:) 
 End Do 
End Do 
TempcplSecHpmcSv = ZcplSecHpmcSv 
ZcplSecHpmcSv = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplSecHpmcSv(:,gt2,:) = ZcplSecHpmcSv(:,gt2,:) + ZRUZP(gt2,gt1)*TempcplSecHpmcSv(:,gt1,:) 
 End Do 
End Do 
TempcplSecHpmcSv = ZcplSecHpmcSv 
ZcplSecHpmcSv = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplSecHpmcSv(:,:,gt2) = ZcplSecHpmcSv(:,:,gt2) + ZRUZVc(gt2,gt1)*TempcplSecHpmcSv(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplAhAhAhAh ## 
ZcplAhAhAhAh = 0._dp 


 ! ## ZcplAhAhAhhh ## 
ZcplAhAhAhhh = 0._dp 


 ! ## ZcplAhAhhhhh ## 
ZcplAhAhhhhh = 0._dp 


 ! ## ZcplAhAhHpmcHpm ## 
ZcplAhAhHpmcHpm = 0._dp 


 ! ## ZcplAhAhSdcSd ## 
ZcplAhAhSdcSd = 0._dp 


 ! ## ZcplAhAhSecSe ## 
ZcplAhAhSecSe = 0._dp 


 ! ## ZcplAhAhSucSu ## 
ZcplAhAhSucSu = 0._dp 


 ! ## ZcplAhAhSvcSv ## 
ZcplAhAhSvcSv = 0._dp 


 ! ## ZcplAhhhhhhh ## 
ZcplAhhhhhhh = 0._dp 


 ! ## ZcplAhhhHpmcHpm ## 
ZcplAhhhHpmcHpm = 0._dp 


 ! ## ZcplAhhhSdcSd ## 
ZcplAhhhSdcSd = 0._dp 


 ! ## ZcplAhhhSecSe ## 
ZcplAhhhSecSe = 0._dp 


 ! ## ZcplAhhhSucSu ## 
ZcplAhhhSucSu = 0._dp 


 ! ## ZcplAhHpmSucSd ## 
ZcplAhHpmSucSd = 0._dp 


 ! ## ZcplAhHpmSvcSe ## 
ZcplAhHpmSvcSe = 0._dp 


 ! ## ZcplAhSdcHpmcSu ## 
ZcplAhSdcHpmcSu = 0._dp 


 ! ## ZcplAhSecHpmcSv ## 
ZcplAhSecHpmcSv = 0._dp 


 ! ## Zcplhhhhhhhh ## 
Zcplhhhhhhhh = 0._dp 


 ! ## ZcplhhhhHpmcHpm ## 
ZcplhhhhHpmcHpm = 0._dp 


 ! ## ZcplhhhhSdcSd ## 
ZcplhhhhSdcSd = 0._dp 


 ! ## ZcplhhhhSecSe ## 
ZcplhhhhSecSe = 0._dp 


 ! ## ZcplhhhhSucSu ## 
ZcplhhhhSucSu = 0._dp 


 ! ## ZcplhhhhSvcSv ## 
ZcplhhhhSvcSv = 0._dp 


 ! ## ZcplhhHpmSucSd ## 
ZcplhhHpmSucSd = 0._dp 


 ! ## ZcplhhHpmSvcSe ## 
ZcplhhHpmSvcSe = 0._dp 


 ! ## ZcplhhSdcHpmcSu ## 
ZcplhhSdcHpmcSu = 0._dp 


 ! ## ZcplhhSecHpmcSv ## 
ZcplhhSecHpmcSv = 0._dp 


 ! ## ZcplHpmHpmcHpmcHpm ## 
ZcplHpmHpmcHpmcHpm = 0._dp 


 ! ## ZcplHpmSdcHpmcSd ## 
ZcplHpmSdcHpmcSd = 0._dp 


 ! ## ZcplHpmSecHpmcSe ## 
ZcplHpmSecHpmcSe = 0._dp 


 ! ## ZcplHpmSucHpmcSu ## 
ZcplHpmSucHpmcSu = 0._dp 


 ! ## ZcplHpmSvcHpmcSv ## 
ZcplHpmSvcHpmcSv = 0._dp 


 ! ## ZcplSdSdcSdcSd ## 
ZcplSdSdcSdcSd = 0._dp 


 ! ## ZcplSdSecSdcSe ## 
ZcplSdSecSdcSe = 0._dp 


 ! ## ZcplSdSucSdcSu ## 
ZcplSdSucSdcSu = 0._dp 


 ! ## ZcplSdSvcSdcSv ## 
ZcplSdSvcSdcSv = 0._dp 


 ! ## ZcplSdSvcSecSu ## 
ZcplSdSvcSecSu = 0._dp 


 ! ## ZcplSeSecSecSe ## 
ZcplSeSecSecSe = 0._dp 


 ! ## ZcplSeSucSdcSv ## 
ZcplSeSucSdcSv = 0._dp 


 ! ## ZcplSeSucSecSu ## 
ZcplSeSucSecSu = 0._dp 


 ! ## ZcplSeSvcSecSv ## 
ZcplSeSvcSecSv = 0._dp 


 ! ## ZcplSuSucSucSu ## 
ZcplSuSucSucSu = 0._dp 


 ! ## ZcplSuSvcSucSv ## 
ZcplSuSvcSucSv = 0._dp 


 ! ## ZcplSvSvcSvcSv ## 
ZcplSvSvcSvcSv = 0._dp 


 ! ## ZcplAhhhVZ ## 
ZcplAhhhVZ = 0._dp 
TempcplAhhhVZ = cplAhhhVZ 
Do gt1=1,3
  Do gt2=1,3
ZcplAhhhVZ(gt2,:) = ZcplAhhhVZ(gt2,:) + ZRUZA(gt2,gt1)*TempcplAhhhVZ(gt1,:) 
 End Do 
End Do 
TempcplAhhhVZ = ZcplAhhhVZ 
ZcplAhhhVZ = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplAhhhVZ(:,gt2) = ZcplAhhhVZ(:,gt2) + ZRUZH(gt2,gt1)*TempcplAhhhVZ(:,gt1) 
 End Do 
End Do 
TempcplAhhhVZ = ZcplAhhhVZ 


 ! ## ZcplAhHpmcVWm ## 
ZcplAhHpmcVWm = 0._dp 
TempcplAhHpmcVWm = cplAhHpmcVWm 
Do gt1=1,3
  Do gt2=1,3
ZcplAhHpmcVWm(gt2,:) = ZcplAhHpmcVWm(gt2,:) + ZRUZA(gt2,gt1)*TempcplAhHpmcVWm(gt1,:) 
 End Do 
End Do 
TempcplAhHpmcVWm = ZcplAhHpmcVWm 
ZcplAhHpmcVWm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplAhHpmcVWm(:,gt2) = ZcplAhHpmcVWm(:,gt2) + ZRUZP(gt2,gt1)*TempcplAhHpmcVWm(:,gt1) 
 End Do 
End Do 
TempcplAhHpmcVWm = ZcplAhHpmcVWm 


 ! ## ZcplAhcHpmVWm ## 
ZcplAhcHpmVWm = 0._dp 
TempcplAhcHpmVWm = cplAhcHpmVWm 
Do gt1=1,3
  Do gt2=1,3
ZcplAhcHpmVWm(gt2,:) = ZcplAhcHpmVWm(gt2,:) + ZRUZA(gt2,gt1)*TempcplAhcHpmVWm(gt1,:) 
 End Do 
End Do 
TempcplAhcHpmVWm = ZcplAhcHpmVWm 
ZcplAhcHpmVWm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplAhcHpmVWm(:,gt2) = ZcplAhcHpmVWm(:,gt2) + ZRUZP(gt2,gt1)*TempcplAhcHpmVWm(:,gt1) 
 End Do 
End Do 
TempcplAhcHpmVWm = ZcplAhcHpmVWm 


 ! ## ZcplhhHpmcVWm ## 
ZcplhhHpmcVWm = 0._dp 
TempcplhhHpmcVWm = cplhhHpmcVWm 
Do gt1=1,3
  Do gt2=1,3
ZcplhhHpmcVWm(gt2,:) = ZcplhhHpmcVWm(gt2,:) + ZRUZH(gt2,gt1)*TempcplhhHpmcVWm(gt1,:) 
 End Do 
End Do 
TempcplhhHpmcVWm = ZcplhhHpmcVWm 
ZcplhhHpmcVWm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhHpmcVWm(:,gt2) = ZcplhhHpmcVWm(:,gt2) + ZRUZP(gt2,gt1)*TempcplhhHpmcVWm(:,gt1) 
 End Do 
End Do 
TempcplhhHpmcVWm = ZcplhhHpmcVWm 


 ! ## ZcplhhcHpmVWm ## 
ZcplhhcHpmVWm = 0._dp 
TempcplhhcHpmVWm = cplhhcHpmVWm 
Do gt1=1,3
  Do gt2=1,3
ZcplhhcHpmVWm(gt2,:) = ZcplhhcHpmVWm(gt2,:) + ZRUZH(gt2,gt1)*TempcplhhcHpmVWm(gt1,:) 
 End Do 
End Do 
TempcplhhcHpmVWm = ZcplhhcHpmVWm 
ZcplhhcHpmVWm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhcHpmVWm(:,gt2) = ZcplhhcHpmVWm(:,gt2) + ZRUZP(gt2,gt1)*TempcplhhcHpmVWm(:,gt1) 
 End Do 
End Do 
TempcplhhcHpmVWm = ZcplhhcHpmVWm 


 ! ## ZcplHpmcHpmVP ## 
ZcplHpmcHpmVP = 0._dp 
TempcplHpmcHpmVP = cplHpmcHpmVP 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmcHpmVP(gt2,:) = ZcplHpmcHpmVP(gt2,:) + ZRUZP(gt2,gt1)*TempcplHpmcHpmVP(gt1,:) 
 End Do 
End Do 
TempcplHpmcHpmVP = ZcplHpmcHpmVP 
ZcplHpmcHpmVP = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmcHpmVP(:,gt2) = ZcplHpmcHpmVP(:,gt2) + ZRUZP(gt2,gt1)*TempcplHpmcHpmVP(:,gt1) 
 End Do 
End Do 
TempcplHpmcHpmVP = ZcplHpmcHpmVP 


 ! ## ZcplHpmcHpmVZ ## 
ZcplHpmcHpmVZ = 0._dp 
TempcplHpmcHpmVZ = cplHpmcHpmVZ 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmcHpmVZ(gt2,:) = ZcplHpmcHpmVZ(gt2,:) + ZRUZP(gt2,gt1)*TempcplHpmcHpmVZ(gt1,:) 
 End Do 
End Do 
TempcplHpmcHpmVZ = ZcplHpmcHpmVZ 
ZcplHpmcHpmVZ = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmcHpmVZ(:,gt2) = ZcplHpmcHpmVZ(:,gt2) + ZRUZP(gt2,gt1)*TempcplHpmcHpmVZ(:,gt1) 
 End Do 
End Do 
TempcplHpmcHpmVZ = ZcplHpmcHpmVZ 


 ! ## ZcplSdcSdVG ## 
ZcplSdcSdVG = 0._dp 
TempcplSdcSdVG = cplSdcSdVG 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSdVG(gt2,:) = ZcplSdcSdVG(gt2,:) + ZRUZD(gt2,gt1)*TempcplSdcSdVG(gt1,:) 
 End Do 
End Do 
TempcplSdcSdVG = ZcplSdcSdVG 
ZcplSdcSdVG = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSdVG(:,gt2) = ZcplSdcSdVG(:,gt2) + ZRUZDc(gt2,gt1)*TempcplSdcSdVG(:,gt1) 
 End Do 
End Do 
TempcplSdcSdVG = ZcplSdcSdVG 


 ! ## ZcplSdcSdVP ## 
ZcplSdcSdVP = 0._dp 
TempcplSdcSdVP = cplSdcSdVP 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSdVP(gt2,:) = ZcplSdcSdVP(gt2,:) + ZRUZD(gt2,gt1)*TempcplSdcSdVP(gt1,:) 
 End Do 
End Do 
TempcplSdcSdVP = ZcplSdcSdVP 
ZcplSdcSdVP = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSdVP(:,gt2) = ZcplSdcSdVP(:,gt2) + ZRUZDc(gt2,gt1)*TempcplSdcSdVP(:,gt1) 
 End Do 
End Do 
TempcplSdcSdVP = ZcplSdcSdVP 


 ! ## ZcplSdcSdVZ ## 
ZcplSdcSdVZ = 0._dp 
TempcplSdcSdVZ = cplSdcSdVZ 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSdVZ(gt2,:) = ZcplSdcSdVZ(gt2,:) + ZRUZD(gt2,gt1)*TempcplSdcSdVZ(gt1,:) 
 End Do 
End Do 
TempcplSdcSdVZ = ZcplSdcSdVZ 
ZcplSdcSdVZ = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSdVZ(:,gt2) = ZcplSdcSdVZ(:,gt2) + ZRUZDc(gt2,gt1)*TempcplSdcSdVZ(:,gt1) 
 End Do 
End Do 
TempcplSdcSdVZ = ZcplSdcSdVZ 


 ! ## ZcplSdcSucVWm ## 
ZcplSdcSucVWm = 0._dp 
TempcplSdcSucVWm = cplSdcSucVWm 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSucVWm(gt2,:) = ZcplSdcSucVWm(gt2,:) + ZRUZD(gt2,gt1)*TempcplSdcSucVWm(gt1,:) 
 End Do 
End Do 
TempcplSdcSucVWm = ZcplSdcSucVWm 
ZcplSdcSucVWm = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSdcSucVWm(:,gt2) = ZcplSdcSucVWm(:,gt2) + ZRUZUc(gt2,gt1)*TempcplSdcSucVWm(:,gt1) 
 End Do 
End Do 
TempcplSdcSucVWm = ZcplSdcSucVWm 


 ! ## ZcplSecSeVP ## 
ZcplSecSeVP = 0._dp 
TempcplSecSeVP = cplSecSeVP 
Do gt1=1,6
  Do gt2=1,6
ZcplSecSeVP(gt2,:) = ZcplSecSeVP(gt2,:) + ZRUZE(gt2,gt1)*TempcplSecSeVP(gt1,:) 
 End Do 
End Do 
TempcplSecSeVP = ZcplSecSeVP 
ZcplSecSeVP = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSecSeVP(:,gt2) = ZcplSecSeVP(:,gt2) + ZRUZEc(gt2,gt1)*TempcplSecSeVP(:,gt1) 
 End Do 
End Do 
TempcplSecSeVP = ZcplSecSeVP 


 ! ## ZcplSecSeVZ ## 
ZcplSecSeVZ = 0._dp 
TempcplSecSeVZ = cplSecSeVZ 
Do gt1=1,6
  Do gt2=1,6
ZcplSecSeVZ(gt2,:) = ZcplSecSeVZ(gt2,:) + ZRUZE(gt2,gt1)*TempcplSecSeVZ(gt1,:) 
 End Do 
End Do 
TempcplSecSeVZ = ZcplSecSeVZ 
ZcplSecSeVZ = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSecSeVZ(:,gt2) = ZcplSecSeVZ(:,gt2) + ZRUZEc(gt2,gt1)*TempcplSecSeVZ(:,gt1) 
 End Do 
End Do 
TempcplSecSeVZ = ZcplSecSeVZ 


 ! ## ZcplSecSvcVWm ## 
ZcplSecSvcVWm = 0._dp 
TempcplSecSvcVWm = cplSecSvcVWm 
Do gt1=1,6
  Do gt2=1,6
ZcplSecSvcVWm(gt2,:) = ZcplSecSvcVWm(gt2,:) + ZRUZE(gt2,gt1)*TempcplSecSvcVWm(gt1,:) 
 End Do 
End Do 
TempcplSecSvcVWm = ZcplSecSvcVWm 
ZcplSecSvcVWm = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplSecSvcVWm(:,gt2) = ZcplSecSvcVWm(:,gt2) + ZRUZVc(gt2,gt1)*TempcplSecSvcVWm(:,gt1) 
 End Do 
End Do 
TempcplSecSvcVWm = ZcplSecSvcVWm 


 ! ## ZcplSucSuVG ## 
ZcplSucSuVG = 0._dp 
TempcplSucSuVG = cplSucSuVG 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSuVG(gt2,:) = ZcplSucSuVG(gt2,:) + ZRUZU(gt2,gt1)*TempcplSucSuVG(gt1,:) 
 End Do 
End Do 
TempcplSucSuVG = ZcplSucSuVG 
ZcplSucSuVG = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSuVG(:,gt2) = ZcplSucSuVG(:,gt2) + ZRUZUc(gt2,gt1)*TempcplSucSuVG(:,gt1) 
 End Do 
End Do 
TempcplSucSuVG = ZcplSucSuVG 


 ! ## ZcplSucSuVP ## 
ZcplSucSuVP = 0._dp 
TempcplSucSuVP = cplSucSuVP 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSuVP(gt2,:) = ZcplSucSuVP(gt2,:) + ZRUZU(gt2,gt1)*TempcplSucSuVP(gt1,:) 
 End Do 
End Do 
TempcplSucSuVP = ZcplSucSuVP 
ZcplSucSuVP = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSuVP(:,gt2) = ZcplSucSuVP(:,gt2) + ZRUZUc(gt2,gt1)*TempcplSucSuVP(:,gt1) 
 End Do 
End Do 
TempcplSucSuVP = ZcplSucSuVP 


 ! ## ZcplSucSdVWm ## 
ZcplSucSdVWm = 0._dp 
TempcplSucSdVWm = cplSucSdVWm 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSdVWm(gt2,:) = ZcplSucSdVWm(gt2,:) + ZRUZU(gt2,gt1)*TempcplSucSdVWm(gt1,:) 
 End Do 
End Do 
TempcplSucSdVWm = ZcplSucSdVWm 
ZcplSucSdVWm = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSdVWm(:,gt2) = ZcplSucSdVWm(:,gt2) + ZRUZDc(gt2,gt1)*TempcplSucSdVWm(:,gt1) 
 End Do 
End Do 
TempcplSucSdVWm = ZcplSucSdVWm 


 ! ## ZcplSucSuVZ ## 
ZcplSucSuVZ = 0._dp 
TempcplSucSuVZ = cplSucSuVZ 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSuVZ(gt2,:) = ZcplSucSuVZ(gt2,:) + ZRUZU(gt2,gt1)*TempcplSucSuVZ(gt1,:) 
 End Do 
End Do 
TempcplSucSuVZ = ZcplSucSuVZ 
ZcplSucSuVZ = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSucSuVZ(:,gt2) = ZcplSucSuVZ(:,gt2) + ZRUZUc(gt2,gt1)*TempcplSucSuVZ(:,gt1) 
 End Do 
End Do 
TempcplSucSuVZ = ZcplSucSuVZ 


 ! ## ZcplSvcSeVWm ## 
ZcplSvcSeVWm = 0._dp 
TempcplSvcSeVWm = cplSvcSeVWm 
Do gt1=1,3
  Do gt2=1,3
ZcplSvcSeVWm(gt2,:) = ZcplSvcSeVWm(gt2,:) + ZRUZV(gt2,gt1)*TempcplSvcSeVWm(gt1,:) 
 End Do 
End Do 
TempcplSvcSeVWm = ZcplSvcSeVWm 
ZcplSvcSeVWm = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplSvcSeVWm(:,gt2) = ZcplSvcSeVWm(:,gt2) + ZRUZEc(gt2,gt1)*TempcplSvcSeVWm(:,gt1) 
 End Do 
End Do 
TempcplSvcSeVWm = ZcplSvcSeVWm 


 ! ## ZcplSvcSvVZ ## 
ZcplSvcSvVZ = 0._dp 
TempcplSvcSvVZ = cplSvcSvVZ 
Do gt1=1,3
  Do gt2=1,3
ZcplSvcSvVZ(gt2,:) = ZcplSvcSvVZ(gt2,:) + ZRUZV(gt2,gt1)*TempcplSvcSvVZ(gt1,:) 
 End Do 
End Do 
TempcplSvcSvVZ = ZcplSvcSvVZ 
ZcplSvcSvVZ = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplSvcSvVZ(:,gt2) = ZcplSvcSvVZ(:,gt2) + ZRUZVc(gt2,gt1)*TempcplSvcSvVZ(:,gt1) 
 End Do 
End Do 
TempcplSvcSvVZ = ZcplSvcSvVZ 


 ! ## ZcplhhcVWmVWm ## 
ZcplhhcVWmVWm = 0._dp 
TempcplhhcVWmVWm = cplhhcVWmVWm 
Do gt1=1,3
  Do gt2=1,3
ZcplhhcVWmVWm(gt2) = ZcplhhcVWmVWm(gt2) + ZRUZH(gt2,gt1)*TempcplhhcVWmVWm(gt1) 
 End Do 
End Do 
TempcplhhcVWmVWm = ZcplhhcVWmVWm 


 ! ## ZcplhhVZVZ ## 
ZcplhhVZVZ = 0._dp 
TempcplhhVZVZ = cplhhVZVZ 
Do gt1=1,3
  Do gt2=1,3
ZcplhhVZVZ(gt2) = ZcplhhVZVZ(gt2) + ZRUZH(gt2,gt1)*TempcplhhVZVZ(gt1) 
 End Do 
End Do 
TempcplhhVZVZ = ZcplhhVZVZ 


 ! ## ZcplHpmcVWmVP ## 
ZcplHpmcVWmVP = 0._dp 
TempcplHpmcVWmVP = cplHpmcVWmVP 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmcVWmVP(gt2) = ZcplHpmcVWmVP(gt2) + ZRUZP(gt2,gt1)*TempcplHpmcVWmVP(gt1) 
 End Do 
End Do 
TempcplHpmcVWmVP = ZcplHpmcVWmVP 


 ! ## ZcplHpmcVWmVZ ## 
ZcplHpmcVWmVZ = 0._dp 
TempcplHpmcVWmVZ = cplHpmcVWmVZ 
Do gt1=1,2
  Do gt2=1,2
ZcplHpmcVWmVZ(gt2) = ZcplHpmcVWmVZ(gt2) + ZRUZP(gt2,gt1)*TempcplHpmcVWmVZ(gt1) 
 End Do 
End Do 
TempcplHpmcVWmVZ = ZcplHpmcVWmVZ 


 ! ## ZcplcHpmVPVWm ## 
ZcplcHpmVPVWm = 0._dp 
TempcplcHpmVPVWm = cplcHpmVPVWm 
Do gt1=1,2
  Do gt2=1,2
ZcplcHpmVPVWm(gt2) = ZcplcHpmVPVWm(gt2) + ZRUZP(gt2,gt1)*TempcplcHpmVPVWm(gt1) 
 End Do 
End Do 
TempcplcHpmVPVWm = ZcplcHpmVPVWm 


 ! ## ZcplcHpmVWmVZ ## 
ZcplcHpmVWmVZ = 0._dp 
TempcplcHpmVWmVZ = cplcHpmVWmVZ 
Do gt1=1,2
  Do gt2=1,2
ZcplcHpmVWmVZ(gt2) = ZcplcHpmVWmVZ(gt2) + ZRUZP(gt2,gt1)*TempcplcHpmVWmVZ(gt1) 
 End Do 
End Do 
TempcplcHpmVWmVZ = ZcplcHpmVWmVZ 


 ! ## ZcplAhAhcVWmVWm ## 
ZcplAhAhcVWmVWm = 0._dp 


 ! ## ZcplAhAhVZVZ ## 
ZcplAhAhVZVZ = 0._dp 


 ! ## ZcplAhHpmcVWmVP ## 
ZcplAhHpmcVWmVP = 0._dp 


 ! ## ZcplAhHpmcVWmVZ ## 
ZcplAhHpmcVWmVZ = 0._dp 


 ! ## ZcplAhcHpmVPVWm ## 
ZcplAhcHpmVPVWm = 0._dp 


 ! ## ZcplAhcHpmVWmVZ ## 
ZcplAhcHpmVWmVZ = 0._dp 


 ! ## ZcplhhhhcVWmVWm ## 
ZcplhhhhcVWmVWm = 0._dp 


 ! ## ZcplhhhhVZVZ ## 
ZcplhhhhVZVZ = 0._dp 


 ! ## ZcplhhHpmcVWmVP ## 
ZcplhhHpmcVWmVP = 0._dp 


 ! ## ZcplhhHpmcVWmVZ ## 
ZcplhhHpmcVWmVZ = 0._dp 


 ! ## ZcplhhcHpmVPVWm ## 
ZcplhhcHpmVPVWm = 0._dp 


 ! ## ZcplhhcHpmVWmVZ ## 
ZcplhhcHpmVWmVZ = 0._dp 


 ! ## ZcplHpmcHpmVPVP ## 
ZcplHpmcHpmVPVP = 0._dp 


 ! ## ZcplHpmcHpmVPVZ ## 
ZcplHpmcHpmVPVZ = 0._dp 


 ! ## ZcplHpmcHpmcVWmVWm ## 
ZcplHpmcHpmcVWmVWm = 0._dp 


 ! ## ZcplHpmcHpmVZVZ ## 
ZcplHpmcHpmVZVZ = 0._dp 


 ! ## ZcplSdcSdVGVG ## 
ZcplSdcSdVGVG = 0._dp 


 ! ## ZcplSdcSdVGVP ## 
ZcplSdcSdVGVP = 0._dp 


 ! ## ZcplSdcSdVGVZ ## 
ZcplSdcSdVGVZ = 0._dp 


 ! ## ZcplSdcSucVWmVG ## 
ZcplSdcSucVWmVG = 0._dp 


 ! ## ZcplSdcSdVPVP ## 
ZcplSdcSdVPVP = 0._dp 


 ! ## ZcplSdcSdVPVZ ## 
ZcplSdcSdVPVZ = 0._dp 


 ! ## ZcplSdcSucVWmVP ## 
ZcplSdcSucVWmVP = 0._dp 


 ! ## ZcplSdcSdcVWmVWm ## 
ZcplSdcSdcVWmVWm = 0._dp 


 ! ## ZcplSdcSdVZVZ ## 
ZcplSdcSdVZVZ = 0._dp 


 ! ## ZcplSdcSucVWmVZ ## 
ZcplSdcSucVWmVZ = 0._dp 


 ! ## ZcplSecSeVPVP ## 
ZcplSecSeVPVP = 0._dp 


 ! ## ZcplSecSeVPVZ ## 
ZcplSecSeVPVZ = 0._dp 


 ! ## ZcplSecSvcVWmVP ## 
ZcplSecSvcVWmVP = 0._dp 


 ! ## ZcplSecSecVWmVWm ## 
ZcplSecSecVWmVWm = 0._dp 


 ! ## ZcplSecSeVZVZ ## 
ZcplSecSeVZVZ = 0._dp 


 ! ## ZcplSecSvcVWmVZ ## 
ZcplSecSvcVWmVZ = 0._dp 


 ! ## ZcplSucSuVGVG ## 
ZcplSucSuVGVG = 0._dp 


 ! ## ZcplSucSuVGVP ## 
ZcplSucSuVGVP = 0._dp 


 ! ## ZcplSucSdVGVWm ## 
ZcplSucSdVGVWm = 0._dp 


 ! ## ZcplSucSuVGVZ ## 
ZcplSucSuVGVZ = 0._dp 


 ! ## ZcplSucSuVPVP ## 
ZcplSucSuVPVP = 0._dp 


 ! ## ZcplSucSdVPVWm ## 
ZcplSucSdVPVWm = 0._dp 


 ! ## ZcplSucSuVPVZ ## 
ZcplSucSuVPVZ = 0._dp 


 ! ## ZcplSucSdVWmVZ ## 
ZcplSucSdVWmVZ = 0._dp 


 ! ## ZcplSucSucVWmVWm ## 
ZcplSucSucVWmVWm = 0._dp 


 ! ## ZcplSucSuVZVZ ## 
ZcplSucSuVZVZ = 0._dp 


 ! ## ZcplSvcSeVPVWm ## 
ZcplSvcSeVPVWm = 0._dp 


 ! ## ZcplSvcSeVWmVZ ## 
ZcplSvcSeVWmVZ = 0._dp 


 ! ## ZcplSvcSvcVWmVWm ## 
ZcplSvcSvcVWmVWm = 0._dp 


 ! ## ZcplSvcSvVZVZ ## 
ZcplSvcSvVZVZ = 0._dp 


 ! ## ZcplVGVGVG ## 
ZcplVGVGVG = 0._dp 
TempcplVGVGVG = cplVGVGVG 
ZcplVGVGVG = TempcplVGVGVG 


 ! ## ZcplcVWmVPVWm ## 
ZcplcVWmVPVWm = 0._dp 
TempcplcVWmVPVWm = cplcVWmVPVWm 
ZcplcVWmVPVWm = TempcplcVWmVPVWm 


 ! ## ZcplcVWmVWmVZ ## 
ZcplcVWmVWmVZ = 0._dp 
TempcplcVWmVWmVZ = cplcVWmVWmVZ 
ZcplcVWmVWmVZ = TempcplcVWmVWmVZ 


 ! ## ZcplcChaChaAhL ## 
ZcplcChaChaAhL = 0._dp 
TempcplcChaChaAhL = cplcChaChaAhL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaAhL(gt2,:,:) = ZcplcChaChaAhL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChaChaAhL(gt1,:,:) 
 End Do 
End Do 
TempcplcChaChaAhL = ZcplcChaChaAhL 
ZcplcChaChaAhL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaAhL(:,gt2,:) = ZcplcChaChaAhL(:,gt2,:) + ZRUUM(gt2,gt1)*TempcplcChaChaAhL(:,gt1,:) 
 End Do 
End Do 
TempcplcChaChaAhL = ZcplcChaChaAhL 
ZcplcChaChaAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaChaAhL(:,:,gt2) = ZcplcChaChaAhL(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcChaChaAhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaChaAhR ## 
ZcplcChaChaAhR = 0._dp 
TempcplcChaChaAhR = cplcChaChaAhR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaAhR(gt2,:,:) = ZcplcChaChaAhR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChaChaAhR(gt1,:,:) 
 End Do 
End Do 
TempcplcChaChaAhR = ZcplcChaChaAhR 
ZcplcChaChaAhR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaAhR(:,gt2,:) = ZcplcChaChaAhR(:,gt2,:) + ZRUUPc(gt2,gt1)*TempcplcChaChaAhR(:,gt1,:) 
 End Do 
End Do 
TempcplcChaChaAhR = ZcplcChaChaAhR 
ZcplcChaChaAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaChaAhR(:,:,gt2) = ZcplcChaChaAhR(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcChaChaAhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChiAhL ## 
ZcplChiChiAhL = 0._dp 
TempcplChiChiAhL = cplChiChiAhL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiAhL(gt2,:,:) = ZcplChiChiAhL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiChiAhL(gt1,:,:) 
 End Do 
End Do 
TempcplChiChiAhL = ZcplChiChiAhL 
ZcplChiChiAhL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiAhL(:,gt2,:) = ZcplChiChiAhL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplChiChiAhL(:,gt1,:) 
 End Do 
End Do 
TempcplChiChiAhL = ZcplChiChiAhL 
ZcplChiChiAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiChiAhL(:,:,gt2) = ZcplChiChiAhL(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplChiChiAhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChiAhR ## 
ZcplChiChiAhR = 0._dp 
TempcplChiChiAhR = cplChiChiAhR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiAhR(gt2,:,:) = ZcplChiChiAhR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiChiAhR(gt1,:,:) 
 End Do 
End Do 
TempcplChiChiAhR = ZcplChiChiAhR 
ZcplChiChiAhR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiAhR(:,gt2,:) = ZcplChiChiAhR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplChiChiAhR(:,gt1,:) 
 End Do 
End Do 
TempcplChiChiAhR = ZcplChiChiAhR 
ZcplChiChiAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiChiAhR(:,:,gt2) = ZcplChiChiAhR(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplChiChiAhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFdAhL ## 
ZcplcFdFdAhL = 0._dp 
TempcplcFdFdAhL = cplcFdFdAhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdAhL(gt2,:,:) = ZcplcFdFdAhL(gt2,:,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdAhL(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFdAhL = ZcplcFdFdAhL 
ZcplcFdFdAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdAhL(:,gt2,:) = ZcplcFdFdAhL(:,gt2,:) + ZRUZDL(gt2,gt1)*TempcplcFdFdAhL(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFdAhL = ZcplcFdFdAhL 
ZcplcFdFdAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdAhL(:,:,gt2) = ZcplcFdFdAhL(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcFdFdAhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFdAhR ## 
ZcplcFdFdAhR = 0._dp 
TempcplcFdFdAhR = cplcFdFdAhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdAhR(gt2,:,:) = ZcplcFdFdAhR(gt2,:,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdAhR(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFdAhR = ZcplcFdFdAhR 
ZcplcFdFdAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdAhR(:,gt2,:) = ZcplcFdFdAhR(:,gt2,:) + ZRUZDRc(gt2,gt1)*TempcplcFdFdAhR(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFdAhR = ZcplcFdFdAhR 
ZcplcFdFdAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdAhR(:,:,gt2) = ZcplcFdFdAhR(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcFdFdAhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFeAhL ## 
ZcplcFeFeAhL = 0._dp 
TempcplcFeFeAhL = cplcFeFeAhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeAhL(gt2,:,:) = ZcplcFeFeAhL(gt2,:,:) + ZRUZER(gt2,gt1)*TempcplcFeFeAhL(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFeAhL = ZcplcFeFeAhL 
ZcplcFeFeAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeAhL(:,gt2,:) = ZcplcFeFeAhL(:,gt2,:) + ZRUZEL(gt2,gt1)*TempcplcFeFeAhL(:,gt1,:) 
 End Do 
End Do 
TempcplcFeFeAhL = ZcplcFeFeAhL 
ZcplcFeFeAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeAhL(:,:,gt2) = ZcplcFeFeAhL(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcFeFeAhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFeAhR ## 
ZcplcFeFeAhR = 0._dp 
TempcplcFeFeAhR = cplcFeFeAhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeAhR(gt2,:,:) = ZcplcFeFeAhR(gt2,:,:) + ZRUZELc(gt2,gt1)*TempcplcFeFeAhR(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFeAhR = ZcplcFeFeAhR 
ZcplcFeFeAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeAhR(:,gt2,:) = ZcplcFeFeAhR(:,gt2,:) + ZRUZERc(gt2,gt1)*TempcplcFeFeAhR(:,gt1,:) 
 End Do 
End Do 
TempcplcFeFeAhR = ZcplcFeFeAhR 
ZcplcFeFeAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeAhR(:,:,gt2) = ZcplcFeFeAhR(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcFeFeAhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFuAhL ## 
ZcplcFuFuAhL = 0._dp 
TempcplcFuFuAhL = cplcFuFuAhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuAhL(gt2,:,:) = ZcplcFuFuAhL(gt2,:,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuAhL(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFuAhL = ZcplcFuFuAhL 
ZcplcFuFuAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuAhL(:,gt2,:) = ZcplcFuFuAhL(:,gt2,:) + ZRUZUL(gt2,gt1)*TempcplcFuFuAhL(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFuAhL = ZcplcFuFuAhL 
ZcplcFuFuAhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuAhL(:,:,gt2) = ZcplcFuFuAhL(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcFuFuAhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFuAhR ## 
ZcplcFuFuAhR = 0._dp 
TempcplcFuFuAhR = cplcFuFuAhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuAhR(gt2,:,:) = ZcplcFuFuAhR(gt2,:,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuAhR(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFuAhR = ZcplcFuFuAhR 
ZcplcFuFuAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuAhR(:,gt2,:) = ZcplcFuFuAhR(:,gt2,:) + ZRUZURc(gt2,gt1)*TempcplcFuFuAhR(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFuAhR = ZcplcFuFuAhR 
ZcplcFuFuAhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuAhR(:,:,gt2) = ZcplcFuFuAhR(:,:,gt2) + ZRUZA(gt2,gt1)*TempcplcFuFuAhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChacHpmL ## 
ZcplChiChacHpmL = 0._dp 
TempcplChiChacHpmL = cplChiChacHpmL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChacHpmL(gt2,:,:) = ZcplChiChacHpmL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiChacHpmL(gt1,:,:) 
 End Do 
End Do 
TempcplChiChacHpmL = ZcplChiChacHpmL 
ZcplChiChacHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplChiChacHpmL(:,gt2,:) = ZcplChiChacHpmL(:,gt2,:) + ZRUUM(gt2,gt1)*TempcplChiChacHpmL(:,gt1,:) 
 End Do 
End Do 
TempcplChiChacHpmL = ZcplChiChacHpmL 
ZcplChiChacHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplChiChacHpmL(:,:,gt2) = ZcplChiChacHpmL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplChiChacHpmL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChacHpmR ## 
ZcplChiChacHpmR = 0._dp 
TempcplChiChacHpmR = cplChiChacHpmR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChacHpmR(gt2,:,:) = ZcplChiChacHpmR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiChacHpmR(gt1,:,:) 
 End Do 
End Do 
TempcplChiChacHpmR = ZcplChiChacHpmR 
ZcplChiChacHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplChiChacHpmR(:,gt2,:) = ZcplChiChacHpmR(:,gt2,:) + ZRUUPc(gt2,gt1)*TempcplChiChacHpmR(:,gt1,:) 
 End Do 
End Do 
TempcplChiChacHpmR = ZcplChiChacHpmR 
ZcplChiChacHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplChiChacHpmR(:,:,gt2) = ZcplChiChacHpmR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplChiChacHpmR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChaFucSdL ## 
ZcplChaFucSdL = 0._dp 
TempcplChaFucSdL = cplChaFucSdL 
Do gt1=1,2
  Do gt2=1,2
ZcplChaFucSdL(gt2,:,:) = ZcplChaFucSdL(gt2,:,:) + ZRUUM(gt2,gt1)*TempcplChaFucSdL(gt1,:,:) 
 End Do 
End Do 
TempcplChaFucSdL = ZcplChaFucSdL 
ZcplChaFucSdL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChaFucSdL(:,gt2,:) = ZcplChaFucSdL(:,gt2,:) + ZRUZUL(gt2,gt1)*TempcplChaFucSdL(:,gt1,:) 
 End Do 
End Do 
TempcplChaFucSdL = ZcplChaFucSdL 
ZcplChaFucSdL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChaFucSdL(:,:,gt2) = ZcplChaFucSdL(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplChaFucSdL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChaFucSdR ## 
ZcplChaFucSdR = 0._dp 
TempcplChaFucSdR = cplChaFucSdR 
Do gt1=1,2
  Do gt2=1,2
ZcplChaFucSdR(gt2,:,:) = ZcplChaFucSdR(gt2,:,:) + ZRUUPc(gt2,gt1)*TempcplChaFucSdR(gt1,:,:) 
 End Do 
End Do 
TempcplChaFucSdR = ZcplChaFucSdR 
ZcplChaFucSdR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChaFucSdR(:,gt2,:) = ZcplChaFucSdR(:,gt2,:) + ZRUZURc(gt2,gt1)*TempcplChaFucSdR(:,gt1,:) 
 End Do 
End Do 
TempcplChaFucSdR = ZcplChaFucSdR 
ZcplChaFucSdR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChaFucSdR(:,:,gt2) = ZcplChaFucSdR(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplChaFucSdR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChaFvcSeL ## 
ZcplChaFvcSeL = 0._dp 
TempcplChaFvcSeL = cplChaFvcSeL 
Do gt1=1,2
  Do gt2=1,2
ZcplChaFvcSeL(gt2,:,:) = ZcplChaFvcSeL(gt2,:,:) + ZRUUM(gt2,gt1)*TempcplChaFvcSeL(gt1,:,:) 
 End Do 
End Do 
TempcplChaFvcSeL = ZcplChaFvcSeL 
ZcplChaFvcSeL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChaFvcSeL(:,:,gt2) = ZcplChaFvcSeL(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplChaFvcSeL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChaFvcSeR ## 
ZcplChaFvcSeR = 0._dp 
TempcplChaFvcSeR = cplChaFvcSeR 
Do gt1=1,2
  Do gt2=1,2
ZcplChaFvcSeR(gt2,:,:) = ZcplChaFvcSeR(gt2,:,:) + ZRUUPc(gt2,gt1)*TempcplChaFvcSeR(gt1,:,:) 
 End Do 
End Do 
TempcplChaFvcSeR = ZcplChaFvcSeR 
ZcplChaFvcSeR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChaFvcSeR(:,:,gt2) = ZcplChaFvcSeR(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplChaFvcSeR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaChahhL ## 
ZcplcChaChahhL = 0._dp 
TempcplcChaChahhL = cplcChaChahhL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChahhL(gt2,:,:) = ZcplcChaChahhL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChaChahhL(gt1,:,:) 
 End Do 
End Do 
TempcplcChaChahhL = ZcplcChaChahhL 
ZcplcChaChahhL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChahhL(:,gt2,:) = ZcplcChaChahhL(:,gt2,:) + ZRUUM(gt2,gt1)*TempcplcChaChahhL(:,gt1,:) 
 End Do 
End Do 
TempcplcChaChahhL = ZcplcChaChahhL 
ZcplcChaChahhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaChahhL(:,:,gt2) = ZcplcChaChahhL(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcChaChahhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaChahhR ## 
ZcplcChaChahhR = 0._dp 
TempcplcChaChahhR = cplcChaChahhR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChahhR(gt2,:,:) = ZcplcChaChahhR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChaChahhR(gt1,:,:) 
 End Do 
End Do 
TempcplcChaChahhR = ZcplcChaChahhR 
ZcplcChaChahhR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChahhR(:,gt2,:) = ZcplcChaChahhR(:,gt2,:) + ZRUUPc(gt2,gt1)*TempcplcChaChahhR(:,gt1,:) 
 End Do 
End Do 
TempcplcChaChahhR = ZcplcChaChahhR 
ZcplcChaChahhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaChahhR(:,:,gt2) = ZcplcChaChahhR(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcChaChahhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdChaSuL ## 
ZcplcFdChaSuL = 0._dp 
TempcplcFdChaSuL = cplcFdChaSuL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdChaSuL(gt2,:,:) = ZcplcFdChaSuL(gt2,:,:) + ZRUZDR(gt2,gt1)*TempcplcFdChaSuL(gt1,:,:) 
 End Do 
End Do 
TempcplcFdChaSuL = ZcplcFdChaSuL 
ZcplcFdChaSuL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFdChaSuL(:,gt2,:) = ZcplcFdChaSuL(:,gt2,:) + ZRUUM(gt2,gt1)*TempcplcFdChaSuL(:,gt1,:) 
 End Do 
End Do 
TempcplcFdChaSuL = ZcplcFdChaSuL 
ZcplcFdChaSuL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFdChaSuL(:,:,gt2) = ZcplcFdChaSuL(:,:,gt2) + ZRUZU(gt2,gt1)*TempcplcFdChaSuL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdChaSuR ## 
ZcplcFdChaSuR = 0._dp 
TempcplcFdChaSuR = cplcFdChaSuR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdChaSuR(gt2,:,:) = ZcplcFdChaSuR(gt2,:,:) + ZRUZDLc(gt2,gt1)*TempcplcFdChaSuR(gt1,:,:) 
 End Do 
End Do 
TempcplcFdChaSuR = ZcplcFdChaSuR 
ZcplcFdChaSuR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFdChaSuR(:,gt2,:) = ZcplcFdChaSuR(:,gt2,:) + ZRUUPc(gt2,gt1)*TempcplcFdChaSuR(:,gt1,:) 
 End Do 
End Do 
TempcplcFdChaSuR = ZcplcFdChaSuR 
ZcplcFdChaSuR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFdChaSuR(:,:,gt2) = ZcplcFdChaSuR(:,:,gt2) + ZRUZU(gt2,gt1)*TempcplcFdChaSuR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeChaSvL ## 
ZcplcFeChaSvL = 0._dp 
TempcplcFeChaSvL = cplcFeChaSvL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeChaSvL(gt2,:,:) = ZcplcFeChaSvL(gt2,:,:) + ZRUZER(gt2,gt1)*TempcplcFeChaSvL(gt1,:,:) 
 End Do 
End Do 
TempcplcFeChaSvL = ZcplcFeChaSvL 
ZcplcFeChaSvL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFeChaSvL(:,gt2,:) = ZcplcFeChaSvL(:,gt2,:) + ZRUUM(gt2,gt1)*TempcplcFeChaSvL(:,gt1,:) 
 End Do 
End Do 
TempcplcFeChaSvL = ZcplcFeChaSvL 
ZcplcFeChaSvL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeChaSvL(:,:,gt2) = ZcplcFeChaSvL(:,:,gt2) + ZRUZV(gt2,gt1)*TempcplcFeChaSvL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeChaSvR ## 
ZcplcFeChaSvR = 0._dp 
TempcplcFeChaSvR = cplcFeChaSvR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeChaSvR(gt2,:,:) = ZcplcFeChaSvR(gt2,:,:) + ZRUZELc(gt2,gt1)*TempcplcFeChaSvR(gt1,:,:) 
 End Do 
End Do 
TempcplcFeChaSvR = ZcplcFeChaSvR 
ZcplcFeChaSvR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFeChaSvR(:,gt2,:) = ZcplcFeChaSvR(:,gt2,:) + ZRUUPc(gt2,gt1)*TempcplcFeChaSvR(:,gt1,:) 
 End Do 
End Do 
TempcplcFeChaSvR = ZcplcFeChaSvR 
ZcplcFeChaSvR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeChaSvR(:,:,gt2) = ZcplcFeChaSvR(:,:,gt2) + ZRUZV(gt2,gt1)*TempcplcFeChaSvR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChihhL ## 
ZcplChiChihhL = 0._dp 
TempcplChiChihhL = cplChiChihhL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChihhL(gt2,:,:) = ZcplChiChihhL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiChihhL(gt1,:,:) 
 End Do 
End Do 
TempcplChiChihhL = ZcplChiChihhL 
ZcplChiChihhL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChihhL(:,gt2,:) = ZcplChiChihhL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplChiChihhL(:,gt1,:) 
 End Do 
End Do 
TempcplChiChihhL = ZcplChiChihhL 
ZcplChiChihhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiChihhL(:,:,gt2) = ZcplChiChihhL(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplChiChihhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChihhR ## 
ZcplChiChihhR = 0._dp 
TempcplChiChihhR = cplChiChihhR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChihhR(gt2,:,:) = ZcplChiChihhR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiChihhR(gt1,:,:) 
 End Do 
End Do 
TempcplChiChihhR = ZcplChiChihhR 
ZcplChiChihhR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChihhR(:,gt2,:) = ZcplChiChihhR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplChiChihhR(:,gt1,:) 
 End Do 
End Do 
TempcplChiChihhR = ZcplChiChihhR 
ZcplChiChihhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiChihhR(:,:,gt2) = ZcplChiChihhR(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplChiChihhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFdcSdL ## 
ZcplChiFdcSdL = 0._dp 
TempcplChiFdcSdL = cplChiFdcSdL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFdcSdL(gt2,:,:) = ZcplChiFdcSdL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiFdcSdL(gt1,:,:) 
 End Do 
End Do 
TempcplChiFdcSdL = ZcplChiFdcSdL 
ZcplChiFdcSdL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFdcSdL(:,gt2,:) = ZcplChiFdcSdL(:,gt2,:) + ZRUZDL(gt2,gt1)*TempcplChiFdcSdL(:,gt1,:) 
 End Do 
End Do 
TempcplChiFdcSdL = ZcplChiFdcSdL 
ZcplChiFdcSdL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChiFdcSdL(:,:,gt2) = ZcplChiFdcSdL(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplChiFdcSdL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFdcSdR ## 
ZcplChiFdcSdR = 0._dp 
TempcplChiFdcSdR = cplChiFdcSdR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFdcSdR(gt2,:,:) = ZcplChiFdcSdR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiFdcSdR(gt1,:,:) 
 End Do 
End Do 
TempcplChiFdcSdR = ZcplChiFdcSdR 
ZcplChiFdcSdR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFdcSdR(:,gt2,:) = ZcplChiFdcSdR(:,gt2,:) + ZRUZDRc(gt2,gt1)*TempcplChiFdcSdR(:,gt1,:) 
 End Do 
End Do 
TempcplChiFdcSdR = ZcplChiFdcSdR 
ZcplChiFdcSdR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChiFdcSdR(:,:,gt2) = ZcplChiFdcSdR(:,:,gt2) + ZRUZDc(gt2,gt1)*TempcplChiFdcSdR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFecSeL ## 
ZcplChiFecSeL = 0._dp 
TempcplChiFecSeL = cplChiFecSeL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFecSeL(gt2,:,:) = ZcplChiFecSeL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiFecSeL(gt1,:,:) 
 End Do 
End Do 
TempcplChiFecSeL = ZcplChiFecSeL 
ZcplChiFecSeL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFecSeL(:,gt2,:) = ZcplChiFecSeL(:,gt2,:) + ZRUZEL(gt2,gt1)*TempcplChiFecSeL(:,gt1,:) 
 End Do 
End Do 
TempcplChiFecSeL = ZcplChiFecSeL 
ZcplChiFecSeL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChiFecSeL(:,:,gt2) = ZcplChiFecSeL(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplChiFecSeL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFecSeR ## 
ZcplChiFecSeR = 0._dp 
TempcplChiFecSeR = cplChiFecSeR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFecSeR(gt2,:,:) = ZcplChiFecSeR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiFecSeR(gt1,:,:) 
 End Do 
End Do 
TempcplChiFecSeR = ZcplChiFecSeR 
ZcplChiFecSeR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFecSeR(:,gt2,:) = ZcplChiFecSeR(:,gt2,:) + ZRUZERc(gt2,gt1)*TempcplChiFecSeR(:,gt1,:) 
 End Do 
End Do 
TempcplChiFecSeR = ZcplChiFecSeR 
ZcplChiFecSeR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChiFecSeR(:,:,gt2) = ZcplChiFecSeR(:,:,gt2) + ZRUZEc(gt2,gt1)*TempcplChiFecSeR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFucSuL ## 
ZcplChiFucSuL = 0._dp 
TempcplChiFucSuL = cplChiFucSuL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFucSuL(gt2,:,:) = ZcplChiFucSuL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiFucSuL(gt1,:,:) 
 End Do 
End Do 
TempcplChiFucSuL = ZcplChiFucSuL 
ZcplChiFucSuL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFucSuL(:,gt2,:) = ZcplChiFucSuL(:,gt2,:) + ZRUZUL(gt2,gt1)*TempcplChiFucSuL(:,gt1,:) 
 End Do 
End Do 
TempcplChiFucSuL = ZcplChiFucSuL 
ZcplChiFucSuL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChiFucSuL(:,:,gt2) = ZcplChiFucSuL(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplChiFucSuL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFucSuR ## 
ZcplChiFucSuR = 0._dp 
TempcplChiFucSuR = cplChiFucSuR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFucSuR(gt2,:,:) = ZcplChiFucSuR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiFucSuR(gt1,:,:) 
 End Do 
End Do 
TempcplChiFucSuR = ZcplChiFucSuR 
ZcplChiFucSuR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFucSuR(:,gt2,:) = ZcplChiFucSuR(:,gt2,:) + ZRUZURc(gt2,gt1)*TempcplChiFucSuR(:,gt1,:) 
 End Do 
End Do 
TempcplChiFucSuR = ZcplChiFucSuR 
ZcplChiFucSuR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplChiFucSuR(:,:,gt2) = ZcplChiFucSuR(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplChiFucSuR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFvcSvL ## 
ZcplChiFvcSvL = 0._dp 
TempcplChiFvcSvL = cplChiFvcSvL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFvcSvL(gt2,:,:) = ZcplChiFvcSvL(gt2,:,:) + ZRUZN(gt2,gt1)*TempcplChiFvcSvL(gt1,:,:) 
 End Do 
End Do 
TempcplChiFvcSvL = ZcplChiFvcSvL 
ZcplChiFvcSvL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFvcSvL(:,:,gt2) = ZcplChiFvcSvL(:,:,gt2) + ZRUZVc(gt2,gt1)*TempcplChiFvcSvL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiFvcSvR ## 
ZcplChiFvcSvR = 0._dp 
TempcplChiFvcSvR = cplChiFvcSvR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiFvcSvR(gt2,:,:) = ZcplChiFvcSvR(gt2,:,:) + ZRUZNc(gt2,gt1)*TempcplChiFvcSvR(gt1,:,:) 
 End Do 
End Do 
TempcplChiFvcSvR = ZcplChiFvcSvR 
ZcplChiFvcSvR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplChiFvcSvR(:,:,gt2) = ZcplChiFvcSvR(:,:,gt2) + ZRUZVc(gt2,gt1)*TempcplChiFvcSvR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaChiHpmL ## 
ZcplcChaChiHpmL = 0._dp 
TempcplcChaChiHpmL = cplcChaChiHpmL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChiHpmL(gt2,:,:) = ZcplcChaChiHpmL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChaChiHpmL(gt1,:,:) 
 End Do 
End Do 
TempcplcChaChiHpmL = ZcplcChaChiHpmL 
ZcplcChaChiHpmL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcChaChiHpmL(:,gt2,:) = ZcplcChaChiHpmL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplcChaChiHpmL(:,gt1,:) 
 End Do 
End Do 
TempcplcChaChiHpmL = ZcplcChaChiHpmL 
ZcplcChaChiHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChiHpmL(:,:,gt2) = ZcplcChaChiHpmL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcChaChiHpmL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaChiHpmR ## 
ZcplcChaChiHpmR = 0._dp 
TempcplcChaChiHpmR = cplcChaChiHpmR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChiHpmR(gt2,:,:) = ZcplcChaChiHpmR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChaChiHpmR(gt1,:,:) 
 End Do 
End Do 
TempcplcChaChiHpmR = ZcplcChaChiHpmR 
ZcplcChaChiHpmR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcChaChiHpmR(:,gt2,:) = ZcplcChaChiHpmR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplcChaChiHpmR(:,gt1,:) 
 End Do 
End Do 
TempcplcChaChiHpmR = ZcplcChaChiHpmR 
ZcplcChaChiHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChiHpmR(:,:,gt2) = ZcplcChaChiHpmR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcChaChiHpmR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdChiSdL ## 
ZcplcFdChiSdL = 0._dp 
TempcplcFdChiSdL = cplcFdChiSdL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdChiSdL(gt2,:,:) = ZcplcFdChiSdL(gt2,:,:) + ZRUZDR(gt2,gt1)*TempcplcFdChiSdL(gt1,:,:) 
 End Do 
End Do 
TempcplcFdChiSdL = ZcplcFdChiSdL 
ZcplcFdChiSdL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFdChiSdL(:,gt2,:) = ZcplcFdChiSdL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplcFdChiSdL(:,gt1,:) 
 End Do 
End Do 
TempcplcFdChiSdL = ZcplcFdChiSdL 
ZcplcFdChiSdL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFdChiSdL(:,:,gt2) = ZcplcFdChiSdL(:,:,gt2) + ZRUZD(gt2,gt1)*TempcplcFdChiSdL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdChiSdR ## 
ZcplcFdChiSdR = 0._dp 
TempcplcFdChiSdR = cplcFdChiSdR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdChiSdR(gt2,:,:) = ZcplcFdChiSdR(gt2,:,:) + ZRUZDLc(gt2,gt1)*TempcplcFdChiSdR(gt1,:,:) 
 End Do 
End Do 
TempcplcFdChiSdR = ZcplcFdChiSdR 
ZcplcFdChiSdR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFdChiSdR(:,gt2,:) = ZcplcFdChiSdR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplcFdChiSdR(:,gt1,:) 
 End Do 
End Do 
TempcplcFdChiSdR = ZcplcFdChiSdR 
ZcplcFdChiSdR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFdChiSdR(:,:,gt2) = ZcplcFdChiSdR(:,:,gt2) + ZRUZD(gt2,gt1)*TempcplcFdChiSdR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeChiSeL ## 
ZcplcFeChiSeL = 0._dp 
TempcplcFeChiSeL = cplcFeChiSeL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeChiSeL(gt2,:,:) = ZcplcFeChiSeL(gt2,:,:) + ZRUZER(gt2,gt1)*TempcplcFeChiSeL(gt1,:,:) 
 End Do 
End Do 
TempcplcFeChiSeL = ZcplcFeChiSeL 
ZcplcFeChiSeL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFeChiSeL(:,gt2,:) = ZcplcFeChiSeL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplcFeChiSeL(:,gt1,:) 
 End Do 
End Do 
TempcplcFeChiSeL = ZcplcFeChiSeL 
ZcplcFeChiSeL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFeChiSeL(:,:,gt2) = ZcplcFeChiSeL(:,:,gt2) + ZRUZE(gt2,gt1)*TempcplcFeChiSeL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeChiSeR ## 
ZcplcFeChiSeR = 0._dp 
TempcplcFeChiSeR = cplcFeChiSeR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeChiSeR(gt2,:,:) = ZcplcFeChiSeR(gt2,:,:) + ZRUZELc(gt2,gt1)*TempcplcFeChiSeR(gt1,:,:) 
 End Do 
End Do 
TempcplcFeChiSeR = ZcplcFeChiSeR 
ZcplcFeChiSeR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFeChiSeR(:,gt2,:) = ZcplcFeChiSeR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplcFeChiSeR(:,gt1,:) 
 End Do 
End Do 
TempcplcFeChiSeR = ZcplcFeChiSeR 
ZcplcFeChiSeR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFeChiSeR(:,:,gt2) = ZcplcFeChiSeR(:,:,gt2) + ZRUZE(gt2,gt1)*TempcplcFeChiSeR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuChiSuL ## 
ZcplcFuChiSuL = 0._dp 
TempcplcFuChiSuL = cplcFuChiSuL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuChiSuL(gt2,:,:) = ZcplcFuChiSuL(gt2,:,:) + ZRUZUR(gt2,gt1)*TempcplcFuChiSuL(gt1,:,:) 
 End Do 
End Do 
TempcplcFuChiSuL = ZcplcFuChiSuL 
ZcplcFuChiSuL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFuChiSuL(:,gt2,:) = ZcplcFuChiSuL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplcFuChiSuL(:,gt1,:) 
 End Do 
End Do 
TempcplcFuChiSuL = ZcplcFuChiSuL 
ZcplcFuChiSuL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFuChiSuL(:,:,gt2) = ZcplcFuChiSuL(:,:,gt2) + ZRUZU(gt2,gt1)*TempcplcFuChiSuL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuChiSuR ## 
ZcplcFuChiSuR = 0._dp 
TempcplcFuChiSuR = cplcFuChiSuR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuChiSuR(gt2,:,:) = ZcplcFuChiSuR(gt2,:,:) + ZRUZULc(gt2,gt1)*TempcplcFuChiSuR(gt1,:,:) 
 End Do 
End Do 
TempcplcFuChiSuR = ZcplcFuChiSuR 
ZcplcFuChiSuR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFuChiSuR(:,gt2,:) = ZcplcFuChiSuR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplcFuChiSuR(:,gt1,:) 
 End Do 
End Do 
TempcplcFuChiSuR = ZcplcFuChiSuR 
ZcplcFuChiSuR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFuChiSuR(:,:,gt2) = ZcplcFuChiSuR(:,:,gt2) + ZRUZU(gt2,gt1)*TempcplcFuChiSuR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFvChiSvL ## 
ZcplcFvChiSvL = 0._dp 
TempcplcFvChiSvL = cplcFvChiSvL 
ZcplcFvChiSvL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFvChiSvL(:,gt2,:) = ZcplcFvChiSvL(:,gt2,:) + ZRUZN(gt2,gt1)*TempcplcFvChiSvL(:,gt1,:) 
 End Do 
End Do 
TempcplcFvChiSvL = ZcplcFvChiSvL 
ZcplcFvChiSvL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvChiSvL(:,:,gt2) = ZcplcFvChiSvL(:,:,gt2) + ZRUZV(gt2,gt1)*TempcplcFvChiSvL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFvChiSvR ## 
ZcplcFvChiSvR = 0._dp 
TempcplcFvChiSvR = cplcFvChiSvR 
ZcplcFvChiSvR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcFvChiSvR(:,gt2,:) = ZcplcFvChiSvR(:,gt2,:) + ZRUZNc(gt2,gt1)*TempcplcFvChiSvR(:,gt1,:) 
 End Do 
End Do 
TempcplcFvChiSvR = ZcplcFvChiSvR 
ZcplcFvChiSvR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvChiSvR(:,:,gt2) = ZcplcFvChiSvR(:,:,gt2) + ZRUZV(gt2,gt1)*TempcplcFvChiSvR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplGluFdcSdL ## 
ZcplGluFdcSdL = 0._dp 
TempcplGluFdcSdL = cplGluFdcSdL 
ZcplGluFdcSdL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplGluFdcSdL(gt2,:) = ZcplGluFdcSdL(gt2,:) + ZRUZDL(gt2,gt1)*TempcplGluFdcSdL(gt1,:) 
 End Do 
End Do 
TempcplGluFdcSdL = ZcplGluFdcSdL 
ZcplGluFdcSdL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplGluFdcSdL(:,gt2) = ZcplGluFdcSdL(:,gt2) + ZRUZDc(gt2,gt1)*TempcplGluFdcSdL(:,gt1) 
 End Do 
End Do 


 ! ## ZcplGluFdcSdR ## 
ZcplGluFdcSdR = 0._dp 
TempcplGluFdcSdR = cplGluFdcSdR 
ZcplGluFdcSdR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplGluFdcSdR(gt2,:) = ZcplGluFdcSdR(gt2,:) + ZRUZDRc(gt2,gt1)*TempcplGluFdcSdR(gt1,:) 
 End Do 
End Do 
TempcplGluFdcSdR = ZcplGluFdcSdR 
ZcplGluFdcSdR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplGluFdcSdR(:,gt2) = ZcplGluFdcSdR(:,gt2) + ZRUZDc(gt2,gt1)*TempcplGluFdcSdR(:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFdhhL ## 
ZcplcFdFdhhL = 0._dp 
TempcplcFdFdhhL = cplcFdFdhhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhL(gt2,:,:) = ZcplcFdFdhhL(gt2,:,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdhhL(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFdhhL = ZcplcFdFdhhL 
ZcplcFdFdhhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhL(:,gt2,:) = ZcplcFdFdhhL(:,gt2,:) + ZRUZDL(gt2,gt1)*TempcplcFdFdhhL(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFdhhL = ZcplcFdFdhhL 
ZcplcFdFdhhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhL(:,:,gt2) = ZcplcFdFdhhL(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcFdFdhhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFdhhR ## 
ZcplcFdFdhhR = 0._dp 
TempcplcFdFdhhR = cplcFdFdhhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhR(gt2,:,:) = ZcplcFdFdhhR(gt2,:,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdhhR(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFdhhR = ZcplcFdFdhhR 
ZcplcFdFdhhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhR(:,gt2,:) = ZcplcFdFdhhR(:,gt2,:) + ZRUZDRc(gt2,gt1)*TempcplcFdFdhhR(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFdhhR = ZcplcFdFdhhR 
ZcplcFdFdhhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhR(:,:,gt2) = ZcplcFdFdhhR(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcFdFdhhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaFdcSuL ## 
ZcplcChaFdcSuL = 0._dp 
TempcplcChaFdcSuL = cplcChaFdcSuL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaFdcSuL(gt2,:,:) = ZcplcChaFdcSuL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChaFdcSuL(gt1,:,:) 
 End Do 
End Do 
TempcplcChaFdcSuL = ZcplcChaFdcSuL 
ZcplcChaFdcSuL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaFdcSuL(:,gt2,:) = ZcplcChaFdcSuL(:,gt2,:) + ZRUZDL(gt2,gt1)*TempcplcChaFdcSuL(:,gt1,:) 
 End Do 
End Do 
TempcplcChaFdcSuL = ZcplcChaFdcSuL 
ZcplcChaFdcSuL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcChaFdcSuL(:,:,gt2) = ZcplcChaFdcSuL(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplcChaFdcSuL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaFdcSuR ## 
ZcplcChaFdcSuR = 0._dp 
TempcplcChaFdcSuR = cplcChaFdcSuR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaFdcSuR(gt2,:,:) = ZcplcChaFdcSuR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChaFdcSuR(gt1,:,:) 
 End Do 
End Do 
TempcplcChaFdcSuR = ZcplcChaFdcSuR 
ZcplcChaFdcSuR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaFdcSuR(:,gt2,:) = ZcplcChaFdcSuR(:,gt2,:) + ZRUZDRc(gt2,gt1)*TempcplcChaFdcSuR(:,gt1,:) 
 End Do 
End Do 
TempcplcChaFdcSuR = ZcplcChaFdcSuR 
ZcplcChaFdcSuR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcChaFdcSuR(:,:,gt2) = ZcplcChaFdcSuR(:,:,gt2) + ZRUZUc(gt2,gt1)*TempcplcChaFdcSuR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFdcHpmL ## 
ZcplcFuFdcHpmL = 0._dp 
TempcplcFuFdcHpmL = cplcFuFdcHpmL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcHpmL(gt2,:,:) = ZcplcFuFdcHpmL(gt2,:,:) + ZRUZUR(gt2,gt1)*TempcplcFuFdcHpmL(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFdcHpmL = ZcplcFuFdcHpmL 
ZcplcFuFdcHpmL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcHpmL(:,gt2,:) = ZcplcFuFdcHpmL(:,gt2,:) + ZRUZDL(gt2,gt1)*TempcplcFuFdcHpmL(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFdcHpmL = ZcplcFuFdcHpmL 
ZcplcFuFdcHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFuFdcHpmL(:,:,gt2) = ZcplcFuFdcHpmL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFuFdcHpmL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFdcHpmR ## 
ZcplcFuFdcHpmR = 0._dp 
TempcplcFuFdcHpmR = cplcFuFdcHpmR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcHpmR(gt2,:,:) = ZcplcFuFdcHpmR(gt2,:,:) + ZRUZULc(gt2,gt1)*TempcplcFuFdcHpmR(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFdcHpmR = ZcplcFuFdcHpmR 
ZcplcFuFdcHpmR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcHpmR(:,gt2,:) = ZcplcFuFdcHpmR(:,gt2,:) + ZRUZDRc(gt2,gt1)*TempcplcFuFdcHpmR(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFdcHpmR = ZcplcFuFdcHpmR 
ZcplcFuFdcHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFuFdcHpmR(:,:,gt2) = ZcplcFuFdcHpmR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFuFdcHpmR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFehhL ## 
ZcplcFeFehhL = 0._dp 
TempcplcFeFehhL = cplcFeFehhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhL(gt2,:,:) = ZcplcFeFehhL(gt2,:,:) + ZRUZER(gt2,gt1)*TempcplcFeFehhL(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFehhL = ZcplcFeFehhL 
ZcplcFeFehhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhL(:,gt2,:) = ZcplcFeFehhL(:,gt2,:) + ZRUZEL(gt2,gt1)*TempcplcFeFehhL(:,gt1,:) 
 End Do 
End Do 
TempcplcFeFehhL = ZcplcFeFehhL 
ZcplcFeFehhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhL(:,:,gt2) = ZcplcFeFehhL(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcFeFehhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFehhR ## 
ZcplcFeFehhR = 0._dp 
TempcplcFeFehhR = cplcFeFehhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhR(gt2,:,:) = ZcplcFeFehhR(gt2,:,:) + ZRUZELc(gt2,gt1)*TempcplcFeFehhR(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFehhR = ZcplcFeFehhR 
ZcplcFeFehhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhR(:,gt2,:) = ZcplcFeFehhR(:,gt2,:) + ZRUZERc(gt2,gt1)*TempcplcFeFehhR(:,gt1,:) 
 End Do 
End Do 
TempcplcFeFehhR = ZcplcFeFehhR 
ZcplcFeFehhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhR(:,:,gt2) = ZcplcFeFehhR(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcFeFehhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaFecSvL ## 
ZcplcChaFecSvL = 0._dp 
TempcplcChaFecSvL = cplcChaFecSvL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaFecSvL(gt2,:,:) = ZcplcChaFecSvL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChaFecSvL(gt1,:,:) 
 End Do 
End Do 
TempcplcChaFecSvL = ZcplcChaFecSvL 
ZcplcChaFecSvL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaFecSvL(:,gt2,:) = ZcplcChaFecSvL(:,gt2,:) + ZRUZEL(gt2,gt1)*TempcplcChaFecSvL(:,gt1,:) 
 End Do 
End Do 
TempcplcChaFecSvL = ZcplcChaFecSvL 
ZcplcChaFecSvL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaFecSvL(:,:,gt2) = ZcplcChaFecSvL(:,:,gt2) + ZRUZVc(gt2,gt1)*TempcplcChaFecSvL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChaFecSvR ## 
ZcplcChaFecSvR = 0._dp 
TempcplcChaFecSvR = cplcChaFecSvR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaFecSvR(gt2,:,:) = ZcplcChaFecSvR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChaFecSvR(gt1,:,:) 
 End Do 
End Do 
TempcplcChaFecSvR = ZcplcChaFecSvR 
ZcplcChaFecSvR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaFecSvR(:,gt2,:) = ZcplcChaFecSvR(:,gt2,:) + ZRUZERc(gt2,gt1)*TempcplcChaFecSvR(:,gt1,:) 
 End Do 
End Do 
TempcplcChaFecSvR = ZcplcChaFecSvR 
ZcplcChaFecSvR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChaFecSvR(:,:,gt2) = ZcplcChaFecSvR(:,:,gt2) + ZRUZVc(gt2,gt1)*TempcplcChaFecSvR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFvFecHpmL ## 
ZcplcFvFecHpmL = 0._dp 
TempcplcFvFecHpmL = cplcFvFecHpmL 
ZcplcFvFecHpmL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFecHpmL(:,gt2,:) = ZcplcFvFecHpmL(:,gt2,:) + ZRUZEL(gt2,gt1)*TempcplcFvFecHpmL(:,gt1,:) 
 End Do 
End Do 
TempcplcFvFecHpmL = ZcplcFvFecHpmL 
ZcplcFvFecHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFvFecHpmL(:,:,gt2) = ZcplcFvFecHpmL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFvFecHpmL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFvFecHpmR ## 
ZcplcFvFecHpmR = 0._dp 
TempcplcFvFecHpmR = cplcFvFecHpmR 
ZcplcFvFecHpmR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFecHpmR(:,gt2,:) = ZcplcFvFecHpmR(:,gt2,:) + ZRUZERc(gt2,gt1)*TempcplcFvFecHpmR(:,gt1,:) 
 End Do 
End Do 
TempcplcFvFecHpmR = ZcplcFvFecHpmR 
ZcplcFvFecHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFvFecHpmR(:,:,gt2) = ZcplcFvFecHpmR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFvFecHpmR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplGluFucSuL ## 
ZcplGluFucSuL = 0._dp 
TempcplGluFucSuL = cplGluFucSuL 
ZcplGluFucSuL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplGluFucSuL(gt2,:) = ZcplGluFucSuL(gt2,:) + ZRUZUL(gt2,gt1)*TempcplGluFucSuL(gt1,:) 
 End Do 
End Do 
TempcplGluFucSuL = ZcplGluFucSuL 
ZcplGluFucSuL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplGluFucSuL(:,gt2) = ZcplGluFucSuL(:,gt2) + ZRUZUc(gt2,gt1)*TempcplGluFucSuL(:,gt1) 
 End Do 
End Do 


 ! ## ZcplGluFucSuR ## 
ZcplGluFucSuR = 0._dp 
TempcplGluFucSuR = cplGluFucSuR 
ZcplGluFucSuR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplGluFucSuR(gt2,:) = ZcplGluFucSuR(gt2,:) + ZRUZURc(gt2,gt1)*TempcplGluFucSuR(gt1,:) 
 End Do 
End Do 
TempcplGluFucSuR = ZcplGluFucSuR 
ZcplGluFucSuR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplGluFucSuR(:,gt2) = ZcplGluFucSuR(:,gt2) + ZRUZUc(gt2,gt1)*TempcplGluFucSuR(:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFuhhL ## 
ZcplcFuFuhhL = 0._dp 
TempcplcFuFuhhL = cplcFuFuhhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhL(gt2,:,:) = ZcplcFuFuhhL(gt2,:,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuhhL(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFuhhL = ZcplcFuFuhhL 
ZcplcFuFuhhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhL(:,gt2,:) = ZcplcFuFuhhL(:,gt2,:) + ZRUZUL(gt2,gt1)*TempcplcFuFuhhL(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFuhhL = ZcplcFuFuhhL 
ZcplcFuFuhhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhL(:,:,gt2) = ZcplcFuFuhhL(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcFuFuhhL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFuhhR ## 
ZcplcFuFuhhR = 0._dp 
TempcplcFuFuhhR = cplcFuFuhhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhR(gt2,:,:) = ZcplcFuFuhhR(gt2,:,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuhhR(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFuhhR = ZcplcFuFuhhR 
ZcplcFuFuhhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhR(:,gt2,:) = ZcplcFuFuhhR(:,gt2,:) + ZRUZURc(gt2,gt1)*TempcplcFuFuhhR(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFuhhR = ZcplcFuFuhhR 
ZcplcFuFuhhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhR(:,:,gt2) = ZcplcFuFuhhR(:,:,gt2) + ZRUZH(gt2,gt1)*TempcplcFuFuhhR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFuHpmL ## 
ZcplcFdFuHpmL = 0._dp 
TempcplcFdFuHpmL = cplcFdFuHpmL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuHpmL(gt2,:,:) = ZcplcFdFuHpmL(gt2,:,:) + ZRUZDR(gt2,gt1)*TempcplcFdFuHpmL(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFuHpmL = ZcplcFdFuHpmL 
ZcplcFdFuHpmL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuHpmL(:,gt2,:) = ZcplcFdFuHpmL(:,gt2,:) + ZRUZUL(gt2,gt1)*TempcplcFdFuHpmL(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFuHpmL = ZcplcFdFuHpmL 
ZcplcFdFuHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFdFuHpmL(:,:,gt2) = ZcplcFdFuHpmL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFdFuHpmL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFuHpmR ## 
ZcplcFdFuHpmR = 0._dp 
TempcplcFdFuHpmR = cplcFdFuHpmR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuHpmR(gt2,:,:) = ZcplcFdFuHpmR(gt2,:,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFuHpmR(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFuHpmR = ZcplcFdFuHpmR 
ZcplcFdFuHpmR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuHpmR(:,gt2,:) = ZcplcFdFuHpmR(:,gt2,:) + ZRUZURc(gt2,gt1)*TempcplcFdFuHpmR(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFuHpmR = ZcplcFdFuHpmR 
ZcplcFdFuHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFdFuHpmR(:,:,gt2) = ZcplcFdFuHpmR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFdFuHpmR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFvHpmL ## 
ZcplcFeFvHpmL = 0._dp 
TempcplcFeFvHpmL = cplcFeFvHpmL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvHpmL(gt2,:,:) = ZcplcFeFvHpmL(gt2,:,:) + ZRUZER(gt2,gt1)*TempcplcFeFvHpmL(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFvHpmL = ZcplcFeFvHpmL 
ZcplcFeFvHpmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFeFvHpmL(:,:,gt2) = ZcplcFeFvHpmL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFeFvHpmL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFvHpmR ## 
ZcplcFeFvHpmR = 0._dp 
TempcplcFeFvHpmR = cplcFeFvHpmR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvHpmR(gt2,:,:) = ZcplcFeFvHpmR(gt2,:,:) + ZRUZELc(gt2,gt1)*TempcplcFeFvHpmR(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFvHpmR = ZcplcFeFvHpmR 
ZcplcFeFvHpmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFeFvHpmR(:,:,gt2) = ZcplcFeFvHpmR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFeFvHpmR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdGluSdL ## 
ZcplcFdGluSdL = 0._dp 
TempcplcFdGluSdL = cplcFdGluSdL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdGluSdL(gt2,:) = ZcplcFdGluSdL(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdGluSdL(gt1,:) 
 End Do 
End Do 
TempcplcFdGluSdL = ZcplcFdGluSdL 
ZcplcFdGluSdL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFdGluSdL(:,gt2) = ZcplcFdGluSdL(:,gt2) + ZRUZD(gt2,gt1)*TempcplcFdGluSdL(:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdGluSdR ## 
ZcplcFdGluSdR = 0._dp 
TempcplcFdGluSdR = cplcFdGluSdR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdGluSdR(gt2,:) = ZcplcFdGluSdR(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdGluSdR(gt1,:) 
 End Do 
End Do 
TempcplcFdGluSdR = ZcplcFdGluSdR 
ZcplcFdGluSdR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFdGluSdR(:,gt2) = ZcplcFdGluSdR(:,gt2) + ZRUZD(gt2,gt1)*TempcplcFdGluSdR(:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuGluSuL ## 
ZcplcFuGluSuL = 0._dp 
TempcplcFuGluSuL = cplcFuGluSuL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuGluSuL(gt2,:) = ZcplcFuGluSuL(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuGluSuL(gt1,:) 
 End Do 
End Do 
TempcplcFuGluSuL = ZcplcFuGluSuL 
ZcplcFuGluSuL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFuGluSuL(:,gt2) = ZcplcFuGluSuL(:,gt2) + ZRUZU(gt2,gt1)*TempcplcFuGluSuL(:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuGluSuR ## 
ZcplcFuGluSuR = 0._dp 
TempcplcFuGluSuR = cplcFuGluSuR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuGluSuR(gt2,:) = ZcplcFuGluSuR(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuGluSuR(gt1,:) 
 End Do 
End Do 
TempcplcFuGluSuR = ZcplcFuGluSuR 
ZcplcFuGluSuR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcFuGluSuR(:,gt2) = ZcplcFuGluSuR(:,gt2) + ZRUZU(gt2,gt1)*TempcplcFuGluSuR(:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChacFuSdL ## 
ZcplcChacFuSdL = 0._dp 
TempcplcChacFuSdL = cplcChacFuSdL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChacFuSdL(gt2,:,:) = ZcplcChacFuSdL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChacFuSdL(gt1,:,:) 
 End Do 
End Do 
TempcplcChacFuSdL = ZcplcChacFuSdL 
ZcplcChacFuSdL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChacFuSdL(:,gt2,:) = ZcplcChacFuSdL(:,gt2,:) + ZRUZUR(gt2,gt1)*TempcplcChacFuSdL(:,gt1,:) 
 End Do 
End Do 
TempcplcChacFuSdL = ZcplcChacFuSdL 
ZcplcChacFuSdL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcChacFuSdL(:,:,gt2) = ZcplcChacFuSdL(:,:,gt2) + ZRUZD(gt2,gt1)*TempcplcChacFuSdL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChacFuSdR ## 
ZcplcChacFuSdR = 0._dp 
TempcplcChacFuSdR = cplcChacFuSdR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChacFuSdR(gt2,:,:) = ZcplcChacFuSdR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChacFuSdR(gt1,:,:) 
 End Do 
End Do 
TempcplcChacFuSdR = ZcplcChacFuSdR 
ZcplcChacFuSdR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcChacFuSdR(:,gt2,:) = ZcplcChacFuSdR(:,gt2,:) + ZRUZULc(gt2,gt1)*TempcplcChacFuSdR(:,gt1,:) 
 End Do 
End Do 
TempcplcChacFuSdR = ZcplcChacFuSdR 
ZcplcChacFuSdR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcChacFuSdR(:,:,gt2) = ZcplcChacFuSdR(:,:,gt2) + ZRUZD(gt2,gt1)*TempcplcChacFuSdR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChacFvSeL ## 
ZcplcChacFvSeL = 0._dp 
TempcplcChacFvSeL = cplcChacFvSeL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChacFvSeL(gt2,:,:) = ZcplcChacFvSeL(gt2,:,:) + ZRUUP(gt2,gt1)*TempcplcChacFvSeL(gt1,:,:) 
 End Do 
End Do 
TempcplcChacFvSeL = ZcplcChacFvSeL 
ZcplcChacFvSeL = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcChacFvSeL(:,:,gt2) = ZcplcChacFvSeL(:,:,gt2) + ZRUZE(gt2,gt1)*TempcplcChacFvSeL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcChacFvSeR ## 
ZcplcChacFvSeR = 0._dp 
TempcplcChacFvSeR = cplcChacFvSeR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChacFvSeR(gt2,:,:) = ZcplcChacFvSeR(gt2,:,:) + ZRUUMc(gt2,gt1)*TempcplcChacFvSeR(gt1,:,:) 
 End Do 
End Do 
TempcplcChacFvSeR = ZcplcChacFvSeR 
ZcplcChacFvSeR = 0._dp 
Do gt1=1,6
  Do gt2=1,6
ZcplcChacFvSeR(:,:,gt2) = ZcplcChacFvSeR(:,:,gt2) + ZRUZE(gt2,gt1)*TempcplcChacFvSeR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplChiChacVWmL ## 
ZcplChiChacVWmL = 0._dp 
TempcplChiChacVWmL = cplChiChacVWmL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChacVWmL(gt2,:) = ZcplChiChacVWmL(gt2,:) + ZRUZNc(gt2,gt1)*TempcplChiChacVWmL(gt1,:) 
 End Do 
End Do 
TempcplChiChacVWmL = ZcplChiChacVWmL 
ZcplChiChacVWmL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplChiChacVWmL(:,gt2) = ZcplChiChacVWmL(:,gt2) + ZRUUM(gt2,gt1)*TempcplChiChacVWmL(:,gt1) 
 End Do 
End Do 
TempcplChiChacVWmL = ZcplChiChacVWmL 


 ! ## ZcplChiChacVWmR ## 
ZcplChiChacVWmR = 0._dp 
TempcplChiChacVWmR = cplChiChacVWmR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChacVWmR(gt2,:) = ZcplChiChacVWmR(gt2,:) + ZRUZN(gt2,gt1)*TempcplChiChacVWmR(gt1,:) 
 End Do 
End Do 
TempcplChiChacVWmR = ZcplChiChacVWmR 
ZcplChiChacVWmR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplChiChacVWmR(:,gt2) = ZcplChiChacVWmR(:,gt2) + ZRUUPc(gt2,gt1)*TempcplChiChacVWmR(:,gt1) 
 End Do 
End Do 
TempcplChiChacVWmR = ZcplChiChacVWmR 


 ! ## ZcplcChaChaVPL ## 
ZcplcChaChaVPL = 0._dp 
TempcplcChaChaVPL = cplcChaChaVPL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVPL(gt2,:) = ZcplcChaChaVPL(gt2,:) + ZRUUMc(gt2,gt1)*TempcplcChaChaVPL(gt1,:) 
 End Do 
End Do 
TempcplcChaChaVPL = ZcplcChaChaVPL 
ZcplcChaChaVPL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVPL(:,gt2) = ZcplcChaChaVPL(:,gt2) + ZRUUM(gt2,gt1)*TempcplcChaChaVPL(:,gt1) 
 End Do 
End Do 
TempcplcChaChaVPL = ZcplcChaChaVPL 


 ! ## ZcplcChaChaVPR ## 
ZcplcChaChaVPR = 0._dp 
TempcplcChaChaVPR = cplcChaChaVPR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVPR(gt2,:) = ZcplcChaChaVPR(gt2,:) + ZRUUP(gt2,gt1)*TempcplcChaChaVPR(gt1,:) 
 End Do 
End Do 
TempcplcChaChaVPR = ZcplcChaChaVPR 
ZcplcChaChaVPR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVPR(:,gt2) = ZcplcChaChaVPR(:,gt2) + ZRUUPc(gt2,gt1)*TempcplcChaChaVPR(:,gt1) 
 End Do 
End Do 
TempcplcChaChaVPR = ZcplcChaChaVPR 


 ! ## ZcplcChaChaVZL ## 
ZcplcChaChaVZL = 0._dp 
TempcplcChaChaVZL = cplcChaChaVZL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVZL(gt2,:) = ZcplcChaChaVZL(gt2,:) + ZRUUMc(gt2,gt1)*TempcplcChaChaVZL(gt1,:) 
 End Do 
End Do 
TempcplcChaChaVZL = ZcplcChaChaVZL 
ZcplcChaChaVZL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVZL(:,gt2) = ZcplcChaChaVZL(:,gt2) + ZRUUM(gt2,gt1)*TempcplcChaChaVZL(:,gt1) 
 End Do 
End Do 
TempcplcChaChaVZL = ZcplcChaChaVZL 


 ! ## ZcplcChaChaVZR ## 
ZcplcChaChaVZR = 0._dp 
TempcplcChaChaVZR = cplcChaChaVZR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVZR(gt2,:) = ZcplcChaChaVZR(gt2,:) + ZRUUP(gt2,gt1)*TempcplcChaChaVZR(gt1,:) 
 End Do 
End Do 
TempcplcChaChaVZR = ZcplcChaChaVZR 
ZcplcChaChaVZR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChaVZR(:,gt2) = ZcplcChaChaVZR(:,gt2) + ZRUUPc(gt2,gt1)*TempcplcChaChaVZR(:,gt1) 
 End Do 
End Do 
TempcplcChaChaVZR = ZcplcChaChaVZR 


 ! ## ZcplChiChiVZL ## 
ZcplChiChiVZL = 0._dp 
TempcplChiChiVZL = cplChiChiVZL 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiVZL(gt2,:) = ZcplChiChiVZL(gt2,:) + ZRUZNc(gt2,gt1)*TempcplChiChiVZL(gt1,:) 
 End Do 
End Do 
TempcplChiChiVZL = ZcplChiChiVZL 
ZcplChiChiVZL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiVZL(:,gt2) = ZcplChiChiVZL(:,gt2) + ZRUZN(gt2,gt1)*TempcplChiChiVZL(:,gt1) 
 End Do 
End Do 
TempcplChiChiVZL = ZcplChiChiVZL 


 ! ## ZcplChiChiVZR ## 
ZcplChiChiVZR = 0._dp 
TempcplChiChiVZR = cplChiChiVZR 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiVZR(gt2,:) = ZcplChiChiVZR(gt2,:) + ZRUZN(gt2,gt1)*TempcplChiChiVZR(gt1,:) 
 End Do 
End Do 
TempcplChiChiVZR = ZcplChiChiVZR 
ZcplChiChiVZR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplChiChiVZR(:,gt2) = ZcplChiChiVZR(:,gt2) + ZRUZNc(gt2,gt1)*TempcplChiChiVZR(:,gt1) 
 End Do 
End Do 
TempcplChiChiVZR = ZcplChiChiVZR 


 ! ## ZcplcChaChiVWmL ## 
ZcplcChaChiVWmL = 0._dp 
TempcplcChaChiVWmL = cplcChaChiVWmL 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChiVWmL(gt2,:) = ZcplcChaChiVWmL(gt2,:) + ZRUUMc(gt2,gt1)*TempcplcChaChiVWmL(gt1,:) 
 End Do 
End Do 
TempcplcChaChiVWmL = ZcplcChaChiVWmL 
ZcplcChaChiVWmL = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcChaChiVWmL(:,gt2) = ZcplcChaChiVWmL(:,gt2) + ZRUZN(gt2,gt1)*TempcplcChaChiVWmL(:,gt1) 
 End Do 
End Do 
TempcplcChaChiVWmL = ZcplcChaChiVWmL 


 ! ## ZcplcChaChiVWmR ## 
ZcplcChaChiVWmR = 0._dp 
TempcplcChaChiVWmR = cplcChaChiVWmR 
Do gt1=1,2
  Do gt2=1,2
ZcplcChaChiVWmR(gt2,:) = ZcplcChaChiVWmR(gt2,:) + ZRUUP(gt2,gt1)*TempcplcChaChiVWmR(gt1,:) 
 End Do 
End Do 
TempcplcChaChiVWmR = ZcplcChaChiVWmR 
ZcplcChaChiVWmR = 0._dp 
Do gt1=1,5
  Do gt2=1,5
ZcplcChaChiVWmR(:,gt2) = ZcplcChaChiVWmR(:,gt2) + ZRUZNc(gt2,gt1)*TempcplcChaChiVWmR(:,gt1) 
 End Do 
End Do 
TempcplcChaChiVWmR = ZcplcChaChiVWmR 


 ! ## ZcplcFdFdVGL ## 
ZcplcFdFdVGL = 0._dp 
TempcplcFdFdVGL = cplcFdFdVGL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGL(gt2,:) = ZcplcFdFdVGL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdVGL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVGL = ZcplcFdFdVGL 
ZcplcFdFdVGL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGL(:,gt2) = ZcplcFdFdVGL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdVGL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVGL = ZcplcFdFdVGL 


 ! ## ZcplcFdFdVGR ## 
ZcplcFdFdVGR = 0._dp 
TempcplcFdFdVGR = cplcFdFdVGR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGR(gt2,:) = ZcplcFdFdVGR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdVGR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVGR = ZcplcFdFdVGR 
ZcplcFdFdVGR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGR(:,gt2) = ZcplcFdFdVGR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdVGR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVGR = ZcplcFdFdVGR 


 ! ## ZcplcFdFdVPL ## 
ZcplcFdFdVPL = 0._dp 
TempcplcFdFdVPL = cplcFdFdVPL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPL(gt2,:) = ZcplcFdFdVPL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdVPL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVPL = ZcplcFdFdVPL 
ZcplcFdFdVPL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPL(:,gt2) = ZcplcFdFdVPL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdVPL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVPL = ZcplcFdFdVPL 


 ! ## ZcplcFdFdVPR ## 
ZcplcFdFdVPR = 0._dp 
TempcplcFdFdVPR = cplcFdFdVPR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPR(gt2,:) = ZcplcFdFdVPR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdVPR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVPR = ZcplcFdFdVPR 
ZcplcFdFdVPR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPR(:,gt2) = ZcplcFdFdVPR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdVPR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVPR = ZcplcFdFdVPR 


 ! ## ZcplcFdFdVZL ## 
ZcplcFdFdVZL = 0._dp 
TempcplcFdFdVZL = cplcFdFdVZL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZL(gt2,:) = ZcplcFdFdVZL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdVZL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVZL = ZcplcFdFdVZL 
ZcplcFdFdVZL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZL(:,gt2) = ZcplcFdFdVZL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdVZL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVZL = ZcplcFdFdVZL 


 ! ## ZcplcFdFdVZR ## 
ZcplcFdFdVZR = 0._dp 
TempcplcFdFdVZR = cplcFdFdVZR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZR(gt2,:) = ZcplcFdFdVZR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdVZR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVZR = ZcplcFdFdVZR 
ZcplcFdFdVZR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZR(:,gt2) = ZcplcFdFdVZR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdVZR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVZR = ZcplcFdFdVZR 


 ! ## ZcplcFuFdcVWmL ## 
ZcplcFuFdcVWmL = 0._dp 
TempcplcFuFdcVWmL = cplcFuFdcVWmL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcVWmL(gt2,:) = ZcplcFuFdcVWmL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFdcVWmL(gt1,:) 
 End Do 
End Do 
TempcplcFuFdcVWmL = ZcplcFuFdcVWmL 
ZcplcFuFdcVWmL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcVWmL(:,gt2) = ZcplcFuFdcVWmL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFuFdcVWmL(:,gt1) 
 End Do 
End Do 
TempcplcFuFdcVWmL = ZcplcFuFdcVWmL 


 ! ## ZcplcFuFdcVWmR ## 
ZcplcFuFdcVWmR = 0._dp 
TempcplcFuFdcVWmR = cplcFuFdcVWmR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcVWmR(gt2,:) = ZcplcFuFdcVWmR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFdcVWmR(gt1,:) 
 End Do 
End Do 
TempcplcFuFdcVWmR = ZcplcFuFdcVWmR 
ZcplcFuFdcVWmR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdcVWmR(:,gt2) = ZcplcFuFdcVWmR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFuFdcVWmR(:,gt1) 
 End Do 
End Do 
TempcplcFuFdcVWmR = ZcplcFuFdcVWmR 


 ! ## ZcplcFeFeVPL ## 
ZcplcFeFeVPL = 0._dp 
TempcplcFeFeVPL = cplcFeFeVPL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPL(gt2,:) = ZcplcFeFeVPL(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFeVPL(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVPL = ZcplcFeFeVPL 
ZcplcFeFeVPL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPL(:,gt2) = ZcplcFeFeVPL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFeFeVPL(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVPL = ZcplcFeFeVPL 


 ! ## ZcplcFeFeVPR ## 
ZcplcFeFeVPR = 0._dp 
TempcplcFeFeVPR = cplcFeFeVPR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPR(gt2,:) = ZcplcFeFeVPR(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFeVPR(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVPR = ZcplcFeFeVPR 
ZcplcFeFeVPR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPR(:,gt2) = ZcplcFeFeVPR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFeFeVPR(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVPR = ZcplcFeFeVPR 


 ! ## ZcplcFeFeVZL ## 
ZcplcFeFeVZL = 0._dp 
TempcplcFeFeVZL = cplcFeFeVZL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZL(gt2,:) = ZcplcFeFeVZL(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFeVZL(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVZL = ZcplcFeFeVZL 
ZcplcFeFeVZL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZL(:,gt2) = ZcplcFeFeVZL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFeFeVZL(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVZL = ZcplcFeFeVZL 


 ! ## ZcplcFeFeVZR ## 
ZcplcFeFeVZR = 0._dp 
TempcplcFeFeVZR = cplcFeFeVZR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZR(gt2,:) = ZcplcFeFeVZR(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFeVZR(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVZR = ZcplcFeFeVZR 
ZcplcFeFeVZR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZR(:,gt2) = ZcplcFeFeVZR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFeFeVZR(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVZR = ZcplcFeFeVZR 


 ! ## ZcplcFvFecVWmL ## 
ZcplcFvFecVWmL = 0._dp 
TempcplcFvFecVWmL = cplcFvFecVWmL 
ZcplcFvFecVWmL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFecVWmL(:,gt2) = ZcplcFvFecVWmL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFvFecVWmL(:,gt1) 
 End Do 
End Do 
TempcplcFvFecVWmL = ZcplcFvFecVWmL 


 ! ## ZcplcFvFecVWmR ## 
ZcplcFvFecVWmR = 0._dp 
TempcplcFvFecVWmR = cplcFvFecVWmR 
ZcplcFvFecVWmR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFecVWmR(:,gt2) = ZcplcFvFecVWmR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFvFecVWmR(:,gt1) 
 End Do 
End Do 
TempcplcFvFecVWmR = ZcplcFvFecVWmR 


 ! ## ZcplcFuFuVGL ## 
ZcplcFuFuVGL = 0._dp 
TempcplcFuFuVGL = cplcFuFuVGL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGL(gt2,:) = ZcplcFuFuVGL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuVGL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVGL = ZcplcFuFuVGL 
ZcplcFuFuVGL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGL(:,gt2) = ZcplcFuFuVGL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuVGL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVGL = ZcplcFuFuVGL 


 ! ## ZcplcFuFuVGR ## 
ZcplcFuFuVGR = 0._dp 
TempcplcFuFuVGR = cplcFuFuVGR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGR(gt2,:) = ZcplcFuFuVGR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuVGR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVGR = ZcplcFuFuVGR 
ZcplcFuFuVGR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGR(:,gt2) = ZcplcFuFuVGR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuVGR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVGR = ZcplcFuFuVGR 


 ! ## ZcplcFuFuVPL ## 
ZcplcFuFuVPL = 0._dp 
TempcplcFuFuVPL = cplcFuFuVPL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPL(gt2,:) = ZcplcFuFuVPL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuVPL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVPL = ZcplcFuFuVPL 
ZcplcFuFuVPL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPL(:,gt2) = ZcplcFuFuVPL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuVPL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVPL = ZcplcFuFuVPL 


 ! ## ZcplcFuFuVPR ## 
ZcplcFuFuVPR = 0._dp 
TempcplcFuFuVPR = cplcFuFuVPR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPR(gt2,:) = ZcplcFuFuVPR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuVPR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVPR = ZcplcFuFuVPR 
ZcplcFuFuVPR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPR(:,gt2) = ZcplcFuFuVPR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuVPR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVPR = ZcplcFuFuVPR 


 ! ## ZcplcFdFuVWmL ## 
ZcplcFdFuVWmL = 0._dp 
TempcplcFdFuVWmL = cplcFdFuVWmL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuVWmL(gt2,:) = ZcplcFdFuVWmL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFuVWmL(gt1,:) 
 End Do 
End Do 
TempcplcFdFuVWmL = ZcplcFdFuVWmL 
ZcplcFdFuVWmL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuVWmL(:,gt2) = ZcplcFdFuVWmL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFdFuVWmL(:,gt1) 
 End Do 
End Do 
TempcplcFdFuVWmL = ZcplcFdFuVWmL 


 ! ## ZcplcFdFuVWmR ## 
ZcplcFdFuVWmR = 0._dp 
TempcplcFdFuVWmR = cplcFdFuVWmR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuVWmR(gt2,:) = ZcplcFdFuVWmR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFuVWmR(gt1,:) 
 End Do 
End Do 
TempcplcFdFuVWmR = ZcplcFdFuVWmR 
ZcplcFdFuVWmR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFuVWmR(:,gt2) = ZcplcFdFuVWmR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFdFuVWmR(:,gt1) 
 End Do 
End Do 
TempcplcFdFuVWmR = ZcplcFdFuVWmR 


 ! ## ZcplcFuFuVZL ## 
ZcplcFuFuVZL = 0._dp 
TempcplcFuFuVZL = cplcFuFuVZL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZL(gt2,:) = ZcplcFuFuVZL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuVZL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVZL = ZcplcFuFuVZL 
ZcplcFuFuVZL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZL(:,gt2) = ZcplcFuFuVZL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuVZL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVZL = ZcplcFuFuVZL 


 ! ## ZcplcFuFuVZR ## 
ZcplcFuFuVZR = 0._dp 
TempcplcFuFuVZR = cplcFuFuVZR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZR(gt2,:) = ZcplcFuFuVZR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuVZR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVZR = ZcplcFuFuVZR 
ZcplcFuFuVZR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZR(:,gt2) = ZcplcFuFuVZR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuVZR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVZR = ZcplcFuFuVZR 


 ! ## ZcplcFeFvVWmL ## 
ZcplcFeFvVWmL = 0._dp 
TempcplcFeFvVWmL = cplcFeFvVWmL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvVWmL(gt2,:) = ZcplcFeFvVWmL(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFvVWmL(gt1,:) 
 End Do 
End Do 
TempcplcFeFvVWmL = ZcplcFeFvVWmL 


 ! ## ZcplcFeFvVWmR ## 
ZcplcFeFvVWmR = 0._dp 
TempcplcFeFvVWmR = cplcFeFvVWmR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvVWmR(gt2,:) = ZcplcFeFvVWmR(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFvVWmR(gt1,:) 
 End Do 
End Do 
TempcplcFeFvVWmR = ZcplcFeFvVWmR 


 ! ## ZcplcFvFvVZL ## 
ZcplcFvFvVZL = 0._dp 
TempcplcFvFvVZL = cplcFvFvVZL 


 ! ## ZcplcFvFvVZR ## 
ZcplcFvFvVZR = 0._dp 
TempcplcFvFvVZR = cplcFvFvVZR 


 ! ## ZcplGluGluVGL ## 
ZcplGluGluVGL = 0._dp 
TempcplGluGluVGL = cplGluGluVGL 
ZcplGluGluVGL = TempcplGluGluVGL 


 ! ## ZcplGluGluVGR ## 
ZcplGluGluVGR = 0._dp 
TempcplGluGluVGR = cplGluGluVGR 
ZcplGluGluVGR = TempcplGluGluVGR 


 ! ## ZcplVGVGVGVG1 ## 
ZcplVGVGVGVG1 = 0._dp 


 ! ## ZcplVGVGVGVG2 ## 
ZcplVGVGVGVG2 = 0._dp 


 ! ## ZcplVGVGVGVG3 ## 
ZcplVGVGVGVG3 = 0._dp 


 ! ## ZcplcVWmVPVPVWm1 ## 
ZcplcVWmVPVPVWm1 = 0._dp 


 ! ## ZcplcVWmVPVPVWm2 ## 
ZcplcVWmVPVPVWm2 = 0._dp 


 ! ## ZcplcVWmVPVPVWm3 ## 
ZcplcVWmVPVPVWm3 = 0._dp 


 ! ## ZcplcVWmVPVWmVZ1 ## 
ZcplcVWmVPVWmVZ1 = 0._dp 


 ! ## ZcplcVWmVPVWmVZ2 ## 
ZcplcVWmVPVWmVZ2 = 0._dp 


 ! ## ZcplcVWmVPVWmVZ3 ## 
ZcplcVWmVPVWmVZ3 = 0._dp 


 ! ## ZcplcVWmcVWmVWmVWm1 ## 
ZcplcVWmcVWmVWmVWm1 = 0._dp 


 ! ## ZcplcVWmcVWmVWmVWm2 ## 
ZcplcVWmcVWmVWmVWm2 = 0._dp 


 ! ## ZcplcVWmcVWmVWmVWm3 ## 
ZcplcVWmcVWmVWmVWm3 = 0._dp 


 ! ## ZcplcVWmVWmVZVZ1 ## 
ZcplcVWmVWmVZVZ1 = 0._dp 


 ! ## ZcplcVWmVWmVZVZ2 ## 
ZcplcVWmVWmVZVZ2 = 0._dp 


 ! ## ZcplcVWmVWmVZVZ3 ## 
ZcplcVWmVWmVZVZ3 = 0._dp 


 ! ## ZcplcgGgGVG ## 
ZcplcgGgGVG = 0._dp 
TempcplcgGgGVG = cplcgGgGVG 
ZcplcgGgGVG = TempcplcgGgGVG 


 ! ## ZcplcgWmgAVWm ## 
ZcplcgWmgAVWm = 0._dp 
TempcplcgWmgAVWm = cplcgWmgAVWm 
ZcplcgWmgAVWm = TempcplcgWmgAVWm 


 ! ## ZcplcgWpCgAcVWm ## 
ZcplcgWpCgAcVWm = 0._dp 
TempcplcgWpCgAcVWm = cplcgWpCgAcVWm 
ZcplcgWpCgAcVWm = TempcplcgWpCgAcVWm 


 ! ## ZcplcgWmgWmVP ## 
ZcplcgWmgWmVP = 0._dp 
TempcplcgWmgWmVP = cplcgWmgWmVP 
ZcplcgWmgWmVP = TempcplcgWmgWmVP 


 ! ## ZcplcgWmgWmVZ ## 
ZcplcgWmgWmVZ = 0._dp 
TempcplcgWmgWmVZ = cplcgWmgWmVZ 
ZcplcgWmgWmVZ = TempcplcgWmgWmVZ 


 ! ## ZcplcgAgWmcVWm ## 
ZcplcgAgWmcVWm = 0._dp 
TempcplcgAgWmcVWm = cplcgAgWmcVWm 
ZcplcgAgWmcVWm = TempcplcgAgWmcVWm 


 ! ## ZcplcgZgWmcVWm ## 
ZcplcgZgWmcVWm = 0._dp 
TempcplcgZgWmcVWm = cplcgZgWmcVWm 
ZcplcgZgWmcVWm = TempcplcgZgWmcVWm 


 ! ## ZcplcgWpCgWpCVP ## 
ZcplcgWpCgWpCVP = 0._dp 
TempcplcgWpCgWpCVP = cplcgWpCgWpCVP 
ZcplcgWpCgWpCVP = TempcplcgWpCgWpCVP 


 ! ## ZcplcgAgWpCVWm ## 
ZcplcgAgWpCVWm = 0._dp 
TempcplcgAgWpCVWm = cplcgAgWpCVWm 
ZcplcgAgWpCVWm = TempcplcgAgWpCVWm 


 ! ## ZcplcgZgWpCVWm ## 
ZcplcgZgWpCVWm = 0._dp 
TempcplcgZgWpCVWm = cplcgZgWpCVWm 
ZcplcgZgWpCVWm = TempcplcgZgWpCVWm 


 ! ## ZcplcgWpCgWpCVZ ## 
ZcplcgWpCgWpCVZ = 0._dp 
TempcplcgWpCgWpCVZ = cplcgWpCgWpCVZ 
ZcplcgWpCgWpCVZ = TempcplcgWpCgWpCVZ 


 ! ## ZcplcgWmgZVWm ## 
ZcplcgWmgZVWm = 0._dp 
TempcplcgWmgZVWm = cplcgWmgZVWm 
ZcplcgWmgZVWm = TempcplcgWmgZVWm 


 ! ## ZcplcgWpCgZcVWm ## 
ZcplcgWpCgZcVWm = 0._dp 
TempcplcgWpCgZcVWm = cplcgWpCgZcVWm 
ZcplcgWpCgZcVWm = TempcplcgWpCgZcVWm 


 ! ## ZcplcgWmgWmAh ## 
ZcplcgWmgWmAh = 0._dp 
TempcplcgWmgWmAh = cplcgWmgWmAh 
ZcplcgWmgWmAh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcgWmgWmAh(gt2) = ZcplcgWmgWmAh(gt2) + ZRUZA(gt2,gt1)*TempcplcgWmgWmAh(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWpCgWpCAh ## 
ZcplcgWpCgWpCAh = 0._dp 
TempcplcgWpCgWpCAh = cplcgWpCgWpCAh 
ZcplcgWpCgWpCAh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcgWpCgWpCAh(gt2) = ZcplcgWpCgWpCAh(gt2) + ZRUZA(gt2,gt1)*TempcplcgWpCgWpCAh(gt1) 
 End Do 
End Do 


 ! ## ZcplcgZgAhh ## 
ZcplcgZgAhh = 0._dp 
TempcplcgZgAhh = cplcgZgAhh 
ZcplcgZgAhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcgZgAhh(gt2) = ZcplcgZgAhh(gt2) + ZRUZH(gt2,gt1)*TempcplcgZgAhh(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWmgAHpm ## 
ZcplcgWmgAHpm = 0._dp 
TempcplcgWmgAHpm = cplcgWmgAHpm 
ZcplcgWmgAHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWmgAHpm(gt2) = ZcplcgWmgAHpm(gt2) + ZRUZP(gt2,gt1)*TempcplcgWmgAHpm(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWpCgAcHpm ## 
ZcplcgWpCgAcHpm = 0._dp 
TempcplcgWpCgAcHpm = cplcgWpCgAcHpm 
ZcplcgWpCgAcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWpCgAcHpm(gt2) = ZcplcgWpCgAcHpm(gt2) + ZRUZP(gt2,gt1)*TempcplcgWpCgAcHpm(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWmgWmhh ## 
ZcplcgWmgWmhh = 0._dp 
TempcplcgWmgWmhh = cplcgWmgWmhh 
ZcplcgWmgWmhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcgWmgWmhh(gt2) = ZcplcgWmgWmhh(gt2) + ZRUZH(gt2,gt1)*TempcplcgWmgWmhh(gt1) 
 End Do 
End Do 


 ! ## ZcplcgZgWmcHpm ## 
ZcplcgZgWmcHpm = 0._dp 
TempcplcgZgWmcHpm = cplcgZgWmcHpm 
ZcplcgZgWmcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgZgWmcHpm(gt2) = ZcplcgZgWmcHpm(gt2) + ZRUZP(gt2,gt1)*TempcplcgZgWmcHpm(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWpCgWpChh ## 
ZcplcgWpCgWpChh = 0._dp 
TempcplcgWpCgWpChh = cplcgWpCgWpChh 
ZcplcgWpCgWpChh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcgWpCgWpChh(gt2) = ZcplcgWpCgWpChh(gt2) + ZRUZH(gt2,gt1)*TempcplcgWpCgWpChh(gt1) 
 End Do 
End Do 


 ! ## ZcplcgZgWpCHpm ## 
ZcplcgZgWpCHpm = 0._dp 
TempcplcgZgWpCHpm = cplcgZgWpCHpm 
ZcplcgZgWpCHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgZgWpCHpm(gt2) = ZcplcgZgWpCHpm(gt2) + ZRUZP(gt2,gt1)*TempcplcgZgWpCHpm(gt1) 
 End Do 
End Do 


 ! ## ZcplcgZgZhh ## 
ZcplcgZgZhh = 0._dp 
TempcplcgZgZhh = cplcgZgZhh 
ZcplcgZgZhh = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcgZgZhh(gt2) = ZcplcgZgZhh(gt2) + ZRUZH(gt2,gt1)*TempcplcgZgZhh(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWmgZHpm ## 
ZcplcgWmgZHpm = 0._dp 
TempcplcgWmgZHpm = cplcgWmgZHpm 
ZcplcgWmgZHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWmgZHpm(gt2) = ZcplcgWmgZHpm(gt2) + ZRUZP(gt2,gt1)*TempcplcgWmgZHpm(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWpCgZcHpm ## 
ZcplcgWpCgZcHpm = 0._dp 
TempcplcgWpCgZcHpm = cplcgWpCgZcHpm 
ZcplcgWpCgZcHpm = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWpCgZcHpm(gt2) = ZcplcgWpCgZcHpm(gt2) + ZRUZP(gt2,gt1)*TempcplcgWpCgZcHpm(gt1) 
 End Do 
End Do 
End Subroutine  getZCouplings 

Subroutine getGBCouplings(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,               & 
& MSe2OS,MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,         & 
& MFeOS,MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,             & 
& MVWm2OS,ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,           & 
& ZDROS,ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,cplAhcHpmVWm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,cplcFdFuVWmR,   & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,     & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplSdcSucVWm,cplSecSvcVWm,cplSucSdVWm,cplSvcSeVWm,           & 
& ZcplAhcHpmVWm,ZcplcChaChiVWmL,ZcplcChaChiVWmR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,             & 
& ZcplcFeFvVWmL,ZcplcFeFvVWmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFvFecVWmL,              & 
& ZcplcFvFecVWmR,ZcplChiChacVWmL,ZcplChiChacVWmR,ZcplcHpmVPVWm,ZcplcHpmVWmVZ,            & 
& ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplhhcHpmVWm,ZcplhhcVWmVWm,ZcplSdcSucVWm,ZcplSecSvcVWm,   & 
& ZcplSucSdVWm,ZcplSvcSeVWm,GcplAhHpmcHpm,GcplhhHpmcHpm,GcplHpmSucSd,GcplHpmSvcSe,       & 
& GcplSdcHpmcSu,GcplSecHpmcSv,GcplAhHpmcVWm,GcplAhcHpmVWm,GcplhhHpmcVWm,GcplhhcHpmVWm,   & 
& GcplHpmcHpmVP,GcplHpmcHpmVZ,GcplHpmcVWmVP,GcplHpmcVWmVZ,GcplcHpmVPVWm,GcplcHpmVWmVZ,   & 
& GcplChiChacHpmL,GcplChiChacHpmR,GcplcChaChiHpmL,GcplcChaChiHpmR,GcplcFuFdcHpmL,        & 
& GcplcFuFdcHpmR,GcplcFvFecHpmL,GcplcFvFecHpmR,GcplcFdFuHpmL,GcplcFdFuHpmR,              & 
& GcplcFeFvHpmL,GcplcFeFvHpmR,GZcplAhHpmcHpm,GZcplhhHpmcHpm,GZcplHpmSucSd,               & 
& GZcplHpmSvcSe,GZcplSdcHpmcSu,GZcplSecHpmcSv,GZcplAhHpmcVWm,GZcplAhcHpmVWm,             & 
& GZcplhhHpmcVWm,GZcplhhcHpmVWm,GZcplHpmcHpmVP,GZcplHpmcHpmVZ,GZcplHpmcVWmVP,            & 
& GZcplHpmcVWmVZ,GZcplcHpmVPVWm,GZcplcHpmVWmVZ,GZcplChiChacHpmL,GZcplChiChacHpmR,        & 
& GZcplcChaChiHpmL,GZcplcChaChiHpmR,GZcplcFuFdcHpmL,GZcplcFuFdcHpmR,GZcplcFvFecHpmL,     & 
& GZcplcFvFecHpmR,GZcplcFdFuHpmL,GZcplcFdFuHpmR,GZcplcFeFvHpmL,GZcplcFeFvHpmR,           & 
& GosZcplAhHpmcHpm,GosZcplhhHpmcHpm,GosZcplHpmSucSd,GosZcplHpmSvcSe,GosZcplSdcHpmcSu,    & 
& GosZcplSecHpmcSv,GosZcplAhHpmcVWm,GosZcplAhcHpmVWm,GosZcplhhHpmcVWm,GosZcplhhcHpmVWm,  & 
& GosZcplHpmcHpmVP,GosZcplHpmcHpmVZ,GosZcplHpmcVWmVP,GosZcplHpmcVWmVZ,GosZcplcHpmVPVWm,  & 
& GosZcplcHpmVWmVZ,GosZcplChiChacHpmL,GosZcplChiChacHpmR,GosZcplcChaChiHpmL,             & 
& GosZcplcChaChiHpmR,GosZcplcFuFdcHpmL,GosZcplcFuFdcHpmR,GosZcplcFvFecHpmL,              & 
& GosZcplcFvFecHpmR,GosZcplcFdFuHpmL,GosZcplcFdFuHpmR,GosZcplcFeFvHpmL,GosZcplcFeFvHpmR)

Implicit None

Real(dp), Intent(in) :: MSdOS(6),MSd2OS(6),MSvOS(3),MSv2OS(3),MSuOS(6),MSu2OS(6),MSeOS(6),MSe2OS(6),          & 
& MhhOS(3),Mhh2OS(3),MAhOS(3),MAh2OS(3),MHpmOS(2),MHpm2OS(2),MChiOS(5),MChi2OS(5),       & 
& MChaOS(2),MCha2OS(2),MFeOS(3),MFe2OS(3),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),         & 
& MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(3,3),ZAOS(3,3),ZPOS(2,2)

Complex(dp), Intent(in) :: ZDOS(6,6),ZVOS(3,3),ZUOS(6,6),ZEOS(6,6),ZNOS(5,5),UMOS(2,2),UPOS(2,2),ZELOS(3,3),     & 
& ZEROS(3,3),ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3)

Real(dp), Intent(in) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp), Intent(in) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp), Intent(in) :: cplAhcHpmVWm(3,2),cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),cplcFdFuVWmL(3,3),          & 
& cplcFdFuVWmR(3,3),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFuFdcVWmL(3,3),              & 
& cplcFuFdcVWmR(3,3),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplChiChacVWmL(5,2),          & 
& cplChiChacVWmR(5,2),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,         & 
& cplhhcHpmVWm(3,2),cplhhcVWmVWm(3),cplSdcSucVWm(6,6),cplSecSvcVWm(6,3),cplSucSdVWm(6,6),& 
& cplSvcSeVWm(3,6),ZcplAhcHpmVWm(3,2),ZcplcChaChiVWmL(2,5),ZcplcChaChiVWmR(2,5),         & 
& ZcplcFdFuVWmL(3,3),ZcplcFdFuVWmR(3,3),ZcplcFeFvVWmL(3,3),ZcplcFeFvVWmR(3,3),           & 
& ZcplcFuFdcVWmL(3,3),ZcplcFuFdcVWmR(3,3),ZcplcFvFecVWmL(3,3),ZcplcFvFecVWmR(3,3),       & 
& ZcplChiChacVWmL(5,2),ZcplChiChacVWmR(5,2),ZcplcHpmVPVWm(2),ZcplcHpmVWmVZ(2),           & 
& ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplhhcHpmVWm(3,2),ZcplhhcVWmVWm(3),ZcplSdcSucVWm(6,6),    & 
& ZcplSecSvcVWm(6,3),ZcplSucSdVWm(6,6),ZcplSvcSeVWm(3,6)

Integer :: gt1, gt2, gt3, i1, i2
Complex(dp), Intent(out) :: GcplAhHpmcHpm(3,2,2),GcplhhHpmcHpm(3,2,2),GcplHpmSucSd(2,6,6),GcplHpmSvcSe(2,3,6),    & 
& GcplSdcHpmcSu(6,2,6),GcplSecHpmcSv(6,2,3),GcplAhHpmcVWm(3,2),GcplAhcHpmVWm(3,2),       & 
& GcplhhHpmcVWm(3,2),GcplhhcHpmVWm(3,2),GcplHpmcHpmVP(2,2),GcplHpmcHpmVZ(2,2),           & 
& GcplHpmcVWmVP(2),GcplHpmcVWmVZ(2),GcplcHpmVPVWm(2),GcplcHpmVWmVZ(2),GcplChiChacHpmL(5,2,2),& 
& GcplChiChacHpmR(5,2,2),GcplcChaChiHpmL(2,5,2),GcplcChaChiHpmR(2,5,2),GcplcFuFdcHpmL(3,3,2),& 
& GcplcFuFdcHpmR(3,3,2),GcplcFvFecHpmL(3,3,2),GcplcFvFecHpmR(3,3,2),GcplcFdFuHpmL(3,3,2),& 
& GcplcFdFuHpmR(3,3,2),GcplcFeFvHpmL(3,3,2),GcplcFeFvHpmR(3,3,2)

Complex(dp), Intent(out) :: GZcplAhHpmcHpm(3,2,2),GZcplhhHpmcHpm(3,2,2),GZcplHpmSucSd(2,6,6),GZcplHpmSvcSe(2,3,6),& 
& GZcplSdcHpmcSu(6,2,6),GZcplSecHpmcSv(6,2,3),GZcplAhHpmcVWm(3,2),GZcplAhcHpmVWm(3,2),   & 
& GZcplhhHpmcVWm(3,2),GZcplhhcHpmVWm(3,2),GZcplHpmcHpmVP(2,2),GZcplHpmcHpmVZ(2,2),       & 
& GZcplHpmcVWmVP(2),GZcplHpmcVWmVZ(2),GZcplcHpmVPVWm(2),GZcplcHpmVWmVZ(2),               & 
& GZcplChiChacHpmL(5,2,2),GZcplChiChacHpmR(5,2,2),GZcplcChaChiHpmL(2,5,2),               & 
& GZcplcChaChiHpmR(2,5,2),GZcplcFuFdcHpmL(3,3,2),GZcplcFuFdcHpmR(3,3,2),GZcplcFvFecHpmL(3,3,2),& 
& GZcplcFvFecHpmR(3,3,2),GZcplcFdFuHpmL(3,3,2),GZcplcFdFuHpmR(3,3,2),GZcplcFeFvHpmL(3,3,2),& 
& GZcplcFeFvHpmR(3,3,2)

Complex(dp), Intent(out) :: GosZcplAhHpmcHpm(3,2,2),GosZcplhhHpmcHpm(3,2,2),GosZcplHpmSucSd(2,6,6),               & 
& GosZcplHpmSvcSe(2,3,6),GosZcplSdcHpmcSu(6,2,6),GosZcplSecHpmcSv(6,2,3),GosZcplAhHpmcVWm(3,2),& 
& GosZcplAhcHpmVWm(3,2),GosZcplhhHpmcVWm(3,2),GosZcplhhcHpmVWm(3,2),GosZcplHpmcHpmVP(2,2),& 
& GosZcplHpmcHpmVZ(2,2),GosZcplHpmcVWmVP(2),GosZcplHpmcVWmVZ(2),GosZcplcHpmVPVWm(2),     & 
& GosZcplcHpmVWmVZ(2),GosZcplChiChacHpmL(5,2,2),GosZcplChiChacHpmR(5,2,2),               & 
& GosZcplcChaChiHpmL(2,5,2),GosZcplcChaChiHpmR(2,5,2),GosZcplcFuFdcHpmL(3,3,2),          & 
& GosZcplcFuFdcHpmR(3,3,2),GosZcplcFvFecHpmL(3,3,2),GosZcplcFvFecHpmR(3,3,2),            & 
& GosZcplcFdFuHpmL(3,3,2),GosZcplcFdFuHpmR(3,3,2),GosZcplcFeFvHpmL(3,3,2),               & 
& GosZcplcFeFvHpmR(3,3,2)

Do i1=1,3
 Do i2=1,2
GcplAhHpmcHpm(i1,1,i2) = (1)*(MAh2OS(i1) - MHpm2OS(i2))/MVWmOS*cplAhcHpmVWm(i1,i2)
GosZcplAhHpmcHpm(i1,1,i2) = (1)*(MAh2OS(i1) - MHpm2OS(i2))/MVWmOS*ZcplAhcHpmVWm(i1,i2)
GZcplAhHpmcHpm(i1,1,i2) = (1)*(MAh2(i1) - MHpm2(i2))/MVWm*ZcplAhcHpmVWm(i1,i2)
 End Do
End Do 
Do i1=1,3
 Do i2=1,2
GcplhhHpmcHpm(i1,1,i2) = (1)*(Mhh2OS(i1) - MHpm2OS(i2))/MVWmOS*cplhhcHpmVWm(i1,i2)
GosZcplhhHpmcHpm(i1,1,i2) = (1)*(Mhh2OS(i1) - MHpm2OS(i2))/MVWmOS*ZcplhhcHpmVWm(i1,i2)
GZcplhhHpmcHpm(i1,1,i2) = (1)*(Mhh2(i1) - MHpm2(i2))/MVWm*ZcplhhcHpmVWm(i1,i2)
 End Do
End Do 
Do i1=1,6
 Do i2=1,6
GcplHpmSucSd(1,i1,i2) = (1)*(MSu2OS(i1) - MSd2OS(i2))/MVWmOS*cplSucSdVWm(i1,i2)
GosZcplHpmSucSd(1,i1,i2) = (1)*(MSu2OS(i1) - MSd2OS(i2))/MVWmOS*ZcplSucSdVWm(i1,i2)
GZcplHpmSucSd(1,i1,i2) = (1)*(MSu2(i1) - MSd2(i2))/MVWm*ZcplSucSdVWm(i1,i2)
 End Do
End Do 
Do i1=1,3
 Do i2=1,6
GcplHpmSvcSe(1,i1,i2) = (1)*(MSv2OS(i1) - MSe2OS(i2))/MVWmOS*cplSvcSeVWm(i1,i2)
GosZcplHpmSvcSe(1,i1,i2) = (1)*(MSv2OS(i1) - MSe2OS(i2))/MVWmOS*ZcplSvcSeVWm(i1,i2)
GZcplHpmSvcSe(1,i1,i2) = (1)*(MSv2(i1) - MSe2(i2))/MVWm*ZcplSvcSeVWm(i1,i2)
 End Do
End Do 
Do i1=1,6
 Do i2=1,6
GcplSdcHpmcSu(i1,1,i2) = (1)*(MSd2OS(i1) - MSu2OS(i2))/MVWmOS*cplSdcSucVWm(i1,i2)
GosZcplSdcHpmcSu(i1,1,i2) = (1)*(MSd2OS(i1) - MSu2OS(i2))/MVWmOS*ZcplSdcSucVWm(i1,i2)
GZcplSdcHpmcSu(i1,1,i2) = (1)*(MSd2(i1) - MSu2(i2))/MVWm*ZcplSdcSucVWm(i1,i2)
 End Do
End Do 
Do i1=1,6
 Do i2=1,3
GcplSecHpmcSv(i1,1,i2) = (1)*(MSe2OS(i1) - MSv2OS(i2))/MVWmOS*cplSecSvcVWm(i1,i2)
GosZcplSecHpmcSv(i1,1,i2) = (1)*(MSe2OS(i1) - MSv2OS(i2))/MVWmOS*ZcplSecSvcVWm(i1,i2)
GZcplSecHpmcSv(i1,1,i2) = (1)*(MSe2(i1) - MSv2(i2))/MVWm*ZcplSecSvcVWm(i1,i2)
 End Do
End Do 
Do i1=1,3
GcplAhHpmcVWm(i1,1) = 0._dp 
GosZcplAhHpmcVWm(i1,1) = 0._dp
GZcplAhHpmcVWm(i1,1) = 0._dp
End Do 
Do i1=1,3
GcplAhcHpmVWm(i1,1) = 0._dp 
GosZcplAhcHpmVWm(i1,1) = 0._dp
GZcplAhcHpmVWm(i1,1) = 0._dp
End Do 
Do i1=1,3
GcplhhHpmcVWm(i1,1) = 0.5_dp*(1)/MVWmOS*cplhhcVWmVWm(i1)
GosZcplhhHpmcVWm(i1,1) = 0.5_dp*(1)/MVWmOS*ZcplhhcVWmVWm(i1)
GZcplhhHpmcVWm(i1,1) = 0.5_dp*(1)/MVWm*ZcplhhcVWmVWm(i1)
End Do 
Do i1=1,3
GcplhhcHpmVWm(i1,1) = 0.5_dp*(1)/MVWmOS*cplhhcVWmVWm(i1)
GosZcplhhcHpmVWm(i1,1) = 0.5_dp*(1)/MVWmOS*ZcplhhcVWmVWm(i1)
GZcplhhcHpmVWm(i1,1) = 0.5_dp*(1)/MVWm*ZcplhhcVWmVWm(i1)
End Do 
Do i1=1,2
GcplHpmcHpmVP(1,i1) = 0.5_dp*(1)/MVWmOS*cplcHpmVPVWm(i1)
GosZcplHpmcHpmVP(1,i1) = 0.5_dp*(1)/MVWmOS*ZcplcHpmVPVWm(i1)
GZcplHpmcHpmVP(1,i1) = 0.5_dp*(1)/MVWm*ZcplcHpmVPVWm(i1)
End Do 
Do i1=1,2
GcplHpmcHpmVZ(1,i1) = 0.5_dp*(1)/MVWmOS*cplcHpmVWmVZ(i1)
GosZcplHpmcHpmVZ(1,i1) = 0.5_dp*(1)/MVWmOS*ZcplcHpmVWmVZ(i1)
GZcplHpmcHpmVZ(1,i1) = 0.5_dp*(1)/MVWm*ZcplcHpmVWmVZ(i1)
End Do 
GcplHpmcVWmVP(1) = (-1)*(MVWm2OS - 0._dp)/MVWmOS*cplcVWmVPVWm
GosZcplHpmcVWmVP(1) = (-1)*(MVWm2OS - 0._dp)/MVWmOS*ZcplcVWmVPVWm
GZcplHpmcVWmVP(1) = (-1)*(MVWm2 - 0._dp)/MVWmOS*ZcplcVWmVPVWm 
GcplHpmcVWmVZ(1) = (1)*(MVWm2OS - MVZ2OS)/MVWmOS*cplcVWmVWmVZ
GosZcplHpmcVWmVZ(1) = (1)*(MVWm2OS - MVZ2OS)/MVWmOS*ZcplcVWmVWmVZ
GZcplHpmcVWmVZ(1) = (1)*(MVWm2 - MVZ2)/MVWmOS*ZcplcVWmVWmVZ 
GcplcHpmVPVWm(1) = (-1)*(0._dp - MVWm2OS)/MVWmOS*cplcVWmVPVWm
GosZcplcHpmVPVWm(1) = (-1)*(0._dp - MVWm2OS)/MVWmOS*ZcplcVWmVPVWm
GZcplcHpmVPVWm(1) = (-1)*(0._dp - MVWm2)/MVWmOS*ZcplcVWmVPVWm 
GcplcHpmVWmVZ(1) = (-1)*(MVWm2OS - MVZ2OS)/MVWmOS*cplcVWmVWmVZ
GosZcplcHpmVWmVZ(1) = (-1)*(MVWm2OS - MVZ2OS)/MVWmOS*ZcplcVWmVWmVZ
GZcplcHpmVWmVZ(1) = (-1)*(MVWm2 - MVZ2)/MVWmOS*ZcplcVWmVWmVZ 
Do i1=1,5
 Do i2=1,2
GcplChiChacHpmL(i1,i2,1) = (MChiOS(i1)*cplChiChacVWmL(i1,i2) - MChaOS(i2)*cplChiChacVWmR(i1,i2))/MVWmOS
GcplChiChacHpmR(i1,i2,1) = -(MChaOS(i2)*cplChiChacVWmL(i1,i2) - MChiOS(i1)*cplChiChacVWmR(i1,i2))/MVWmOS
GosZcplChiChacHpmL(i1,i2,1) = (MChiOS(i1)*ZcplChiChacVWmL(i1,i2) - MChaOS(i2)*ZcplChiChacVWmR(i1,i2))/MVWmOS
GosZcplChiChacHpmR(i1,i2,1) = -(MChaOS(i2)*ZcplChiChacVWmL(i1,i2) - MChiOS(i1)*ZcplChiChacVWmR(i1,i2))/MVWmOS
GZcplChiChacHpmL(i1,i2,1) = (MChi(i1)*ZcplChiChacVWmL(i1,i2) - MCha(i2)*ZcplChiChacVWmR(i1,i2))/MVWm
GZcplChiChacHpmR(i1,i2,1) = -(MCha(i2)*ZcplChiChacVWmL(i1,i2) - MChi(i1)*ZcplChiChacVWmR(i1,i2))/MVWm
 End Do
End Do 
Do i1=1,2
 Do i2=1,5
GcplcChaChiHpmL(i1,i2,1) = (MChaOS(i1)*cplcChaChiVWmL(i1,i2) - MChiOS(i2)*cplcChaChiVWmR(i1,i2))/MVWmOS
GcplcChaChiHpmR(i1,i2,1) = -(MChiOS(i2)*cplcChaChiVWmL(i1,i2) - MChaOS(i1)*cplcChaChiVWmR(i1,i2))/MVWmOS
GosZcplcChaChiHpmL(i1,i2,1) = (MChaOS(i1)*ZcplcChaChiVWmL(i1,i2) - MChiOS(i2)*ZcplcChaChiVWmR(i1,i2))/MVWmOS
GosZcplcChaChiHpmR(i1,i2,1) = -(MChiOS(i2)*ZcplcChaChiVWmL(i1,i2) - MChaOS(i1)*ZcplcChaChiVWmR(i1,i2))/MVWmOS
GZcplcChaChiHpmL(i1,i2,1) = (MCha(i1)*ZcplcChaChiVWmL(i1,i2) - MChi(i2)*ZcplcChaChiVWmR(i1,i2))/MVWm
GZcplcChaChiHpmR(i1,i2,1) = -(MChi(i2)*ZcplcChaChiVWmL(i1,i2) - MCha(i1)*ZcplcChaChiVWmR(i1,i2))/MVWm
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFuFdcHpmL(i1,i2,1) = (MFuOS(i1)*cplcFuFdcVWmL(i1,i2) - MFdOS(i2)*cplcFuFdcVWmR(i1,i2))/MVWmOS
GcplcFuFdcHpmR(i1,i2,1) = -(MFdOS(i2)*cplcFuFdcVWmL(i1,i2) - MFuOS(i1)*cplcFuFdcVWmR(i1,i2))/MVWmOS
GosZcplcFuFdcHpmL(i1,i2,1) = (MFuOS(i1)*ZcplcFuFdcVWmL(i1,i2) - MFdOS(i2)*ZcplcFuFdcVWmR(i1,i2))/MVWmOS
GosZcplcFuFdcHpmR(i1,i2,1) = -(MFdOS(i2)*ZcplcFuFdcVWmL(i1,i2) - MFuOS(i1)*ZcplcFuFdcVWmR(i1,i2))/MVWmOS
GZcplcFuFdcHpmL(i1,i2,1) = (MFu(i1)*ZcplcFuFdcVWmL(i1,i2) - MFd(i2)*ZcplcFuFdcVWmR(i1,i2))/MVWm
GZcplcFuFdcHpmR(i1,i2,1) = -(MFd(i2)*ZcplcFuFdcVWmL(i1,i2) - MFu(i1)*ZcplcFuFdcVWmR(i1,i2))/MVWm
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFvFecHpmL(i1,i2,1) = (0.*cplcFvFecVWmL(i1,i2) - MFeOS(i2)*cplcFvFecVWmR(i1,i2))/MVWmOS
GcplcFvFecHpmR(i1,i2,1) = -(MFeOS(i2)*cplcFvFecVWmL(i1,i2) - 0.*cplcFvFecVWmR(i1,i2))/MVWmOS
GosZcplcFvFecHpmL(i1,i2,1) = (0.*ZcplcFvFecVWmL(i1,i2) - MFeOS(i2)*ZcplcFvFecVWmR(i1,i2))/MVWmOS
GosZcplcFvFecHpmR(i1,i2,1) = -(MFeOS(i2)*ZcplcFvFecVWmL(i1,i2) - 0.*ZcplcFvFecVWmR(i1,i2))/MVWmOS
GZcplcFvFecHpmL(i1,i2,1) = (0.*ZcplcFvFecVWmL(i1,i2) - MFe(i2)*ZcplcFvFecVWmR(i1,i2))/MVWm
GZcplcFvFecHpmR(i1,i2,1) = -(MFe(i2)*ZcplcFvFecVWmL(i1,i2) - 0.*ZcplcFvFecVWmR(i1,i2))/MVWm
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFdFuHpmL(i1,i2,1) = (MFdOS(i1)*cplcFdFuVWmL(i1,i2) - MFuOS(i2)*cplcFdFuVWmR(i1,i2))/MVWmOS
GcplcFdFuHpmR(i1,i2,1) = -(MFuOS(i2)*cplcFdFuVWmL(i1,i2) - MFdOS(i1)*cplcFdFuVWmR(i1,i2))/MVWmOS
GosZcplcFdFuHpmL(i1,i2,1) = (MFdOS(i1)*ZcplcFdFuVWmL(i1,i2) - MFuOS(i2)*ZcplcFdFuVWmR(i1,i2))/MVWmOS
GosZcplcFdFuHpmR(i1,i2,1) = -(MFuOS(i2)*ZcplcFdFuVWmL(i1,i2) - MFdOS(i1)*ZcplcFdFuVWmR(i1,i2))/MVWmOS
GZcplcFdFuHpmL(i1,i2,1) = (MFd(i1)*ZcplcFdFuVWmL(i1,i2) - MFu(i2)*ZcplcFdFuVWmR(i1,i2))/MVWm
GZcplcFdFuHpmR(i1,i2,1) = -(MFu(i2)*ZcplcFdFuVWmL(i1,i2) - MFd(i1)*ZcplcFdFuVWmR(i1,i2))/MVWm
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFeFvHpmL(i1,i2,1) = (MFeOS(i1)*cplcFeFvVWmL(i1,i2) - 0.*cplcFeFvVWmR(i1,i2))/MVWmOS
GcplcFeFvHpmR(i1,i2,1) = -(0.*cplcFeFvVWmL(i1,i2) - MFeOS(i1)*cplcFeFvVWmR(i1,i2))/MVWmOS
GosZcplcFeFvHpmL(i1,i2,1) = (MFeOS(i1)*ZcplcFeFvVWmL(i1,i2) - 0.*ZcplcFeFvVWmR(i1,i2))/MVWmOS
GosZcplcFeFvHpmR(i1,i2,1) = -(0.*ZcplcFeFvVWmL(i1,i2) - MFeOS(i1)*ZcplcFeFvVWmR(i1,i2))/MVWmOS
GZcplcFeFvHpmL(i1,i2,1) = (MFe(i1)*ZcplcFeFvVWmL(i1,i2) - 0.*ZcplcFeFvVWmR(i1,i2))/MVWm
GZcplcFeFvHpmR(i1,i2,1) = -(0.*ZcplcFeFvVWmL(i1,i2) - MFe(i1)*ZcplcFeFvVWmR(i1,i2))/MVWm
 End Do
End Do 
End Subroutine  getGBCouplings 

Subroutine WaveFunctionRenormalisation(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,               & 
& MSu2OS,MSeOS,MSe2OS,MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,           & 
& MChaOS,MCha2OS,MFeOS,MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,            & 
& MVZ2OS,MVWmOS,MVWm2OS,ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,               & 
& ZELOS,ZEROS,ZDLOS,ZDROS,ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,           & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,cplAhAhAh,cplAhAhhh,               & 
& cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,      & 
& cplSecHpmcSv,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,          & 
& cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhhhhhhh,cplAhhhHpmcHpm,cplAhhhSdcSd,        & 
& cplAhhhSecSe,cplAhhhSucSu,cplAhHpmSucSd,cplAhHpmSvcSe,cplAhSdcHpmcSu,cplAhSecHpmcSv,   & 
& cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplhhhhSvcSv,        & 
& cplhhHpmSucSd,cplhhHpmSvcSe,cplhhSdcHpmcSu,cplhhSecHpmcSv,cplHpmHpmcHpmcHpm,           & 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSdSvcSdcSv,cplSdSvcSecSu,cplSeSecSecSe,cplSeSucSdcSv,   & 
& cplSeSucSecSu,cplSeSvcSecSv,cplSuSucSucSu,cplSuSvcSucSv,cplSvSvcSvcSv,cplAhhhVZ,       & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,      & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,      & 
& cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhcVWmVWm,          & 
& cplAhAhVZVZ,cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,cplAhcHpmVWmVZ,               & 
& cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,cplhhcHpmVPVWm,               & 
& cplhhcHpmVWmVZ,cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,         & 
& cplSdcSdVGVG,cplSdcSdVGVP,cplSdcSdVGVZ,cplSdcSucVWmVG,cplSdcSdVPVP,cplSdcSdVPVZ,       & 
& cplSdcSucVWmVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,cplSdcSucVWmVZ,cplSecSeVPVP,               & 
& cplSecSeVPVZ,cplSecSvcVWmVP,cplSecSecVWmVWm,cplSecSeVZVZ,cplSecSvcVWmVZ,               & 
& cplSucSuVGVG,cplSucSuVGVP,cplSucSdVGVWm,cplSucSuVGVZ,cplSucSuVPVP,cplSucSdVPVWm,       & 
& cplSucSuVPVZ,cplSucSdVWmVZ,cplSucSucVWmVWm,cplSucSuVZVZ,cplSvcSeVPVWm,cplSvcSeVWmVZ,   & 
& cplSvcSvcVWmVWm,cplSvcSvVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,        & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,        & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,   & 
& cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,           & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,            & 
& cplGluGluVGR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,   & 
& cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,    & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3, & 
& cplcgGgGVG,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,               & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,       & 
& cplcgWpCgAcHpm,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,     & 
& cplcgWmgZHpm,cplcgWpCgZcHpm,GcplAhHpmcHpm,GcplhhHpmcHpm,GcplHpmSucSd,GcplHpmSvcSe,     & 
& GcplSdcHpmcSu,GcplSecHpmcSv,GcplAhHpmcVWm,GcplAhcHpmVWm,GcplhhHpmcVWm,GcplhhcHpmVWm,   & 
& GcplHpmcHpmVP,GcplHpmcHpmVZ,GcplHpmcVWmVP,GcplHpmcVWmVZ,GcplcHpmVPVWm,GcplcHpmVWmVZ,   & 
& GcplChiChacHpmL,GcplChiChacHpmR,GcplcChaChiHpmL,GcplcChaChiHpmR,GcplcFuFdcHpmL,        & 
& GcplcFuFdcHpmR,GcplcFvFecHpmL,GcplcFvFecHpmR,GcplcFdFuHpmL,GcplcFdFuHpmR,              & 
& GcplcFeFvHpmL,GcplcFeFvHpmR,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,               & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,ctcplAhAhAh,ctcplAhAhhh,ctcplAhhhhh,ctcplAhHpmcHpm,ctcplAhSdcSd,         & 
& ctcplAhSecSe,ctcplAhSucSu,ctcplhhhhhh,ctcplhhHpmcHpm,ctcplhhSdcSd,ctcplhhSecSe,        & 
& ctcplhhSucSu,ctcplhhSvcSv,ctcplHpmSucSd,ctcplHpmSvcSe,ctcplSdcHpmcSu,ctcplSecHpmcSv,   & 
& ctcplAhhhVZ,ctcplAhHpmcVWm,ctcplAhcHpmVWm,ctcplhhHpmcVWm,ctcplhhcHpmVWm,               & 
& ctcplHpmcHpmVP,ctcplHpmcHpmVZ,ctcplSdcSdVG,ctcplSdcSdVP,ctcplSdcSdVZ,ctcplSdcSucVWm,   & 
& ctcplSecSeVP,ctcplSecSeVZ,ctcplSecSvcVWm,ctcplSucSuVG,ctcplSucSuVP,ctcplSucSdVWm,      & 
& ctcplSucSuVZ,ctcplSvcSeVWm,ctcplSvcSvVZ,ctcplhhcVWmVWm,ctcplhhVZVZ,ctcplHpmcVWmVP,     & 
& ctcplHpmcVWmVZ,ctcplcHpmVPVWm,ctcplcHpmVWmVZ,ctcplVGVGVG,ctcplcVWmVPVWm,               & 
& ctcplcVWmVWmVZ,ctcplcChaChaAhL,ctcplcChaChaAhR,ctcplChiChiAhL,ctcplChiChiAhR,          & 
& ctcplcFdFdAhL,ctcplcFdFdAhR,ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,   & 
& ctcplChiChacHpmL,ctcplChiChacHpmR,ctcplChaFucSdL,ctcplChaFucSdR,ctcplChaFvcSeL,        & 
& ctcplChaFvcSeR,ctcplcChaChahhL,ctcplcChaChahhR,ctcplcFdChaSuL,ctcplcFdChaSuR,          & 
& ctcplcFeChaSvL,ctcplcFeChaSvR,ctcplChiChihhL,ctcplChiChihhR,ctcplChiFdcSdL,            & 
& ctcplChiFdcSdR,ctcplChiFecSeL,ctcplChiFecSeR,ctcplChiFucSuL,ctcplChiFucSuR,            & 
& ctcplChiFvcSvL,ctcplChiFvcSvR,ctcplcChaChiHpmL,ctcplcChaChiHpmR,ctcplcFdChiSdL,        & 
& ctcplcFdChiSdR,ctcplcFeChiSeL,ctcplcFeChiSeR,ctcplcFuChiSuL,ctcplcFuChiSuR,            & 
& ctcplcFvChiSvL,ctcplcFvChiSvR,ctcplGluFdcSdL,ctcplGluFdcSdR,ctcplcFdFdhhL,             & 
& ctcplcFdFdhhR,ctcplcChaFdcSuL,ctcplcChaFdcSuR,ctcplcFuFdcHpmL,ctcplcFuFdcHpmR,         & 
& ctcplcFeFehhL,ctcplcFeFehhR,ctcplcChaFecSvL,ctcplcChaFecSvR,ctcplcFvFecHpmL,           & 
& ctcplcFvFecHpmR,ctcplGluFucSuL,ctcplGluFucSuR,ctcplcFuFuhhL,ctcplcFuFuhhR,             & 
& ctcplcFdFuHpmL,ctcplcFdFuHpmR,ctcplcFeFvHpmL,ctcplcFeFvHpmR,ctcplcFdGluSdL,            & 
& ctcplcFdGluSdR,ctcplcFuGluSuL,ctcplcFuGluSuR,ctcplcChacFuSdL,ctcplcChacFuSdR,          & 
& ctcplcChacFvSeL,ctcplcChacFvSeR,ctcplChiChacVWmL,ctcplChiChacVWmR,ctcplcChaChaVPL,     & 
& ctcplcChaChaVPR,ctcplcChaChaVZL,ctcplcChaChaVZR,ctcplChiChiVZL,ctcplChiChiVZR,         & 
& ctcplcChaChiVWmL,ctcplcChaChiVWmR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,           & 
& ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,ctcplcFuFdcVWmL,ctcplcFuFdcVWmR,             & 
& ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFvFecVWmL,               & 
& ctcplcFvFecVWmR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,               & 
& ctcplcFdFuVWmL,ctcplcFdFuVWmR,ctcplcFuFuVZL,ctcplcFuFuVZR,ctcplcFeFvVWmL,              & 
& ctcplcFeFvVWmR,ctcplcFvFvVZL,ctcplcFvFvVZR,ctcplGluGluVGL,ctcplGluGluVGR,              & 
& MLambda,deltaM,kont)

Implicit None 
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(inout) :: vd,vu,vS

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplhhSvcSv(3,3,3),               & 
& cplHpmSucSd(2,6,6),cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),         & 
& cplAhAhAhAh(3,3,3,3),cplAhAhAhhh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),& 
& cplAhAhSdcSd(3,3,6,6),cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplAhAhSvcSv(3,3,3,3),& 
& cplAhhhhhhh(3,3,3,3),cplAhhhHpmcHpm(3,3,2,2),cplAhhhSdcSd(3,3,6,6),cplAhhhSecSe(3,3,6,6),& 
& cplAhhhSucSu(3,3,6,6),cplAhHpmSucSd(3,2,6,6),cplAhHpmSvcSe(3,2,3,6),cplAhSdcHpmcSu(3,6,2,6),& 
& cplAhSecHpmcSv(3,6,2,3),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),cplhhhhSdcSd(3,3,6,6),& 
& cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplhhhhSvcSv(3,3,3,3),cplhhHpmSucSd(3,2,6,6),& 
& cplhhHpmSvcSe(3,2,3,6),cplhhSdcHpmcSu(3,6,2,6),cplhhSecHpmcSv(3,6,2,3),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSdSvcSdcSv(6,3,6,3),cplSdSvcSecSu(6,3,6,6),cplSeSecSecSe(6,6,6,6),cplSeSucSdcSv(6,6,6,3),& 
& cplSeSucSecSu(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSuSvcSucSv(6,3,6,3),& 
& cplSvSvcSvcSv(3,3,3,3),cplAhhhVZ(3,3),cplAhHpmcVWm(3,2),cplAhcHpmVWm(3,2),             & 
& cplhhHpmcVWm(3,2),cplhhcHpmVWm(3,2),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),               & 
& cplSdcSdVG(6,6),cplSdcSdVP(6,6),cplSdcSdVZ(6,6),cplSdcSucVWm(6,6),cplSecSeVP(6,6),     & 
& cplSecSeVZ(6,6),cplSecSvcVWm(6,3),cplSucSuVG(6,6),cplSucSuVP(6,6),cplSucSdVWm(6,6),    & 
& cplSucSuVZ(6,6),cplSvcSeVWm(3,6),cplSvcSvVZ(3,3),cplhhcVWmVWm(3),cplhhVZVZ(3),         & 
& cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplAhAhcVWmVWm(3,3),   & 
& cplAhAhVZVZ(3,3),cplAhHpmcVWmVP(3,2),cplAhHpmcVWmVZ(3,2),cplAhcHpmVPVWm(3,2),          & 
& cplAhcHpmVWmVZ(3,2),cplhhhhcVWmVWm(3,3),cplhhhhVZVZ(3,3),cplhhHpmcVWmVP(3,2),          & 
& cplhhHpmcVWmVZ(3,2),cplhhcHpmVPVWm(3,2),cplhhcHpmVWmVZ(3,2),cplHpmcHpmVPVP(2,2),       & 
& cplHpmcHpmVPVZ(2,2),cplHpmcHpmcVWmVWm(2,2),cplHpmcHpmVZVZ(2,2),cplSdcSdVGVG(6,6),      & 
& cplSdcSdVGVP(6,6),cplSdcSdVGVZ(6,6),cplSdcSucVWmVG(6,6),cplSdcSdVPVP(6,6),             & 
& cplSdcSdVPVZ(6,6),cplSdcSucVWmVP(6,6),cplSdcSdcVWmVWm(6,6),cplSdcSdVZVZ(6,6),          & 
& cplSdcSucVWmVZ(6,6),cplSecSeVPVP(6,6),cplSecSeVPVZ(6,6),cplSecSvcVWmVP(6,3),           & 
& cplSecSecVWmVWm(6,6),cplSecSeVZVZ(6,6),cplSecSvcVWmVZ(6,3),cplSucSuVGVG(6,6),          & 
& cplSucSuVGVP(6,6),cplSucSdVGVWm(6,6),cplSucSuVGVZ(6,6),cplSucSuVPVP(6,6),              & 
& cplSucSdVPVWm(6,6),cplSucSuVPVZ(6,6),cplSucSdVWmVZ(6,6),cplSucSucVWmVWm(6,6),          & 
& cplSucSuVZVZ(6,6),cplSvcSeVPVWm(3,6),cplSvcSeVWmVZ(3,6),cplSvcSvcVWmVWm(3,3),          & 
& cplSvcSvVZVZ(3,3),cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL(2,2,3),            & 
& cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),       & 
& cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),           & 
& cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),    & 
& cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3)

Complex(dp),Intent(in) :: cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),      & 
& cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),       & 
& cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),       & 
& cplChiFucSuR(5,3,6),cplChiFvcSvL(5,3,3),cplChiFvcSvR(5,3,3),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplcFvChiSvL(3,5,3),       & 
& cplcFvChiSvR(3,5,3),cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),            & 
& cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),     & 
& cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),       & 
& cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),      & 
& cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),           & 
& cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),         & 
& cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),            & 
& cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),cplChiChacVWmL(5,2),    & 
& cplChiChacVWmR(5,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),          & 
& cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplcChaChiVWmL(2,5),            & 
& cplcChaChiVWmR(2,5),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecVWmL(3,3),& 
& cplcFvFecVWmR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),& 
& cplcFeFvVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplGluGluVGL,cplGluGluVGR,         & 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,& 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2, & 
& cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,         & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm, & 
& cplcgWmgWmAh(3),cplcgWpCgWpCAh(3),cplcgZgAhh(3),cplcgWmgAHpm(2),cplcgWpCgAcHpm(2),     & 
& cplcgWmgWmhh(3),cplcgZgWmcHpm(2),cplcgWpCgWpChh(3),cplcgZgWpCHpm(2),cplcgZgZhh(3),     & 
& cplcgWmgZHpm(2),cplcgWpCgZcHpm(2)

Real(dp),Intent(in) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp),Intent(in) :: MSdOS(6),MSd2OS(6),MSvOS(3),MSv2OS(3),MSuOS(6),MSu2OS(6),MSeOS(6),MSe2OS(6),          & 
& MhhOS(3),Mhh2OS(3),MAhOS(3),MAh2OS(3),MHpmOS(2),MHpm2OS(2),MChiOS(5),MChi2OS(5),       & 
& MChaOS(2),MCha2OS(2),MFeOS(3),MFe2OS(3),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),         & 
& MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(3,3),ZAOS(3,3),ZPOS(2,2)

Complex(dp),Intent(in) :: ZDOS(6,6),ZVOS(3,3),ZUOS(6,6),ZEOS(6,6),ZNOS(5,5),UMOS(2,2),UPOS(2,2),ZELOS(3,3),     & 
& ZEROS(3,3),ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3)

Complex(dp) :: PiSd(6,6,6),DerPiSd(6,6,6),PiSv(3,3,3),DerPiSv(3,3,3),PiSu(6,6,6),DerPiSu(6,6,6),     & 
& PiSe(6,6,6),DerPiSe(6,6,6),Pihh(3,3,3),DerPihh(3,3,3),PiAh(3,3,3),DerPiAh(3,3,3),      & 
& PiHpm(2,2,2),DerPiHpm(2,2,2),SigmaLChi(5,5,5),SigmaSLChi(5,5,5),SigmaSRChi(5,5,5),     & 
& SigmaRChi(5,5,5),DerSigmaLChi(5,5,5),DerSigmaSLChi(5,5,5),DerSigmaSRChi(5,5,5),        & 
& DerSigmaRChi(5,5,5),DerSigmaLirChi(5,5,5),DerSigmaSLirChi(5,5,5),DerSigmaSRirChi(5,5,5),& 
& DerSigmaRirChi(5,5,5),SigmaLCha(2,2,2),SigmaSLCha(2,2,2),SigmaSRCha(2,2,2),            & 
& SigmaRCha(2,2,2),DerSigmaLCha(2,2,2),DerSigmaSLCha(2,2,2),DerSigmaSRCha(2,2,2),        & 
& DerSigmaRCha(2,2,2),DerSigmaLirCha(2,2,2),DerSigmaSLirCha(2,2,2),DerSigmaSRirCha(2,2,2),& 
& DerSigmaRirCha(2,2,2),SigmaLFe(3,3,3),SigmaSLFe(3,3,3),SigmaSRFe(3,3,3),               & 
& SigmaRFe(3,3,3),DerSigmaLFe(3,3,3),DerSigmaSLFe(3,3,3),DerSigmaSRFe(3,3,3),            & 
& DerSigmaRFe(3,3,3),DerSigmaLirFe(3,3,3),DerSigmaSLirFe(3,3,3),DerSigmaSRirFe(3,3,3),   & 
& DerSigmaRirFe(3,3,3),SigmaLFd(3,3,3),SigmaSLFd(3,3,3),SigmaSRFd(3,3,3),SigmaRFd(3,3,3),& 
& DerSigmaLFd(3,3,3),DerSigmaSLFd(3,3,3),DerSigmaSRFd(3,3,3),DerSigmaRFd(3,3,3),         & 
& DerSigmaLirFd(3,3,3),DerSigmaSLirFd(3,3,3),DerSigmaSRirFd(3,3,3),DerSigmaRirFd(3,3,3), & 
& SigmaLFu(3,3,3),SigmaSLFu(3,3,3),SigmaSRFu(3,3,3),SigmaRFu(3,3,3),DerSigmaLFu(3,3,3),  & 
& DerSigmaSLFu(3,3,3),DerSigmaSRFu(3,3,3),DerSigmaRFu(3,3,3),DerSigmaLirFu(3,3,3),       & 
& DerSigmaSLirFu(3,3,3),DerSigmaSRirFu(3,3,3),DerSigmaRirFu(3,3,3),SigmaLGlu,            & 
& SigmaSLGlu,SigmaSRGlu,SigmaRGlu,DerSigmaLGlu,DerSigmaSLGlu,DerSigmaSRGlu,              & 
& DerSigmaRGlu,DerSigmaLirGlu,DerSigmaSLirGlu,DerSigmaSRirGlu,DerSigmaRirGlu,            & 
& SigmaLFv(3,3,3),SigmaSLFv(3,3,3),SigmaSRFv(3,3,3),SigmaRFv(3,3,3),DerSigmaLFv(3,3,3),  & 
& DerSigmaSLFv(3,3,3),DerSigmaSRFv(3,3,3),DerSigmaRFv(3,3,3),DerSigmaLirFv(3,3,3),       & 
& DerSigmaSLirFv(3,3,3),DerSigmaSRirFv(3,3,3),DerSigmaRirFv(3,3,3),PiVG,DerPiVG,         & 
& PiVP,DerPiVP,PiVZ,DerPiVZ,PiVWm,DerPiVWm,PiVPlight0,DerPiVPlight0,PiVPheavy0,          & 
& DerPiVPheavy0,PiVPlightMZ,DerPiVPlightMZ,PiVPheavyMZ,DerPiVPheavyMZ,PiVPVZ,            & 
& DerPiVPVZ,PiVZVP,DerPiVZVP,PiVZhh(3,3,3),DerPiVZhh(3,3,3),PihhVZ(3,3,3),               & 
& DerPihhVZ(3,3,3),PiVZAh(3,3,3),DerPiVZAh(3,3,3),PiAhVZ(3,3,3),DerPiAhVZ(3,3,3),        & 
& PiVWmHpm(2,2,2),DerPiVWmHpm(2,2,2),PiHpmVWm(2,2,2),DerPiHpmVWm(2,2,2)

Complex(dp) :: PiSdDR(6,6,6),DerPiSdDR(6,6,6),PiSvDR(3,3,3),DerPiSvDR(3,3,3),PiSuDR(6,6,6),          & 
& DerPiSuDR(6,6,6),PiSeDR(6,6,6),DerPiSeDR(6,6,6),PihhDR(3,3,3),DerPihhDR(3,3,3),        & 
& PiAhDR(3,3,3),DerPiAhDR(3,3,3),PiHpmDR(2,2,2),DerPiHpmDR(2,2,2),SigmaLChiDR(5,5,5),    & 
& SigmaSLChiDR(5,5,5),SigmaSRChiDR(5,5,5),SigmaRChiDR(5,5,5),DerSigmaLChiDR(5,5,5),      & 
& DerSigmaSLChiDR(5,5,5),DerSigmaSRChiDR(5,5,5),DerSigmaRChiDR(5,5,5),DerSigmaLirChiDR(5,5,5),& 
& DerSigmaSLirChiDR(5,5,5),DerSigmaSRirChiDR(5,5,5),DerSigmaRirChiDR(5,5,5),             & 
& SigmaLChaDR(2,2,2),SigmaSLChaDR(2,2,2),SigmaSRChaDR(2,2,2),SigmaRChaDR(2,2,2),         & 
& DerSigmaLChaDR(2,2,2),DerSigmaSLChaDR(2,2,2),DerSigmaSRChaDR(2,2,2),DerSigmaRChaDR(2,2,2),& 
& DerSigmaLirChaDR(2,2,2),DerSigmaSLirChaDR(2,2,2),DerSigmaSRirChaDR(2,2,2),             & 
& DerSigmaRirChaDR(2,2,2),SigmaLFeDR(3,3,3),SigmaSLFeDR(3,3,3),SigmaSRFeDR(3,3,3),       & 
& SigmaRFeDR(3,3,3),DerSigmaLFeDR(3,3,3),DerSigmaSLFeDR(3,3,3),DerSigmaSRFeDR(3,3,3),    & 
& DerSigmaRFeDR(3,3,3),DerSigmaLirFeDR(3,3,3),DerSigmaSLirFeDR(3,3,3),DerSigmaSRirFeDR(3,3,3),& 
& DerSigmaRirFeDR(3,3,3),SigmaLFdDR(3,3,3),SigmaSLFdDR(3,3,3),SigmaSRFdDR(3,3,3),        & 
& SigmaRFdDR(3,3,3),DerSigmaLFdDR(3,3,3),DerSigmaSLFdDR(3,3,3),DerSigmaSRFdDR(3,3,3),    & 
& DerSigmaRFdDR(3,3,3),DerSigmaLirFdDR(3,3,3),DerSigmaSLirFdDR(3,3,3),DerSigmaSRirFdDR(3,3,3),& 
& DerSigmaRirFdDR(3,3,3),SigmaLFuDR(3,3,3),SigmaSLFuDR(3,3,3),SigmaSRFuDR(3,3,3),        & 
& SigmaRFuDR(3,3,3),DerSigmaLFuDR(3,3,3),DerSigmaSLFuDR(3,3,3),DerSigmaSRFuDR(3,3,3),    & 
& DerSigmaRFuDR(3,3,3),DerSigmaLirFuDR(3,3,3),DerSigmaSLirFuDR(3,3,3),DerSigmaSRirFuDR(3,3,3),& 
& DerSigmaRirFuDR(3,3,3),SigmaLGluDR,SigmaSLGluDR,SigmaSRGluDR,SigmaRGluDR,              & 
& DerSigmaLGluDR,DerSigmaSLGluDR,DerSigmaSRGluDR,DerSigmaRGluDR,DerSigmaLirGluDR,        & 
& DerSigmaSLirGluDR,DerSigmaSRirGluDR,DerSigmaRirGluDR,SigmaLFvDR(3,3,3),SigmaSLFvDR(3,3,3),& 
& SigmaSRFvDR(3,3,3),SigmaRFvDR(3,3,3),DerSigmaLFvDR(3,3,3),DerSigmaSLFvDR(3,3,3),       & 
& DerSigmaSRFvDR(3,3,3),DerSigmaRFvDR(3,3,3),DerSigmaLirFvDR(3,3,3),DerSigmaSLirFvDR(3,3,3),& 
& DerSigmaSRirFvDR(3,3,3),DerSigmaRirFvDR(3,3,3),PiVGDR,DerPiVGDR,PiVPDR,DerPiVPDR,      & 
& PiVZDR,DerPiVZDR,PiVWmDR,DerPiVWmDR,PiVPlight0DR,DerPiVPlight0DR,PiVPheavy0DR,         & 
& DerPiVPheavy0DR,PiVPlightMZDR,DerPiVPlightMZDR,PiVPheavyMZDR,DerPiVPheavyMZDR,         & 
& PiVPVZDR,DerPiVPVZDR,PiVZVPDR,DerPiVZVPDR,PiVZhhDR(3,3,3),DerPiVZhhDR(3,3,3),          & 
& PihhVZDR(3,3,3),DerPihhVZDR(3,3,3),PiVZAhDR(3,3,3),DerPiVZAhDR(3,3,3),PiAhVZDR(3,3,3), & 
& DerPiAhVZDR(3,3,3),PiVWmHpmDR(2,2,2),DerPiVWmHpmDR(2,2,2),PiHpmVWmDR(2,2,2),           & 
& DerPiHpmVWmDR(2,2,2)

Complex(dp) :: PiSdOS(6,6,6),DerPiSdOS(6,6,6),PiSvOS(3,3,3),DerPiSvOS(3,3,3),PiSuOS(6,6,6),          & 
& DerPiSuOS(6,6,6),PiSeOS(6,6,6),DerPiSeOS(6,6,6),PihhOS(3,3,3),DerPihhOS(3,3,3),        & 
& PiAhOS(3,3,3),DerPiAhOS(3,3,3),PiHpmOS(2,2,2),DerPiHpmOS(2,2,2),SigmaLChiOS(5,5,5),    & 
& SigmaSLChiOS(5,5,5),SigmaSRChiOS(5,5,5),SigmaRChiOS(5,5,5),DerSigmaLChiOS(5,5,5),      & 
& DerSigmaSLChiOS(5,5,5),DerSigmaSRChiOS(5,5,5),DerSigmaRChiOS(5,5,5),DerSigmaLirChiOS(5,5,5),& 
& DerSigmaSLirChiOS(5,5,5),DerSigmaSRirChiOS(5,5,5),DerSigmaRirChiOS(5,5,5),             & 
& SigmaLChaOS(2,2,2),SigmaSLChaOS(2,2,2),SigmaSRChaOS(2,2,2),SigmaRChaOS(2,2,2),         & 
& DerSigmaLChaOS(2,2,2),DerSigmaSLChaOS(2,2,2),DerSigmaSRChaOS(2,2,2),DerSigmaRChaOS(2,2,2),& 
& DerSigmaLirChaOS(2,2,2),DerSigmaSLirChaOS(2,2,2),DerSigmaSRirChaOS(2,2,2),             & 
& DerSigmaRirChaOS(2,2,2),SigmaLFeOS(3,3,3),SigmaSLFeOS(3,3,3),SigmaSRFeOS(3,3,3),       & 
& SigmaRFeOS(3,3,3),DerSigmaLFeOS(3,3,3),DerSigmaSLFeOS(3,3,3),DerSigmaSRFeOS(3,3,3),    & 
& DerSigmaRFeOS(3,3,3),DerSigmaLirFeOS(3,3,3),DerSigmaSLirFeOS(3,3,3),DerSigmaSRirFeOS(3,3,3),& 
& DerSigmaRirFeOS(3,3,3),SigmaLFdOS(3,3,3),SigmaSLFdOS(3,3,3),SigmaSRFdOS(3,3,3),        & 
& SigmaRFdOS(3,3,3),DerSigmaLFdOS(3,3,3),DerSigmaSLFdOS(3,3,3),DerSigmaSRFdOS(3,3,3),    & 
& DerSigmaRFdOS(3,3,3),DerSigmaLirFdOS(3,3,3),DerSigmaSLirFdOS(3,3,3),DerSigmaSRirFdOS(3,3,3),& 
& DerSigmaRirFdOS(3,3,3),SigmaLFuOS(3,3,3),SigmaSLFuOS(3,3,3),SigmaSRFuOS(3,3,3),        & 
& SigmaRFuOS(3,3,3),DerSigmaLFuOS(3,3,3),DerSigmaSLFuOS(3,3,3),DerSigmaSRFuOS(3,3,3),    & 
& DerSigmaRFuOS(3,3,3),DerSigmaLirFuOS(3,3,3),DerSigmaSLirFuOS(3,3,3),DerSigmaSRirFuOS(3,3,3),& 
& DerSigmaRirFuOS(3,3,3),SigmaLGluOS,SigmaSLGluOS,SigmaSRGluOS,SigmaRGluOS,              & 
& DerSigmaLGluOS,DerSigmaSLGluOS,DerSigmaSRGluOS,DerSigmaRGluOS,DerSigmaLirGluOS,        & 
& DerSigmaSLirGluOS,DerSigmaSRirGluOS,DerSigmaRirGluOS,SigmaLFvOS(3,3,3),SigmaSLFvOS(3,3,3),& 
& SigmaSRFvOS(3,3,3),SigmaRFvOS(3,3,3),DerSigmaLFvOS(3,3,3),DerSigmaSLFvOS(3,3,3),       & 
& DerSigmaSRFvOS(3,3,3),DerSigmaRFvOS(3,3,3),DerSigmaLirFvOS(3,3,3),DerSigmaSLirFvOS(3,3,3),& 
& DerSigmaSRirFvOS(3,3,3),DerSigmaRirFvOS(3,3,3),PiVGOS,DerPiVGOS,PiVPOS,DerPiVPOS,      & 
& PiVZOS,DerPiVZOS,PiVWmOS,DerPiVWmOS,PiVPlight0OS,DerPiVPlight0OS,PiVPheavy0OS,         & 
& DerPiVPheavy0OS,PiVPlightMZOS,DerPiVPlightMZOS,PiVPheavyMZOS,DerPiVPheavyMZOS,         & 
& PiVPVZOS,DerPiVPVZOS,PiVZVPOS,DerPiVZVPOS,PiVZhhOS(3,3,3),DerPiVZhhOS(3,3,3),          & 
& PihhVZOS(3,3,3),DerPihhVZOS(3,3,3),PiVZAhOS(3,3,3),DerPiVZAhOS(3,3,3),PiAhVZOS(3,3,3), & 
& DerPiAhVZOS(3,3,3),PiVWmHpmOS(2,2,2),DerPiVWmHpmOS(2,2,2),PiHpmVWmOS(2,2,2),           & 
& DerPiHpmVWmOS(2,2,2)

Real(dp), Intent(in) :: MLambda, deltaM 

Integer, Intent(out) :: kont 
Real(dp),Intent(out) :: dg1,dg2,dg3,dmHd2,dmHu2,dms2,dvd,dvu,dvS,dZH(3,3),dZA(3,3),dZP(2,2),dSinTW,           & 
& dCosTW,dTanTW

Complex(dp),Intent(out) :: dYd(3,3),dTd(3,3),dYe(3,3),dTe(3,3),dlam,dTlam,dkap,dTk,dYu(3,3),dTu(3,3),            & 
& dmq2(3,3),dml2(3,3),dmd2(3,3),dmu2(3,3),dme2(3,3),dM1,dM2,dM3,dpG,dZD(6,6),            & 
& dZV(3,3),dZU(6,6),dZE(6,6),dZN(5,5),dUM(2,2),dUP(2,2),dZEL(3,3),dZER(3,3),             & 
& dZDL(3,3),dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp),Intent(out) :: ZfVG,ZffG,ZfFvL(3,3),ZfVP,ZfVZ,ZfVWm,ZfSd(6,6),ZfSv(3,3),ZfSu(6,6),ZfSe(6,6),         & 
& Zfhh(3,3),ZfAh(3,3),ZfHpm(2,2),ZfL0(5,5),ZfLm(2,2),ZfLp(2,2),ZfFEL(3,3),               & 
& ZfFER(3,3),ZfFDL(3,3),ZfFDR(3,3),ZfFUL(3,3),ZfFUR(3,3),ZfVPVZ,ZfVZVP

Complex(dp),Intent(out) :: ctcplAhAhAh(3,3,3),ctcplAhAhhh(3,3,3),ctcplAhhhhh(3,3,3),ctcplAhHpmcHpm(3,2,2),       & 
& ctcplAhSdcSd(3,6,6),ctcplAhSecSe(3,6,6),ctcplAhSucSu(3,6,6),ctcplhhhhhh(3,3,3),        & 
& ctcplhhHpmcHpm(3,2,2),ctcplhhSdcSd(3,6,6),ctcplhhSecSe(3,6,6),ctcplhhSucSu(3,6,6),     & 
& ctcplhhSvcSv(3,3,3),ctcplHpmSucSd(2,6,6),ctcplHpmSvcSe(2,3,6),ctcplSdcHpmcSu(6,2,6),   & 
& ctcplSecHpmcSv(6,2,3),ctcplAhhhVZ(3,3),ctcplAhHpmcVWm(3,2),ctcplAhcHpmVWm(3,2),        & 
& ctcplhhHpmcVWm(3,2),ctcplhhcHpmVWm(3,2),ctcplHpmcHpmVP(2,2),ctcplHpmcHpmVZ(2,2),       & 
& ctcplSdcSdVG(6,6),ctcplSdcSdVP(6,6),ctcplSdcSdVZ(6,6),ctcplSdcSucVWm(6,6),             & 
& ctcplSecSeVP(6,6),ctcplSecSeVZ(6,6),ctcplSecSvcVWm(6,3),ctcplSucSuVG(6,6),             & 
& ctcplSucSuVP(6,6),ctcplSucSdVWm(6,6),ctcplSucSuVZ(6,6),ctcplSvcSeVWm(3,6),             & 
& ctcplSvcSvVZ(3,3),ctcplhhcVWmVWm(3),ctcplhhVZVZ(3),ctcplHpmcVWmVP(2),ctcplHpmcVWmVZ(2),& 
& ctcplcHpmVPVWm(2),ctcplcHpmVWmVZ(2),ctcplVGVGVG,ctcplcVWmVPVWm,ctcplcVWmVWmVZ,         & 
& ctcplcChaChaAhL(2,2,3),ctcplcChaChaAhR(2,2,3),ctcplChiChiAhL(5,5,3),ctcplChiChiAhR(5,5,3),& 
& ctcplcFdFdAhL(3,3,3),ctcplcFdFdAhR(3,3,3),ctcplcFeFeAhL(3,3,3),ctcplcFeFeAhR(3,3,3),   & 
& ctcplcFuFuAhL(3,3,3),ctcplcFuFuAhR(3,3,3),ctcplChiChacHpmL(5,2,2),ctcplChiChacHpmR(5,2,2),& 
& ctcplChaFucSdL(2,3,6),ctcplChaFucSdR(2,3,6),ctcplChaFvcSeL(2,3,6),ctcplChaFvcSeR(2,3,6),& 
& ctcplcChaChahhL(2,2,3),ctcplcChaChahhR(2,2,3),ctcplcFdChaSuL(3,2,6),ctcplcFdChaSuR(3,2,6),& 
& ctcplcFeChaSvL(3,2,3),ctcplcFeChaSvR(3,2,3),ctcplChiChihhL(5,5,3),ctcplChiChihhR(5,5,3),& 
& ctcplChiFdcSdL(5,3,6),ctcplChiFdcSdR(5,3,6),ctcplChiFecSeL(5,3,6),ctcplChiFecSeR(5,3,6),& 
& ctcplChiFucSuL(5,3,6),ctcplChiFucSuR(5,3,6),ctcplChiFvcSvL(5,3,3),ctcplChiFvcSvR(5,3,3),& 
& ctcplcChaChiHpmL(2,5,2),ctcplcChaChiHpmR(2,5,2),ctcplcFdChiSdL(3,5,6),ctcplcFdChiSdR(3,5,6),& 
& ctcplcFeChiSeL(3,5,6),ctcplcFeChiSeR(3,5,6),ctcplcFuChiSuL(3,5,6),ctcplcFuChiSuR(3,5,6),& 
& ctcplcFvChiSvL(3,5,3),ctcplcFvChiSvR(3,5,3),ctcplGluFdcSdL(3,6),ctcplGluFdcSdR(3,6),   & 
& ctcplcFdFdhhL(3,3,3),ctcplcFdFdhhR(3,3,3),ctcplcChaFdcSuL(2,3,6),ctcplcChaFdcSuR(2,3,6),& 
& ctcplcFuFdcHpmL(3,3,2),ctcplcFuFdcHpmR(3,3,2),ctcplcFeFehhL(3,3,3),ctcplcFeFehhR(3,3,3),& 
& ctcplcChaFecSvL(2,3,3),ctcplcChaFecSvR(2,3,3),ctcplcFvFecHpmL(3,3,2),ctcplcFvFecHpmR(3,3,2),& 
& ctcplGluFucSuL(3,6),ctcplGluFucSuR(3,6),ctcplcFuFuhhL(3,3,3),ctcplcFuFuhhR(3,3,3),     & 
& ctcplcFdFuHpmL(3,3,2),ctcplcFdFuHpmR(3,3,2),ctcplcFeFvHpmL(3,3,2),ctcplcFeFvHpmR(3,3,2),& 
& ctcplcFdGluSdL(3,6),ctcplcFdGluSdR(3,6),ctcplcFuGluSuL(3,6),ctcplcFuGluSuR(3,6),       & 
& ctcplcChacFuSdL(2,3,6),ctcplcChacFuSdR(2,3,6),ctcplcChacFvSeL(2,3,6),ctcplcChacFvSeR(2,3,6),& 
& ctcplChiChacVWmL(5,2),ctcplChiChacVWmR(5,2),ctcplcChaChaVPL(2,2),ctcplcChaChaVPR(2,2), & 
& ctcplcChaChaVZL(2,2),ctcplcChaChaVZR(2,2),ctcplChiChiVZL(5,5),ctcplChiChiVZR(5,5),     & 
& ctcplcChaChiVWmL(2,5),ctcplcChaChiVWmR(2,5),ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),     & 
& ctcplcFdFdVPL(3,3),ctcplcFdFdVPR(3,3),ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3),           & 
& ctcplcFuFdcVWmL(3,3),ctcplcFuFdcVWmR(3,3),ctcplcFeFeVPL(3,3),ctcplcFeFeVPR(3,3),       & 
& ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),ctcplcFvFecVWmL(3,3),ctcplcFvFecVWmR(3,3),       & 
& ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),           & 
& ctcplcFdFuVWmL(3,3),ctcplcFdFuVWmR(3,3),ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3)

Complex(dp),Intent(out) :: ctcplcFeFvVWmL(3,3),ctcplcFeFvVWmR(3,3),ctcplcFvFvVZL(3,3),ctcplcFvFvVZR(3,3),         & 
& ctcplGluGluVGL,ctcplGluGluVGR

Complex(dp),Intent(in) :: GcplAhHpmcHpm(3,2,2),GcplhhHpmcHpm(3,2,2),GcplHpmSucSd(2,6,6),GcplHpmSvcSe(2,3,6),    & 
& GcplSdcHpmcSu(6,2,6),GcplSecHpmcSv(6,2,3),GcplAhHpmcVWm(3,2),GcplAhcHpmVWm(3,2),       & 
& GcplhhHpmcVWm(3,2),GcplhhcHpmVWm(3,2),GcplHpmcHpmVP(2,2),GcplHpmcHpmVZ(2,2),           & 
& GcplHpmcVWmVP(2),GcplHpmcVWmVZ(2),GcplcHpmVPVWm(2),GcplcHpmVWmVZ(2),GcplChiChacHpmL(5,2,2),& 
& GcplChiChacHpmR(5,2,2),GcplcChaChiHpmL(2,5,2),GcplcChaChiHpmR(2,5,2),GcplcFuFdcHpmL(3,3,2),& 
& GcplcFuFdcHpmR(3,3,2),GcplcFvFecHpmL(3,3,2),GcplcFvFecHpmR(3,3,2),GcplcFdFuHpmL(3,3,2),& 
& GcplcFdFuHpmR(3,3,2),GcplcFeFvHpmL(3,3,2),GcplcFeFvHpmR(3,3,2)

Real(dp) ::  g1D(221) 
Real(dp) :: p2 
Logical :: TwoLoopRGEsave 
Real(dp) ::MVG,MVP,MVG2,MVP2
Complex(dp) ::  Tad1Loop(3)
Complex(dp) :: MatTad_hh(3,3)=0._dp 
Integer :: i1,i2,i3 

MVG = MLambda 
MVP = MLambda 
MVG2 = MLambda**2 
MVP2 = MLambda**2 

Call OneLoopTadpoleshh(vd,vS,vu,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,              & 
& MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,             & 
& MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,              & 
& cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcVWmVWm,cplhhVZVZ,Tad1Loop(1:3))

Tad1Loop(1:3) = MatMul(ZH,Tad1Loop(1:3)) 
Tad1Loop(1) = Tad1Loop(1)/vd 
Tad1Loop(2) = Tad1Loop(2)/vu 
Tad1Loop(3) = Tad1Loop(3)/vS 
Do i1=1,3
MatTad_hh(i1,i1) = Tad1Loop(0+ i1) 
End Do 
MatTad_hh = MatMul(MatMul(ZH,MatTad_hh),Transpose(ZH)) 
! Not working!! 
MatTad_hh= 0._dp
!--------------------------
!Sd
!--------------------------
Do i1=1,6
p2 = MSd2(i1)
Call Pi1LoopSd(p2,MSd,MSd2,MAh,MAh2,MFu,MFu2,MCha,MCha2,MFd,MFd2,MChi,MChi2,          & 
& MGlu,MGlu2,Mhh,Mhh2,MSu,MSu2,MHpm,MHpm2,MVZ,MVZ2,MVWm,MVWm2,MSe,MSe2,MSv,              & 
& MSv2,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,      & 
& cplGluFdcSdR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,      & 
& cplAhAhSdcSd,cplhhhhSdcSd,cplHpmSdcHpmcSd,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,   & 
& cplSdSvcSdcSv,cplSdcSdVGVG,cplSdcSdVPVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,kont,             & 
& PiSd(i1,:,:))

Call DerPi1LoopSd(p2,MSd,MSd2,MAh,MAh2,MFu,MFu2,MCha,MCha2,MFd,MFd2,MChi,             & 
& MChi2,MGlu,MGlu2,Mhh,Mhh2,MSu,MSu2,MHpm,MHpm2,MVZ,MVZ2,MVWm,MVWm2,MSe,MSe2,            & 
& MSv,MSv2,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,               & 
& cplGluFdcSdL,cplGluFdcSdR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,     & 
& cplSucSdVWm,cplAhAhSdcSd,cplhhhhSdcSd,cplHpmSdcHpmcSd,cplSdSdcSdcSd,cplSdSecSdcSe,     & 
& cplSdSucSdcSu,cplSdSvcSdcSv,cplSdcSdVGVG,cplSdcSdVPVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,    & 
& kont,DerPiSd(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopSd(p2,MSd,MSd2,MAh,MAh2,MFu,MFu2,MCha,MCha2,MFd,MFd2,MChi,             & 
& MChi2,MGlu,MGlu2,Mhh,Mhh2,MSu,MSu2,MHpm,MHpm2,MVZ,MVZ2,MVWm,MVWm2,MSe,MSe2,            & 
& MSv,MSv2,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,               & 
& cplGluFdcSdL,cplGluFdcSdR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,     & 
& cplSucSdVWm,cplAhAhSdcSd,cplhhhhSdcSd,cplHpmSdcHpmcSd,cplSdSdcSdcSd,cplSdSecSdcSe,     & 
& cplSdSucSdcSu,cplSdSvcSdcSv,cplSdcSdVGVG,cplSdcSdVPVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,    & 
& kont,DerPiSdDR(i1,:,:))

p2 =MSd2OS(i1)
Call DerPi1LoopSd(p2,MSdOS,MSd2OS,MAhOS,MAh2OS,MFuOS,MFu2OS,MChaOS,MCha2OS,           & 
& MFdOS,MFd2OS,MChiOS,MChi2OS,MGluOS,MGlu2OS,MhhOS,Mhh2OS,MSuOS,MSu2OS,MHpmOS,           & 
& MHpm2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,MSeOS,MSe2OS,MSvOS,MSv2OS,cplAhSdcSd,              & 
& cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,cplAhAhSdcSd,      & 
& cplhhhhSdcSd,cplHpmSdcHpmcSd,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,cplSdSvcSdcSv,  & 
& cplSdcSdVGVG,cplSdcSdVPVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,kont,DerPiSdOS(i1,:,:))

DerPiSd(i1,:,:) = DerPiSd(i1,:,:)- DerPiSdDR(i1,:,:) + DerPiSdOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Sv
!--------------------------
Do i1=1,3
p2 = MSv2(i1)
Call Pi1LoopSv(p2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MSv,MSv2,Mhh,Mhh2,MHpm,              & 
& MHpm2,MSe,MSe2,MVWm,MVWm2,MVZ,MVZ2,MAh,MAh2,MSd,MSd2,MSu,MSu2,cplChiFvcSvL,            & 
& cplChiFvcSvR,cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplSecHpmcSv,cplSecSvcVWm,         & 
& cplSvcSvVZ,cplAhAhSvcSv,cplhhhhSvcSv,cplHpmSvcHpmcSv,cplSdSvcSdcSv,cplSeSvcSecSv,      & 
& cplSuSvcSucSv,cplSvSvcSvcSv,cplSvcSvcVWmVWm,cplSvcSvVZVZ,kont,PiSv(i1,:,:))

Call DerPi1LoopSv(p2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MSv,MSv2,Mhh,Mhh2,MHpm,           & 
& MHpm2,MSe,MSe2,MVWm,MVWm2,MVZ,MVZ2,MAh,MAh2,MSd,MSd2,MSu,MSu2,cplChiFvcSvL,            & 
& cplChiFvcSvR,cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplSecHpmcSv,cplSecSvcVWm,         & 
& cplSvcSvVZ,cplAhAhSvcSv,cplhhhhSvcSv,cplHpmSvcHpmcSv,cplSdSvcSdcSv,cplSeSvcSecSv,      & 
& cplSuSvcSucSv,cplSvSvcSvcSv,cplSvcSvcVWmVWm,cplSvcSvVZVZ,kont,DerPiSv(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopSv(p2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MSv,MSv2,Mhh,Mhh2,MHpm,           & 
& MHpm2,MSe,MSe2,MVWm,MVWm2,MVZ,MVZ2,MAh,MAh2,MSd,MSd2,MSu,MSu2,cplChiFvcSvL,            & 
& cplChiFvcSvR,cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplSecHpmcSv,cplSecSvcVWm,         & 
& cplSvcSvVZ,cplAhAhSvcSv,cplhhhhSvcSv,cplHpmSvcHpmcSv,cplSdSvcSdcSv,cplSeSvcSecSv,      & 
& cplSuSvcSucSv,cplSvSvcSvcSv,cplSvcSvcVWmVWm,cplSvcSvVZVZ,kont,DerPiSvDR(i1,:,:))

p2 =MSv2OS(i1)
Call DerPi1LoopSv(p2,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,MFe2OS,MSvOS,MSv2OS,         & 
& MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSeOS,MSe2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,MAhOS,            & 
& MAh2OS,MSdOS,MSd2OS,MSuOS,MSu2OS,cplChiFvcSvL,cplChiFvcSvR,cplcChaFecSvL,              & 
& cplcChaFecSvR,cplhhSvcSv,cplSecHpmcSv,cplSecSvcVWm,cplSvcSvVZ,cplAhAhSvcSv,            & 
& cplhhhhSvcSv,cplHpmSvcHpmcSv,cplSdSvcSdcSv,cplSeSvcSecSv,cplSuSvcSucSv,cplSvSvcSvcSv,  & 
& cplSvcSvcVWmVWm,cplSvcSvVZVZ,kont,DerPiSvOS(i1,:,:))

DerPiSv(i1,:,:) = DerPiSv(i1,:,:)- DerPiSvDR(i1,:,:) + DerPiSvOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Su
!--------------------------
Do i1=1,6
p2 = MSu2(i1)
Call Pi1LoopSu(p2,MSu,MSu2,MAh,MAh2,MFu,MFu2,MChi,MChi2,MCha,MCha2,MFd,               & 
& MFd2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MVWm,MVWm2,MVZ,MVZ2,MSe,MSe2,             & 
& MSv,MSv2,cplAhSucSu,cplChiFucSuL,cplChiFucSuR,cplcChaFdcSuL,cplcChaFdcSuR,             & 
& cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,             & 
& cplSucSuVP,cplSucSuVZ,cplAhAhSucSu,cplhhhhSucSu,cplHpmSucHpmcSu,cplSdSucSdcSu,         & 
& cplSeSucSecSu,cplSuSucSucSu,cplSuSvcSucSv,cplSucSuVGVG,cplSucSuVPVP,cplSucSucVWmVWm,   & 
& cplSucSuVZVZ,kont,PiSu(i1,:,:))

Call DerPi1LoopSu(p2,MSu,MSu2,MAh,MAh2,MFu,MFu2,MChi,MChi2,MCha,MCha2,MFd,            & 
& MFd2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MVWm,MVWm2,MVZ,MVZ2,MSe,MSe2,             & 
& MSv,MSv2,cplAhSucSu,cplChiFucSuL,cplChiFucSuR,cplcChaFdcSuL,cplcChaFdcSuR,             & 
& cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,             & 
& cplSucSuVP,cplSucSuVZ,cplAhAhSucSu,cplhhhhSucSu,cplHpmSucHpmcSu,cplSdSucSdcSu,         & 
& cplSeSucSecSu,cplSuSucSucSu,cplSuSvcSucSv,cplSucSuVGVG,cplSucSuVPVP,cplSucSucVWmVWm,   & 
& cplSucSuVZVZ,kont,DerPiSu(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopSu(p2,MSu,MSu2,MAh,MAh2,MFu,MFu2,MChi,MChi2,MCha,MCha2,MFd,            & 
& MFd2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MVWm,MVWm2,MVZ,MVZ2,MSe,MSe2,             & 
& MSv,MSv2,cplAhSucSu,cplChiFucSuL,cplChiFucSuR,cplcChaFdcSuL,cplcChaFdcSuR,             & 
& cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,             & 
& cplSucSuVP,cplSucSuVZ,cplAhAhSucSu,cplhhhhSucSu,cplHpmSucHpmcSu,cplSdSucSdcSu,         & 
& cplSeSucSecSu,cplSuSucSucSu,cplSuSvcSucSv,cplSucSuVGVG,cplSucSuVPVP,cplSucSucVWmVWm,   & 
& cplSucSuVZVZ,kont,DerPiSuDR(i1,:,:))

p2 =MSu2OS(i1)
Call DerPi1LoopSu(p2,MSuOS,MSu2OS,MAhOS,MAh2OS,MFuOS,MFu2OS,MChiOS,MChi2OS,           & 
& MChaOS,MCha2OS,MFdOS,MFd2OS,MGluOS,MGlu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,          & 
& MSd2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,MSeOS,MSe2OS,MSvOS,MSv2OS,cplAhSucSu,               & 
& cplChiFucSuL,cplChiFucSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplAhAhSucSu,    & 
& cplhhhhSucSu,cplHpmSucHpmcSu,cplSdSucSdcSu,cplSeSucSecSu,cplSuSucSucSu,cplSuSvcSucSv,  & 
& cplSucSuVGVG,cplSucSuVPVP,cplSucSucVWmVWm,cplSucSuVZVZ,kont,DerPiSuOS(i1,:,:))

DerPiSu(i1,:,:) = DerPiSu(i1,:,:)- DerPiSuDR(i1,:,:) + DerPiSuOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Se
!--------------------------
Do i1=1,6
p2 = MSe2(i1)
Call Pi1LoopSe(p2,MSe,MSe2,MAh,MAh2,MCha,MCha2,MFe,MFe2,MChi,MChi2,Mhh,               & 
& Mhh2,MSv,MSv2,MHpm,MHpm2,MVZ,MVZ2,MVWm,MVWm2,MSd,MSd2,MSu,MSu2,cplAhSecSe,             & 
& cplChaFvcSeL,cplChaFvcSeR,cplChiFecSeL,cplChiFecSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplSvcSeVWm,cplAhAhSecSe,cplhhhhSecSe,cplHpmSecHpmcSe,           & 
& cplSdSecSdcSe,cplSeSecSecSe,cplSeSucSecSu,cplSeSvcSecSv,cplSecSeVPVP,cplSecSecVWmVWm,  & 
& cplSecSeVZVZ,kont,PiSe(i1,:,:))

Call DerPi1LoopSe(p2,MSe,MSe2,MAh,MAh2,MCha,MCha2,MFe,MFe2,MChi,MChi2,Mhh,            & 
& Mhh2,MSv,MSv2,MHpm,MHpm2,MVZ,MVZ2,MVWm,MVWm2,MSd,MSd2,MSu,MSu2,cplAhSecSe,             & 
& cplChaFvcSeL,cplChaFvcSeR,cplChiFecSeL,cplChiFecSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplSvcSeVWm,cplAhAhSecSe,cplhhhhSecSe,cplHpmSecHpmcSe,           & 
& cplSdSecSdcSe,cplSeSecSecSe,cplSeSucSecSu,cplSeSvcSecSv,cplSecSeVPVP,cplSecSecVWmVWm,  & 
& cplSecSeVZVZ,kont,DerPiSe(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopSe(p2,MSe,MSe2,MAh,MAh2,MCha,MCha2,MFe,MFe2,MChi,MChi2,Mhh,            & 
& Mhh2,MSv,MSv2,MHpm,MHpm2,MVZ,MVZ2,MVWm,MVWm2,MSd,MSd2,MSu,MSu2,cplAhSecSe,             & 
& cplChaFvcSeL,cplChaFvcSeR,cplChiFecSeL,cplChiFecSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplSvcSeVWm,cplAhAhSecSe,cplhhhhSecSe,cplHpmSecHpmcSe,           & 
& cplSdSecSdcSe,cplSeSecSecSe,cplSeSucSecSu,cplSeSvcSecSv,cplSecSeVPVP,cplSecSecVWmVWm,  & 
& cplSecSeVZVZ,kont,DerPiSeDR(i1,:,:))

p2 =MSe2OS(i1)
Call DerPi1LoopSe(p2,MSeOS,MSe2OS,MAhOS,MAh2OS,MChaOS,MCha2OS,MFeOS,MFe2OS,           & 
& MChiOS,MChi2OS,MhhOS,Mhh2OS,MSvOS,MSv2OS,MHpmOS,MHpm2OS,MVZOS,MVZ2OS,MVWmOS,           & 
& MVWm2OS,MSdOS,MSd2OS,MSuOS,MSu2OS,cplAhSecSe,cplChaFvcSeL,cplChaFvcSeR,cplChiFecSeL,   & 
& cplChiFecSeR,cplhhSecSe,cplHpmSvcSe,cplSecSeVP,cplSecSeVZ,cplSvcSeVWm,cplAhAhSecSe,    & 
& cplhhhhSecSe,cplHpmSecHpmcSe,cplSdSecSdcSe,cplSeSecSecSe,cplSeSucSecSu,cplSeSvcSecSv,  & 
& cplSecSeVPVP,cplSecSecVWmVWm,cplSecSeVZVZ,kont,DerPiSeOS(i1,:,:))

DerPiSe(i1,:,:) = DerPiSe(i1,:,:)- DerPiSeDR(i1,:,:) + DerPiSeOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!hh
!--------------------------
Do i1=1,3
p2 = Mhh2(i1)
Call Pi1Loophh(p2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MCha,MCha2,MChi,MChi2,MFd,               & 
& MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,             & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplAhAhhhhh,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,         & 
& cplhhhhSvcSv,cplhhhhcVWmVWm,cplhhhhVZVZ,kont,Pihh(i1,:,:))

Pihh(i1,:,:) = Pihh(i1,:,:) + MatTad_hh
Call DerPi1Loophh(p2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MCha,MCha2,MChi,MChi2,MFd,            & 
& MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,             & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplAhAhhhhh,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,         & 
& cplhhhhSvcSv,cplhhhhcVWmVWm,cplhhhhVZVZ,kont,DerPihh(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1Loophh(p2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MCha,MCha2,MChi,MChi2,MFd,            & 
& MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,             & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplAhAhhhhh,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,         & 
& cplhhhhSvcSv,cplhhhhcVWmVWm,cplhhhhVZVZ,kont,DerPihhDR(i1,:,:))

p2 =Mhh2OS(i1)
Call DerPi1Loophh(p2,MAhOS,MAh2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,MChaOS,MCha2OS,           & 
& MChiOS,MChi2OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MHpmOS,MHpm2OS,MVWmOS,           & 
& MVWm2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,cplAhAhhh,cplAhhhhh,       & 
& cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,           & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,              & 
& cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh,cplhhhhhhhh,       & 
& cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplhhhhSvcSv,cplhhhhcVWmVWm,     & 
& cplhhhhVZVZ,kont,DerPihhOS(i1,:,:))

DerPihh(i1,:,:) = DerPihh(i1,:,:)- DerPihhDR(i1,:,:) + DerPihhOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Ah
!--------------------------
Do i1=1,3
p2 = MAh2(i1)
Call Pi1LoopAh(p2,MAh,MAh2,Mhh,Mhh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,               & 
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,    & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,               & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhAhcVWmVWm,cplAhAhVZVZ,        & 
& kont,PiAh(i1,:,:))

Call DerPi1LoopAh(p2,MAh,MAh2,Mhh,Mhh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,    & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,               & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhAhcVWmVWm,cplAhAhVZVZ,        & 
& kont,DerPiAh(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopAh(p2,MAh,MAh2,Mhh,Mhh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,    & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,               & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhAhcVWmVWm,cplAhAhVZVZ,        & 
& kont,DerPiAhDR(i1,:,:))

p2 =MAh2OS(i1)
Call DerPi1LoopAh(p2,MAhOS,MAh2OS,MhhOS,Mhh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,         & 
& MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MVZOS,MVZ2OS,MHpmOS,MHpm2OS,MVWmOS,             & 
& MVWm2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,cplAhAhAh,cplAhAhhh,       & 
& cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,         & 
& cplAhAhSvcSv,cplAhAhcVWmVWm,cplAhAhVZVZ,kont,DerPiAhOS(i1,:,:))

DerPiAh(i1,:,:) = DerPiAh(i1,:,:)- DerPiAhDR(i1,:,:) + DerPiAhOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Hpm
!--------------------------
Do i1=1,2
p2 = MHpm2(i1)
Call Pi1LoopHpm(p2,MHpm,MHpm2,MAh,MAh2,MVWm,MVWm2,MChi,MChi2,MCha,MCha2,              & 
& MFu,MFu2,MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MSu,MSu2,MSd,MSd2,MSv,MSv2,               & 
& MSe,MSe2,cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcgZgWmcHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,   & 
& cplcgZgWpCHpm,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcHpmcSu,        & 
& cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm,& 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplHpmcHpmVPVP,        & 
& cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,kont,PiHpm(i1,:,:))

Call DerPi1LoopHpm(p2,MHpm,MHpm2,MAh,MAh2,MVWm,MVWm2,MChi,MChi2,MCha,MCha2,           & 
& MFu,MFu2,MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MSu,MSu2,MSd,MSd2,MSv,MSv2,               & 
& MSe,MSe2,cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcgZgWmcHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,   & 
& cplcgZgWpCHpm,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcHpmcSu,        & 
& cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm,& 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplHpmcHpmVPVP,        & 
& cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,kont,DerPiHpm(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopHpm(p2,MHpm,MHpm2,MAh,MAh2,MVWm,MVWm2,MChi,MChi2,MCha,MCha2,           & 
& MFu,MFu2,MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MSu,MSu2,MSd,MSd2,MSv,MSv2,               & 
& MSe,MSe2,cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcgZgWmcHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,   & 
& cplcgZgWpCHpm,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcHpmcSu,        & 
& cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm,& 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplHpmcHpmVPVP,        & 
& cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,kont,DerPiHpmDR(i1,:,:))

p2 =MHpm2OS(i1)
Call DerPi1LoopHpm(p2,MHpmOS,MHpm2OS,MAhOS,MAh2OS,MVWmOS,MVWm2OS,MChiOS,              & 
& MChi2OS,MChaOS,MCha2OS,MFuOS,MFu2OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MhhOS,Mhh2OS,            & 
& MVZOS,MVZ2OS,MSuOS,MSu2OS,MSdOS,MSd2OS,MSvOS,MSv2OS,MSeOS,MSe2OS,cplAhHpmcHpm,         & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,  & 
& cplcFvFecHpmR,cplcgZgWmcHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplcgZgWpCHpm,cplhhHpmcHpm,    & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplAhAhHpmcHpm,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,          & 
& cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplHpmcHpmVPVP,cplHpmcHpmcVWmVWm,      & 
& cplHpmcHpmVZVZ,kont,DerPiHpmOS(i1,:,:))

DerPiHpm(i1,:,:) = DerPiHpm(i1,:,:)- DerPiHpmDR(i1,:,:) + DerPiHpmOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Chi
!--------------------------
Do i1=1,5
p2 = MChi2(i1)
Call Sigma1LoopChi(p2,MChi,MChi2,MAh,MAh2,MHpm,MHpm2,MCha,MCha2,MVWm,MVWm2,           & 
& Mhh,Mhh2,MVZ,MVZ2,MSd,MSd2,MFd,MFd2,MSe,MSe2,MFe,MFe2,MSu,MSu2,MFu,MFu2,               & 
& MSv,MSv2,cplChiChiAhL,cplChiChiAhR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,       & 
& cplChiChacVWmR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,       & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplcChaChiVWmL,       & 
& cplcChaChiVWmR,SigmaLChi(i1,:,:),SigmaRChi(i1,:,:),SigmaSLChi(i1,:,:),SigmaSRChi(i1,:,:))

Call DerSigma1LoopChi(p2,MChi,MChi2,MAh,MAh2,MHpm,MHpm2,MCha,MCha2,MVWm,              & 
& MVWm2,Mhh,Mhh2,MVZ,MVZ2,MSd,MSd2,MFd,MFd2,MSe,MSe2,MFe,MFe2,MSu,MSu2,MFu,              & 
& MFu2,MSv,MSv2,cplChiChiAhL,cplChiChiAhR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,  & 
& cplChiChacVWmR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,       & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplcChaChiVWmL,       & 
& cplcChaChiVWmR,DerSigmaLChi(i1,:,:),DerSigmaRChi(i1,:,:),DerSigmaSLChi(i1,:,:)         & 
& ,DerSigmaSRChi(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopChi(p2,MChi,MChi2,MAh,MAh2,MHpm,MHpm2,MCha,MCha2,MVWm,              & 
& MVWm2,Mhh,Mhh2,MVZ,MVZ2,MSd,MSd2,MFd,MFd2,MSe,MSe2,MFe,MFe2,MSu,MSu2,MFu,              & 
& MFu2,MSv,MSv2,cplChiChiAhL,cplChiChiAhR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,  & 
& cplChiChacVWmR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,       & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplcChaChiVWmL,       & 
& cplcChaChiVWmR,DerSigmaLChiDR(i1,:,:),DerSigmaRChiDR(i1,:,:),DerSigmaSLChiDR(i1,:,:)   & 
& ,DerSigmaSRChiDR(i1,:,:))

p2 =MChi2OS(i1)
Call DerSigma1LoopChi(p2,MChiOS,MChi2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChaOS,           & 
& MCha2OS,MVWmOS,MVWm2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,MSdOS,MSd2OS,MFdOS,MFd2OS,            & 
& MSeOS,MSe2OS,MFeOS,MFe2OS,MSuOS,MSu2OS,MFuOS,MFu2OS,MSvOS,MSv2OS,cplChiChiAhL,         & 
& cplChiChiAhR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,              & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,     & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplcChaChiVWmL,cplcChaChiVWmR,     & 
& DerSigmaLChiOS(i1,:,:),DerSigmaRChiOS(i1,:,:),DerSigmaSLChiOS(i1,:,:),DerSigmaSRChiOS(i1,:,:))

DerSigmaLChi(i1,:,:) = DerSigmaLChi(i1,:,:) - DerSigmaLChiDR(i1,:,:)! + DerSigmaLChiOS(i1,:,:)
DerSigmaRChi(i1,:,:) = DerSigmaRChi(i1,:,:) - DerSigmaRChiDR(i1,:,:)! + DerSigmaRChiOS(i1,:,:)
DerSigmaSLChi(i1,:,:) = DerSigmaSLChi(i1,:,:) - DerSigmaSLChiDR(i1,:,:)! + DerSigmaSLChiOS(i1,:,:)
DerSigmaSRChi(i1,:,:) = DerSigmaSRChi(i1,:,:) - DerSigmaSRChiDR(i1,:,:)! + DerSigmaSRChiOS(i1,:,:)
DerSigmaLirChi(i1,:,:) =  + DerSigmaLChiOS(i1,:,:)
DerSigmaRirChi(i1,:,:) =  + DerSigmaRChiOS(i1,:,:)
DerSigmaSLirChi(i1,:,:) = + DerSigmaSLChiOS(i1,:,:)
DerSigmaSRirChi(i1,:,:) = + DerSigmaSRChiOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirChi(i1,:,:) =  0._dp
DerSigmaRirChi(i1,:,:) =  0._dp
DerSigmaSLirChi(i1,:,:) = 0._dp
DerSigmaSRirChi(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Cha
!--------------------------
Do i1=1,2
p2 =MCha2(i1)
Call Sigma1LoopCha(p2,MCha,MCha2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,               & 
& MChi,MChi2,MVWm,MVWm2,MSu,MSu2,MFd,MFd2,MSv,MSv2,MFe,MFe2,MFu,MFu2,MSd,MSd2,           & 
& MSe,MSe2,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,        & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,SigmaLCha(i1,:,:)& 
& ,SigmaRCha(i1,:,:),SigmaSLCha(i1,:,:),SigmaSRCha(i1,:,:))

Call DerSigma1LoopCha(p2,MCha,MCha2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,            & 
& MChi,MChi2,MVWm,MVWm2,MSu,MSu2,MFd,MFd2,MSv,MSv2,MFe,MFe2,MFu,MFu2,MSd,MSd2,           & 
& MSe,MSe2,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,        & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,DerSigmaLCha(i1,:,:)& 
& ,DerSigmaRCha(i1,:,:),DerSigmaSLCha(i1,:,:),DerSigmaSRCha(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopCha(p2,MCha,MCha2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,            & 
& MChi,MChi2,MVWm,MVWm2,MSu,MSu2,MFd,MFd2,MSv,MSv2,MFe,MFe2,MFu,MFu2,MSd,MSd2,           & 
& MSe,MSe2,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,        & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,DerSigmaLChaDR(i1,:,:)& 
& ,DerSigmaRChaDR(i1,:,:),DerSigmaSLChaDR(i1,:,:),DerSigmaSRChaDR(i1,:,:))

p2 =MCha2OS(i1)
Call DerSigma1LoopCha(p2,MChaOS,MCha2OS,MAhOS,MAh2OS,MhhOS,Mhh2OS,MVZOS,              & 
& MVZ2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MVWmOS,MVWm2OS,MSuOS,MSu2OS,MFdOS,MFd2OS,         & 
& MSvOS,MSv2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,cplcChaChaAhL,        & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplcChacFvSeL,cplcChacFvSeR,DerSigmaLChaOS(i1,:,:),DerSigmaRChaOS(i1,:,:)              & 
& ,DerSigmaSLChaOS(i1,:,:),DerSigmaSRChaOS(i1,:,:))

DerSigmaLCha(i1,:,:) = DerSigmaLCha(i1,:,:) - DerSigmaLChaDR(i1,:,:)! + DerSigmaLChaOS(i1,:,:)
DerSigmaRCha(i1,:,:) = DerSigmaRCha(i1,:,:) - DerSigmaRChaDR(i1,:,:)! + DerSigmaRChaOS(i1,:,:)
DerSigmaSLCha(i1,:,:) = DerSigmaSLCha(i1,:,:) - DerSigmaSLChaDR(i1,:,:)! + DerSigmaSLChaOS(i1,:,:)
DerSigmaSRCha(i1,:,:) = DerSigmaSRCha(i1,:,:) - DerSigmaSRChaDR(i1,:,:)! + DerSigmaSRChaOS(i1,:,:)
DerSigmaLirCha(i1,:,:) = + DerSigmaLChaOS(i1,:,:)
DerSigmaRirCha(i1,:,:) = + DerSigmaRChaOS(i1,:,:)
DerSigmaSLirCha(i1,:,:) = + DerSigmaSLChaOS(i1,:,:)
DerSigmaSRirCha(i1,:,:) = + DerSigmaSRChaOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirCha(i1,:,:) = 0._dp
DerSigmaRirCha(i1,:,:) = 0._dp
DerSigmaSLirCha(i1,:,:) = 0._dp
DerSigmaSRirCha(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Fe
!--------------------------
Do i1=1,3
p2 =MFe2(i1)
Call Sigma1LoopFe(p2,MFe,MFe2,MAh,MAh2,MSv,MSv2,MCha,MCha2,MSe,MSe2,MChi,             & 
& MChi2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,    & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,            & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,            & 
& cplcFeFvVWmR,SigmaLFe(i1,:,:),SigmaRFe(i1,:,:),SigmaSLFe(i1,:,:),SigmaSRFe(i1,:,:))

Call DerSigma1LoopFe(p2,MFe,MFe2,MAh,MAh2,MSv,MSv2,MCha,MCha2,MSe,MSe2,               & 
& MChi,MChi2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,           & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,DerSigmaLFe(i1,:,:),DerSigmaRFe(i1,:,:),DerSigmaSLFe(i1,:,:) & 
& ,DerSigmaSRFe(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFe(p2,MFe,MFe2,MAh,MAh2,MSv,MSv2,MCha,MCha2,MSe,MSe2,               & 
& MChi,MChi2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,           & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,DerSigmaLFeDR(i1,:,:),DerSigmaRFeDR(i1,:,:),DerSigmaSLFeDR(i1,:,:)& 
& ,DerSigmaSRFeDR(i1,:,:))

p2 =MFe2OS(i1)
Call DerSigma1LoopFe(p2,MFeOS,MFe2OS,MAhOS,MAh2OS,MSvOS,MSv2OS,MChaOS,MCha2OS,        & 
& MSeOS,MSe2OS,MChiOS,MChi2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,MHpmOS,MHpm2OS,MVWmOS,           & 
& MVWm2OS,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,   & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,DerSigmaLFeOS(i1,:,:)              & 
& ,DerSigmaRFeOS(i1,:,:),DerSigmaSLFeOS(i1,:,:),DerSigmaSRFeOS(i1,:,:))

DerSigmaLFe(i1,:,:) = DerSigmaLFe(i1,:,:) - DerSigmaLFeDR(i1,:,:)! + DerSigmaLFeOS(i1,:,:)
DerSigmaRFe(i1,:,:) = DerSigmaRFe(i1,:,:) - DerSigmaRFeDR(i1,:,:)! + DerSigmaRFeOS(i1,:,:)
DerSigmaSLFe(i1,:,:) = DerSigmaSLFe(i1,:,:) - DerSigmaSLFeDR(i1,:,:)! + DerSigmaSLFeOS(i1,:,:)
DerSigmaSRFe(i1,:,:) = DerSigmaSRFe(i1,:,:) - DerSigmaSRFeDR(i1,:,:)! + DerSigmaSRFeOS(i1,:,:)
DerSigmaLirFe(i1,:,:) = + DerSigmaLFeOS(i1,:,:)
DerSigmaRirFe(i1,:,:) = + DerSigmaRFeOS(i1,:,:)
DerSigmaSLirFe(i1,:,:) = + DerSigmaSLFeOS(i1,:,:)
DerSigmaSRirFe(i1,:,:) = + DerSigmaSRFeOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFe(i1,:,:) = 0._dp
DerSigmaRirFe(i1,:,:) = 0._dp
DerSigmaSLirFe(i1,:,:) = 0._dp
DerSigmaSRirFe(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Fd
!--------------------------
Do i1=1,3
p2 =MFd2(i1)
Call Sigma1LoopFd(p2,MFd,MFd2,MAh,MAh2,MSu,MSu2,MCha,MCha2,MSd,MSd2,MChi,             & 
& MChi2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MFu,MFu2,MVWm,MVWm2,MGlu,MGlu2,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdhhL,           & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,SigmaLFd(i1,:,:),SigmaRFd(i1,:,:),SigmaSLFd(i1,:,:),SigmaSRFd(i1,:,:))

Call DerSigma1LoopFd(p2,MFd,MFd2,MAh,MAh2,MSu,MSu2,MCha,MCha2,MSd,MSd2,               & 
& MChi,MChi2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MFu,MFu2,MVWm,MVWm2,MGlu,MGlu2,cplcFdFdAhL,    & 
& cplcFdFdAhR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdhhL,           & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,DerSigmaLFd(i1,:,:),DerSigmaRFd(i1,:,:),DerSigmaSLFd(i1,:,:)              & 
& ,DerSigmaSRFd(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFd(p2,MFd,MFd2,MAh,MAh2,MSu,MSu2,MCha,MCha2,MSd,MSd2,               & 
& MChi,MChi2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MFu,MFu2,MVWm,MVWm2,MGlu,MGlu2,cplcFdFdAhL,    & 
& cplcFdFdAhR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdhhL,           & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,DerSigmaLFdDR(i1,:,:),DerSigmaRFdDR(i1,:,:),DerSigmaSLFdDR(i1,:,:)        & 
& ,DerSigmaSRFdDR(i1,:,:))

p2 =MFd2OS(i1)
Call DerSigma1LoopFd(p2,MFdOS,MFd2OS,MAhOS,MAh2OS,MSuOS,MSu2OS,MChaOS,MCha2OS,        & 
& MSdOS,MSd2OS,MChiOS,MChi2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,MHpmOS,MHpm2OS,MFuOS,            & 
& MFu2OS,MVWmOS,MVWm2OS,MGluOS,MGlu2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFdChaSuL,             & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,DerSigmaLFdOS(i1,:,:) & 
& ,DerSigmaRFdOS(i1,:,:),DerSigmaSLFdOS(i1,:,:),DerSigmaSRFdOS(i1,:,:))

DerSigmaLFd(i1,:,:) = DerSigmaLFd(i1,:,:) - DerSigmaLFdDR(i1,:,:)! + DerSigmaLFdOS(i1,:,:)
DerSigmaRFd(i1,:,:) = DerSigmaRFd(i1,:,:) - DerSigmaRFdDR(i1,:,:)! + DerSigmaRFdOS(i1,:,:)
DerSigmaSLFd(i1,:,:) = DerSigmaSLFd(i1,:,:) - DerSigmaSLFdDR(i1,:,:)! + DerSigmaSLFdOS(i1,:,:)
DerSigmaSRFd(i1,:,:) = DerSigmaSRFd(i1,:,:) - DerSigmaSRFdDR(i1,:,:)! + DerSigmaSRFdOS(i1,:,:)
DerSigmaLirFd(i1,:,:) = + DerSigmaLFdOS(i1,:,:)
DerSigmaRirFd(i1,:,:) = + DerSigmaRFdOS(i1,:,:)
DerSigmaSLirFd(i1,:,:) = + DerSigmaSLFdOS(i1,:,:)
DerSigmaSRirFd(i1,:,:) = + DerSigmaSRFdOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFd(i1,:,:) = 0._dp
DerSigmaRirFd(i1,:,:) = 0._dp
DerSigmaSLirFd(i1,:,:) = 0._dp
DerSigmaSRirFd(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Fu
!--------------------------
Do i1=1,3
p2 =MFu2(i1)
Call Sigma1LoopFu(p2,MFu,MFu2,MAh,MAh2,MSu,MSu2,MChi,MChi2,MHpm,MHpm2,MFd,            & 
& MFd2,MVWm,MVWm2,Mhh,Mhh2,MVZ,MVZ2,MGlu,MGlu2,MCha,MCha2,MSd,MSd2,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,       & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,           & 
& cplcChacFuSdR,SigmaLFu(i1,:,:),SigmaRFu(i1,:,:),SigmaSLFu(i1,:,:),SigmaSRFu(i1,:,:))

Call DerSigma1LoopFu(p2,MFu,MFu2,MAh,MAh2,MSu,MSu2,MChi,MChi2,MHpm,MHpm2,             & 
& MFd,MFd2,MVWm,MVWm2,Mhh,Mhh2,MVZ,MVZ2,MGlu,MGlu2,MCha,MCha2,MSd,MSd2,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,       & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,           & 
& cplcChacFuSdR,DerSigmaLFu(i1,:,:),DerSigmaRFu(i1,:,:),DerSigmaSLFu(i1,:,:)             & 
& ,DerSigmaSRFu(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFu(p2,MFu,MFu2,MAh,MAh2,MSu,MSu2,MChi,MChi2,MHpm,MHpm2,             & 
& MFd,MFd2,MVWm,MVWm2,Mhh,Mhh2,MVZ,MVZ2,MGlu,MGlu2,MCha,MCha2,MSd,MSd2,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,       & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,           & 
& cplcChacFuSdR,DerSigmaLFuDR(i1,:,:),DerSigmaRFuDR(i1,:,:),DerSigmaSLFuDR(i1,:,:)       & 
& ,DerSigmaSRFuDR(i1,:,:))

p2 =MFu2OS(i1)
Call DerSigma1LoopFu(p2,MFuOS,MFu2OS,MAhOS,MAh2OS,MSuOS,MSu2OS,MChiOS,MChi2OS,        & 
& MHpmOS,MHpm2OS,MFdOS,MFd2OS,MVWmOS,MVWm2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,MGluOS,           & 
& MGlu2OS,MChaOS,MCha2OS,MSdOS,MSd2OS,cplcFuFuAhL,cplcFuFuAhR,cplcFuChiSuL,              & 
& cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,      & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,DerSigmaLFuOS(i1,:,:)& 
& ,DerSigmaRFuOS(i1,:,:),DerSigmaSLFuOS(i1,:,:),DerSigmaSRFuOS(i1,:,:))

DerSigmaLFu(i1,:,:) = DerSigmaLFu(i1,:,:) - DerSigmaLFuDR(i1,:,:)! + DerSigmaLFuOS(i1,:,:)
DerSigmaRFu(i1,:,:) = DerSigmaRFu(i1,:,:) - DerSigmaRFuDR(i1,:,:)! + DerSigmaRFuOS(i1,:,:)
DerSigmaSLFu(i1,:,:) = DerSigmaSLFu(i1,:,:) - DerSigmaSLFuDR(i1,:,:)! + DerSigmaSLFuOS(i1,:,:)
DerSigmaSRFu(i1,:,:) = DerSigmaSRFu(i1,:,:) - DerSigmaSRFuDR(i1,:,:)! + DerSigmaSRFuOS(i1,:,:)
DerSigmaLirFu(i1,:,:) = + DerSigmaLFuOS(i1,:,:)
DerSigmaRirFu(i1,:,:) = + DerSigmaRFuOS(i1,:,:)
DerSigmaSLirFu(i1,:,:) = + DerSigmaSLFuOS(i1,:,:)
DerSigmaSRirFu(i1,:,:) = + DerSigmaSRFuOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFu(i1,:,:) = 0._dp
DerSigmaRirFu(i1,:,:) = 0._dp
DerSigmaSLirFu(i1,:,:) = 0._dp
DerSigmaSRirFu(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Glu
!--------------------------
p2 = MGlu2
Call Sigma1LoopGlu(p2,MSd,MSd2,MFd,MFd2,MSu,MSu2,MFu,MFu2,MGlu,MGlu2,cplGluFdcSdL,    & 
& cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,         & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,SigmaLGlu,SigmaRGlu,SigmaSLGlu,SigmaSRGlu)

Call DerSigma1LoopGlu(p2,MSd,MSd2,MFd,MFd2,MSu,MSu2,MFu,MFu2,MGlu,MGlu2,              & 
& cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,         & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,DerSigmaLGlu,DerSigmaRGlu,         & 
& DerSigmaSLGlu,DerSigmaSRGlu)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopGlu(p2,MSd,MSd2,MFd,MFd2,MSu,MSu2,MFu,MFu2,MGlu,MGlu2,              & 
& cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,         & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,DerSigmaLGluDR,DerSigmaRGluDR,     & 
& DerSigmaSLGluDR,DerSigmaSRGluDR)

p2 = MGlu2OS
Call DerSigma1LoopGlu(p2,MSdOS,MSd2OS,MFdOS,MFd2OS,MSuOS,MSu2OS,MFuOS,MFu2OS,         & 
& MGluOS,MGlu2OS,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,       & 
& cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,DerSigmaLGluOS,       & 
& DerSigmaRGluOS,DerSigmaSLGluOS,DerSigmaSRGluOS)

DerSigmaLGlu = DerSigmaLGlu - DerSigmaLGluDR !+ DerSigmaLGluOS
DerSigmaRGlu = DerSigmaRGlu - DerSigmaRGluDR !+ DerSigmaRGluOS
DerSigmaSLGlu = DerSigmaSLGlu - DerSigmaSLGluDR !+ DerSigmaSLGluOS
DerSigmaSRGlu = DerSigmaSRGlu - DerSigmaSRGluDR !+ DerSigmaSRGluOS
DerSigmaLirGlu = + DerSigmaLGluOS
DerSigmaRirGlu = + DerSigmaRGluOS
DerSigmaSLirGlu = + DerSigmaSLGluOS
DerSigmaSRirGlu = + DerSigmaSRGluOS
IRdivonly=.False. 
Else 
DerSigmaLirGlu = 0._dp
DerSigmaRirGlu = 0._dp
DerSigmaSLirGlu = 0._dp
DerSigmaSRirGlu = 0._dp 
End if 
!--------------------------
!Fv
!--------------------------
Do i1=1,3
p2 =0._dp
Call Sigma1LoopFv(p2,MSv,MSv2,MChi,MChi2,MHpm,MHpm2,MFe,MFe2,MVWm,MVWm2,              & 
& MVZ,MVZ2,MCha,MCha2,MSe,MSe2,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,    & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcChacFvSeL,cplcChacFvSeR,       & 
& SigmaLFv(i1,:,:),SigmaRFv(i1,:,:),SigmaSLFv(i1,:,:),SigmaSRFv(i1,:,:))

Call DerSigma1LoopFv(p2,MSv,MSv2,MChi,MChi2,MHpm,MHpm2,MFe,MFe2,MVWm,MVWm2,           & 
& MVZ,MVZ2,MCha,MCha2,MSe,MSe2,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,    & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcChacFvSeL,cplcChacFvSeR,       & 
& DerSigmaLFv(i1,:,:),DerSigmaRFv(i1,:,:),DerSigmaSLFv(i1,:,:),DerSigmaSRFv(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFv(p2,MSv,MSv2,MChi,MChi2,MHpm,MHpm2,MFe,MFe2,MVWm,MVWm2,           & 
& MVZ,MVZ2,MCha,MCha2,MSe,MSe2,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,    & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcChacFvSeL,cplcChacFvSeR,       & 
& DerSigmaLFvDR(i1,:,:),DerSigmaRFvDR(i1,:,:),DerSigmaSLFvDR(i1,:,:),DerSigmaSRFvDR(i1,:,:))

p2 =0._dp
Call DerSigma1LoopFv(p2,MSvOS,MSv2OS,MChiOS,MChi2OS,MHpmOS,MHpm2OS,MFeOS,             & 
& MFe2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,MChaOS,MCha2OS,MSeOS,MSe2OS,cplcFvChiSvL,           & 
& cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,      & 
& cplcFvFvVZR,cplcChacFvSeL,cplcChacFvSeR,DerSigmaLFvOS(i1,:,:),DerSigmaRFvOS(i1,:,:)    & 
& ,DerSigmaSLFvOS(i1,:,:),DerSigmaSRFvOS(i1,:,:))

DerSigmaLFv(i1,:,:) = DerSigmaLFv(i1,:,:) - DerSigmaLFvDR(i1,:,:)! + DerSigmaLFvOS(i1,:,:)
DerSigmaRFv(i1,:,:) = DerSigmaRFv(i1,:,:) - DerSigmaRFvDR(i1,:,:)! + DerSigmaRFvOS(i1,:,:)
DerSigmaSLFv(i1,:,:) = DerSigmaSLFv(i1,:,:) - DerSigmaSLFvDR(i1,:,:)! + DerSigmaSLFvOS(i1,:,:)
DerSigmaSRFv(i1,:,:) = DerSigmaSRFv(i1,:,:) - DerSigmaSRFvDR(i1,:,:)! + DerSigmaSRFvOS(i1,:,:)
DerSigmaLirFv(i1,:,:) = + DerSigmaLFvOS(i1,:,:)
DerSigmaRirFv(i1,:,:) = + DerSigmaRFvOS(i1,:,:)
DerSigmaSLirFv(i1,:,:) = + DerSigmaSLFvOS(i1,:,:)
DerSigmaSRirFv(i1,:,:) = + DerSigmaSRFvOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFv(i1,:,:) = 0._dp
DerSigmaRirFv(i1,:,:) = 0._dp
DerSigmaSLirFv(i1,:,:) = 0._dp
DerSigmaSRirFv(i1,:,:) = 0._dp
End if
End do


!--------------------------
!VG
!--------------------------
p2 = MVG2
Call Pi1LoopVG(p2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,MSd,MSd2,MSu,MSu2,cplcFdFdVGL,         & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplGluGluVGL,cplGluGluVGR,              & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplSdcSdVGVG,cplSucSuVGVG,cplVGVGVGVG1,cplVGVGVGVG2,   & 
& cplVGVGVGVG3,kont,PiVG)

Call DerPi1LoopVG(p2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,MSd,MSd2,MSu,MSu2,cplcFdFdVGL,      & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplGluGluVGL,cplGluGluVGR,              & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplSdcSdVGVG,cplSucSuVGVG,cplVGVGVGVG1,cplVGVGVGVG2,   & 
& cplVGVGVGVG3,kont,DerPiVG)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVG(p2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,MSd,MSd2,MSu,MSu2,cplcFdFdVGL,      & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplGluGluVGL,cplGluGluVGR,              & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplSdcSdVGVG,cplSucSuVGVG,cplVGVGVGVG1,cplVGVGVGVG2,   & 
& cplVGVGVGVG3,kont,DerPiVGDR)

p2 = 0.
Call DerPi1LoopVG(p2,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MSdOS,MSd2OS,           & 
& MSuOS,MSu2OS,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,               & 
& cplGluGluVGL,cplGluGluVGR,cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplSdcSdVGVG,cplSucSuVGVG,   & 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,kont,DerPiVGOS)

DerPiVG = DerPiVG-DerPiVGDR + DerPiVGOS
IRdivonly=.False. 
End if 
!--------------------------
!VP
!--------------------------
p2 = MVP2
Call Pi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,              & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,PiVP)

Call DerPi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,           & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVP)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,           & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVPDR)

p2 = 0.
Call DerPi1LoopVP(p2,MChaOS,MCha2OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,           & 
& MHpmOS,MHpm2OS,MVWmOS,MVWm2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,MSuOS,MSu2OS,cplcChaChaVPL,    & 
& cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,GcplHpmcHpmVP,GcplHpmcVWmVP,cplSdcSdVP,        & 
& cplSecSeVP,cplSucSuVP,cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,           & 
& cplSucSuVPVP,cplcVWmVPVPVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVPOS)

DerPiVP = DerPiVP-DerPiVPDR + DerPiVPOS
IRdivonly=.False. 
End if 
!--------------------------
!VZ
!--------------------------
p2 = MVZ2
Call Pi1LoopVZ(p2,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,               & 
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,PiVZ)

Call DerPi1LoopVZ(p2,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,DerPiVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZ(p2,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,DerPiVZDR)

p2 = MVZ2OS
Call DerPi1LoopVZ(p2,MhhOS,Mhh2OS,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,         & 
& MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MVZOS,MVZ2OS,MHpmOS,MHpm2OS,MVWmOS,             & 
& MVWm2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,cplAhhhVZ,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,           & 
& cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,GcplHpmcHpmVZ,GcplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,            & 
& cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpmcHpmVZVZ,             & 
& cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,   & 
& cplcVWmVWmVZVZ3,kont,DerPiVZOS)

DerPiVZ = DerPiVZ-DerPiVZDR + DerPiVZOS
IRdivonly=.False. 
End if 
!--------------------------
!VWm
!--------------------------
p2 = MVWm2
Call Pi1LoopVWm(p2,MHpm,MHpm2,MAh,MAh2,MChi,MChi2,MCha,MCha2,MFu,MFu2,MFd,            & 
& MFd2,MFe,MFe2,Mhh,Mhh2,MVWm,MVWm2,MVZ,MVZ2,MSu,MSu2,MSd,MSd2,MSv,MSv2,MSe,             & 
& MSe2,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,           & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm, & 
& cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,             & 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm3,       & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,& 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,PiVWm)

Call DerPi1LoopVWm(p2,MHpm,MHpm2,MAh,MAh2,MChi,MChi2,MCha,MCha2,MFu,MFu2,             & 
& MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVWm,MVWm2,MVZ,MVZ2,MSu,MSu2,MSd,MSd2,MSv,MSv2,             & 
& MSe,MSe2,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm, & 
& cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,             & 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm3,       & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,& 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,DerPiVWm)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVWm(p2,MHpm,MHpm2,MAh,MAh2,MChi,MChi2,MCha,MCha2,MFu,MFu2,             & 
& MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVWm,MVWm2,MVZ,MVZ2,MSu,MSu2,MSd,MSd2,MSv,MSv2,             & 
& MSe,MSe2,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm, & 
& cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,             & 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm3,       & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,& 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,DerPiVWmDR)

p2 = MVWm2OS
Call DerPi1LoopVWm(p2,MHpmOS,MHpm2OS,MAhOS,MAh2OS,MChiOS,MChi2OS,MChaOS,              & 
& MCha2OS,MFuOS,MFu2OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MhhOS,Mhh2OS,MVWmOS,MVWm2OS,            & 
& MVZOS,MVZ2OS,MSuOS,MSu2OS,MSdOS,MSd2OS,MSvOS,MSv2OS,MSeOS,MSe2OS,GcplAhHpmcVWm,        & 
& cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,               & 
& cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,               & 
& GcplhhHpmcVWm,cplhhcVWmVWm,GcplHpmcVWmVP,GcplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,      & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,             & 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm3,       & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,& 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,DerPiVWmOS)

DerPiVWm = DerPiVWm-DerPiVWmDR + DerPiVWmOS
IRdivonly=.False. 
End if 
!--------------------------
! Additional Self-Energies for Photon
!--------------------------
p2 = 0._dp
OnlyLightStates = .True. 
Call Pi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,              & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,PiVPlight0)

Call DerPi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,           & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVPlight0)

OnlyLightStates = .False. 
p2 = 0._dp
OnlyHeavyStates = .True. 
Call Pi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,              & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,PiVPheavy0)

Call DerPi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,           & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVPheavy0)

OnlyHeavyStates = .False. 
p2 = MVZ2
OnlyLightStates = .True. 
Call Pi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,              & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,PiVPlightMZ)

Call DerPi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,           & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVPlightMZ)

OnlyLightStates = .False. 
p2 = MVZ2
OnlyHeavyStates = .True. 
Call Pi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,              & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,PiVPheavyMZ)

Call DerPi1LoopVP(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MVWm,           & 
& MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcVWmVPVWm,cplHpmcHpmVPVP,cplSdcSdVPVP,cplSecSeVPVP,cplSucSuVPVP,cplcVWmVPVPVWm3,    & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,DerPiVPheavyMZ)

OnlyHeavyStates = .False. 
!--------------------------
!VP
!--------------------------
p2 = MVZ2
Call Pi1LoopVPVZ(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MSd,             & 
& MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,           & 
& cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHpmVPVWm,      & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,             & 
& cplcVWmVWmVZ,cplHpmcHpmVP,cplHpmcHpmVPVZ,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,       & 
& cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,      & 
& cplSucSuVPVZ,cplSucSuVZ,kont,PiVPVZ)

Call DerPi1LoopVPVZ(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,              & 
& MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,       & 
& cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHpmVPVWm,      & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,             & 
& cplcVWmVWmVZ,cplHpmcHpmVP,cplHpmcHpmVPVZ,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,       & 
& cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,      & 
& cplSucSuVPVZ,cplSucSuVZ,kont,DerPiVPVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVPVZ(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,              & 
& MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,       & 
& cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHpmVPVWm,      & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,             & 
& cplcVWmVWmVZ,cplHpmcHpmVP,cplHpmcHpmVPVZ,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,       & 
& cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,      & 
& cplSucSuVPVZ,cplSucSuVZ,kont,DerPiVPVZDR)

p2 =MVZ2OS
Call DerPi1LoopVPVZ(p2,MChaOS,MCha2OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,         & 
& MHpmOS,MHpm2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,MSuOS,MSu2OS,MVWmOS,MVWm2OS,cplcChaChaVPL,    & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,         & 
& cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,          & 
& cplcgWpCgWpCVZ,GcplcHpmVPVWm,GcplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,               & 
& cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmVWmVZ,GcplHpmcHpmVP,cplHpmcHpmVPVZ,             & 
& GcplHpmcHpmVZ,GcplHpmcVWmVP,GcplHpmcVWmVZ,cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,          & 
& cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,cplSucSuVPVZ,cplSucSuVZ,kont,            & 
& DerPiVPVZOS)

DerPiVPVZ = DerPiVPVZ- DerPiVPVZDR + DerPiVPVZOS
IRdivonly=.False. 
End if
p2 = 0._dp 
Call Pi1LoopVPVZ(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,MSd,             & 
& MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,           & 
& cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHpmVPVWm,      & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,             & 
& cplcVWmVWmVZ,cplHpmcHpmVP,cplHpmcHpmVPVZ,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,       & 
& cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,      & 
& cplSucSuVPVZ,cplSucSuVZ,kont,PiVZVP)

Call DerPi1LoopVPVZ(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,              & 
& MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,       & 
& cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHpmVPVWm,      & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,             & 
& cplcVWmVWmVZ,cplHpmcHpmVP,cplHpmcHpmVPVZ,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,       & 
& cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,      & 
& cplSucSuVPVZ,cplSucSuVZ,kont,DerPiVZVP)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVPVZ(p2,MCha,MCha2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHpm,MHpm2,              & 
& MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,       & 
& cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHpmVPVWm,      & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,             & 
& cplcVWmVWmVZ,cplHpmcHpmVP,cplHpmcHpmVPVZ,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,       & 
& cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,      & 
& cplSucSuVPVZ,cplSucSuVZ,kont,DerPiVPVZDR)

p2 = 0._dp 
Call DerPi1LoopVPVZ(p2,MChaOS,MCha2OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,         & 
& MHpmOS,MHpm2OS,MSdOS,MSd2OS,MSeOS,MSe2OS,MSuOS,MSu2OS,MVWmOS,MVWm2OS,cplcChaChaVPL,    & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,         & 
& cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,          & 
& cplcgWpCgWpCVZ,GcplcHpmVPVWm,GcplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVPVWmVZ1,               & 
& cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmVWmVZ,GcplHpmcHpmVP,cplHpmcHpmVPVZ,             & 
& GcplHpmcHpmVZ,GcplHpmcVWmVP,GcplHpmcVWmVZ,cplSdcSdVP,cplSdcSdVPVZ,cplSdcSdVZ,          & 
& cplSecSeVP,cplSecSeVPVZ,cplSecSeVZ,cplSucSuVP,cplSucSuVPVZ,cplSucSuVZ,kont,            & 
& DerPiVPVZOS)

DerPiVPVZ = DerPiVPVZ- DerPiVPVZDR + DerPiVPVZOS
IRdivonly=.False. 
End if
!--------------------------
!VZ
!--------------------------
Do i1=1,3
p2 = Mhh2(i1)
Call Pi1LoopVZhh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,             & 
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,               & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmcHpmVZ,    & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,PiVZhh(i1,:,:))

Call DerPi1LoopVZhh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmcHpmVZ,    & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,DerPiVZhh(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZhh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmcHpmVZ,    & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,DerPiVZhhDR(i1,:,:))

p2 =Mhh2OS(i1)
Call DerPi1LoopVZhh(p2,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,MFdOS,              & 
& MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,MSd2OS,             & 
& MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,MVWmOS,MVWm2OS,cplAhhhhh,cplAhhhVZ,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,     & 
& GcplcHpmVWmVZ,cplcVWmVWmVZ,GcplhhcHpmVWm,cplhhcVWmVWm,GcplhhHpmcHpm,GcplhhHpmcVWm,     & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,GcplHpmcHpmVZ,GcplHpmcVWmVZ,               & 
& cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,DerPiVZhhOS(i1,:,:))

DerPiVZhh(i1,:,:) = DerPiVZhh(i1,:,:)- DerPiVZhhDR(i1,:,:) + DerPiVZhhOS(i1,:,:)
IRdivonly=.False. 
End if
End do
p2 = MVZ2
Call Pi1LoopVZhh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,             & 
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,               & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmcHpmVZ,    & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,PihhVZ)

Call DerPi1LoopVZhh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmcHpmVZ,    & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,DerPihhVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZhh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmcHpmVZ,    & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,DerPiVZhhDR)

p2 =MVZ2OS
Call DerPi1LoopVZhh(p2,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,MFdOS,              & 
& MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,MSd2OS,             & 
& MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,MVWmOS,MVWm2OS,cplAhhhhh,cplAhhhVZ,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,     & 
& GcplcHpmVWmVZ,cplcVWmVWmVZ,GcplhhcHpmVWm,cplhhcVWmVWm,GcplhhHpmcHpm,GcplhhHpmcVWm,     & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,GcplHpmcHpmVZ,GcplHpmcVWmVZ,               & 
& cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,kont,DerPiVZhhOS)

DerPiVZhh = DerPiVZhh- DerPiVZhhDR + DerPiVZhhOS
IRdivonly=.False. 
End if
!--------------------------
!VZ
!--------------------------
Do i1=1,3
p2 = MAh2(i1)
Call Pi1LoopVZAh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,             & 
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,MVZ,MVZ2,               & 
& cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCAh,cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcHpmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,              & 
& cplSecSeVZ,cplSucSuVZ,kont,PiVZAh(i1,:,:))

Call DerPi1LoopVZAh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,MVZ,MVZ2,           & 
& cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCAh,cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcHpmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,              & 
& cplSecSeVZ,cplSucSuVZ,kont,DerPiVZAh(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZAh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,MVZ,MVZ2,           & 
& cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCAh,cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcHpmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,              & 
& cplSecSeVZ,cplSucSuVZ,kont,DerPiVZAhDR(i1,:,:))

p2 =MAh2OS(i1)
Call DerPi1LoopVZAh(p2,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,MFdOS,              & 
& MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,MSd2OS,             & 
& MSeOS,MSe2OS,MSuOS,MSu2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,cplAhAhhh,GcplAhcHpmVWm,         & 
& cplAhhhVZ,GcplAhHpmcHpm,GcplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,  & 
& cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdVZL,         & 
& cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuAhL,               & 
& cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,cplcgWmgWmVZ,cplcgWpCgWpCAh,          & 
& cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,cplChiChiVZR,GcplcHpmVWmVZ,      & 
& cplhhVZVZ,GcplHpmcHpmVZ,GcplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,kont,           & 
& DerPiVZAhOS(i1,:,:))

DerPiVZAh(i1,:,:) = DerPiVZAh(i1,:,:)- DerPiVZAhDR(i1,:,:) + DerPiVZAhOS(i1,:,:)
IRdivonly=.False. 
End if
End do
p2 = MVZ2
Call Pi1LoopVZAh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,             & 
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,MVZ,MVZ2,               & 
& cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCAh,cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcHpmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,              & 
& cplSecSeVZ,cplSucSuVZ,kont,PiAhVZ)

Call DerPi1LoopVZAh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,MVZ,MVZ2,           & 
& cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCAh,cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcHpmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,              & 
& cplSecSeVZ,cplSucSuVZ,kont,DerPiAhVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZAh(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MVWm,MVWm2,MVZ,MVZ2,           & 
& cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCAh,cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcHpmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,              & 
& cplSecSeVZ,cplSucSuVZ,kont,DerPiVZAhDR)

p2 =MVZ2OS
Call DerPi1LoopVZAh(p2,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,MFdOS,              & 
& MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,MSd2OS,             & 
& MSeOS,MSe2OS,MSuOS,MSu2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,cplAhAhhh,GcplAhcHpmVWm,         & 
& cplAhhhVZ,GcplAhHpmcHpm,GcplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,  & 
& cplcChaChaAhR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdVZL,         & 
& cplcFdFdVZR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuAhL,               & 
& cplcFuFuAhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmAh,cplcgWmgWmVZ,cplcgWpCgWpCAh,          & 
& cplcgWpCgWpCVZ,cplChiChiAhL,cplChiChiAhR,cplChiChiVZL,cplChiChiVZR,GcplcHpmVWmVZ,      & 
& cplhhVZVZ,GcplHpmcHpmVZ,GcplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,kont,           & 
& DerPiVZAhOS)

DerPiVZAh = DerPiVZAh- DerPiVZAhDR + DerPiVZAhOS
IRdivonly=.False. 
End if
!--------------------------
!VWm
!--------------------------
Do i1=1,2
p2 = MHpm2(i1)
Call Pi1LoopVWmHpm(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,      & 
& cplcFvFecHpmR,cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,  & 
& cplcgZgWpCVWm,cplChiChacHpmL,cplChiChacHpmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhHpmcHpm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcHpmcSu,cplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,PiVWmHpm(i1,:,:))

Call DerPi1LoopVWmHpm(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,      & 
& cplcFvFecHpmR,cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,  & 
& cplcgZgWpCVWm,cplChiChacHpmL,cplChiChacHpmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhHpmcHpm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcHpmcSu,cplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,DerPiVWmHpm(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVWmHpm(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,      & 
& cplcFvFecHpmR,cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,  & 
& cplcgZgWpCVWm,cplChiChacHpmL,cplChiChacHpmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhHpmcHpm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcHpmcSu,cplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,DerPiVWmHpmDR(i1,:,:))

p2 =MHpm2OS(i1)
Call DerPi1LoopVWmHpm(p2,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,MFdOS,            & 
& MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,MSd2OS,             & 
& MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,GcplAhcHpmVWm,      & 
& GcplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,    & 
& cplcFeFvVWmR,GcplcFuFdcHpmL,GcplcFuFdcHpmR,GcplcFvFecHpmL,GcplcFvFecHpmR,              & 
& cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,cplcgZgWpCVWm,  & 
& GcplChiChacHpmL,GcplChiChacHpmR,GcplcHpmVPVWm,GcplcHpmVWmVZ,cplcVWmVPVWm,              & 
& cplcVWmVWmVZ,GcplhhcHpmVWm,cplhhcVWmVWm,GcplhhHpmcHpm,GcplHpmcHpmVP,GcplHpmcHpmVZ,     & 
& GcplSdcHpmcSu,GcplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,DerPiVWmHpmOS(i1,:,:))

DerPiVWmHpm(i1,:,:) = DerPiVWmHpm(i1,:,:)- DerPiVWmHpmDR(i1,:,:) + DerPiVWmHpmOS(i1,:,:)
IRdivonly=.False. 
End if
End do
p2 = MVWm2
Call Pi1LoopVWmHpm(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,      & 
& cplcFvFecHpmR,cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,  & 
& cplcgZgWpCVWm,cplChiChacHpmL,cplChiChacHpmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhHpmcHpm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcHpmcSu,cplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,PiHpmVWm)

Call DerPi1LoopVWmHpm(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,      & 
& cplcFvFecHpmR,cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,  & 
& cplcgZgWpCVWm,cplChiChacHpmL,cplChiChacHpmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhHpmcHpm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcHpmcSu,cplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,DerPiHpmVWm)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVWmHpm(p2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,      & 
& cplcFvFecHpmR,cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,  & 
& cplcgZgWpCVWm,cplChiChacHpmL,cplChiChacHpmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhHpmcHpm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcHpmcSu,cplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,DerPiVWmHpmDR)

p2 =MVWm2OS
Call DerPi1LoopVWmHpm(p2,MAhOS,MAh2OS,MChaOS,MCha2OS,MChiOS,MChi2OS,MFdOS,            & 
& MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MHpmOS,MHpm2OS,MSdOS,MSd2OS,             & 
& MSeOS,MSe2OS,MSuOS,MSu2OS,MSvOS,MSv2OS,MVWmOS,MVWm2OS,MVZOS,MVZ2OS,GcplAhcHpmVWm,      & 
& GcplAhHpmcHpm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,    & 
& cplcFeFvVWmR,GcplcFuFdcHpmL,GcplcFuFdcHpmR,GcplcFvFecHpmL,GcplcFvFecHpmR,              & 
& cplcgAgWpCVWm,cplcgWmgZVWm,cplcgWpCgAcHpm,cplcgWpCgZcHpm,cplcgZgWmcHpm,cplcgZgWpCVWm,  & 
& GcplChiChacHpmL,GcplChiChacHpmR,GcplcHpmVPVWm,GcplcHpmVWmVZ,cplcVWmVPVWm,              & 
& cplcVWmVWmVZ,GcplhhcHpmVWm,cplhhcVWmVWm,GcplhhHpmcHpm,GcplHpmcHpmVP,GcplHpmcHpmVZ,     & 
& GcplSdcHpmcSu,GcplSecHpmcSv,cplSucSdVWm,cplSvcSeVWm,kont,DerPiVWmHpmOS)

DerPiVWmHpm = DerPiVWmHpm- DerPiVWmHpmDR + DerPiVWmHpmOS
IRdivonly=.False. 
End if
! -----------------------------------------------------------
! Calculate now all wave-function renormalisation constants 
! -----------------------------------------------------------


!  ######    VG    ###### 
ZfVG = -DerPiVG


!  ######    fG    ###### 
ZffG = -SigmaRGlu + &
& -MGlu*(MGlu*DerSigmaRGlu+MGlu*DerSigmaLGlu+DerSigmaSRGlu+DerSigmaSLGlu)
If (OSkinematics) Then 
ZffG = ZffG &
& + -MGluOS*(MGluOS*DerSigmaRirGlu+MGluOS*DerSigmaLirGlu+(DerSigmaSRirGlu+DerSigmaSLirGlu))
Else 
ZffG = ZffG &
& + -MGlu*(MGlu*DerSigmaRirGlu+MGlu*DerSigmaLirGlu+(DerSigmaSRirGlu+DerSigmaSLirGlu))
End if 


!  ######    FvL    ###### 
Do i1=1,3
  Do i2=1,3
   If (i1.eq.i2) Then 
     ZfFvL(i1,i2) = -SigmaRFv(i2,i1,i2) 
   Else 
     ZfFvL(i1,i2) = 0._dp 
   End if 
  End Do 
End Do 


!  ######    VP    ###### 
ZfVP = -DerPiVP


!  ######    VZ    ###### 
ZfVZ = -DerPiVZ


!  ######    VWm    ###### 
ZfVWm = -DerPiVWm


!  ######    Sd    ###### 
Do i1=1,6
  Do i2=1,6
   If ((i1.eq.i2).or.(MSd(i1).eq.MSd(i2))) Then 
       ZfSd(i1,i2) = -DerPiSd(i1,i1,i2)
   Else 
       ZfSd(i1,i2) = 2._dp/(MSd2(i1)-MSd2(i2))*PiSd(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    Sv    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MSv(i1).eq.MSv(i2))) Then 
       ZfSv(i1,i2) = -DerPiSv(i1,i1,i2)
   Else 
       ZfSv(i1,i2) = 2._dp/(MSv2(i1)-MSv2(i2))*PiSv(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    Su    ###### 
Do i1=1,6
  Do i2=1,6
   If ((i1.eq.i2).or.(MSu(i1).eq.MSu(i2))) Then 
       ZfSu(i1,i2) = -DerPiSu(i1,i1,i2)
   Else 
       ZfSu(i1,i2) = 2._dp/(MSu2(i1)-MSu2(i2))*PiSu(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    Se    ###### 
Do i1=1,6
  Do i2=1,6
   If ((i1.eq.i2).or.(MSe(i1).eq.MSe(i2))) Then 
       ZfSe(i1,i2) = -DerPiSe(i1,i1,i2)
   Else 
       ZfSe(i1,i2) = 2._dp/(MSe2(i1)-MSe2(i2))*PiSe(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    hh    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(Mhh(i1).eq.Mhh(i2))) Then 
       Zfhh(i1,i2) = -DerPihh(i1,i1,i2)
   Else 
       Zfhh(i1,i2) = 2._dp/(Mhh2(i1)-Mhh2(i2))*Pihh(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    Ah    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MAh(i1).eq.MAh(i2))) Then 
       ZfAh(i1,i2) = -DerPiAh(i1,i1,i2)
   Else 
       ZfAh(i1,i2) = 2._dp/(MAh2(i1)-MAh2(i2))*PiAh(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    Hpm    ###### 
Do i1=1,2
  Do i2=1,2
   If ((i1.eq.i2).or.(MHpm(i1).eq.MHpm(i2))) Then 
       ZfHpm(i1,i2) = -DerPiHpm(i1,i1,i2)
   Else 
       ZfHpm(i1,i2) = 2._dp/(MHpm2(i1)-MHpm2(i2))*PiHpm(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    L0    ###### 
Do i1=1,5
  Do i2=1,5
   If ((i1.eq.i2).or.(MChi(i1).eq.MChi(i2))) Then 
     ZfL0(i1,i2) = -SigmaRChi(i2,i1,i2) &
      & -MChi2(i1)*(DerSigmaRChi(i2,i1,i2) + DerSigmaLChi(i2,i1,i2))&
      & -MChi(i1)*(DerSigmaSRChi(i2,i1,i2)+DerSigmaSLChi(i2,i1,i2))
     If (OSkinematics) Then 
     ZfL0(i1,i2) = ZfL0(i1,i2) &
      & -MChi2OS(i1)*(DerSigmaRirChi(i2,i1,i2) + DerSigmaLirChi(i2,i1,i2))&
      & -MChiOS(i1)*(DerSigmaSRirChi(i2,i1,i2)+DerSigmaSLirChi(i2,i1,i2))
     Else 
     ZfL0(i1,i2) = ZfL0(i1,i2) &
      & -MChi2(i1)*(DerSigmaRirChi(i2,i1,i2) + DerSigmaLirChi(i2,i1,i2))&
      & -MChi(i1)*(DerSigmaSRirChi(i2,i1,i2)+DerSigmaSLirChi(i2,i1,i2))
     End if 
   Else 
     ZfL0(i1,i2) = 2._dp/(MChi2(i1) - MChi2(i2))* &
      & (MChi2(i2)*SigmaRChi(i2,i1,i2) + MChi(i1)*MChi(i2)*SigmaLChi(i2,i1,i2) + MChi(i1)*SigmaSRChi(i2,i1,i2) + MChi(i2)*SigmaSLChi(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    Lm    ###### 
Do i1=1,2
  Do i2=1,2
   If ((i1.eq.i2).or.(MCha(i1).eq.MCha(i2))) Then 
     ZfLm(i1,i2) = -SigmaRCha(i2,i1,i2) &
      & -MCha2(i1)*(DerSigmaRCha(i2,i1,i2) + DerSigmaLCha(i2,i1,i2))&
      & -MCha(i1)*(DerSigmaSRCha(i2,i1,i2)+DerSigmaSLCha(i2,i1,i2))
     If (OSkinematics) Then 
     ZfLm(i1,i2) = ZfLm(i1,i2) &
      & -MCha2OS(i1)*(DerSigmaRirCha(i2,i1,i2) + DerSigmaLirCha(i2,i1,i2))&
      & -MChaOS(i1)*(DerSigmaSRirCha(i2,i1,i2)+DerSigmaSLirCha(i2,i1,i2))
     Else 
     ZfLm(i1,i2) = ZfLm(i1,i2) &
      & -MCha2(i1)*(DerSigmaRirCha(i2,i1,i2) + DerSigmaLirCha(i2,i1,i2))&
      & -MCha(i1)*(DerSigmaSRirCha(i2,i1,i2)+DerSigmaSLirCha(i2,i1,i2))
     End if 
   Else 
     ZfLm(i1,i2) = 2._dp/(MCha2(i1) - MCha2(i2))* &
      & (MCha2(i2)*SigmaRCha(i2,i1,i2) + MCha(i1)*MCha(i2)*SigmaLCha(i2,i1,i2) + MCha(i1)*SigmaSRCha(i2,i1,i2) + MCha(i2)*SigmaSLCha(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    Lp    ###### 
Do i1=1,2
  Do i2=1,2
   If ((i1.eq.i2).or.(MCha(i1).eq.MCha(i2))) Then 
     ZfLp(i1,i2) = -SigmaLCha(i2,i1,i2) &
      & -MCha2(i1)*(DerSigmaLCha(i2,i1,i2) + DerSigmaRCha(i2,i1,i2))&
      & -MCha(i1)*(DerSigmaSLCha(i2,i1,i2)+DerSigmaSRCha(i2,i1,i2))
     If (OSkinematics) Then 
     ZfLp(i1,i2) = ZfLp(i1,i2) &
      & -MCha2OS(i1)*(DerSigmaLirCha(i2,i1,i2) + DerSigmaRirCha(i2,i1,i2))&
      & -MChaOS(i1)*(DerSigmaSLirCha(i2,i1,i2)+DerSigmaSRirCha(i2,i1,i2))
     Else 
     ZfLp(i1,i2) = ZfLp(i1,i2) &
      & -MCha2(i1)*(DerSigmaLirCha(i2,i1,i2) + DerSigmaRirCha(i2,i1,i2))&
      & -MCha(i1)*(DerSigmaSLirCha(i2,i1,i2)+DerSigmaSRirCha(i2,i1,i2))
     End if 
   Else 
     ZfLp(i1,i2) = 2._dp/(MCha2(i1) - MCha2(i2))* &
      & (MCha2(i2)*SigmaLCha(i2,i1,i2) + MCha(i1)*MCha(i2)*SigmaRCha(i2,i1,i2) + MCha(i1)*SigmaSLCha(i2,i1,i2) + MCha(i2)*SigmaSRCha(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    FEL    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFe(i1).eq.MFe(i2))) Then 
     ZfFEL(i1,i2) = -SigmaRFe(i2,i1,i2) &
      & -MFe2(i1)*(DerSigmaRFe(i2,i1,i2) + DerSigmaLFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSRFe(i2,i1,i2)+DerSigmaSLFe(i2,i1,i2))
     If (OSkinematics) Then 
     ZfFEL(i1,i2) = ZfFEL(i1,i2) &
      & -MFe2OS(i1)*(DerSigmaRirFe(i2,i1,i2) + DerSigmaLirFe(i2,i1,i2))&
      & -MFeOS(i1)*(DerSigmaSRirFe(i2,i1,i2)+DerSigmaSLirFe(i2,i1,i2))
     Else 
     ZfFEL(i1,i2) = ZfFEL(i1,i2) &
      & -MFe2(i1)*(DerSigmaRirFe(i2,i1,i2) + DerSigmaLirFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSRirFe(i2,i1,i2)+DerSigmaSLirFe(i2,i1,i2))
     End if 
   Else 
     ZfFEL(i1,i2) = 2._dp/(MFe2(i1) - MFe2(i2))* &
      & (MFe2(i2)*SigmaRFe(i2,i1,i2) + MFe(i1)*MFe(i2)*SigmaLFe(i2,i1,i2) + MFe(i1)*SigmaSRFe(i2,i1,i2) + MFe(i2)*SigmaSLFe(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    FER    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFe(i1).eq.MFe(i2))) Then 
     ZfFER(i1,i2) = -SigmaLFe(i2,i1,i2) &
      & -MFe2(i1)*(DerSigmaLFe(i2,i1,i2) + DerSigmaRFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSLFe(i2,i1,i2)+DerSigmaSRFe(i2,i1,i2))
     If (OSkinematics) Then 
     ZfFER(i1,i2) = ZfFER(i1,i2) &
      & -MFe2OS(i1)*(DerSigmaLirFe(i2,i1,i2) + DerSigmaRirFe(i2,i1,i2))&
      & -MFeOS(i1)*(DerSigmaSLirFe(i2,i1,i2)+DerSigmaSRirFe(i2,i1,i2))
     Else 
     ZfFER(i1,i2) = ZfFER(i1,i2) &
      & -MFe2(i1)*(DerSigmaLirFe(i2,i1,i2) + DerSigmaRirFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSLirFe(i2,i1,i2)+DerSigmaSRirFe(i2,i1,i2))
     End if 
   Else 
     ZfFER(i1,i2) = 2._dp/(MFe2(i1) - MFe2(i2))* &
      & (MFe2(i2)*SigmaLFe(i2,i1,i2) + MFe(i1)*MFe(i2)*SigmaRFe(i2,i1,i2) + MFe(i1)*SigmaSLFe(i2,i1,i2) + MFe(i2)*SigmaSRFe(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    FDL    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFd(i1).eq.MFd(i2))) Then 
     ZfFDL(i1,i2) = -SigmaRFd(i2,i1,i2) &
      & -MFd2(i1)*(DerSigmaRFd(i2,i1,i2) + DerSigmaLFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSRFd(i2,i1,i2)+DerSigmaSLFd(i2,i1,i2))
     If (OSkinematics) Then 
     ZfFDL(i1,i2) = ZfFDL(i1,i2) &
      & -MFd2OS(i1)*(DerSigmaRirFd(i2,i1,i2) + DerSigmaLirFd(i2,i1,i2))&
      & -MFdOS(i1)*(DerSigmaSRirFd(i2,i1,i2)+DerSigmaSLirFd(i2,i1,i2))
     Else 
     ZfFDL(i1,i2) = ZfFDL(i1,i2) &
      & -MFd2(i1)*(DerSigmaRirFd(i2,i1,i2) + DerSigmaLirFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSRirFd(i2,i1,i2)+DerSigmaSLirFd(i2,i1,i2))
     End if 
   Else 
     ZfFDL(i1,i2) = 2._dp/(MFd2(i1) - MFd2(i2))* &
      & (MFd2(i2)*SigmaRFd(i2,i1,i2) + MFd(i1)*MFd(i2)*SigmaLFd(i2,i1,i2) + MFd(i1)*SigmaSRFd(i2,i1,i2) + MFd(i2)*SigmaSLFd(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    FDR    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFd(i1).eq.MFd(i2))) Then 
     ZfFDR(i1,i2) = -SigmaLFd(i2,i1,i2) &
      & -MFd2(i1)*(DerSigmaLFd(i2,i1,i2) + DerSigmaRFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSLFd(i2,i1,i2)+DerSigmaSRFd(i2,i1,i2))
     If (OSkinematics) Then 
     ZfFDR(i1,i2) = ZfFDR(i1,i2) &
      & -MFd2OS(i1)*(DerSigmaLirFd(i2,i1,i2) + DerSigmaRirFd(i2,i1,i2))&
      & -MFdOS(i1)*(DerSigmaSLirFd(i2,i1,i2)+DerSigmaSRirFd(i2,i1,i2))
     Else 
     ZfFDR(i1,i2) = ZfFDR(i1,i2) &
      & -MFd2(i1)*(DerSigmaLirFd(i2,i1,i2) + DerSigmaRirFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSLirFd(i2,i1,i2)+DerSigmaSRirFd(i2,i1,i2))
     End if 
   Else 
     ZfFDR(i1,i2) = 2._dp/(MFd2(i1) - MFd2(i2))* &
      & (MFd2(i2)*SigmaLFd(i2,i1,i2) + MFd(i1)*MFd(i2)*SigmaRFd(i2,i1,i2) + MFd(i1)*SigmaSLFd(i2,i1,i2) + MFd(i2)*SigmaSRFd(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    FUL    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFu(i1).eq.MFu(i2))) Then 
     ZfFUL(i1,i2) = -SigmaRFu(i2,i1,i2) &
      & -MFu2(i1)*(DerSigmaRFu(i2,i1,i2) + DerSigmaLFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSRFu(i2,i1,i2)+DerSigmaSLFu(i2,i1,i2))
     If (OSkinematics) Then 
     ZfFUL(i1,i2) = ZfFUL(i1,i2) &
      & -MFu2OS(i1)*(DerSigmaRirFu(i2,i1,i2) + DerSigmaLirFu(i2,i1,i2))&
      & -MFuOS(i1)*(DerSigmaSRirFu(i2,i1,i2)+DerSigmaSLirFu(i2,i1,i2))
     Else 
     ZfFUL(i1,i2) = ZfFUL(i1,i2) &
      & -MFu2(i1)*(DerSigmaRirFu(i2,i1,i2) + DerSigmaLirFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSRirFu(i2,i1,i2)+DerSigmaSLirFu(i2,i1,i2))
     End if 
   Else 
     ZfFUL(i1,i2) = 2._dp/(MFu2(i1) - MFu2(i2))* &
      & (MFu2(i2)*SigmaRFu(i2,i1,i2) + MFu(i1)*MFu(i2)*SigmaLFu(i2,i1,i2) + MFu(i1)*SigmaSRFu(i2,i1,i2) + MFu(i2)*SigmaSLFu(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    FUR    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFu(i1).eq.MFu(i2))) Then 
     ZfFUR(i1,i2) = -SigmaLFu(i2,i1,i2) &
      & -MFu2(i1)*(DerSigmaLFu(i2,i1,i2) + DerSigmaRFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSLFu(i2,i1,i2)+DerSigmaSRFu(i2,i1,i2))
     If (OSkinematics) Then 
     ZfFUR(i1,i2) = ZfFUR(i1,i2) &
      & -MFu2OS(i1)*(DerSigmaLirFu(i2,i1,i2) + DerSigmaRirFu(i2,i1,i2))&
      & -MFuOS(i1)*(DerSigmaSLirFu(i2,i1,i2)+DerSigmaSRirFu(i2,i1,i2))
     Else 
     ZfFUR(i1,i2) = ZfFUR(i1,i2) &
      & -MFu2(i1)*(DerSigmaLirFu(i2,i1,i2) + DerSigmaRirFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSLirFu(i2,i1,i2)+DerSigmaSRirFu(i2,i1,i2))
     End if 
   Else 
     ZfFUR(i1,i2) = 2._dp/(MFu2(i1) - MFu2(i2))* &
      & (MFu2(i2)*SigmaLFu(i2,i1,i2) + MFu(i1)*MFu(i2)*SigmaRFu(i2,i1,i2) + MFu(i1)*SigmaSLFu(i2,i1,i2) + MFu(i2)*SigmaSRFu(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    VPVZ    ###### 
ZfVPVZ = 2._dp*PiVPVZ/(MVP2-MVZ2 )
ZfVZVP = 2._dp*PiVZVP/(MVZ2-MVP2 )
! -----------------------------------------------------------
! Setting the Counter-Terms 
! -----------------------------------------------------------
! ----------- getting the divergent pieces ---------

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG221(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,g1D)

TwoLoopRGEsave=TwoLoopRGE 
TwoLoopRGE=.False. 
Call rge221(221,0._dp,g1D,g1D) 
TwoLoopRGE=TwoLoopRGEsave 
Call GToParameters221(g1D,dg1,dg2,dg3,dYd,dYe,dlam,dkap,dYu,dTd,dTe,dTlam,            & 
& dTk,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,dvS)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
dg1 = Sqrt(3._dp/5._dp)*dg1 
! ----------------------- 
 

 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
dg1 = 0.5_dp*divergence*dg1 
dg2 = 0.5_dp*divergence*dg2 
dg3 = 0.5_dp*divergence*dg3 
dYd = 0.5_dp*divergence*dYd 
dTd = 0.5_dp*divergence*dTd 
dYe = 0.5_dp*divergence*dYe 
dTe = 0.5_dp*divergence*dTe 
dlam = 0.5_dp*divergence*dlam 
dTlam = 0.5_dp*divergence*dTlam 
dkap = 0.5_dp*divergence*dkap 
dTk = 0.5_dp*divergence*dTk 
dYu = 0.5_dp*divergence*dYu 
dTu = 0.5_dp*divergence*dTu 
dmq2 = 0.5_dp*divergence*dmq2 
dml2 = 0.5_dp*divergence*dml2 
dmHd2 = 0.5_dp*divergence*dmHd2 
dmHu2 = 0.5_dp*divergence*dmHu2 
dmd2 = 0.5_dp*divergence*dmd2 
dmu2 = 0.5_dp*divergence*dmu2 
dme2 = 0.5_dp*divergence*dme2 
dms2 = 0.5_dp*divergence*dms2 
dM1 = 0.5_dp*divergence*dM1 
dM2 = 0.5_dp*divergence*dM2 
dM3 = 0.5_dp*divergence*dM3 
dvd = 0.5_dp*divergence*dvd 
dvu = 0.5_dp*divergence*dvu 
dvS = 0.5_dp*divergence*dvS 
dpG = 0._dp 
dZD = 0._dp 
dZV = 0._dp 
dZU = 0._dp 
dZE = 0._dp 
dZH = 0._dp 
dZA = 0._dp 
dZP = 0._dp 
dZN = 0._dp 
dUM = 0._dp 
dUP = 0._dp 
dZEL = 0._dp 
dZER = 0._dp 
dZDL = 0._dp 
dZDR = 0._dp 
dZUL = 0._dp 
dZUR = 0._dp 
dSinTW = 0._dp 
dCosTW = 0._dp 
dTanTW = 0._dp 
If (CTinLoopDecays) Then 
dCosTW = ((PiVWm/MVWM**2 - PiVZ/mVZ**2)*Cos(TW))/2._dp 
dSinTW = -(dCosTW*1/Tan(TW)) 
dg2 = (g2*(derPiVPheavy0 + PiVPlightMZ/MVZ**2 - (-(PiVWm/MVWm**2) + PiVZ/MVZ**2)*1/Tan(TW)**2 + (2*PiVZVP*Tan(TW))/MVZ**2))/2._dp 
dg1 = dSinTW*g2*1/Cos(TW) + dg2*Tan(TW) - dCosTW*g2*1/Cos(TW)*Tan(TW) 
End if 
 
dUM = 0.25_dp*MatMul(ZfLm- Conjg(Transpose(ZfLm)),UM)
dUP = 0.25_dp*MatMul(ZfLp- Conjg(Transpose(ZfLp)),UP)
dZA = 0.25_dp*MatMul(ZfAh- Conjg(Transpose(ZfAh)),ZA)
dZD = 0.25_dp*MatMul(ZfSd- Conjg(Transpose(ZfSd)),ZD)
dZDL = 0.25_dp*MatMul(ZfFDL- Conjg(Transpose(ZfFDL)),ZDL)
dZDR = 0.25_dp*MatMul(ZfFDR- Conjg(Transpose(ZfFDR)),ZDR)
dZE = 0.25_dp*MatMul(ZfSe- Conjg(Transpose(ZfSe)),ZE)
dZEL = 0.25_dp*MatMul(ZfFEL- Conjg(Transpose(ZfFEL)),ZEL)
dZER = 0.25_dp*MatMul(ZfFER- Conjg(Transpose(ZfFER)),ZER)
dZH = 0.25_dp*MatMul(Zfhh- Conjg(Transpose(Zfhh)),ZH)
dZN = 0.25_dp*MatMul(ZfL0- Conjg(Transpose(ZfL0)),ZN)
dZP = 0.25_dp*MatMul(ZfHpm- Conjg(Transpose(ZfHpm)),ZP)
dZU = 0.25_dp*MatMul(ZfSu- Conjg(Transpose(ZfSu)),ZU)
dZUL = 0.25_dp*MatMul(ZfFUL- Conjg(Transpose(ZfFUL)),ZUL)
dZUR = 0.25_dp*MatMul(ZfFUR- Conjg(Transpose(ZfFUR)),ZUR)
dZV = 0.25_dp*MatMul(ZfSv- Conjg(Transpose(ZfSv)),ZV)


! -----------------------------------------------------------
! Calculating the CT vertices 
! -----------------------------------------------------------
Call CalculateCouplingCT(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,Yd,Td,               & 
& ZD,Ye,Te,ZE,Yu,Tu,ZU,ZV,TW,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,dlam,dTlam,          & 
& dkap,dTk,dvd,dvu,dvS,dZA,dg1,dg2,dZH,dZP,dYd,dTd,dZD,dYe,dTe,dZE,dYu,dTu,              & 
& dZU,dZV,dSinTW,dCosTW,dTanTW,dg3,dUM,dUP,dZN,dZDL,dZDR,dZEL,dZER,dZUL,dZUR,            & 
& dpG,ctcplAhAhAh,ctcplAhAhhh,ctcplAhhhhh,ctcplAhHpmcHpm,ctcplAhSdcSd,ctcplAhSecSe,      & 
& ctcplAhSucSu,ctcplhhhhhh,ctcplhhHpmcHpm,ctcplhhSdcSd,ctcplhhSecSe,ctcplhhSucSu,        & 
& ctcplhhSvcSv,ctcplHpmSucSd,ctcplHpmSvcSe,ctcplSdcHpmcSu,ctcplSecHpmcSv,ctcplAhhhVZ,    & 
& ctcplAhHpmcVWm,ctcplAhcHpmVWm,ctcplhhHpmcVWm,ctcplhhcHpmVWm,ctcplHpmcHpmVP,            & 
& ctcplHpmcHpmVZ,ctcplSdcSdVG,ctcplSdcSdVP,ctcplSdcSdVZ,ctcplSdcSucVWm,ctcplSecSeVP,     & 
& ctcplSecSeVZ,ctcplSecSvcVWm,ctcplSucSuVG,ctcplSucSuVP,ctcplSucSdVWm,ctcplSucSuVZ,      & 
& ctcplSvcSeVWm,ctcplSvcSvVZ,ctcplhhcVWmVWm,ctcplhhVZVZ,ctcplHpmcVWmVP,ctcplHpmcVWmVZ,   & 
& ctcplcHpmVPVWm,ctcplcHpmVWmVZ,ctcplVGVGVG,ctcplcVWmVPVWm,ctcplcVWmVWmVZ,               & 
& ctcplcChaChaAhL,ctcplcChaChaAhR,ctcplChiChiAhL,ctcplChiChiAhR,ctcplcFdFdAhL,           & 
& ctcplcFdFdAhR,ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplChiChacHpmL,& 
& ctcplChiChacHpmR,ctcplChaFucSdL,ctcplChaFucSdR,ctcplChaFvcSeL,ctcplChaFvcSeR,          & 
& ctcplcChaChahhL,ctcplcChaChahhR,ctcplcFdChaSuL,ctcplcFdChaSuR,ctcplcFeChaSvL,          & 
& ctcplcFeChaSvR,ctcplChiChihhL,ctcplChiChihhR,ctcplChiFdcSdL,ctcplChiFdcSdR,            & 
& ctcplChiFecSeL,ctcplChiFecSeR,ctcplChiFucSuL,ctcplChiFucSuR,ctcplChiFvcSvL,            & 
& ctcplChiFvcSvR,ctcplcChaChiHpmL,ctcplcChaChiHpmR,ctcplcFdChiSdL,ctcplcFdChiSdR,        & 
& ctcplcFeChiSeL,ctcplcFeChiSeR,ctcplcFuChiSuL,ctcplcFuChiSuR,ctcplcFvChiSvL,            & 
& ctcplcFvChiSvR,ctcplGluFdcSdL,ctcplGluFdcSdR,ctcplcFdFdhhL,ctcplcFdFdhhR,              & 
& ctcplcChaFdcSuL,ctcplcChaFdcSuR,ctcplcFuFdcHpmL,ctcplcFuFdcHpmR,ctcplcFeFehhL,         & 
& ctcplcFeFehhR,ctcplcChaFecSvL,ctcplcChaFecSvR,ctcplcFvFecHpmL,ctcplcFvFecHpmR,         & 
& ctcplGluFucSuL,ctcplGluFucSuR,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFuHpmL,              & 
& ctcplcFdFuHpmR,ctcplcFeFvHpmL,ctcplcFeFvHpmR,ctcplcFdGluSdL,ctcplcFdGluSdR,            & 
& ctcplcFuGluSuL,ctcplcFuGluSuR,ctcplcChacFuSdL,ctcplcChacFuSdR,ctcplcChacFvSeL,         & 
& ctcplcChacFvSeR,ctcplChiChacVWmL,ctcplChiChacVWmR,ctcplcChaChaVPL,ctcplcChaChaVPR,     & 
& ctcplcChaChaVZL,ctcplcChaChaVZR,ctcplChiChiVZL,ctcplChiChiVZR,ctcplcChaChiVWmL,        & 
& ctcplcChaChiVWmR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,ctcplcFdFdVPR,              & 
& ctcplcFdFdVZL,ctcplcFdFdVZR,ctcplcFuFdcVWmL,ctcplcFuFdcVWmR,ctcplcFeFeVPL,             & 
& ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFvFecVWmL,ctcplcFvFecVWmR,             & 
& ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFdFuVWmL,ctcplcFdFuVWmR, & 
& ctcplcFuFuVZL,ctcplcFuFuVZR,ctcplcFeFvVWmL,ctcplcFeFvVWmR,ctcplcFvFvVZL,               & 
& ctcplcFvFvVZR,ctcplGluGluVGL,ctcplGluGluVGR)

End Subroutine WaveFunctionRenormalisation 
Subroutine CalculateOneLoopDecays(gP1LSd,gP1LSu,gP1LSe,gP1LSv,gP1Lhh,gP1LAh,          & 
& gP1LHpm,gP1LGlu,gP1LChi,gP1LCha,gP1LFu,MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,         & 
& MSeOS,MSe2OS,MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,           & 
& MCha2OS,MFeOS,MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,            & 
& MVWmOS,MVWm2OS,ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,          & 
& ZDLOS,ZDROS,ZULOS,ZUROS,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,              & 
& Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,epsI,deltaM,kont)

Implicit None 
Real(dp), Intent(in) :: epsI, deltaM 
Integer, Intent(inout) :: kont 
Real(dp) :: MLambda, em, gs, vSM, sinW2, g1SM, g2SM 
Integer :: divset, i1 
Complex(dp) :: divvalue, YuSM(3,3), YdSM(3,3), YeSM(3,3) 
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(inout) :: vd,vu,vS

Real(dp) :: dg1,dg2,dg3,dmHd2,dmHu2,dms2,dvd,dvu,dvS,dZH(3,3),dZA(3,3),dZP(2,2),dSinTW,           & 
& dCosTW,dTanTW

Complex(dp) :: dYd(3,3),dTd(3,3),dYe(3,3),dTe(3,3),dlam,dTlam,dkap,dTk,dYu(3,3),dTu(3,3),            & 
& dmq2(3,3),dml2(3,3),dmd2(3,3),dmu2(3,3),dme2(3,3),dM1,dM2,dM3,dpG,dZD(6,6),            & 
& dZV(3,3),dZU(6,6),dZE(6,6),dZN(5,5),dUM(2,2),dUP(2,2),dZEL(3,3),dZER(3,3),             & 
& dZDL(3,3),dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp) :: ZfVG,ZffG,ZfFvL(3,3),ZfVP,ZfVZ,ZfVWm,ZfSd(6,6),ZfSv(3,3),ZfSu(6,6),ZfSe(6,6),         & 
& Zfhh(3,3),ZfAh(3,3),ZfHpm(2,2),ZfL0(5,5),ZfLm(2,2),ZfLp(2,2),ZfFEL(3,3),               & 
& ZfFER(3,3),ZfFDL(3,3),ZfFDR(3,3),ZfFUL(3,3),ZfFUR(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MSdOS(6),MSd2OS(6),MSvOS(3),MSv2OS(3),MSuOS(6),MSu2OS(6),MSeOS(6),MSe2OS(6),          & 
& MhhOS(3),Mhh2OS(3),MAhOS(3),MAh2OS(3),MHpmOS(2),MHpm2OS(2),MChiOS(5),MChi2OS(5),       & 
& MChaOS(2),MCha2OS(2),MFeOS(3),MFe2OS(3),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),         & 
& MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(3,3),ZAOS(3,3),ZPOS(2,2)

Complex(dp),Intent(in) :: ZDOS(6,6),ZVOS(3,3),ZUOS(6,6),ZEOS(6,6),ZNOS(5,5),UMOS(2,2),UPOS(2,2),ZELOS(3,3),     & 
& ZEROS(3,3),ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3)

Real(dp) :: p2, q2, q2_save 
Real(dp) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp) :: cplAhAhAhAh1(3,3,3,3),cplAhAhAhhh1(3,3,3,3),cplAhAhhhhh1(3,3,3,3),cplAhAhHpmcHpm1(3,3,2,2),& 
& cplAhAhSdcSdaa(3,3,6,6),cplAhAhSecSe1(3,3,6,6),cplAhAhSucSuaa(3,3,6,6),cplAhAhSvcSv1(3,3,3,3),& 
& cplAhhhhhhh1(3,3,3,3),cplAhhhHpmcHpm1(3,3,2,2),cplAhhhSdcSdaa(3,3,6,6),cplAhhhSecSe1(3,3,6,6),& 
& cplAhhhSucSuaa(3,3,6,6),cplAhHpmSucSdaa(3,2,6,6),cplAhHpmSvcSe1(3,2,3,6),              & 
& cplAhSdcHpmcSuaa(3,6,2,6),cplAhSecHpmcSv1(3,6,2,3),cplhhhhhhhh1(3,3,3,3),              & 
& cplhhhhHpmcHpm1(3,3,2,2),cplhhhhSdcSdaa(3,3,6,6),cplhhhhSecSe1(3,3,6,6),               & 
& cplhhhhSucSuaa(3,3,6,6),cplhhhhSvcSv1(3,3,3,3),cplhhHpmSucSdaa(3,2,6,6),               & 
& cplhhHpmSvcSe1(3,2,3,6),cplhhSdcHpmcSuaa(3,6,2,6),cplhhSecHpmcSv1(3,6,2,3),            & 
& cplHpmHpmcHpmcHpm1(2,2,2,2),cplHpmSdcHpmcSdaa(2,6,2,6),cplHpmSecHpmcSe1(2,6,2,6),      & 
& cplHpmSucHpmcSuaa(2,6,2,6),cplHpmSvcHpmcSv1(2,3,2,3),cplSdSdcSdcSdabba(6,6,6,6),       & 
& cplSdSdcSdcSdabab(6,6,6,6),cplSdSecSdcSeaa(6,6,6,6),cplSdSucSdcSuabba(6,6,6,6),        & 
& cplSdSucSdcSuabab(6,6,6,6),cplSdSvcSdcSvaa(6,3,6,3),cplSdSvcSecSuaa(6,3,6,6),          & 
& cplSeSecSecSe1(6,6,6,6),cplSeSucSdcSvaa(6,6,6,3),cplSeSucSecSuaa(6,6,6,6),             & 
& cplSeSvcSecSv1(6,3,6,3),cplSuSucSucSuabba(6,6,6,6),cplSuSucSucSuabab(6,6,6,6),         & 
& cplSuSvcSucSvaa(6,3,6,3),cplSvSvcSvcSv1(3,3,3,3),cplAhAhcVWmVWm1(3,3),cplAhAhVZVZ1(3,3),& 
& cplAhHpmcVWmVP1(3,2),cplAhHpmcVWmVZ1(3,2),cplAhcHpmVPVWm1(3,2),cplAhcHpmVWmVZ1(3,2),   & 
& cplhhhhcVWmVWm1(3,3),cplhhhhVZVZ1(3,3),cplhhHpmcVWmVP1(3,2),cplhhHpmcVWmVZ1(3,2),      & 
& cplhhcHpmVPVWm1(3,2),cplhhcHpmVWmVZ1(3,2),cplHpmcHpmVPVP1(2,2),cplHpmcHpmVPVZ1(2,2),   & 
& cplHpmcHpmcVWmVWm1(2,2),cplHpmcHpmVZVZ1(2,2),cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1(6,6),& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1(6,6),cplSdcSdVGVPLamct3ct2ct1(6,6),          & 
& cplSdcSdVGVZLamct3ct2ct1(6,6),cplSdcSucVWmVGLamct4ct2ct1(6,6),cplSdcSdVPVPaa(6,6),     & 
& cplSdcSdVPVZaa(6,6),cplSdcSucVWmVPaa(6,6),cplSdcSdcVWmVWmaa(6,6),cplSdcSdVZVZaa(6,6),  & 
& cplSdcSucVWmVZaa(6,6),cplSecSeVPVP1(6,6),cplSecSeVPVZ1(6,6),cplSecSvcVWmVP1(6,3),      & 
& cplSecSecVWmVWm1(6,6),cplSecSeVZVZ1(6,6),cplSecSvcVWmVZ1(6,3),cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1(6,6),& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1(6,6),cplSucSuVGVPLamct3ct2ct1(6,6),          & 
& cplSucSdVGVWmLamct3ct2ct1(6,6),cplSucSuVGVZLamct3ct2ct1(6,6),cplSucSuVPVPaa(6,6),      & 
& cplSucSdVPVWmaa(6,6),cplSucSuVPVZaa(6,6),cplSucSdVWmVZaa(6,6),cplSucSucVWmVWmaa(6,6),  & 
& cplSucSuVZVZaa(6,6),cplSvcSeVPVWm1(3,6),cplSvcSeVWmVZ1(3,6),cplSvcSvcVWmVWm1(3,3),     & 
& cplSvcSvVZVZ1(3,3),cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWmVPVPVWm1Q,         & 
& cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,  & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ1Q,          & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q

Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplhhSvcSv(3,3,3),               & 
& cplHpmSucSd(2,6,6),cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),         & 
& cplAhAhAhAh(3,3,3,3),cplAhAhAhhh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),& 
& cplAhAhSdcSd(3,3,6,6),cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplAhAhSvcSv(3,3,3,3),& 
& cplAhhhhhhh(3,3,3,3),cplAhhhHpmcHpm(3,3,2,2),cplAhhhSdcSd(3,3,6,6),cplAhhhSecSe(3,3,6,6),& 
& cplAhhhSucSu(3,3,6,6),cplAhHpmSucSd(3,2,6,6),cplAhHpmSvcSe(3,2,3,6),cplAhSdcHpmcSu(3,6,2,6),& 
& cplAhSecHpmcSv(3,6,2,3),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),cplhhhhSdcSd(3,3,6,6),& 
& cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplhhhhSvcSv(3,3,3,3),cplhhHpmSucSd(3,2,6,6),& 
& cplhhHpmSvcSe(3,2,3,6),cplhhSdcHpmcSu(3,6,2,6),cplhhSecHpmcSv(3,6,2,3),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSdSvcSdcSv(6,3,6,3),cplSdSvcSecSu(6,3,6,6),cplSeSecSecSe(6,6,6,6),cplSeSucSdcSv(6,6,6,3),& 
& cplSeSucSecSu(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSuSvcSucSv(6,3,6,3),& 
& cplSvSvcSvcSv(3,3,3,3),cplAhhhVZ(3,3),cplAhHpmcVWm(3,2),cplAhcHpmVWm(3,2),             & 
& cplhhHpmcVWm(3,2),cplhhcHpmVWm(3,2),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),               & 
& cplSdcSdVG(6,6),cplSdcSdVP(6,6),cplSdcSdVZ(6,6),cplSdcSucVWm(6,6),cplSecSeVP(6,6),     & 
& cplSecSeVZ(6,6),cplSecSvcVWm(6,3),cplSucSuVG(6,6),cplSucSuVP(6,6),cplSucSdVWm(6,6),    & 
& cplSucSuVZ(6,6),cplSvcSeVWm(3,6),cplSvcSvVZ(3,3),cplhhcVWmVWm(3),cplhhVZVZ(3),         & 
& cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplAhAhcVWmVWm(3,3),   & 
& cplAhAhVZVZ(3,3),cplAhHpmcVWmVP(3,2),cplAhHpmcVWmVZ(3,2),cplAhcHpmVPVWm(3,2),          & 
& cplAhcHpmVWmVZ(3,2),cplhhhhcVWmVWm(3,3),cplhhhhVZVZ(3,3),cplhhHpmcVWmVP(3,2),          & 
& cplhhHpmcVWmVZ(3,2),cplhhcHpmVPVWm(3,2),cplhhcHpmVWmVZ(3,2),cplHpmcHpmVPVP(2,2),       & 
& cplHpmcHpmVPVZ(2,2),cplHpmcHpmcVWmVWm(2,2),cplHpmcHpmVZVZ(2,2),cplSdcSdVGVG(6,6),      & 
& cplSdcSdVGVP(6,6),cplSdcSdVGVZ(6,6),cplSdcSucVWmVG(6,6),cplSdcSdVPVP(6,6),             & 
& cplSdcSdVPVZ(6,6),cplSdcSucVWmVP(6,6),cplSdcSdcVWmVWm(6,6),cplSdcSdVZVZ(6,6),          & 
& cplSdcSucVWmVZ(6,6),cplSecSeVPVP(6,6),cplSecSeVPVZ(6,6),cplSecSvcVWmVP(6,3),           & 
& cplSecSecVWmVWm(6,6),cplSecSeVZVZ(6,6),cplSecSvcVWmVZ(6,3),cplSucSuVGVG(6,6),          & 
& cplSucSuVGVP(6,6),cplSucSdVGVWm(6,6),cplSucSuVGVZ(6,6),cplSucSuVPVP(6,6),              & 
& cplSucSdVPVWm(6,6),cplSucSuVPVZ(6,6),cplSucSdVWmVZ(6,6),cplSucSucVWmVWm(6,6),          & 
& cplSucSuVZVZ(6,6),cplSvcSeVPVWm(3,6),cplSvcSeVWmVZ(3,6),cplSvcSvcVWmVWm(3,3),          & 
& cplSvcSvVZVZ(3,3),cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL(2,2,3),            & 
& cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),       & 
& cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),           & 
& cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),    & 
& cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3)

Complex(dp) :: cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),      & 
& cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),       & 
& cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),       & 
& cplChiFucSuR(5,3,6),cplChiFvcSvL(5,3,3),cplChiFvcSvR(5,3,3),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplcFvChiSvL(3,5,3),       & 
& cplcFvChiSvR(3,5,3),cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),            & 
& cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),     & 
& cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),       & 
& cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),      & 
& cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),           & 
& cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),         & 
& cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),            & 
& cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),cplChiChacVWmL(5,2),    & 
& cplChiChacVWmR(5,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),          & 
& cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplcChaChiVWmL(2,5),            & 
& cplcChaChiVWmR(2,5),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecVWmL(3,3),& 
& cplcFvFecVWmR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),& 
& cplcFeFvVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplGluGluVGL,cplGluGluVGR,         & 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,& 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2, & 
& cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,         & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm, & 
& cplcgWmgWmAh(3),cplcgWpCgWpCAh(3),cplcgZgAhh(3),cplcgWmgAHpm(2),cplcgWpCgAcHpm(2),     & 
& cplcgWmgWmhh(3),cplcgZgWmcHpm(2),cplcgWpCgWpChh(3),cplcgZgWpCHpm(2),cplcgZgZhh(3),     & 
& cplcgWmgZHpm(2),cplcgWpCgZcHpm(2)

Complex(dp) :: ctcplAhAhAh(3,3,3),ctcplAhAhhh(3,3,3),ctcplAhhhhh(3,3,3),ctcplAhHpmcHpm(3,2,2),       & 
& ctcplAhSdcSd(3,6,6),ctcplAhSecSe(3,6,6),ctcplAhSucSu(3,6,6),ctcplhhhhhh(3,3,3),        & 
& ctcplhhHpmcHpm(3,2,2),ctcplhhSdcSd(3,6,6),ctcplhhSecSe(3,6,6),ctcplhhSucSu(3,6,6),     & 
& ctcplhhSvcSv(3,3,3),ctcplHpmSucSd(2,6,6),ctcplHpmSvcSe(2,3,6),ctcplSdcHpmcSu(6,2,6),   & 
& ctcplSecHpmcSv(6,2,3),ctcplAhhhVZ(3,3),ctcplAhHpmcVWm(3,2),ctcplAhcHpmVWm(3,2),        & 
& ctcplhhHpmcVWm(3,2),ctcplhhcHpmVWm(3,2),ctcplHpmcHpmVP(2,2),ctcplHpmcHpmVZ(2,2),       & 
& ctcplSdcSdVG(6,6),ctcplSdcSdVP(6,6),ctcplSdcSdVZ(6,6),ctcplSdcSucVWm(6,6),             & 
& ctcplSecSeVP(6,6),ctcplSecSeVZ(6,6),ctcplSecSvcVWm(6,3),ctcplSucSuVG(6,6),             & 
& ctcplSucSuVP(6,6),ctcplSucSdVWm(6,6),ctcplSucSuVZ(6,6),ctcplSvcSeVWm(3,6),             & 
& ctcplSvcSvVZ(3,3),ctcplhhcVWmVWm(3),ctcplhhVZVZ(3),ctcplHpmcVWmVP(2),ctcplHpmcVWmVZ(2),& 
& ctcplcHpmVPVWm(2),ctcplcHpmVWmVZ(2),ctcplVGVGVG,ctcplcVWmVPVWm,ctcplcVWmVWmVZ,         & 
& ctcplcChaChaAhL(2,2,3),ctcplcChaChaAhR(2,2,3),ctcplChiChiAhL(5,5,3),ctcplChiChiAhR(5,5,3),& 
& ctcplcFdFdAhL(3,3,3),ctcplcFdFdAhR(3,3,3),ctcplcFeFeAhL(3,3,3),ctcplcFeFeAhR(3,3,3),   & 
& ctcplcFuFuAhL(3,3,3),ctcplcFuFuAhR(3,3,3),ctcplChiChacHpmL(5,2,2),ctcplChiChacHpmR(5,2,2),& 
& ctcplChaFucSdL(2,3,6),ctcplChaFucSdR(2,3,6),ctcplChaFvcSeL(2,3,6),ctcplChaFvcSeR(2,3,6),& 
& ctcplcChaChahhL(2,2,3),ctcplcChaChahhR(2,2,3),ctcplcFdChaSuL(3,2,6),ctcplcFdChaSuR(3,2,6),& 
& ctcplcFeChaSvL(3,2,3),ctcplcFeChaSvR(3,2,3),ctcplChiChihhL(5,5,3),ctcplChiChihhR(5,5,3),& 
& ctcplChiFdcSdL(5,3,6),ctcplChiFdcSdR(5,3,6),ctcplChiFecSeL(5,3,6),ctcplChiFecSeR(5,3,6),& 
& ctcplChiFucSuL(5,3,6),ctcplChiFucSuR(5,3,6),ctcplChiFvcSvL(5,3,3),ctcplChiFvcSvR(5,3,3),& 
& ctcplcChaChiHpmL(2,5,2),ctcplcChaChiHpmR(2,5,2),ctcplcFdChiSdL(3,5,6),ctcplcFdChiSdR(3,5,6),& 
& ctcplcFeChiSeL(3,5,6),ctcplcFeChiSeR(3,5,6),ctcplcFuChiSuL(3,5,6),ctcplcFuChiSuR(3,5,6),& 
& ctcplcFvChiSvL(3,5,3),ctcplcFvChiSvR(3,5,3),ctcplGluFdcSdL(3,6),ctcplGluFdcSdR(3,6),   & 
& ctcplcFdFdhhL(3,3,3),ctcplcFdFdhhR(3,3,3),ctcplcChaFdcSuL(2,3,6),ctcplcChaFdcSuR(2,3,6),& 
& ctcplcFuFdcHpmL(3,3,2),ctcplcFuFdcHpmR(3,3,2),ctcplcFeFehhL(3,3,3),ctcplcFeFehhR(3,3,3),& 
& ctcplcChaFecSvL(2,3,3),ctcplcChaFecSvR(2,3,3),ctcplcFvFecHpmL(3,3,2),ctcplcFvFecHpmR(3,3,2),& 
& ctcplGluFucSuL(3,6),ctcplGluFucSuR(3,6),ctcplcFuFuhhL(3,3,3),ctcplcFuFuhhR(3,3,3),     & 
& ctcplcFdFuHpmL(3,3,2),ctcplcFdFuHpmR(3,3,2),ctcplcFeFvHpmL(3,3,2),ctcplcFeFvHpmR(3,3,2),& 
& ctcplcFdGluSdL(3,6),ctcplcFdGluSdR(3,6),ctcplcFuGluSuL(3,6),ctcplcFuGluSuR(3,6),       & 
& ctcplcChacFuSdL(2,3,6),ctcplcChacFuSdR(2,3,6),ctcplcChacFvSeL(2,3,6),ctcplcChacFvSeR(2,3,6),& 
& ctcplChiChacVWmL(5,2),ctcplChiChacVWmR(5,2),ctcplcChaChaVPL(2,2),ctcplcChaChaVPR(2,2), & 
& ctcplcChaChaVZL(2,2),ctcplcChaChaVZR(2,2),ctcplChiChiVZL(5,5),ctcplChiChiVZR(5,5),     & 
& ctcplcChaChiVWmL(2,5),ctcplcChaChiVWmR(2,5),ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),     & 
& ctcplcFdFdVPL(3,3),ctcplcFdFdVPR(3,3),ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3),           & 
& ctcplcFuFdcVWmL(3,3),ctcplcFuFdcVWmR(3,3),ctcplcFeFeVPL(3,3),ctcplcFeFeVPR(3,3),       & 
& ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),ctcplcFvFecVWmL(3,3),ctcplcFvFecVWmR(3,3),       & 
& ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),           & 
& ctcplcFdFuVWmL(3,3),ctcplcFdFuVWmR(3,3),ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3)

Complex(dp) :: ctcplcFeFvVWmL(3,3),ctcplcFeFvVWmR(3,3),ctcplcFvFvVZL(3,3),ctcplcFvFvVZR(3,3),         & 
& ctcplGluGluVGL,ctcplGluGluVGR

Complex(dp) :: ZRUZD(6,6),ZRUZV(3,3),ZRUZU(6,6),ZRUZE(6,6),ZRUZH(3,3),ZRUZA(3,3),ZRUZP(2,2),         & 
& ZRUZN(5,5),ZRUUM(2,2),ZRUUP(2,2),ZRUZEL(3,3),ZRUZER(3,3),ZRUZDL(3,3),ZRUZDR(3,3),      & 
& ZRUZUL(3,3),ZRUZUR(3,3)

Complex(dp) :: ZcplAhAhAh(3,3,3),ZcplAhAhhh(3,3,3),ZcplAhhhhh(3,3,3),ZcplAhHpmcHpm(3,2,2),           & 
& ZcplAhSdcSd(3,6,6),ZcplAhSecSe(3,6,6),ZcplAhSucSu(3,6,6),Zcplhhhhhh(3,3,3),            & 
& ZcplhhHpmcHpm(3,2,2),ZcplhhSdcSd(3,6,6),ZcplhhSecSe(3,6,6),ZcplhhSucSu(3,6,6),         & 
& ZcplhhSvcSv(3,3,3),ZcplHpmSucSd(2,6,6),ZcplHpmSvcSe(2,3,6),ZcplSdcHpmcSu(6,2,6),       & 
& ZcplSecHpmcSv(6,2,3),ZcplAhAhAhAh(3,3,3,3),ZcplAhAhAhhh(3,3,3,3),ZcplAhAhhhhh(3,3,3,3),& 
& ZcplAhAhHpmcHpm(3,3,2,2),ZcplAhAhSdcSd(3,3,6,6),ZcplAhAhSecSe(3,3,6,6),ZcplAhAhSucSu(3,3,6,6),& 
& ZcplAhAhSvcSv(3,3,3,3),ZcplAhhhhhhh(3,3,3,3),ZcplAhhhHpmcHpm(3,3,2,2),ZcplAhhhSdcSd(3,3,6,6),& 
& ZcplAhhhSecSe(3,3,6,6),ZcplAhhhSucSu(3,3,6,6),ZcplAhHpmSucSd(3,2,6,6),ZcplAhHpmSvcSe(3,2,3,6),& 
& ZcplAhSdcHpmcSu(3,6,2,6),ZcplAhSecHpmcSv(3,6,2,3),Zcplhhhhhhhh(3,3,3,3),               & 
& ZcplhhhhHpmcHpm(3,3,2,2),ZcplhhhhSdcSd(3,3,6,6),ZcplhhhhSecSe(3,3,6,6),ZcplhhhhSucSu(3,3,6,6),& 
& ZcplhhhhSvcSv(3,3,3,3),ZcplhhHpmSucSd(3,2,6,6),ZcplhhHpmSvcSe(3,2,3,6),ZcplhhSdcHpmcSu(3,6,2,6),& 
& ZcplhhSecHpmcSv(3,6,2,3),ZcplHpmHpmcHpmcHpm(2,2,2,2),ZcplHpmSdcHpmcSd(2,6,2,6),        & 
& ZcplHpmSecHpmcSe(2,6,2,6),ZcplHpmSucHpmcSu(2,6,2,6),ZcplHpmSvcHpmcSv(2,3,2,3),         & 
& ZcplSdSdcSdcSd(6,6,6,6),ZcplSdSecSdcSe(6,6,6,6),ZcplSdSucSdcSu(6,6,6,6),               & 
& ZcplSdSvcSdcSv(6,3,6,3),ZcplSdSvcSecSu(6,3,6,6),ZcplSeSecSecSe(6,6,6,6),               & 
& ZcplSeSucSdcSv(6,6,6,3),ZcplSeSucSecSu(6,6,6,6),ZcplSeSvcSecSv(6,3,6,3),               & 
& ZcplSuSucSucSu(6,6,6,6),ZcplSuSvcSucSv(6,3,6,3),ZcplSvSvcSvcSv(3,3,3,3),               & 
& ZcplAhhhVZ(3,3),ZcplAhHpmcVWm(3,2),ZcplAhcHpmVWm(3,2),ZcplhhHpmcVWm(3,2),              & 
& ZcplhhcHpmVWm(3,2),ZcplHpmcHpmVP(2,2),ZcplHpmcHpmVZ(2,2),ZcplSdcSdVG(6,6),             & 
& ZcplSdcSdVP(6,6),ZcplSdcSdVZ(6,6),ZcplSdcSucVWm(6,6),ZcplSecSeVP(6,6),ZcplSecSeVZ(6,6),& 
& ZcplSecSvcVWm(6,3),ZcplSucSuVG(6,6),ZcplSucSuVP(6,6),ZcplSucSdVWm(6,6),ZcplSucSuVZ(6,6),& 
& ZcplSvcSeVWm(3,6),ZcplSvcSvVZ(3,3),ZcplhhcVWmVWm(3),ZcplhhVZVZ(3),ZcplHpmcVWmVP(2),    & 
& ZcplHpmcVWmVZ(2),ZcplcHpmVPVWm(2),ZcplcHpmVWmVZ(2),ZcplAhAhcVWmVWm(3,3),               & 
& ZcplAhAhVZVZ(3,3),ZcplAhHpmcVWmVP(3,2),ZcplAhHpmcVWmVZ(3,2),ZcplAhcHpmVPVWm(3,2),      & 
& ZcplAhcHpmVWmVZ(3,2),ZcplhhhhcVWmVWm(3,3),ZcplhhhhVZVZ(3,3),ZcplhhHpmcVWmVP(3,2),      & 
& ZcplhhHpmcVWmVZ(3,2),ZcplhhcHpmVPVWm(3,2),ZcplhhcHpmVWmVZ(3,2),ZcplHpmcHpmVPVP(2,2),   & 
& ZcplHpmcHpmVPVZ(2,2),ZcplHpmcHpmcVWmVWm(2,2),ZcplHpmcHpmVZVZ(2,2),ZcplSdcSdVGVG(6,6),  & 
& ZcplSdcSdVGVP(6,6),ZcplSdcSdVGVZ(6,6),ZcplSdcSucVWmVG(6,6),ZcplSdcSdVPVP(6,6),         & 
& ZcplSdcSdVPVZ(6,6),ZcplSdcSucVWmVP(6,6),ZcplSdcSdcVWmVWm(6,6),ZcplSdcSdVZVZ(6,6),      & 
& ZcplSdcSucVWmVZ(6,6),ZcplSecSeVPVP(6,6),ZcplSecSeVPVZ(6,6),ZcplSecSvcVWmVP(6,3),       & 
& ZcplSecSecVWmVWm(6,6),ZcplSecSeVZVZ(6,6),ZcplSecSvcVWmVZ(6,3),ZcplSucSuVGVG(6,6),      & 
& ZcplSucSuVGVP(6,6),ZcplSucSdVGVWm(6,6),ZcplSucSuVGVZ(6,6),ZcplSucSuVPVP(6,6),          & 
& ZcplSucSdVPVWm(6,6),ZcplSucSuVPVZ(6,6),ZcplSucSdVWmVZ(6,6),ZcplSucSucVWmVWm(6,6),      & 
& ZcplSucSuVZVZ(6,6),ZcplSvcSeVPVWm(3,6),ZcplSvcSeVWmVZ(3,6),ZcplSvcSvcVWmVWm(3,3),      & 
& ZcplSvcSvVZVZ(3,3),ZcplVGVGVG,ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplcChaChaAhL(2,2,3),       & 
& ZcplcChaChaAhR(2,2,3),ZcplChiChiAhL(5,5,3),ZcplChiChiAhR(5,5,3),ZcplcFdFdAhL(3,3,3),   & 
& ZcplcFdFdAhR(3,3,3),ZcplcFeFeAhL(3,3,3),ZcplcFeFeAhR(3,3,3),ZcplcFuFuAhL(3,3,3)

Complex(dp) :: ZcplcFuFuAhR(3,3,3),ZcplChiChacHpmL(5,2,2),ZcplChiChacHpmR(5,2,2),ZcplChaFucSdL(2,3,6),& 
& ZcplChaFucSdR(2,3,6),ZcplChaFvcSeL(2,3,6),ZcplChaFvcSeR(2,3,6),ZcplcChaChahhL(2,2,3),  & 
& ZcplcChaChahhR(2,2,3),ZcplcFdChaSuL(3,2,6),ZcplcFdChaSuR(3,2,6),ZcplcFeChaSvL(3,2,3),  & 
& ZcplcFeChaSvR(3,2,3),ZcplChiChihhL(5,5,3),ZcplChiChihhR(5,5,3),ZcplChiFdcSdL(5,3,6),   & 
& ZcplChiFdcSdR(5,3,6),ZcplChiFecSeL(5,3,6),ZcplChiFecSeR(5,3,6),ZcplChiFucSuL(5,3,6),   & 
& ZcplChiFucSuR(5,3,6),ZcplChiFvcSvL(5,3,3),ZcplChiFvcSvR(5,3,3),ZcplcChaChiHpmL(2,5,2), & 
& ZcplcChaChiHpmR(2,5,2),ZcplcFdChiSdL(3,5,6),ZcplcFdChiSdR(3,5,6),ZcplcFeChiSeL(3,5,6), & 
& ZcplcFeChiSeR(3,5,6),ZcplcFuChiSuL(3,5,6),ZcplcFuChiSuR(3,5,6),ZcplcFvChiSvL(3,5,3),   & 
& ZcplcFvChiSvR(3,5,3),ZcplGluFdcSdL(3,6),ZcplGluFdcSdR(3,6),ZcplcFdFdhhL(3,3,3),        & 
& ZcplcFdFdhhR(3,3,3),ZcplcChaFdcSuL(2,3,6),ZcplcChaFdcSuR(2,3,6),ZcplcFuFdcHpmL(3,3,2), & 
& ZcplcFuFdcHpmR(3,3,2),ZcplcFeFehhL(3,3,3),ZcplcFeFehhR(3,3,3),ZcplcChaFecSvL(2,3,3),   & 
& ZcplcChaFecSvR(2,3,3),ZcplcFvFecHpmL(3,3,2),ZcplcFvFecHpmR(3,3,2),ZcplGluFucSuL(3,6),  & 
& ZcplGluFucSuR(3,6),ZcplcFuFuhhL(3,3,3),ZcplcFuFuhhR(3,3,3),ZcplcFdFuHpmL(3,3,2),       & 
& ZcplcFdFuHpmR(3,3,2),ZcplcFeFvHpmL(3,3,2),ZcplcFeFvHpmR(3,3,2),ZcplcFdGluSdL(3,6),     & 
& ZcplcFdGluSdR(3,6),ZcplcFuGluSuL(3,6),ZcplcFuGluSuR(3,6),ZcplcChacFuSdL(2,3,6),        & 
& ZcplcChacFuSdR(2,3,6),ZcplcChacFvSeL(2,3,6),ZcplcChacFvSeR(2,3,6),ZcplChiChacVWmL(5,2),& 
& ZcplChiChacVWmR(5,2),ZcplcChaChaVPL(2,2),ZcplcChaChaVPR(2,2),ZcplcChaChaVZL(2,2),      & 
& ZcplcChaChaVZR(2,2),ZcplChiChiVZL(5,5),ZcplChiChiVZR(5,5),ZcplcChaChiVWmL(2,5),        & 
& ZcplcChaChiVWmR(2,5),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),ZcplcFdFdVPL(3,3),            & 
& ZcplcFdFdVPR(3,3),ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),ZcplcFuFdcVWmL(3,3),             & 
& ZcplcFuFdcVWmR(3,3),ZcplcFeFeVPL(3,3),ZcplcFeFeVPR(3,3),ZcplcFeFeVZL(3,3),             & 
& ZcplcFeFeVZR(3,3),ZcplcFvFecVWmL(3,3),ZcplcFvFecVWmR(3,3),ZcplcFuFuVGL(3,3),           & 
& ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),ZcplcFdFuVWmL(3,3),              & 
& ZcplcFdFuVWmR(3,3),ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcFeFvVWmL(3,3),             & 
& ZcplcFeFvVWmR(3,3),ZcplcFvFvVZL(3,3),ZcplcFvFvVZR(3,3),ZcplGluGluVGL,ZcplGluGluVGR,    & 
& ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,ZcplcVWmVPVPVWm1,ZcplcVWmVPVPVWm2,           & 
& ZcplcVWmVPVPVWm3,ZcplcVWmVPVWmVZ1,ZcplcVWmVPVWmVZ2,ZcplcVWmVPVWmVZ3,ZcplcVWmcVWmVWmVWm1,& 
& ZcplcVWmcVWmVWmVWm2,ZcplcVWmcVWmVWmVWm3,ZcplcVWmVWmVZVZ1,ZcplcVWmVWmVZVZ2,             & 
& ZcplcVWmVWmVZVZ3,ZcplcgGgGVG,ZcplcgWmgAVWm,ZcplcgWpCgAcVWm,ZcplcgWmgWmVP,              & 
& ZcplcgWmgWmVZ,ZcplcgAgWmcVWm,ZcplcgZgWmcVWm,ZcplcgWpCgWpCVP,ZcplcgAgWpCVWm,            & 
& ZcplcgZgWpCVWm,ZcplcgWpCgWpCVZ,ZcplcgWmgZVWm,ZcplcgWpCgZcVWm,ZcplcgWmgWmAh(3),         & 
& ZcplcgWpCgWpCAh(3),ZcplcgZgAhh(3),ZcplcgWmgAHpm(2),ZcplcgWpCgAcHpm(2),ZcplcgWmgWmhh(3),& 
& ZcplcgZgWmcHpm(2),ZcplcgWpCgWpChh(3),ZcplcgZgWpCHpm(2),ZcplcgZgZhh(3),ZcplcgWmgZHpm(2),& 
& ZcplcgWpCgZcHpm(2)

Complex(dp) :: GcplAhHpmcHpm(3,2,2),GcplhhHpmcHpm(3,2,2),GcplHpmSucSd(2,6,6),GcplHpmSvcSe(2,3,6),    & 
& GcplSdcHpmcSu(6,2,6),GcplSecHpmcSv(6,2,3),GcplAhHpmcVWm(3,2),GcplAhcHpmVWm(3,2),       & 
& GcplhhHpmcVWm(3,2),GcplhhcHpmVWm(3,2),GcplHpmcHpmVP(2,2),GcplHpmcHpmVZ(2,2),           & 
& GcplHpmcVWmVP(2),GcplHpmcVWmVZ(2),GcplcHpmVPVWm(2),GcplcHpmVWmVZ(2),GcplChiChacHpmL(5,2,2),& 
& GcplChiChacHpmR(5,2,2),GcplcChaChiHpmL(2,5,2),GcplcChaChiHpmR(2,5,2),GcplcFuFdcHpmL(3,3,2),& 
& GcplcFuFdcHpmR(3,3,2),GcplcFvFecHpmL(3,3,2),GcplcFvFecHpmR(3,3,2),GcplcFdFuHpmL(3,3,2),& 
& GcplcFdFuHpmR(3,3,2),GcplcFeFvHpmL(3,3,2),GcplcFeFvHpmR(3,3,2)

Complex(dp) :: GZcplAhHpmcHpm(3,2,2),GZcplhhHpmcHpm(3,2,2),GZcplHpmSucSd(2,6,6),GZcplHpmSvcSe(2,3,6),& 
& GZcplSdcHpmcSu(6,2,6),GZcplSecHpmcSv(6,2,3),GZcplAhHpmcVWm(3,2),GZcplAhcHpmVWm(3,2),   & 
& GZcplhhHpmcVWm(3,2),GZcplhhcHpmVWm(3,2),GZcplHpmcHpmVP(2,2),GZcplHpmcHpmVZ(2,2),       & 
& GZcplHpmcVWmVP(2),GZcplHpmcVWmVZ(2),GZcplcHpmVPVWm(2),GZcplcHpmVWmVZ(2),               & 
& GZcplChiChacHpmL(5,2,2),GZcplChiChacHpmR(5,2,2),GZcplcChaChiHpmL(2,5,2),               & 
& GZcplcChaChiHpmR(2,5,2),GZcplcFuFdcHpmL(3,3,2),GZcplcFuFdcHpmR(3,3,2),GZcplcFvFecHpmL(3,3,2),& 
& GZcplcFvFecHpmR(3,3,2),GZcplcFdFuHpmL(3,3,2),GZcplcFdFuHpmR(3,3,2),GZcplcFeFvHpmL(3,3,2),& 
& GZcplcFeFvHpmR(3,3,2)

Complex(dp) :: GosZcplAhHpmcHpm(3,2,2),GosZcplhhHpmcHpm(3,2,2),GosZcplHpmSucSd(2,6,6),               & 
& GosZcplHpmSvcSe(2,3,6),GosZcplSdcHpmcSu(6,2,6),GosZcplSecHpmcSv(6,2,3),GosZcplAhHpmcVWm(3,2),& 
& GosZcplAhcHpmVWm(3,2),GosZcplhhHpmcVWm(3,2),GosZcplhhcHpmVWm(3,2),GosZcplHpmcHpmVP(2,2),& 
& GosZcplHpmcHpmVZ(2,2),GosZcplHpmcVWmVP(2),GosZcplHpmcVWmVZ(2),GosZcplcHpmVPVWm(2),     & 
& GosZcplcHpmVWmVZ(2),GosZcplChiChacHpmL(5,2,2),GosZcplChiChacHpmR(5,2,2),               & 
& GosZcplcChaChiHpmL(2,5,2),GosZcplcChaChiHpmR(2,5,2),GosZcplcFuFdcHpmL(3,3,2),          & 
& GosZcplcFuFdcHpmR(3,3,2),GosZcplcFvFecHpmL(3,3,2),GosZcplcFvFecHpmR(3,3,2),            & 
& GosZcplcFdFuHpmL(3,3,2),GosZcplcFdFuHpmR(3,3,2),GosZcplcFeFvHpmL(3,3,2),               & 
& GosZcplcFeFvHpmR(3,3,2)

Real(dp), Intent(out) :: gP1LSd(6,84) 
Real(dp), Intent(out) :: gP1LSu(6,84) 
Real(dp), Intent(out) :: gP1LSe(6,69) 
Real(dp), Intent(out) :: gP1LSv(3,54) 
Real(dp), Intent(out) :: gP1Lhh(3,209) 
Real(dp), Intent(out) :: gP1LAh(3,207) 
Real(dp), Intent(out) :: gP1LHpm(2,96) 
Real(dp), Intent(out) :: gP1LGlu(1,49) 
Real(dp), Intent(out) :: gP1LChi(5,103) 
Real(dp), Intent(out) :: gP1LCha(2,87) 
Real(dp), Intent(out) :: gP1LFu(3,78) 
Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateOneLoopDecays'
 
Write(*,*) "Calculating one loop decays" 
! Regulator mass for gluon/photon 
MLambda = Mass_Regulator_PhotonGluon 
divset=SetDivonlyAdd(INT(divonly_save)) 
divvalue=SetDivergenceAdd(divergence_save) 
If (.not.CalculateOneLoopMasses) Then 
 If (OSkinematics) Then 
  Write(*,*) "Loop masses not calculated: tree-level masses used for kinematics" 
  OSkinematics = .false. 
 End if
 If (ExternalZfactors) Then 
  Write(*,*) "Loop masses not calculated: no U-factors are applied" 
  ExternalZfactors = .false. 
 End if
End if

If (Extra_scale_loopDecays) Then 
q2_save = GetRenormalizationScale() 
q2 = SetRenormalizationScale(scale_loopdecays **2) 
End if 
If ((OSkinematics).or.(ExternalZfactors)) ShiftIRdiv = .true. 
If (ewOSinDecays) Then 
sinW2=1._dp-mW2/mZ2 
g1SM=sqrt(4*Pi*Alpha_MZ/(1-sinW2)) 
g2SM=sqrt(4*Pi*Alpha_MZ/Sinw2) 
vSM=sqrt(mz2*4._dp/(g1SM**2+g2SM**2)) 
g1=g1SM 
g2=g2SM 
vd=vSM/Sqrt(1 + TanBeta**2) 
vu=TanBeta*vd 
 If (yukOSinDecays) Then !! Allow OS Yukawas only together with vSM 
    YuSM = 0._dp 
    YdSM = 0._dp 
    YuSM = 0._dp 
   Do i1=1,3 
      YuSM(i1,i1)=sqrt(2._dp)*mf_u(i1)/vSM 
      YeSM(i1,i1)=sqrt(2._dp)*mf_l(i1)/vSM 
      YdSM(i1,i1)=sqrt(2._dp)*mf_d(i1)/vSM 
    End Do 
   If(GenerationMixing) Then 
    YuSM = Transpose(Matmul(Transpose(CKM),Transpose(YuSM))) 
   End if 
Yu=(vSM*YuSM)/vu 
Yd=(vSM*YdSM)/vd 
Ye=(vSM*YeSM)/vd 
 End if 
End if 
! -------------------------------------------- 
! General information needed in the following 
! -------------------------------------------- 

! DR parameters 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,            & 
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,GenerationMixing,kont)

! Stabilize numerics 
Where (Abs(MSd).lt.1.0E-15_dp) MSd=0._dp
Where (Abs(MSd2).lt.1.0E-30_dp) MSd2=0._dp
Where (Abs(MSv).lt.1.0E-15_dp) MSv=0._dp
Where (Abs(MSv2).lt.1.0E-30_dp) MSv2=0._dp
Where (Abs(MSu).lt.1.0E-15_dp) MSu=0._dp
Where (Abs(MSu2).lt.1.0E-30_dp) MSu2=0._dp
Where (Abs(MSe).lt.1.0E-15_dp) MSe=0._dp
Where (Abs(MSe2).lt.1.0E-30_dp) MSe2=0._dp
Where (Abs(Mhh).lt.1.0E-15_dp) Mhh=0._dp
Where (Abs(Mhh2).lt.1.0E-30_dp) Mhh2=0._dp
Where (Abs(MAh).lt.1.0E-15_dp) MAh=0._dp
Where (Abs(MAh2).lt.1.0E-30_dp) MAh2=0._dp
Where (Abs(MHpm).lt.1.0E-15_dp) MHpm=0._dp
Where (Abs(MHpm2).lt.1.0E-30_dp) MHpm2=0._dp
If (Abs(MGlu).lt.1.0E-15_dp) MGlu=0._dp
If (Abs(MGlu2).lt.1.0E-30_dp) MGlu2=0._dp
Where (Abs(MChi).lt.1.0E-15_dp) MChi=0._dp
Where (Abs(MChi2).lt.1.0E-30_dp) MChi2=0._dp
Where (Abs(MCha).lt.1.0E-15_dp) MCha=0._dp
Where (Abs(MCha2).lt.1.0E-30_dp) MCha2=0._dp
Where (Abs(MFe).lt.1.0E-15_dp) MFe=0._dp
Where (Abs(MFe2).lt.1.0E-30_dp) MFe2=0._dp
Where (Abs(MFd).lt.1.0E-15_dp) MFd=0._dp
Where (Abs(MFd2).lt.1.0E-30_dp) MFd2=0._dp
Where (Abs(MFu).lt.1.0E-15_dp) MFu=0._dp
Where (Abs(MFu2).lt.1.0E-30_dp) MFu2=0._dp
If (UseZeroRotationMatrices) Then  ! Rotation matrices calculated for p2=0
ZRUZD = MatMul(ZDOS_0, Conjg(Transpose(ZD)))
ZRUZV = MatMul(ZVOS_0, Conjg(Transpose(ZV)))
ZRUZU = MatMul(ZUOS_0, Conjg(Transpose(ZU)))
ZRUZE = MatMul(ZEOS_0, Conjg(Transpose(ZE)))
ZRUZH = MatMul(ZHOS_0, Transpose(ZH))
ZRUZA = MatMul(ZAOS_0, Transpose(ZA))
ZRUZP = MatMul(ZPOS_0, Transpose(ZP))
ZRUZN = MatMul(ZNOS_0, Conjg(Transpose(ZN)))
ZRUUM = MatMul(UMOS_0, Conjg(Transpose(UM)))
ZRUUP = MatMul(UPOS_0, Conjg(Transpose(UP)))
ZRUZEL = MatMul(ZELOS_0, Conjg(Transpose(ZEL)))
ZRUZER = MatMul(ZEROS_0, Conjg(Transpose(ZER)))
ZRUZDL = MatMul(ZDLOS_0, Conjg(Transpose(ZDL)))
ZRUZDR = MatMul(ZDROS_0, Conjg(Transpose(ZDR)))
ZRUZUL = MatMul(ZULOS_0, Conjg(Transpose(ZUL)))
ZRUZUR = MatMul(ZUROS_0, Conjg(Transpose(ZUR)))
Else If (UseP2Matrices) Then   ! p2 dependent matrix 
ZRUZD = MatMul(ZDOS_p2, Conjg(Transpose(ZD)))
ZRUZV = MatMul(ZVOS_p2, Conjg(Transpose(ZV)))
ZRUZU = MatMul(ZUOS_p2, Conjg(Transpose(ZU)))
ZRUZE = MatMul(ZEOS_p2, Conjg(Transpose(ZE)))
ZRUZH = MatMul(ZHOS_p2, Transpose(ZH))
ZRUZA = MatMul(ZAOS_p2, Transpose(ZA))
ZRUZP = MatMul(ZPOS_p2, Transpose(ZP))
ZRUZN = MatMul(ZNOS_p2, Conjg(Transpose(ZN)))
ZRUUM = MatMul(UMOS_p2, Conjg(Transpose(UM)))
ZRUUP = MatMul(UPOS_p2, Conjg(Transpose(UP)))
ZRUZEL = MatMul(ZELOS_p2, Conjg(Transpose(ZEL)))
ZRUZER = MatMul(ZEROS_p2, Conjg(Transpose(ZER)))
ZRUZDL = MatMul(ZDLOS_p2, Conjg(Transpose(ZDL)))
ZRUZDR = MatMul(ZDROS_p2, Conjg(Transpose(ZDR)))
ZRUZUL = MatMul(ZULOS_p2, Conjg(Transpose(ZUL)))
ZRUZUR = MatMul(ZUROS_p2, Conjg(Transpose(ZUR)))
Else  ! Rotation matrix for lightest state
ZRUZD = MatMul(ZDOS, Conjg(Transpose(ZD)))
ZRUZV = MatMul(ZVOS, Conjg(Transpose(ZV)))
ZRUZU = MatMul(ZUOS, Conjg(Transpose(ZU)))
ZRUZE = MatMul(ZEOS, Conjg(Transpose(ZE)))
ZRUZH = MatMul(ZHOS, Transpose(ZH))
ZRUZA = MatMul(ZAOS, Transpose(ZA))
ZRUZP = MatMul(ZPOS, Transpose(ZP))
ZRUZN = MatMul(ZNOS, Conjg(Transpose(ZN)))
ZRUUM = MatMul(UMOS, Conjg(Transpose(UM)))
ZRUUP = MatMul(UPOS, Conjg(Transpose(UP)))
ZRUZEL = MatMul(ZELOS, Conjg(Transpose(ZEL)))
ZRUZER = MatMul(ZEROS, Conjg(Transpose(ZER)))
ZRUZDL = MatMul(ZDLOS, Conjg(Transpose(ZDL)))
ZRUZDR = MatMul(ZDROS, Conjg(Transpose(ZDR)))
ZRUZUL = MatMul(ZULOS, Conjg(Transpose(ZUL)))
ZRUZUR = MatMul(ZUROS, Conjg(Transpose(ZUR)))
End if 
! Couplings 
Call AllCouplingsReallyAll(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,Yd,Td,             & 
& ZD,Ye,Te,ZE,Yu,Tu,ZU,ZV,g3,TW,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,           & 
& cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,           & 
& cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,      & 
& cplSdcHpmcSu,cplSecHpmcSv,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhhhhhhh,cplAhhhHpmcHpm,        & 
& cplAhhhSdcSd,cplAhhhSecSe,cplAhhhSucSu,cplAhHpmSucSd,cplAhHpmSvcSe,cplAhSdcHpmcSu,     & 
& cplAhSecHpmcSv,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,      & 
& cplhhhhSvcSv,cplhhHpmSucSd,cplhhHpmSvcSe,cplhhSdcHpmcSu,cplhhSecHpmcSv,cplHpmHpmcHpmcHpm,& 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSdSvcSdcSv,cplSdSvcSecSu,cplSeSecSecSe,cplSeSucSdcSv,   & 
& cplSeSucSecSu,cplSeSvcSecSv,cplSuSucSucSu,cplSuSvcSucSv,cplSvSvcSvcSv,cplAhhhVZ,       & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,      & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,      & 
& cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhcVWmVWm,          & 
& cplAhAhVZVZ,cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,cplAhcHpmVWmVZ,               & 
& cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,cplhhcHpmVPVWm,               & 
& cplhhcHpmVWmVZ,cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,         & 
& cplSdcSdVGVG,cplSdcSdVGVP,cplSdcSdVGVZ,cplSdcSucVWmVG,cplSdcSdVPVP,cplSdcSdVPVZ,       & 
& cplSdcSucVWmVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,cplSdcSucVWmVZ,cplSecSeVPVP,               & 
& cplSecSeVPVZ,cplSecSvcVWmVP,cplSecSecVWmVWm,cplSecSeVZVZ,cplSecSvcVWmVZ,               & 
& cplSucSuVGVG,cplSucSuVGVP,cplSucSdVGVWm,cplSucSuVGVZ,cplSucSuVPVP,cplSucSdVPVWm,       & 
& cplSucSuVPVZ,cplSucSdVWmVZ,cplSucSucVWmVWm,cplSucSuVZVZ,cplSvcSeVPVWm,cplSvcSeVWmVZ,   & 
& cplSvcSvcVWmVWm,cplSvcSvVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,        & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,        & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,   & 
& cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,           & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,            & 
& cplGluGluVGR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,   & 
& cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,    & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3, & 
& cplcgGgGVG,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,               & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,       & 
& cplcgWpCgAcHpm,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,     & 
& cplcgWmgZHpm,cplcgWpCgZcHpm)

em = cplcVWmVPVWm 
gs = cplcFdFdVGL(1,1) 
Call CouplingsColoredQuartics(g1,g2,lam,kap,ZA,ZH,ZP,Yd,ZD,Ye,ZE,Yu,ZU,               & 
& ZV,g3,TW,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,        & 
& cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,cplAhhhhhhh1,cplAhhhHpmcHpm1,               & 
& cplAhhhSdcSdaa,cplAhhhSecSe1,cplAhhhSucSuaa,cplAhHpmSucSdaa,cplAhHpmSvcSe1,            & 
& cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,          & 
& cplhhhhSecSe1,cplhhhhSucSuaa,cplhhhhSvcSv1,cplhhHpmSucSdaa,cplhhHpmSvcSe1,             & 
& cplhhSdcHpmcSuaa,cplhhSecHpmcSv1,cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,& 
& cplHpmSucHpmcSuaa,cplHpmSvcHpmcSv1,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,& 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSdSvcSdcSvaa,cplSdSvcSecSuaa,cplSeSecSecSe1,    & 
& cplSeSucSdcSvaa,cplSeSucSecSuaa,cplSeSvcSecSv1,cplSuSucSucSuabba,cplSuSucSucSuabab,    & 
& cplSuSvcSucSvaa,cplSvSvcSvcSv1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhHpmcVWmVP1,           & 
& cplAhHpmcVWmVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,          & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmVPVP1,       & 
& cplHpmcHpmVPVZ1,cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVGVZLamct3ct2ct1,& 
& cplSdcSucVWmVGLamct4ct2ct1,cplSdcSdVPVPaa,cplSdcSdVPVZaa,cplSdcSucVWmVPaa,             & 
& cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,cplSecSeVPVP1,cplSecSeVPVZ1,         & 
& cplSecSvcVWmVP1,cplSecSecVWmVWm1,cplSecSeVZVZ1,cplSecSvcVWmVZ1,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSucSuVGVPLamct3ct2ct1,cplSucSdVGVWmLamct3ct2ct1,& 
& cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVPaa,cplSucSdVPVWmaa,cplSucSuVPVZaa,cplSucSdVWmVZaa,& 
& cplSucSucVWmVWmaa,cplSucSuVZVZaa,cplSvcSeVPVWm1,cplSvcSeVWmVZ1,cplSvcSvcVWmVWm1,       & 
& cplSvcSvVZVZ1,cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWmVPVPVWm1Q,              & 
& cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,  & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ1Q,          & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q)

If (externalZfactors) Then 
Call getZCouplings(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,Yd,Td,ZD,Ye,               & 
& Te,ZE,Yu,Tu,ZU,ZV,g3,TW,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,cplAhAhhh,       & 
& cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,      & 
& cplSecHpmcSv,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,          & 
& cplAhAhSecSe,cplAhAhSucSu,cplAhAhSvcSv,cplAhhhhhhh,cplAhhhHpmcHpm,cplAhhhSdcSd,        & 
& cplAhhhSecSe,cplAhhhSucSu,cplAhHpmSucSd,cplAhHpmSvcSe,cplAhSdcHpmcSu,cplAhSecHpmcSv,   & 
& cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplhhhhSvcSv,        & 
& cplhhHpmSucSd,cplhhHpmSvcSe,cplhhSdcHpmcSu,cplhhSecHpmcSv,cplHpmHpmcHpmcHpm,           & 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSdSvcSdcSv,cplSdSvcSecSu,cplSeSecSecSe,cplSeSucSdcSv,   & 
& cplSeSucSecSu,cplSeSvcSecSv,cplSuSucSucSu,cplSuSvcSucSv,cplSvSvcSvcSv,cplAhhhVZ,       & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,      & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,      & 
& cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhcVWmVWm,          & 
& cplAhAhVZVZ,cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,cplAhcHpmVWmVZ,               & 
& cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,cplhhcHpmVPVWm,               & 
& cplhhcHpmVWmVZ,cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,         & 
& cplSdcSdVGVG,cplSdcSdVGVP,cplSdcSdVGVZ,cplSdcSucVWmVG,cplSdcSdVPVP,cplSdcSdVPVZ,       & 
& cplSdcSucVWmVP,cplSdcSdcVWmVWm,cplSdcSdVZVZ,cplSdcSucVWmVZ,cplSecSeVPVP,               & 
& cplSecSeVPVZ,cplSecSvcVWmVP,cplSecSecVWmVWm,cplSecSeVZVZ,cplSecSvcVWmVZ,               & 
& cplSucSuVGVG,cplSucSuVGVP,cplSucSdVGVWm,cplSucSuVGVZ,cplSucSuVPVP,cplSucSdVPVWm,       & 
& cplSucSuVPVZ,cplSucSdVWmVZ,cplSucSucVWmVWm,cplSucSuVZVZ,cplSvcSeVPVWm,cplSvcSeVWmVZ,   & 
& cplSvcSvcVWmVWm,cplSvcSvVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,        & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,        & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,cplcFvChiSvR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,   & 
& cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,           & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,            & 
& cplGluGluVGR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,   & 
& cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,    & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3, & 
& cplcgGgGVG,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,               & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,       & 
& cplcgWpCgAcHpm,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,     & 
& cplcgWmgZHpm,cplcgWpCgZcHpm,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,           & 
& ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZcplAhAhAh,ZcplAhAhhh,           & 
& ZcplAhhhhh,ZcplAhHpmcHpm,ZcplAhSdcSd,ZcplAhSecSe,ZcplAhSucSu,Zcplhhhhhh,               & 
& ZcplhhHpmcHpm,ZcplhhSdcSd,ZcplhhSecSe,ZcplhhSucSu,ZcplhhSvcSv,ZcplHpmSucSd,            & 
& ZcplHpmSvcSe,ZcplSdcHpmcSu,ZcplSecHpmcSv,ZcplAhAhAhAh,ZcplAhAhAhhh,ZcplAhAhhhhh,       & 
& ZcplAhAhHpmcHpm,ZcplAhAhSdcSd,ZcplAhAhSecSe,ZcplAhAhSucSu,ZcplAhAhSvcSv,               & 
& ZcplAhhhhhhh,ZcplAhhhHpmcHpm,ZcplAhhhSdcSd,ZcplAhhhSecSe,ZcplAhhhSucSu,ZcplAhHpmSucSd, & 
& ZcplAhHpmSvcSe,ZcplAhSdcHpmcSu,ZcplAhSecHpmcSv,Zcplhhhhhhhh,ZcplhhhhHpmcHpm,           & 
& ZcplhhhhSdcSd,ZcplhhhhSecSe,ZcplhhhhSucSu,ZcplhhhhSvcSv,ZcplhhHpmSucSd,ZcplhhHpmSvcSe, & 
& ZcplhhSdcHpmcSu,ZcplhhSecHpmcSv,ZcplHpmHpmcHpmcHpm,ZcplHpmSdcHpmcSd,ZcplHpmSecHpmcSe,  & 
& ZcplHpmSucHpmcSu,ZcplHpmSvcHpmcSv,ZcplSdSdcSdcSd,ZcplSdSecSdcSe,ZcplSdSucSdcSu,        & 
& ZcplSdSvcSdcSv,ZcplSdSvcSecSu,ZcplSeSecSecSe,ZcplSeSucSdcSv,ZcplSeSucSecSu,            & 
& ZcplSeSvcSecSv,ZcplSuSucSucSu,ZcplSuSvcSucSv,ZcplSvSvcSvcSv,ZcplAhhhVZ,ZcplAhHpmcVWm,  & 
& ZcplAhcHpmVWm,ZcplhhHpmcVWm,ZcplhhcHpmVWm,ZcplHpmcHpmVP,ZcplHpmcHpmVZ,ZcplSdcSdVG,     & 
& ZcplSdcSdVP,ZcplSdcSdVZ,ZcplSdcSucVWm,ZcplSecSeVP,ZcplSecSeVZ,ZcplSecSvcVWm,           & 
& ZcplSucSuVG,ZcplSucSuVP,ZcplSucSdVWm,ZcplSucSuVZ,ZcplSvcSeVWm,ZcplSvcSvVZ,             & 
& ZcplhhcVWmVWm,ZcplhhVZVZ,ZcplHpmcVWmVP,ZcplHpmcVWmVZ,ZcplcHpmVPVWm,ZcplcHpmVWmVZ,      & 
& ZcplAhAhcVWmVWm,ZcplAhAhVZVZ,ZcplAhHpmcVWmVP,ZcplAhHpmcVWmVZ,ZcplAhcHpmVPVWm,          & 
& ZcplAhcHpmVWmVZ,ZcplhhhhcVWmVWm,ZcplhhhhVZVZ,ZcplhhHpmcVWmVP,ZcplhhHpmcVWmVZ,          & 
& ZcplhhcHpmVPVWm,ZcplhhcHpmVWmVZ,ZcplHpmcHpmVPVP,ZcplHpmcHpmVPVZ,ZcplHpmcHpmcVWmVWm,    & 
& ZcplHpmcHpmVZVZ,ZcplSdcSdVGVG,ZcplSdcSdVGVP,ZcplSdcSdVGVZ,ZcplSdcSucVWmVG,             & 
& ZcplSdcSdVPVP,ZcplSdcSdVPVZ,ZcplSdcSucVWmVP,ZcplSdcSdcVWmVWm,ZcplSdcSdVZVZ,            & 
& ZcplSdcSucVWmVZ,ZcplSecSeVPVP,ZcplSecSeVPVZ,ZcplSecSvcVWmVP,ZcplSecSecVWmVWm,          & 
& ZcplSecSeVZVZ,ZcplSecSvcVWmVZ,ZcplSucSuVGVG,ZcplSucSuVGVP,ZcplSucSdVGVWm,              & 
& ZcplSucSuVGVZ,ZcplSucSuVPVP,ZcplSucSdVPVWm,ZcplSucSuVPVZ,ZcplSucSdVWmVZ,               & 
& ZcplSucSucVWmVWm,ZcplSucSuVZVZ,ZcplSvcSeVPVWm,ZcplSvcSeVWmVZ,ZcplSvcSvcVWmVWm,         & 
& ZcplSvcSvVZVZ,ZcplVGVGVG,ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplcChaChaAhL,ZcplcChaChaAhR,    & 
& ZcplChiChiAhL,ZcplChiChiAhR,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFeFeAhL,ZcplcFeFeAhR,       & 
& ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplChaFucSdL,               & 
& ZcplChaFucSdR,ZcplChaFvcSeL,ZcplChaFvcSeR,ZcplcChaChahhL,ZcplcChaChahhR,               & 
& ZcplcFdChaSuL,ZcplcFdChaSuR,ZcplcFeChaSvL,ZcplcFeChaSvR,ZcplChiChihhL,ZcplChiChihhR,   & 
& ZcplChiFdcSdL,ZcplChiFdcSdR,ZcplChiFecSeL,ZcplChiFecSeR,ZcplChiFucSuL,ZcplChiFucSuR,   & 
& ZcplChiFvcSvL,ZcplChiFvcSvR,ZcplcChaChiHpmL,ZcplcChaChiHpmR,ZcplcFdChiSdL,             & 
& ZcplcFdChiSdR,ZcplcFeChiSeL,ZcplcFeChiSeR,ZcplcFuChiSuL,ZcplcFuChiSuR,ZcplcFvChiSvL,   & 
& ZcplcFvChiSvR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcChaFdcSuL,    & 
& ZcplcChaFdcSuR,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,ZcplcFeFehhL,ZcplcFeFehhR,ZcplcChaFecSvL, & 
& ZcplcChaFecSvR,ZcplcFvFecHpmL,ZcplcFvFecHpmR,ZcplGluFucSuL,ZcplGluFucSuR,              & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFuHpmL,ZcplcFdFuHpmR,ZcplcFeFvHpmL,ZcplcFeFvHpmR,     & 
& ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplcChacFuSdL,ZcplcChacFuSdR, & 
& ZcplcChacFvSeL,ZcplcChacFvSeR,ZcplChiChacVWmL,ZcplChiChacVWmR,ZcplcChaChaVPL,          & 
& ZcplcChaChaVPR,ZcplcChaChaVZL,ZcplcChaChaVZR,ZcplChiChiVZL,ZcplChiChiVZR,              & 
& ZcplcChaChiVWmL,ZcplcChaChiVWmR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,   & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFeFeVPL,ZcplcFeFeVPR,     & 
& ZcplcFeFeVZL,ZcplcFeFeVZR,ZcplcFvFecVWmL,ZcplcFvFecVWmR,ZcplcFuFuVGL,ZcplcFuFuVGR,     & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,       & 
& ZcplcFeFvVWmL,ZcplcFeFvVWmR,ZcplcFvFvVZL,ZcplcFvFvVZR,ZcplGluGluVGL,ZcplGluGluVGR,     & 
& ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,ZcplcVWmVPVPVWm1,ZcplcVWmVPVPVWm2,           & 
& ZcplcVWmVPVPVWm3,ZcplcVWmVPVWmVZ1,ZcplcVWmVPVWmVZ2,ZcplcVWmVPVWmVZ3,ZcplcVWmcVWmVWmVWm1,& 
& ZcplcVWmcVWmVWmVWm2,ZcplcVWmcVWmVWmVWm3,ZcplcVWmVWmVZVZ1,ZcplcVWmVWmVZVZ2,             & 
& ZcplcVWmVWmVZVZ3,ZcplcgGgGVG,ZcplcgWmgAVWm,ZcplcgWpCgAcVWm,ZcplcgWmgWmVP,              & 
& ZcplcgWmgWmVZ,ZcplcgAgWmcVWm,ZcplcgZgWmcVWm,ZcplcgWpCgWpCVP,ZcplcgAgWpCVWm,            & 
& ZcplcgZgWpCVWm,ZcplcgWpCgWpCVZ,ZcplcgWmgZVWm,ZcplcgWpCgZcVWm,ZcplcgWmgWmAh,            & 
& ZcplcgWpCgWpCAh,ZcplcgZgAhh,ZcplcgWmgAHpm,ZcplcgWpCgAcHpm,ZcplcgWmgWmhh,               & 
& ZcplcgZgWmcHpm,ZcplcgWpCgWpChh,ZcplcgZgWpCHpm,ZcplcgZgZhh,ZcplcgWmgZHpm,               & 
& ZcplcgWpCgZcHpm)

End if 
Call getGBCouplings(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,              & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,cplAhcHpmVWm,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,     & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplSdcSucVWm,cplSecSvcVWm,cplSucSdVWm,cplSvcSeVWm,           & 
& ZcplAhcHpmVWm,ZcplcChaChiVWmL,ZcplcChaChiVWmR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,             & 
& ZcplcFeFvVWmL,ZcplcFeFvVWmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFvFecVWmL,              & 
& ZcplcFvFecVWmR,ZcplChiChacVWmL,ZcplChiChacVWmR,ZcplcHpmVPVWm,ZcplcHpmVWmVZ,            & 
& ZcplcVWmVPVWm,ZcplcVWmVWmVZ,ZcplhhcHpmVWm,ZcplhhcVWmVWm,ZcplSdcSucVWm,ZcplSecSvcVWm,   & 
& ZcplSucSdVWm,ZcplSvcSeVWm,GcplAhHpmcHpm,GcplhhHpmcHpm,GcplHpmSucSd,GcplHpmSvcSe,       & 
& GcplSdcHpmcSu,GcplSecHpmcSv,GcplAhHpmcVWm,GcplAhcHpmVWm,GcplhhHpmcVWm,GcplhhcHpmVWm,   & 
& GcplHpmcHpmVP,GcplHpmcHpmVZ,GcplHpmcVWmVP,GcplHpmcVWmVZ,GcplcHpmVPVWm,GcplcHpmVWmVZ,   & 
& GcplChiChacHpmL,GcplChiChacHpmR,GcplcChaChiHpmL,GcplcChaChiHpmR,GcplcFuFdcHpmL,        & 
& GcplcFuFdcHpmR,GcplcFvFecHpmL,GcplcFvFecHpmR,GcplcFdFuHpmL,GcplcFdFuHpmR,              & 
& GcplcFeFvHpmL,GcplcFeFvHpmR,GZcplAhHpmcHpm,GZcplhhHpmcHpm,GZcplHpmSucSd,               & 
& GZcplHpmSvcSe,GZcplSdcHpmcSu,GZcplSecHpmcSv,GZcplAhHpmcVWm,GZcplAhcHpmVWm,             & 
& GZcplhhHpmcVWm,GZcplhhcHpmVWm,GZcplHpmcHpmVP,GZcplHpmcHpmVZ,GZcplHpmcVWmVP,            & 
& GZcplHpmcVWmVZ,GZcplcHpmVPVWm,GZcplcHpmVWmVZ,GZcplChiChacHpmL,GZcplChiChacHpmR,        & 
& GZcplcChaChiHpmL,GZcplcChaChiHpmR,GZcplcFuFdcHpmL,GZcplcFuFdcHpmR,GZcplcFvFecHpmL,     & 
& GZcplcFvFecHpmR,GZcplcFdFuHpmL,GZcplcFdFuHpmR,GZcplcFeFvHpmL,GZcplcFeFvHpmR,           & 
& GosZcplAhHpmcHpm,GosZcplhhHpmcHpm,GosZcplHpmSucSd,GosZcplHpmSvcSe,GosZcplSdcHpmcSu,    & 
& GosZcplSecHpmcSv,GosZcplAhHpmcVWm,GosZcplAhcHpmVWm,GosZcplhhHpmcVWm,GosZcplhhcHpmVWm,  & 
& GosZcplHpmcHpmVP,GosZcplHpmcHpmVZ,GosZcplHpmcVWmVP,GosZcplHpmcVWmVZ,GosZcplcHpmVPVWm,  & 
& GosZcplcHpmVWmVZ,GosZcplChiChacHpmL,GosZcplChiChacHpmR,GosZcplcChaChiHpmL,             & 
& GosZcplcChaChiHpmR,GosZcplcFuFdcHpmL,GosZcplcFuFdcHpmR,GosZcplcFvFecHpmL,              & 
& GosZcplcFvFecHpmR,GosZcplcFdFuHpmL,GosZcplcFdFuHpmR,GosZcplcFeFvHpmL,GosZcplcFeFvHpmR)

! Write intilization of all counter terms 
Call WaveFunctionRenormalisation(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,              & 
& MSeOS,MSe2OS,MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,           & 
& MCha2OS,MFeOS,MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,            & 
& MVWmOS,MVWm2OS,ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,          & 
& ZDLOS,ZDROS,ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,     & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,         & 
& cplhhSucSu,cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,               & 
& cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,          & 
& cplAhAhSucSu,cplAhAhSvcSv,cplAhhhhhhh,cplAhhhHpmcHpm,cplAhhhSdcSd,cplAhhhSecSe,        & 
& cplAhhhSucSu,cplAhHpmSucSd,cplAhHpmSvcSe,cplAhSdcHpmcSu,cplAhSecHpmcSv,cplhhhhhhhh,    & 
& cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplhhhhSvcSv,cplhhHpmSucSd,      & 
& cplhhHpmSvcSe,cplhhSdcHpmcSu,cplhhSecHpmcSv,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,         & 
& cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,cplSdSecSdcSe,           & 
& cplSdSucSdcSu,cplSdSvcSdcSv,cplSdSvcSecSu,cplSeSecSecSe,cplSeSucSdcSv,cplSeSucSecSu,   & 
& cplSeSvcSecSv,cplSuSucSucSu,cplSuSvcSucSv,cplSvSvcSvcSv,cplAhhhVZ,cplAhHpmcVWm,        & 
& cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSucSuVG,      & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhcVWmVWm,cplAhAhVZVZ,        & 
& cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,cplAhcHpmVWmVZ,cplhhhhcVWmVWm,            & 
& cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,cplhhcHpmVPVWm,cplhhcHpmVWmVZ,               & 
& cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,cplHpmcHpmVZVZ,cplSdcSdVGVG,           & 
& cplSdcSdVGVP,cplSdcSdVGVZ,cplSdcSucVWmVG,cplSdcSdVPVP,cplSdcSdVPVZ,cplSdcSucVWmVP,     & 
& cplSdcSdcVWmVWm,cplSdcSdVZVZ,cplSdcSucVWmVZ,cplSecSeVPVP,cplSecSeVPVZ,cplSecSvcVWmVP,  & 
& cplSecSecVWmVWm,cplSecSeVZVZ,cplSecSvcVWmVZ,cplSucSuVGVG,cplSucSuVGVP,cplSucSdVGVWm,   & 
& cplSucSuVGVZ,cplSucSuVPVP,cplSucSdVPVWm,cplSucSuVPVZ,cplSucSdVWmVZ,cplSucSucVWmVWm,    & 
& cplSucSuVZVZ,cplSvcSeVPVWm,cplSvcSeVWmVZ,cplSvcSvcVWmVWm,cplSvcSvVZVZ,cplVGVGVG,       & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,     & 
& cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,       & 
& cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,         & 
& cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFvChiSvL,cplcFvChiSvR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,       & 
& cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,       & 
& cplcChacFvSeL,cplcChacFvSeR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVPL,               & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcChaChiVWmL,    & 
& cplcChaChiVWmR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,            & 
& cplcFdFdVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,           & 
& cplcFeFeVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,           & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,            & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,cplGluGluVGR,cplVGVGVGVG1,           & 
& cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,             & 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2, & 
& cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,         & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm, & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,cplcgWpCgAcHpm,cplcgWmgWmhh,       & 
& cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcHpm,     & 
& GcplAhHpmcHpm,GcplhhHpmcHpm,GcplHpmSucSd,GcplHpmSvcSe,GcplSdcHpmcSu,GcplSecHpmcSv,     & 
& GcplAhHpmcVWm,GcplAhcHpmVWm,GcplhhHpmcVWm,GcplhhcHpmVWm,GcplHpmcHpmVP,GcplHpmcHpmVZ,   & 
& GcplHpmcVWmVP,GcplHpmcVWmVZ,GcplcHpmVPVWm,GcplcHpmVWmVZ,GcplChiChacHpmL,               & 
& GcplChiChacHpmR,GcplcChaChiHpmL,GcplcChaChiHpmR,GcplcFuFdcHpmL,GcplcFuFdcHpmR,         & 
& GcplcFvFecHpmL,GcplcFvFecHpmR,GcplcFdFuHpmL,GcplcFdFuHpmR,GcplcFeFvHpmL,               & 
& GcplcFeFvHpmR,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,dTk,dYu,dTu,dmq2,            & 
& dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,dvS,dpG,dZD,dZV,              & 
& dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,dZUR,dSinTW,dCosTW,           & 
& dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,ZfSe,Zfhh,ZfAh,ZfHpm,            & 
& ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,ZfVPVZ,ZfVZVP,ctcplAhAhAh,          & 
& ctcplAhAhhh,ctcplAhhhhh,ctcplAhHpmcHpm,ctcplAhSdcSd,ctcplAhSecSe,ctcplAhSucSu,         & 
& ctcplhhhhhh,ctcplhhHpmcHpm,ctcplhhSdcSd,ctcplhhSecSe,ctcplhhSucSu,ctcplhhSvcSv,        & 
& ctcplHpmSucSd,ctcplHpmSvcSe,ctcplSdcHpmcSu,ctcplSecHpmcSv,ctcplAhhhVZ,ctcplAhHpmcVWm,  & 
& ctcplAhcHpmVWm,ctcplhhHpmcVWm,ctcplhhcHpmVWm,ctcplHpmcHpmVP,ctcplHpmcHpmVZ,            & 
& ctcplSdcSdVG,ctcplSdcSdVP,ctcplSdcSdVZ,ctcplSdcSucVWm,ctcplSecSeVP,ctcplSecSeVZ,       & 
& ctcplSecSvcVWm,ctcplSucSuVG,ctcplSucSuVP,ctcplSucSdVWm,ctcplSucSuVZ,ctcplSvcSeVWm,     & 
& ctcplSvcSvVZ,ctcplhhcVWmVWm,ctcplhhVZVZ,ctcplHpmcVWmVP,ctcplHpmcVWmVZ,ctcplcHpmVPVWm,  & 
& ctcplcHpmVWmVZ,ctcplVGVGVG,ctcplcVWmVPVWm,ctcplcVWmVWmVZ,ctcplcChaChaAhL,              & 
& ctcplcChaChaAhR,ctcplChiChiAhL,ctcplChiChiAhR,ctcplcFdFdAhL,ctcplcFdFdAhR,             & 
& ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplChiChacHpmL,              & 
& ctcplChiChacHpmR,ctcplChaFucSdL,ctcplChaFucSdR,ctcplChaFvcSeL,ctcplChaFvcSeR,          & 
& ctcplcChaChahhL,ctcplcChaChahhR,ctcplcFdChaSuL,ctcplcFdChaSuR,ctcplcFeChaSvL,          & 
& ctcplcFeChaSvR,ctcplChiChihhL,ctcplChiChihhR,ctcplChiFdcSdL,ctcplChiFdcSdR,            & 
& ctcplChiFecSeL,ctcplChiFecSeR,ctcplChiFucSuL,ctcplChiFucSuR,ctcplChiFvcSvL,            & 
& ctcplChiFvcSvR,ctcplcChaChiHpmL,ctcplcChaChiHpmR,ctcplcFdChiSdL,ctcplcFdChiSdR,        & 
& ctcplcFeChiSeL,ctcplcFeChiSeR,ctcplcFuChiSuL,ctcplcFuChiSuR,ctcplcFvChiSvL,            & 
& ctcplcFvChiSvR,ctcplGluFdcSdL,ctcplGluFdcSdR,ctcplcFdFdhhL,ctcplcFdFdhhR,              & 
& ctcplcChaFdcSuL,ctcplcChaFdcSuR,ctcplcFuFdcHpmL,ctcplcFuFdcHpmR,ctcplcFeFehhL,         & 
& ctcplcFeFehhR,ctcplcChaFecSvL,ctcplcChaFecSvR,ctcplcFvFecHpmL,ctcplcFvFecHpmR,         & 
& ctcplGluFucSuL,ctcplGluFucSuR,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFuHpmL,              & 
& ctcplcFdFuHpmR,ctcplcFeFvHpmL,ctcplcFeFvHpmR,ctcplcFdGluSdL,ctcplcFdGluSdR,            & 
& ctcplcFuGluSuL,ctcplcFuGluSuR,ctcplcChacFuSdL,ctcplcChacFuSdR,ctcplcChacFvSeL,         & 
& ctcplcChacFvSeR,ctcplChiChacVWmL,ctcplChiChacVWmR,ctcplcChaChaVPL,ctcplcChaChaVPR,     & 
& ctcplcChaChaVZL,ctcplcChaChaVZR,ctcplChiChiVZL,ctcplChiChiVZR,ctcplcChaChiVWmL,        & 
& ctcplcChaChiVWmR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,ctcplcFdFdVPR,              & 
& ctcplcFdFdVZL,ctcplcFdFdVZR,ctcplcFuFdcVWmL,ctcplcFuFdcVWmR,ctcplcFeFeVPL,             & 
& ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFvFecVWmL,ctcplcFvFecVWmR,             & 
& ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFdFuVWmL,ctcplcFdFuVWmR, & 
& ctcplcFuFuVZL,ctcplcFuFuVZR,ctcplcFeFvVWmL,ctcplcFeFvVWmR,ctcplcFvFvVZL,               & 
& ctcplcFvFvVZR,ctcplGluGluVGL,ctcplGluGluVGR,MLambda,deltaM,kont)

! -------------------------------------------- 
! The decays at one-loop 
! -------------------------------------------- 

! Sd
If (CalcLoopDecay_Sd) Then 
Call OneLoopDecay_Sd(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhAhSdcSdaa,cplAhcHpmVWm,cplAhhhhh,               & 
& cplAhhhSdcSdaa,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,   & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplcChaChaAhL,            & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChaFucSdL,cplChaFucSdR,           & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,              & 
& cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,         & 
& cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhhhSdcSdaa,cplhhHpmcHpm,          & 
& cplhhHpmcVWm,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplhhSdcSd,cplhhSecSe,cplhhSucSu,        & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,              & 
& cplSdcSdcVWmVWmaa,cplSdcSdVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVP,cplSdcSdVPVPaa,           & 
& cplSdcSdVPVZaa,cplSdcSdVZ,cplSdcSdVZVZaa,cplSdcSucVWm,cplSdcSucVWmVGLamct4ct2ct1,      & 
& cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,cplSdSdcSdcSdabab,cplSdSdcSdcSdabba,cplSdSecSdcSeaa, & 
& cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSdcSvaa,cplSeSucSdcSvaa,cplSucSdVGVWmLamct3ct2ct1,& 
& cplSucSdVPVWmaa,cplSucSdVWm,cplSucSdVWmVZaa,cplSucSucVWmVWmaa,cplSucSuVG,              & 
& cplSucSuVP,cplSucSuVZ,cplVGVGVG,ctcplAhSdcSd,ctcplChaFucSdL,ctcplChaFucSdR,            & 
& ctcplChiFdcSdL,ctcplChiFdcSdR,ctcplGluFdcSdL,ctcplGluFdcSdR,ctcplhhSdcSd,              & 
& ctcplHpmSucSd,ctcplSdcSdVG,ctcplSdcSdVP,ctcplSdcSdVZ,ctcplSucSdVWm,GcplcHpmVPVWm,      & 
& GcplHpmcVWmVP,GcplHpmSucSd,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,GosZcplHpmSucSd,          & 
& GZcplcHpmVPVWm,GZcplHpmcVWmVP,GZcplHpmSucSd,ZcplAhSdcSd,ZcplChaFucSdL,ZcplChaFucSdR,   & 
& ZcplChiFdcSdL,ZcplChiFdcSdR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplhhSdcSd,ZcplHpmSucSd,      & 
& ZcplSdcSdVZ,ZcplSucSdVWm,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,              & 
& ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,            & 
& kont,gP1LSd)

End if 
! Su
If (CalcLoopDecay_Su) Then 
Call OneLoopDecay_Su(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhAhSucSuaa,cplAhcHpmVWm,cplAhhhhh,               & 
& cplAhhhSucSuaa,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,   & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplcChaChaAhL,            & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChaFucSdL,cplChaFucSdR,           & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,              & 
& cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,         & 
& cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhhhSucSuaa,cplhhHpmcHpm,          & 
& cplhhHpmcVWm,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplhhSdcSd,cplhhSecSe,cplhhSucSu,        & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplHpmSucSd,cplSdcHpmcSu,cplSdcSdcVWmVWmaa,        & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSdcSucVWmVGLamct4ct2ct1,              & 
& cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSecSuaa, & 
& cplSecHpmcSv,cplSeSucSecSuaa,cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWm,    & 
& cplSucSdVWmVZaa,cplSucSucVWmVWmaa,cplSucSuVG,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSucSuVGVPLamct3ct2ct1,cplSucSuVGVZLamct3ct2ct1,& 
& cplSucSuVP,cplSucSuVPVPaa,cplSucSuVPVZaa,cplSucSuVZ,cplSucSuVZVZaa,cplSuSucSucSuabab,  & 
& cplSuSucSucSuabba,cplSuSvcSucSvaa,cplVGVGVG,ctcplAhSucSu,ctcplcChaFdcSuL,              & 
& ctcplcChaFdcSuR,ctcplChiFucSuL,ctcplChiFucSuR,ctcplGluFucSuL,ctcplGluFucSuR,           & 
& ctcplhhSucSu,ctcplSdcHpmcSu,ctcplSdcSucVWm,ctcplSucSuVG,ctcplSucSuVP,ctcplSucSuVZ,     & 
& GcplcHpmVPVWm,GcplHpmcVWmVP,GcplSdcHpmcSu,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,           & 
& GosZcplSdcHpmcSu,GZcplcHpmVPVWm,GZcplHpmcVWmVP,GZcplSdcHpmcSu,ZcplAhSucSu,             & 
& ZcplcChaFdcSuL,ZcplcChaFdcSuR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplGluFucSuL,               & 
& ZcplGluFucSuR,ZcplhhSucSu,ZcplSdcHpmcSu,ZcplSdcSucVWm,ZcplSucSuVZ,ZRUZD,               & 
& ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,            & 
& ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LSu)

End if 
! Se
If (CalcLoopDecay_Se) Then 
Call OneLoopDecay_Se(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhAhSecSe1,cplAhcHpmVWm,cplAhhhhh,cplAhhhSecSe1,  & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmSvcSe1,cplAhSdcSd,cplAhSecHpmcSv1,         & 
& cplAhSecSe,cplAhSucSu,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,         & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFecSvL,             & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvChiSvL,          & 
& cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,      & 
& cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,    & 
& cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,       & 
& cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,            & 
& cplhhhhSecSe1,cplhhHpmcHpm,cplhhHpmcVWm,cplhhHpmSvcSe1,cplhhSdcSd,cplhhSecHpmcSv1,     & 
& cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,     & 
& cplHpmcVWmVZ,cplHpmSecHpmcSe1,cplHpmSucSd,cplHpmSvcHpmcSv1,cplHpmSvcSe,cplSdSecSdcSeaa,& 
& cplSdSvcSecSuaa,cplSecHpmcSv,cplSecSecVWmVWm1,cplSecSeVP,cplSecSeVPVP1,cplSecSeVPVZ1,  & 
& cplSecSeVZ,cplSecSeVZVZ1,cplSecSvcVWm,cplSecSvcVWmVP1,cplSecSvcVWmVZ1,cplSeSecSecSe1,  & 
& cplSeSucSecSuaa,cplSeSvcSecSv1,cplSvcSeVPVWm1,cplSvcSeVWm,cplSvcSeVWmVZ1,              & 
& cplSvcSvcVWmVWm1,cplSvcSvVZ,ctcplAhSecSe,ctcplChaFvcSeL,ctcplChaFvcSeR,ctcplChiFecSeL, & 
& ctcplChiFecSeR,ctcplhhSecSe,ctcplHpmSvcSe,ctcplSecSeVP,ctcplSecSeVZ,ctcplSvcSeVWm,     & 
& GcplcHpmVPVWm,GcplHpmcVWmVP,GcplHpmSvcSe,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,            & 
& GosZcplHpmSvcSe,GZcplcHpmVPVWm,GZcplHpmcVWmVP,GZcplHpmSvcSe,ZcplAhSecSe,               & 
& ZcplChaFvcSeL,ZcplChaFvcSeR,ZcplChiFecSeL,ZcplChiFecSeR,ZcplhhSecSe,ZcplHpmSvcSe,      & 
& ZcplSecSeVZ,ZcplSvcSeVWm,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,              & 
& ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,            & 
& kont,gP1LSe)

End if 
! Sv
If (CalcLoopDecay_Sv) Then 
Call OneLoopDecay_Sv(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhAhSvcSv1,cplAhcHpmVWm,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmSvcSe1,cplAhSdcSd,cplAhSecHpmcSv1,cplAhSecSe,        & 
& cplAhSucSu,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,  & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFecSvL,cplcChaFecSvR,              & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvChiSvL,cplcFvChiSvR,         & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhhhSvcSv1,           & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhHpmSvcSe1,cplhhSdcSd,cplhhSecHpmcSv1,cplhhSecSe,        & 
& cplhhSucSu,cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,   & 
& cplHpmSecHpmcSe1,cplHpmSvcHpmcSv1,cplHpmSvcSe,cplSdcHpmcSu,cplSdSvcSdcSvaa,            & 
& cplSecHpmcSv,cplSecSecVWmVWm1,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSecSvcVWmVP1,      & 
& cplSecSvcVWmVZ1,cplSeSucSdcSvaa,cplSeSvcSecSv1,cplSuSvcSucSvaa,cplSvcSeVPVWm1,         & 
& cplSvcSeVWm,cplSvcSeVWmVZ1,cplSvcSvcVWmVWm1,cplSvcSvVZ,cplSvcSvVZVZ1,cplSvSvcSvcSv1,   & 
& ctcplcChaFecSvL,ctcplcChaFecSvR,ctcplChiFvcSvL,ctcplChiFvcSvR,ctcplhhSvcSv,            & 
& ctcplSecHpmcSv,ctcplSecSvcVWm,ctcplSvcSvVZ,GcplcHpmVPVWm,GcplHpmcVWmVP,GcplSecHpmcSv,  & 
& GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,GosZcplSecHpmcSv,GZcplcHpmVPVWm,GZcplHpmcVWmVP,      & 
& GZcplSecHpmcSv,ZcplcChaFecSvL,ZcplcChaFecSvR,ZcplChiFvcSvL,ZcplChiFvcSvR,              & 
& ZcplhhSvcSv,ZcplSecHpmcSv,ZcplSecSvcVWm,ZcplSvcSvVZ,ZRUZD,ZRUZV,ZRUZU,ZRUZE,           & 
& ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,         & 
& MLambda,em,gs,deltaM,kont,gP1LSv)

End if 
! hh
If (CalcLoopDecay_hh) Then 
Call OneLoopDecay_hh(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhcVWmVWm1,cplAhAhhh,           & 
& cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,              & 
& cplAhAhSvcSv1,cplAhAhVZVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWm,cplAhcHpmVWmVZ1,               & 
& cplAhhhhh,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,cplAhhhSucSuaa,    & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplAhSdcSd,        & 
& cplAhSecSe,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,         & 
& cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,   & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,              & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,          & 
& cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,            & 
& cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,      & 
& cplcFvFvVZR,cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHpm,cplcgWmgAVWm,cplcgWmgWmAh,        & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHpm,cplcgWmgZVWm,cplcgWpCgAcVWm,       & 
& cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcgWpCgZcHpm,            & 
& cplcgWpCgZcVWm,cplcgZgAhh,cplcgZgWmcHpm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgZgWpCVWm,     & 
& cplcgZgZhh,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,         & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,              & 
& cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,cplcVWmVPVWmVZ1Q,      & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,      & 
& cplcVWmVWmVZVZ3Q,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVPVWm1,  & 
& cplhhcHpmVWm,cplhhcHpmVWmVZ1,cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhhhhh1,      & 
& cplhhhhHpmcHpm1,cplhhhhSdcSdaa,cplhhhhSecSe1,cplhhhhSucSuaa,cplhhhhSvcSv1,             & 
& cplhhhhVZVZ1,cplhhHpmcHpm,cplhhHpmcVWm,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhHpmSucSdaa,& 
& cplhhHpmSvcSe1,cplhhSdcHpmcSuaa,cplhhSdcSd,cplhhSecHpmcSv1,cplhhSecSe,cplhhSucSu,      & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmcVWmVWm1,cplHpmcHpmVP,cplHpmcHpmVPVP1,cplHpmcHpmVPVZ1,  & 
& cplHpmcHpmVZ,cplHpmcHpmVZVZ1,cplHpmcVWmVP,cplHpmcVWmVZ,cplHpmHpmcHpmcHpm1,             & 
& cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,cplHpmSucSd,cplHpmSvcHpmcSv1,     & 
& cplHpmSvcSe,cplSdcHpmcSu,cplSdcSdcVWmVWmaa,cplSdcSdVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSdcSdVP,cplSdcSdVPVPaa,cplSdcSdVPVZaa,    & 
& cplSdcSdVZ,cplSdcSdVZVZaa,cplSdcSucVWm,cplSdSdcSdcSdabab,cplSdSdcSdcSdabba,            & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSdcSvaa,cplSecHpmcSv,      & 
& cplSecSecVWmVWm1,cplSecSeVP,cplSecSeVPVP1,cplSecSeVPVZ1,cplSecSeVZ,cplSecSeVZVZ1,      & 
& cplSecSvcVWm,cplSeSecSecSe1,cplSeSucSecSuaa,cplSeSvcSecSv1,cplSucSdVWm,cplSucSucVWmVWmaa,& 
& cplSucSuVG,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSucSuVP,cplSucSuVPVPaa,cplSucSuVPVZaa,cplSucSuVZ,cplSucSuVZVZaa,cplSuSucSucSuabab,  & 
& cplSuSucSucSuabba,cplSuSvcSucSvaa,cplSvcSeVWm,cplSvcSvcVWmVWm1,cplSvcSvVZ,             & 
& cplSvcSvVZVZ1,cplSvSvcSvcSv1,ctcplAhAhhh,ctcplAhhhhh,ctcplAhhhVZ,ctcplcChaChahhL,      & 
& ctcplcChaChahhR,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFeFehhL,ctcplcFeFehhR,               & 
& ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplChiChihhL,ctcplChiChihhR,ctcplhhcVWmVWm,              & 
& ctcplhhhhhh,ctcplhhHpmcHpm,ctcplhhHpmcVWm,ctcplhhSdcSd,ctcplhhSecSe,ctcplhhSucSu,      & 
& ctcplhhSvcSv,ctcplhhVZVZ,GcplcHpmVPVWm,GcplhhcHpmVWm,GcplhhHpmcHpm,GcplHpmcVWmVP,      & 
& GosZcplcHpmVPVWm,GosZcplhhcHpmVWm,GosZcplhhHpmcHpm,GosZcplHpmcVWmVP,GZcplcHpmVPVWm,    & 
& GZcplhhcHpmVWm,GZcplhhHpmcHpm,GZcplHpmcVWmVP,ZcplAhAhhh,ZcplAhhhhh,ZcplAhhhVZ,         & 
& ZcplcChaChahhL,ZcplcChaChahhR,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFeFehhL,ZcplcFeFehhR,     & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplChiChihhL,ZcplChiChihhR,ZcplhhcVWmVWm,Zcplhhhhhh,        & 
& ZcplhhHpmcHpm,ZcplhhHpmcVWm,ZcplhhSdcSd,ZcplhhSecSe,ZcplhhSucSu,ZcplhhSvcSv,           & 
& ZcplhhVZVZ,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,         & 
& ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1Lhh)

End if 
! Ah
If (CalcLoopDecay_Ah) Then 
Call OneLoopDecay_Ah(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhcVWmVWm1,cplAhAhhh,           & 
& cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,              & 
& cplAhAhSvcSv1,cplAhAhVZVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWm,cplAhcHpmVWmVZ1,               & 
& cplAhhhhh,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,cplAhhhSucSuaa,    & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplAhHpmSucSdaa,   & 
& cplAhHpmSvcSe1,cplAhSdcHpmcSuaa,cplAhSdcSd,cplAhSecHpmcSv1,cplAhSecSe,cplAhSucSu,      & 
& cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,      & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHpm,    & 
& cplcgWmgAVWm,cplcgWmgWmAh,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHpm,         & 
& cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP,              & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHpm,cplcgWpCgZcVWm,cplcgZgWmcHpm,cplcgZgWmcVWm,              & 
& cplcgZgWpCHpm,cplcgZgWpCVWm,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,       & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,              & 
& cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVPVWm1,cplhhcHpmVWm,cplhhcHpmVWmVZ1,   & 
& cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,    & 
& cplhhhhSecSe1,cplhhhhSucSuaa,cplhhhhSvcSv1,cplhhhhVZVZ1,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,           & 
& cplhhVZVZ,cplHpmcHpmcVWmVWm1,cplHpmcHpmVP,cplHpmcHpmVPVP1,cplHpmcHpmVPVZ1,             & 
& cplHpmcHpmVZ,cplHpmcHpmVZVZ1,cplHpmcVWmVP,cplHpmcVWmVZ,cplHpmHpmcHpmcHpm1,             & 
& cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,cplHpmSucSd,cplHpmSvcHpmcSv1,     & 
& cplHpmSvcSe,cplSdcHpmcSu,cplSdcSdcVWmVWmaa,cplSdcSdVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSdcSdVP,cplSdcSdVPVPaa,cplSdcSdVPVZaa,    & 
& cplSdcSdVZ,cplSdcSdVZVZaa,cplSdcSucVWm,cplSdSdcSdcSdabab,cplSdSdcSdcSdabba,            & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSdcSvaa,cplSecHpmcSv,      & 
& cplSecSecVWmVWm1,cplSecSeVP,cplSecSeVPVP1,cplSecSeVPVZ1,cplSecSeVZ,cplSecSeVZVZ1,      & 
& cplSecSvcVWm,cplSeSecSecSe1,cplSeSucSecSuaa,cplSeSvcSecSv1,cplSucSdVWm,cplSucSucVWmVWmaa,& 
& cplSucSuVG,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSucSuVP,cplSucSuVPVPaa,cplSucSuVPVZaa,cplSucSuVZ,cplSucSuVZVZaa,cplSuSucSucSuabab,  & 
& cplSuSucSucSuabba,cplSuSvcSucSvaa,cplSvcSeVWm,cplSvcSvVZ,ctcplAhAhAh,ctcplAhAhhh,      & 
& ctcplAhhhhh,ctcplAhhhVZ,ctcplAhHpmcHpm,ctcplAhHpmcVWm,ctcplAhSdcSd,ctcplAhSecSe,       & 
& ctcplAhSucSu,ctcplcChaChaAhL,ctcplcChaChaAhR,ctcplcFdFdAhL,ctcplcFdFdAhR,              & 
& ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplChiChiAhL,ctcplChiChiAhR, & 
& GcplAhHpmcHpm,GcplcHpmVPVWm,GcplHpmcVWmVP,GosZcplAhHpmcHpm,GosZcplcHpmVPVWm,           & 
& GosZcplHpmcVWmVP,GZcplAhHpmcHpm,GZcplcHpmVPVWm,GZcplHpmcVWmVP,ZcplAhAhAh,              & 
& ZcplAhAhhh,ZcplAhhhhh,ZcplAhhhVZ,ZcplAhHpmcHpm,ZcplAhHpmcVWm,ZcplAhSdcSd,              & 
& ZcplAhSecSe,ZcplAhSucSu,ZcplcChaChaAhL,ZcplcChaChaAhR,ZcplcFdFdAhL,ZcplcFdFdAhR,       & 
& ZcplcFeFeAhL,ZcplcFeFeAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplChiChiAhL,ZcplChiChiAhR,       & 
& ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,             & 
& ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LAh)

End if 
! Hpm
If (CalcLoopDecay_Hpm) Then 
Call OneLoopDecay_Hpm(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,            & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhcVWmVWm1,cplAhAhhh,cplAhAhHpmcHpm1,cplAhcHpmVPVWm1,     & 
& cplAhcHpmVWm,cplAhcHpmVWmVZ1,cplAhhhhh,cplAhhhHpmcHpm1,cplAhhhVZ,cplAhHpmcHpm,         & 
& cplAhHpmcVWm,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,           & 
& cplAhSdcHpmcSuaa,cplAhSdcSd,cplAhSecHpmcSv1,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,       & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,   & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,  & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,         & 
& cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgAgWpCVWm,cplcgWmgWmAh,        & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHpm,cplcgWmgZVWm,cplcgWpCgAcHpm,       & 
& cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcgWpCgZcHpm,            & 
& cplcgZgAhh,cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgZgWpCVWm,cplcgZgZhh,cplChaFucSdL,          & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,       & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVPVWm1Q,     & 
& cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,      & 
& cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,      & 
& cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVPVWm1,cplhhcHpmVWm,      & 
& cplhhcHpmVWmVZ1,cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhHpmcHpm1,cplhhHpmcHpm,   & 
& cplhhHpmcVWm,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhHpmSucSdaa,cplhhHpmSvcSe1,           & 
& cplhhSdcHpmcSuaa,cplhhSdcSd,cplhhSecHpmcSv1,cplhhSecSe,cplhhSucSu,cplhhSvcSv,          & 
& cplhhVZVZ,cplHpmcHpmcVWmVWm1,cplHpmcHpmVP,cplHpmcHpmVPVP1,cplHpmcHpmVPVZ1,             & 
& cplHpmcHpmVZ,cplHpmcHpmVZVZ1,cplHpmcVWmVP,cplHpmcVWmVZ,cplHpmHpmcHpmcHpm1,             & 
& cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,cplHpmSucSd,cplHpmSvcHpmcSv1,     & 
& cplHpmSvcSe,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSdcSucVWmVPaa,& 
& cplSdcSucVWmVZaa,cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSecSuaa,cplSecHpmcSv,     & 
& cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSecSvcVWmVP1,cplSecSvcVWmVZ1,cplSeSucSdcSvaa,    & 
& cplSeSvcSecSv1,cplSucSdVPVWmaa,cplSucSdVWm,cplSucSdVWmVZaa,cplSucSuVG,cplSucSuVP,      & 
& cplSucSuVZ,cplSvcSeVPVWm1,cplSvcSeVWm,cplSvcSeVWmVZ1,cplSvcSvVZ,ctcplAhcHpmVWm,        & 
& ctcplAhHpmcHpm,ctcplcFuFdcHpmL,ctcplcFuFdcHpmR,ctcplcFvFecHpmL,ctcplcFvFecHpmR,        & 
& ctcplChiChacHpmL,ctcplChiChacHpmR,ctcplcHpmVPVWm,ctcplcHpmVWmVZ,ctcplhhcHpmVWm,        & 
& ctcplhhHpmcHpm,ctcplHpmcHpmVP,ctcplHpmcHpmVZ,ctcplSdcHpmcSu,ctcplSecHpmcSv,            & 
& GcplAhHpmcHpm,GcplcHpmVPVWm,GcplhhHpmcHpm,GcplHpmcHpmVZ,GcplHpmcVWmVP,GosZcplAhHpmcHpm,& 
& GosZcplcHpmVPVWm,GosZcplhhHpmcHpm,GosZcplHpmcHpmVZ,GosZcplHpmcVWmVP,GZcplAhHpmcHpm,    & 
& GZcplcHpmVPVWm,GZcplhhHpmcHpm,GZcplHpmcHpmVZ,GZcplHpmcVWmVP,ZcplAhcHpmVWm,             & 
& ZcplAhHpmcHpm,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,ZcplcFvFecHpmL,ZcplcFvFecHpmR,             & 
& ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplcHpmVWmVZ,ZcplhhcHpmVWm,ZcplhhHpmcHpm,             & 
& ZcplHpmcHpmVZ,ZcplSdcHpmcSu,ZcplSecHpmcSv,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,               & 
& ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,               & 
& MLambda,em,gs,deltaM,kont,gP1LHpm)

End if 
! Glu
If (CalcLoopDecay_Glu) Then 
Call OneLoopDecay_Glu(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,            & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhSdcSd,cplAhSucSu,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChiSdL,          & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChaFucSdL,            & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplhhSdcSd,           & 
& cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,     & 
& cplSucSdVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplVGVGVG,ctcplGluFdcSdL,ctcplGluFdcSdR,  & 
& ctcplGluFucSuL,ctcplGluFucSuR,ctcplGluGluVGL,ctcplGluGluVGR,ZcplAhSdcSd,               & 
& ZcplAhSucSu,ZcplcFdChiSdL,ZcplcFdChiSdR,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFdFdhhL,        & 
& ZcplcFdFdhhR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,         & 
& ZcplcFdFdVZR,ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuChiSuL,ZcplcFuChiSuR,ZcplcFuFuAhL,     & 
& ZcplcFuFuAhR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,         & 
& ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplChiFdcSdL,      & 
& ZcplChiFdcSdR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplGluFucSuL,   & 
& ZcplGluFucSuR,ZcplGluGluVGL,ZcplGluGluVGR,ZcplhhSdcSd,ZcplhhSucSu,ZcplSdcSdVG,         & 
& ZcplSdcSdVP,ZcplSdcSdVZ,ZcplSucSuVG,ZcplSucSuVP,ZcplSucSuVZ,ZcplVGVGVG,ZRUZD,          & 
& ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,            & 
& ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LGlu)

End if 
! Chi
If (CalcLoopDecay_Chi) Then 
Call OneLoopDecay_Chi(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,            & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHpmVWm,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,       & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,      & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFucSdL,        & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,       & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,    & 
& cplSecHpmcSv,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSucSdVWm,cplSucSuVG,cplSucSuVP,     & 
& cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,ctcplChiChacHpmL,ctcplChiChacHpmR,ctcplChiChacVWmL,  & 
& ctcplChiChacVWmR,ctcplChiChiAhL,ctcplChiChiAhR,ctcplChiChihhL,ctcplChiChihhR,          & 
& ctcplChiChiVZL,ctcplChiChiVZR,ctcplChiFdcSdL,ctcplChiFdcSdR,ctcplChiFecSeL,            & 
& ctcplChiFecSeR,ctcplChiFucSuL,ctcplChiFucSuR,ctcplChiFvcSvL,ctcplChiFvcSvR,            & 
& GcplChiChacHpmL,GcplChiChacHpmR,GcplcHpmVPVWm,GcplHpmcVWmVP,GosZcplChiChacHpmL,        & 
& GosZcplChiChacHpmR,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,GZcplChiChacHpmL,GZcplChiChacHpmR,& 
& GZcplcHpmVPVWm,GZcplHpmcVWmVP,ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplcChaChiHpmL,           & 
& ZcplcChaChiHpmR,ZcplcChaChiVWmL,ZcplcChaChiVWmR,ZcplcFdChiSdL,ZcplcFdChiSdR,           & 
& ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdGluSdL,ZcplcFdGluSdR,       & 
& ZcplcFeChiSeL,ZcplcFeChiSeR,ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFuChiSuL,ZcplcFuChiSuR,     & 
& ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuGluSuL,ZcplcFuGluSuR,       & 
& ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplChiChacVWmL,ZcplChiChacVWmR,ZcplChiChiAhL,         & 
& ZcplChiChiAhR,ZcplChiChihhL,ZcplChiChihhR,ZcplChiChiVZL,ZcplChiChiVZR,ZcplChiFdcSdL,   & 
& ZcplChiFdcSdR,ZcplChiFecSeL,ZcplChiFecSeR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplChiFvcSvL,   & 
& ZcplChiFvcSvR,ZcplcHpmVPVWm,ZcplcVWmVPVWm,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplGluFucSuL,   & 
& ZcplGluFucSuR,ZcplHpmcHpmVP,ZcplHpmcVWmVP,ZcplSdcSdVG,ZcplSdcSdVP,ZcplSecSeVP,         & 
& ZcplSucSuVG,ZcplSucSuVP,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,               & 
& ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,            & 
& kont,gP1LChi)

End if 
! Cha
If (CalcLoopDecay_Cha) Then 
Call OneLoopDecay_Cha(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,            & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHpmVWm,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,       & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,             & 
& cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,   & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR, & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,               & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,            & 
& cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,         & 
& cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,              & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,            & 
& cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,      & 
& cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,          & 
& cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,              & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,         & 
& cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplHpmSucSd,             & 
& cplHpmSvcSe,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecHpmcSv,   & 
& cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSucSdVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,       & 
& cplSvcSeVWm,cplSvcSvVZ,ctcplcChacFuSdL,ctcplcChacFuSdR,ctcplcChacFvSeL,ctcplcChacFvSeR,& 
& ctcplcChaChaAhL,ctcplcChaChaAhR,ctcplcChaChahhL,ctcplcChaChahhR,ctcplcChaChaVPL,       & 
& ctcplcChaChaVPR,ctcplcChaChaVZL,ctcplcChaChaVZR,ctcplcChaChiHpmL,ctcplcChaChiHpmR,     & 
& ctcplcChaChiVWmL,ctcplcChaChiVWmR,ctcplcChaFdcSuL,ctcplcChaFdcSuR,ctcplcChaFecSvL,     & 
& ctcplcChaFecSvR,GcplcChaChiHpmL,GcplcChaChiHpmR,GcplcHpmVPVWm,GcplHpmcVWmVP,           & 
& GosZcplcChaChiHpmL,GosZcplcChaChiHpmR,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,               & 
& GZcplcChaChiHpmL,GZcplcChaChiHpmR,GZcplcHpmVPVWm,GZcplHpmcVWmVP,ZcplcChacFuSdL,        & 
& ZcplcChacFuSdR,ZcplcChacFvSeL,ZcplcChacFvSeR,ZcplcChaChaAhL,ZcplcChaChaAhR,            & 
& ZcplcChaChahhL,ZcplcChaChahhR,ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplcChaChaVZL,            & 
& ZcplcChaChaVZR,ZcplcChaChiHpmL,ZcplcChaChiHpmR,ZcplcChaChiVWmL,ZcplcChaChiVWmR,        & 
& ZcplcChaFdcSuL,ZcplcChaFdcSuR,ZcplcChaFecSvL,ZcplcChaFecSvR,ZcplcFdChaSuL,             & 
& ZcplcFdChaSuR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFeChaSvL,ZcplcFeChaSvR,ZcplcFeFeVPL,      & 
& ZcplcFeFeVPR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplChaFucSdL,ZcplChaFucSdR,ZcplChaFvcSeL,      & 
& ZcplChaFvcSeR,ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplChiChacVWmL,ZcplChiChacVWmR,         & 
& ZcplcHpmVPVWm,ZcplcVWmVPVWm,ZcplHpmcHpmVP,ZcplHpmcVWmVP,ZcplSdcSdVP,ZcplSecSeVP,       & 
& ZcplSucSuVP,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,               & 
& ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LCha)

End if 
! Fu
If (CalcLoopDecay_Fu) Then 
Call OneLoopDecay_Fu(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,MSe2OS,             & 
& MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,MFeOS,          & 
& MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,           & 
& ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,             & 
& ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,            & 
& MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,              & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,             & 
& dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,             & 
& dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,              & 
& dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,ZfSu,              & 
& ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,               & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHpmVWm,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,       & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChaFucSdL,cplChaFucSdR,           & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,              & 
& cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,         & 
& cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,   & 
& cplHpmSucSd,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSucSdVWm,    & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplVGVGVG,ctcplcChacFuSdL,ctcplcChacFuSdR,            & 
& ctcplcFuChiSuL,ctcplcFuChiSuR,ctcplcFuFdcHpmL,ctcplcFuFdcHpmR,ctcplcFuFdcVWmL,         & 
& ctcplcFuFdcVWmR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplcFuFuhhL,ctcplcFuFuhhR,               & 
& ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,   & 
& ctcplcFuGluSuL,ctcplcFuGluSuR,GcplcFuFdcHpmL,GcplcFuFdcHpmR,GcplcHpmVPVWm,             & 
& GcplHpmcVWmVP,GosZcplcFuFdcHpmL,GosZcplcFuFdcHpmR,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,   & 
& GZcplcFuFdcHpmL,GZcplcFuFdcHpmR,GZcplcHpmVPVWm,GZcplHpmcVWmVP,ZcplcChacFuSdL,          & 
& ZcplcChacFuSdR,ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,   & 
& ZcplcFdFdVPR,ZcplcFdFuHpmL,ZcplcFdFuHpmR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplcFuChiSuL,    & 
& ZcplcFuChiSuR,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,             & 
& ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,         & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFuGluSuL,ZcplcFuGluSuR,       & 
& ZcplChaFucSdL,ZcplChaFucSdR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplcHpmVPVWm,ZcplcVWmVPVWm,   & 
& ZcplGluFucSuL,ZcplGluFucSuR,ZcplGluGluVGL,ZcplGluGluVGR,ZcplHpmcHpmVP,ZcplHpmcVWmVP,   & 
& ZcplSdcSdVG,ZcplSdcSdVP,ZcplSucSuVG,ZcplSucSuVP,ZcplVGVGVG,ZRUZD,ZRUZV,ZRUZU,          & 
& ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,          & 
& ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LFu)

End if 
If (Extra_scale_loopDecays) Then 
q2 = SetRenormalizationScale(q2_save) 
End if 
Iname = Iname - 1 
 
End Subroutine CalculateOneLoopDecays  
 
 
End Module OneLoopDecays_NMSSM 
 