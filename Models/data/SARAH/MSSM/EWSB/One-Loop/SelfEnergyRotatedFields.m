{4*Cp[USd[{gO1}], conj[USd[{gO2}]], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[USd[{gO1}], conj[USd[{gO2}]], VZ, VZ]*(A0[Mass2[VZ]] - 
    (rMS*Mass2[VZ])/2) - sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*
     Cp[USd[{gO1}], conj[USd[{gO2}]], Ah[{gI1}], Ah[{gI1}]]]/2 - 
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[USd[{gO1}], conj[USd[{gO2}]], 
     conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[USd[{gO1}], conj[USd[{gO2}]], 
      hh[{gI1}], hh[{gI1}]]]/2 - sum[gI1, 1, 3, 
   A0[Mass2[Sv[{gI1}]]]*Cp[USd[{gO1}], conj[USd[{gO2}]], conj[Sv[{gI1}]], 
     Sv[{gI1}]]] - 2*sum[gI1, 1, 3, Mass[Fu[{gI1}]]*
     sum[gI2, 1, 2, B0[p^2, Mass2[Fu[{gI1}]], Mass2[Cha[{gI2}]]]*
       Mass[Cha[{gI2}]]*(conj[Cp[conj[USd[{gO2}]], Fu[{gI1}], Cha[{gI2}]][
           PR]]*Cp[conj[USd[{gO1}]], Fu[{gI1}], Cha[{gI2}]][PL] + 
        conj[Cp[conj[USd[{gO2}]], Fu[{gI1}], Cha[{gI2}]][PL]]*
         Cp[conj[USd[{gO1}]], Fu[{gI1}], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 2, G0[p^2, Mass2[Fu[{gI1}]], Mass2[Cha[{gI2}]]]*
     (conj[Cp[conj[USd[{gO2}]], Fu[{gI1}], Cha[{gI2}]][PL]]*
       Cp[conj[USd[{gO1}]], Fu[{gI1}], Cha[{gI2}]][PL] + 
      conj[Cp[conj[USd[{gO2}]], Fu[{gI1}], Cha[{gI2}]][PR]]*
       Cp[conj[USd[{gO1}]], Fu[{gI1}], Cha[{gI2}]][PR])]] - 
  2*sum[gI1, 1, 3, Mass[Fd[{gI1}]]*sum[gI2, 1, 4, 
      B0[p^2, Mass2[Fd[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI2}]]*
       (conj[Cp[conj[USd[{gO2}]], Fd[{gI1}], Chi[{gI2}]][PR]]*
         Cp[conj[USd[{gO1}]], Fd[{gI1}], Chi[{gI2}]][PL] + 
        conj[Cp[conj[USd[{gO2}]], Fd[{gI1}], Chi[{gI2}]][PL]]*
         Cp[conj[USd[{gO1}]], Fd[{gI1}], Chi[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 4, G0[p^2, Mass2[Fd[{gI1}]], Mass2[Chi[{gI2}]]]*
     (conj[Cp[conj[USd[{gO2}]], Fd[{gI1}], Chi[{gI2}]][PL]]*
       Cp[conj[USd[{gO1}]], Fd[{gI1}], Chi[{gI2}]][PL] + 
      conj[Cp[conj[USd[{gO2}]], Fd[{gI1}], Chi[{gI2}]][PR]]*
       Cp[conj[USd[{gO1}]], Fd[{gI1}], Chi[{gI2}]][PR])]] - 
  C*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[USd[{gO1}], conj[USd[{gO2}]], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[USd[{gO1}], conj[USd[{gO2}]], conj[Se[{gI1}]], 
     Se[{gI1}]]] - C*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[USd[{gO1}], conj[USd[{gO2}]], conj[Su[{gI1}]], Su[{gI1}]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Sd[{gI1}]], Mass2[Ah[{gI2}]]]*
     conj[Cp[conj[USd[{gO2}]], Sd[{gI1}], Ah[{gI2}]]]*
     Cp[conj[USd[{gO1}]], Sd[{gI1}], Ah[{gI2}]]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Sd[{gI1}]], Mass2[hh[{gI2}]]]*
     conj[Cp[conj[USd[{gO2}]], Sd[{gI1}], hh[{gI2}]]]*
     Cp[conj[USd[{gO1}]], Sd[{gI1}], hh[{gI2}]]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Su[{gI1}]], Mass2[Hpm[{gI2}]]]*
     conj[Cp[conj[USd[{gO2}]], Su[{gI1}], Hpm[{gI2}]]]*
     Cp[conj[USd[{gO1}]], Su[{gI1}], Hpm[{gI2}]]]] - 
  (8*Mass[Glu]*sum[gI2, 1, 3, B0[p^2, Mass2[Glu], Mass2[Fd[{gI2}]]]*
      Mass[Fd[{gI2}]]*(conj[Cp[conj[USd[{gO2}]], Glu[{1}], Fd[{gI2}]][PR]]*
        Cp[conj[USd[{gO1}]], Glu[{1}], Fd[{gI2}]][PL] + 
       conj[Cp[conj[USd[{gO2}]], Glu[{1}], Fd[{gI2}]][PL]]*
        Cp[conj[USd[{gO1}]], Glu[{1}], Fd[{gI2}]][PR])])/3 + 
  (4*sum[gI2, 1, 3, G0[p^2, Mass2[Glu], Mass2[Fd[{gI2}]]]*
      (conj[Cp[conj[USd[{gO2}]], Glu[{1}], Fd[{gI2}]][PL]]*
        Cp[conj[USd[{gO1}]], Glu[{1}], Fd[{gI2}]][PL] + 
       conj[Cp[conj[USd[{gO2}]], Glu[{1}], Fd[{gI2}]][PR]]*
        Cp[conj[USd[{gO1}]], Glu[{1}], Fd[{gI2}]][PR])])/3 + 
  (4*sum[gI2, 1, 6, conj[Cp[conj[USd[{gO2}]], VG, Sd[{gI2}]]]*
      Cp[conj[USd[{gO1}]], VG, Sd[{gI2}]]*F0[p^2, Mass2[Sd[{gI2}]], 0]])/3 + 
  sum[gI2, 1, 6, conj[Cp[conj[USd[{gO2}]], VP, Sd[{gI2}]]]*
    Cp[conj[USd[{gO1}]], VP, Sd[{gI2}]]*F0[p^2, Mass2[Sd[{gI2}]], 0]] + 
  sum[gI2, 1, 6, conj[Cp[conj[USd[{gO2}]], VZ, Sd[{gI2}]]]*
    Cp[conj[USd[{gO1}]], VZ, Sd[{gI2}]]*F0[p^2, Mass2[Sd[{gI2}]], 
     Mass2[VZ]]] + sum[gI2, 1, 6, conj[Cp[conj[USd[{gO2}]], VWm, Su[{gI2}]]]*
    Cp[conj[USd[{gO1}]], VWm, Su[{gI2}]]*F0[p^2, Mass2[Su[{gI2}]], 
     Mass2[VWm]]], 4*Cp[USv[{gO1}], conj[USv[{gO2}]], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[USv[{gO1}], conj[USv[{gO2}]], VZ, VZ]*(A0[Mass2[VZ]] - 
    (rMS*Mass2[VZ])/2) - sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*
     Cp[USv[{gO1}], conj[USv[{gO2}]], Ah[{gI1}], Ah[{gI1}]]]/2 - 
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[USv[{gO1}], conj[USv[{gO2}]], 
     conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[USv[{gO1}], conj[USv[{gO2}]], 
      hh[{gI1}], hh[{gI1}]]]/2 - 
  2*sum[gI1, 1, 2, Mass[Cha[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Cha[{gI1}]], Mass2[Fe[{gI2}]]]*Mass[Fe[{gI2}]]*
       (conj[Cp[conj[USv[{gO2}]], bar[Cha[{gI1}]], Fe[{gI2}]][PR]]*
         Cp[conj[USv[{gO1}]], bar[Cha[{gI1}]], Fe[{gI2}]][PL] + 
        conj[Cp[conj[USv[{gO2}]], bar[Cha[{gI1}]], Fe[{gI2}]][PL]]*
         Cp[conj[USv[{gO1}]], bar[Cha[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 3, G0[p^2, Mass2[Cha[{gI1}]], Mass2[Fe[{gI2}]]]*
     (conj[Cp[conj[USv[{gO2}]], bar[Cha[{gI1}]], Fe[{gI2}]][PL]]*
       Cp[conj[USv[{gO1}]], bar[Cha[{gI1}]], Fe[{gI2}]][PL] + 
      conj[Cp[conj[USv[{gO2}]], bar[Cha[{gI1}]], Fe[{gI2}]][PR]]*
       Cp[conj[USv[{gO1}]], bar[Cha[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 6, B0[p^2, Mass2[Hpm[{gI1}]], Mass2[Se[{gI2}]]]*
     conj[Cp[conj[USv[{gO2}]], conj[Hpm[{gI1}]], Se[{gI2}]]]*
     Cp[conj[USv[{gO1}]], conj[Hpm[{gI1}]], Se[{gI2}]]]] - 
  sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*Cp[USv[{gO1}], conj[USv[{gO2}]], 
     conj[Sv[{gI1}]], Sv[{gI1}]]] + sum[gI1, 1, 3, 
   sum[gI2, 1, 2, B0[p^2, Mass2[Sv[{gI1}]], Mass2[hh[{gI2}]]]*
     conj[Cp[conj[USv[{gO2}]], Sv[{gI1}], hh[{gI2}]]]*
     Cp[conj[USv[{gO1}]], Sv[{gI1}], hh[{gI2}]]]] - 
  2*sum[gI1, 1, 3, Mass[Fv[{gI1}]]*sum[gI2, 1, 4, 
      B0[p^2, Mass2[Fv[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI2}]]*
       (conj[Cp[conj[USv[{gO2}]], Fv[{gI1}], Chi[{gI2}]][PR]]*
         Cp[conj[USv[{gO1}]], Fv[{gI1}], Chi[{gI2}]][PL] + 
        conj[Cp[conj[USv[{gO2}]], Fv[{gI1}], Chi[{gI2}]][PL]]*
         Cp[conj[USv[{gO1}]], Fv[{gI1}], Chi[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 4, G0[p^2, Mass2[Fv[{gI1}]], Mass2[Chi[{gI2}]]]*
     (conj[Cp[conj[USv[{gO2}]], Fv[{gI1}], Chi[{gI2}]][PL]]*
       Cp[conj[USv[{gO1}]], Fv[{gI1}], Chi[{gI2}]][PL] + 
      conj[Cp[conj[USv[{gO2}]], Fv[{gI1}], Chi[{gI2}]][PR]]*
       Cp[conj[USv[{gO1}]], Fv[{gI1}], Chi[{gI2}]][PR])]] - 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[USv[{gO1}], conj[USv[{gO2}]], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[USv[{gO1}], conj[USv[{gO2}]], conj[Se[{gI1}]], 
     Se[{gI1}]]] - 3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[USv[{gO1}], conj[USv[{gO2}]], conj[Su[{gI1}]], Su[{gI1}]]] + 
  sum[gI2, 1, 3, conj[Cp[conj[USv[{gO2}]], VZ, Sv[{gI2}]]]*
    Cp[conj[USv[{gO1}]], VZ, Sv[{gI2}]]*F0[p^2, Mass2[Sv[{gI2}]], 
     Mass2[VZ]]] + sum[gI2, 1, 6, 
   conj[Cp[conj[USv[{gO2}]], conj[VWm], Se[{gI2}]]]*
    Cp[conj[USv[{gO1}]], conj[VWm], Se[{gI2}]]*F0[p^2, Mass2[Se[{gI2}]], 
     Mass2[VWm]]], 4*Cp[USu[{gO1}], conj[USu[{gO2}]], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[USu[{gO1}], conj[USu[{gO2}]], VZ, VZ]*(A0[Mass2[VZ]] - 
    (rMS*Mass2[VZ])/2) - sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*
     Cp[USu[{gO1}], conj[USu[{gO2}]], Ah[{gI1}], Ah[{gI1}]]]/2 - 
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[USu[{gO1}], conj[USu[{gO2}]], 
     conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[USu[{gO1}], conj[USu[{gO2}]], 
      hh[{gI1}], hh[{gI1}]]]/2 - 
  2*sum[gI1, 1, 2, Mass[Cha[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Cha[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI2}]]*
       (conj[Cp[conj[USu[{gO2}]], bar[Cha[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[conj[USu[{gO1}]], bar[Cha[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[conj[USu[{gO2}]], bar[Cha[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[conj[USu[{gO1}]], bar[Cha[{gI1}]], Fd[{gI2}]][PR])]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 3, G0[p^2, Mass2[Cha[{gI1}]], Mass2[Fd[{gI2}]]]*
     (conj[Cp[conj[USu[{gO2}]], bar[Cha[{gI1}]], Fd[{gI2}]][PL]]*
       Cp[conj[USu[{gO1}]], bar[Cha[{gI1}]], Fd[{gI2}]][PL] + 
      conj[Cp[conj[USu[{gO2}]], bar[Cha[{gI1}]], Fd[{gI2}]][PR]]*
       Cp[conj[USu[{gO1}]], bar[Cha[{gI1}]], Fd[{gI2}]][PR])]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 6, B0[p^2, Mass2[Hpm[{gI1}]], Mass2[Sd[{gI2}]]]*
     conj[Cp[conj[USu[{gO2}]], conj[Hpm[{gI1}]], Sd[{gI2}]]]*
     Cp[conj[USu[{gO1}]], conj[Hpm[{gI1}]], Sd[{gI2}]]]] - 
  sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*Cp[USu[{gO1}], conj[USu[{gO2}]], 
     conj[Sv[{gI1}]], Sv[{gI1}]]] - 
  2*sum[gI1, 1, 3, Mass[Fu[{gI1}]]*sum[gI2, 1, 4, 
      B0[p^2, Mass2[Fu[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI2}]]*
       (conj[Cp[conj[USu[{gO2}]], Fu[{gI1}], Chi[{gI2}]][PR]]*
         Cp[conj[USu[{gO1}]], Fu[{gI1}], Chi[{gI2}]][PL] + 
        conj[Cp[conj[USu[{gO2}]], Fu[{gI1}], Chi[{gI2}]][PL]]*
         Cp[conj[USu[{gO1}]], Fu[{gI1}], Chi[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 4, G0[p^2, Mass2[Fu[{gI1}]], Mass2[Chi[{gI2}]]]*
     (conj[Cp[conj[USu[{gO2}]], Fu[{gI1}], Chi[{gI2}]][PL]]*
       Cp[conj[USu[{gO1}]], Fu[{gI1}], Chi[{gI2}]][PL] + 
      conj[Cp[conj[USu[{gO2}]], Fu[{gI1}], Chi[{gI2}]][PR]]*
       Cp[conj[USu[{gO1}]], Fu[{gI1}], Chi[{gI2}]][PR])]] - 
  C*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[USu[{gO1}], conj[USu[{gO2}]], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[USu[{gO1}], conj[USu[{gO2}]], conj[Se[{gI1}]], 
     Se[{gI1}]]] - C*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[USu[{gO1}], conj[USu[{gO2}]], conj[Su[{gI1}]], Su[{gI1}]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Su[{gI1}]], Mass2[Ah[{gI2}]]]*
     conj[Cp[conj[USu[{gO2}]], Su[{gI1}], Ah[{gI2}]]]*
     Cp[conj[USu[{gO1}]], Su[{gI1}], Ah[{gI2}]]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Su[{gI1}]], Mass2[hh[{gI2}]]]*
     conj[Cp[conj[USu[{gO2}]], Su[{gI1}], hh[{gI2}]]]*
     Cp[conj[USu[{gO1}]], Su[{gI1}], hh[{gI2}]]]] - 
  (8*Mass[Glu]*sum[gI2, 1, 3, B0[p^2, Mass2[Glu], Mass2[Fu[{gI2}]]]*
      Mass[Fu[{gI2}]]*(conj[Cp[conj[USu[{gO2}]], Glu[{1}], Fu[{gI2}]][PR]]*
        Cp[conj[USu[{gO1}]], Glu[{1}], Fu[{gI2}]][PL] + 
       conj[Cp[conj[USu[{gO2}]], Glu[{1}], Fu[{gI2}]][PL]]*
        Cp[conj[USu[{gO1}]], Glu[{1}], Fu[{gI2}]][PR])])/3 + 
  (4*sum[gI2, 1, 3, G0[p^2, Mass2[Glu], Mass2[Fu[{gI2}]]]*
      (conj[Cp[conj[USu[{gO2}]], Glu[{1}], Fu[{gI2}]][PL]]*
        Cp[conj[USu[{gO1}]], Glu[{1}], Fu[{gI2}]][PL] + 
       conj[Cp[conj[USu[{gO2}]], Glu[{1}], Fu[{gI2}]][PR]]*
        Cp[conj[USu[{gO1}]], Glu[{1}], Fu[{gI2}]][PR])])/3 + 
  sum[gI2, 1, 6, conj[Cp[conj[USu[{gO2}]], conj[VWm], Sd[{gI2}]]]*
    Cp[conj[USu[{gO1}]], conj[VWm], Sd[{gI2}]]*F0[p^2, Mass2[Sd[{gI2}]], 
     Mass2[VWm]]] + 
  (4*sum[gI2, 1, 6, conj[Cp[conj[USu[{gO2}]], VG, Su[{gI2}]]]*
      Cp[conj[USu[{gO1}]], VG, Su[{gI2}]]*F0[p^2, Mass2[Su[{gI2}]], 0]])/3 + 
  sum[gI2, 1, 6, conj[Cp[conj[USu[{gO2}]], VP, Su[{gI2}]]]*
    Cp[conj[USu[{gO1}]], VP, Su[{gI2}]]*F0[p^2, Mass2[Su[{gI2}]], 0]] + 
  sum[gI2, 1, 6, conj[Cp[conj[USu[{gO2}]], VZ, Su[{gI2}]]]*
    Cp[conj[USu[{gO1}]], VZ, Su[{gI2}]]*F0[p^2, Mass2[Su[{gI2}]], 
     Mass2[VZ]]], 4*Cp[USe[{gO1}], conj[USe[{gO2}]], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[USe[{gO1}], conj[USe[{gO2}]], VZ, VZ]*(A0[Mass2[VZ]] - 
    (rMS*Mass2[VZ])/2) - sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*
     Cp[USe[{gO1}], conj[USe[{gO2}]], Ah[{gI1}], Ah[{gI1}]]]/2 - 
  sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*Cp[USe[{gO1}], conj[USe[{gO2}]], 
     conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[USe[{gO1}], conj[USe[{gO2}]], 
      hh[{gI1}], hh[{gI1}]]]/2 - sum[gI1, 1, 3, 
   A0[Mass2[Sv[{gI1}]]]*Cp[USe[{gO1}], conj[USe[{gO2}]], conj[Sv[{gI1}]], 
     Sv[{gI1}]]] + sum[gI1, 1, 3, sum[gI2, 1, 2, 
    B0[p^2, Mass2[Sv[{gI1}]], Mass2[Hpm[{gI2}]]]*
     conj[Cp[conj[USe[{gO2}]], Sv[{gI1}], Hpm[{gI2}]]]*
     Cp[conj[USe[{gO1}]], Sv[{gI1}], Hpm[{gI2}]]]] - 
  2*sum[gI1, 1, 3, Mass[Fv[{gI1}]]*sum[gI2, 1, 2, 
      B0[p^2, Mass2[Fv[{gI1}]], Mass2[Cha[{gI2}]]]*Mass[Cha[{gI2}]]*
       (conj[Cp[conj[USe[{gO2}]], Fv[{gI1}], Cha[{gI2}]][PR]]*
         Cp[conj[USe[{gO1}]], Fv[{gI1}], Cha[{gI2}]][PL] + 
        conj[Cp[conj[USe[{gO2}]], Fv[{gI1}], Cha[{gI2}]][PL]]*
         Cp[conj[USe[{gO1}]], Fv[{gI1}], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 2, G0[p^2, Mass2[Fv[{gI1}]], Mass2[Cha[{gI2}]]]*
     (conj[Cp[conj[USe[{gO2}]], Fv[{gI1}], Cha[{gI2}]][PL]]*
       Cp[conj[USe[{gO1}]], Fv[{gI1}], Cha[{gI2}]][PL] + 
      conj[Cp[conj[USe[{gO2}]], Fv[{gI1}], Cha[{gI2}]][PR]]*
       Cp[conj[USe[{gO1}]], Fv[{gI1}], Cha[{gI2}]][PR])]] - 
  2*sum[gI1, 1, 3, Mass[Fe[{gI1}]]*sum[gI2, 1, 4, 
      B0[p^2, Mass2[Fe[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI2}]]*
       (conj[Cp[conj[USe[{gO2}]], Fe[{gI1}], Chi[{gI2}]][PR]]*
         Cp[conj[USe[{gO1}]], Fe[{gI1}], Chi[{gI2}]][PL] + 
        conj[Cp[conj[USe[{gO2}]], Fe[{gI1}], Chi[{gI2}]][PL]]*
         Cp[conj[USe[{gO1}]], Fe[{gI1}], Chi[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 4, G0[p^2, Mass2[Fe[{gI1}]], Mass2[Chi[{gI2}]]]*
     (conj[Cp[conj[USe[{gO2}]], Fe[{gI1}], Chi[{gI2}]][PL]]*
       Cp[conj[USe[{gO1}]], Fe[{gI1}], Chi[{gI2}]][PL] + 
      conj[Cp[conj[USe[{gO2}]], Fe[{gI1}], Chi[{gI2}]][PR]]*
       Cp[conj[USe[{gO1}]], Fe[{gI1}], Chi[{gI2}]][PR])]] - 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[USe[{gO1}], conj[USe[{gO2}]], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[USe[{gO1}], conj[USe[{gO2}]], conj[Se[{gI1}]], 
     Se[{gI1}]]] - 3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[USe[{gO1}], conj[USe[{gO2}]], conj[Su[{gI1}]], Su[{gI1}]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Se[{gI1}]], Mass2[Ah[{gI2}]]]*
     conj[Cp[conj[USe[{gO2}]], Se[{gI1}], Ah[{gI2}]]]*
     Cp[conj[USe[{gO1}]], Se[{gI1}], Ah[{gI2}]]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Se[{gI1}]], Mass2[hh[{gI2}]]]*
     conj[Cp[conj[USe[{gO2}]], Se[{gI1}], hh[{gI2}]]]*
     Cp[conj[USe[{gO1}]], Se[{gI1}], hh[{gI2}]]]] + 
  sum[gI2, 1, 3, conj[Cp[conj[USe[{gO2}]], VWm, Sv[{gI2}]]]*
    Cp[conj[USe[{gO1}]], VWm, Sv[{gI2}]]*F0[p^2, Mass2[Sv[{gI2}]], 
     Mass2[VWm]]] + sum[gI2, 1, 6, conj[Cp[conj[USe[{gO2}]], VP, Se[{gI2}]]]*
    Cp[conj[USe[{gO1}]], VP, Se[{gI2}]]*F0[p^2, Mass2[Se[{gI2}]], 0]] + 
  sum[gI2, 1, 6, conj[Cp[conj[USe[{gO2}]], VZ, Se[{gI2}]]]*
    Cp[conj[USe[{gO1}]], VZ, Se[{gI2}]]*F0[p^2, Mass2[Se[{gI2}]], 
     Mass2[VZ]]], 2*(-rMS/2 + B0[p^2, Mass2[VZ], Mass2[VZ]])*
   conj[Cp[Uhh[{gO2}], VZ, VZ]]*Cp[Uhh[{gO1}], VZ, VZ] + 
  4*(-rMS/2 + B0[p^2, Mass2[VWm], Mass2[VWm]])*
   conj[Cp[Uhh[{gO2}], conj[VWm], VWm]]*Cp[Uhh[{gO1}], conj[VWm], VWm] - 
  B0[p^2, Mass2[gWm], Mass2[gWm]]*Cp[Uhh[{gO1}], bar[gWm], gWm]*
   Cp[Uhh[{gO2}], bar[gWm], gWm] - B0[p^2, Mass2[gWmC], Mass2[gWmC]]*
   Cp[Uhh[{gO1}], bar[gWmC], gWmC]*Cp[Uhh[{gO2}], bar[gWmC], gWmC] - 
  B0[p^2, Mass2[gZ], Mass2[gZ]]*Cp[Uhh[{gO1}], bar[gZ], gZ]*
   Cp[Uhh[{gO2}], bar[gZ], gZ] + 4*Cp[Uhh[{gO1}], Uhh[{gO2}], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[Uhh[{gO1}], Uhh[{gO2}], VZ, VZ]*(A0[Mass2[VZ]] - (rMS*Mass2[VZ])/2) - 
  sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*Cp[Uhh[{gO1}], Uhh[{gO2}], Ah[{gI1}], 
      Ah[{gI1}]]]/2 - sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*
    Cp[Uhh[{gO1}], Uhh[{gO2}], conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[Uhh[{gO1}], Uhh[{gO2}], hh[{gI1}], 
      hh[{gI1}]]]/2 + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, B0[p^2, Mass2[Ah[{gI1}]], Mass2[Ah[{gI2}]]]*
      conj[Cp[Uhh[{gO2}], Ah[{gI1}], Ah[{gI2}]]]*Cp[Uhh[{gO1}], Ah[{gI1}], 
       Ah[{gI2}]]]]/2 + sum[gI1, 1, 2, sum[gI2, 1, 2, 
    B0[p^2, Mass2[Hpm[{gI1}]], Mass2[Hpm[{gI2}]]]*
     conj[Cp[Uhh[{gO2}], conj[Hpm[{gI1}]], Hpm[{gI2}]]]*
     Cp[Uhh[{gO1}], conj[Hpm[{gI1}]], Hpm[{gI2}]]]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, B0[p^2, Mass2[hh[{gI1}]], Mass2[hh[{gI2}]]]*
      conj[Cp[Uhh[{gO2}], hh[{gI1}], hh[{gI2}]]]*Cp[Uhh[{gO1}], hh[{gI1}], 
       hh[{gI2}]]]]/2 - 2*sum[gI1, 1, 2, Mass[Cha[{gI1}]]*
     sum[gI2, 1, 2, B0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
       Mass[Cha[{gI2}]]*(conj[Cp[Uhh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][
           PR]]*Cp[Uhh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
        conj[Cp[Uhh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
         Cp[Uhh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, G0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
     (conj[Cp[Uhh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
       Cp[Uhh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
      conj[Cp[Uhh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][PR]]*
       Cp[Uhh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] - 
  sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*Cp[Uhh[{gO1}], Uhh[{gO2}], 
     conj[Sv[{gI1}]], Sv[{gI1}]]] + sum[gI1, 1, 3, 
   sum[gI2, 1, 3, B0[p^2, Mass2[Sv[{gI1}]], Mass2[Sv[{gI2}]]]*
     conj[Cp[Uhh[{gO2}], conj[Sv[{gI1}]], Sv[{gI2}]]]*
     Cp[Uhh[{gO1}], conj[Sv[{gI1}]], Sv[{gI2}]]]] - 
  6*sum[gI1, 1, 3, Mass[Fd[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI2}]]*
       (conj[Cp[Uhh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[Uhh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[Uhh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[Uhh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*
      (conj[Cp[Uhh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
        Cp[Uhh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
       conj[Cp[Uhh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
        Cp[Uhh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PR])]] - 
  2*sum[gI1, 1, 3, Mass[Fe[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*Mass[Fe[{gI2}]]*
       (conj[Cp[Uhh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PR]]*
         Cp[Uhh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PL] + 
        conj[Cp[Uhh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
         Cp[Uhh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*
     (conj[Cp[Uhh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
       Cp[Uhh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PL] + 
      conj[Cp[Uhh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PR]]*
       Cp[Uhh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PR])]] - 
  6*sum[gI1, 1, 3, Mass[Fu[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*Mass[Fu[{gI2}]]*
       (conj[Cp[Uhh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
         Cp[Uhh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
        conj[Cp[Uhh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[Uhh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*
      (conj[Cp[Uhh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
        Cp[Uhh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
       conj[Cp[Uhh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
        Cp[Uhh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PR])]] - 
  sum[gI1, 1, 4, Mass[Chi[{gI1}]]*sum[gI2, 1, 4, 
     B0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI2}]]*
      (conj[Cp[Uhh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PR]]*
        Cp[Uhh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PL] + 
       conj[Cp[Uhh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PL]]*
        Cp[Uhh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PR])]] + 
  sum[gI1, 1, 4, sum[gI2, 1, 4, G0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*
      (conj[Cp[Uhh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PL]]*
        Cp[Uhh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PL] + 
       conj[Cp[Uhh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PR]]*
        Cp[Uhh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PR])]]/2 - 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[Uhh[{gO1}], Uhh[{gO2}], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[Uhh[{gO1}], Uhh[{gO2}], conj[Se[{gI1}]], 
     Se[{gI1}]]] - 3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[Uhh[{gO1}], Uhh[{gO2}], conj[Su[{gI1}]], Su[{gI1}]]] + 
  3*sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Sd[{gI1}]], Mass2[Sd[{gI2}]]]*
      conj[Cp[Uhh[{gO2}], conj[Sd[{gI1}]], Sd[{gI2}]]]*
      Cp[Uhh[{gO1}], conj[Sd[{gI1}]], Sd[{gI2}]]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Se[{gI1}]], Mass2[Se[{gI2}]]]*
     conj[Cp[Uhh[{gO2}], conj[Se[{gI1}]], Se[{gI2}]]]*
     Cp[Uhh[{gO1}], conj[Se[{gI1}]], Se[{gI2}]]]] + 
  3*sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Su[{gI1}]], Mass2[Su[{gI2}]]]*
      conj[Cp[Uhh[{gO2}], conj[Su[{gI1}]], Su[{gI2}]]]*
      Cp[Uhh[{gO1}], conj[Su[{gI1}]], Su[{gI2}]]]] + 
  sum[gI2, 1, 2, conj[Cp[Uhh[{gO2}], VZ, Ah[{gI2}]]]*
    Cp[Uhh[{gO1}], VZ, Ah[{gI2}]]*F0[p^2, Mass2[Ah[{gI2}]], Mass2[VZ]]] + 
  2*sum[gI2, 1, 2, conj[Cp[Uhh[{gO2}], conj[VWm], Hpm[{gI2}]]]*
     Cp[Uhh[{gO1}], conj[VWm], Hpm[{gI2}]]*F0[p^2, Mass2[Hpm[{gI2}]], 
      Mass2[VWm]]], -(B0[p^2, Mass2[gWm], Mass2[gWm]]*
    Cp[UAh[{gO1}], bar[gWm], gWm]*Cp[UAh[{gO2}], bar[gWm], gWm]) - 
  B0[p^2, Mass2[gWmC], Mass2[gWmC]]*Cp[UAh[{gO1}], bar[gWmC], gWmC]*
   Cp[UAh[{gO2}], bar[gWmC], gWmC] + 
  4*Cp[UAh[{gO1}], UAh[{gO2}], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[UAh[{gO1}], UAh[{gO2}], VZ, VZ]*(A0[Mass2[VZ]] - (rMS*Mass2[VZ])/2) - 
  sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*Cp[UAh[{gO1}], UAh[{gO2}], Ah[{gI1}], 
      Ah[{gI1}]]]/2 - sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*
    Cp[UAh[{gO1}], UAh[{gO2}], conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[UAh[{gO1}], UAh[{gO2}], hh[{gI1}], 
      hh[{gI1}]]]/2 + sum[gI1, 1, 2, sum[gI2, 1, 2, 
    B0[p^2, Mass2[Hpm[{gI1}]], Mass2[Hpm[{gI2}]]]*
     conj[Cp[UAh[{gO2}], conj[Hpm[{gI1}]], Hpm[{gI2}]]]*
     Cp[UAh[{gO1}], conj[Hpm[{gI1}]], Hpm[{gI2}]]]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, B0[p^2, Mass2[hh[{gI1}]], Mass2[Ah[{gI2}]]]*
     conj[Cp[UAh[{gO2}], hh[{gI1}], Ah[{gI2}]]]*Cp[UAh[{gO1}], hh[{gI1}], 
      Ah[{gI2}]]]] - 2*sum[gI1, 1, 2, Mass[Cha[{gI1}]]*
     sum[gI2, 1, 2, B0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
       Mass[Cha[{gI2}]]*(conj[Cp[UAh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][
           PR]]*Cp[UAh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
        conj[Cp[UAh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
         Cp[UAh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, G0[p^2, Mass2[Cha[{gI1}]], Mass2[Cha[{gI2}]]]*
     (conj[Cp[UAh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][PL]]*
       Cp[UAh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PL] + 
      conj[Cp[UAh[{gO2}], bar[Cha[{gI1}]], Cha[{gI2}]][PR]]*
       Cp[UAh[{gO1}], bar[Cha[{gI1}]], Cha[{gI2}]][PR])]] - 
  sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*Cp[UAh[{gO1}], UAh[{gO2}], 
     conj[Sv[{gI1}]], Sv[{gI1}]]] - 
  6*sum[gI1, 1, 3, Mass[Fd[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI2}]]*
       (conj[Cp[UAh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[UAh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[UAh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[UAh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fd[{gI1}]], Mass2[Fd[{gI2}]]]*
      (conj[Cp[UAh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PL]]*
        Cp[UAh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PL] + 
       conj[Cp[UAh[{gO2}], bar[Fd[{gI1}]], Fd[{gI2}]][PR]]*
        Cp[UAh[{gO1}], bar[Fd[{gI1}]], Fd[{gI2}]][PR])]] - 
  2*sum[gI1, 1, 3, Mass[Fe[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*Mass[Fe[{gI2}]]*
       (conj[Cp[UAh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PR]]*
         Cp[UAh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PL] + 
        conj[Cp[UAh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
         Cp[UAh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fe[{gI1}]], Mass2[Fe[{gI2}]]]*
     (conj[Cp[UAh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PL]]*
       Cp[UAh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PL] + 
      conj[Cp[UAh[{gO2}], bar[Fe[{gI1}]], Fe[{gI2}]][PR]]*
       Cp[UAh[{gO1}], bar[Fe[{gI1}]], Fe[{gI2}]][PR])]] - 
  6*sum[gI1, 1, 3, Mass[Fu[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*Mass[Fu[{gI2}]]*
       (conj[Cp[UAh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
         Cp[UAh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
        conj[Cp[UAh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
         Cp[UAh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fu[{gI1}]], Mass2[Fu[{gI2}]]]*
      (conj[Cp[UAh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PL]]*
        Cp[UAh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PL] + 
       conj[Cp[UAh[{gO2}], bar[Fu[{gI1}]], Fu[{gI2}]][PR]]*
        Cp[UAh[{gO1}], bar[Fu[{gI1}]], Fu[{gI2}]][PR])]] - 
  sum[gI1, 1, 4, Mass[Chi[{gI1}]]*sum[gI2, 1, 4, 
     B0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*Mass[Chi[{gI2}]]*
      (conj[Cp[UAh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PR]]*
        Cp[UAh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PL] + 
       conj[Cp[UAh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PL]]*
        Cp[UAh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PR])]] + 
  sum[gI1, 1, 4, sum[gI2, 1, 4, G0[p^2, Mass2[Chi[{gI1}]], Mass2[Chi[{gI2}]]]*
      (conj[Cp[UAh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PL]]*
        Cp[UAh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PL] + 
       conj[Cp[UAh[{gO2}], Chi[{gI1}], Chi[{gI2}]][PR]]*
        Cp[UAh[{gO1}], Chi[{gI1}], Chi[{gI2}]][PR])]]/2 - 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[UAh[{gO1}], UAh[{gO2}], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[UAh[{gO1}], UAh[{gO2}], conj[Se[{gI1}]], 
     Se[{gI1}]]] - 3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[UAh[{gO1}], UAh[{gO2}], conj[Su[{gI1}]], Su[{gI1}]]] + 
  3*sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Sd[{gI1}]], Mass2[Sd[{gI2}]]]*
      conj[Cp[UAh[{gO2}], conj[Sd[{gI1}]], Sd[{gI2}]]]*
      Cp[UAh[{gO1}], conj[Sd[{gI1}]], Sd[{gI2}]]]] + 
  sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Se[{gI1}]], Mass2[Se[{gI2}]]]*
     conj[Cp[UAh[{gO2}], conj[Se[{gI1}]], Se[{gI2}]]]*
     Cp[UAh[{gO1}], conj[Se[{gI1}]], Se[{gI2}]]]] + 
  3*sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Su[{gI1}]], Mass2[Su[{gI2}]]]*
      conj[Cp[UAh[{gO2}], conj[Su[{gI1}]], Su[{gI2}]]]*
      Cp[UAh[{gO1}], conj[Su[{gI1}]], Su[{gI2}]]]] + 
  sum[gI2, 1, 2, conj[Cp[UAh[{gO2}], VZ, hh[{gI2}]]]*
    Cp[UAh[{gO1}], VZ, hh[{gI2}]]*F0[p^2, Mass2[hh[{gI2}]], Mass2[VZ]]] + 
  2*sum[gI2, 1, 2, conj[Cp[UAh[{gO2}], conj[VWm], Hpm[{gI2}]]]*
     Cp[UAh[{gO1}], conj[VWm], Hpm[{gI2}]]*F0[p^2, Mass2[Hpm[{gI2}]], 
      Mass2[VWm]]], 4*(-rMS/2 + B0[p^2, 0, Mass2[VWm]])*
   conj[Cp[conj[UHpm[{gO2}]], VWm, VP]]*Cp[conj[UHpm[{gO1}]], VWm, VP] + 
  4*(-rMS/2 + B0[p^2, Mass2[VWm], Mass2[VZ]])*
   conj[Cp[conj[UHpm[{gO2}]], VZ, VWm]]*Cp[conj[UHpm[{gO1}]], VZ, VWm] - 
  B0[p^2, Mass2[gZ], Mass2[gWmC]]*Cp[conj[UHpm[{gO1}]], bar[gWmC], gZ]*
   Cp[UHpm[{gO2}], gWmC, bar[gZ]] - B0[p^2, Mass2[gWm], Mass2[gZ]]*
   Cp[conj[UHpm[{gO1}]], bar[gZ], gWm]*Cp[UHpm[{gO2}], gZ, bar[gWm]] + 
  4*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], conj[VWm], VWm]*
   (A0[Mass2[VWm]] - (rMS*Mass2[VWm])/2) + 
  2*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], VZ, VZ]*
   (A0[Mass2[VZ]] - (rMS*Mass2[VZ])/2) - 
  sum[gI1, 1, 2, A0[Mass2[Ah[{gI1}]]]*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], 
      Ah[{gI1}], Ah[{gI1}]]]/2 - sum[gI1, 1, 2, A0[Mass2[Hpm[{gI1}]]]*
    Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], conj[Hpm[{gI1}]], Hpm[{gI1}]]] - 
  sum[gI1, 1, 2, A0[Mass2[hh[{gI1}]]]*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], 
      hh[{gI1}], hh[{gI1}]]]/2 + sum[gI1, 1, 2, 
   sum[gI2, 1, 2, B0[p^2, Mass2[Hpm[{gI1}]], Mass2[Ah[{gI2}]]]*
     conj[Cp[conj[UHpm[{gO2}]], Hpm[{gI1}], Ah[{gI2}]]]*
     Cp[conj[UHpm[{gO1}]], Hpm[{gI1}], Ah[{gI2}]]]] + 
  sum[gI1, 1, 2, sum[gI2, 1, 2, B0[p^2, Mass2[Hpm[{gI1}]], Mass2[hh[{gI2}]]]*
     conj[Cp[conj[UHpm[{gO2}]], Hpm[{gI1}], hh[{gI2}]]]*
     Cp[conj[UHpm[{gO1}]], Hpm[{gI1}], hh[{gI2}]]]] - 
  sum[gI1, 1, 3, A0[Mass2[Sv[{gI1}]]]*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], 
     conj[Sv[{gI1}]], Sv[{gI1}]]] - 
  6*sum[gI1, 1, 3, Mass[Fu[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fu[{gI1}]], Mass2[Fd[{gI2}]]]*Mass[Fd[{gI2}]]*
       (conj[Cp[conj[UHpm[{gO2}]], bar[Fu[{gI1}]], Fd[{gI2}]][PR]]*
         Cp[conj[UHpm[{gO1}]], bar[Fu[{gI1}]], Fd[{gI2}]][PL] + 
        conj[Cp[conj[UHpm[{gO2}]], bar[Fu[{gI1}]], Fd[{gI2}]][PL]]*
         Cp[conj[UHpm[{gO1}]], bar[Fu[{gI1}]], Fd[{gI2}]][PR])]] + 
  3*sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fu[{gI1}]], Mass2[Fd[{gI2}]]]*
      (conj[Cp[conj[UHpm[{gO2}]], bar[Fu[{gI1}]], Fd[{gI2}]][PL]]*
        Cp[conj[UHpm[{gO1}]], bar[Fu[{gI1}]], Fd[{gI2}]][PL] + 
       conj[Cp[conj[UHpm[{gO2}]], bar[Fu[{gI1}]], Fd[{gI2}]][PR]]*
        Cp[conj[UHpm[{gO1}]], bar[Fu[{gI1}]], Fd[{gI2}]][PR])]] - 
  2*sum[gI1, 1, 3, Mass[Fv[{gI1}]]*sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fv[{gI1}]], Mass2[Fe[{gI2}]]]*Mass[Fe[{gI2}]]*
       (conj[Cp[conj[UHpm[{gO2}]], bar[Fv[{gI1}]], Fe[{gI2}]][PR]]*
         Cp[conj[UHpm[{gO1}]], bar[Fv[{gI1}]], Fe[{gI2}]][PL] + 
        conj[Cp[conj[UHpm[{gO2}]], bar[Fv[{gI1}]], Fe[{gI2}]][PL]]*
         Cp[conj[UHpm[{gO1}]], bar[Fv[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 3, G0[p^2, Mass2[Fv[{gI1}]], Mass2[Fe[{gI2}]]]*
     (conj[Cp[conj[UHpm[{gO2}]], bar[Fv[{gI1}]], Fe[{gI2}]][PL]]*
       Cp[conj[UHpm[{gO1}]], bar[Fv[{gI1}]], Fe[{gI2}]][PL] + 
      conj[Cp[conj[UHpm[{gO2}]], bar[Fv[{gI1}]], Fe[{gI2}]][PR]]*
       Cp[conj[UHpm[{gO1}]], bar[Fv[{gI1}]], Fe[{gI2}]][PR])]] + 
  sum[gI1, 1, 3, sum[gI2, 1, 6, B0[p^2, Mass2[Sv[{gI1}]], Mass2[Se[{gI2}]]]*
     conj[Cp[conj[UHpm[{gO2}]], conj[Sv[{gI1}]], Se[{gI2}]]]*
     Cp[conj[UHpm[{gO1}]], conj[Sv[{gI1}]], Se[{gI2}]]]] - 
  2*sum[gI1, 1, 4, Mass[Chi[{gI1}]]*sum[gI2, 1, 2, 
      B0[p^2, Mass2[Chi[{gI1}]], Mass2[Cha[{gI2}]]]*Mass[Cha[{gI2}]]*
       (conj[Cp[conj[UHpm[{gO2}]], Chi[{gI1}], Cha[{gI2}]][PR]]*
         Cp[conj[UHpm[{gO1}]], Chi[{gI1}], Cha[{gI2}]][PL] + 
        conj[Cp[conj[UHpm[{gO2}]], Chi[{gI1}], Cha[{gI2}]][PL]]*
         Cp[conj[UHpm[{gO1}]], Chi[{gI1}], Cha[{gI2}]][PR])]] + 
  sum[gI1, 1, 4, sum[gI2, 1, 2, G0[p^2, Mass2[Chi[{gI1}]], Mass2[Cha[{gI2}]]]*
     (conj[Cp[conj[UHpm[{gO2}]], Chi[{gI1}], Cha[{gI2}]][PL]]*
       Cp[conj[UHpm[{gO1}]], Chi[{gI1}], Cha[{gI2}]][PL] + 
      conj[Cp[conj[UHpm[{gO2}]], Chi[{gI1}], Cha[{gI2}]][PR]]*
       Cp[conj[UHpm[{gO1}]], Chi[{gI1}], Cha[{gI2}]][PR])]] - 
  3*sum[gI1, 1, 6, A0[Mass2[Sd[{gI1}]]]*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], 
      conj[Sd[{gI1}]], Sd[{gI1}]]] - sum[gI1, 1, 6, 
   A0[Mass2[Se[{gI1}]]]*Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], conj[Se[{gI1}]], 
     Se[{gI1}]]] - 3*sum[gI1, 1, 6, A0[Mass2[Su[{gI1}]]]*
     Cp[UHpm[{gO1}], conj[UHpm[{gO2}]], conj[Su[{gI1}]], Su[{gI1}]]] + 
  3*sum[gI1, 1, 6, sum[gI2, 1, 6, B0[p^2, Mass2[Su[{gI1}]], Mass2[Sd[{gI2}]]]*
      conj[Cp[conj[UHpm[{gO2}]], conj[Su[{gI1}]], Sd[{gI2}]]]*
      Cp[conj[UHpm[{gO1}]], conj[Su[{gI1}]], Sd[{gI2}]]]] + 
  sum[gI2, 1, 2, conj[Cp[conj[UHpm[{gO2}]], VWm, Ah[{gI2}]]]*
    Cp[conj[UHpm[{gO1}]], VWm, Ah[{gI2}]]*F0[p^2, Mass2[Ah[{gI2}]], 
     Mass2[VWm]]] + sum[gI2, 1, 2, 
   conj[Cp[conj[UHpm[{gO2}]], VWm, hh[{gI2}]]]*Cp[conj[UHpm[{gO1}]], VWm, 
     hh[{gI2}]]*F0[p^2, Mass2[hh[{gI2}]], Mass2[VWm]]] + 
  sum[gI2, 1, 2, conj[Cp[conj[UHpm[{gO2}]], VP, Hpm[{gI2}]]]*
    Cp[conj[UHpm[{gO1}]], VP, Hpm[{gI2}]]*F0[p^2, Mass2[Hpm[{gI2}]], 0]] + 
  sum[gI2, 1, 2, conj[Cp[conj[UHpm[{gO2}]], VZ, Hpm[{gI2}]]]*
    Cp[conj[UHpm[{gO1}]], VZ, Hpm[{gI2}]]*F0[p^2, Mass2[Hpm[{gI2}]], 
     Mass2[VZ]]], 
 {2*sum[gI1, 1, 2, sum[gI2, 1, 2, B0[p^2, Mass2[Cha[{gI2}]], 
        Mass2[Hpm[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Hpm[{gI1}]], Cha[{gI2}]][
         PL]]*Mass[Cha[{gI2}]]*Cp[UChi[{gO1}], conj[Hpm[{gI1}]], Cha[{gI2}]][
        PR]]] + sum[gI1, 1, 2, sum[gI2, 1, 4, 
     B0[p^2, Mass2[Chi[{gI2}]], Mass2[hh[{gI1}]]]*
      conj[Cp[UChi[{gO2}], hh[{gI1}], Chi[{gI2}]][PL]]*Mass[Chi[{gI2}]]*
      Cp[UChi[{gO1}], hh[{gI1}], Chi[{gI2}]][PR]]] + 
   2*sum[gI1, 1, 3, sum[gI2, 1, 3, B0[p^2, Mass2[Fv[{gI2}]], 
        Mass2[Sv[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Sv[{gI1}]], Fv[{gI2}]][
         PL]]*Mass[Fv[{gI2}]]*Cp[UChi[{gO1}], conj[Sv[{gI1}]], Fv[{gI2}]][
        PR]]] + sum[gI1, 1, 4, Mass[Chi[{gI1}]]*
     sum[gI2, 1, 2, B0[p^2, Mass2[Chi[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[UChi[{gO2}], Chi[{gI1}], Ah[{gI2}]][PL]]*
       Cp[UChi[{gO1}], Chi[{gI1}], Ah[{gI2}]][PR]]] + 
   6*sum[gI1, 1, 6, sum[gI2, 1, 3, B0[p^2, Mass2[Fd[{gI2}]], 
        Mass2[Sd[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Sd[{gI1}]], Fd[{gI2}]][
         PL]]*Mass[Fd[{gI2}]]*Cp[UChi[{gO1}], conj[Sd[{gI1}]], Fd[{gI2}]][
        PR]]] + 2*sum[gI1, 1, 6, sum[gI2, 1, 3, 
      B0[p^2, Mass2[Fe[{gI2}]], Mass2[Se[{gI1}]]]*
       conj[Cp[UChi[{gO2}], conj[Se[{gI1}]], Fe[{gI2}]][PL]]*Mass[Fe[{gI2}]]*
       Cp[UChi[{gO1}], conj[Se[{gI1}]], Fe[{gI2}]][PR]]] + 
   6*sum[gI1, 1, 6, sum[gI2, 1, 3, B0[p^2, Mass2[Fu[{gI2}]], 
        Mass2[Su[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Su[{gI1}]], Fu[{gI2}]][
         PL]]*Mass[Fu[{gI2}]]*Cp[UChi[{gO1}], conj[Su[{gI1}]], Fu[{gI2}]][
        PR]]] - 8*sum[gI2, 1, 2, (-rMS/2 + B0[p^2, Mass2[Cha[{gI2}]], 
        Mass2[VWm]])*conj[Cp[UChi[{gO2}], conj[VWm], Cha[{gI2}]][PR]]*
      Mass[Cha[{gI2}]]*Cp[UChi[{gO1}], conj[VWm], Cha[{gI2}]][PL]] - 
   4*sum[gI2, 1, 4, (-rMS/2 + B0[p^2, Mass2[Chi[{gI2}]], Mass2[VZ]])*
      conj[Cp[UChi[{gO2}], VZ, Chi[{gI2}]][PR]]*Mass[Chi[{gI2}]]*
      Cp[UChi[{gO1}], VZ, Chi[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], 
        Mass2[Hpm[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Hpm[{gI1}]], Cha[{gI2}]][
         PR]]*Cp[UChi[{gO1}], conj[Hpm[{gI1}]], Cha[{gI2}]][PR]]] - 
   sum[gI1, 1, 2, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[hh[{gI1}]]]*
       conj[Cp[UChi[{gO2}], hh[{gI1}], Chi[{gI2}]][PR]]*
       Cp[UChi[{gO1}], hh[{gI1}], Chi[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 3, B1[p^2, Mass2[Fv[{gI2}]], Mass2[Sv[{gI1}]]]*
      conj[Cp[UChi[{gO2}], conj[Sv[{gI1}]], Fv[{gI2}]][PR]]*
      Cp[UChi[{gO1}], conj[Sv[{gI1}]], Fv[{gI2}]][PR]]] - 
   sum[gI1, 1, 4, sum[gI2, 1, 2, B1[p^2, Mass2[Chi[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[UChi[{gO2}], Chi[{gI1}], Ah[{gI2}]][PR]]*
       Cp[UChi[{gO1}], Chi[{gI1}], Ah[{gI2}]][PR]]]/2 - 
   3*sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], 
        Mass2[Sd[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Sd[{gI1}]], Fd[{gI2}]][
         PR]]*Cp[UChi[{gO1}], conj[Sd[{gI1}]], Fd[{gI2}]][PR]]] - 
   sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[Se[{gI1}]]]*
      conj[Cp[UChi[{gO2}], conj[Se[{gI1}]], Fe[{gI2}]][PR]]*
      Cp[UChi[{gO1}], conj[Se[{gI1}]], Fe[{gI2}]][PR]]] - 
   3*sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], 
        Mass2[Su[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Su[{gI1}]], Fu[{gI2}]][
         PR]]*Cp[UChi[{gO1}], conj[Su[{gI1}]], Fu[{gI2}]][PR]]] - 
   2*sum[gI2, 1, 2, (rMS/2 + B1[p^2, Mass2[Cha[{gI2}]], Mass2[VWm]])*
      conj[Cp[UChi[{gO2}], conj[VWm], Cha[{gI2}]][PL]]*
      Cp[UChi[{gO1}], conj[VWm], Cha[{gI2}]][PL]] - 
   sum[gI2, 1, 4, (rMS/2 + B1[p^2, Mass2[Chi[{gI2}]], Mass2[VZ]])*
     conj[Cp[UChi[{gO2}], VZ, Chi[{gI2}]][PL]]*
     Cp[UChi[{gO1}], VZ, Chi[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], 
        Mass2[Hpm[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Hpm[{gI1}]], Cha[{gI2}]][
         PL]]*Cp[UChi[{gO1}], conj[Hpm[{gI1}]], Cha[{gI2}]][PL]]] - 
   sum[gI1, 1, 2, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[hh[{gI1}]]]*
       conj[Cp[UChi[{gO2}], hh[{gI1}], Chi[{gI2}]][PL]]*
       Cp[UChi[{gO1}], hh[{gI1}], Chi[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 3, B1[p^2, Mass2[Fv[{gI2}]], Mass2[Sv[{gI1}]]]*
      conj[Cp[UChi[{gO2}], conj[Sv[{gI1}]], Fv[{gI2}]][PL]]*
      Cp[UChi[{gO1}], conj[Sv[{gI1}]], Fv[{gI2}]][PL]]] - 
   sum[gI1, 1, 4, sum[gI2, 1, 2, B1[p^2, Mass2[Chi[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[UChi[{gO2}], Chi[{gI1}], Ah[{gI2}]][PL]]*
       Cp[UChi[{gO1}], Chi[{gI1}], Ah[{gI2}]][PL]]]/2 - 
   3*sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], 
        Mass2[Sd[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Sd[{gI1}]], Fd[{gI2}]][
         PL]]*Cp[UChi[{gO1}], conj[Sd[{gI1}]], Fd[{gI2}]][PL]]] - 
   sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[Se[{gI1}]]]*
      conj[Cp[UChi[{gO2}], conj[Se[{gI1}]], Fe[{gI2}]][PL]]*
      Cp[UChi[{gO1}], conj[Se[{gI1}]], Fe[{gI2}]][PL]]] - 
   3*sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], 
        Mass2[Su[{gI1}]]]*conj[Cp[UChi[{gO2}], conj[Su[{gI1}]], Fu[{gI2}]][
         PL]]*Cp[UChi[{gO1}], conj[Su[{gI1}]], Fu[{gI2}]][PL]]] - 
   2*sum[gI2, 1, 2, (rMS/2 + B1[p^2, Mass2[Cha[{gI2}]], Mass2[VWm]])*
      conj[Cp[UChi[{gO2}], conj[VWm], Cha[{gI2}]][PR]]*
      Cp[UChi[{gO1}], conj[VWm], Cha[{gI2}]][PR]] - 
   sum[gI2, 1, 4, (rMS/2 + B1[p^2, Mass2[Chi[{gI2}]], Mass2[VZ]])*
     conj[Cp[UChi[{gO2}], VZ, Chi[{gI2}]][PR]]*
     Cp[UChi[{gO1}], VZ, Chi[{gI2}]][PR]]}, 
 {sum[gI1, 1, 2, Mass[Cha[{gI1}]]*sum[gI2, 1, 2, 
      B0[p^2, Mass2[Cha[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UCha[{gO2}]], Cha[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UCha[{gO1}]], Cha[{gI1}], Ah[{gI2}]][PR]]] + 
   sum[gI1, 1, 2, sum[gI2, 1, 2, B0[p^2, Mass2[Cha[{gI2}]], Mass2[hh[{gI1}]]]*
      conj[Cp[bar[UCha[{gO2}]], hh[{gI1}], Cha[{gI2}]][PL]]*Mass[Cha[{gI2}]]*
      Cp[bar[UCha[{gO1}]], hh[{gI1}], Cha[{gI2}]][PR]]] + 
   sum[gI1, 1, 2, sum[gI2, 1, 4, B0[p^2, Mass2[Chi[{gI2}]], 
       Mass2[Hpm[{gI1}]]]*conj[Cp[bar[UCha[{gO2}]], Hpm[{gI1}], Chi[{gI2}]][
        PL]]*Mass[Chi[{gI2}]]*Cp[bar[UCha[{gO1}]], Hpm[{gI1}], Chi[{gI2}]][
       PR]]] + sum[gI1, 1, 3, sum[gI2, 1, 3, 
     B0[p^2, Mass2[Fe[{gI2}]], Mass2[Sv[{gI1}]]]*
      conj[Cp[bar[UCha[{gO2}]], conj[Sv[{gI1}]], Fe[{gI2}]][PL]]*
      Mass[Fe[{gI2}]]*Cp[bar[UCha[{gO1}]], conj[Sv[{gI1}]], Fe[{gI2}]][
       PR]]] + 3*sum[gI1, 1, 3, Mass[Fu[{gI1}]]*sum[gI2, 1, 6, 
       B0[p^2, Mass2[Fu[{gI1}]], Mass2[Sd[{gI2}]]]*
        conj[Cp[bar[UCha[{gO2}]], bar[Fu[{gI1}]], Sd[{gI2}]][PL]]*
        Cp[bar[UCha[{gO1}]], bar[Fu[{gI1}]], Sd[{gI2}]][PR]]] + 
   sum[gI1, 1, 3, Mass[Fv[{gI1}]]*sum[gI2, 1, 6, 
      B0[p^2, Mass2[Fv[{gI1}]], Mass2[Se[{gI2}]]]*
       conj[Cp[bar[UCha[{gO2}]], bar[Fv[{gI1}]], Se[{gI2}]][PL]]*
       Cp[bar[UCha[{gO1}]], bar[Fv[{gI1}]], Se[{gI2}]][PR]]] + 
   3*sum[gI1, 1, 6, sum[gI2, 1, 3, B0[p^2, Mass2[Fd[{gI2}]], 
        Mass2[Su[{gI1}]]]*conj[Cp[bar[UCha[{gO2}]], conj[Su[{gI1}]], 
          Fd[{gI2}]][PL]]*Mass[Fd[{gI2}]]*
       Cp[bar[UCha[{gO1}]], conj[Su[{gI1}]], Fd[{gI2}]][PR]]] - 
   4*sum[gI2, 1, 2, (-rMS/2 + B0[p^2, Mass2[Cha[{gI2}]], 0])*
      conj[Cp[bar[UCha[{gO2}]], VP, Cha[{gI2}]][PR]]*Mass[Cha[{gI2}]]*
      Cp[bar[UCha[{gO1}]], VP, Cha[{gI2}]][PL]] - 
   4*sum[gI2, 1, 2, (-rMS/2 + B0[p^2, Mass2[Cha[{gI2}]], Mass2[VZ]])*
      conj[Cp[bar[UCha[{gO2}]], VZ, Cha[{gI2}]][PR]]*Mass[Cha[{gI2}]]*
      Cp[bar[UCha[{gO1}]], VZ, Cha[{gI2}]][PL]] - 
   4*sum[gI2, 1, 4, (-rMS/2 + B0[p^2, Mass2[Chi[{gI2}]], Mass2[VWm]])*
      conj[Cp[bar[UCha[{gO2}]], VWm, Chi[{gI2}]][PR]]*Mass[Chi[{gI2}]]*
      Cp[bar[UCha[{gO1}]], VWm, Chi[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI1}]], Mass2[Ah[{gI2}]]]*
        conj[Cp[bar[UCha[{gO2}]], Cha[{gI1}], Ah[{gI2}]][PR]]*
        Cp[bar[UCha[{gO1}]], Cha[{gI1}], Ah[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], Mass2[hh[{gI1}]]]*
       conj[Cp[bar[UCha[{gO2}]], hh[{gI1}], Cha[{gI2}]][PR]]*
       Cp[bar[UCha[{gO1}]], hh[{gI1}], Cha[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], 
        Mass2[Hpm[{gI1}]]]*conj[Cp[bar[UCha[{gO2}]], Hpm[{gI1}], Chi[{gI2}]][
         PR]]*Cp[bar[UCha[{gO1}]], Hpm[{gI1}], Chi[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[Sv[{gI1}]]]*
       conj[Cp[bar[UCha[{gO2}]], conj[Sv[{gI1}]], Fe[{gI2}]][PR]]*
       Cp[bar[UCha[{gO1}]], conj[Sv[{gI1}]], Fe[{gI2}]][PR]]]/2 - 
   (3*sum[gI1, 1, 3, sum[gI2, 1, 6, B1[p^2, Mass2[Fu[{gI1}]], 
         Mass2[Sd[{gI2}]]]*conj[Cp[bar[UCha[{gO2}]], bar[Fu[{gI1}]], 
           Sd[{gI2}]][PR]]*Cp[bar[UCha[{gO1}]], bar[Fu[{gI1}]], Sd[{gI2}]][
         PR]]])/2 - sum[gI1, 1, 3, sum[gI2, 1, 6, 
      B1[p^2, Mass2[Fv[{gI1}]], Mass2[Se[{gI2}]]]*
       conj[Cp[bar[UCha[{gO2}]], bar[Fv[{gI1}]], Se[{gI2}]][PR]]*
       Cp[bar[UCha[{gO1}]], bar[Fv[{gI1}]], Se[{gI2}]][PR]]]/2 - 
   (3*sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], 
         Mass2[Su[{gI1}]]]*conj[Cp[bar[UCha[{gO2}]], conj[Su[{gI1}]], 
           Fd[{gI2}]][PR]]*Cp[bar[UCha[{gO1}]], conj[Su[{gI1}]], Fd[{gI2}]][
         PR]]])/2 - sum[gI2, 1, 2, (rMS/2 + B1[p^2, Mass2[Cha[{gI2}]], 0])*
     conj[Cp[bar[UCha[{gO2}]], VP, Cha[{gI2}]][PL]]*
     Cp[bar[UCha[{gO1}]], VP, Cha[{gI2}]][PL]] - 
   sum[gI2, 1, 2, (rMS/2 + B1[p^2, Mass2[Cha[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UCha[{gO2}]], VZ, Cha[{gI2}]][PL]]*
     Cp[bar[UCha[{gO1}]], VZ, Cha[{gI2}]][PL]] - 
   sum[gI2, 1, 4, (rMS/2 + B1[p^2, Mass2[Chi[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UCha[{gO2}]], VWm, Chi[{gI2}]][PL]]*
     Cp[bar[UCha[{gO1}]], VWm, Chi[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI1}]], Mass2[Ah[{gI2}]]]*
        conj[Cp[bar[UCha[{gO2}]], Cha[{gI1}], Ah[{gI2}]][PL]]*
        Cp[bar[UCha[{gO1}]], Cha[{gI1}], Ah[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], Mass2[hh[{gI1}]]]*
       conj[Cp[bar[UCha[{gO2}]], hh[{gI1}], Cha[{gI2}]][PL]]*
       Cp[bar[UCha[{gO1}]], hh[{gI1}], Cha[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], 
        Mass2[Hpm[{gI1}]]]*conj[Cp[bar[UCha[{gO2}]], Hpm[{gI1}], Chi[{gI2}]][
         PL]]*Cp[bar[UCha[{gO1}]], Hpm[{gI1}], Chi[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[Sv[{gI1}]]]*
       conj[Cp[bar[UCha[{gO2}]], conj[Sv[{gI1}]], Fe[{gI2}]][PL]]*
       Cp[bar[UCha[{gO1}]], conj[Sv[{gI1}]], Fe[{gI2}]][PL]]]/2 - 
   (3*sum[gI1, 1, 3, sum[gI2, 1, 6, B1[p^2, Mass2[Fu[{gI1}]], 
         Mass2[Sd[{gI2}]]]*conj[Cp[bar[UCha[{gO2}]], bar[Fu[{gI1}]], 
           Sd[{gI2}]][PL]]*Cp[bar[UCha[{gO1}]], bar[Fu[{gI1}]], Sd[{gI2}]][
         PL]]])/2 - sum[gI1, 1, 3, sum[gI2, 1, 6, 
      B1[p^2, Mass2[Fv[{gI1}]], Mass2[Se[{gI2}]]]*
       conj[Cp[bar[UCha[{gO2}]], bar[Fv[{gI1}]], Se[{gI2}]][PL]]*
       Cp[bar[UCha[{gO1}]], bar[Fv[{gI1}]], Se[{gI2}]][PL]]]/2 - 
   (3*sum[gI1, 1, 6, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], 
         Mass2[Su[{gI1}]]]*conj[Cp[bar[UCha[{gO2}]], conj[Su[{gI1}]], 
           Fd[{gI2}]][PL]]*Cp[bar[UCha[{gO1}]], conj[Su[{gI1}]], Fd[{gI2}]][
         PL]]])/2 - sum[gI2, 1, 2, (rMS/2 + B1[p^2, Mass2[Cha[{gI2}]], 0])*
     conj[Cp[bar[UCha[{gO2}]], VP, Cha[{gI2}]][PR]]*
     Cp[bar[UCha[{gO1}]], VP, Cha[{gI2}]][PR]] - 
   sum[gI2, 1, 2, (rMS/2 + B1[p^2, Mass2[Cha[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UCha[{gO2}]], VZ, Cha[{gI2}]][PR]]*
     Cp[bar[UCha[{gO1}]], VZ, Cha[{gI2}]][PR]] - 
   sum[gI2, 1, 4, (rMS/2 + B1[p^2, Mass2[Chi[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UCha[{gO2}]], VWm, Chi[{gI2}]][PR]]*
     Cp[bar[UCha[{gO1}]], VWm, Chi[{gI2}]][PR]]}, 
 {sum[gI1, 1, 2, sum[gI2, 1, 3, B0[p^2, Mass2[Fe[{gI2}]], Mass2[hh[{gI1}]]]*
      conj[Cp[bar[UFe[{gO2}]], hh[{gI1}], Fe[{gI2}]][PL]]*Mass[Fe[{gI2}]]*
      Cp[bar[UFe[{gO1}]], hh[{gI1}], Fe[{gI2}]][PR]]] + 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B0[p^2, Mass2[Fv[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[bar[UFe[{gO2}]], Hpm[{gI1}], Fv[{gI2}]][PL]]*Mass[Fv[{gI2}]]*
      Cp[bar[UFe[{gO1}]], Hpm[{gI1}], Fv[{gI2}]][PR]]] + 
   sum[gI1, 1, 3, Mass[Fe[{gI1}]]*sum[gI2, 1, 2, 
      B0[p^2, Mass2[Fe[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFe[{gO2}]], Fe[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UFe[{gO1}]], Fe[{gI1}], Ah[{gI2}]][PR]]] + 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B0[p^2, Mass2[Cha[{gI2}]], Mass2[Sv[{gI1}]]]*
      conj[Cp[bar[UFe[{gO2}]], Sv[{gI1}], Cha[{gI2}]][PL]]*Mass[Cha[{gI2}]]*
      Cp[bar[UFe[{gO1}]], Sv[{gI1}], Cha[{gI2}]][PR]]] + 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B0[p^2, Mass2[Chi[{gI2}]], Mass2[Se[{gI1}]]]*
      conj[Cp[bar[UFe[{gO2}]], Se[{gI1}], Chi[{gI2}]][PL]]*Mass[Chi[{gI2}]]*
      Cp[bar[UFe[{gO1}]], Se[{gI1}], Chi[{gI2}]][PR]]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fe[{gI2}]], 0])*
      conj[Cp[bar[UFe[{gO2}]], VP, Fe[{gI2}]][PR]]*Mass[Fe[{gI2}]]*
      Cp[bar[UFe[{gO1}]], VP, Fe[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fv[{gI2}]], Mass2[VWm]])*
      conj[Cp[bar[UFe[{gO2}]], VWm, Fv[{gI2}]][PR]]*Mass[Fv[{gI2}]]*
      Cp[bar[UFe[{gO1}]], VWm, Fv[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fe[{gI2}]], Mass2[VZ]])*
      conj[Cp[bar[UFe[{gO2}]], VZ, Fe[{gI2}]][PR]]*Mass[Fe[{gI2}]]*
      Cp[bar[UFe[{gO1}]], VZ, Fe[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[hh[{gI1}]]]*
        conj[Cp[bar[UFe[{gO2}]], hh[{gI1}], Fe[{gI2}]][PR]]*
        Cp[bar[UFe[{gO1}]], hh[{gI1}], Fe[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fv[{gI2}]], Mass2[Hpm[{gI1}]]]*
       conj[Cp[bar[UFe[{gO2}]], Hpm[{gI1}], Fv[{gI2}]][PR]]*
       Cp[bar[UFe[{gO1}]], Hpm[{gI1}], Fv[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Fe[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFe[{gO2}]], Fe[{gI1}], Ah[{gI2}]][PR]]*
       Cp[bar[UFe[{gO1}]], Fe[{gI1}], Ah[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], Mass2[Sv[{gI1}]]]*
       conj[Cp[bar[UFe[{gO2}]], Sv[{gI1}], Cha[{gI2}]][PR]]*
       Cp[bar[UFe[{gO1}]], Sv[{gI1}], Cha[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[Se[{gI1}]]]*
       conj[Cp[bar[UFe[{gO2}]], Se[{gI1}], Chi[{gI2}]][PR]]*
       Cp[bar[UFe[{gO1}]], Se[{gI1}], Chi[{gI2}]][PR]]]/2 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fe[{gI2}]], 0])*
     conj[Cp[bar[UFe[{gO2}]], VP, Fe[{gI2}]][PL]]*
     Cp[bar[UFe[{gO1}]], VP, Fe[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fv[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UFe[{gO2}]], VWm, Fv[{gI2}]][PL]]*
     Cp[bar[UFe[{gO1}]], VWm, Fv[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fe[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UFe[{gO2}]], VZ, Fe[{gI2}]][PL]]*
     Cp[bar[UFe[{gO1}]], VZ, Fe[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fe[{gI2}]], Mass2[hh[{gI1}]]]*
        conj[Cp[bar[UFe[{gO2}]], hh[{gI1}], Fe[{gI2}]][PL]]*
        Cp[bar[UFe[{gO1}]], hh[{gI1}], Fe[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fv[{gI2}]], Mass2[Hpm[{gI1}]]]*
       conj[Cp[bar[UFe[{gO2}]], Hpm[{gI1}], Fv[{gI2}]][PL]]*
       Cp[bar[UFe[{gO1}]], Hpm[{gI1}], Fv[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Fe[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFe[{gO2}]], Fe[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UFe[{gO1}]], Fe[{gI1}], Ah[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], Mass2[Sv[{gI1}]]]*
       conj[Cp[bar[UFe[{gO2}]], Sv[{gI1}], Cha[{gI2}]][PL]]*
       Cp[bar[UFe[{gO1}]], Sv[{gI1}], Cha[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[Se[{gI1}]]]*
       conj[Cp[bar[UFe[{gO2}]], Se[{gI1}], Chi[{gI2}]][PL]]*
       Cp[bar[UFe[{gO1}]], Se[{gI1}], Chi[{gI2}]][PL]]]/2 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fe[{gI2}]], 0])*
     conj[Cp[bar[UFe[{gO2}]], VP, Fe[{gI2}]][PR]]*
     Cp[bar[UFe[{gO1}]], VP, Fe[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fv[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UFe[{gO2}]], VWm, Fv[{gI2}]][PR]]*
     Cp[bar[UFe[{gO1}]], VWm, Fv[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fe[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UFe[{gO2}]], VZ, Fe[{gI2}]][PR]]*
     Cp[bar[UFe[{gO1}]], VZ, Fe[{gI2}]][PR]]}, 
 {sum[gI1, 1, 2, sum[gI2, 1, 3, B0[p^2, Mass2[Fd[{gI2}]], Mass2[hh[{gI1}]]]*
      conj[Cp[bar[UFd[{gO2}]], hh[{gI1}], Fd[{gI2}]][PL]]*Mass[Fd[{gI2}]]*
      Cp[bar[UFd[{gO1}]], hh[{gI1}], Fd[{gI2}]][PR]]] + 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B0[p^2, Mass2[Fu[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[bar[UFd[{gO2}]], Hpm[{gI1}], Fu[{gI2}]][PL]]*Mass[Fu[{gI2}]]*
      Cp[bar[UFd[{gO1}]], Hpm[{gI1}], Fu[{gI2}]][PR]]] + 
   sum[gI1, 1, 3, Mass[Fd[{gI1}]]*sum[gI2, 1, 2, 
      B0[p^2, Mass2[Fd[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFd[{gO2}]], Fd[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UFd[{gO1}]], Fd[{gI1}], Ah[{gI2}]][PR]]] + 
   sum[gI1, 1, 6, sum[gI2, 1, 2, B0[p^2, Mass2[Cha[{gI2}]], Mass2[Su[{gI1}]]]*
      conj[Cp[bar[UFd[{gO2}]], Su[{gI1}], Cha[{gI2}]][PL]]*Mass[Cha[{gI2}]]*
      Cp[bar[UFd[{gO1}]], Su[{gI1}], Cha[{gI2}]][PR]]] + 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B0[p^2, Mass2[Chi[{gI2}]], Mass2[Sd[{gI1}]]]*
      conj[Cp[bar[UFd[{gO2}]], Sd[{gI1}], Chi[{gI2}]][PL]]*Mass[Chi[{gI2}]]*
      Cp[bar[UFd[{gO1}]], Sd[{gI1}], Chi[{gI2}]][PR]]] + 
   (4*Mass[Glu]*sum[gI1, 1, 6, B0[p^2, Mass2[Glu], Mass2[Sd[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Sd[{gI1}], Glu[{1}]][PL]]*
       Cp[bar[UFd[{gO1}]], Sd[{gI1}], Glu[{1}]][PR]])/3 - 
   (16*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fd[{gI2}]], 0])*
       conj[Cp[bar[UFd[{gO2}]], VG, Fd[{gI2}]][PR]]*Mass[Fd[{gI2}]]*
       Cp[bar[UFd[{gO1}]], VG, Fd[{gI2}]][PL]])/3 - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fd[{gI2}]], 0])*
      conj[Cp[bar[UFd[{gO2}]], VP, Fd[{gI2}]][PR]]*Mass[Fd[{gI2}]]*
      Cp[bar[UFd[{gO1}]], VP, Fd[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fu[{gI2}]], Mass2[VWm]])*
      conj[Cp[bar[UFd[{gO2}]], VWm, Fu[{gI2}]][PR]]*Mass[Fu[{gI2}]]*
      Cp[bar[UFd[{gO1}]], VWm, Fu[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fd[{gI2}]], Mass2[VZ]])*
      conj[Cp[bar[UFd[{gO2}]], VZ, Fd[{gI2}]][PR]]*Mass[Fd[{gI2}]]*
      Cp[bar[UFd[{gO1}]], VZ, Fd[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], Mass2[hh[{gI1}]]]*
        conj[Cp[bar[UFd[{gO2}]], hh[{gI1}], Fd[{gI2}]][PR]]*
        Cp[bar[UFd[{gO1}]], hh[{gI1}], Fd[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], Mass2[Hpm[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Hpm[{gI1}], Fu[{gI2}]][PR]]*
       Cp[bar[UFd[{gO1}]], Hpm[{gI1}], Fu[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Fd[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFd[{gO2}]], Fd[{gI1}], Ah[{gI2}]][PR]]*
       Cp[bar[UFd[{gO1}]], Fd[{gI1}], Ah[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Su[{gI1}], Cha[{gI2}]][PR]]*
       Cp[bar[UFd[{gO1}]], Su[{gI1}], Cha[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[Sd[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Sd[{gI1}], Chi[{gI2}]][PR]]*
       Cp[bar[UFd[{gO1}]], Sd[{gI1}], Chi[{gI2}]][PR]]]/2 - 
   (2*sum[gI1, 1, 6, B1[p^2, Mass2[Glu], Mass2[Sd[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Sd[{gI1}], Glu[{1}]][PR]]*
       Cp[bar[UFd[{gO1}]], Sd[{gI1}], Glu[{1}]][PR]])/3 - 
   (4*sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], 0])*
       conj[Cp[bar[UFd[{gO2}]], VG, Fd[{gI2}]][PL]]*
       Cp[bar[UFd[{gO1}]], VG, Fd[{gI2}]][PL]])/3 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], 0])*
     conj[Cp[bar[UFd[{gO2}]], VP, Fd[{gI2}]][PL]]*
     Cp[bar[UFd[{gO1}]], VP, Fd[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UFd[{gO2}]], VWm, Fu[{gI2}]][PL]]*
     Cp[bar[UFd[{gO1}]], VWm, Fu[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UFd[{gO2}]], VZ, Fd[{gI2}]][PL]]*
     Cp[bar[UFd[{gO1}]], VZ, Fd[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], Mass2[hh[{gI1}]]]*
        conj[Cp[bar[UFd[{gO2}]], hh[{gI1}], Fd[{gI2}]][PL]]*
        Cp[bar[UFd[{gO1}]], hh[{gI1}], Fd[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], Mass2[Hpm[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Hpm[{gI1}], Fu[{gI2}]][PL]]*
       Cp[bar[UFd[{gO1}]], Hpm[{gI1}], Fu[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Fd[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFd[{gO2}]], Fd[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UFd[{gO1}]], Fd[{gI1}], Ah[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 2, B1[p^2, Mass2[Cha[{gI2}]], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Su[{gI1}], Cha[{gI2}]][PL]]*
       Cp[bar[UFd[{gO1}]], Su[{gI1}], Cha[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[Sd[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Sd[{gI1}], Chi[{gI2}]][PL]]*
       Cp[bar[UFd[{gO1}]], Sd[{gI1}], Chi[{gI2}]][PL]]]/2 - 
   (2*sum[gI1, 1, 6, B1[p^2, Mass2[Glu], Mass2[Sd[{gI1}]]]*
       conj[Cp[bar[UFd[{gO2}]], Sd[{gI1}], Glu[{1}]][PL]]*
       Cp[bar[UFd[{gO1}]], Sd[{gI1}], Glu[{1}]][PL]])/3 - 
   (4*sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], 0])*
       conj[Cp[bar[UFd[{gO2}]], VG, Fd[{gI2}]][PR]]*
       Cp[bar[UFd[{gO1}]], VG, Fd[{gI2}]][PR]])/3 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], 0])*
     conj[Cp[bar[UFd[{gO2}]], VP, Fd[{gI2}]][PR]]*
     Cp[bar[UFd[{gO1}]], VP, Fd[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UFd[{gO2}]], VWm, Fu[{gI2}]][PR]]*
     Cp[bar[UFd[{gO1}]], VWm, Fu[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UFd[{gO2}]], VZ, Fd[{gI2}]][PR]]*
     Cp[bar[UFd[{gO1}]], VZ, Fd[{gI2}]][PR]]}, 
 {sum[gI1, 1, 2, sum[gI2, 1, 3, B0[p^2, Mass2[Fd[{gI2}]], Mass2[Hpm[{gI1}]]]*
      conj[Cp[bar[UFu[{gO2}]], conj[Hpm[{gI1}]], Fd[{gI2}]][PL]]*
      Mass[Fd[{gI2}]]*Cp[bar[UFu[{gO1}]], conj[Hpm[{gI1}]], Fd[{gI2}]][
       PR]]] + sum[gI1, 1, 2, sum[gI2, 1, 3, 
     B0[p^2, Mass2[Fu[{gI2}]], Mass2[hh[{gI1}]]]*
      conj[Cp[bar[UFu[{gO2}]], hh[{gI1}], Fu[{gI2}]][PL]]*Mass[Fu[{gI2}]]*
      Cp[bar[UFu[{gO1}]], hh[{gI1}], Fu[{gI2}]][PR]]] + 
   sum[gI1, 1, 2, Mass[Cha[{gI1}]]*sum[gI2, 1, 6, 
      B0[p^2, Mass2[Cha[{gI1}]], Mass2[Sd[{gI2}]]]*
       conj[Cp[bar[UFu[{gO2}]], bar[Cha[{gI1}]], Sd[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], bar[Cha[{gI1}]], Sd[{gI2}]][PR]]] + 
   sum[gI1, 1, 3, Mass[Fu[{gI1}]]*sum[gI2, 1, 2, 
      B0[p^2, Mass2[Fu[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFu[{gO2}]], Fu[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], Fu[{gI1}], Ah[{gI2}]][PR]]] + 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B0[p^2, Mass2[Chi[{gI2}]], Mass2[Su[{gI1}]]]*
      conj[Cp[bar[UFu[{gO2}]], Su[{gI1}], Chi[{gI2}]][PL]]*Mass[Chi[{gI2}]]*
      Cp[bar[UFu[{gO1}]], Su[{gI1}], Chi[{gI2}]][PR]]] + 
   (4*Mass[Glu]*sum[gI1, 1, 6, B0[p^2, Mass2[Glu], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], Su[{gI1}], Glu[{1}]][PL]]*
       Cp[bar[UFu[{gO1}]], Su[{gI1}], Glu[{1}]][PR]])/3 - 
   (16*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fu[{gI2}]], 0])*
       conj[Cp[bar[UFu[{gO2}]], VG, Fu[{gI2}]][PR]]*Mass[Fu[{gI2}]]*
       Cp[bar[UFu[{gO1}]], VG, Fu[{gI2}]][PL]])/3 - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fu[{gI2}]], 0])*
      conj[Cp[bar[UFu[{gO2}]], VP, Fu[{gI2}]][PR]]*Mass[Fu[{gI2}]]*
      Cp[bar[UFu[{gO1}]], VP, Fu[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fu[{gI2}]], Mass2[VZ]])*
      conj[Cp[bar[UFu[{gO2}]], VZ, Fu[{gI2}]][PR]]*Mass[Fu[{gI2}]]*
      Cp[bar[UFu[{gO1}]], VZ, Fu[{gI2}]][PL]] - 
   4*sum[gI2, 1, 3, (-rMS/2 + B0[p^2, Mass2[Fd[{gI2}]], Mass2[VWm]])*
      conj[Cp[bar[UFu[{gO2}]], conj[VWm], Fd[{gI2}]][PR]]*Mass[Fd[{gI2}]]*
      Cp[bar[UFu[{gO1}]], conj[VWm], Fd[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], Mass2[Hpm[{gI1}]]]*
        conj[Cp[bar[UFu[{gO2}]], conj[Hpm[{gI1}]], Fd[{gI2}]][PR]]*
        Cp[bar[UFu[{gO1}]], conj[Hpm[{gI1}]], Fd[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], Mass2[hh[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], hh[{gI1}], Fu[{gI2}]][PR]]*
       Cp[bar[UFu[{gO1}]], hh[{gI1}], Fu[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 6, B1[p^2, Mass2[Cha[{gI1}]], Mass2[Sd[{gI2}]]]*
       conj[Cp[bar[UFu[{gO2}]], bar[Cha[{gI1}]], Sd[{gI2}]][PR]]*
       Cp[bar[UFu[{gO1}]], bar[Cha[{gI1}]], Sd[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Fu[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFu[{gO2}]], Fu[{gI1}], Ah[{gI2}]][PR]]*
       Cp[bar[UFu[{gO1}]], Fu[{gI1}], Ah[{gI2}]][PR]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], Su[{gI1}], Chi[{gI2}]][PR]]*
       Cp[bar[UFu[{gO1}]], Su[{gI1}], Chi[{gI2}]][PR]]]/2 - 
   (2*sum[gI1, 1, 6, B1[p^2, Mass2[Glu], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], Su[{gI1}], Glu[{1}]][PR]]*
       Cp[bar[UFu[{gO1}]], Su[{gI1}], Glu[{1}]][PR]])/3 - 
   (4*sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], 0])*
       conj[Cp[bar[UFu[{gO2}]], VG, Fu[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], VG, Fu[{gI2}]][PL]])/3 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], 0])*
     conj[Cp[bar[UFu[{gO2}]], VP, Fu[{gI2}]][PL]]*
     Cp[bar[UFu[{gO1}]], VP, Fu[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UFu[{gO2}]], VZ, Fu[{gI2}]][PL]]*
     Cp[bar[UFu[{gO1}]], VZ, Fu[{gI2}]][PL]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UFu[{gO2}]], conj[VWm], Fd[{gI2}]][PL]]*
     Cp[bar[UFu[{gO1}]], conj[VWm], Fd[{gI2}]][PL]], 
  -sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fd[{gI2}]], Mass2[Hpm[{gI1}]]]*
        conj[Cp[bar[UFu[{gO2}]], conj[Hpm[{gI1}]], Fd[{gI2}]][PL]]*
        Cp[bar[UFu[{gO1}]], conj[Hpm[{gI1}]], Fd[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 3, B1[p^2, Mass2[Fu[{gI2}]], Mass2[hh[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], hh[{gI1}], Fu[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], hh[{gI1}], Fu[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 2, sum[gI2, 1, 6, B1[p^2, Mass2[Cha[{gI1}]], Mass2[Sd[{gI2}]]]*
       conj[Cp[bar[UFu[{gO2}]], bar[Cha[{gI1}]], Sd[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], bar[Cha[{gI1}]], Sd[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 3, sum[gI2, 1, 2, B1[p^2, Mass2[Fu[{gI1}]], Mass2[Ah[{gI2}]]]*
       conj[Cp[bar[UFu[{gO2}]], Fu[{gI1}], Ah[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], Fu[{gI1}], Ah[{gI2}]][PL]]]/2 - 
   sum[gI1, 1, 6, sum[gI2, 1, 4, B1[p^2, Mass2[Chi[{gI2}]], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], Su[{gI1}], Chi[{gI2}]][PL]]*
       Cp[bar[UFu[{gO1}]], Su[{gI1}], Chi[{gI2}]][PL]]]/2 - 
   (2*sum[gI1, 1, 6, B1[p^2, Mass2[Glu], Mass2[Su[{gI1}]]]*
       conj[Cp[bar[UFu[{gO2}]], Su[{gI1}], Glu[{1}]][PL]]*
       Cp[bar[UFu[{gO1}]], Su[{gI1}], Glu[{1}]][PL]])/3 - 
   (4*sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], 0])*
       conj[Cp[bar[UFu[{gO2}]], VG, Fu[{gI2}]][PR]]*
       Cp[bar[UFu[{gO1}]], VG, Fu[{gI2}]][PR]])/3 - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], 0])*
     conj[Cp[bar[UFu[{gO2}]], VP, Fu[{gI2}]][PR]]*
     Cp[bar[UFu[{gO1}]], VP, Fu[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fu[{gI2}]], Mass2[VZ]])*
     conj[Cp[bar[UFu[{gO2}]], VZ, Fu[{gI2}]][PR]]*
     Cp[bar[UFu[{gO1}]], VZ, Fu[{gI2}]][PR]] - 
   sum[gI2, 1, 3, (rMS/2 + B1[p^2, Mass2[Fd[{gI2}]], Mass2[VWm]])*
     conj[Cp[bar[UFu[{gO2}]], conj[VWm], Fd[{gI2}]][PR]]*
     Cp[bar[UFu[{gO1}]], conj[VWm], Fd[{gI2}]][PR]]}}
