! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:01 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module HiggsCS_MSSM 
 
Use Control 
Use Model_Data_MSSM 
Contains 
 
Subroutine HiggsCrossSections(mh,ratGG,ratPP,ratWW,ratZZ,ratTT,CS,kont)

Implicit None 
Real(dp), Intent(in) :: mh(:)  
Complex(dp), Intent(in) :: ratPP(:), ratGG(:)  
Real(dp), Intent(in) :: ratZZ(:), ratWW(:), ratTT(:)  
Real(dp), Intent(Out) :: CS(:,:,:)  
Integer, Intent(inout) :: kont 
Real(dp) :: x, res 
Integer :: i1 
Integer :: nG 
nG = Size(mh) 
!-------------------- 
! LHC 7 
!-------------------- 
Do i1=1, nG 
x = mh(i1) 
! Gluon fusion 
If ((x.gt.50._dp).AND.(x.lt.400._dp)) Then 
res = (1885.956352363666 + 65.64473765370352*x + 0.03702472403087486*x**2 - 0.00003515710830973974*x**3 + 1.8376395763565472e-8*x**4 - 741.0418758247033*Log(x) &
& - 5.809522140310252*x*Log(x) - 2.9047610698096142*x*Log(x**2))*ratGG(i1) 
Else If ((x.gt.400._dp).AND.(x.lt.1000._dp)) Then 
res = (-2189.522472919207 - 27.969039799037308*x - 0.004715946291758915*x**2 + 1.5079927656212702e-6*x**3 - 2.641896875867281e-10*x**4 + 660.9792799041949*Log(x) &
& + 2.103783219830703*x*Log(x) + 1.0518916099153515*x*Log(x**2))*ratGG(i1) 
Else 
res = - 1._dp 
      Write(10,*) 'Higgs mass outside range of cross section fit (gluon fusion): ',i1 
End if 
CS(1,i1,1) = res 
! Vector boson fusion 
If ((x.gt.50._dp).AND.(x.lt.1000._dp)) Then 
res = (5.25414_dp - 0.0734533_dp*x+0.000581303_dp*x**2-3.01053E-6_dp*x**3+1.04525E-8_dp*x**4 & 
   & -2.45215E-11_dp*x**5+3.88202E-14_dp*x**6-4.07876E-17_dp*x**7+2.72251E-20_dp*x**8 & 
   & -1.04436E-23_dp*x**9+1.7524E-27_dp*x**10)*ratZZ(i1) 
Else 
res = - 1._dp 
      Write(10,*) 'Higgs mass outside range of cross section fit (vector boson fusion): ',i1 
End if 
CS(1,i1,2) = res 
! W H production 
If ((x.gt.50._dp).AND.(x.lt.300._dp)) Then 
res = (-69.4076_dp+5.38691_dp*x-0.161522_dp*x**2+0.00267221_dp*x**3-0.0000277307_dp*x**4 & 
   & +1.90753E-7_dp*x**5-8.86085E-10_dp*x**6+2.75463E-12_dp*x**7-5.49889E-15_dp*x**8+ & 
   & 6.37758E-18_dp*x**9-3.26861E-21_dp*x**10)*ratWW(i1) 
Else 
res = - 1._dp 
      Write(10,*) 'Higgs mass outside range of cross section fit (associated W production): ',i1 
End if 
CS(1,i1,3) = res 
! Z H production 
If ((x.gt.50._dp).AND.(x.lt.300._dp)) Then 
res = (-4.51808_dp+0.879332_dp*x-0.0327293_dp*x**2+0.000599188_dp*x**3-6.60546E-6_dp*x**4+ & 
    & 4.73453E-8_dp*x**5-2.26708E-10_dp*x**6+7.2167E-13_dp*x**7-1.46855E-15_dp*x**8 & 
    & +1.73069E-18_dp*x**9-8.99186E-22_dp*x**10)*ratZZ(i1) 
Else 
res = - 1._dp 
      Write(10,*) 'Higgs mass outside range of cross section fit (associated Z production): ',i1 
