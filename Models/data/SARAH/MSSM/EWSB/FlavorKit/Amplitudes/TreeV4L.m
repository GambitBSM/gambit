(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.8.1  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 15:02 on 22.11.2017  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[TreeV4L]={
(*VZ*) 
{{VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fe], Fe, VZ][L][gt2,gt1],coup1R -> Cp[bar[Fe], Fe, VZ][R][gt2,gt1],coup2L -> Cp[bar[Fe], Fe, VZ][L][gt4,gt3],coup2R -> Cp[bar[Fe], Fe, VZ][R][gt4,gt3]},{MP -> M[VZ]}  {TVO4lSLL,0},   {TVO4lSRR,0},   {TVO4lSRL,0},   {TVO4lSLR,0}   {TVO4lVRR,-(coup1R*coup2R*IMP2)}   {TVO4lVLL,-(coup1L*coup2L*IMP2)}   {TVO4lVRL,-(coup1R*coup2L*IMP2)}   {TVO4lVLR,-(coup1L*coup2R*IMP2)}   {TVO4lTLL,0}   {TVO4lTLR,0}   {TVO4lTRL,0}   {TVO4lTRR,0} }
};