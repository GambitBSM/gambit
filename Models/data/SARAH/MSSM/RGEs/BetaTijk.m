{{T[Yd][i1, i2], ((14*g1^2*MassB)/15 + (32*g3^2*MassG)/3 + 6*g2^2*MassWB + 
     6*trace[Adj[Yd], T[Yd]] + 2*trace[Adj[Ye], T[Ye]])*Yd[i1, i2] + 
   4*MatMul[Yd, Adj[Yd], T[Yd]][i1, i2] + 
   2*MatMul[Yd, Adj[Yu], T[Yu]][i1, i2] + 
   5*MatMul[T[Yd], Adj[Yd], Yd][i1, i2] + MatMul[T[Yd], Adj[Yu], Yu][i1, 
    i2] - (7*g1^2*T[Yd][i1, i2])/15 - 3*g2^2*T[Yd][i1, i2] - 
   (16*g3^2*T[Yd][i1, i2])/3 + 3*trace[Yd, Adj[Yd]]*T[Yd][i1, i2] + 
   trace[Ye, Adj[Ye]]*T[Yd][i1, i2], 
  (-2*(287*g1^4*MassB + 45*g1^2*g2^2*MassB + 40*g1^2*g3^2*MassB + 
      40*g1^2*g3^2*MassG + 360*g2^2*g3^2*MassG - 160*g3^4*MassG + 
      45*g1^2*g2^2*MassWB + 675*g2^4*MassWB + 360*g2^2*g3^2*MassWB - 
      18*(g1^2*MassB - 40*g3^2*MassG)*trace[Yd, Adj[Yd]] + 
      54*g1^2*MassB*trace[Ye, Adj[Ye]] + 18*g1^2*trace[Adj[Yd], T[Yd]] - 
      720*g3^2*trace[Adj[Yd], T[Yd]] - 54*g1^2*trace[Adj[Ye], T[Ye]] + 
      810*trace[Yd, Adj[Yd], T[Yd], Adj[Yd]] + 
      135*trace[Yd, Adj[Yu], T[Yu], Adj[Yd]] + 
      270*trace[Ye, Adj[Ye], T[Ye], Adj[Ye]] + 
      135*trace[Yu, Adj[Yd], T[Yd], Adj[Yu]])*Yd[i1, i2])/45 - 
   (2*(4*g1^2*MassB + 30*g2^2*MassWB + 45*trace[Adj[Yd], T[Yd]] + 
      15*trace[Adj[Ye], T[Ye]])*MatMul[Yd, Adj[Yd], Yd][i1, i2])/5 + 
   (6*g1^2*MatMul[Yd, Adj[Yd], T[Yd]][i1, i2])/5 + 
   6*g2^2*MatMul[Yd, Adj[Yd], T[Yd]][i1, i2] - 12*trace[Yd, Adj[Yd]]*
    MatMul[Yd, Adj[Yd], T[Yd]][i1, i2] - 4*trace[Ye, Adj[Ye]]*
    MatMul[Yd, Adj[Yd], T[Yd]][i1, i2] - 
   (8*g1^2*MassB*MatMul[Yd, Adj[Yu], Yu][i1, i2])/5 - 
   6*trace[Adj[Yu], T[Yu]]*MatMul[Yd, Adj[Yu], Yu][i1, i2] + 
   (8*g1^2*MatMul[Yd, Adj[Yu], T[Yu]][i1, i2])/5 - 
   6*trace[Yu, Adj[Yu]]*MatMul[Yd, Adj[Yu], T[Yu]][i1, i2] + 
   (6*g1^2*MatMul[T[Yd], Adj[Yd], Yd][i1, i2])/5 + 
   12*g2^2*MatMul[T[Yd], Adj[Yd], Yd][i1, i2] - 15*trace[Yd, Adj[Yd]]*
    MatMul[T[Yd], Adj[Yd], Yd][i1, i2] - 5*trace[Ye, Adj[Ye]]*
    MatMul[T[Yd], Adj[Yd], Yd][i1, i2] + 
   (4*g1^2*MatMul[T[Yd], Adj[Yu], Yu][i1, i2])/5 - 
   3*trace[Yu, Adj[Yu]]*MatMul[T[Yd], Adj[Yu], Yu][i1, i2] - 
   6*MatMul[Yd, Adj[Yd], Yd, Adj[Yd], T[Yd]][i1, i2] - 
   8*MatMul[Yd, Adj[Yd], T[Yd], Adj[Yd], Yd][i1, i2] - 
   2*MatMul[Yd, Adj[Yu], Yu, Adj[Yd], T[Yd]][i1, i2] - 
   4*MatMul[Yd, Adj[Yu], Yu, Adj[Yu], T[Yu]][i1, i2] - 
   4*MatMul[Yd, Adj[Yu], T[Yu], Adj[Yd], Yd][i1, i2] - 
   4*MatMul[Yd, Adj[Yu], T[Yu], Adj[Yu], Yu][i1, i2] - 
   6*MatMul[T[Yd], Adj[Yd], Yd, Adj[Yd], Yd][i1, i2] - 
   4*MatMul[T[Yd], Adj[Yu], Yu, Adj[Yd], Yd][i1, i2] - 
   2*MatMul[T[Yd], Adj[Yu], Yu, Adj[Yu], Yu][i1, i2] + 
   (287*g1^4*T[Yd][i1, i2])/90 + g1^2*g2^2*T[Yd][i1, i2] + 
   (15*g2^4*T[Yd][i1, i2])/2 + (8*g1^2*g3^2*T[Yd][i1, i2])/9 + 
   8*g2^2*g3^2*T[Yd][i1, i2] - (16*g3^4*T[Yd][i1, i2])/9 - 
   (2*g1^2*trace[Yd, Adj[Yd]]*T[Yd][i1, i2])/5 + 16*g3^2*trace[Yd, Adj[Yd]]*
    T[Yd][i1, i2] + (6*g1^2*trace[Ye, Adj[Ye]]*T[Yd][i1, i2])/5 - 
   9*trace[Yd, Adj[Yd], Yd, Adj[Yd]]*T[Yd][i1, i2] - 
   3*trace[Yd, Adj[Yu], Yu, Adj[Yd]]*T[Yd][i1, i2] - 
   3*trace[Ye, Adj[Ye], Ye, Adj[Ye]]*T[Yd][i1, i2]}, 
 {T[Ye][i1, i2], ((18*g1^2*MassB)/5 + 6*g2^2*MassWB + 
     6*trace[Adj[Yd], T[Yd]] + 2*trace[Adj[Ye], T[Ye]])*Ye[i1, i2] + 
   4*MatMul[Ye, Adj[Ye], T[Ye]][i1, i2] + 
   5*MatMul[T[Ye], Adj[Ye], Ye][i1, i2] - (9*g1^2*T[Ye][i1, i2])/5 - 
   3*g2^2*T[Ye][i1, i2] + 3*trace[Yd, Adj[Yd]]*T[Ye][i1, i2] + 
   trace[Ye, Adj[Ye]]*T[Ye][i1, i2], 
  (-2*(135*g1^4*MassB + 9*g1^2*g2^2*MassB + 9*g1^2*g2^2*MassWB + 
      75*g2^4*MassWB + (-2*g1^2*MassB + 80*g3^2*MassG)*trace[Yd, Adj[Yd]] + 
      6*g1^2*MassB*trace[Ye, Adj[Ye]] + 2*g1^2*trace[Adj[Yd], T[Yd]] - 
      80*g3^2*trace[Adj[Yd], T[Yd]] - 6*g1^2*trace[Adj[Ye], T[Ye]] + 
      90*trace[Yd, Adj[Yd], T[Yd], Adj[Yd]] + 
      15*trace[Yd, Adj[Yu], T[Yu], Adj[Yd]] + 
      30*trace[Ye, Adj[Ye], T[Ye], Adj[Ye]] + 
      15*trace[Yu, Adj[Yd], T[Yd], Adj[Yu]])*Ye[i1, i2])/5 - 
   6*(2*g2^2*MassWB + 3*trace[Adj[Yd], T[Yd]] + trace[Adj[Ye], T[Ye]])*
    MatMul[Ye, Adj[Ye], Ye][i1, i2] + 
   (6*g1^2*MatMul[Ye, Adj[Ye], T[Ye]][i1, i2])/5 + 
   6*g2^2*MatMul[Ye, Adj[Ye], T[Ye]][i1, i2] - 12*trace[Yd, Adj[Yd]]*
    MatMul[Ye, Adj[Ye], T[Ye]][i1, i2] - 4*trace[Ye, Adj[Ye]]*
    MatMul[Ye, Adj[Ye], T[Ye]][i1, i2] - 
   (6*g1^2*MatMul[T[Ye], Adj[Ye], Ye][i1, i2])/5 + 
   12*g2^2*MatMul[T[Ye], Adj[Ye], Ye][i1, i2] - 15*trace[Yd, Adj[Yd]]*
    MatMul[T[Ye], Adj[Ye], Ye][i1, i2] - 5*trace[Ye, Adj[Ye]]*
    MatMul[T[Ye], Adj[Ye], Ye][i1, i2] - 
   6*MatMul[Ye, Adj[Ye], Ye, Adj[Ye], T[Ye]][i1, i2] - 
   8*MatMul[Ye, Adj[Ye], T[Ye], Adj[Ye], Ye][i1, i2] - 
   6*MatMul[T[Ye], Adj[Ye], Ye, Adj[Ye], Ye][i1, i2] + 
   (27*g1^4*T[Ye][i1, i2])/2 + (9*g1^2*g2^2*T[Ye][i1, i2])/5 + 
   (15*g2^4*T[Ye][i1, i2])/2 - (2*g1^2*trace[Yd, Adj[Yd]]*T[Ye][i1, i2])/5 + 
   16*g3^2*trace[Yd, Adj[Yd]]*T[Ye][i1, i2] + 
   (6*g1^2*trace[Ye, Adj[Ye]]*T[Ye][i1, i2])/5 - 
   9*trace[Yd, Adj[Yd], Yd, Adj[Yd]]*T[Ye][i1, i2] - 
   3*trace[Yd, Adj[Yu], Yu, Adj[Yd]]*T[Ye][i1, i2] - 
   3*trace[Ye, Adj[Ye], Ye, Adj[Ye]]*T[Ye][i1, i2]}, 
 {T[Yu][i1, i2], ((26*g1^2*MassB)/15 + (32*g3^2*MassG)/3 + 6*g2^2*MassWB + 
     6*trace[Adj[Yu], T[Yu]])*Yu[i1, i2] + 
   2*MatMul[Yu, Adj[Yd], T[Yd]][i1, i2] + 
   4*MatMul[Yu, Adj[Yu], T[Yu]][i1, i2] + MatMul[T[Yu], Adj[Yd], Yd][i1, 
    i2] + 5*MatMul[T[Yu], Adj[Yu], Yu][i1, i2] - (13*g1^2*T[Yu][i1, i2])/15 - 
   3*g2^2*T[Yu][i1, i2] - (16*g3^2*T[Yu][i1, i2])/3 + 
   3*trace[Yu, Adj[Yu]]*T[Yu][i1, i2], 
  (-2*(2743*g1^4*MassB + 225*g1^2*g2^2*MassB + 680*g1^2*g3^2*MassB + 
      680*g1^2*g3^2*MassG + 1800*g2^2*g3^2*MassG - 800*g3^4*MassG + 
      225*g1^2*g2^2*MassWB + 3375*g2^4*MassWB + 1800*g2^2*g3^2*MassWB + 
      180*(g1^2*MassB + 20*g3^2*MassG)*trace[Yu, Adj[Yu]] - 
      180*(g1^2 + 20*g3^2)*trace[Adj[Yu], T[Yu]] + 
      675*trace[Yd, Adj[Yu], T[Yu], Adj[Yd]] + 
      675*trace[Yu, Adj[Yd], T[Yd], Adj[Yu]] + 
      4050*trace[Yu, Adj[Yu], T[Yu], Adj[Yu]])*Yu[i1, i2])/225 - 
   (2*(2*g1^2*MassB + 15*trace[Adj[Yd], T[Yd]] + 5*trace[Adj[Ye], T[Ye]])*
     MatMul[Yu, Adj[Yd], Yd][i1, i2])/5 + 
   (4*g1^2*MatMul[Yu, Adj[Yd], T[Yd]][i1, i2])/5 - 
   6*trace[Yd, Adj[Yd]]*MatMul[Yu, Adj[Yd], T[Yd]][i1, i2] - 
   2*trace[Ye, Adj[Ye]]*MatMul[Yu, Adj[Yd], T[Yd]][i1, i2] - 
   (4*g1^2*MassB*MatMul[Yu, Adj[Yu], Yu][i1, i2])/5 - 
   12*g2^2*MassWB*MatMul[Yu, Adj[Yu], Yu][i1, i2] - 
   18*trace[Adj[Yu], T[Yu]]*MatMul[Yu, Adj[Yu], Yu][i1, i2] + 
   (6*g1^2*MatMul[Yu, Adj[Yu], T[Yu]][i1, i2])/5 + 
   6*g2^2*MatMul[Yu, Adj[Yu], T[Yu]][i1, i2] - 12*trace[Yu, Adj[Yu]]*
    MatMul[Yu, Adj[Yu], T[Yu]][i1, i2] + 
   (2*g1^2*MatMul[T[Yu], Adj[Yd], Yd][i1, i2])/5 - 
   3*trace[Yd, Adj[Yd]]*MatMul[T[Yu], Adj[Yd], Yd][i1, i2] - 
   trace[Ye, Adj[Ye]]*MatMul[T[Yu], Adj[Yd], Yd][i1, i2] + 
   12*g2^2*MatMul[T[Yu], Adj[Yu], Yu][i1, i2] - 15*trace[Yu, Adj[Yu]]*
    MatMul[T[Yu], Adj[Yu], Yu][i1, i2] - 
   4*MatMul[Yu, Adj[Yd], Yd, Adj[Yd], T[Yd]][i1, i2] - 
   2*MatMul[Yu, Adj[Yd], Yd, Adj[Yu], T[Yu]][i1, i2] - 
   4*MatMul[Yu, Adj[Yd], T[Yd], Adj[Yd], Yd][i1, i2] - 
   4*MatMul[Yu, Adj[Yd], T[Yd], Adj[Yu], Yu][i1, i2] - 
   6*MatMul[Yu, Adj[Yu], Yu, Adj[Yu], T[Yu]][i1, i2] - 
   8*MatMul[Yu, Adj[Yu], T[Yu], Adj[Yu], Yu][i1, i2] - 
   2*MatMul[T[Yu], Adj[Yd], Yd, Adj[Yd], Yd][i1, i2] - 
   4*MatMul[T[Yu], Adj[Yd], Yd, Adj[Yu], Yu][i1, i2] - 
   6*MatMul[T[Yu], Adj[Yu], Yu, Adj[Yu], Yu][i1, i2] + 
   (2743*g1^4*T[Yu][i1, i2])/450 + g1^2*g2^2*T[Yu][i1, i2] + 
   (15*g2^4*T[Yu][i1, i2])/2 + (136*g1^2*g3^2*T[Yu][i1, i2])/45 + 
   8*g2^2*g3^2*T[Yu][i1, i2] - (16*g3^4*T[Yu][i1, i2])/9 + 
   (4*g1^2*trace[Yu, Adj[Yu]]*T[Yu][i1, i2])/5 + 16*g3^2*trace[Yu, Adj[Yu]]*
    T[Yu][i1, i2] - 3*trace[Yd, Adj[Yu], Yu, Adj[Yd]]*T[Yu][i1, i2] - 
   9*trace[Yu, Adj[Yu], Yu, Adj[Yu]]*T[Yu][i1, i2]}}
