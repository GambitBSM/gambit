(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.8.1  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 15:02 on 22.11.2017  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[TreeV4Lcross]={
(*VZ*) 
{{VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fe], Fe, VZ][L][gt2,gt1],coup1R -> Cp[bar[Fe], Fe, VZ][R][gt2,gt1],coup2L -> Cp[bar[Fe], Fe, VZ][L][gt4,gt3],coup2R -> Cp[bar[Fe], Fe, VZ][R][gt4,gt3]},{MP -> M[VZ]}  {TVO4lSLLcross,0},   {TVO4lSRRcross,0},   {TVO4lSRLcross,0},   {TVO4lSLRcross,0}   {TVO4lVRRcross,-(coup1R*coup2R*IMP2)}   {TVO4lVLLcross,-(coup1L*coup2L*IMP2)}   {TVO4lVRLcross,-(coup1R*coup2L*IMP2)}   {TVO4lVLRcross,-(coup1L*coup2R*IMP2)}   {TVO4lTLLcross,0}   {TVO4lTLRcross,0}   {TVO4lTRLcross,0}   {TVO4lTRRcross,0} },
(*VZ*) 
{{VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fe], Fe, VZ][L][gt4,gt1],coup1R -> Cp[bar[Fe], Fe, VZ][R][gt4,gt1],coup2L -> Cp[bar[Fe], Fe, VZ][L][gt2,gt3],coup2R -> Cp[bar[Fe], Fe, VZ][R][gt2,gt3]},{MP -> M[VZ]}  {TVO4lSLLcross,0},   {TVO4lSRRcross,0},   {TVO4lSRLcross,2*coup1R*coup2L*IMP2},   {TVO4lSLRcross,2*coup1L*coup2R*IMP2}   {TVO4lVRRcross,-(coup1R*coup2R*IMP2)}   {TVO4lVLLcross,-(coup1L*coup2L*IMP2)}   {TVO4lVRLcross,0}   {TVO4lVLRcross,0}   {TVO4lTLLcross,0}   {TVO4lTLRcross,0}   {TVO4lTRLcross,0}   {TVO4lTRRcross,0} }
};