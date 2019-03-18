(* ----------------------------------------------------------------------------- *) 
(* This model was automatically created by SARAH version4.8.1  *) 
(* SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223 *) 
(* (c) Florian Staub, 2013  *) 
(* ----------------------------------------------------------------------------- *) 
(* File created at 15:02 on 22.11.2017  *) 
(* ---------------------------------------------------------------------- *) 
 
 
LoopContributions[Box2d2nu]={
(* Sd,Chi,Sv,Chi*) 
{{Sd,Chi,Sv,Chi},chargefactor -> 1,{coup1L -> Cp[Chi, Fd, conj[Sd]][L][i4,gt1,i1],coup1R -> Cp[Chi, Fd, conj[Sd]][R][i4,gt1,i1],coup2L -> Cp[bar[Fd], Chi, Sd][L][gt2,i2,i1],coup2R -> Cp[bar[Fd], Chi, Sd][R][gt2,i2,i1],coup3L -> Cp[Chi, Fv, conj[Sv]][L][i2,gt3,i3],coup3R -> Cp[Chi, Fv, conj[Sv]][R][i2,gt3,i3],coup4L -> Cp[bar[Fv], Chi, Sv][L][gt4,i4,i3],coup4R -> Cp[bar[Fv], Chi, Sv][R][gt4,i4,i3]},},
(* Fd,VZ,Fv,VZ*) 
{{Fd,VZ,Fv,VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][i1,gt1],coup1R -> Cp[bar[Fd], Fd, VZ][R][i1,gt1],coup2L -> Cp[bar[Fd], Fd, VZ][L][gt2,i1],coup2R -> Cp[bar[Fd], Fd, VZ][R][gt2,i1],coup3L -> Cp[bar[Fv], Fv, VZ][L][i3,gt3],coup3R -> Cp[bar[Fv], Fv, VZ][R][i3,gt3],coup4L -> Cp[bar[Fv], Fv, VZ][L][gt4,i3],coup4R -> Cp[bar[Fv], Fv, VZ][R][gt4,i3]},},
(* Sd,Chi,conj[Sv],Chi*) 
{{Sd,Chi,conj[Sv],Chi},chargefactor -> 1,{coup1L -> Cp[Chi, Fd, conj[Sd]][L][i4,gt1,i1],coup1R -> Cp[Chi, Fd, conj[Sd]][R][i4,gt1,i1],coup2L -> Cp[bar[Fd], Chi, Sd][L][gt2,i2,i1],coup2R -> Cp[bar[Fd], Chi, Sd][R][gt2,i2,i1],coup3L -> Cp[bar[Fv], Chi, Sv][L][gt4,i2,i3],coup3R -> Cp[bar[Fv], Chi, Sv][R][gt4,i2,i3],coup4L -> Cp[Chi, Fv, conj[Sv]][L][i4,gt3,i3],coup4R -> Cp[Chi, Fv, conj[Sv]][R][i4,gt3,i3]},},
(* Fd,VZ,bar[Fv],VZ*) 
{{Fd,VZ,bar[Fv],VZ},chargefactor -> 1,{coup1L -> Cp[bar[Fd], Fd, VZ][L][i1,gt1],coup1R -> Cp[bar[Fd], Fd, VZ][R][i1,gt1],coup2L -> Cp[bar[Fd], Fd, VZ][L][gt2,i1],coup2R -> Cp[bar[Fd], Fd, VZ][R][gt2,i1],coup3L -> Cp[bar[Fv], Fv, VZ][L][gt4,i3],coup3R -> Cp[bar[Fv], Fv, VZ][R][gt4,i3],coup4L -> Cp[bar[Fv], Fv, VZ][L][i3,gt3],coup4R -> Cp[bar[Fv], Fv, VZ][R][i3,gt3]},},
(* Su,bar[Cha],conj[Se],bar[Cha]*) 
{{Su,bar[Cha],conj[Se],bar[Cha]},chargefactor -> 1,{coup1L -> Cp[bar[Cha], Fd, conj[Su]][L][i4,gt1,i1],coup1R -> Cp[bar[Cha], Fd, conj[Su]][R][i4,gt1,i1],coup2L -> Cp[bar[Fd], Cha, Su][L][gt2,i2,i1],coup2R -> Cp[bar[Fd], Cha, Su][R][gt2,i2,i1],coup3L -> Cp[bar[Cha], bar[Fv], Se][L][i2,gt4,i3],coup3R -> Cp[bar[Cha], bar[Fv], Se][R][i2,gt4,i3],coup4L -> Cp[Cha, Fv, conj[Se]][L][i4,gt3,i3],coup4R -> Cp[Cha, Fv, conj[Se]][R][i4,gt3,i3]},},
(* Fu,conj[Hpm],bar[Fe],conj[Hpm]*) 
{{Fu,conj[Hpm],bar[Fe],conj[Hpm]},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,gt1,i4],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,gt1,i4],coup2L -> Cp[bar[Fd], Fu, Hpm][L][gt2,i1,i2],coup2R -> Cp[bar[Fd], Fu, Hpm][R][gt2,i1,i2],coup3L -> Cp[bar[Fv], Fe, conj[Hpm]][L][gt4,i3,i2],coup3R -> Cp[bar[Fv], Fe, conj[Hpm]][R][gt4,i3,i2],coup4L -> Cp[bar[Fe], Fv, Hpm][L][i3,gt3,i4],coup4R -> Cp[bar[Fe], Fv, Hpm][R][i3,gt3,i4]},},
(* Fu,conj[VWm],bar[Fe],conj[Hpm]*) 
{{Fu,conj[VWm],bar[Fe],conj[Hpm]},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[Hpm]][L][i1,gt1,i4],coup1R -> Cp[bar[Fu], Fd, conj[Hpm]][R][i1,gt1,i4],coup2L -> Cp[bar[Fd], Fu, VWm][L][gt2,i1],coup2R -> Cp[bar[Fd], Fu, VWm][R][gt2,i1],coup3L -> Cp[bar[Fv], Fe, conj[VWm]][L][gt4,i3],coup3R -> Cp[bar[Fv], Fe, conj[VWm]][R][gt4,i3],coup4L -> Cp[bar[Fe], Fv, Hpm][L][i3,gt3,i4],coup4R -> Cp[bar[Fe], Fv, Hpm][R][i3,gt3,i4]},},
(* Fu,conj[Hpm],bar[Fe],conj[VWm]*) 
{{Fu,conj[Hpm],bar[Fe],conj[VWm]},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][i1,gt1],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][i1,gt1],coup2L -> Cp[bar[Fd], Fu, Hpm][L][gt2,i1,i2],coup2R -> Cp[bar[Fd], Fu, Hpm][R][gt2,i1,i2],coup3L -> Cp[bar[Fv], Fe, conj[Hpm]][L][gt4,i3,i2],coup3R -> Cp[bar[Fv], Fe, conj[Hpm]][R][gt4,i3,i2],coup4L -> Cp[bar[Fe], Fv, VWm][L][i3,gt3],coup4R -> Cp[bar[Fe], Fv, VWm][R][i3,gt3]},},
(* Fu,conj[VWm],bar[Fe],conj[VWm]*) 
{{Fu,conj[VWm],bar[Fe],conj[VWm]},chargefactor -> 1,{coup1L -> Cp[bar[Fu], Fd, conj[VWm]][L][i1,gt1],coup1R -> Cp[bar[Fu], Fd, conj[VWm]][R][i1,gt1],coup2L -> Cp[bar[Fd], Fu, VWm][L][gt2,i1],coup2R -> Cp[bar[Fd], Fu, VWm][R][gt2,i1],coup3L -> Cp[bar[Fv], Fe, conj[VWm]][L][gt4,i3],coup3R -> Cp[bar[Fv], Fe, conj[VWm]][R][gt4,i3],coup4L -> Cp[bar[Fe], Fv, VWm][L][i3,gt3],coup4R -> Cp[bar[Fe], Fv, VWm][R][i3,gt3]},}
};