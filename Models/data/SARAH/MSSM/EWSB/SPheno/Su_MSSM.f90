! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 14:59 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module Su3Decays_MSSM 
 
Use Control 
Use CouplingsForDecays_MSSM 
Use ThreeBodyPhaseSpaceS 
 
Contains 
 
Subroutine SuThreeBodyDecay(n_in,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,            & 
& gSuSuChiChi,gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,               & 
& gSuFdFvcSe,gSuhhFdcCha,gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,       & 
& gSuFuFvcSv,gSucChaFuHpm,gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,      & 
& gSuhhFuGlu,gSuGluGluSu,gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,     & 
& epsI,deltaM,CheckRealStates,gT,gPartial,BR)

Implicit None 
 
Real(dp),Intent(in) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp) :: cplAhSucSu(2,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChaChaAhL(2,2,2),     & 
& cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),cplcChaChaVZL(2,2),     & 
& cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),cplcChaChiVWmL(2,4),    & 
& cplcChaChiVWmR(2,4),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFdFdAhL(3,3,2),        & 
& cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVZL(3,3),             & 
& cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),            & 
& cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFeChaSvL(3,2,3),             & 
& cplcFeChaSvR(3,2,3),cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),        & 
& cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),             & 
& cplcFeFeVZR(3,3),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),            & 
& cplcFeFvVWmR(3,3),cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuFdcHpmL(3,3,2),        & 
& cplcFuFdcHpmR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),         & 
& cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),& 
& cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),             & 
& cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),       & 
& cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),   & 
& cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),cplChiChiVZR(4,4),           & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),       & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6),               & 
& cplhhSucSu(2,6,6),cplSdcHpmcSu(6,2,6),cplSdcSucVWm(6,6),cplSucSuVZ(6,6)

Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(inout) :: gSuAhChiFu(6,2,4,3),gSuAhFdcCha(6,2,3,2),gSuAhFuGlu(6,2,3,1),gSuSuChiChi(6,6,4,4),    & 
& gSucHpmChiFd(6,2,4,3),gSuhhChiFu(6,2,4,3),gSuChiGluSu(6,4,1,6),gSuSdChicCha(6,6,4,2),  & 
& gSuFdFucSd(6,3,3,6),gSuFdFvcSe(6,3,3,6),gSuhhFdcCha(6,2,3,2),gSuSuFdcFd(6,6,3,3),      & 
& gSuFdSvcFe(6,3,3,3),gSucHpmChaFu(6,2,2,3),gSuFuFecSe(6,3,3,6),gSuFuFucSu(6,3,3,6),     & 
& gSuFuFvcSv(6,3,3,3),gSucChaFuHpm(6,2,3,2),gSuSdFucFd(6,6,3,3),gSuFuSecFe(6,3,6,3),     & 
& gSuSuFucFu(6,6,3,3),gSuFuSvcFv(6,3,3,3),gSucHpmFdGlu(6,2,3,1),gSuhhFuGlu(6,2,3,1),     & 
& gSuGluGluSu(6,1,1,6),gSuGluSdcCha(6,1,6,2),gSuSdFvcFe(6,6,3,3),gSuSuChacCha(6,6,2,2),  & 
& gSuSuFecFe(6,6,3,3),gSuSuFvcFv(6,6,3,3)

Real(dp) :: gSuAhChiFui(2,4,3),gSuAhFdcChai(2,3,2),gSuAhFuGlui(2,3,1),gSuSuChiChii(6,4,4),        & 
& gSucHpmChiFdi(2,4,3),gSuhhChiFui(2,4,3),gSuChiGluSui(4,1,6),gSuSdChicChai(6,4,2),      & 
& gSuFdFucSdi(3,3,6),gSuFdFvcSei(3,3,6),gSuhhFdcChai(2,3,2),gSuSuFdcFdi(6,3,3),          & 
& gSuFdSvcFei(3,3,3),gSucHpmChaFui(2,2,3),gSuFuFecSei(3,3,6),gSuFuFucSui(3,3,6),         & 
& gSuFuFvcSvi(3,3,3),gSucChaFuHpmi(2,3,2),gSuSdFucFdi(6,3,3),gSuFuSecFei(3,6,3),         & 
& gSuSuFucFui(6,3,3),gSuFuSvcFvi(3,3,3),gSucHpmFdGlui(2,3,1),gSuhhFuGlui(2,3,1),         & 
& gSuGluGluSui(1,1,6),gSuGluSdcChai(1,6,2),gSuSdFvcFei(6,3,3),gSuSuChacChai(6,2,2),      & 
& gSuSuFecFei(6,3,3),gSuSuFvcFvi(6,3,3)

Real(dp), Intent(inout), Optional :: BR(:,:), gPartial(:,:) 
Real(dp), Intent(inout) :: gT(:) 
Integer, Intent(in) :: n_in 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Intent(in) ::  CheckRealStates 
Integer :: i_start, i_end, i_run, n_out, n_length, gt1, gt2, gt3, i1 
Logical :: check 
Iname = Iname +1 
NameOfUnit(Iname) = 'SuThreeBodyDecay' 
 

 
If (CheckRealStates) Then 
Else 
End If 
 
check=CheckRealStates 

 
If (n_in.Lt.0) Then 
 i_start = 1 
 i_end = 6 
 Else If ( (n_in.Ge.1).And.(n_in.Le. 6) ) Then 
 i_start = n_in 
 i_end = n_in 
Else 
 If (ErrorLevel.Ge.-1) Then 
   Write (ErrCan, *) 'Problem in subroutine'//NameOfUnit(Iname) 
   Write (ErrCan, *) 'Value of n_in out of range, (n_in,6) = ',n_in,6 
 End If 
 
 If (ErrorLevel.Gt.0) Call TerminateProgram 
 
 If (Present(BR)) BR = 0._dp 
 Iname = Iname - 1 
 Return 
End If 
 
Do i_run = i_start, i_end 
 
Call CouplingsFor_Su_decays_3B(MSu(i_run),i_run,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,            & 
& ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,             & 
& Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,cplAhSucSu,cplcChacFuSdL,    & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFvVZL,cplcFvFvVZR,           & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,         & 
& cplChiFvcSvL,cplChiFvcSvR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,         & 
& cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVZ,deltaM)


 
gSuAhChiFui = 0._dp 
Call SuToAhChiFu(i_run,MAh,MChi,MFu,MSu,cplAhSucSu,cplcFuFuAhL,cplcFuFuAhR,           & 
& cplChiChiAhL,cplChiChiAhR,cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,gSuAhChiFui)

gSuAhChiFu(i_run,:,:,:) = gSuAhChiFui 
gT(i_run) = gT(i_run) + Sum(gSuAhChiFui) 
 
gSuAhFdcChai = 0._dp 
Call SuToAhFdcCha(i_run,MAh,MFd,MCha,MSu,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdFdAhL,cplcFdFdAhR,deltaM,epsI,check,gSuAhFdcChai)

gSuAhFdcCha(i_run,:,:,:) = gSuAhFdcChai 
gT(i_run) = gT(i_run) + Sum(gSuAhFdcChai) 
 
gSuAhFuGlui = 0._dp 
Call SuToAhFuGlu(i_run,MAh,MFu,MGlu,MSu,cplAhSucSu,cplcFuFuAhL,cplcFuFuAhR,           & 
& cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,gSuAhFuGlui)

gSuAhFuGlu(i_run,:,:,:) = gSuAhFuGlui 
gT(i_run) = gT(i_run) + Sum(gSuAhFuGlui) 
 
gSuSuChiChii = 0._dp 
Call SuToSuChiChi(i_run,MSu,MChi,MVZ,MAh,Mhh,MFu,cplAhSucSu,cplhhSucSu,               & 
& cplSucSuVZ,cplcFuChiSuL,cplcFuChiSuR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,           & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,deltaM,               & 
& epsI,check,gSuSuChiChii)

gSuSuChiChi(i_run,:,:,:) = gSuSuChiChii 
gT(i_run) = gT(i_run) + Sum(gSuSuChiChii) 
 
gSucHpmChiFdi = 0._dp 
Call SuTocHpmChiFd(i_run,MHpm,MChi,MFd,MSd,MFu,MCha,MSu,cplSdcHpmcSu,cplcChaFdcSuL,   & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplChiChacHpmL,cplChiChacHpmR,               & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,gSucHpmChiFdi)

gSucHpmChiFd(i_run,:,:,:) = gSucHpmChiFdi 
gT(i_run) = gT(i_run) + Sum(gSucHpmChiFdi) 
 
gSuhhChiFui = 0._dp 
Call SuTohhChiFu(i_run,Mhh,MChi,MFu,MSu,cplhhSucSu,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplChiChihhL,cplChiChihhR,cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,gSuhhChiFui)

gSuhhChiFu(i_run,:,:,:) = gSuhhChiFui 
gT(i_run) = gT(i_run) + Sum(gSuhhChiFui) 
 
gSuChiGluSui = 0._dp 
Call SuToChiGluSu(i_run,MChi,MGlu,MSu,MFu,cplcFuChiSuL,cplcFuChiSuR,cplcFuGluSuL,     & 
& cplcFuGluSuR,cplChiFucSuL,cplChiFucSuR,cplGluFucSuL,cplGluFucSuR,deltaM,               & 
& epsI,check,gSuChiGluSui)

gSuChiGluSu(i_run,:,:,:) = gSuChiGluSui 
gT(i_run) = gT(i_run) + Sum(gSuChiGluSui) 
 
gSuSdChicChai = 0._dp 
Call SuToSdChicCha(i_run,MSd,MChi,MCha,MVWm,MHpm,MFu,MFd,MSu,cplSdcHpmcSu,            & 
& cplSdcSucVWm,cplcChacFuSdL,cplcChacFuSdR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL, & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChiSdL,cplcFdChiSdR,cplChiFucSuL,     & 
& cplChiFucSuR,deltaM,epsI,check,gSuSdChicChai)

gSuSdChicCha(i_run,:,:,:) = gSuSdChicChai 
gT(i_run) = gT(i_run) + Sum(gSuSdChicChai) 
 
gSuFdFucSdi = 0._dp 
Call SuToFdFucSd(i_run,MFd,MFu,MSd,MCha,MChi,MGlu,MSu,cplcChaFdcSuL,cplcChaFdcSuR,    & 
& cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,gSuFdFucSdi)

gSuFdFucSd(i_run,:,:,:) = gSuFdFucSdi 
gT(i_run) = gT(i_run) + Sum(gSuFdFucSdi) 
 
gSuFdFvcSei = 0._dp 
Call SuToFdFvcSe(i_run,MFd,MSe,MCha,MSu,cplcChaFdcSuL,cplcChaFdcSuR,cplChaFvcSeL,     & 
& cplChaFvcSeR,deltaM,epsI,check,gSuFdFvcSei)

gSuFdFvcSe(i_run,:,:,:) = gSuFdFvcSei 
gT(i_run) = gT(i_run) + Sum(gSuFdFvcSei) 
 
gSuhhFdcChai = 0._dp 
Call SuTohhFdcCha(i_run,Mhh,MFd,MCha,MSu,cplhhSucSu,cplcChaChahhL,cplcChaChahhR,      & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdFdhhL,cplcFdFdhhR,deltaM,epsI,check,gSuhhFdcChai)

gSuhhFdcCha(i_run,:,:,:) = gSuhhFdcChai 
gT(i_run) = gT(i_run) + Sum(gSuhhFdcChai) 
 
gSuSuFdcFdi = 0._dp 
Call SuToSuFdcFd(i_run,MSu,MFd,MVZ,MAh,Mhh,MCha,cplAhSucSu,cplhhSucSu,cplSucSuVZ,     & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdFdAhL,cplcFdFdAhR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,deltaM,epsI,check,gSuSuFdcFdi)

gSuSuFdcFd(i_run,:,:,:) = gSuSuFdcFdi 
gT(i_run) = gT(i_run) + Sum(gSuSuFdcFdi) 
 
gSuFdSvcFei = 0._dp 
Call SuToFdSvcFe(i_run,MFd,MSv,MFe,MCha,MSu,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplcFeChaSvL,cplcFeChaSvR,deltaM,epsI,check,gSuFdSvcFei)

gSuFdSvcFe(i_run,:,:,:) = gSuFdSvcFei 
gT(i_run) = gT(i_run) + Sum(gSuFdSvcFei) 
 
gSucHpmChaFui = 0._dp 
Call SuTocHpmChaFu(i_run,MHpm,MCha,MFu,MSd,MChi,MSu,cplSdcHpmcSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,deltaM,           & 
& epsI,check,gSucHpmChaFui)

gSucHpmChaFu(i_run,:,:,:) = gSucHpmChaFui 
gT(i_run) = gT(i_run) + Sum(gSucHpmChaFui) 
 
gSuFuFecSei = 0._dp 
Call SuToFuFecSe(i_run,MFu,MFe,MSe,MChi,MSu,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,   & 
& cplChiFucSuR,deltaM,epsI,check,gSuFuFecSei)

gSuFuFecSe(i_run,:,:,:) = gSuFuFecSei 
gT(i_run) = gT(i_run) + Sum(gSuFuFecSei) 
 
gSuFuFucSui = 0._dp 
Call SuToFuFucSu(i_run,MFu,MSu,MChi,MGlu,cplChiFucSuL,cplChiFucSuR,cplGluFucSuL,      & 
& cplGluFucSuR,deltaM,epsI,check,gSuFuFucSui)

gSuFuFucSu(i_run,:,:,:) = gSuFuFucSui 
gT(i_run) = gT(i_run) + Sum(gSuFuFucSui) 
 
gSuFuFvcSvi = 0._dp 
Call SuToFuFvcSv(i_run,MFu,MSv,MChi,MSu,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,       & 
& cplChiFvcSvR,deltaM,epsI,check,gSuFuFvcSvi)

gSuFuFvcSv(i_run,:,:,:) = gSuFuFvcSvi 
gT(i_run) = gT(i_run) + Sum(gSuFuFvcSvi) 
 
gSucChaFuHpmi = 0._dp 
Call SuTocChaFuHpm(i_run,MCha,MFu,MHpm,MFd,MChi,MSu,cplcChaChiHpmL,cplcChaChiHpmR,    & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdFuHpmL,cplcFdFuHpmR,cplChiFucSuL,cplChiFucSuR,       & 
& deltaM,epsI,check,gSucChaFuHpmi)

gSucChaFuHpm(i_run,:,:,:) = gSucChaFuHpmi 
gT(i_run) = gT(i_run) + Sum(gSucChaFuHpmi) 
 
gSuSdFucFdi = 0._dp 
Call SuToSdFucFd(i_run,MSd,MFu,MFd,MVWm,MHpm,MChi,MGlu,MSu,cplSdcHpmcSu,              & 
& cplSdcSucVWm,cplcFdChiSdL,cplcFdChiSdR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplChiFucSuL,cplChiFucSuR,cplGluFucSuL,         & 
& cplGluFucSuR,deltaM,epsI,check,gSuSdFucFdi)

gSuSdFucFd(i_run,:,:,:) = gSuSdFucFdi 
gT(i_run) = gT(i_run) + Sum(gSuSdFucFdi) 
 
gSuFuSecFei = 0._dp 
Call SuToFuSecFe(i_run,MFu,MSe,MFe,MChi,MSu,cplcFeChiSeL,cplcFeChiSeR,cplChiFucSuL,   & 
& cplChiFucSuR,deltaM,epsI,check,gSuFuSecFei)

gSuFuSecFe(i_run,:,:,:) = gSuFuSecFei 
gT(i_run) = gT(i_run) + Sum(gSuFuSecFei) 
 
