{{sum[gI1, 1, 2, sum[gI2, 1, 3, B0[p^2, Mass2[Fe[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[bar[Fv[{gO2}]], conj[Hpm[{gI1}]], Fe[{gI2}]][PL]]*
      Mass[Fe[{gI2}]]*Cp[bar[Fv[{gO1}]], conj[Hpm[{gI1}]], Fe[{gI2}]][PR]]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fv[{gI2}]], Mass2[VZ]])*
      conj[Cp[bar[Fv[{gO2}]], VZ, Fv[{gI2}]][PR]]*Mass[Fv[{gI2}]]*
      Cp[bar[Fv[{gO1}]], VZ, Fv[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fe[{gI2}]], Mass2[VWm]])*
      conj[Cp[bar[Fv[{gO2}]], conj[VWm], Fe[{gI2}]][PR]]*Mass[Fe[{gI2}]]*
      Cp[bar[Fv[{gO1}]], conj[VWm], Fe[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[Hpm[{gI1}]]]*
        conj[Cp[bar[Fv[{gO2}]], conj[Hpm[{gI1}]], Fe[{gI2}]][PR]]*
        Cp[bar[Fv[{gO1}]], conj[Hpm[{gI1}]], Fe[{gI2}]][PR]]]/2 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fv[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[Fv[{gO2}]], VZ, Fv[{gI2}]][PL]]*
     Cp[bar[Fv[{gO1}]], VZ, Fv[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fe[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[Fv[{gO2}]], conj[VWm], Fe[{gI2}]][PL]]*
     Cp[bar[Fv[{gO1}]], conj[VWm], Fe[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[Hpm[{gI1}]]]*
        conj[Cp[bar[Fv[{gO2}]], conj[Hpm[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[bar[Fv[{gO1}]], conj[Hpm[{gI1}]], Fe[{gI2}]][PL]]]/2 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fv[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[Fv[{gO2}]], VZ, Fv[{gI2}]][PR]]*
     Cp[bar[Fv[{gO1}]], VZ, Fv[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fe[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[Fv[{gO2}]], conj[VWm], Fe[{gI2}]][PR]]*
     Cp[bar[Fv[{gO1}]], conj[VWm], Fe[{gI2}]][PR]]}, 
 (-3*((2*p^2*rMS)/3 + 2*A0[0] + 4*p^2*B0[p^2, 0, 0] + 10*B00[p^2, 0, 0])*
    conj[Cp[VG, VG, VG]]*Cp[VG, VG, VG])/2 + 3*B00[p^2, Mass2[gG], Mass2[gG]]*
   conj[Cp[VG, bar[gG], gG]]*Cp[VG, bar[gG], gG] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, 4*B0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*
       Mass[Fd[{gI1}]]*Mass[Fd[{gI2}]]*
       Re[conj[Cp[VG, bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[VG, bar[Fd[{gI1}]], Fd[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*
       (conj[Cp[VG, bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[VG, bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[VG, bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[VG, bar[Fd[{gI1}]], Fd[{gI2}]][PR])]]/2 + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, 4*B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*
       Mass[Fu[{gI1}]]*Mass[Fu[{gI2}]]*
       Re[conj[Cp[VG, bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[VG, bar[Fu[{gI1}]], Fu[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*
       (conj[Cp[VG, bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[VG, bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
        conj[Cp[VG, bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
         Cp[VG, bar[Fu[{gI1}]], Fu[{gI2}]][PR])]]/2 - 
  (A0[0]*(4*Cp[VG, VG, VG, VG][1] + Cp[VG, VG, VG, VG][2] + 
     Cp[VG, VG, VG, VG][3]))/2, B00[p^2, Mass2[gWm], Mass2[gWm]]*
   conj[Cp[VP, bar[gWm], gWm]]*Cp[VP, bar[gWm], gWm] + 
  B00[p^2, Mass2[gWmC], Mass2[gWmC]]*conj[Cp[VP, bar[gWmC], gWmC]]*
   Cp[VP, bar[gWmC], gWmC] - conj[Cp[VP, conj[VWm], VWm]]*
   Cp[VP, conj[VWm], VWm]*(2*A0[Mass2[VWm]] + 
    10*B00[p^2, Mass2[VWm], Mass2[VWm]] - 2*rMS*(-p^2/3 + 2*Mass2[VWm]) + 
    B0[p^2, Mass2[VWm], Mass2[VWm]]*(4*p^2 + 2*Mass2[VWm])) + 
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[VP, VP, conj[Hpm[{gI1}]], 
     Hpm[{gI1}]]] - 4*sum[gI1, 1, 2, sum[gI2, 1, 2, 
     B00[p^2, Mass2[Hpm[{gI1}]], Mass2[Hpm[{gI2}]]]*
      conj[Cp[VP, conj[Hpm[{gI1}]], Hpm[{gI2}]]]*Cp[VP, conj[Hpm[{gI1}]], 
       Hpm[{gI2}]]]] + sum[gI1, 1, 2, sum[gI2, 1, 2, 
    4*B0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*Mass[Cha[{gI1}]]*
      Mass[Cha[{gI2}]]*Re[conj[Cp[VP, bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
        Cp[VP, bar[Cha[{gI1}]], Cha[{gI2}]][PR]] + 
     H0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
      (conj[Cp[VP, bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
        Cp[VP, bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
       conj[Cp[VP, bar[Cha[{gI1}]], Cha[{gI2}]][PR]]*
        Cp[VP, bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
     4*B0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI1}]]*
       Mass[Fd[{gI2}]]*Re[conj[Cp[VP, bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[VP, bar[Fd[{gI1}]], Fd[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*
       (conj[Cp[VP, bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[VP, bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[VP, bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[VP, bar[Fd[{gI1}]], Fd[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, 4*B0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*
      Mass[Fe[{gI1}]]*Mass[Fe[{gI2}]]*
      Re[conj[Cp[VP, bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[VP, bar[Fe[{gI1}]], Fe[{gI2}]][PR]] + 
     H0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*
      (conj[Cp[VP, bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
        Cp[VP, bar[Fe[{gI1}]], Fe[{gI2}]][PL] + 
       conj[Cp[VP, bar[Fe[{gI1}]], Fe[{gI2}]][PR]]*
        Cp[VP, bar[Fe[{gI1}]], Fe[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
     4*B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*Mass[Fu[{gI1}]]*
       Mass[Fu[{gI2}]]*Re[conj[Cp[VP, bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[VP, bar[Fu[{gI1}]], Fu[{gI2}]][PR]] + 
      H0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*
       (conj[Cp[VP, bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[VP, bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
        conj[Cp[VP, bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
         Cp[VP, bar[Fu[{gI1}]], Fu[{gI2}]][PR])]] + 
  2*sum[gI2, 1, 2, B0[p^2, Mass2[VWm], Mass2[Hpm[{gI2}]]]*
     conj[Cp[VP, conj[VWm], Hpm[{gI2}]]]*Cp[VP, conj[VWm], Hpm[{gI2}]]] + 
  2*rMS*Mass2[VWm]*Cp[VP, VP, conj[VWm], VWm][1] - 
  A0[Mass2[VWm]]*(4*Cp[VP, VP, conj[VWm], VWm][1] + 
    Cp[VP, VP, conj[VWm], VWm][2] + Cp[VP, VP, conj[VWm], VWm][3]), 
 B00[p^2, Mass2[gWm], Mass2[gWm]]*conj[Cp[VZ, bar[gWm], gWm]]*
   Cp[VZ, bar[gWm], gWm] + B00[p^2, Mass2[gWmC], Mass2[gWmC]]*
   conj[Cp[VZ, bar[gWmC], gWmC]]*Cp[VZ, bar[gWmC], gWmC] - 
  conj[Cp[VZ, conj[VWm], VWm]]*Cp[VZ, conj[VWm], VWm]*
   (2*A0[Mass2[VWm]] + 10*B00[p^2, Mass2[VWm], Mass2[VWm]] - 
    2*rMS*(-p^2/3 + 2*Mass2[VWm]) + B0[p^2, Mass2[VWm], Mass2[VWm]]*
     (4*p^2 + 2*Mass2[VWm])) + sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*
    Cp[VZ, VZ, conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  4*sum[gI1, 1, 2, sum[gI2, 1, 2, B00[p^2, Mass2[Hpm[{gI1}]], 
       Mass2[Hpm[{gI2}]]]*conj[Cp[VZ, conj[Hpm[{gI1}]], Hpm[{gI2}]]]*
      Cp[VZ, conj[Hpm[{gI1}]], Hpm[{gI2}]]]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, 
    4*B0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*Mass[Cha[{gI1}]]*
      Mass[Cha[{gI2}]]*Re[conj[Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
        Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PR]] + 
     H0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
      (conj[Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
        Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
       conj[Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PR]]*
        Cp[VZ, bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, A0[Mass2[Ah[{gI1}]]]*Cp[VZ, VZ, Ah[{gI1}], Ah[{gI1}]]]/2 + 
  sum[gI1, 1, 3, A0[Mass2[hh[{gI1}]]]*Cp[VZ, VZ, hh[{gI1}], hh[{gI1}]]]/2 - 
  4*sum[gI1, 1, 3, sum[gI2, 1, 3, B00[p^2, Mass2[Ah[{gI2}]], 
       Mass2[hh[{gI1}]]]*conj[Cp[VZ, hh[{gI1}], Ah[{gI2}]]]*
      Cp[VZ, hh[{gI1}], Ah[{gI2}]]]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
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
  sum[gI1, 1, 5, sum[gI2, 1, 5, 
     4*B0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI1}]]*
       Mass[Chi[{gI2}]]*Re[conj[Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PL]]*
         Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PR]] + 
      H0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*
       (conj[Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PL]]*
         Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PL] + 
        conj[Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PR]]*
         Cp[VZ, Chi[{gI1}], Chi[{gI2}]][PR])]]/2 + 
  2*sum[gI2, 1, 2, B0[p^2, Mass2[VWm], Mass2[Hpm[{gI2}]]]*
     conj[Cp[VZ, conj[VWm], Hpm[{gI2}]]]*Cp[VZ, conj[VWm], Hpm[{gI2}]]] + 
  sum[gI2, 1, 3, B0[p^2, Mass2[VZ], Mass2[hh[{gI2}]]]*
    conj[Cp[VZ, VZ, hh[{gI2}]]]*Cp[VZ, VZ, hh[{gI2}]]] + 
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
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[VWm, conj[VWm], conj[Hpm[{gI1}]], 
     Hpm[{gI1}]]] - 4*sum[gI1, 1, 2, sum[gI2, 1, 3, 
     B00[p^2, Mass2[Ah[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[conj[VWm], Hpm[{gI1}], Ah[{gI2}]]]*Cp[conj[VWm], Hpm[{gI1}], 
       Ah[{gI2}]]]] - 4*sum[gI1, 1, 2, sum[gI2, 1, 3, 
     B00[p^2, Mass2[hh[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[conj[VWm], Hpm[{gI1}], hh[{gI2}]]]*Cp[conj[VWm], Hpm[{gI1}], 
       hh[{gI2}]]]] + sum[gI1, 1, 3, A0[Mass2[Ah[{gI1}]]]*
     Cp[VWm, conj[VWm], Ah[{gI1}], Ah[{gI1}]]]/2 + 
  sum[gI1, 1, 3, A0[Mass2[hh[{gI1}]]]*Cp[VWm, conj[VWm], hh[{gI1}], 
      hh[{gI1}]]]/2 + 3*sum[gI1, 1, 3, sum[gI2, 1, 3, 
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
        Cp[conj[VWm], bar[Fv[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 5, sum[gI2, 1, 2, 
    4*B0[p^2, Mass2[Chi[{gI1}]], Mass2[Cha[{gI2}]]]*Mass[Cha[{gI2}]]*
      Mass[Chi[{gI1}]]*Re[conj[Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PL]]*
        Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PR]] + 
     H0[p^2, Mass2[Chi[{gI1}]], Mass2[Cha[{gI2}]]]*
      (conj[Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PL]]*
        Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PL] + 
       conj[Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PR]]*
        Cp[conj[VWm], Chi[{gI1}], Cha[{gI2}]][PR])]] + 
  sum[gI2, 1, 2, B0[p^2, 0, Mass2[Hpm[{gI2}]]]*
    conj[Cp[conj[VWm], VP, Hpm[{gI2}]]]*Cp[conj[VWm], VP, Hpm[{gI2}]]] + 
  sum[gI2, 1, 2, B0[p^2, Mass2[VZ], Mass2[Hpm[{gI2}]]]*
    conj[Cp[conj[VWm], VZ, Hpm[{gI2}]]]*Cp[conj[VWm], VZ, Hpm[{gI2}]]] + 
  sum[gI2, 1, 3, B0[p^2, Mass2[VWm], Mass2[hh[{gI2}]]]*
    conj[Cp[conj[VWm], VWm, hh[{gI2}]]]*Cp[conj[VWm], VWm, hh[{gI2}]]] - 
  (A0[0]*(4*Cp[VWm, conj[VWm], VP, VP][1] + Cp[VWm, conj[VWm], VP, VP][2] + 
     Cp[VWm, conj[VWm], VP, VP][3]))/2 + 
  (2*rMS*Mass2[VZ]*Cp[VWm, conj[VWm], VZ, VZ][1] - 
    A0[Mass2[VZ]]*(4*Cp[VWm, conj[VWm], VZ, VZ][1] + 
      Cp[VWm, conj[VWm], VZ, VZ][2] + Cp[VWm, conj[VWm], VZ, VZ][3]))/2 + 
  2*rMS*Mass2[VWm]*Cp[VWm, conj[VWm], conj[VWm], VWm][1] - 
  A0[Mass2[VWm]]*(4*Cp[VWm, conj[VWm], conj[VWm], VWm][1] + 
    Cp[VWm, conj[VWm], conj[VWm], VWm][2] + 
    Cp[VWm, conj[VWm], conj[VWm], VWm][3])}
