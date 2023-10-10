Module Kinematics
Use Control

Contains

Real(dp) Function kaellen(mx,my,mz)
Implicit None
Real(dp), Intent(in) :: mx, my, mz

kaellen = mx * mx + my * my + mz * mz &
  & - 2._dp * mx * my - 2._dp * mx * mz - 2._dp * my *mz

End Function kaellen

Real(dp) Function GammaTPS(mci,mw,mch,RMsquared)
!TPS = Two-Body Phase Space
Implicit None
Real(dp), Intent(in) :: mci,mw,mch,RMsquared
Real(dp) :: mcip2, mwp2, mchp2

mcip2 = mci * mci
mwp2 = mw * mw
mchp2 = mch * mch

GammaTPS = kaellen(mcip2,mwp2,mchp2)
GammaTPS = sqrt(GammaTPS)
GammaTPS = GammaTPS * RMSquared
GammaTPS = GammaTPS / (16._dp * Pi * mci * mcip2)

End Function GammaTPS

End Module Kinematics