gSuSuFucFui = 0._dp 
Call SuToSuFucFu(i_run,MSu,MFu,MVZ,MAh,Mhh,MChi,MGlu,cplAhSucSu,cplhhSucSu,           & 
& cplSucSuVZ,cplcFuChiSuL,cplcFuChiSuR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChiFucSuL,            & 
& cplChiFucSuR,cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,gSuSuFucFui)

gSuSuFucFu(i_run,:,:,:) = gSuSuFucFui 
gT(i_run) = gT(i_run) + Sum(gSuSuFucFui) 
 
gSuFuSvcFvi = 0._dp 
Call SuToFuSvcFv(i_run,MFu,MSv,MChi,MSu,cplcFvChiSvL,cplcFvChiSvR,cplChiFucSuL,       & 
& cplChiFucSuR,deltaM,epsI,check,gSuFuSvcFvi)

gSuFuSvcFv(i_run,:,:,:) = gSuFuSvcFvi 
gT(i_run) = gT(i_run) + Sum(gSuFuSvcFvi) 
 
gSucHpmFdGlui = 0._dp 
Call SuTocHpmFdGlu(i_run,MHpm,MFd,MGlu,MSd,MFu,MSu,cplSdcHpmcSu,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,deltaM,              & 
& epsI,check,gSucHpmFdGlui)

gSucHpmFdGlu(i_run,:,:,:) = gSucHpmFdGlui 
gT(i_run) = gT(i_run) + Sum(gSucHpmFdGlui) 
 
gSuhhFuGlui = 0._dp 
Call SuTohhFuGlu(i_run,Mhh,MFu,MGlu,MSu,cplhhSucSu,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,gSuhhFuGlui)

gSuhhFuGlu(i_run,:,:,:) = gSuhhFuGlui 
gT(i_run) = gT(i_run) + Sum(gSuhhFuGlui) 
 
gSuGluGluSui = 0._dp 
Call SuToGluGluSu(i_run,MGlu,MSu,MFu,cplcFuGluSuL,cplcFuGluSuR,cplGluFucSuL,          & 
& cplGluFucSuR,deltaM,epsI,check,gSuGluGluSui)

gSuGluGluSu(i_run,:,:,:) = gSuGluGluSui 
gT(i_run) = gT(i_run) + Sum(gSuGluGluSui) 
 
gSuGluSdcChai = 0._dp 
Call SuToGluSdcCha(i_run,MGlu,MSd,MCha,MFu,MFd,MSu,cplcChacFuSdL,cplcChacFuSdR,       & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdGluSdL,cplcFdGluSdR,cplGluFucSuL,cplGluFucSuR,       & 
& deltaM,epsI,check,gSuGluSdcChai)

gSuGluSdcCha(i_run,:,:,:) = gSuGluSdcChai 
gT(i_run) = gT(i_run) + Sum(gSuGluSdcChai) 
 
gSuSdFvcFei = 0._dp 
Call SuToSdFvcFe(i_run,MSd,MFe,MVWm,MHpm,MSu,cplSdcHpmcSu,cplSdcSucVWm,               & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,deltaM,epsI,check,gSuSdFvcFei)

gSuSdFvcFe(i_run,:,:,:) = gSuSdFvcFei 
gT(i_run) = gT(i_run) + Sum(gSuSdFvcFei) 
 
gSuSuChacChai = 0._dp 
Call SuToSuChacCha(i_run,MSu,MCha,MVZ,MAh,Mhh,MFd,cplAhSucSu,cplhhSucSu,              & 
& cplSucSuVZ,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,deltaM,            & 
& epsI,check,gSuSuChacChai)

gSuSuChacCha(i_run,:,:,:) = gSuSuChacChai 
gT(i_run) = gT(i_run) + Sum(gSuSuChacChai) 
 
gSuSuFecFei = 0._dp 
Call SuToSuFecFe(i_run,MSu,MFe,MVZ,MAh,Mhh,cplAhSucSu,cplhhSucSu,cplSucSuVZ,          & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& deltaM,epsI,check,gSuSuFecFei)

gSuSuFecFe(i_run,:,:,:) = gSuSuFecFei 
gT(i_run) = gT(i_run) + Sum(gSuSuFecFei) 
 
gSuSuFvcFvi = 0._dp 
Call SuToSuFvcFv(i_run,MSu,MVZ,cplSucSuVZ,cplcFvFvVZL,cplcFvFvVZR,deltaM,             & 
& epsI,check,gSuSuFvcFvi)

gSuSuFvcFv(i_run,:,:,:) = gSuSuFvcFvi 
gT(i_run) = gT(i_run) + Sum(gSuSuFvcFvi) 
 
End Do 
 

If (Present(gPartial)) Then
Do i1 = i_start, i_end 
 
n_length=1
Do gt1=2,2
  Do gt2=1,4
    Do gt3=1,3
gPartial(i1,n_length)= gSuAhChiFu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=2,2
  Do gt2=1,3
    Do gt3=1,2
