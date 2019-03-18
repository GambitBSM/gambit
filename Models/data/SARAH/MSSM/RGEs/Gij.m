{{{Sq[{lef1}][{gen1, col1}], Sq[{lef2}][{gen2, col2}]}, 
  -((g1^2 + 45*g2^2 + 80*g3^2)*Kronecker[i1, i2])/30 + 
   MatMul[Adj[Yd], Yd][i1, i2] + MatMul[Adj[Yu], Yu][i1, i2], 
  ((199*g1^4)/900 + (15*g2^4)/4 + 8*g2^2*g3^2 - (8*g3^4)/9 + 
     (g1^2*(9*g2^2 + 16*g3^2))/90)*Kronecker[i1, i2] + 
   ((2*g1^2)/5 - 3*trace[Yd, Adj[Yd]] - trace[Ye, Adj[Ye]])*
    MatMul[Adj[Yd], Yd][i1, i2] + (4*g1^2*MatMul[Adj[Yu], Yu][i1, i2])/5 - 
   3*trace[Yu, Adj[Yu]]*MatMul[Adj[Yu], Yu][i1, i2] - 
   2*MatMul[Adj[Yd], Yd, Adj[Yd], Yd][i1, i2] - 
   2*MatMul[Adj[Yu], Yu, Adj[Yu], Yu][i1, i2]}, 
 {{Sl[{lef1}][{gen1}], Sl[{lef2}][{gen2}]}, 
  (-3*(g1^2 + 5*g2^2)*Kronecker[i1, i2])/10 + MatMul[Adj[Ye], Ye][i1, i2], 
  (3*(69*g1^4 + 30*g1^2*g2^2 + 125*g2^4)*Kronecker[i1, i2])/100 + 
   ((6*g1^2)/5 - 3*trace[Yd, Adj[Yd]] - trace[Ye, Adj[Ye]])*
    MatMul[Adj[Ye], Ye][i1, i2] - 2*MatMul[Adj[Ye], Ye, Adj[Ye], Ye][i1, 
     i2]}, {{SHd[{lef1}][{gen1}], SHd[{lef2}][{gen2}]}, 
  (-3*(g1^2 + 5*g2^2))/10 + 3*trace[Yd, Adj[Yd]] + trace[Ye, Adj[Ye]], 
  (207*g1^4)/100 + (9*g1^2*g2^2)/10 + (15*g2^4)/4 - 
   (2*(g1^2 - 40*g3^2)*trace[Yd, Adj[Yd]])/5 + (6*g1^2*trace[Ye, Adj[Ye]])/
    5 - 9*trace[Yd, Adj[Yd], Yd, Adj[Yd]] - 
   3*trace[Yd, Adj[Yu], Yu, Adj[Yd]] - 3*trace[Ye, Adj[Ye], Ye, Adj[Ye]]}, 
 {{SHu[{lef1}][{gen1}], SHu[{lef2}][{gen2}]}, 
  (-3*(g1^2 + 5*g2^2 - 10*trace[Yu, Adj[Yu]]))/10, 
  (207*g1^4)/100 + (9*g1^2*g2^2)/10 + (15*g2^4)/4 + 
   (4*(g1^2 + 20*g3^2)*trace[Yu, Adj[Yu]])/5 - 
   3*trace[Yd, Adj[Yu], Yu, Adj[Yd]] - 9*trace[Yu, Adj[Yu], Yu, Adj[Yu]]}, 
 {{SdR[{gen1, col1}], SdR[{gen2, col2}]}, 
  (-2*(g1^2 + 20*g3^2)*Kronecker[i1, i2])/15 + 
   2*MatMul[conj[Yd], Tp[Yd]][i1, i2], 
  (2*(101*g1^4 + 80*g1^2*g3^2 - 100*g3^4)*Kronecker[i1, i2])/225 + 
   ((2*g1^2)/5 + 6*g2^2 - 6*trace[Yd, Adj[Yd]] - 2*trace[Ye, Adj[Ye]])*
    MatMul[conj[Yd], Tp[Yd]][i1, i2] - 
   2*(MatMul[conj[Yd], Tp[Yd], conj[Yd], Tp[Yd]][i1, i2] + 
     MatMul[conj[Yd], Tp[Yu], conj[Yu], Tp[Yd]][i1, i2])}, 
 {{SuR[{gen1, col1}], SuR[{gen2, col2}]}, 
  (-8*(g1^2 + 5*g3^2)*Kronecker[i1, i2])/15 + 
   2*MatMul[conj[Yu], Tp[Yu]][i1, i2], 
  (8*(107*g1^4 + 80*g1^2*g3^2 - 25*g3^4)*Kronecker[i1, i2])/225 + 
   ((-2*g1^2)/5 + 6*g2^2 - 6*trace[Yu, Adj[Yu]])*MatMul[conj[Yu], Tp[Yu]][i1, 
     i2] - 2*(MatMul[conj[Yu], Tp[Yd], conj[Yd], Tp[Yu]][i1, i2] + 
     MatMul[conj[Yu], Tp[Yu], conj[Yu], Tp[Yu]][i1, i2])}, 
 {{SeR[{gen1}], SeR[{gen2}]}, (-6*g1^2*Kronecker[i1, i2])/5 + 
   2*MatMul[conj[Ye], Tp[Ye]][i1, i2], (234*g1^4*Kronecker[i1, i2])/25 + 
   ((-6*g1^2)/5 + 6*g2^2 - 6*trace[Yd, Adj[Yd]] - 2*trace[Ye, Adj[Ye]])*
    MatMul[conj[Ye], Tp[Ye]][i1, i2] - 
   2*MatMul[conj[Ye], Tp[Ye], conj[Ye], Tp[Ye]][i1, i2]}}
