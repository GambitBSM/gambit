(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.13.0  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 14:01 on 29.10.2018  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[TreeVdulv]={
(*VZ*) 
{{VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][gt2,gt1],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][gt2,gt1],coup2L -> Cp[bar[Fe], Fv, VWm][L][gt4,gt3],coup2R -> Cp[bar[Fe], Fv, VWm][R][gt4,gt3]},{MP -> M[VWm]}  {TVOdulvSLL,0},   {TVOdulvSRR,0},   {TVOdulvSRL,0},   {TVOdulvSLR,0}   {TVOdulvVRR,coup1R*coup2L*IMP2}   {TVOdulvVLL,coup1L*coup2R*IMP2}   {TVOdulvVRL,coup1R*coup2R*IMP2}   {TVOdulvVLR,coup1L*coup2L*IMP2} }
};