(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.8.1  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 15:03 on 22.11.2017  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[A2q]={
chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][gt2,gt1,gt3],coup1R -> Cp[bar[Fd], Fd, Ah][R][gt2,gt1,gt3]},}
(* Ah,Fd, Internal:bar[Fd]*) 
{{Ah,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][i2,gt1,i1],coup1R -> Cp[bar[Fd], Fd, Ah][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Fd, Ah][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Fd, Ah][R][i3,i2,i1],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mS1 -> M[Ah][i1],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Chi,Sd, Internal:bar[Fd]*) 
{{Chi,Sd,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[Chi, Fd, conj[Sd]][L][i1,gt1,i2],coup1R -> Cp[Chi, Fd, conj[Sd]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Chi, Sd][L][i3,i1,i2],coup2R -> Cp[bar[Fd], Chi, Sd][R][i3,i1,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mF1 -> M[Chi][i1],mS1 -> M[Sd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Glu,Sd, Internal:bar[Fd]*) 
{{Glu,Sd,Internal->bar[Fd]},chargefactor -> 4/3,{coup1L -> Cp[Glu, Fd, conj[Sd]][L][gt1,i2],coup1R -> Cp[Glu, Fd, conj[Sd]][R][gt1,i2],coup2L -> Cp[bar[Fd], Glu, Sd][L][i3,i2],coup2R -> Cp[bar[Fd], Glu, Sd][R][i3,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mF1 -> M[Glu],mS1 -> M[Sd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* hh,Fd, Internal:bar[Fd]*) 
{{hh,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][i2,gt1,i1],coup1R -> Cp[bar[Fd], Fd, hh][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Fd, hh][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Fd, hh][R][i3,i2,i1],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mS1 -> M[hh][i1],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* VG,Fd, Internal:bar[Fd]*) 
{{VG,Fd,Internal->bar[Fd]},chargefactor -> 4/3,{coup1L -> Cp[bar[Fd], Fd, VG][L][i2,gt1],coup1R -> Cp[bar[Fd], Fd, VG][R][i2,gt1],coup2L -> Cp[bar[Fd], Fd, VG][L][i3,i2],coup2R -> Cp[bar[Fd], Fd, VG][R][i3,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mV1 -> 0,mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* VP,Fd, Internal:bar[Fd]*) 
{{VP,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VP][L][i2,gt1],coup1R -> Cp[bar[Fd], Fd, VP][R][i2,gt1],coup2L -> Cp[bar[Fd], Fd, VP][L][i3,i2],coup2R -> Cp[bar[Fd], Fd, VP][R][i3,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mV1 -> 0,mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* VZ,Fd, Internal:bar[Fd]*) 
{{VZ,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][i2,gt1],coup1R -> Cp[bar[Fd], Fd, VZ][R][i2,gt1],coup2L -> Cp[bar[Fd], Fd, VZ][L][i3,i2],coup2R -> Cp[bar[Fd], Fd, VZ][R][i3,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mV1 -> M[VZ],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* bar[Cha],Su, Internal:bar[Fd]*) 
{{bar[Cha],Su,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Cha], Fd, conj[Su]][L][i1,gt1,i2],coup1R -> Cp[bar[Cha], Fd, conj[Su]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Cha, Su][L][i3,i1,i2],coup2R -> Cp[bar[Fd], Cha, Su][R][i3,i1,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mF1 -> M[Cha][i1],mS1 -> M[Su][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* bar[Fu],Hpm, Internal:bar[Fd]*) 
{{bar[Fu],Hpm,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,gt1,i2],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Fu, Hpm][L][i3,i1,i2],coup2R -> Cp[bar[Fd], Fu, Hpm][R][i3,i1,i2],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mF1 -> M[Fu][i1],mS1 -> M[Hpm][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* bar[Fu],VWm, Internal:bar[Fd]*) 
{{bar[Fu],VWm,Internal->bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][i1,gt1],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][i1,gt1],coup2L -> Cp[bar[Fd], Fu, VWm][L][i3,i1],coup2R -> Cp[bar[Fd], Fu, VWm][R][i3,i1],coup3L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,gt3]},{mF1 -> M[Fu][i1],mV1 -> M[VWm],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,Ah, Internal:Fd*) 
{{Fd,Ah,Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fd], Fd, Ah][L][i1,i3,i2],coup2R -> Cp[bar[Fd], Fd, Ah][R][i1,i3,i2],coup1L -> Cp[bar[Fd], Fd, Ah][L][gt2,i1,i2],coup1R -> Cp[bar[Fd], Fd, Ah][R][gt2,i1,i2]},{mF1 -> M[Fd][i1],mS1 -> M[Ah][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Sd,Chi, Internal:Fd*) 
{{Sd,Chi,Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[Chi, Fd, conj[Sd]][L][i2,i3,i1],coup2R -> Cp[Chi, Fd, conj[Sd]][R][i2,i3,i1],coup1L -> Cp[bar[Fd], Chi, Sd][L][gt2,i2,i1],coup1R -> Cp[bar[Fd], Chi, Sd][R][gt2,i2,i1]},{mS1 -> M[Sd][i1],mF1 -> M[Chi][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Sd,Glu, Internal:Fd*) 
{{Sd,Glu,Internal->Fd},chargefactor -> 4/3,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[Glu, Fd, conj[Sd]][L][i3,i1],coup2R -> Cp[Glu, Fd, conj[Sd]][R][i3,i1],coup1L -> Cp[bar[Fd], Glu, Sd][L][gt2,i1],coup1R -> Cp[bar[Fd], Glu, Sd][R][gt2,i1]},{mS1 -> M[Sd][i1],mF1 -> M[Glu],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Fd,hh, Internal:Fd*) 
{{Fd,hh,Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fd], Fd, hh][L][i1,i3,i2],coup2R -> Cp[bar[Fd], Fd, hh][R][i1,i3,i2],coup1L -> Cp[bar[Fd], Fd, hh][L][gt2,i1,i2],coup1R -> Cp[bar[Fd], Fd, hh][R][gt2,i1,i2]},{mF1 -> M[Fd][i1],mS1 -> M[hh][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Fd,VG, Internal:Fd*) 
{{Fd,VG,Internal->Fd},chargefactor -> 4/3,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fd], Fd, VG][L][i1,i3],coup2R -> Cp[bar[Fd], Fd, VG][R][i1,i3],coup1L -> Cp[bar[Fd], Fd, VG][L][gt2,i1],coup1R -> Cp[bar[Fd], Fd, VG][R][gt2,i1]},{mF1 -> M[Fd][i1],mV1 -> 0,MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Fd,VP, Internal:Fd*) 
{{Fd,VP,Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fd], Fd, VP][L][i1,i3],coup2R -> Cp[bar[Fd], Fd, VP][R][i1,i3],coup1L -> Cp[bar[Fd], Fd, VP][L][gt2,i1],coup1R -> Cp[bar[Fd], Fd, VP][R][gt2,i1]},{mF1 -> M[Fd][i1],mV1 -> 0,MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Fd,VZ, Internal:Fd*) 
{{Fd,VZ,Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fd], Fd, VZ][L][i1,i3],coup2R -> Cp[bar[Fd], Fd, VZ][R][i1,i3],coup1L -> Cp[bar[Fd], Fd, VZ][L][gt2,i1],coup1R -> Cp[bar[Fd], Fd, VZ][R][gt2,i1]},{mF1 -> M[Fd][i1],mV1 -> M[VZ],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Su,bar[Cha], Internal:Fd*) 
{{Su,bar[Cha],Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Cha], Fd, conj[Su]][L][i2,i3,i1],coup2R -> Cp[bar[Cha], Fd, conj[Su]][R][i2,i3,i1],coup1L -> Cp[bar[Fd], Cha, Su][L][gt2,i2,i1],coup1R -> Cp[bar[Fd], Cha, Su][R][gt2,i2,i1]},{mS1 -> M[Su][i1],mF1 -> M[Cha][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* Hpm,bar[Fu], Internal:Fd*) 
{{Hpm,bar[Fu],Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i2,i3,i1],coup2R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i2,i3,i1],coup1L -> Cp[bar[Fd], Fu, Hpm][L][gt2,i2,i1],coup1R -> Cp[bar[Fd], Fu, Hpm][R][gt2,i2,i1]},{mS1 -> M[Hpm][i1],mF1 -> M[Fu][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* VWm,bar[Fu], Internal:Fd*) 
{{VWm,bar[Fu],Internal->Fd},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,gt1,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,gt1,gt3],coup2L -> Cp[bar[Fu], Fd, conj[VWm]][L][i2,i3],coup2R -> Cp[bar[Fu], Fd, conj[VWm]][R][i2,i3],coup1L -> Cp[bar[Fd], Fu, VWm][L][gt2,i2],coup1R -> Cp[bar[Fd], Fu, VWm][R][gt2,i2]},{mV1 -> M[VWm],mF1 -> M[Fu][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}}
(* Ah,Fd,Fd*) 
{{Ah,Fd,Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][i2,gt1,i1],coup1R -> Cp[bar[Fd], Fd, Ah][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Fd, Ah][L][gt2,i3,i1],coup2R -> Cp[bar[Fd], Fd, Ah][R][gt2,i3,i1],coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,i2,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,i2,gt3]},},
(* Chi,Sd,Sd*) 
{{Chi,Sd,Sd},chargefactor -> 1,{coup1L -> Cp[Chi, Fd, conj[Sd]][L][i1,gt1,i2],coup1R -> Cp[Chi, Fd, conj[Sd]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Chi, Sd][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Chi, Sd][R][gt2,i1,i3],coup3 -> Cp[Ah, Sd, conj[Sd]][gt3,i2,i3]},},
(* Glu,Sd,Sd*) 
{{Glu,Sd,Sd},chargefactor -> 4/3,{coup1L -> Cp[Glu, Fd, conj[Sd]][L][gt1,i2],coup1R -> Cp[Glu, Fd, conj[Sd]][R][gt1,i2],coup2L -> Cp[bar[Fd], Glu, Sd][L][gt2,i3],coup2R -> Cp[bar[Fd], Glu, Sd][R][gt2,i3],coup3 -> Cp[Ah, Sd, conj[Sd]][gt3,i2,i3]},},
(* hh,Fd,Fd*) 
{{hh,Fd,Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][i2,gt1,i1],coup1R -> Cp[bar[Fd], Fd, hh][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Fd, hh][L][gt2,i3,i1],coup2R -> Cp[bar[Fd], Fd, hh][R][gt2,i3,i1],coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,i2,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,i2,gt3]},},
(* VZ,Fd,Fd*) 
{{VZ,Fd,Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][i2,gt1],coup1R -> Cp[bar[Fd], Fd, VZ][R][i2,gt1],coup2L -> Cp[bar[Fd], Fd, VZ][L][gt2,i3],coup2R -> Cp[bar[Fd], Fd, VZ][R][gt2,i3],coup3L -> Cp[bar[Fd], Fd, Ah][L][i3,i2,gt3],coup3R -> Cp[bar[Fd], Fd, Ah][R][i3,i2,gt3]},},
(* bar[Cha],Su,Su*) 
{{bar[Cha],Su,Su},chargefactor -> 1,{coup1L -> Cp[bar[Cha], Fd, conj[Su]][L][i1,gt1,i2],coup1R -> Cp[bar[Cha], Fd, conj[Su]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Cha, Su][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Cha, Su][R][gt2,i1,i3],coup3 -> Cp[Ah, Su, conj[Su]][gt3,i2,i3]},},
(* bar[Fd],hh,Ah*) 
{{bar[Fd],hh,Ah},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][i1,gt1,i2],coup1R -> Cp[bar[Fd], Fd, hh][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Fd, Ah][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Fd, Ah][R][gt2,i1,i3],coup3 -> Cp[Ah, Ah, hh][gt3,i3,i2]},},
(* bar[Fd],Ah,hh*) 
{{bar[Fd],Ah,hh},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][i1,gt1,i2],coup1R -> Cp[bar[Fd], Fd, Ah][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Fd, hh][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Fd, hh][R][gt2,i1,i3],coup3 -> Cp[Ah, Ah, hh][gt3,i2,i3]},},
(* bar[Fd],VZ,hh*) 
{{bar[Fd],VZ,hh},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][i1,gt1],coup1R -> Cp[bar[Fd], Fd, VZ][R][i1,gt1],coup2L -> Cp[bar[Fd], Fd, hh][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Fd, hh][R][gt2,i1,i3],coup3 -> Cp[Ah, hh, VZ][gt3,i3]},},
(* bar[Fd],hh,VZ*) 
{{bar[Fd],hh,VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][i1,gt1,i2],coup1R -> Cp[bar[Fd], Fd, hh][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Fd, VZ][L][gt2,i1],coup2R -> Cp[bar[Fd], Fd, VZ][R][gt2,i1],coup3 -> Cp[Ah, hh, VZ][gt3,i2]},},
(* bar[Fu],Hpm,Hpm*) 
{{bar[Fu],Hpm,Hpm},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,gt1,i2],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Fu, Hpm][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Fu, Hpm][R][gt2,i1,i3],coup3 -> Cp[Ah, Hpm, conj[Hpm]][gt3,i2,i3]},},
(* bar[Fu],VWm,Hpm*) 
{{bar[Fu],VWm,Hpm},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][i1,gt1],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][i1,gt1],coup2L -> Cp[bar[Fd], Fu, Hpm][L][gt2,i1,i3],coup2R -> Cp[bar[Fd], Fu, Hpm][R][gt2,i1,i3],coup3 -> Cp[Ah, conj[Hpm], VWm][gt3,i3]},},
(* bar[Fu],Hpm,VWm*) 
{{bar[Fu],Hpm,VWm},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,gt1,i2],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,gt1,i2],coup2L -> Cp[bar[Fd], Fu, VWm][L][gt2,i1],coup2R -> Cp[bar[Fd], Fu, VWm][R][gt2,i1],coup3 -> Cp[Ah, Hpm, conj[VWm]][gt3,i2]},},
(* conj[Hpm],Fu,Fu*) 
{{conj[Hpm],Fu,Fu},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i2,gt1,i1],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Fu, Hpm][L][gt2,i3,i1],coup2R -> Cp[bar[Fd], Fu, Hpm][R][gt2,i3,i1],coup3L -> Cp[bar[Fu], Fu, Ah][L][i3,i2,gt3],coup3R -> Cp[bar[Fu], Fu, Ah][R][i3,i2,gt3]},},
(* conj[Sd],Chi,Chi*) 
{{conj[Sd],Chi,Chi},chargefactor -> 1,{coup1L -> Cp[Chi, Fd, conj[Sd]][L][i2,gt1,i1],coup1R -> Cp[Chi, Fd, conj[Sd]][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Chi, Sd][L][gt2,i3,i1],coup2R -> Cp[bar[Fd], Chi, Sd][R][gt2,i3,i1],coup3L -> Cp[Chi, Chi, Ah][L][i3,i2,gt3],coup3R -> Cp[Chi, Chi, Ah][R][i3,i2,gt3]},},
(* conj[Su],Cha,Cha*) 
{{conj[Su],Cha,Cha},chargefactor -> 1,{coup1L -> Cp[bar[Cha], Fd, conj[Su]][L][i2,gt1,i1],coup1R -> Cp[bar[Cha], Fd, conj[Su]][R][i2,gt1,i1],coup2L -> Cp[bar[Fd], Cha, Su][L][gt2,i3,i1],coup2R -> Cp[bar[Fd], Cha, Su][R][gt2,i3,i1],coup3L -> Cp[bar[Cha], Cha, Ah][L][i3,i2,gt3],coup3R -> Cp[bar[Cha], Cha, Ah][R][i3,i2,gt3]},},
(* conj[VWm],Fu,Fu*) 
{{conj[VWm],Fu,Fu},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][i2,gt1],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][i2,gt1],coup2L -> Cp[bar[Fd], Fu, VWm][L][gt2,i3],coup2R -> Cp[bar[Fd], Fu, VWm][R][gt2,i3],coup3L -> Cp[bar[Fu], Fu, Ah][L][i3,i2,gt3],coup3R -> Cp[bar[Fu], Fu, Ah][R][i3,i2,gt3]},}
};