End if 
CS(1,i1,4) = res 
! Top H production 
If ((x.gt.50._dp).AND.(x.lt.300._dp)) Then 
res = (5.79335_dp-0.252526*x+0.00556789_dp*x**2-0.0000774759_dp*x**3+7.28126E-7_dp*x**4 & 
   & -4.73452E-9_dp*x**5+2.13368E-11_dp*x**6-6.54283E-14_dp*x**7+1.30272E-16_dp*x**8 & 
   &-1.5188E-19_dp*x**9+7.87005E-23_dp*x**10)*ratTT(i1) 
Else 
res = - 1._dp 
      Write(10,*) 'Higgs mass outside range of cross section fit (associated top production): ',i1 
End if 
CS(1,i1,5) = res 
End Do 
!-------------------- 
! LHC 8 
!-------------------- 
Do i1=1,nG 
x = mh(i1) 
! Gluon fusion 
If ((x.gt.50._dp).AND.(x.lt.400._dp)) Then 
res = (2744.9702423084677 + 103.81729098620063*x + 0.06139677255630899*x**2 - 0.00005979983439515144*x**3 + 3.1844027995550145e-8*x**4 - 1111.3925134279953*Log(x)  &
& - 9.267622203785539*x*Log(x) - 4.6338111018940715*x*Log(x**2))*ratGG(i1) 
Else If ((x.gt.400._dp).AND.(x.lt.1000._dp)) Then 
res = (-3272.341690614643 - 41.18064985541245*x - 0.006881077235681396*x**2 + 2.1884539660190887e-6*x**3 - 3.818620289401707e-10*x**4 + 983.3789350725115*Log(x)  &
& + 3.093230920215274*x*Log(x) + 1.546615460107637*x*Log(x**2))*ratGG(i1) 
Else 
res = - 1._dp 
End if 
CS(2,i1,1) = res 
! Vector boson fusion 
If ((x.gt.50._dp).AND.(x.lt.1000._dp)) Then 
res = (6.45917_dp-0.090696_dp*x+0.000756681_dp*x**2-4.25544E-6_dp*x**3+1.6216E-8_dp*x**4 & 
  &-4.16953E-11_dp*x**5+7.18694E-14_dp*x**6-8.15593E-17_dp*x**7+5.83415E-20_dp*x**8 & 
  & -2.38158E-23_dp*x**9+4.22658E-27_dp*x**10)*ratZZ(i1)
Else 
res = - 1._dp 
End if 
CS(2,i1,2) = res 
! W H production 
If ((x.gt.50._dp).AND.(x.lt.300._dp)) Then 
res = (51.9185_dp-1.66922_dp*x+0.0217199_dp*x**2-0.000108854_dp*x**3-4.74324E-7_dp*x**4 & 
  & +1.06345E-8_dp*x**5-7.33073E-11_dp*x**6+2.80923E-13_dp*x**7-6.36746E-16_dp*x**8 & 
  & +8.01196E-19_dp*x**9-4.32969E-22_dp*x**10)*ratWW(i1) 
Else 
res = - 1._dp 
End if 
CS(2,i1,3) = res 
! Z H production 
If ((x.gt.50._dp).AND.(x.lt.300._dp)) Then 
res = (37.2204_dp-1.53699_dp*x+0.0301782_dp*x**2-0.000360433_dp*x**3+2.85526E-6_dp*x**4 & 
  & -1.55501E-8_dp*x**5+5.87383E-11_dp*x**6-1.51741E-13_dp*x**7+2.56563E-16_dp*x**8 & 
  & -2.56563E-19_dp*x**9+1.15347E-22_dp*x**10)*ratZZ(i1) 
Else 
res = - 1._dp 
End if 
CS(2,i1,4) = res 
! Top H production 
If ((x.gt.50._dp).AND.(x.lt.300._dp)) Then 
res = (5.11388_dp-0.148939_dp*x+0.00188169_dp*x**2-0.0000111773_dp*x**3+2.1513E-9_dp*x**4 & 
  & +4.65548E-10_dp*x**5-3.64602E-12_dp*x**6+1.46E-14_dp*x**7-3.40031E-17_dp*x**8 & 
  & +4.38198E-20_dp*x**9-2.42706E-23_dp*x**10)*ratTT(i1) 
