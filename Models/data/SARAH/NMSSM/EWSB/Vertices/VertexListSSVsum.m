{{{Ah[{gt1}], hh[{gt2}], VZ[{lt3}]}, 
  {((g2*Cos[ThetaW] + g1*Sin[ThetaW])*(ZA[gt1, 1]*ZH[gt2, 1] - 
      ZA[gt1, 2]*ZH[gt2, 2]))/2, Mom[Ah[{gt1}], lt3] - Mom[hh[{gt2}], lt3]}}, 
 {{Ah[{gt1}], Hpm[{gt2}], conj[VWm[{lt3}]]}, 
  {(g2*(ZA[gt1, 1]*ZP[gt2, 1] + ZA[gt1, 2]*ZP[gt2, 2]))/2, 
   Mom[Ah[{gt1}], lt3] - Mom[Hpm[{gt2}], lt3]}}, 
 {{Ah[{gt1}], conj[Hpm[{gt2}]], VWm[{lt3}]}, 
  {(g2*(ZA[gt1, 1]*ZP[gt2, 1] + ZA[gt1, 2]*ZP[gt2, 2]))/2, 
   Mom[Ah[{gt1}], lt3] - Mom[conj[Hpm[{gt2}]], lt3]}}, 
 {{hh[{gt1}], Hpm[{gt2}], conj[VWm[{lt3}]]}, 
  {(I/2)*g2*(ZH[gt1, 1]*ZP[gt2, 1] - ZH[gt1, 2]*ZP[gt2, 2]), 
   Mom[hh[{gt1}], lt3] - Mom[Hpm[{gt2}], lt3]}}, 
 {{hh[{gt1}], conj[Hpm[{gt2}]], VWm[{lt3}]}, 
  {(-I/2)*g2*(ZH[gt1, 1]*ZP[gt2, 1] - ZH[gt1, 2]*ZP[gt2, 2]), 
   -Mom[conj[Hpm[{gt2}]], lt3] + Mom[hh[{gt1}], lt3]}}, 
 {{Hpm[{gt1}], conj[Hpm[{gt2}]], VP[{lt3}]}, 
  {(I/2)*(g1*Cos[ThetaW] + g2*Sin[ThetaW])*(ZP[gt1, 1]*ZP[gt2, 1] + 
     ZP[gt1, 2]*ZP[gt2, 2]), -Mom[conj[Hpm[{gt2}]], lt3] + 
    Mom[Hpm[{gt1}], lt3]}}, {{Hpm[{gt1}], conj[Hpm[{gt2}]], VZ[{lt3}]}, 
  {(I/2)*(g2*Cos[ThetaW] - g1*Sin[ThetaW])*(ZP[gt1, 1]*ZP[gt2, 1] + 
     ZP[gt1, 2]*ZP[gt2, 2]), -Mom[conj[Hpm[{gt2}]], lt3] + 
    Mom[Hpm[{gt1}], lt3]}}, {{Sd[{gt1, ct1}], conj[Sd[{gt2, ct2}]], 
   VG[{ct3, lt3}]}, {(-I/2)*g3*Lam[ct3, ct2, ct1]*
    sumExp[j1, 1, 6, conj[ZD[gt1, j1]]*ZD[gt2, j1]], 
   -Mom[conj[Sd[{gt2, ct2}]], lt3] + Mom[Sd[{gt1, ct1}], lt3]}}, 
 {{Sd[{gt1, ct1}], conj[Sd[{gt2, ct2}]], VP[{lt3}]}, 
  {(-I/6)*Delta[ct1, ct2]*((g1*Cos[ThetaW] - 3*g2*Sin[ThetaW])*
      sumExp[j1, 1, 3, conj[ZD[gt1, j1]]*ZD[gt2, j1]] - 
     2*g1*Cos[ThetaW]*sumExp[j1, 1, 3, conj[ZD[gt1, 3 + j1]]*
        ZD[gt2, 3 + j1]]), -Mom[conj[Sd[{gt2, ct2}]], lt3] + 
    Mom[Sd[{gt1, ct1}], lt3]}}, {{Sd[{gt1, ct1}], conj[Sd[{gt2, ct2}]], 
   VZ[{lt3}]}, {(I/6)*Delta[ct1, ct2]*((3*g2*Cos[ThetaW] + g1*Sin[ThetaW])*
      sumExp[j1, 1, 3, conj[ZD[gt1, j1]]*ZD[gt2, j1]] - 
     2*g1*Sin[ThetaW]*sumExp[j1, 1, 3, conj[ZD[gt1, 3 + j1]]*
        ZD[gt2, 3 + j1]]), -Mom[conj[Sd[{gt2, ct2}]], lt3] + 
    Mom[Sd[{gt1, ct1}], lt3]}}, {{Sd[{gt1, ct1}], conj[Su[{gt2, ct2}]], 
   conj[VWm[{lt3}]]}, 
  {((-I)*g2*Delta[ct1, ct2]*sumExp[j1, 1, 3, conj[ZD[gt1, j1]]*ZU[gt2, j1]])/
    Sqrt[2], -Mom[conj[Su[{gt2, ct2}]], lt3] + Mom[Sd[{gt1, ct1}], lt3]}}, 
 {{Se[{gt1}], conj[Se[{gt2}]], VP[{lt3}]}, 
  {(I/2)*((g1*Cos[ThetaW] + g2*Sin[ThetaW])*sumExp[j1, 1, 3, 
       conj[ZE[gt1, j1]]*ZE[gt2, j1]] + 2*g1*Cos[ThetaW]*
      sumExp[j1, 1, 3, conj[ZE[gt1, 3 + j1]]*ZE[gt2, 3 + j1]]), 
   -Mom[conj[Se[{gt2}]], lt3] + Mom[Se[{gt1}], lt3]}}, 
 {{Se[{gt1}], conj[Se[{gt2}]], VZ[{lt3}]}, 
  {(I/2)*((g2*Cos[ThetaW] - g1*Sin[ThetaW])*sumExp[j1, 1, 3, 
       conj[ZE[gt1, j1]]*ZE[gt2, j1]] - 2*g1*Sin[ThetaW]*
      sumExp[j1, 1, 3, conj[ZE[gt1, 3 + j1]]*ZE[gt2, 3 + j1]]), 
   -Mom[conj[Se[{gt2}]], lt3] + Mom[Se[{gt1}], lt3]}}, 
 {{Se[{gt1}], conj[Sv[{gt2}]], conj[VWm[{lt3}]]}, 
  {((-I)*g2*sumExp[j1, 1, 3, conj[ZE[gt1, j1]]*ZV[gt2, j1]])/Sqrt[2], 
   -Mom[conj[Sv[{gt2}]], lt3] + Mom[Se[{gt1}], lt3]}}, 
 {{Su[{gt1, ct1}], conj[Su[{gt2, ct2}]], VG[{ct3, lt3}]}, 
  {(-I/2)*g3*Lam[ct3, ct2, ct1]*sumExp[j1, 1, 6, conj[ZU[gt1, j1]]*
      ZU[gt2, j1]], -Mom[conj[Su[{gt2, ct2}]], lt3] + 
    Mom[Su[{gt1, ct1}], lt3]}}, {{Su[{gt1, ct1}], conj[Su[{gt2, ct2}]], 
   VP[{lt3}]}, {(-I/6)*Delta[ct1, ct2]*((g1*Cos[ThetaW] + 3*g2*Sin[ThetaW])*
      sumExp[j1, 1, 3, conj[ZU[gt1, j1]]*ZU[gt2, j1]] + 
     4*g1*Cos[ThetaW]*sumExp[j1, 1, 3, conj[ZU[gt1, 3 + j1]]*
        ZU[gt2, 3 + j1]]), -Mom[conj[Su[{gt2, ct2}]], lt3] + 
    Mom[Su[{gt1, ct1}], lt3]}}, {{Su[{gt1, ct1}], conj[Sd[{gt2, ct2}]], 
   VWm[{lt3}]}, {((-I)*g2*Delta[ct1, ct2]*sumExp[j1, 1, 3, 
      conj[ZU[gt1, j1]]*ZD[gt2, j1]])/Sqrt[2], 
   -Mom[conj[Sd[{gt2, ct2}]], lt3] + Mom[Su[{gt1, ct1}], lt3]}}, 
 {{Su[{gt1, ct1}], conj[Su[{gt2, ct2}]], VZ[{lt3}]}, 
  {(-I/6)*Delta[ct1, ct2]*((3*g2*Cos[ThetaW] - g1*Sin[ThetaW])*
      sumExp[j1, 1, 3, conj[ZU[gt1, j1]]*ZU[gt2, j1]] - 
     4*g1*Sin[ThetaW]*sumExp[j1, 1, 3, conj[ZU[gt1, 3 + j1]]*
        ZU[gt2, 3 + j1]]), -Mom[conj[Su[{gt2, ct2}]], lt3] + 
    Mom[Su[{gt1, ct1}], lt3]}}, {{Sv[{gt1}], conj[Se[{gt2}]], VWm[{lt3}]}, 
  {((-I)*g2*sumExp[j1, 1, 3, conj[ZV[gt1, j1]]*ZE[gt2, j1]])/Sqrt[2], 
   -Mom[conj[Se[{gt2}]], lt3] + Mom[Sv[{gt1}], lt3]}}, 
 {{Sv[{gt1}], conj[Sv[{gt2}]], VZ[{lt3}]}, 
  {(-I/2)*(g2*Cos[ThetaW] + g1*Sin[ThetaW])*sumExp[j1, 1, 3, 
     conj[ZV[gt1, j1]]*ZV[gt2, j1]], -Mom[conj[Sv[{gt2}]], lt3] + 
    Mom[Sv[{gt1}], lt3]}}}
