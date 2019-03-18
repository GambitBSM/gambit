{{sum[gI1, 1, 6, sum[gI2, 1, 3, B0[p^2, Mass2[Fd[{gI2}]], Mass2[Sd[{gI1}]]]*
      conj[Cp[Glu[{gO2}], conj[Sd[{gI1}]], Fd[{gI2}]][PL]]*Mass[Fd[{gI2}]]*
      Cp[Glu[{gO1}], conj[Sd[{gI1}]], Fd[{gI2}]][PR]]] + 
   sum[gI1, 1, 6, sum[gI2, 1, 3, B0[p^2, Mass2[Fu[{gI2}]], Mass2[Su[{gI1}]]]*
      conj[Cp[Glu[{gO2}], conj[Su[{gI1}]], Fu[{gI2}]][PL]]*Mass[Fu[{gI2}]]*
      Cp[Glu[{gO1}], conj[Su[{gI1}]], Fu[{gI2}]][PR]]] - 
   12*(-rMS/2 + B0[p^2, Mass2[Glu], 0])*
    conj[Cp[Glu[{gO2}], VG, Glu[{1}]][PR]]*Mass[Glu]*
    Cp[Glu[{gO1}], VG, Glu[{1}]][PL], 
  -sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], Mass2[Sd[{gI1}]]]*
        conj[Cp[Glu[{gO2}], conj[Sd[{gI1}]], Fd[{gI2}]][PR]]*
        Cp[Glu[{gO1}], conj[Sd[{gI1}]], Fd[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], Mass2[Su[{gI1}]]]*
       conj[Cp[Glu[{gO2}], conj[Su[{gI1}]], Fu[{gI2}]][PR]]*
       Cp[Glu[{gO1}], conj[Su[{gI1}]], Fu[{gI2}]][PR]]]/2 - 
   3*(rMS/2 + B1[p^2, Mass2[Glu], 0])*conj[Cp[Glu[{gO2}], VG, Glu[{1}]][PL]]*
    Cp[Glu[{gO1}], VG, Glu[{1}]][PL], 
  -sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], Mass2[Sd[{gI1}]]]*
        conj[Cp[Glu[{gO2}], conj[Sd[{gI1}]], Fd[{gI2}]][PL]]*
        Cp[Glu[{gO1}], conj[Sd[{gI1}]], Fd[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], Mass2[Su[{gI1}]]]*
       conj[Cp[Glu[{gO2}], conj[Su[{gI1}]], Fu[{gI2}]][PL]]*
       Cp[Glu[{gO1}], conj[Su[{gI1}]], Fu[{gI2}]][PL]]]/2 - 
   3*(rMS/2 + B1[p^2, Mass2[Glu], 0])*conj[Cp[Glu[{gO2}], VG, Glu[{1}]][PR]]*
    Cp[Glu[{gO1}], VG, Glu[{1}]][PR]}, 0, 0, 0, 
 B00[p^2, Mass2[gWm], Mass2[gWm]]*conj[Cp[VZ, bar[gWm], gWm]]*
   Cp[VZ, bar[gWm], gWm] + B00[p^2, Mass2[gWmC], Mass2[gWmC]]*
   conj[Cp[VZ, bar[gWmC], gWmC]]*Cp[VZ, bar[gWmC], gWmC] - 
  conj[Cp[VZ, conj[VWm], VWm]]*Cp[VZ, conj[VWm], VWm]*
   (2*A0[Mass2[VWm]] + 10*B00[p^2, Mass2[VWm], Mass2[VWm]] - 
    2*rMS*(-p^2/3 + 2*Mass2[VWm]) + B0[p^2, Mass2[VWm], Mass2[VWm]]*
     (4*p^2 + 2*Mass2[VWm])) + 
  sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*Cp[VZ, VZ, Ah[{gI1}], Ah[{gI1}]]]/2 + 
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[VZ, VZ, conj[Hpm[{gI1}]], 
     Hpm[{gI1}]]] + sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*
     Cp[VZ, VZ, hh[{gI1}], hh[{gI1}]]]/2 - 
  4*sum[gI1, 1, 2, sum[gI2, 1, 2, B00[p^2, Mass2[Hpm[{gI1}]], 
       Mass2[Hpm[{gI2}]]]*conj[Cp[VZ, conj[Hpm[{gI1}]], Hpm[{gI2}]]]*
      Cp[VZ, conj[Hpm[{gI1}]], Hpm[{gI2}]]]] - 
  4*sum[gI1, 1, 2, sum[gI2, 1, 2, B00[p^2, Mass2[Ah[{gI2}]], 
       Mass2[hh[{gI1}]]]*conj[Cp[VZ, hh[{gI1}], Ah[{gI2}]]]*
      Cp[VZ, hh[{gI1}], Ah[{gI2}]]]] + sum[gI1, 1, 2, 
   sum[gI2, 1, 2, 4*B0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
      Mass[Cha[{gI1}]]*Mass[Cha[{gI2}]]*
      Re[conj[Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
        Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PR]] + 
     H0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
      (conj[Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
        Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
       conj[Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PR]]*
        Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*Cp[VZ, VZ, conj[Sv[{gI1}]], 
     Sv[{gI1}]]] - 4*sum[gI1, 1, 3, sum[gI2, 1, 3, 
     B00[p^2, Mass2[Sv[{gI1}]], Mass2[Sv[{gI2}]]]*
      conj[Cp[VZ, conj[Sv[{gI1}]], Sv[{gI2}]]]*Cp[VZ, conj[Sv[{gI1}]], 
       Sv[{gI2}]]]] + 3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
     4*B0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI1}]]*
       Mass[Fd[{gI2}]]*Re[conj[Cp[VZ, bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[VZ, bar[Fd[{gI1}]], Fd[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*
       (conj[Cp[VZ, bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[VZ, bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[VZ, bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[VZ, bar[Fd[{gI1}]], Fd[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, 4*B0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*
      Mass[Fe[{gI1}]]*Mass[Fe[{gI2}]]*
      Re[conj[Cp[VZ, bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[VZ, bar[Fe[{gI1}]], Fe[{gI2}]][PR]] + 
     H0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*
      (conj[Cp[VZ, bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[VZ, bar[Fe[{gI1}]], Fe[{gI2}]][PL] + 
       conj[Cp[VZ, bar[Fe[{gI1}]], Fe[{gI2}]][PR]]*
        Cp[VZ, bar[Fe[{gI1}]], Fe[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
     4*B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*Mass[Fu[{gI1}]]*
       Mass[Fu[{gI2}]]*Re[conj[Cp[VZ, bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[VZ, bar[Fu[{gI1}]], Fu[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*
       (conj[Cp[VZ, bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[VZ, bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
        conj[Cp[VZ, bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
         Cp[VZ, bar[Fu[{gI1}]], Fu[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, 4*B0[p^2, Mass2[Fv[{gI1}]], Mass2[Fv[{gI2}]]]*
      Mass[Fv[{gI1}]]*Mass[Fv[{gI2}]]*
      Re[conj[Cp[VZ, bar[Fv[{gI1}]], Fv[{gI2}]][PL]]*
        Cp[VZ, bar[Fv[{gI1}]], Fv[{gI2}]][PR]] + 
     H0[p^2, Mass2[Fv[{gI1}]], Mass2[Fv[{gI2}]]]*
      (conj[Cp[VZ, bar[Fv[{gI1}]], Fv[{gI2}]][PL]]*
        Cp[VZ, bar[Fv[{gI1}]], Fv[{gI2}]][PL] + 
       conj[Cp[VZ, bar[Fv[{gI1}]], Fv[{gI2}]][PR]]*
        Cp[VZ, bar[Fv[{gI1}]], Fv[{gI2}]][PR])]] + 
  sum[gI1, 1, 4, sum[gI2, 1, 4, 
     4*B0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI1}]]*
       Mass[Chi[{gI2}]]*Re[conj[Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PL]]*
         Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PR]] + 
      H0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*
       (conj[Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PL]]*
         Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PL] + 
        conj[Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PR]]*
         Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PR])]]/2 + 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[VZ, VZ, conj[Sd[{gI1}]], 
      Sd[{gI1}]]] + sum[gI1, 1, 6, A0[Mass2[Se[{gI1}]]]*
    Cp[VZ, VZ, conj[Se[{gI1}]], Se[{gI1}]]] + 
  3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*Cp[VZ, VZ, conj[Su[{gI1}]], 
      Su[{gI1}]]] - 12*sum[gI1, 1, 6, sum[gI2, 1, 6, 
     B00[p^2, Mass2[Sd[{gI1}]], Mass2[Sd[{gI2}]]]*
      conj[Cp[VZ, conj[Sd[{gI1}]], Sd[{gI2}]]]*Cp[VZ, conj[Sd[{gI1}]], 
       Sd[{gI2}]]]] - 4*sum[gI1, 1, 6, sum[gI2, 1, 6, 
     B00[p^2, Mass2[Se[{gI1}]], Mass2[Se[{gI2}]]]*
      conj[Cp[VZ, conj[Se[{gI1}]], Se[{gI2}]]]*Cp[VZ, conj[Se[{gI1}]], 
       Se[{gI2}]]]] - 12*sum[gI1, 1, 6, sum[gI2, 1, 6, 
     B00[p^2, Mass2[Su[{gI1}]], Mass2[Su[{gI2}]]]*
      conj[Cp[VZ, conj[Su[{gI1}]], Su[{gI2}]]]*Cp[VZ, conj[Su[{gI1}]], 
       Su[{gI2}]]]] + sum[gI2, 1, 2, B0[p^2, Mass2[VZ], Mass2[hh[{gI2}]]]*
    conj[Cp[VZ, VZ, hh[{gI2}]]]*Cp[VZ, VZ, hh[{gI2}]]] + 
  2*sum[gI2, 1, 2, B0[p^2, Mass2[VWm], Mass2[Hpm[{gI2}]]]*
     conj[Cp[VZ, conj[VWm], Hpm[{gI2}]]]*Cp[VZ, conj[VWm], Hpm[{gI2}]]] + 
  2*rMS*Mass2[VWm]*Cp[VZ, VZ, conj[VWm], VWm][1] - 
  A0[Mass2[VWm]]*(4*Cp[VZ, VZ, conj[VWm], VWm][1] + 
    Cp[VZ, VZ, conj[VWm], VWm][2] + Cp[VZ, VZ, conj[VWm], VWm][3]), 
 B00[p^2, Mass2[gWm], Mass2[gP]]*conj[Cp[conj[VWm], bar[gP], gWm]]*
   Cp[conj[VWm], bar[gP], gWm] + B00[p^2, Mass2[gP], Mass2[gWmC]]*
   conj[Cp[conj[VWm], bar[gWmC], gP]]*Cp[conj[VWm], bar[gWmC], gP] + 
  B00[p^2, Mass2[gZ], Mass2[gWmC]]*conj[Cp[conj[VWm], bar[gWmC], gZ]]*
   Cp[conj[VWm], bar[gWmC], gZ] + B00[p^2, Mass2[gWm], Mass2[gZ]]*
   conj[Cp[conj[VWm], bar[gZ], gWm]]*Cp[conj[VWm], bar[gZ], gWm] - 
  conj[Cp[conj[VWm], VWm, VP]]*Cp[conj[VWm], VWm, VP]*
   (A0[0] + A0[Mass2[VWm]] + 10*B00[p^2, Mass2[VWm], 0] - 
    2*rMS*(-p^2/3 + Mass2[VWm]) + B0[p^2, Mass2[VWm], 0]*
     (4*p^2 + Mass2[VWm])) - conj[Cp[conj[VWm], VZ, VWm]]*
   Cp[conj[VWm], VZ, VWm]*(A0[Mass2[VWm]] + A0[Mass2[VZ]] + 
    10*B00[p^2, Mass2[VZ], Mass2[VWm]] - 
    2*rMS*(-p^2/3 + Mass2[VWm] + Mass2[VZ]) + B0[p^2, Mass2[VZ], Mass2[VWm]]*
     (4*p^2 + Mass2[VWm] + Mass2[VZ])) + 
  sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*Cp[VWm, conj[VWm], Ah[{gI1}], 
      Ah[{gI1}]]]/2 + sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*
    Cp[VWm, conj[VWm], conj[Hpm[{gI1}]], Hpm[{gI1}]]] + 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[VWm, conj[VWm], hh[{gI1}], 
      hh[{gI1}]]]/2 - 4*sum[gI1, 1, 2, sum[gI2, 1, 2, 
     B00[p^2, Mass2[Ah[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[conj[VWm], Hpm[{gI1}], Ah[{gI2}]]]*Cp[conj[VWm], Hpm[{gI1}], 
       Ah[{gI2}]]]] - 4*sum[gI1, 1, 2, sum[gI2, 1, 2, 
     B00[p^2, Mass2[hh[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[conj[VWm], Hpm[{gI1}], hh[{gI2}]]]*Cp[conj[VWm], Hpm[{gI1}], 
       hh[{gI2}]]]] + sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*
    Cp[VWm, conj[VWm], conj[Sv[{gI1}]], Sv[{gI1}]]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
     4*B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI2}]]*
       Mass[Fu[{gI1}]]*Re[conj[Cp[conj[VWm], bar[Fu[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[conj[VWm], bar[Fu[{gI1}]], Fd[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fu[{gI1}]], Mass2[Fd[{gI2}]]]*
       (conj[Cp[conj[VWm], bar[Fu[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[conj[VWm], bar[Fu[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[conj[VWm], bar[Fu[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[conj[VWm], bar[Fu[{gI1}]], Fd[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, 4*B0[p^2, Mass2[Fv[{gI1}]], Mass2[Fe[{gI2}]]]*
      Mass[Fe[{gI2}]]*Mass[Fv[{gI1}]]*
      Re[conj[Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PR]] + 
     H0[p^2, Mass2[Fv[{gI1}]], Mass2[Fe[{gI2}]]]*
      (conj[Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PL] + 
       conj[Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PR]]*
        Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PR])]] - 
  4*sum[gI1, 1, 3, sum[gI2, 1, 6, B00[p^2, Mass2[Se[{gI2}]], 
       Mass2[Sv[{gI1}]]]*conj[Cp[conj[VWm], conj[Sv[{gI1}]], Se[{gI2}]]]*
      Cp[conj[VWm], conj[Sv[{gI1}]], Se[{gI2}]]]] + 
  sum[gI1, 1, 4, sum[gI2, 1, 2, 
    4*B0[p^2, Mass2[Chi[{gI1}]], Mass2[Cha[{gI2}]]]*Mass[Cha[{gI2}]]*
      Mass[Chi[{gI1}]]*Re[conj[Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PL]]*
        Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PR]] + 
     H0[p^2, Mass2[Chi[{gI1}]], Mass2[Cha[{gI2}]]]*
      (conj[Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PL]]*
        Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PL] + 
       conj[Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PR]]*
        Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[VWm, conj[VWm], conj[Sd[{gI1}]], 
      Sd[{gI1}]]] + sum[gI1, 1, 6, A0[Mass2[Se[{gI1}]]]*
    Cp[VWm, conj[VWm], conj[Se[{gI1}]], Se[{gI1}]]] + 
  3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*Cp[VWm, conj[VWm], conj[Su[{gI1}]], 
      Su[{gI1}]]] - 12*sum[gI1, 1, 6, sum[gI2, 1, 6, 
     B00[p^2, Mass2[Sd[{gI2}]], Mass2[Su[{gI1}]]]*
      conj[Cp[conj[VWm], conj[Su[{gI1}]], Sd[{gI2}]]]*
      Cp[conj[VWm], conj[Su[{gI1}]], Sd[{gI2}]]]] + 
  sum[gI2, 1, 2, B0[p^2, 0, Mass2[Hpm[{gI2}]]]*
    conj[Cp[conj[VWm], VP, Hpm[{gI2}]]]*Cp[conj[VWm], VP, Hpm[{gI2}]]] + 
  sum[gI2, 1, 2, B0[p^2, Mass2[VWm], Mass2[hh[{gI2}]]]*
    conj[Cp[conj[VWm], VWm, hh[{gI2}]]]*Cp[conj[VWm], VWm, hh[{gI2}]]] + 
  sum[gI2, 1, 2, B0[p^2, Mass2[VZ], Mass2[Hpm[{gI2}]]]*
    conj[Cp[conj[VWm], VZ, Hpm[{gI2}]]]*Cp[conj[VWm], VZ, Hpm[{gI2}]]] - 
  (A0[0]*(4*Cp[VWm, conj[VWm], VP, VP][1] + Cp[VWm, conj[VWm], VP, VP][2] + 
     Cp[VWm, conj[VWm], VP, VP][3]))/2 + 
  (2*rMS*Mass2[VZ]*Cp[VWm, conj[VWm], VZ, VZ][1] - 
    A0[Mass2[VZ]]*(4*Cp[VWm, conj[VWm], VZ, VZ][1] + 
      Cp[VWm, conj[VWm], VZ, VZ][2] + Cp[VWm, conj[VWm], VZ, VZ][3]))/2 + 
  2*rMS*Mass2[VWm]*Cp[VWm, conj[VWm], conj[VWm], VWm][1] - 
  A0[Mass2[VWm]]*(4*Cp[VWm, conj[VWm], conj[VWm], VWm][1] + 
    Cp[VWm, conj[VWm], conj[VWm], VWm][2] + 
    Cp[VWm, conj[VWm], conj[VWm], VWm][3])}