Else 
res = - 1._dp 
End if 
CS(2,i1,5) = res 
End Do 
!-------------------- 
! LHC 13 
!-------------------- 
Do i1=1,nG 
x = mh(i1) 
! Gluon fusion 
If ((x.gt.50._dp).AND.(x.lt.400._dp)) Then 
res = (11616.77702766903 + 700.9534922253372*x + 0.6550151443825573*x**2 - 0.0010432868789482976*x**3 + 1.208231269118169e-6*x**4 - 6.502604577273565e-10*x**5 &
&  - 5555.016263186344*Log(x) - 66.97248427992604*x*Log(x) - 33.486242139963004*x*Log(x**2))*ratGG(i1) 
Else If ((x.gt.400._dp).AND.(x.lt.1000._dp)) Then 
res = (-37568.9089823239 - 544.6657590030997*x - 0.11932971667208431*x**2 + 0.000055460517739423844*x**3 - 1.909418438981979e-8*x**4 + 3.1219539385171897e-12*x**5 &
& + 11611.750198662685*Log(x) + 42.11680032656563*x*Log(x) + 21.058400163282815*x*Log(x**2))*ratGG(i1) 
Else 
res = - 1._dp 
End if 
CS(3,i1,1) = res 
CS(3,i1,2) = -1._dp 
CS(3,i1,3) = -1._dp 
CS(3,i1,4) = -1._dp 
CS(3,i1,5) = -1._dp 
End Do 
!-------------------- 
! LHC 14 
!-------------------- 
Do i1=1,nG 
x = mh(i1) 
! Gluon fusion 
If ((x.gt.50._dp).AND.(x.lt.400._dp)) Then 
res = (12627.037286907853 + 761.7561325918041*x + 0.7127313611572541*x**2 - 0.001136747682670838*x**3 + 1.3186088702471044e-6*x**4 - 7.109649199986356e-10*x**5 - &
& 6035.831412165335*Log(x) - 72.79453235633025*x*Log(x) - 36.39726617816514*x*Log(x**2))*ratGG(i1) 
Else If ((x.gt.400._dp).AND.(x.lt.1000._dp)) Then 
res = (-44114.027394060526 - 638.1870701097589*x - 0.1396008932035218*x**2 + 0.00006481592980613609*x**3 - 2.229740732085902e-8*x**4 + 3.643396291746081e-12*x**5 & 
 & + 13626.22975496127*Log(x) + 49.33683580242861*x*Log(x) + 24.66841790121431*x*Log(x**2))*ratGG(i1) 
Else 
res = - 1._dp 
End if 
CS(4,i1,1) = res 
CS(4,i1,2) = -1._dp 
CS(4,i1,3) = -1._dp 
CS(4,i1,4) = -1._dp 
CS(4,i1,5) = -1._dp 
End Do 
!-------------------- 
! FCC 100 
!-------------------- 
Do i1=1,nG 
x = mh(i1) 
! Gluon fusion 
If ((x.gt.50._dp).AND.(x.lt.400._dp)) Then 
res = (91563.13847371943 + 5841.145237134141*x + 5.929645328153345*x**2 - 0.010165009857023455*x**3 + 0.000012703573375868591*x**4 - 7.36545750406916e-9*x**5 - &
 & 44361.1760451764*Log(x) - 565.3597702677172*x*Log(x) - 282.6798851338586*x*Log(x**2))*ratGG(i1) 
Else If ((x.gt.400._dp).AND.(x.lt.1000._dp)) Then 
res = (-1.2460207772054581e6 - 17442.734204568525*x - 3.72429466661745*x**2 + 0.0017023146911045368*x**3 - 5.785813311932391e-7*x**4 + 9.364790456487542e-11*x**5 &
& + 381260.0641650691*Log(x) + 1343.5646363825153*x*Log(x) + 671.7823181912577*x*Log(x**2))*ratGG(i1) 
Else 
res = - 1._dp 
End if 
CS(5,i1,1) = res 
CS(5,i1,2) = -1._dp 
CS(5,i1,3) = -1._dp 
CS(5,i1,4) = -1._dp 
CS(5,i1,5) = -1._dp 
End Do 
End Subroutine HiggsCrossSections 
End Module HiggsCS_MSSM
