(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.8.1  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 15:02 on 22.11.2017  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[TreeV2d2L]={
(*VZ*) 
{{VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][gt2,gt1],coup1R -> Cp[bar[Fd], Fd, VZ][R][gt2,gt1],coup2L -> Cp[bar[Fe], Fe, VZ][L][gt4,gt3],coup2R -> Cp[bar[Fe], Fe, VZ][R][gt4,gt3]},{MP -> M[VZ]}  {TVOddllSLL,0},   {TVOddllSRR,0},   {TVOddllSRL,0},   {TVOddllSLR,0}   {TVOddllVRR,-(coup1R*coup2R*IMP2)}   {TVOddllVLL,-(coup1L*coup2L*IMP2)}   {TVOddllVRL,-(coup1R*coup2L*IMP2)}   {TVOddllVLR,-(coup1L*coup2R*IMP2)}   {TVOddllTLL,0}   {TVOddllTLR,0}   {TVOddllTRL,0}   {TVOddllTRR,0} }
};