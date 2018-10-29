(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.13.0  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 14:02 on 29.10.2018  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[Gluon2Q]={
chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VG][L][gt1,gt2],coup1R -> Cp[bar[Fd], Fd, VG][R][gt1,gt2]},}
(* Ah,bar[Fd], Internal:Fd*) 
{{Ah,bar[Fd],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fd, Ah][R][gt1,i2,i1],coup2L -> Cp[bar[Fd], Fd, Ah][L][i2,i3,i1],coup2R -> Cp[bar[Fd], Fd, Ah][R][i2,i3,i1],coup3L -> Cp[bar[Fd], Fd, VG][L][i3,gt2],coup3R -> Cp[bar[Fd], Fd, VG][R][i3,gt2]},{mS1 -> M[Ah][i1],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,hh, Internal:Fd*) 
{{Fd,hh,Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Fd, hh][R][gt1,i1,i2],coup2L -> Cp[bar[Fd], Fd, hh][L][i1,i3,i2],coup2R -> Cp[bar[Fd], Fd, hh][R][i1,i3,i2],coup3L -> Cp[bar[Fd], Fd, VG][L][i3,gt2],coup3R -> Cp[bar[Fd], Fd, VG][R][i3,gt2]},{mF1 -> M[Fd][i1],mS1 -> M[hh][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fd,VZ, Internal:Fd*) 
{{Fd,VZ,Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][gt1,i1],coup1R -> Cp[bar[Fd], Fd, VZ][R][gt1,i1],coup2L -> Cp[bar[Fd], Fd, VZ][L][i1,i3],coup2R -> Cp[bar[Fd], Fd, VZ][R][i1,i3],coup3L -> Cp[bar[Fd], Fd, VG][L][i3,gt2],coup3R -> Cp[bar[Fd], Fd, VG][R][i3,gt2]},{mF1 -> M[Fd][i1],mV1 -> M[VZ],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fu,conj[Hpm], Internal:Fd*) 
{{Fu,conj[Hpm],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fu, Hpm][L][gt1,i1,i2],coup1R -> Cp[bar[Fd], Fu, Hpm][R][gt1,i1,i2],coup2L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,i3,i2],coup2R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,i3,i2],coup3L -> Cp[bar[Fd], Fd, VG][L][i3,gt2],coup3R -> Cp[bar[Fd], Fd, VG][R][i3,gt2]},{mF1 -> M[Fu][i1],mS1 -> M[Hpm][i2],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* Fu,conj[VWm], Internal:Fd*) 
{{Fu,conj[VWm],Internal->Fd},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fu, VWm][L][gt1,i1],coup1R -> Cp[bar[Fd], Fu, VWm][R][gt1,i1],coup2L -> Cp[bar[Fu], Fd, conj[VWm]][L][i1,i3],coup2R -> Cp[bar[Fu], Fd, conj[VWm]][R][i1,i3],coup3L -> Cp[bar[Fd], Fd, VG][L][i3,gt2],coup3R -> Cp[bar[Fd], Fd, VG][R][i3,gt2]},{mF1 -> M[Fu][i1],mV1 -> M[VWm],MFin -> M[Fd][i3]-M[Fd][gt1]}},
(* bar[Fd],Ah, Internal:bar[Fd]*) 
{{bar[Fd],Ah,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, VG][L][gt1,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][gt1,i3],coup2L -> Cp[bar[Fd], Fd, Ah][L][i3,i1,i2],coup2R -> Cp[bar[Fd], Fd, Ah][R][i3,i1,i2],coup1L -> Cp[bar[Fd], Fd, Ah][L][i1,gt2,i2],coup1R -> Cp[bar[Fd], Fd, Ah][R][i1,gt2,i2]},{mF1 -> M[Fd][i1],mS1 -> M[Ah][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* hh,Fd, Internal:bar[Fd]*) 
{{hh,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, VG][L][gt1,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][gt1,i3],coup2L -> Cp[bar[Fd], Fd, hh][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Fd, hh][R][i3,i2,i1],coup1L -> Cp[bar[Fd], Fd, hh][L][i2,gt2,i1],coup1R -> Cp[bar[Fd], Fd, hh][R][i2,gt2,i1]},{mS1 -> M[hh][i1],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* VZ,Fd, Internal:bar[Fd]*) 
{{VZ,Fd,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, VG][L][gt1,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][gt1,i3],coup2L -> Cp[bar[Fd], Fd, VZ][L][i3,i2],coup2R -> Cp[bar[Fd], Fd, VZ][R][i3,i2],coup1L -> Cp[bar[Fd], Fd, VZ][L][i2,gt2],coup1R -> Cp[bar[Fd], Fd, VZ][R][i2,gt2]},{mV1 -> M[VZ],mF1 -> M[Fd][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[Hpm],Fu, Internal:bar[Fd]*) 
{{conj[Hpm],Fu,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, VG][L][gt1,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][gt1,i3],coup2L -> Cp[bar[Fd], Fu, Hpm][L][i3,i2,i1],coup2R -> Cp[bar[Fd], Fu, Hpm][R][i3,i2,i1],coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i2,gt2,i1],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i2,gt2,i1]},{mS1 -> M[Hpm][i1],mF1 -> M[Fu][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}},
(* conj[VWm],Fu, Internal:bar[Fd]*) 
{{conj[VWm],Fu,Internal->bar[Fd]},chargefactor -> 1,{coup3L -> Cp[bar[Fd], Fd, VG][L][gt1,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][gt1,i3],coup2L -> Cp[bar[Fd], Fu, VWm][L][i3,i2],coup2R -> Cp[bar[Fd], Fu, VWm][R][i3,i2],coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][i2,gt2],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][i2,gt2]},{mV1 -> M[VWm],mF1 -> M[Fu][i2],MFin -> M[Fd][i3]-M[Fd][gt2]}}
(* Ah,bar[Fd],bar[Fd]*) 
{{Ah,bar[Fd],bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, Ah][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fd, Ah][R][gt1,i2,i1],coup2L -> Cp[bar[Fd], Fd, Ah][L][i3,gt2,i1],coup2R -> Cp[bar[Fd], Fd, Ah][R][i3,gt2,i1],coup3L -> Cp[bar[Fd], Fd, VG][L][i2,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][i2,i3]},},
(* hh,bar[Fd],bar[Fd]*) 
{{hh,bar[Fd],bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, hh][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fd, hh][R][gt1,i2,i1],coup2L -> Cp[bar[Fd], Fd, hh][L][i3,gt2,i1],coup2R -> Cp[bar[Fd], Fd, hh][R][i3,gt2,i1],coup3L -> Cp[bar[Fd], Fd, VG][L][i2,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][i2,i3]},},
(* Hpm,bar[Fu],bar[Fu]*) 
{{Hpm,bar[Fu],bar[Fu]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fu, Hpm][L][gt1,i2,i1],coup1R -> Cp[bar[Fd], Fu, Hpm][R][gt1,i2,i1],coup2L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i3,gt2,i1],coup2R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i3,gt2,i1],coup3L -> Cp[bar[Fu], Fu, VG][L][i2,i3],coup3R -> Cp[bar[Fu], Fu, VG][R][i2,i3]},},
(* VWm,bar[Fu],bar[Fu]*) 
{{VWm,bar[Fu],bar[Fu]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fu, VWm][L][gt1,i2],coup1R -> Cp[bar[Fd], Fu, VWm][R][gt1,i2],coup2L -> Cp[bar[Fu], Fd, conj[VWm]][L][i3,gt2],coup2R -> Cp[bar[Fu], Fd, conj[VWm]][R][i3,gt2],coup3L -> Cp[bar[Fu], Fu, VG][L][i2,i3],coup3R -> Cp[bar[Fu], Fu, VG][R][i2,i3]},},
(* VZ,bar[Fd],bar[Fd]*) 
{{VZ,bar[Fd],bar[Fd]},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][gt1,i2],coup1R -> Cp[bar[Fd], Fd, VZ][R][gt1,i2],coup2L -> Cp[bar[Fd], Fd, VZ][L][i3,gt2],coup2R -> Cp[bar[Fd], Fd, VZ][R][i3,gt2],coup3L -> Cp[bar[Fd], Fd, VG][L][i2,i3],coup3R -> Cp[bar[Fd], Fd, VG][R][i2,i3]},}
};