gPartial(i1,n_length)= gSuAhFdcCha(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=2,2
  Do gt2=1,3
    Do gt3=1,1
gPartial(i1,n_length)= gSuAhFuGlu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,4
    Do gt3=gt2,4
gPartial(i1,n_length)= gSuSuChiChi(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=2,2
  Do gt2=1,4
    Do gt3=1,3
gPartial(i1,n_length)= gSucHpmChiFd(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,2
  Do gt2=1,4
    Do gt3=1,3
gPartial(i1,n_length)= gSuhhChiFu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,4
  Do gt2=1,1
    Do gt3=1,6
gPartial(i1,n_length)= gSuChiGluSu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,4
    Do gt3=1,2
gPartial(i1,n_length)= gSuSdChicCha(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,6
gPartial(i1,n_length)= gSuFdFucSd(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,6
gPartial(i1,n_length)= gSuFdFvcSe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,2
gPartial(i1,n_length)= gSuhhFdcCha(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuSuFdcFd(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuFdSvcFe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=2,2
  Do gt2=1,2
    Do gt3=1,3
gPartial(i1,n_length)= gSucHpmChaFu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,6
gPartial(i1,n_length)= gSuFuFecSe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=gt1,3
    Do gt3=1,6
gPartial(i1,n_length)= gSuFuFucSu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuFuFvcSv(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=2,2
gPartial(i1,n_length)= gSucChaFuHpm(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuSdFucFd(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,6
    Do gt3=1,3
gPartial(i1,n_length)= gSuFuSecFe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuSuFucFu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuFuSvcFv(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=2,2
  Do gt2=1,3
    Do gt3=1,1
gPartial(i1,n_length)= gSucHpmFdGlu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,1
gPartial(i1,n_length)= gSuhhFuGlu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,1
  Do gt2=gt1,1
    Do gt3=1,6
gPartial(i1,n_length)= gSuGluGluSu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,1
  Do gt2=1,6
    Do gt3=1,2
gPartial(i1,n_length)= gSuGluSdcCha(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuSdFvcFe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,2
    Do gt3=1,2
gPartial(i1,n_length)= gSuSuChacCha(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuSuFecFe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,6
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gSuSuFvcFv(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
If (Present(BR).And.(gT(i1).Gt.0._dp)) Then 
BR(i1,:)=gPartial(i1,:)/gT(i1)
Else If (Present(BR)) Then
BR(i1,:)=0._dp
End If
 
End Do 
End if 
Iname = Iname - 1 
 
End Subroutine SuThreeBodyDecay
 
 
Subroutine SuToAhChiFu(iIN,MAh,MChi,MFu,MSu,cplAhSucSu,cplcFuFuAhL,cplcFuFuAhR,       & 
& cplChiChiAhL,cplChiChiAhR,cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,g,               & 
& WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MAh(2),MChi(4),MFu(3),MSu(6)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplChiChiAhL(4,4,2),          & 
& cplChiChiAhR(4,4,2),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 169 
Allocate( gSum(2,4,3, Isum) ) 
Allocate( Contribution(2,4,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=2,2
      Do gt2=1,4
        Do gt3=1,3
Isum = 0 
 
rk2 = (MChi(gt2)/MSu(iIN))**2 
rm2 = (MFu(gt3)/MSu(iIN))**2 
rj2 = (MAh(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFu(gt3))+Abs(MChi(gt2))+Abs(MAh(gt1)))) Then 
!-------------- 
!  Su 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSu(i1) 
mass(2) = MSu(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiFucSuR(gt2,gt3,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Su'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt2,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt2,i1,iIN)) 
coup(4) = Conjg(cplcFuFuAhL(i1,gt3,gt1)) 
coup(3) = Conjg(cplcFuFuAhR(i1,gt3,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt3,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt3,iIN)) 
coup(4) = Conjg(cplChiChiAhL(i1,gt2,gt1)) 
coup(3) = Conjg(cplChiChiAhR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Su, Su 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSu(i1)  
mass(2) = MSu(i2)  
coup(1) = cplAhSucSu(gt1,i1,iIN) 
coup(3) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiFucSuR(gt2,gt3,i1))  
coup(4) = cplAhSucSu(gt1,i2,iIN) 
coup(6) = Conjg(cplChiFucSuL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChiFucSuR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Su,Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Su'
        End Do 
      End Do 



!-------------- 
!  Su, Fu 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcFuFuAhL(i2,gt3,gt1)) 
coup(3) = Conjg(cplcFuFuAhR(i2,gt3,gt1))  
coup(5) = cplAhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiFucSuR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Su,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Fu'
        End Do 
      End Do 



!-------------- 
!  Su, Chi 
!-------------- 
Do i1=1,6
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MChi(i2)  
coup(1) = cplChiFucSuL(i2,gt3,iIN) 
coup(2) = cplChiFucSuR(i2,gt3,iIN) 
coup(4) = Conjg(cplChiChiAhL(i2,gt2,gt1)) 
coup(3) = Conjg(cplChiChiAhR(i2,gt2,gt1))  
coup(5) = cplAhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiFucSuR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Su,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Chi'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuFuAhL(i1,gt3,gt1) 
coup(4) = cplcFuFuAhR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(gt2,i2,iIN) 
coup(6) = cplChiFucSuR(gt2,i2,iIN)  
coup(7) = cplcFuFuAhL(i2,gt3,gt1) 
coup(8) = cplcFuFuAhR(i2,gt3,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Chi 
!-------------- 
Do i1=1,3
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuFuAhL(i1,gt3,gt1) 
coup(4) = cplcFuFuAhR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(i2,gt3,iIN) 
coup(6) = cplChiFucSuR(i2,gt3,iIN)  
coup(7) = cplChiChiAhL(i2,gt2,gt1) 
coup(8) = cplChiChiAhR(i2,gt2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Fu,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt3,iIN) 
coup(2) = cplChiFucSuR(i1,gt3,iIN) 
coup(3) = cplChiChiAhL(i1,gt2,gt1) 
coup(4) = cplChiChiAhR(i1,gt2,gt1) 
coup(5) = cplChiFucSuL(i2,gt3,iIN) 
coup(6) = cplChiFucSuR(i2,gt3,iIN)  
coup(7) = cplChiChiAhL(i2,gt2,gt1) 
coup(8) = cplChiChiAhR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Chi Fu Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=2,2
      Do gt2=1,4
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:169))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToAhChiFu 
 
 
Subroutine SuToAhFdcCha(iIN,MAh,MFd,MCha,MSu,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,  & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdFdAhL,cplcFdFdAhR,deltaM,epsI,check,g,               & 
& WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MAh(2),MFd(3),MCha(2),MSu(6)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaFdcSuL(2,3,6),     & 
& cplcChaFdcSuR(2,3,6),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 121 
Allocate( gSum(2,3,2, Isum) ) 
Allocate( Contribution(2,3,2, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=2,2
      Do gt2=1,3
        Do gt3=1,2
Isum = 0 
 
rk2 = (MFd(gt2)/MSu(iIN))**2 
rm2 = (MCha(gt3)/MSu(iIN))**2 
rj2 = (MAh(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MCha(gt3))+Abs(MFd(gt2))+Abs(MAh(gt1)))) Then 
!-------------- 
!  Su 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSu(i1) 
mass(2) = MSu(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Su'
      End Do 



!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplcChaChaAhL(gt3,i1,gt1)) 
coup(3) = Conjg(cplcChaChaAhR(gt3,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  Fd 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFd(i1) 
mass(2) = MFd(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(gt3,i1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(gt3,i1,iIN)) 
coup(4) = Conjg(cplcFdFdAhL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFdFdAhR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd'
      End Do 



!-------------- 
!  Su, Su 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSu(i1)  
mass(2) = MSu(i2)  
coup(1) = cplAhSucSu(gt1,i1,iIN) 
coup(3) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))  
coup(4) = cplAhSucSu(gt1,i2,iIN) 
coup(6) = Conjg(cplcChaFdcSuL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcChaFdcSuR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: Su,Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Su'
        End Do 
      End Do 



!-------------- 
!  Su, bar[Cha] 
!-------------- 
Do i1=1,6
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcChaChaAhL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcChaChaAhR(gt3,i2,gt1))  
coup(5) = cplAhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: Su,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  Su, Fd 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdFdAhL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdFdAhR(i2,gt2,gt1))  
coup(5) = cplAhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: Su,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Fd'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt2,iIN) 
coup(3) = cplcChaChaAhL(gt3,i1,gt1) 
coup(4) = cplcChaChaAhR(gt3,i1,gt1) 
coup(5) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt2,iIN)  
coup(7) = cplcChaChaAhL(gt3,i2,gt1) 
coup(8) = cplcChaChaAhR(gt3,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], Fd 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(i1,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt2,iIN) 
coup(3) = cplcChaChaAhL(gt3,i1,gt1) 
coup(4) = cplcChaChaAhR(gt3,i1,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdFdAhL(i2,gt2,gt1) 
coup(8) = cplcFdFdAhR(i2,gt2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: bar[Cha],Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],Fd'
        End Do 
      End Do 



!-------------- 
!  Fd, Fd 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i1,iIN) 
coup(3) = cplcFdFdAhL(i1,gt2,gt1) 
coup(4) = cplcFdFdAhR(i1,gt2,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdFdAhL(i2,gt2,gt1) 
coup(8) = cplcFdFdAhR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fd cCha Propagator: Fd,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd,Fd'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=2,2
      Do gt2=1,3
        Do gt3=1,2
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:121))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToAhFdcCha 
 
 
Subroutine SuToAhFuGlu(iIN,MAh,MFu,MGlu,MSu,cplAhSucSu,cplcFuFuAhL,cplcFuFuAhR,       & 
& cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MAh(2),MFu(3),MGlu,MSu(6)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplGluFucSuL(3,6),            & 
& cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 81 
Allocate( gSum(2,3,1, Isum) ) 
Allocate( Contribution(2,3,1, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=2,2
      Do gt2=1,3
Isum = 0 
 
rk2 = (MFu(gt2)/MSu(iIN))**2 
rm2 = (MGlu/MSu(iIN))**2 
rj2 = (MAh(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MGlu)+Abs(MFu(gt2))+Abs(MAh(gt1)))) Then 
!-------------- 
!  Su 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSu(i1) 
mass(2) = MSu(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplGluFucSuL(gt2,i1)) 
coup(2) = Conjg(cplGluFucSuR(gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fu Glu Propagator: Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp
Else 
gSum(gt1,gt2,1,Isum)=resD
End If 
Contribution(gt1,gt2,1,Isum)='Su'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcFuFuAhL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFuFuAhR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fu Glu Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp
Else 
gSum(gt1,gt2,1,Isum)=resD
End If 
Contribution(gt1,gt2,1,Isum)='Fu'
      End Do 



!-------------- 
!  Su, Su 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSu(i1)  
mass(2) = MSu(i2)  
coup(1) = cplAhSucSu(gt1,i1,iIN) 
coup(3) = Conjg(cplGluFucSuL(gt2,i1)) 
coup(2) = Conjg(cplGluFucSuR(gt2,i1))  
coup(4) = cplAhSucSu(gt1,i2,iIN) 
coup(6) = Conjg(cplGluFucSuL(gt2,i2)) 
coup(5) = Conjg(cplGluFucSuR(gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fu Glu Propagator: Su,Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Su,Su'
        End Do 
      End Do 



!-------------- 
!  Su, Fu 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MFu(i2)  
coup(1) = cplGluFucSuL(i2,iIN) 
coup(2) = cplGluFucSuR(i2,iIN) 
coup(4) = Conjg(cplcFuFuAhL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFuFuAhR(i2,gt2,gt1))  
coup(5) = cplAhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplGluFucSuL(gt2,i1)) 
coup(6) = Conjg(cplGluFucSuR(gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fu Glu Propagator: Su,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Su,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuFuAhL(i1,gt2,gt1) 
coup(4) = cplcFuFuAhR(i1,gt2,gt1) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuFuAhL(i2,gt2,gt1) 
coup(8) = cplcFuFuAhR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Ah Fu Glu Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Fu,Fu'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,1,:)= 0._dp  
End If 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=2,2
      Do gt2=1,3
g(gt1,gt2,1)=Sum(gSum(gt1,gt2,1,1:81))
If (g(gt1,gt2,1).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,1)=0._dp
End If
     End Do 
   End Do 
End Subroutine SuToAhFuGlu 
 
 
Subroutine SuToSuChiChi(iIN,MSu,MChi,MVZ,MAh,Mhh,MFu,cplAhSucSu,cplhhSucSu,           & 
& cplSucSuVZ,cplcFuChiSuL,cplcFuChiSuR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,           & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,deltaM,               & 
& epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSu(6),MChi(4),MVZ,MAh(2),Mhh(2),MFu(3)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplhhSucSu(2,6,6),cplSucSuVZ(6,6),cplcFuChiSuL(3,4,6),              & 
& cplcFuChiSuR(3,4,6),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),cplChiChihhL(4,4,2),       & 
& cplChiChihhR(4,4,2),cplChiChiVZL(4,4),cplChiChiVZR(4,4),cplChiFucSuL(4,3,6),           & 
& cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 64 
Allocate( gSum(6,4,4, Isum) ) 
Allocate( Contribution(6,4,4, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,4
        Do gt3=gt2,4
Isum = 0 
 
rk2 = (MChi(gt2)/MSu(iIN))**2 
rm2 = (MChi(gt3)/MSu(iIN))**2 
rj2 = (MSu(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MChi(gt3))+Abs(MChi(gt2))+Abs(MSu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplChiChiVZL(gt2,gt3)) 
coup(2) = Conjg(cplChiChiVZR(gt2,gt3))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplChiChiVZL(gt3,gt2)) 
coup(2) = Conjg(cplChiChiVZR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MAh(i1) 
mass(2) = MAh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplChiChiAhL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiChiAhR(gt2,gt3,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MAh(i1) 
mass(2) = MAh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplChiChiAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplChiChiAhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MAh(i1)  
mass(2) = MAh(i1)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChiChiAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplChiChiAhR(gt3,gt2,i1))  
coup(4) = cplAhSucSu(i1,gt1,iIN) 
coup(6) = Conjg(cplChiChiAhL(gt2,gt3,i1)) 
coup(5) = Conjg(cplChiChiAhR(gt2,gt3,i1))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = Mhh(i1) 
mass(2) = Mhh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplChiChihhL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiChihhR(gt2,gt3,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = Mhh(i1) 
mass(2) = Mhh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplChiChihhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplChiChihhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = Mhh(i1)  
mass(2) = Mhh(i1)  
coup(1) = cplhhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChiChihhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplChiChihhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i1,gt1,iIN) 
coup(6) = Conjg(cplChiChihhL(gt2,gt3,i1)) 
coup(5) = Conjg(cplChiChihhR(gt2,gt3,i1))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt2,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt2,i1,iIN)) 
coup(4) = Conjg(cplcFuChiSuL(i1,gt3,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i1,gt3,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt3,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt3,i1,iIN)) 
coup(4) = Conjg(cplcFuChiSuL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MFu(i1)  
mass(2) = MFu(i1)  
coup(1) = cplChiFucSuL(gt3,i1,iIN) 
coup(2) = cplChiFucSuR(gt3,i1,iIN) 
coup(3) = cplcFuChiSuL(i1,gt2,gt1) 
coup(4) = cplcFuChiSuR(i1,gt2,gt1) 
coup(5) = cplChiFucSuL(gt2,i1,iIN) 
coup(6) = cplChiFucSuR(gt2,i1,iIN)  
coup(7) = cplcFuChiSuL(i1,gt3,gt1) 
coup(8) = cplcFuChiSuR(i1,gt3,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = MAh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplChiChiVZL(gt2,gt3)) 
coup(3) = Conjg(cplChiChiVZR(gt2,gt3))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplChiChiAhL(gt2,gt3,i2)) 
coup(6) = Conjg(cplChiChiAhR(gt2,gt3,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = Mhh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplChiChiVZL(gt2,gt3)) 
coup(3) = Conjg(cplChiChiVZR(gt2,gt3))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplChiChihhL(gt2,gt3,i2)) 
coup(6) = Conjg(cplChiChihhR(gt2,gt3,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  VZ, Fu 
!-------------- 
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ2  
mass(1) = MFu2(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(i2,gt3,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i2,gt3,gt1))  
coup(5) = cplSucSuVZ(gt1,iIN) 
coup(7) = Conjg(cplChiChiVZL(gt2,gt3)) 
coup(6) = Conjg(cplChiChiVZR(gt2,gt3))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MVZ2  
mass(1) = MFu2(i2)  
coup(1) = cplChiFucSuL(gt3,i2,iIN) 
coup(2) = cplChiFucSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i2,gt2,gt1))  
coup(5) = cplSucSuVZ(gt1,iIN) 
coup(7) = Conjg(cplChiChiVZL(gt2,gt3)) 
coup(6) = Conjg(cplChiChiVZR(gt2,gt3))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: VZ,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Fu'
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = MAh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChiChiAhL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiChiAhR(gt2,gt3,i1))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplChiChiAhL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChiChiAhR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChiChiAhL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiChiAhR(gt2,gt3,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplChiChihhL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChiChihhR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  Ah, Fu 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MAh(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(i2,gt3,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i2,gt3,gt1))  
coup(5) = cplAhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChiChiAhL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiChiAhR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MAh(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt3,i2,iIN) 
coup(2) = cplChiFucSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i2,gt2,gt1))  
coup(5) = cplAhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChiChiAhL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiChiAhR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: Ah,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Fu'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = Mhh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplhhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChiChihhL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiChihhR(gt2,gt3,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplChiChihhL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChiChihhR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



!-------------- 
!  hh, Fu 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = Mhh(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(i2,gt3,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i2,gt3,gt1))  
coup(5) = cplhhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChiChihhL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiChihhR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = Mhh(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt3,i2,iIN) 
coup(2) = cplChiFucSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(i2,gt2,gt1))  
coup(5) = cplhhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChiChihhL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiChihhR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: hh,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuChiSuL(i1,gt3,gt1) 
coup(4) = cplcFuChiSuR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(gt2,i2,iIN) 
coup(6) = cplChiFucSuR(gt2,i2,iIN)  
coup(7) = cplcFuChiSuL(i2,gt3,gt1) 
coup(8) = cplcFuChiSuR(i2,gt3,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt3,i1,iIN) 
coup(2) = cplChiFucSuR(gt3,i1,iIN) 
coup(3) = cplcFuChiSuL(i1,gt2,gt1) 
coup(4) = cplcFuChiSuR(i1,gt2,gt1) 
coup(5) = cplChiFucSuL(gt2,i2,iIN) 
coup(6) = cplChiFucSuR(gt2,i2,iIN)  
coup(7) = cplcFuChiSuL(i2,gt3,gt1) 
coup(8) = cplcFuChiSuR(i2,gt3,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt3,i1,iIN) 
coup(2) = cplChiFucSuR(gt3,i1,iIN) 
coup(3) = cplcFuChiSuL(i1,gt2,gt1) 
coup(4) = cplcFuChiSuR(i1,gt2,gt1) 
coup(5) = cplChiFucSuL(gt3,i2,iIN) 
coup(6) = cplChiFucSuR(gt3,i2,iIN)  
coup(7) = cplcFuChiSuL(i2,gt2,gt1) 
coup(8) = cplcFuChiSuR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuChiSuL(i1,gt3,gt1) 
coup(4) = cplcFuChiSuR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(gt3,i2,iIN) 
coup(6) = cplChiFucSuR(gt3,i2,iIN)  
coup(7) = cplcFuChiSuL(i2,gt2,gt1) 
coup(8) = cplcFuChiSuR(i2,gt2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
If (gt3.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Chi Chi Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,4
        Do gt3=gt2,4
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:64))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSuChiChi 
 
 
Subroutine SuTocHpmChiFd(iIN,MHpm,MChi,MFd,MSd,MFu,MCha,MSu,cplSdcHpmcSu,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplChiChacHpmL,cplChiChacHpmR, & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,g,               & 
& WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MHpm(2),MChi(4),MFd(3),MSd(6),MFu(3),MCha(2),MSu(6)

Complex(dp),Intent(in) :: cplSdcHpmcSu(6,2,6),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),   & 
& cplcFuFdcHpmR(3,3,2),cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),cplChiFdcSdL(4,3,6),  & 
& cplChiFdcSdR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 121 
Allocate( gSum(2,4,3, Isum) ) 
Allocate( Contribution(2,4,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=2,2
      Do gt2=1,4
        Do gt3=1,3
Isum = 0 
 
rk2 = (MChi(gt2)/MSu(iIN))**2 
rm2 = (MFd(gt3)/MSu(iIN))**2 
rj2 = (MHpm(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFd(gt3))+Abs(MChi(gt2))+Abs(MHpm(gt1)))) Then 
!-------------- 
!  Sd 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSd(i1) 
mass(2) = MSd(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcHpmcSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplChiFdcSdL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiFdcSdR(gt2,gt3,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Sd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt2,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt2,i1,iIN)) 
coup(4) = Conjg(cplcFuFdcHpmL(i1,gt3,gt1)) 
coup(3) = Conjg(cplcFuFdcHpmR(i1,gt3,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt3,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt3,iIN)) 
coup(4) = Conjg(cplChiChacHpmL(gt2,i1,gt1)) 
coup(3) = Conjg(cplChiChacHpmR(gt2,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  Sd, Sd 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSd(i1)  
mass(2) = MSd(i2)  
coup(1) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChiFdcSdL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiFdcSdR(gt2,gt3,i1))  
coup(4) = cplSdcHpmcSu(i2,gt1,iIN) 
coup(6) = Conjg(cplChiFdcSdL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChiFdcSdR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Sd,Sd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd,Sd'
        End Do 
      End Do 



!-------------- 
!  Sd, Fu 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSd(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcFuFdcHpmL(i2,gt3,gt1)) 
coup(3) = Conjg(cplcFuFdcHpmR(i2,gt3,gt1))  
coup(5) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChiFdcSdL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiFdcSdR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Sd,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd,Fu'
        End Do 
      End Do 



!-------------- 
!  Sd, bar[Cha] 
!-------------- 
Do i1=1,6
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSd(i1)  
mass(1) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i2,gt3,iIN) 
coup(2) = cplcChaFdcSuR(i2,gt3,iIN) 
coup(4) = Conjg(cplChiChacHpmL(gt2,i2,gt1)) 
coup(3) = Conjg(cplChiChacHpmR(gt2,i2,gt1))  
coup(5) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChiFdcSdL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiFdcSdR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Sd,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd,bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuFdcHpmL(i1,gt3,gt1) 
coup(4) = cplcFuFdcHpmR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(gt2,i2,iIN) 
coup(6) = cplChiFucSuR(gt2,i2,iIN)  
coup(7) = cplcFuFdcHpmL(i2,gt3,gt1) 
coup(8) = cplcFuFdcHpmR(i2,gt3,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, bar[Cha] 
!-------------- 
Do i1=1,3
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MCha(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuFdcHpmL(i1,gt3,gt1) 
coup(4) = cplcFuFdcHpmR(i1,gt3,gt1) 
coup(5) = cplcChaFdcSuL(i2,gt3,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt3,iIN)  
coup(7) = cplChiChacHpmL(gt2,i2,gt1) 
coup(8) = cplChiChacHpmR(gt2,i2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: Fu,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt3,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt3,iIN) 
coup(3) = cplChiChacHpmL(gt2,i1,gt1) 
coup(4) = cplChiChacHpmR(gt2,i1,gt1) 
coup(5) = cplcChaFdcSuL(i2,gt3,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt3,iIN)  
coup(7) = cplChiChacHpmL(gt2,i2,gt1) 
coup(8) = cplChiChacHpmR(gt2,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Chi Fd Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=2,2
      Do gt2=1,4
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:121))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuTocHpmChiFd 
 
 
Subroutine SuTohhChiFu(iIN,Mhh,MChi,MFu,MSu,cplhhSucSu,cplcFuFuhhL,cplcFuFuhhR,       & 
& cplChiChihhL,cplChiChihhR,cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,g,               & 
& WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: Mhh(2),MChi(4),MFu(3),MSu(6)

Complex(dp),Intent(in) :: cplhhSucSu(2,6,6),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplChiChihhL(4,4,2),          & 
& cplChiChihhR(4,4,2),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 169 
Allocate( gSum(2,4,3, Isum) ) 
Allocate( Contribution(2,4,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,2
      Do gt2=1,4
        Do gt3=1,3
Isum = 0 
 
rk2 = (MChi(gt2)/MSu(iIN))**2 
rm2 = (MFu(gt3)/MSu(iIN))**2 
rj2 = (Mhh(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFu(gt3))+Abs(MChi(gt2))+Abs(Mhh(gt1)))) Then 
!-------------- 
!  Su 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSu(i1) 
mass(2) = MSu(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiFucSuR(gt2,gt3,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Su'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt2,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt2,i1,iIN)) 
coup(4) = Conjg(cplcFuFuhhL(i1,gt3,gt1)) 
coup(3) = Conjg(cplcFuFuhhR(i1,gt3,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt3,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt3,iIN)) 
coup(4) = Conjg(cplChiChihhL(i1,gt2,gt1)) 
coup(3) = Conjg(cplChiChihhR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Su, Su 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSu(i1)  
mass(2) = MSu(i2)  
coup(1) = cplhhSucSu(gt1,i1,iIN) 
coup(3) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChiFucSuR(gt2,gt3,i1))  
coup(4) = cplhhSucSu(gt1,i2,iIN) 
coup(6) = Conjg(cplChiFucSuL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChiFucSuR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Su,Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Su'
        End Do 
      End Do 



!-------------- 
!  Su, Fu 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcFuFuhhL(i2,gt3,gt1)) 
coup(3) = Conjg(cplcFuFuhhR(i2,gt3,gt1))  
coup(5) = cplhhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiFucSuR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Su,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Fu'
        End Do 
      End Do 



!-------------- 
!  Su, Chi 
!-------------- 
Do i1=1,6
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MChi(i2)  
coup(1) = cplChiFucSuL(i2,gt3,iIN) 
coup(2) = cplChiFucSuR(i2,gt3,iIN) 
coup(4) = Conjg(cplChiChihhL(i2,gt2,gt1)) 
coup(3) = Conjg(cplChiChihhR(i2,gt2,gt1))  
coup(5) = cplhhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplChiFucSuL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChiFucSuR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Su,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Chi'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuFuhhL(i1,gt3,gt1) 
coup(4) = cplcFuFuhhR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(gt2,i2,iIN) 
coup(6) = cplChiFucSuR(gt2,i2,iIN)  
coup(7) = cplcFuFuhhL(i2,gt3,gt1) 
coup(8) = cplcFuFuhhR(i2,gt3,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Chi 
!-------------- 
Do i1=1,3
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcFuFuhhL(i1,gt3,gt1) 
coup(4) = cplcFuFuhhR(i1,gt3,gt1) 
coup(5) = cplChiFucSuL(i2,gt3,iIN) 
coup(6) = cplChiFucSuR(i2,gt3,iIN)  
coup(7) = cplChiChihhL(i2,gt2,gt1) 
coup(8) = cplChiChihhR(i2,gt2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Fu,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt3,iIN) 
coup(2) = cplChiFucSuR(i1,gt3,iIN) 
coup(3) = cplChiChihhL(i1,gt2,gt1) 
coup(4) = cplChiChihhR(i1,gt2,gt1) 
coup(5) = cplChiFucSuL(i2,gt3,iIN) 
coup(6) = cplChiFucSuR(i2,gt3,iIN)  
coup(7) = cplChiChihhL(i2,gt2,gt1) 
coup(8) = cplChiChihhR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Chi Fu Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,2
      Do gt2=1,4
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:169))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuTohhChiFu 
 
 
Subroutine SuToChiGluSu(iIN,MChi,MGlu,MSu,MFu,cplcFuChiSuL,cplcFuChiSuR,              & 
& cplcFuGluSuL,cplcFuGluSuR,cplChiFucSuL,cplChiFucSuR,cplGluFucSuL,cplGluFucSuR,         & 
& deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MChi(4),MGlu,MSu(6),MFu(3)

Complex(dp),Intent(in) :: cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),          & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 36 
Allocate( gSum(4,1,6, Isum) ) 
Allocate( Contribution(4,1,6, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,4
        Do gt3=1, iIN-1
Isum = 0 
 
rk2 = (MChi(gt1)/MSu(iIN))**2 
rm2 = (MGlu/MSu(iIN))**2 
rj2 = (MSu(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSu(gt3))+Abs(MGlu)+Abs(MChi(gt1)))) Then 
!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt1,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt1,i1,iIN)) 
coup(4) = Conjg(cplcFuGluSuL(i1,gt3)) 
coup(3) = Conjg(cplcFuGluSuR(i1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Chi Glu Su Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,1,gt3,Isum)= 0._dp
Else 
gSum(gt1,1,gt3,Isum)=resD
End If 
Contribution(gt1,1,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcFuChiSuL(i1,gt1,gt3)) 
coup(3) = Conjg(cplcFuChiSuR(i1,gt1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Chi Glu Su Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,1,gt3,Isum)= 0._dp
Else 
gSum(gt1,1,gt3,Isum)=resD
End If 
Contribution(gt1,1,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt1,i1,iIN) 
coup(2) = cplChiFucSuR(gt1,i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplChiFucSuL(gt1,i2,iIN) 
coup(6) = cplChiFucSuR(gt1,i2,iIN)  
coup(7) = cplcFuGluSuL(i2,gt3) 
coup(8) = cplcFuGluSuR(i2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Chi Glu Su Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,1,gt3,Isum)= 0._dp  
Else 
gSum(gt1,1,gt3,Isum)= resS  
End If 
Contribution(gt1,1,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,3
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt1,i1,iIN) 
coup(2) = cplChiFucSuR(gt1,i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuChiSuL(i2,gt1,gt3) 
coup(8) = cplcFuChiSuR(i2,gt1,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Chi Glu Su Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,1,gt3,Isum)= 0._dp  
Else 
gSum(gt1,1,gt3,Isum)= resS  
End If 
Contribution(gt1,1,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuChiSuL(i1,gt1,gt3) 
coup(4) = cplcFuChiSuR(i1,gt1,gt3) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuChiSuL(i2,gt1,gt3) 
coup(8) = cplcFuChiSuR(i2,gt1,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Chi Glu Su Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,1,gt3,Isum)= 0._dp  
Else 
gSum(gt1,1,gt3,Isum)= resS  
End If 
Contribution(gt1,1,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



Else 
gSum(gt1,1,gt3,:)= 0._dp  
End If 
       End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,4
        Do gt3=1, iIN-1
g(gt1,1,gt3)=Sum(gSum(gt1,1,gt3,1:36))
If (g(gt1,1,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,1,gt3)=0._dp
End If
       End Do 
   End Do 
End Subroutine SuToChiGluSu 
 
 
Subroutine SuToSdChicCha(iIN,MSd,MChi,MCha,MVWm,MHpm,MFu,MFd,MSu,cplSdcHpmcSu,        & 
& cplSdcSucVWm,cplcChacFuSdL,cplcChacFuSdR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL, & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChiSdL,cplcFdChiSdR,cplChiFucSuL,     & 
& cplChiFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSd(6),MChi(4),MCha(2),MVWm,MHpm(2),MFu(3),MFd(3),MSu(6)

Complex(dp),Intent(in) :: cplSdcHpmcSu(6,2,6),cplSdcSucVWm(6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),      & 
& cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),cplcChaChiVWmL(2,4),cplcChaChiVWmR(2,4),   & 
& cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),     & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 81 
Allocate( gSum(6,4,2, Isum) ) 
Allocate( Contribution(6,4,2, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,6
      Do gt2=1,4
        Do gt3=1,2
Isum = 0 
 
rk2 = (MChi(gt2)/MSu(iIN))**2 
rm2 = (MCha(gt3)/MSu(iIN))**2 
rj2 = (MSd(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MCha(gt3))+Abs(MChi(gt2))+Abs(MSd(gt1)))) Then 
!-------------- 
!  conj[VWm] 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVWm 
mass(2) = MVWm 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcSucVWm(gt1,iIN)) 
coup(3) = Conjg(cplcChaChiVWmL(gt3,gt2)) 
coup(2) = Conjg(cplcChaChiVWmR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[VWm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm]'



!-------------- 
!  conj[Hpm] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MHpm(i1) 
mass(2) = MHpm(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcHpmcSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplcChaChiHpmL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChiHpmR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm]'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(gt2,i1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(gt2,i1,iIN)) 
coup(4) = Conjg(cplcChacFuSdL(gt3,i1,gt1)) 
coup(3) = Conjg(cplcChacFuSdR(gt3,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Fd 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFd(i1) 
mass(2) = MFd(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(gt3,i1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(gt3,i1,iIN)) 
coup(4) = Conjg(cplcFdChiSdL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFdChiSdR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd'
      End Do 



!-------------- 
!  conj[VWm], conj[Hpm] 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm  
mass(1) = MHpm(i2)  
coup(1) = cplSdcSucVWm(gt1,iIN) 
coup(2) = Conjg(cplcChaChiVWmL(gt3,gt2)) 
coup(3) = Conjg(cplcChaChiVWmR(gt3,gt2))  
coup(4) = cplSdcHpmcSu(gt1,i2,iIN) 
coup(5) = Conjg(cplcChaChiHpmL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcChaChiHpmR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[VWm],conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],conj[Hpm]'
      End Do 



!-------------- 
!  conj[VWm], Fu 
!-------------- 
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm2  
mass(1) = MFu2(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcChacFuSdL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcChacFuSdR(gt3,i2,gt1))  
coup(5) = cplSdcSucVWm(gt1,iIN) 
coup(7) = Conjg(cplcChaChiVWmL(gt3,gt2)) 
coup(6) = Conjg(cplcChaChiVWmR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[VWm],Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],Fu'
      End Do 



!-------------- 
!  conj[VWm], Fd 
!-------------- 
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm2  
mass(1) = MFd2(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdChiSdL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdChiSdR(i2,gt2,gt1))  
coup(5) = cplSdcSucVWm(gt1,iIN) 
coup(7) = Conjg(cplcChaChiVWmL(gt3,gt2)) 
coup(6) = Conjg(cplcChaChiVWmR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[VWm],Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],Fd'
      End Do 



!-------------- 
!  conj[Hpm], conj[Hpm] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MHpm(i1)  
mass(2) = MHpm(i2)  
coup(1) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(3) = Conjg(cplcChaChiHpmL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChiHpmR(gt3,gt2,i1))  
coup(4) = cplSdcHpmcSu(gt1,i2,iIN) 
coup(6) = Conjg(cplcChaChiHpmL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcChaChiHpmR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[Hpm],conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],conj[Hpm]'
        End Do 
      End Do 



!-------------- 
!  conj[Hpm], Fu 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MHpm(i1)  
mass(1) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i2,iIN) 
coup(2) = cplChiFucSuR(gt2,i2,iIN) 
coup(4) = Conjg(cplcChacFuSdL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcChacFuSdR(gt3,i2,gt1))  
coup(5) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcChaChiHpmL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaChiHpmR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[Hpm],Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],Fu'
        End Do 
      End Do 



!-------------- 
!  conj[Hpm], Fd 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MHpm(i1)  
mass(1) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdChiSdL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdChiSdR(i2,gt2,gt1))  
coup(5) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcChaChiHpmL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaChiHpmR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: conj[Hpm],Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],Fd'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcChacFuSdL(gt3,i1,gt1) 
coup(4) = cplcChacFuSdR(gt3,i1,gt1) 
coup(5) = cplChiFucSuL(gt2,i2,iIN) 
coup(6) = cplChiFucSuR(gt2,i2,iIN)  
coup(7) = cplcChacFuSdL(gt3,i2,gt1) 
coup(8) = cplcChacFuSdR(gt3,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fd 
!-------------- 
Do i1=1,3
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFd(i2)  
coup(1) = cplChiFucSuL(gt2,i1,iIN) 
coup(2) = cplChiFucSuR(gt2,i1,iIN) 
coup(3) = cplcChacFuSdL(gt3,i1,gt1) 
coup(4) = cplcChacFuSdR(gt3,i1,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdChiSdL(i2,gt2,gt1) 
coup(8) = cplcFdChiSdR(i2,gt2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: Fu,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fu,Fd'
        End Do 
      End Do 



!-------------- 
!  Fd, Fd 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i1,iIN) 
coup(3) = cplcFdChiSdL(i1,gt2,gt1) 
coup(4) = cplcFdChiSdR(i1,gt2,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdChiSdL(i2,gt2,gt1) 
coup(8) = cplcFdChiSdR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Chi cCha Propagator: Fd,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd,Fd'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,6
      Do gt2=1,4
        Do gt3=1,2
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:81))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSdChicCha 
 
 
Subroutine SuToFdFucSd(iIN,MFd,MFu,MSd,MCha,MChi,MGlu,MSu,cplcChaFdcSuL,              & 
& cplcChaFdcSuR,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,        & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,deltaM,               & 
& epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFd(3),MFu(3),MSd(6),MCha(2),MChi(4),MGlu,MSu(6)

Complex(dp),Intent(in) :: cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),    & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 49 
Allocate( gSum(3,3,6, Isum) ) 
Allocate( Contribution(3,3,6, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,6
Isum = 0 
 
rk2 = (MFd(gt1)/MSu(iIN))**2 
rm2 = (MFu(gt2)/MSu(iIN))**2 
rj2 = (MSd(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSd(gt3))+Abs(MFu(gt2))+Abs(MFd(gt1)))) Then 
!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplChaFucSdL(i1,gt2,gt3)) 
coup(3) = Conjg(cplChaFucSdR(i1,gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplChiFdcSdL(i1,gt1,gt3)) 
coup(3) = Conjg(cplChiFdcSdR(i1,gt1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Glu 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MGlu 
mass(2) = MGlu 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(gt2,iIN)) 
coup(1) = Conjg(cplGluFucSuR(gt2,iIN)) 
coup(4) = Conjg(cplGluFdcSdL(gt1,gt3)) 
coup(3) = Conjg(cplGluFdcSdR(gt1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Glu'



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt1,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt1,iIN) 
coup(3) = cplChaFucSdL(i1,gt2,gt3) 
coup(4) = cplChaFucSdR(i1,gt2,gt3) 
coup(5) = cplcChaFdcSuL(i2,gt1,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt1,iIN)  
coup(7) = cplChaFucSdL(i2,gt2,gt3) 
coup(8) = cplChaFucSdR(i2,gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], Chi 
!-------------- 
Do i1=1,2
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MChi(i2)  
coup(1) = cplcChaFdcSuL(i1,gt1,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt1,iIN) 
coup(3) = cplChaFucSdL(i1,gt2,gt3) 
coup(4) = cplChaFucSdR(i1,gt2,gt3) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplChiFdcSdL(i2,gt1,gt3) 
coup(8) = cplChiFdcSdR(i2,gt1,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: bar[Cha],Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],Chi'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], Glu 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MGlu  
coup(1) = cplcChaFdcSuL(i1,gt1,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt1,iIN) 
coup(3) = cplChaFucSdL(i1,gt2,gt3) 
coup(4) = cplChaFucSdR(i1,gt2,gt3) 
coup(5) = cplGluFucSuL(gt2,iIN) 
coup(6) = cplGluFucSuR(gt2,iIN)  
coup(7) = cplGluFdcSdL(gt1,gt3) 
coup(8) = cplGluFdcSdR(gt1,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: bar[Cha],Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],Glu'
        End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFdcSdL(i1,gt1,gt3) 
coup(4) = cplChiFdcSdR(i1,gt1,gt3) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplChiFdcSdL(i2,gt1,gt3) 
coup(8) = cplChiFdcSdR(i2,gt1,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Glu 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFdcSdL(i1,gt1,gt3) 
coup(4) = cplChiFdcSdR(i1,gt1,gt3) 
coup(5) = cplGluFucSuL(gt2,iIN) 
coup(6) = cplGluFucSuR(gt2,iIN)  
coup(7) = cplGluFdcSdL(gt1,gt3) 
coup(8) = cplGluFdcSdR(gt1,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fu cSd Propagator: Chi,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Glu'
        End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,6
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:49))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFdFucSd 
 
 
Subroutine SuToFdFvcSe(iIN,MFd,MSe,MCha,MSu,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplChaFvcSeL,cplChaFvcSeR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFd(3),MSe(6),MCha(2),MSu(6)

Complex(dp),Intent(in) :: cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 4 
Allocate( gSum(3,3,6, Isum) ) 
Allocate( Contribution(3,3,6, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,6
Isum = 0 
 
rk2 = (MFd(gt1)/MSu(iIN))**2 
rm2 = (0./MSu(iIN))**2 
rj2 = (MSe(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSe(gt3))+Abs(0.)+Abs(MFd(gt1)))) Then 
!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplChaFvcSeL(i1,gt2,gt3)) 
coup(3) = Conjg(cplChaFvcSeR(i1,gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fv cSe Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt1,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt1,iIN) 
coup(3) = cplChaFvcSeL(i1,gt2,gt3) 
coup(4) = cplChaFvcSeR(i1,gt2,gt3) 
coup(5) = cplcChaFdcSuL(i2,gt1,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt1,iIN)  
coup(7) = cplChaFvcSeL(i2,gt2,gt3) 
coup(8) = cplChaFvcSeR(i2,gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Fv cSe Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,6
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:4))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFdFvcSe 
 
 
Subroutine SuTohhFdcCha(iIN,Mhh,MFd,MCha,MSu,cplhhSucSu,cplcChaChahhL,cplcChaChahhR,  & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdFdhhL,cplcFdFdhhR,deltaM,epsI,check,g,               & 
& WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: Mhh(2),MFd(3),MCha(2),MSu(6)

Complex(dp),Intent(in) :: cplhhSucSu(2,6,6),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),cplcChaFdcSuL(2,3,6),     & 
& cplcChaFdcSuR(2,3,6),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 121 
Allocate( gSum(2,3,2, Isum) ) 
Allocate( Contribution(2,3,2, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,2
      Do gt2=1,3
        Do gt3=1,2
Isum = 0 
 
rk2 = (MFd(gt2)/MSu(iIN))**2 
rm2 = (MCha(gt3)/MSu(iIN))**2 
rj2 = (Mhh(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MCha(gt3))+Abs(MFd(gt2))+Abs(Mhh(gt1)))) Then 
!-------------- 
!  Su 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSu(i1) 
mass(2) = MSu(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Su'
      End Do 



!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplcChaChahhL(gt3,i1,gt1)) 
coup(3) = Conjg(cplcChaChahhR(gt3,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  Fd 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFd(i1) 
mass(2) = MFd(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(gt3,i1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(gt3,i1,iIN)) 
coup(4) = Conjg(cplcFdFdhhL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFdFdhhR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd'
      End Do 



!-------------- 
!  Su, Su 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSu(i1)  
mass(2) = MSu(i2)  
coup(1) = cplhhSucSu(gt1,i1,iIN) 
coup(3) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(gt1,i2,iIN) 
coup(6) = Conjg(cplcChaFdcSuL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcChaFdcSuR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: Su,Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Su'
        End Do 
      End Do 



!-------------- 
!  Su, bar[Cha] 
!-------------- 
Do i1=1,6
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcChaChahhL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcChaChahhR(gt3,i2,gt1))  
coup(5) = cplhhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: Su,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  Su, Fd 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdFdhhL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdFdhhR(i2,gt2,gt1))  
coup(5) = cplhhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcChaFdcSuL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaFdcSuR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: Su,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Su,Fd'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt2,iIN) 
coup(3) = cplcChaChahhL(gt3,i1,gt1) 
coup(4) = cplcChaChahhR(gt3,i1,gt1) 
coup(5) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt2,iIN)  
coup(7) = cplcChaChahhL(gt3,i2,gt1) 
coup(8) = cplcChaChahhR(gt3,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], Fd 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(i1,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt2,iIN) 
coup(3) = cplcChaChahhL(gt3,i1,gt1) 
coup(4) = cplcChaChahhR(gt3,i1,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdFdhhL(i2,gt2,gt1) 
coup(8) = cplcFdFdhhR(i2,gt2,gt1) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: bar[Cha],Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],Fd'
        End Do 
      End Do 



!-------------- 
!  Fd, Fd 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i1,iIN) 
coup(3) = cplcFdFdhhL(i1,gt2,gt1) 
coup(4) = cplcFdFdhhR(i1,gt2,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdFdhhL(i2,gt2,gt1) 
coup(8) = cplcFdFdhhR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fd cCha Propagator: Fd,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd,Fd'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,2
      Do gt2=1,3
        Do gt3=1,2
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:121))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuTohhFdcCha 
 
 
Subroutine SuToSuFdcFd(iIN,MSu,MFd,MVZ,MAh,Mhh,MCha,cplAhSucSu,cplhhSucSu,            & 
& cplSucSuVZ,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,deltaM,epsI,               & 
& check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSu(6),MFd(3),MVZ,MAh(2),Mhh(2),MCha(2)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplhhSucSu(2,6,6),cplSucSuVZ(6,6),cplcChaFdcSuL(2,3,6),             & 
& cplcChaFdcSuR(2,3,6),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFdFdAhL(3,3,2),       & 
& cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVZL(3,3),             & 
& cplcFdFdVZR(3,3)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 49 
Allocate( gSum(6,3,3, Isum) ) 
Allocate( Contribution(6,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFd(gt2)/MSu(iIN))**2 
rm2 = (MFd(gt3)/MSu(iIN))**2 
rj2 = (MSu(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFd(gt3))+Abs(MFd(gt2))+Abs(MSu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplcFdFdVZL(gt3,gt2)) 
coup(2) = Conjg(cplcFdFdVZR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MAh(i1) 
mass(2) = MAh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcFdFdAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFdAhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = Mhh(i1) 
mass(2) = Mhh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcFdFdhhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFdhhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplcFdChaSuL(gt3,i1,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(gt3,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = MAh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcFdFdVZL(gt3,gt2)) 
coup(3) = Conjg(cplcFdFdVZR(gt3,gt2))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcFdFdAhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFdFdAhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = Mhh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcFdFdVZL(gt3,gt2)) 
coup(3) = Conjg(cplcFdFdVZR(gt3,gt2))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFdFdhhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  VZ, bar[Cha] 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ2  
mass(1) = MCha2(i2)  
coup(1) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFdChaSuL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(gt3,i2,gt1))  
coup(5) = cplSucSuVZ(gt1,iIN) 
coup(7) = Conjg(cplcFdFdVZL(gt3,gt2)) 
coup(6) = Conjg(cplcFdFdVZR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: VZ,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,bar[Cha]'
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = MAh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFdFdAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFdAhR(gt3,gt2,i1))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFdFdAhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFdFdAhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFdFdAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFdAhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFdFdhhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  Ah, bar[Cha] 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MAh(i1)  
mass(1) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFdChaSuL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(gt3,i2,gt1))  
coup(5) = cplAhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcFdFdAhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFdFdAhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: Ah,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = Mhh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplhhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFdFdhhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFdhhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFdFdhhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



!-------------- 
!  hh, bar[Cha] 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = Mhh(i1)  
mass(1) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFdChaSuL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(gt3,i2,gt1))  
coup(5) = cplhhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcFdFdhhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFdFdhhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: hh,bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,bar[Cha]'
        End Do 
      End Do 



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt2,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt2,iIN) 
coup(3) = cplcFdChaSuL(gt3,i1,gt1) 
coup(4) = cplcFdChaSuR(gt3,i1,gt1) 
coup(5) = cplcChaFdcSuL(i2,gt2,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt2,iIN)  
coup(7) = cplcFdChaSuL(gt3,i2,gt1) 
coup(8) = cplcFdChaSuR(gt3,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fd cFd Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:49))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSuFdcFd 
 
 
Subroutine SuToFdSvcFe(iIN,MFd,MSv,MFe,MCha,MSu,cplcChaFdcSuL,cplcChaFdcSuR,          & 
& cplcFeChaSvL,cplcFeChaSvR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFd(3),MSv(3),MFe(3),MCha(2),MSu(6)

Complex(dp),Intent(in) :: cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 4 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFd(gt1)/MSu(iIN))**2 
rm2 = (MFe(gt3)/MSu(iIN))**2 
rj2 = (MSv(gt2)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFe(gt3))+Abs(MSv(gt2))+Abs(MFd(gt1)))) Then 
!-------------- 
!  bar[Cha] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MCha(i1) 
mass(2) = MCha(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplcFeChaSvL(gt3,i1,gt2)) 
coup(3) = Conjg(cplcFeChaSvR(gt3,i1,gt2))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Sv cFe Propagator: bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha]'
      End Do 



!-------------- 
!  bar[Cha], bar[Cha] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MCha(i1)  
mass(2) = MCha(i2)  
coup(1) = cplcChaFdcSuL(i1,gt1,iIN) 
coup(2) = cplcChaFdcSuR(i1,gt1,iIN) 
coup(3) = cplcFeChaSvL(gt3,i1,gt2) 
coup(4) = cplcFeChaSvR(gt3,i1,gt2) 
coup(5) = cplcChaFdcSuL(i2,gt1,iIN) 
coup(6) = cplcChaFdcSuR(i2,gt1,iIN)  
coup(7) = cplcFeChaSvL(gt3,i2,gt2) 
coup(8) = cplcFeChaSvR(gt3,i2,gt2) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fd Sv cFe Propagator: bar[Cha],bar[Cha]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='bar[Cha],bar[Cha]'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:4))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFdSvcFe 
 
 
Subroutine SuTocHpmChaFu(iIN,MHpm,MCha,MFu,MSd,MChi,MSu,cplSdcHpmcSu,cplChaFucSdL,    & 
& cplChaFucSdR,cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,deltaM,           & 
& epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MHpm(2),MCha(2),MFu(3),MSd(6),MChi(4),MSu(6)

Complex(dp),Intent(in) :: cplSdcHpmcSu(6,2,6),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChiChacHpmL(4,2,2),    & 
& cplChiChacHpmR(4,2,2),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 100 
Allocate( gSum(2,2,3, Isum) ) 
Allocate( Contribution(2,2,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=2,2
      Do gt2=1,2
        Do gt3=1,3
Isum = 0 
 
rk2 = (MCha(gt2)/MSu(iIN))**2 
rm2 = (MFu(gt3)/MSu(iIN))**2 
rj2 = (MHpm(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFu(gt3))+Abs(MCha(gt2))+Abs(MHpm(gt1)))) Then 
!-------------- 
!  Sd 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSd(i1) 
mass(2) = MSd(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcHpmcSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplChaFucSdL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChaFucSdR(gt2,gt3,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Cha Fu Propagator: Sd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt3,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt3,iIN)) 
coup(4) = Conjg(cplChiChacHpmL(i1,gt2,gt1)) 
coup(3) = Conjg(cplChiChacHpmR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Cha Fu Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Sd, Sd 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSd(i1)  
mass(2) = MSd(i2)  
coup(1) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(3) = Conjg(cplChaFucSdL(gt2,gt3,i1)) 
coup(2) = Conjg(cplChaFucSdR(gt2,gt3,i1))  
coup(4) = cplSdcHpmcSu(i2,gt1,iIN) 
coup(6) = Conjg(cplChaFucSdL(gt2,gt3,i2)) 
coup(5) = Conjg(cplChaFucSdR(gt2,gt3,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Cha Fu Propagator: Sd,Sd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd,Sd'
        End Do 
      End Do 



!-------------- 
!  Sd, Chi 
!-------------- 
Do i1=1,6
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSd(i1)  
mass(1) = MChi(i2)  
coup(1) = cplChiFucSuL(i2,gt3,iIN) 
coup(2) = cplChiFucSuR(i2,gt3,iIN) 
coup(4) = Conjg(cplChiChacHpmL(i2,gt2,gt1)) 
coup(3) = Conjg(cplChiChacHpmR(i2,gt2,gt1))  
coup(5) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(7) = Conjg(cplChaFucSdL(gt2,gt3,i1)) 
coup(6) = Conjg(cplChaFucSdR(gt2,gt3,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Cha Fu Propagator: Sd,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Sd,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt3,iIN) 
coup(2) = cplChiFucSuR(i1,gt3,iIN) 
coup(3) = cplChiChacHpmL(i1,gt2,gt1) 
coup(4) = cplChiChacHpmR(i1,gt2,gt1) 
coup(5) = cplChiFucSuL(i2,gt3,iIN) 
coup(6) = cplChiFucSuR(i2,gt3,iIN)  
coup(7) = cplChiChacHpmL(i2,gt2,gt1) 
coup(8) = cplChiChacHpmR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Cha Fu Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=2,2
      Do gt2=1,2
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:100))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuTocHpmChaFu 
 
 
Subroutine SuToFuFecSe(iIN,MFu,MFe,MSe,MChi,MSu,cplChiFecSeL,cplChiFecSeR,            & 
& cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MFe(3),MSe(6),MChi(4),MSu(6)

Complex(dp),Intent(in) :: cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 16 
Allocate( gSum(3,3,6, Isum) ) 
Allocate( Contribution(3,3,6, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,6
Isum = 0 
 
rk2 = (MFu(gt1)/MSu(iIN))**2 
rm2 = (MFe(gt2)/MSu(iIN))**2 
rj2 = (MSe(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSe(gt3))+Abs(MFe(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplChiFecSeL(i1,gt2,gt3)) 
coup(3) = Conjg(cplChiFecSeR(i1,gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fe cSe Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplChiFecSeL(i1,gt2,gt3) 
coup(4) = cplChiFecSeR(i1,gt2,gt3) 
coup(5) = cplChiFucSuL(i2,gt1,iIN) 
coup(6) = cplChiFucSuR(i2,gt1,iIN)  
coup(7) = cplChiFecSeL(i2,gt2,gt3) 
coup(8) = cplChiFecSeR(i2,gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fe cSe Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,6
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:16))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFuFecSe 
 
 
Subroutine SuToFuFucSu(iIN,MFu,MSu,MChi,MGlu,cplChiFucSuL,cplChiFucSuR,               & 
& cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MSu(6),MChi(4),MGlu

Complex(dp),Intent(in) :: cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 25 
Allocate( gSum(3,3,6, Isum) ) 
Allocate( Contribution(3,3,6, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=gt1,3
        Do gt3=1,6
Isum = 0 
 
rk2 = (MFu(gt1)/MSu(iIN))**2 
rm2 = (MFu(gt2)/MSu(iIN))**2 
rj2 = (MSu(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSu(gt3))+Abs(MFu(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplChiFucSuL(i1,gt2,gt3)) 
coup(3) = Conjg(cplChiFucSuR(i1,gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplChiFucSuL(i1,gt1,gt3)) 
coup(3) = Conjg(cplChiFucSuR(i1,gt1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MChi(i1)  
mass(2) = MChi(i1)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFucSuL(i1,gt1,gt3) 
coup(4) = cplChiFucSuR(i1,gt1,gt3) 
coup(5) = cplChiFucSuL(i1,gt1,iIN) 
coup(6) = cplChiFucSuR(i1,gt1,iIN)  
coup(7) = cplChiFucSuL(i1,gt2,gt3) 
coup(8) = cplChiFucSuR(i1,gt2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fu cSu Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Glu 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MGlu 
mass(2) = MGlu 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(gt1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(gt1,iIN)) 
coup(4) = Conjg(cplGluFucSuL(gt2,gt3)) 
coup(3) = Conjg(cplGluFucSuR(gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp/3._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MGlu 
mass(2) = MGlu 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(gt2,iIN)) 
coup(1) = Conjg(cplGluFucSuR(gt2,iIN)) 
coup(4) = Conjg(cplGluFucSuL(gt1,gt3)) 
coup(3) = Conjg(cplGluFucSuR(gt1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp/3._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MGlu  
mass(2) = MGlu  
coup(1) = cplGluFucSuL(gt2,iIN) 
coup(2) = cplGluFucSuR(gt2,iIN) 
coup(3) = cplGluFucSuL(gt1,gt3) 
coup(4) = cplGluFucSuR(gt1,gt3) 
coup(5) = cplGluFucSuL(gt1,iIN) 
coup(6) = cplGluFucSuR(gt1,iIN)  
coup(7) = cplGluFucSuL(gt2,gt3) 
coup(8) = cplGluFucSuR(gt2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 2._dp/3._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fu cSu Propagator: Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Glu'



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplChiFucSuL(i1,gt2,gt3) 
coup(4) = cplChiFucSuR(i1,gt2,gt3) 
coup(5) = cplChiFucSuL(i2,gt1,iIN) 
coup(6) = cplChiFucSuR(i2,gt1,iIN)  
coup(7) = cplChiFucSuL(i2,gt2,gt3) 
coup(8) = cplChiFucSuR(i2,gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFucSuL(i1,gt1,gt3) 
coup(4) = cplChiFucSuR(i1,gt1,gt3) 
coup(5) = cplChiFucSuL(i2,gt1,iIN) 
coup(6) = cplChiFucSuR(i2,gt1,iIN)  
coup(7) = cplChiFucSuL(i2,gt2,gt3) 
coup(8) = cplChiFucSuR(i2,gt2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFucSuL(i1,gt1,gt3) 
coup(4) = cplChiFucSuR(i1,gt1,gt3) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplChiFucSuL(i2,gt1,gt3) 
coup(8) = cplChiFucSuR(i2,gt1,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplChiFucSuL(i1,gt2,gt3) 
coup(4) = cplChiFucSuR(i1,gt2,gt3) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplChiFucSuL(i2,gt1,gt3) 
coup(8) = cplChiFucSuR(i2,gt1,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fu cSu Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Glu 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplChiFucSuL(i1,gt2,gt3) 
coup(4) = cplChiFucSuR(i1,gt2,gt3) 
coup(5) = cplGluFucSuL(gt1,iIN) 
coup(6) = cplGluFucSuR(gt1,iIN)  
coup(7) = cplGluFucSuL(gt2,gt3) 
coup(8) = cplGluFucSuR(gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFucSuL(i1,gt1,gt3) 
coup(4) = cplChiFucSuR(i1,gt1,gt3) 
coup(5) = cplGluFucSuL(gt1,iIN) 
coup(6) = cplGluFucSuR(gt1,iIN)  
coup(7) = cplGluFucSuL(gt2,gt3) 
coup(8) = cplGluFucSuR(gt2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplChiFucSuL(i1,gt1,gt3) 
coup(4) = cplChiFucSuR(i1,gt1,gt3) 
coup(5) = cplGluFucSuL(gt2,iIN) 
coup(6) = cplGluFucSuR(gt2,iIN)  
coup(7) = cplGluFucSuL(gt1,gt3) 
coup(8) = cplGluFucSuR(gt1,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplChiFucSuL(i1,gt2,gt3) 
coup(4) = cplChiFucSuR(i1,gt2,gt3) 
coup(5) = cplGluFucSuL(gt2,iIN) 
coup(6) = cplGluFucSuR(gt2,iIN)  
coup(7) = cplGluFucSuL(gt1,gt3) 
coup(8) = cplGluFucSuR(gt1,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fu cSu Propagator: Chi,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Glu'
        End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=gt1,3
        Do gt3=1,6
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:25))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFuFucSu 
 
 
Subroutine SuToFuFvcSv(iIN,MFu,MSv,MChi,MSu,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,   & 
& cplChiFvcSvR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MSv(3),MChi(4),MSu(6)

Complex(dp),Intent(in) :: cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 16 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFu(gt1)/MSu(iIN))**2 
rm2 = (0./MSu(iIN))**2 
rj2 = (MSv(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSv(gt3))+Abs(0.)+Abs(MFu(gt1)))) Then 
!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplChiFvcSvL(i1,gt2,gt3)) 
coup(3) = Conjg(cplChiFvcSvR(i1,gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fv cSv Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplChiFvcSvL(i1,gt2,gt3) 
coup(4) = cplChiFvcSvR(i1,gt2,gt3) 
coup(5) = cplChiFucSuL(i2,gt1,iIN) 
coup(6) = cplChiFucSuR(i2,gt1,iIN)  
coup(7) = cplChiFvcSvL(i2,gt2,gt3) 
coup(8) = cplChiFvcSvR(i2,gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Fv cSv Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:16))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFuFvcSv 
 
 
Subroutine SuTocChaFuHpm(iIN,MCha,MFu,MHpm,MFd,MChi,MSu,cplcChaChiHpmL,               & 
& cplcChaChiHpmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdFuHpmL,cplcFdFuHpmR,cplChiFucSuL,     & 
& cplChiFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MCha(2),MFu(3),MHpm(2),MFd(3),MChi(4),MSu(6)

Complex(dp),Intent(in) :: cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),& 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 49 
Allocate( gSum(2,3,2, Isum) ) 
Allocate( Contribution(2,3,2, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,2
      Do gt2=1,3
        Do gt3=2,2
Isum = 0 
 
rk2 = (MCha(gt1)/MSu(iIN))**2 
rm2 = (MFu(gt2)/MSu(iIN))**2 
rj2 = (MHpm(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MHpm(gt3))+Abs(MFu(gt2))+Abs(MCha(gt1)))) Then 
!-------------- 
!  Fd 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFd(i1) 
mass(2) = MFd(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(gt1,i1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(gt1,i1,iIN)) 
coup(4) = Conjg(cplcFdFuHpmL(i1,gt2,gt3)) 
coup(3) = Conjg(cplcFdFuHpmR(i1,gt2,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cCha Fu Hpm Propagator: Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplcChaChiHpmL(gt1,i1,gt3)) 
coup(3) = Conjg(cplcChaChiHpmR(gt1,i1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cCha Fu Hpm Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Fd, Fd 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt1,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt1,i1,iIN) 
coup(3) = cplcFdFuHpmL(i1,gt2,gt3) 
coup(4) = cplcFdFuHpmR(i1,gt2,gt3) 
coup(5) = cplcChaFdcSuL(gt1,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt1,i2,iIN)  
coup(7) = cplcFdFuHpmL(i2,gt2,gt3) 
coup(8) = cplcFdFuHpmR(i2,gt2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cCha Fu Hpm Propagator: Fd,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd,Fd'
        End Do 
      End Do 



!-------------- 
!  Fd, Chi 
!-------------- 
Do i1=1,3
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MChi(i2)  
coup(1) = cplcChaFdcSuL(gt1,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt1,i1,iIN) 
coup(3) = cplcFdFuHpmL(i1,gt2,gt3) 
coup(4) = cplcFdFuHpmR(i1,gt2,gt3) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplcChaChiHpmL(gt1,i2,gt3) 
coup(8) = cplcChaChiHpmR(gt1,i2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cCha Fu Hpm Propagator: Fd,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplcChaChiHpmL(gt1,i1,gt3) 
coup(4) = cplcChaChiHpmR(gt1,i1,gt3) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplcChaChiHpmL(gt1,i2,gt3) 
coup(8) = cplcChaChiHpmR(gt1,i2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cCha Fu Hpm Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,2
      Do gt2=1,3
        Do gt3=2,2
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:49))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuTocChaFuHpm 
 
 
Subroutine SuToSdFucFd(iIN,MSd,MFu,MFd,MVWm,MHpm,MChi,MGlu,MSu,cplSdcHpmcSu,          & 
& cplSdcSucVWm,cplcFdChiSdL,cplcFdChiSdR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplChiFucSuL,cplChiFucSuR,cplGluFucSuL,         & 
& cplGluFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSd(6),MFu(3),MFd(3),MVWm,MHpm(2),MChi(4),MGlu,MSu(6)

Complex(dp),Intent(in) :: cplSdcHpmcSu(6,2,6),cplSdcSucVWm(6,6),cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),        & 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),           & 
& cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),           & 
& cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 64 
Allocate( gSum(6,3,3, Isum) ) 
Allocate( Contribution(6,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,6
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFu(gt2)/MSu(iIN))**2 
rm2 = (MFd(gt3)/MSu(iIN))**2 
rj2 = (MSd(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFd(gt3))+Abs(MFu(gt2))+Abs(MSd(gt1)))) Then 
!-------------- 
!  conj[VWm] 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVWm 
mass(2) = MVWm 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcSucVWm(gt1,iIN)) 
coup(3) = Conjg(cplcFdFuVWmL(gt3,gt2)) 
coup(2) = Conjg(cplcFdFuVWmR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[VWm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm]'



!-------------- 
!  conj[Hpm] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MHpm(i1) 
mass(2) = MHpm(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcHpmcSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplcFdFuHpmL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFuHpmR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm]'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplcFdChiSdL(gt3,i1,gt1)) 
coup(3) = Conjg(cplcFdChiSdR(gt3,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Glu 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MGlu 
mass(2) = MGlu 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(gt2,iIN)) 
coup(1) = Conjg(cplGluFucSuR(gt2,iIN)) 
coup(4) = Conjg(cplcFdGluSdL(gt3,gt1)) 
coup(3) = Conjg(cplcFdGluSdR(gt3,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Glu'



!-------------- 
!  conj[VWm], conj[Hpm] 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm  
mass(1) = MHpm(i2)  
coup(1) = cplSdcSucVWm(gt1,iIN) 
coup(2) = Conjg(cplcFdFuVWmL(gt3,gt2)) 
coup(3) = Conjg(cplcFdFuVWmR(gt3,gt2))  
coup(4) = cplSdcHpmcSu(gt1,i2,iIN) 
coup(5) = Conjg(cplcFdFuHpmL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFdFuHpmR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[VWm],conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],conj[Hpm]'
      End Do 



!-------------- 
!  conj[VWm], Chi 
!-------------- 
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm2  
mass(1) = MChi2(i2)  
coup(1) = cplChiFucSuL(i2,gt2,iIN) 
coup(2) = cplChiFucSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFdChiSdL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFdChiSdR(gt3,i2,gt1))  
coup(5) = cplSdcSucVWm(gt1,iIN) 
coup(7) = Conjg(cplcFdFuVWmL(gt3,gt2)) 
coup(6) = Conjg(cplcFdFuVWmR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[VWm],Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],Chi'
      End Do 



!-------------- 
!  conj[VWm], Glu 
!-------------- 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm2  
mass(1) = MGlu2  
coup(1) = cplGluFucSuL(gt2,iIN) 
coup(2) = cplGluFucSuR(gt2,iIN) 
coup(4) = Conjg(cplcFdGluSdL(gt3,gt1)) 
coup(3) = Conjg(cplcFdGluSdR(gt3,gt1))  
coup(5) = cplSdcSucVWm(gt1,iIN) 
coup(7) = Conjg(cplcFdFuVWmL(gt3,gt2)) 
coup(6) = Conjg(cplcFdFuVWmR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 4._dp/3._dp*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[VWm],Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],Glu'



!-------------- 
!  conj[Hpm], conj[Hpm] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MHpm(i1)  
mass(2) = MHpm(i2)  
coup(1) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(3) = Conjg(cplcFdFuHpmL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFdFuHpmR(gt3,gt2,i1))  
coup(4) = cplSdcHpmcSu(gt1,i2,iIN) 
coup(6) = Conjg(cplcFdFuHpmL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFdFuHpmR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[Hpm],conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],conj[Hpm]'
        End Do 
      End Do 



!-------------- 
!  conj[Hpm], Chi 
!-------------- 
Do i1=1,2
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MHpm(i1)  
mass(1) = MChi(i2)  
coup(1) = cplChiFucSuL(i2,gt2,iIN) 
coup(2) = cplChiFucSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFdChiSdL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFdChiSdR(gt3,i2,gt1))  
coup(5) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcFdFuHpmL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFdFuHpmR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[Hpm],Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],Chi'
        End Do 
      End Do 



!-------------- 
!  conj[Hpm], Glu 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MHpm(i1)  
mass(1) = MGlu  
coup(1) = cplGluFucSuL(gt2,iIN) 
coup(2) = cplGluFucSuR(gt2,iIN) 
coup(4) = Conjg(cplcFdGluSdL(gt3,gt1)) 
coup(3) = Conjg(cplcFdGluSdR(gt3,gt1))  
coup(5) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(7) = Conjg(cplcFdFuHpmL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFdFuHpmR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: conj[Hpm],Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],Glu'
        End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplcFdChiSdL(gt3,i1,gt1) 
coup(4) = cplcFdChiSdR(gt3,i1,gt1) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplcFdChiSdL(gt3,i2,gt1) 
coup(8) = cplcFdChiSdR(gt3,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Glu 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplcFdChiSdL(gt3,i1,gt1) 
coup(4) = cplcFdChiSdR(gt3,i1,gt1) 
coup(5) = cplGluFucSuL(gt2,iIN) 
coup(6) = cplGluFucSuR(gt2,iIN)  
coup(7) = cplcFdGluSdL(gt3,gt1) 
coup(8) = cplcFdGluSdR(gt3,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fu cFd Propagator: Chi,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Glu'
        End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,6
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:64))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSdFucFd 
 
 
Subroutine SuToFuSecFe(iIN,MFu,MSe,MFe,MChi,MSu,cplcFeChiSeL,cplcFeChiSeR,            & 
& cplChiFucSuL,cplChiFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MSe(6),MFe(3),MChi(4),MSu(6)

Complex(dp),Intent(in) :: cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 16 
Allocate( gSum(3,6,3, Isum) ) 
Allocate( Contribution(3,6,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,6
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFu(gt1)/MSu(iIN))**2 
rm2 = (MFe(gt3)/MSu(iIN))**2 
rj2 = (MSe(gt2)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFe(gt3))+Abs(MSe(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplcFeChiSeL(gt3,i1,gt2)) 
coup(3) = Conjg(cplcFeChiSeR(gt3,i1,gt2))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Se cFe Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplcFeChiSeL(gt3,i1,gt2) 
coup(4) = cplcFeChiSeR(gt3,i1,gt2) 
coup(5) = cplChiFucSuL(i2,gt1,iIN) 
coup(6) = cplChiFucSuR(i2,gt1,iIN)  
coup(7) = cplcFeChiSeL(gt3,i2,gt2) 
coup(8) = cplcFeChiSeR(gt3,i2,gt2) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Se cFe Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,6
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:16))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFuSecFe 
 
 
Subroutine SuToSuFucFu(iIN,MSu,MFu,MVZ,MAh,Mhh,MChi,MGlu,cplAhSucSu,cplhhSucSu,       & 
& cplSucSuVZ,cplcFuChiSuL,cplcFuChiSuR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChiFucSuL,            & 
& cplChiFucSuR,cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSu(6),MFu(3),MVZ,MAh(2),Mhh(2),MChi(4),MGlu

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplhhSucSu(2,6,6),cplSucSuVZ(6,6),cplcFuChiSuL(3,4,6),              & 
& cplcFuChiSuR(3,4,6),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),          & 
& cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),& 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 100 
Allocate( gSum(6,3,3, Isum) ) 
Allocate( Contribution(6,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFu(gt2)/MSu(iIN))**2 
rm2 = (MFu(gt3)/MSu(iIN))**2 
rj2 = (MSu(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFu(gt3))+Abs(MFu(gt2))+Abs(MSu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplcFuFuVZL(gt3,gt2)) 
coup(2) = Conjg(cplcFuFuVZR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MAh(i1) 
mass(2) = MAh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcFuFuAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFuFuAhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = Mhh(i1) 
mass(2) = Mhh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcFuFuhhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFuFuhhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt2,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt2,iIN)) 
coup(4) = Conjg(cplcFuChiSuL(gt3,i1,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(gt3,i1,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 3*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Glu 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MGlu 
mass(2) = MGlu 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(gt2,iIN)) 
coup(1) = Conjg(cplGluFucSuR(gt2,iIN)) 
coup(4) = Conjg(cplcFuGluSuL(gt3,gt1)) 
coup(3) = Conjg(cplcFuGluSuR(gt3,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Glu'



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = MAh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcFuFuVZL(gt3,gt2)) 
coup(3) = Conjg(cplcFuFuVZR(gt3,gt2))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcFuFuAhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFuFuAhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = Mhh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcFuFuVZL(gt3,gt2)) 
coup(3) = Conjg(cplcFuFuVZR(gt3,gt2))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFuFuhhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  VZ, Chi 
!-------------- 
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ2  
mass(1) = MChi2(i2)  
coup(1) = cplChiFucSuL(i2,gt2,iIN) 
coup(2) = cplChiFucSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(gt3,i2,gt1))  
coup(5) = cplSucSuVZ(gt1,iIN) 
coup(7) = Conjg(cplcFuFuVZL(gt3,gt2)) 
coup(6) = Conjg(cplcFuFuVZR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: VZ,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Chi'
      End Do 



!-------------- 
!  VZ, Glu 
!-------------- 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ2  
mass(1) = MGlu2  
coup(1) = cplGluFucSuL(gt2,iIN) 
coup(2) = cplGluFucSuR(gt2,iIN) 
coup(4) = Conjg(cplcFuGluSuL(gt3,gt1)) 
coup(3) = Conjg(cplcFuGluSuR(gt3,gt1))  
coup(5) = cplSucSuVZ(gt1,iIN) 
coup(7) = Conjg(cplcFuFuVZL(gt3,gt2)) 
coup(6) = Conjg(cplcFuFuVZR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 4._dp/3._dp*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: VZ,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Glu'



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = MAh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFuFuAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFuFuAhR(gt3,gt2,i1))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFuFuAhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFuFuAhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFuFuAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFuFuAhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFuFuhhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  Ah, Chi 
!-------------- 
Do i1=1,2
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MAh(i1)  
mass(1) = MChi(i2)  
coup(1) = cplChiFucSuL(i2,gt2,iIN) 
coup(2) = cplChiFucSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(gt3,i2,gt1))  
coup(5) = cplAhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcFuFuAhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFuFuAhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Ah,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Chi'
        End Do 
      End Do 



!-------------- 
!  Ah, Glu 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MAh(i1)  
mass(1) = MGlu  
coup(1) = cplGluFucSuL(gt2,iIN) 
coup(2) = cplGluFucSuR(gt2,iIN) 
coup(4) = Conjg(cplcFuGluSuL(gt3,gt1)) 
coup(3) = Conjg(cplcFuGluSuR(gt3,gt1))  
coup(5) = cplAhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcFuFuAhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFuFuAhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Ah,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Glu'
        End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = Mhh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplhhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFuFuhhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFuFuhhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFuFuhhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



!-------------- 
!  hh, Chi 
!-------------- 
Do i1=1,2
  Do i2=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = Mhh(i1)  
mass(1) = MChi(i2)  
coup(1) = cplChiFucSuL(i2,gt2,iIN) 
coup(2) = cplChiFucSuR(i2,gt2,iIN) 
coup(4) = Conjg(cplcFuChiSuL(gt3,i2,gt1)) 
coup(3) = Conjg(cplcFuChiSuR(gt3,i2,gt1))  
coup(5) = cplhhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcFuFuhhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFuFuhhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: hh,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,Chi'
        End Do 
      End Do 



!-------------- 
!  hh, Glu 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = Mhh(i1)  
mass(1) = MGlu  
coup(1) = cplGluFucSuL(gt2,iIN) 
coup(2) = cplGluFucSuR(gt2,iIN) 
coup(4) = Conjg(cplcFuGluSuL(gt3,gt1)) 
coup(3) = Conjg(cplcFuGluSuR(gt3,gt1))  
coup(5) = cplhhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcFuFuhhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcFuFuhhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: hh,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,Glu'
        End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplcFuChiSuL(gt3,i1,gt1) 
coup(4) = cplcFuChiSuR(gt3,i1,gt1) 
coup(5) = cplChiFucSuL(i2,gt2,iIN) 
coup(6) = cplChiFucSuR(i2,gt2,iIN)  
coup(7) = cplcFuChiSuL(gt3,i2,gt1) 
coup(8) = cplcFuChiSuR(gt3,i2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 3*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



!-------------- 
!  Chi, Glu 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MGlu  
coup(1) = cplChiFucSuL(i1,gt2,iIN) 
coup(2) = cplChiFucSuR(i1,gt2,iIN) 
coup(3) = cplcFuChiSuL(gt3,i1,gt1) 
coup(4) = cplcFuChiSuR(gt3,i1,gt1) 
coup(5) = cplGluFucSuL(gt2,iIN) 
coup(6) = cplGluFucSuR(gt2,iIN)  
coup(7) = cplcFuGluSuL(gt3,gt1) 
coup(8) = cplcFuGluSuR(gt3,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 0*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fu cFu Propagator: Chi,Glu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Glu'
        End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:100))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSuFucFu 
 
 
Subroutine SuToFuSvcFv(iIN,MFu,MSv,MChi,MSu,cplcFvChiSvL,cplcFvChiSvR,cplChiFucSuL,   & 
& cplChiFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MSv(3),MChi(4),MSu(6)

Complex(dp),Intent(in) :: cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 16 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFu(gt1)/MSu(iIN))**2 
rm2 = (0./MSu(iIN))**2 
rj2 = (MSv(gt2)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(0.)+Abs(MSv(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  Chi 
!-------------- 
Do i1=1,4
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MChi(i1) 
mass(2) = MChi(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplChiFucSuL(i1,gt1,iIN)) 
coup(1) = Conjg(cplChiFucSuR(i1,gt1,iIN)) 
coup(4) = Conjg(cplcFvChiSvL(gt3,i1,gt2)) 
coup(3) = Conjg(cplcFvChiSvR(gt3,i1,gt2))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Sv cFv Propagator: Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi'
      End Do 



!-------------- 
!  Chi, Chi 
!-------------- 
Do i1=1,3
  Do i2=i1+1,4
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MChi(i1)  
mass(2) = MChi(i2)  
coup(1) = cplChiFucSuL(i1,gt1,iIN) 
coup(2) = cplChiFucSuR(i1,gt1,iIN) 
coup(3) = cplcFvChiSvL(gt3,i1,gt2) 
coup(4) = cplcFvChiSvR(gt3,i1,gt2) 
coup(5) = cplChiFucSuL(i2,gt1,iIN) 
coup(6) = cplChiFucSuR(i2,gt1,iIN)  
coup(7) = cplcFvChiSvL(gt3,i2,gt2) 
coup(8) = cplcFvChiSvR(gt3,i2,gt2) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Fu Sv cFv Propagator: Chi,Chi" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Chi,Chi'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:16))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToFuSvcFv 
 
 
Subroutine SuTocHpmFdGlu(iIN,MHpm,MFd,MGlu,MSd,MFu,MSu,cplSdcHpmcSu,cplcFuFdcHpmL,    & 
& cplcFuFdcHpmR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,deltaM,              & 
& epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MHpm(2),MFd(3),MGlu,MSd(6),MFu(3),MSu(6)

Complex(dp),Intent(in) :: cplSdcHpmcSu(6,2,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplGluFdcSdL(3,6),      & 
& cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 81 
Allocate( gSum(2,3,1, Isum) ) 
Allocate( Contribution(2,3,1, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=2,2
      Do gt2=1,3
Isum = 0 
 
rk2 = (MFd(gt2)/MSu(iIN))**2 
rm2 = (MGlu/MSu(iIN))**2 
rj2 = (MHpm(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MGlu)+Abs(MFd(gt2))+Abs(MHpm(gt1)))) Then 
!-------------- 
!  Sd 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSd(i1) 
mass(2) = MSd(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcHpmcSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplGluFdcSdL(gt2,i1)) 
coup(2) = Conjg(cplGluFdcSdR(gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Fd Glu Propagator: Sd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp
Else 
gSum(gt1,gt2,1,Isum)=resD
End If 
Contribution(gt1,gt2,1,Isum)='Sd'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcFuFdcHpmL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFuFdcHpmR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Fd Glu Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp
Else 
gSum(gt1,gt2,1,Isum)=resD
End If 
Contribution(gt1,gt2,1,Isum)='Fu'
      End Do 



!-------------- 
!  Sd, Sd 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSd(i1)  
mass(2) = MSd(i2)  
coup(1) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(3) = Conjg(cplGluFdcSdL(gt2,i1)) 
coup(2) = Conjg(cplGluFdcSdR(gt2,i1))  
coup(4) = cplSdcHpmcSu(i2,gt1,iIN) 
coup(6) = Conjg(cplGluFdcSdL(gt2,i2)) 
coup(5) = Conjg(cplGluFdcSdR(gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Fd Glu Propagator: Sd,Sd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Sd,Sd'
        End Do 
      End Do 



!-------------- 
!  Sd, Fu 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSd(i1)  
mass(1) = MFu(i2)  
coup(1) = cplGluFucSuL(i2,iIN) 
coup(2) = cplGluFucSuR(i2,iIN) 
coup(4) = Conjg(cplcFuFdcHpmL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFuFdcHpmR(i2,gt2,gt1))  
coup(5) = cplSdcHpmcSu(i1,gt1,iIN) 
coup(7) = Conjg(cplGluFdcSdL(gt2,i1)) 
coup(6) = Conjg(cplGluFdcSdR(gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Fd Glu Propagator: Sd,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Sd,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuFdcHpmL(i1,gt2,gt1) 
coup(4) = cplcFuFdcHpmR(i1,gt2,gt1) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuFdcHpmL(i2,gt2,gt1) 
coup(8) = cplcFuFdcHpmR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->cHpm Fd Glu Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Fu,Fu'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,1,:)= 0._dp  
End If 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=2,2
      Do gt2=1,3
g(gt1,gt2,1)=Sum(gSum(gt1,gt2,1,1:81))
If (g(gt1,gt2,1).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,1)=0._dp
End If
     End Do 
   End Do 
End Subroutine SuTocHpmFdGlu 
 
 
Subroutine SuTohhFuGlu(iIN,Mhh,MFu,MGlu,MSu,cplhhSucSu,cplcFuFuhhL,cplcFuFuhhR,       & 
& cplGluFucSuL,cplGluFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: Mhh(2),MFu(3),MGlu,MSu(6)

Complex(dp),Intent(in) :: cplhhSucSu(2,6,6),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplGluFucSuL(3,6),            & 
& cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 81 
Allocate( gSum(2,3,1, Isum) ) 
Allocate( Contribution(2,3,1, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,2
      Do gt2=1,3
Isum = 0 
 
rk2 = (MFu(gt2)/MSu(iIN))**2 
rm2 = (MGlu/MSu(iIN))**2 
rj2 = (Mhh(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MGlu)+Abs(MFu(gt2))+Abs(Mhh(gt1)))) Then 
!-------------- 
!  Su 
!-------------- 
Do i1=1,6
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MSu(i1) 
mass(2) = MSu(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplGluFucSuL(gt2,i1)) 
coup(2) = Conjg(cplGluFucSuR(gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fu Glu Propagator: Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp
Else 
gSum(gt1,gt2,1,Isum)=resD
End If 
Contribution(gt1,gt2,1,Isum)='Su'
      End Do 



!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcFuFuhhL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFuFuhhR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fu Glu Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp
Else 
gSum(gt1,gt2,1,Isum)=resD
End If 
Contribution(gt1,gt2,1,Isum)='Fu'
      End Do 



!-------------- 
!  Su, Su 
!-------------- 
Do i1=1,5
  Do i2=i1+1,6
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MSu(i1)  
mass(2) = MSu(i2)  
coup(1) = cplhhSucSu(gt1,i1,iIN) 
coup(3) = Conjg(cplGluFucSuL(gt2,i1)) 
coup(2) = Conjg(cplGluFucSuR(gt2,i1))  
coup(4) = cplhhSucSu(gt1,i2,iIN) 
coup(6) = Conjg(cplGluFucSuL(gt2,i2)) 
coup(5) = Conjg(cplGluFucSuR(gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fu Glu Propagator: Su,Su" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Su,Su'
        End Do 
      End Do 



!-------------- 
!  Su, Fu 
!-------------- 
Do i1=1,6
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MSu(i1)  
mass(1) = MFu(i2)  
coup(1) = cplGluFucSuL(i2,iIN) 
coup(2) = cplGluFucSuR(i2,iIN) 
coup(4) = Conjg(cplcFuFuhhL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFuFuhhR(i2,gt2,gt1))  
coup(5) = cplhhSucSu(gt1,i1,iIN) 
coup(7) = Conjg(cplGluFucSuL(gt2,i1)) 
coup(6) = Conjg(cplGluFucSuR(gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fu Glu Propagator: Su,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Su,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuFuhhL(i1,gt2,gt1) 
coup(4) = cplcFuFuhhR(i1,gt2,gt1) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuFuhhL(i2,gt2,gt1) 
coup(8) = cplcFuFuhhR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->hh Fu Glu Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,1,Isum)= 0._dp  
Else 
gSum(gt1,gt2,1,Isum)= resS  
End If 
Contribution(gt1,gt2,1,Isum)='Fu,Fu'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,1,:)= 0._dp  
End If 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,2
      Do gt2=1,3
g(gt1,gt2,1)=Sum(gSum(gt1,gt2,1,1:81))
If (g(gt1,gt2,1).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,1)=0._dp
End If
     End Do 
   End Do 
End Subroutine SuTohhFuGlu 
 
 
Subroutine SuToGluGluSu(iIN,MGlu,MSu,MFu,cplcFuGluSuL,cplcFuGluSuR,cplGluFucSuL,      & 
& cplGluFucSuR,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MGlu,MSu(6),MFu(3)

Complex(dp),Intent(in) :: cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 9 
Allocate( gSum(1,1,6, Isum) ) 
Allocate( Contribution(1,1,6, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
        Do gt3=1, iIN-1
Isum = 0 
 
rk2 = (MGlu/MSu(iIN))**2 
rm2 = (MGlu/MSu(iIN))**2 
rj2 = (MSu(gt3)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MSu(gt3))+Abs(MGlu)+Abs(MGlu))) Then 
!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcFuGluSuL(i1,gt3)) 
coup(3) = Conjg(cplcFuGluSuR(i1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcFuGluSuL(i1,gt3)) 
coup(3) = Conjg(cplcFuGluSuR(i1,gt3))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
 
 mass(1) = MFu(i1)  
mass(2) = MFu(i1)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplGluFucSuL(i1,iIN) 
coup(6) = cplGluFucSuR(i1,iIN)  
coup(7) = cplcFuGluSuL(i1,gt3) 
coup(8) = cplcFuGluSuR(i1,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Glu Su Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,1,gt3,Isum)= 0._dp
Else 
gSum(1,1,gt3,Isum)=resD
End If 
Contribution(1,1,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuGluSuL(i2,gt3) 
coup(8) = cplcFuGluSuR(i2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuGluSuL(i2,gt3) 
coup(8) = cplcFuGluSuR(i2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuGluSuL(i2,gt3) 
coup(8) = cplcFuGluSuR(i2,gt3) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcFuGluSuL(i1,gt3) 
coup(4) = cplcFuGluSuR(i1,gt3) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcFuGluSuL(i2,gt3) 
coup(8) = cplcFuGluSuR(i2,gt3) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 16._dp/9._dp*resC  ! Color factor 
If (gt1.Eq.gt2) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Glu Su Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,1,gt3,Isum)= 0._dp  
Else 
gSum(1,1,gt3,Isum)= resS  
End If 
Contribution(1,1,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



Else 
gSum(1,1,gt3,:)= 0._dp  
End If 
       End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
        Do gt3=1, iIN-1
g(1,1,gt3)=Sum(gSum(1,1,gt3,1:9))
If (g(1,1,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(1,1,gt3)=0._dp
End If
       End Do 
End Subroutine SuToGluGluSu 
 
 
Subroutine SuToGluSdcCha(iIN,MGlu,MSd,MCha,MFu,MFd,MSu,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdGluSdL,cplcFdGluSdR,cplGluFucSuL,cplGluFucSuR,       & 
& deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MGlu,MSd(6),MCha(2),MFu(3),MFd(3),MSu(6)

Complex(dp),Intent(in) :: cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),  & 
& cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 36 
Allocate( gSum(1,6,2, Isum) ) 
Allocate( Contribution(1,6,2, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
      Do gt2=1,6
        Do gt3=1,2
Isum = 0 
 
rk2 = (MGlu/MSu(iIN))**2 
rm2 = (MCha(gt3)/MSu(iIN))**2 
rj2 = (MSd(gt2)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MCha(gt3))+Abs(MSd(gt2))+Abs(MGlu))) Then 
!-------------- 
!  Fu 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFu(i1) 
mass(2) = MFu(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplGluFucSuL(i1,iIN)) 
coup(1) = Conjg(cplGluFucSuR(i1,iIN)) 
coup(4) = Conjg(cplcChacFuSdL(gt3,i1,gt2)) 
coup(3) = Conjg(cplcChacFuSdR(gt3,i1,gt2))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Sd cCha Propagator: Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,gt2,gt3,Isum)= 0._dp
Else 
gSum(1,gt2,gt3,Isum)=resD
End If 
Contribution(1,gt2,gt3,Isum)='Fu'
      End Do 



!-------------- 
!  Fd 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFd(i1) 
mass(2) = MFd(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(gt3,i1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(gt3,i1,iIN)) 
coup(4) = Conjg(cplcFdGluSdL(i1,gt2)) 
coup(3) = Conjg(cplcFdGluSdR(i1,gt2))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Sd cCha Propagator: Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,gt2,gt3,Isum)= 0._dp
Else 
gSum(1,gt2,gt3,Isum)=resD
End If 
Contribution(1,gt2,gt3,Isum)='Fd'
      End Do 



!-------------- 
!  Fu, Fu 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFu(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcChacFuSdL(gt3,i1,gt2) 
coup(4) = cplcChacFuSdR(gt3,i1,gt2) 
coup(5) = cplGluFucSuL(i2,iIN) 
coup(6) = cplGluFucSuR(i2,iIN)  
coup(7) = cplcChacFuSdL(gt3,i2,gt2) 
coup(8) = cplcChacFuSdR(gt3,i2,gt2) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Sd cCha Propagator: Fu,Fu" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(1,gt2,gt3,Isum)= resS  
End If 
Contribution(1,gt2,gt3,Isum)='Fu,Fu'
        End Do 
      End Do 



!-------------- 
!  Fu, Fd 
!-------------- 
Do i1=1,3
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFu(i1)  
mass(2) = MFd(i2)  
coup(1) = cplGluFucSuL(i1,iIN) 
coup(2) = cplGluFucSuR(i1,iIN) 
coup(3) = cplcChacFuSdL(gt3,i1,gt2) 
coup(4) = cplcChacFuSdR(gt3,i1,gt2) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdGluSdL(i2,gt2) 
coup(8) = cplcFdGluSdR(i2,gt2) 
Call IntegrateChiChiInterference(mass,m_in,r_outcrossed,coup,smin2,smax2,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Sd cCha Propagator: Fu,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(1,gt2,gt3,Isum)= resS  
End If 
Contribution(1,gt2,gt3,Isum)='Fu,Fd'
        End Do 
      End Do 



!-------------- 
!  Fd, Fd 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i1,iIN) 
coup(3) = cplcFdGluSdL(i1,gt2) 
coup(4) = cplcFdGluSdR(i1,gt2) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdGluSdL(i2,gt2) 
coup(8) = cplcFdGluSdR(i2,gt2) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 4._dp/3._dp*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Glu Sd cCha Propagator: Fd,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(1,gt2,gt3,Isum)= resS  
End If 
Contribution(1,gt2,gt3,Isum)='Fd,Fd'
        End Do 
      End Do 



Else 
gSum(1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
      Do gt2=1,6
        Do gt3=1,2
g(1,gt2,gt3)=Sum(gSum(1,gt2,gt3,1:36))
If (g(1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
End Subroutine SuToGluSdcCha 
 
 
Subroutine SuToSdFvcFe(iIN,MSd,MFe,MVWm,MHpm,MSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,deltaM,epsI,check,g,               & 
& WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSd(6),MFe(3),MVWm,MHpm(2),MSu(6)

Complex(dp),Intent(in) :: cplSdcHpmcSu(6,2,6),cplSdcSucVWm(6,6),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),        & 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 9 
Allocate( gSum(6,3,3, Isum) ) 
Allocate( Contribution(6,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,6
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (0./MSu(iIN))**2 
rm2 = (MFe(gt3)/MSu(iIN))**2 
rj2 = (MSd(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFe(gt3))+Abs(0.)+Abs(MSd(gt1)))) Then 
!-------------- 
!  conj[VWm] 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVWm 
mass(2) = MVWm 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcSucVWm(gt1,iIN)) 
coup(3) = Conjg(cplcFeFvVWmL(gt3,gt2)) 
coup(2) = Conjg(cplcFeFvVWmR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fv cFe Propagator: conj[VWm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm]'



!-------------- 
!  conj[Hpm] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MHpm(i1) 
mass(2) = MHpm(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSdcHpmcSu(gt1,i1,iIN)) 
coup(3) = Conjg(cplcFeFvHpmL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFvHpmR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fv cFe Propagator: conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm]'
      End Do 



!-------------- 
!  conj[VWm], conj[Hpm] 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVWm  
mass(1) = MHpm(i2)  
coup(1) = cplSdcSucVWm(gt1,iIN) 
coup(2) = Conjg(cplcFeFvVWmL(gt3,gt2)) 
coup(3) = Conjg(cplcFeFvVWmR(gt3,gt2))  
coup(4) = cplSdcHpmcSu(gt1,i2,iIN) 
coup(5) = Conjg(cplcFeFvHpmL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFeFvHpmR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fv cFe Propagator: conj[VWm],conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],conj[Hpm]'
      End Do 



!-------------- 
!  conj[Hpm], conj[Hpm] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MHpm(i1)  
mass(2) = MHpm(i2)  
coup(1) = cplSdcHpmcSu(gt1,i1,iIN) 
coup(3) = Conjg(cplcFeFvHpmL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFvHpmR(gt3,gt2,i1))  
coup(4) = cplSdcHpmcSu(gt1,i2,iIN) 
coup(6) = Conjg(cplcFeFvHpmL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFeFvHpmR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Sd Fv cFe Propagator: conj[Hpm],conj[Hpm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hpm],conj[Hpm]'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,6
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:9))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSdFvcFe 
 
 
Subroutine SuToSuChacCha(iIN,MSu,MCha,MVZ,MAh,Mhh,MFd,cplAhSucSu,cplhhSucSu,          & 
& cplSucSuVZ,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,deltaM,            & 
& epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSu(6),MCha(2),MVZ,MAh(2),Mhh(2),MFd(3)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplhhSucSu(2,6,6),cplSucSuVZ(6,6),cplcChaChaAhL(2,2,2),             & 
& cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),cplcChaChaVZL(2,2),     & 
& cplcChaChaVZR(2,2),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFdChaSuL(3,2,6),      & 
& cplcFdChaSuR(3,2,6)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 64 
Allocate( gSum(6,2,2, Isum) ) 
Allocate( Contribution(6,2,2, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,2
        Do gt3=1,2
Isum = 0 
 
rk2 = (MCha(gt2)/MSu(iIN))**2 
rm2 = (MCha(gt3)/MSu(iIN))**2 
rj2 = (MSu(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MCha(gt3))+Abs(MCha(gt2))+Abs(MSu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplcChaChaVZL(gt3,gt2)) 
coup(2) = Conjg(cplcChaChaVZR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MAh(i1) 
mass(2) = MAh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcChaChaAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChaAhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = Mhh(i1) 
mass(2) = Mhh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcChaChahhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChahhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  Fd 
!-------------- 
Do i1=1,3
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MFd(i1) 
mass(2) = MFd(i1) 
m_in = MSu(iIN) 
coup(2) = Conjg(cplcChaFdcSuL(gt3,i1,iIN)) 
coup(1) = Conjg(cplcChaFdcSuR(gt3,i1,iIN)) 
coup(4) = Conjg(cplcFdChaSuL(i1,gt2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(i1,gt2,gt1))
coup(5:8) = coup(1:4) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = MAh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcChaChaVZL(gt3,gt2)) 
coup(3) = Conjg(cplcChaChaVZR(gt3,gt2))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcChaChaAhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcChaChaAhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = Mhh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcChaChaVZL(gt3,gt2)) 
coup(3) = Conjg(cplcChaChaVZR(gt3,gt2))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcChaChahhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcChaChahhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  VZ, Fd 
!-------------- 
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ2  
mass(1) = MFd2(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdChaSuL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(i2,gt2,gt1))  
coup(5) = cplSucSuVZ(gt1,iIN) 
coup(7) = Conjg(cplcChaChaVZL(gt3,gt2)) 
coup(6) = Conjg(cplcChaChaVZR(gt3,gt2))  
Call IntegrateVF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
resC = 1*resC  ! Color factor 
If (resC.ne.resC) resC = 0._dp
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: VZ,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Fd'
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = MAh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcChaChaAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChaAhR(gt3,gt2,i1))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcChaChaAhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcChaChaAhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcChaChaAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChaAhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcChaChahhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcChaChahhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  Ah, Fd 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MAh(i1)  
mass(1) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdChaSuL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(i2,gt2,gt1))  
coup(5) = cplAhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcChaChaAhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaChaAhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: Ah,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Fd'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = Mhh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplhhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcChaChahhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcChaChahhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcChaChahhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcChaChahhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



!-------------- 
!  hh, Fd 
!-------------- 
Do i1=1,2
  Do i2=1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = Mhh(i1)  
mass(1) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i2,iIN) 
coup(4) = Conjg(cplcFdChaSuL(i2,gt2,gt1)) 
coup(3) = Conjg(cplcFdChaSuR(i2,gt2,gt1))  
coup(5) = cplhhSucSu(i1,gt1,iIN) 
coup(7) = Conjg(cplcChaChahhL(gt3,gt2,i1)) 
coup(6) = Conjg(cplcChaChahhR(gt3,gt2,i1))  
Call IntegrateSF(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: hh,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,Fd'
        End Do 
      End Do 



!-------------- 
!  Fd, Fd 
!-------------- 
Do i1=1,2
  Do i2=i1+1,3
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MFd(i1)  
mass(2) = MFd(i2)  
coup(1) = cplcChaFdcSuL(gt3,i1,iIN) 
coup(2) = cplcChaFdcSuR(gt3,i1,iIN) 
coup(3) = cplcFdChaSuL(i1,gt2,gt1) 
coup(4) = cplcFdChaSuR(i1,gt2,gt1) 
coup(5) = cplcChaFdcSuL(gt3,i2,iIN) 
coup(6) = cplcChaFdcSuR(gt3,i2,iIN)  
coup(7) = cplcFdChaSuL(i2,gt2,gt1) 
coup(8) = cplcFdChaSuR(i2,gt2,gt1) 
Call IntegrateFFLM(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Cha cCha Propagator: Fd,Fd" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Fd,Fd'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,2
        Do gt3=1,2
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:64))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSuChacCha 
 
 
Subroutine SuToSuFecFe(iIN,MSu,MFe,MVZ,MAh,Mhh,cplAhSucSu,cplhhSucSu,cplSucSuVZ,      & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSu(6),MFe(3),MVZ,MAh(2),Mhh(2)

Complex(dp),Intent(in) :: cplAhSucSu(2,6,6),cplhhSucSu(2,6,6),cplSucSuVZ(6,6),cplcFeFeAhL(3,3,2),               & 
& cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),             & 
& cplcFeFeVZR(3,3)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 25 
Allocate( gSum(6,3,3, Isum) ) 
Allocate( Contribution(6,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (MFe(gt2)/MSu(iIN))**2 
rm2 = (MFe(gt3)/MSu(iIN))**2 
rj2 = (MSu(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(MFe(gt3))+Abs(MFe(gt2))+Abs(MSu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplcFeFeVZL(gt3,gt2)) 
coup(2) = Conjg(cplcFeFeVZR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MAh(i1) 
mass(2) = MAh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplAhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcFeFeAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFeAhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = Mhh(i1) 
mass(2) = Mhh(i1) 
m_in = MSu(iIN) 
coup(1) = Conjg(cplhhSucSu(i1,gt1,iIN)) 
coup(3) = Conjg(cplcFeFehhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFehhR(gt3,gt2,i1))
coup(4:6) = coup(1:3) 
Call IntegrateSaSa(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = MAh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcFeFeVZL(gt3,gt2)) 
coup(3) = Conjg(cplcFeFeVZR(gt3,gt2))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcFeFeAhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFeFeAhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MVZ  
mass(1) = Mhh(i2)  
coup(1) = cplSucSuVZ(gt1,iIN) 
coup(2) = Conjg(cplcFeFeVZL(gt3,gt2)) 
coup(3) = Conjg(cplcFeFeVZR(gt3,gt2))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(5) = Conjg(cplcFeFehhL(gt3,gt2,i2)) 
coup(6) = Conjg(cplcFeFehhR(gt3,gt2,i2))  
If(Abs(mass(1)-mass(2)).lt.0.1) Then 
Call IntegrateVSGoldstone(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
Else 
Call IntegrateVS(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
End If 
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = MAh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFeFeAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFeAhR(gt3,gt2,i1))  
coup(4) = cplAhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFeFeAhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFeFeAhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = MAh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplAhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFeFeAhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFeAhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFeFehhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFeFehhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Isum = Isum + 1 
 
resS = 0._dp 
mass(1) = Mhh(i1)  
mass(2) = Mhh(i2)  
coup(1) = cplhhSucSu(i1,gt1,iIN) 
coup(3) = Conjg(cplcFeFehhL(gt3,gt2,i1)) 
coup(2) = Conjg(cplcFeFehhR(gt3,gt2,i1))  
coup(4) = cplhhSucSu(i2,gt1,iIN) 
coup(6) = Conjg(cplcFeFehhL(gt3,gt2,i2)) 
coup(5) = Conjg(cplcFeFehhR(gt3,gt2,i2))  
Call IntegrateSaSb(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC = 1*resC  ! Color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fe cFe Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:25))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSuFecFe 
 
 
Subroutine SuToSuFvcFv(iIN,MSu,MVZ,cplSucSuVZ,cplcFvFvVZL,cplcFvFvVZR,deltaM,         & 
& epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MSu(6),MVZ

Complex(dp),Intent(in) :: cplSucSuVZ(6,6),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3)

Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp)::smin,smax,smin2,smax2,rj2,rk2,rm2 
Real(dp)::r_out(3),r_outcrossed(3) 
Real(dp)::mass(3) 
Complex(dp)::coup(10) 
mass(1) = MSu(iIN) 
 
Isum = 1 
Allocate( gSum(6,3,3, Isum) ) 
Allocate( Contribution(6,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
rk2 = (0./MSu(iIN))**2 
rm2 = (0./MSu(iIN))**2 
rj2 = (MSu(gt1)/MSu(iIN))**2 
smin=2._dp*Sqrt(rk2) 
smax=1._dp+rk2-rj2-rm2-2._dp*Sqrt(rj2*rm2) 
smin2=2._dp*Sqrt(rm2) 
smax2=1._dp+rm2-rj2-rk2-2._dp*Sqrt(rj2*rk2) 
m_in=MSu(iIN) 
r_out(1)=rj2 
r_out(2)=rk2 
r_out(3)=rm2 
r_outcrossed(1)=rj2 
r_outcrossed(2)=rm2 
r_outcrossed(3)=rk2 
If(Abs(MSu(iIN)).gt.(Abs(0.)+Abs(0.)+Abs(MSu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
resS=0._dp 
resD=0._dp 
 
mass(1) = MVZ 
mass(2) = MVZ 
m_in = MSu(iIN) 
coup(1) = Conjg(cplSucSuVZ(gt1,iIN)) 
coup(3) = Conjg(cplcFvFvVZL(gt3,gt2)) 
coup(2) = Conjg(cplcFvFvVZR(gt3,gt2))
coup(4:6) = coup(1:3) 
Call IntegrateVV(mass,m_in,r_out,coup,smin,smax,epsI,resC) 
If (resC.ne.resC) resC = 0._dp
resC = 1*resC  ! Color factor 
resS = resS + resC 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Su->Su Fv cFv Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:1))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
End Subroutine SuToSuFvcFv 
 
 
End Module Su3Decays_MSSM 
 
