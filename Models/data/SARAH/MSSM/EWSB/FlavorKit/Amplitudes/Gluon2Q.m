(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.8.1  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 15:03 on 22.11.2017  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[Gluon2Q]={
chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VG][L][gt1,gt2],coup1R -> Cp[bar[Fd], Fd, VG][R][gt1,gt2]},}
(* Ah,bar[Fd], Internal:Fd*) 
{{Ah,bar[Fd],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fd, Ah][R][gt1,i2,i1],coup2L -> Cp[bar[Fd], Fd, Ah][L][i2,i3,i1],coup2R -> Cp[bar[Fd], Fd, Ah][R][i2,i3,i1],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mS1 -> M[Ah][i1],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Cha,conj[Su], Internal:Fd*) 
{{Cha,conj[Su],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Cha, Su][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Cha, Su][R][gt1,i1,i2],coup2L -> Cp[bar[Cha], Fd, conj[Su]][L][i1,i3,i2],coup2R -> Cp[bar[Cha], Fd, conj[Su]][R][i1,i3,i2],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Cha][i1],mS1 -> M[Su][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Chi,conj[Sd], Internal:Fd*) 
{{Chi,conj[Sd],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Chi, Sd][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Chi, Sd][R][gt1,i1,i2],coup2L -> Cp[Chi, Fd, conj[Sd]][L][i1,i3,i2],coup2R -> Cp[Chi, Fd, conj[Sd]][R][i1,i3,i2],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Chi][i1],mS1 -> M[Sd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,hh, Internal:Fd*) 
{{Fd,hh,Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Fd, hh][R][gt1,i1,i2],coup2L -> Cp[bar[Fd], Fd, hh][L][i1,i3,i2],coup2R -> Cp[bar[Fd], Fd, hh][R][i1,i3,i2],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Fd][i1],mS1 -> M[hh][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,VG, Internal:Fd*) 
{{Fd,VG,Internal->Fd},chargefactor -> 4/3,{coup1L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i1]],coup1R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i1]],coup2L -> conj[Cp[bar[Fd], Fd, VG][L][i1,i3]],coup2R -> conj[Cp[bar[Fd], Fd, VG][R][i1,i3]],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Fd][i1],mV1 -> 0,MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,VP, Internal:Fd*) 
{{Fd,VP,Internal->Fd},chargefactor -> 1,{coup1L -> conj[Cp[bar[Fd], Fd, VP][L][gt1,i1]],coup1R -> conj[Cp[bar[Fd], Fd, VP][R][gt1,i1]],coup2L -> conj[Cp[bar[Fd], Fd, VP][L][i1,i3]],coup2R -> conj[Cp[bar[Fd], Fd, VP][R][i1,i3]],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Fd][i1],mV1 -> 0,MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,VZ, Internal:Fd*) 
{{Fd,VZ,Internal->Fd},chargefactor -> 1,{coup1L -> conj[Cp[bar[Fd], Fd, VZ][L][gt1,i1]],coup1R -> conj[Cp[bar[Fd], Fd, VZ][R][gt1,i1]],coup2L -> conj[Cp[bar[Fd], Fd, VZ][L][i1,i3]],coup2R -> conj[Cp[bar[Fd], Fd, VZ][R][i1,i3]],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Fd][i1],mV1 -> M[VZ],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fu,conj[Hpm], Internal:Fd*) 
{{Fu,conj[Hpm],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fu, Hpm][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Fu, Hpm][R][gt1,i1,i2],coup2L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,i3,i2],coup2R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,i3,i2],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Fu][i1],mS1 -> M[Hpm][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fu,conj[VWm], Internal:Fd*) 
{{Fu,conj[VWm],Internal->Fd},chargefactor -> 1,{coup1L -> conj[Cp[bar[Fd], Fu, VWm][L][gt1,i1]],coup1R -> conj[Cp[bar[Fd], Fu, VWm][R][gt1,i1]],coup2L -> conj[Cp[bar[Fu], Fd, conj[VWm]][L][i1,i3]],coup2R -> conj[Cp[bar[Fu], Fd, conj[VWm]][R][i1,i3]],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Fu][i1],mV1 -> M[VWm],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Glu,conj[Sd], Internal:Fd*) 
{{Glu,conj[Sd],Internal->Fd},chargefactor -> 4/3,{coup1L -> Cp[bar[Fd], Glu, Sd][L][gt1,i2],coup1R -> Cp[bar[Fd], Glu, Sd][R][gt1,i2],coup2L -> Cp[Glu, Fd, conj[Sd]][L][i3,i2],coup2R -> Cp[Glu, Fd, conj[Sd]][R][i3,i2],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i3,gt2]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i3,gt2]]},{mF1 -> M[Glu],mS1 -> M[Sd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* bar[Fd],Ah, Internal:bar[Fd]*) 
{{bar[Fd],Ah,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> Cp[bar[Fd], Fd, Ah][L][i3,i1,i2],coup2R -> Cp[bar[Fd], Fd, Ah][R][i3,i1,i2],coup1L -> Cp[bar[Fd], Fd, Ah][L][i1,gt2,i2],coup1R -> Cp[bar[Fd], Fd, Ah][R][i1,gt2,i2]},{mF1 -> M[Fd][i1],mS1 -> M[Ah][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[Su],Cha, Internal:bar[Fd]*) 
{{conj[Su],Cha,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> Cp[bar[Fd], Cha, Su][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Cha, Su][R][i3,i2,i1],coup1L -> Cp[bar[Cha], Fd, conj[Su]][L][i2,gt2,i1],coup1R -> Cp[bar[Cha], Fd, conj[Su]][R][i2,gt2,i1]},{mS1 -> M[Su][i1],mF1 -> M[Cha][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[Sd],Chi, Internal:bar[Fd]*) 
{{conj[Sd],Chi,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> Cp[bar[Fd], Chi, Sd][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Chi, Sd][R][i3,i2,i1],coup1L -> Cp[Chi, Fd, conj[Sd]][L][i2,gt2,i1],coup1R -> Cp[Chi, Fd, conj[Sd]][R][i2,gt2,i1]},{mS1 -> M[Sd][i1],mF1 -> M[Chi][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* hh,Fd, Internal:bar[Fd]*) 
{{hh,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> Cp[bar[Fd], Fd, hh][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Fd, hh][R][i3,i2,i1],coup1L -> Cp[bar[Fd], Fd, hh][L][i2,gt2,i1],coup1R -> Cp[bar[Fd], Fd, hh][R][i2,gt2,i1]},{mS1 -> M[hh][i1],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* VG,Fd, Internal:bar[Fd]*) 
{{VG,Fd,Internal->bar[Fd]},chargefactor -> 4/3,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> conj[Cp[bar[Fd], Fd, VG][L][i3,i2]],coup2R -> conj[Cp[bar[Fd], Fd, VG][R][i3,i2]],coup1L -> conj[Cp[bar[Fd], Fd, VG][L][i2,gt2]],coup1R -> conj[Cp[bar[Fd], Fd, VG][R][i2,gt2]]},{mV1 -> 0,mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* VP,Fd, Internal:bar[Fd]*) 
{{VP,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> conj[Cp[bar[Fd], Fd, VP][L][i3,i2]],coup2R -> conj[Cp[bar[Fd], Fd, VP][R][i3,i2]],coup1L -> conj[Cp[bar[Fd], Fd, VP][L][i2,gt2]],coup1R -> conj[Cp[bar[Fd], Fd, VP][R][i2,gt2]]},{mV1 -> 0,mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* VZ,Fd, Internal:bar[Fd]*) 
{{VZ,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> conj[Cp[bar[Fd], Fd, VZ][L][i3,i2]],coup2R -> conj[Cp[bar[Fd], Fd, VZ][R][i3,i2]],coup1L -> conj[Cp[bar[Fd], Fd, VZ][L][i2,gt2]],coup1R -> conj[Cp[bar[Fd], Fd, VZ][R][i2,gt2]]},{mV1 -> M[VZ],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[Hpm],Fu, Internal:bar[Fd]*) 
{{conj[Hpm],Fu,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> Cp[bar[Fd], Fu, Hpm][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Fu, Hpm][R][i3,i2,i1],coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i2,gt2,i1],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i2,gt2,i1]},{mS1 -> M[Hpm][i1],mF1 -> M[Fu][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[VWm],Fu, Internal:bar[Fd]*) 
{{conj[VWm],Fu,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> conj[Cp[bar[Fd], Fu, VWm][L][i3,i2]],coup2R -> conj[Cp[bar[Fd], Fu, VWm][R][i3,i2]],coup1L -> conj[Cp[bar[Fu], Fd, conj[VWm]][L][i2,gt2]],coup1R -> conj[Cp[bar[Fu], Fd, conj[VWm]][R][i2,gt2]]},{mV1 -> M[VWm],mF1 -> M[Fu][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[Sd],Glu, Internal:bar[Fd]*) 
{{conj[Sd],Glu,Internal->bar[Fd]},chargefactor -> 4/3,{coup3L -> conj[Cp[bar[Fd], Fd, VG][L][gt1,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][gt1,i3]],coup2L -> Cp[bar[Fd], Glu, Sd][L][i3,i1],coup2R -> Cp[bar[Fd], Glu, Sd][R][i3,i1],coup1L -> Cp[Glu, Fd, conj[Sd]][L][gt2,i1],coup1R -> Cp[Glu, Fd, conj[Sd]][R][gt2,i1]},{mS1 -> M[Sd][i1],mF1 -> M[Glu],MFin -> M[Fd][i3]-M[Fd][gt2]}}
(* Ah,bar[Fd],bar[Fd]*) 
{{Ah,bar[Fd],bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fd, Ah][R][gt1,i2,i1],coup2L -> Cp[bar[Fd], Fd, Ah][L][i3,gt2,i1],coup2R -> Cp[bar[Fd], Fd, Ah][R][i3,gt2,i1],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i2,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i2,i3]]},},
(* Cha,conj[Su],conj[Su]*) 
{{Cha,conj[Su],conj[Su]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Cha, Su][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Cha, Su][R][gt1,i1,i2],coup2L -> Cp[bar[Cha], Fd, conj[Su]][L][i1,gt2,i3],coup2R -> Cp[bar[Cha], Fd, conj[Su]][R][i1,gt2,i3],coup3 -> Cp[Su, conj[Su], VG][i3,i2]},},
(* Chi,conj[Sd],conj[Sd]*) 
{{Chi,conj[Sd],conj[Sd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Chi, Sd][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Chi, Sd][R][gt1,i1,i2],coup2L -> Cp[Chi, Fd, conj[Sd]][L][i1,gt2,i3],coup2R -> Cp[Chi, Fd, conj[Sd]][R][i1,gt2,i3],coup3 -> Cp[Sd, conj[Sd], VG][i3,i2]},},
(* Glu,conj[Sd],conj[Sd]*) 
{{Glu,conj[Sd],conj[Sd]},chargefactor -> -1/6,{coup1L -> Cp[bar[Fd], Glu, Sd][L][gt1,i2],coup1R -> Cp[bar[Fd], Glu, Sd][R][gt1,i2],coup2L -> Cp[Glu, Fd, conj[Sd]][L][gt2,i3],coup2R -> Cp[Glu, Fd, conj[Sd]][R][gt2,i3],coup3 -> Cp[Sd, conj[Sd], VG][i3,i2]},},
(* hh,bar[Fd],bar[Fd]*) 
{{hh,bar[Fd],bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fd, hh][R][gt1,i2,i1],coup2L -> Cp[bar[Fd], Fd, hh][L][i3,gt2,i1],coup2R -> Cp[bar[Fd], Fd, hh][R][i3,gt2,i1],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i2,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i2,i3]]},},
(* Hpm,bar[Fu],bar[Fu]*) 
{{Hpm,bar[Fu],bar[Fu]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fu, Hpm][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fu, Hpm][R][gt1,i2,i1],coup2L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i3,gt2,i1],coup2R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i3,gt2,i1],coup3L -> conj[Cp[bar[Fu], Fu, VG][L][i2,i3]],coup3R -> conj[Cp[bar[Fu], Fu, VG][R][i2,i3]]},},
(* Sd,Glu,Glu*) 
{{Sd,Glu,Glu},chargefactor -> (3*I)/2,{coup1L -> Cp[bar[Fd], Glu, Sd][L][gt1,i1],coup1R -> Cp[bar[Fd], Glu, Sd][R][gt1,i1],coup2L -> Cp[Glu, Fd, conj[Sd]][L][gt2,i1],coup2R -> Cp[Glu, Fd, conj[Sd]][R][gt2,i1],coup3L -> Cp[Glu, Glu, VG][L],coup3R -> Cp[Glu, Glu, VG][R]},},
(* VWm,bar[Fu],bar[Fu]*) 
{{VWm,bar[Fu],bar[Fu]},chargefactor -> 1,{coup1L -> conj[Cp[bar[Fd], Fu, VWm][L][gt1,i2]],coup1R -> conj[Cp[bar[Fd], Fu, VWm][R][gt1,i2]],coup2L -> conj[Cp[bar[Fu], Fd, conj[VWm]][L][i3,gt2]],coup2R -> conj[Cp[bar[Fu], Fd, conj[VWm]][R][i3,gt2]],coup3L -> conj[Cp[bar[Fu], Fu, VG][L][i2,i3]],coup3R -> conj[Cp[bar[Fu], Fu, VG][R][i2,i3]]},},
(* VZ,bar[Fd],bar[Fd]*) 
{{VZ,bar[Fd],bar[Fd]},chargefactor -> 1,{coup1L -> conj[Cp[bar[Fd], Fd, VZ][L][gt1,i2]],coup1R -> conj[Cp[bar[Fd], Fd, VZ][R][gt1,i2]],coup2L -> conj[Cp[bar[Fd], Fd, VZ][L][i3,gt2]],coup2R -> conj[Cp[bar[Fd], Fd, VZ][R][i3,gt2]],coup3L -> conj[Cp[bar[Fd], Fd, VG][L][i2,i3]],coup3R -> conj[Cp[bar[Fd], Fd, VG][R][i2,i3]]},}
};