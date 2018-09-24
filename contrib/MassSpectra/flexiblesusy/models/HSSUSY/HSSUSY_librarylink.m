Print["================================"];
Print["FlexibleSUSY 2.0.1"];
Print["HSSUSY"];
Print["http://flexiblesusy.hepforge.org"];
Print["================================"];

libHSSUSY = FileNameJoin[{Directory[], "models", "HSSUSY", "HSSUSY_librarylink.so"}];

FSHSSUSYGetSettings = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYGetSettings", LinkObject, LinkObject];
FSHSSUSYGetSMInputParameters = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYGetSMInputParameters", LinkObject, LinkObject];
FSHSSUSYGetInputParameters = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYGetInputParameters", LinkObject, LinkObject];
FSHSSUSYGetProblems = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYGetProblems", LinkObject, LinkObject];
FSHSSUSYGetWarnings = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYGetWarnings", LinkObject, LinkObject];
FSHSSUSYToSLHA = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYToSLHA", LinkObject, LinkObject];

FSHSSUSYOpenHandleLib = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYOpenHandle", {{Real,1}}, Integer];
FSHSSUSYCloseHandle = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYCloseHandle", {Integer}, Void];

FSHSSUSYSetLib = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYSet", {Integer, {Real,1}}, Void];

FSHSSUSYCalculateSpectrum = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYCalculateSpectrum", LinkObject, LinkObject];
FSHSSUSYCalculateObservables = LibraryFunctionLoad[libHSSUSY, "FSHSSUSYCalculateObservables", LinkObject, LinkObject];

FSHSSUSYCalculateSpectrum::error = "`1`";
FSHSSUSYCalculateSpectrum::warning = "`1`";

FSHSSUSYCalculateObservables::error = "`1`";
FSHSSUSYCalculateObservables::warning = "`1`";

FSHSSUSY::info = "`1`";
FSHSSUSY::nonum = "Error: `1` is not a numeric input value!";
FSHSSUSYMessage[s_] := Message[FSHSSUSY::info, s];

FSHSSUSYCheckIsNumeric[a_?NumericQ] := a;
FSHSSUSYCheckIsNumeric[a_] := (Message[FSHSSUSY::nonum, a]; Abort[]);

fsDefaultSettings = {
      precisionGoal -> 1.*^-4,           (* FlexibleSUSY[0] *)
      maxIterations -> 0,                (* FlexibleSUSY[1] *)
      solver -> 1,     (* FlexibleSUSY[2] *)
      calculateStandardModelMasses -> 0, (* FlexibleSUSY[3] *)
      poleMassLoopOrder -> 2,            (* FlexibleSUSY[4] *)
      ewsbLoopOrder -> 2,                (* FlexibleSUSY[5] *)
      betaFunctionLoopOrder -> 3,        (* FlexibleSUSY[6] *)
      thresholdCorrectionsLoopOrder -> 2,(* FlexibleSUSY[7] *)
      higgs2loopCorrectionAtAs -> 1,     (* FlexibleSUSY[8] *)
      higgs2loopCorrectionAbAs -> 1,     (* FlexibleSUSY[9] *)
      higgs2loopCorrectionAtAt -> 1,     (* FlexibleSUSY[10] *)
      higgs2loopCorrectionAtauAtau -> 1, (* FlexibleSUSY[11] *)
      forceOutput -> 0,                  (* FlexibleSUSY[12] *)
      topPoleQCDCorrections -> 1,        (* FlexibleSUSY[13] *)
      betaZeroThreshold -> 1.*^-11,      (* FlexibleSUSY[14] *)
      forcePositiveMasses -> 0,          (* FlexibleSUSY[16] *)
      poleMassScale -> 0,                (* FlexibleSUSY[17] *)
      eftPoleMassScale -> 0,             (* FlexibleSUSY[18] *)
      eftMatchingScale -> 0,             (* FlexibleSUSY[19] *)
      eftMatchingLoopOrderUp -> 2,       (* FlexibleSUSY[20] *)
      eftMatchingLoopOrderDown -> 1,     (* FlexibleSUSY[21] *)
      eftHiggsIndex -> 0,                (* FlexibleSUSY[22] *)
      calculateBSMMasses -> 1,           (* FlexibleSUSY[23] *)
      thresholdCorrections -> 123111321, (* FlexibleSUSY[24] *)
      higgs3loopCorrectionRenScheme -> 0,(* FlexibleSUSY[25] *)
      higgs3loopCorrectionAtAsAs -> 1,   (* FlexibleSUSY[26] *)
      higgs3loopCorrectionAbAsAs -> 1,   (* FlexibleSUSY[27] *)
      higgs3loopCorrectionAtAtAs -> 1,   (* FlexibleSUSY[28] *)
      higgs3loopCorrectionAtAtAt -> 1,   (* FlexibleSUSY[29] *)
      parameterOutputScale -> 0          (* MODSEL[12] *)
};

fsDefaultSMParameters = {
    alphaEmMZ -> 1/127.916, (* SMINPUTS[1] *)
    GF -> 1.1663787*^-5,    (* SMINPUTS[2] *)
    alphaSMZ -> 0.1184,     (* SMINPUTS[3] *)
    MZ -> 91.1876,          (* SMINPUTS[4] *)
    mbmb -> 4.18,           (* SMINPUTS[5] *)
    Mt -> 173.34,           (* SMINPUTS[6] *)
    Mtau -> 1.777,          (* SMINPUTS[7] *)
    Mv3 -> 0,               (* SMINPUTS[8] *)
    MW -> 80.385,           (* SMINPUTS[9] *)
    Me -> 0.000510998902,   (* SMINPUTS[11] *)
    Mv1 -> 0,               (* SMINPUTS[12] *)
    Mm -> 0.1056583715,     (* SMINPUTS[13] *)
    Mv2 -> 0,               (* SMINPUTS[14] *)
    md2GeV -> 0.00475,      (* SMINPUTS[21] *)
    mu2GeV -> 0.0024,       (* SMINPUTS[22] *)
    ms2GeV -> 0.104,        (* SMINPUTS[23] *)
    mcmc -> 1.27,           (* SMINPUTS[24] *)
    CKMTheta12 -> 0,
    CKMTheta13 -> 0,
    CKMTheta23 -> 0,
    CKMDelta -> 0,
    PMNSTheta12 -> 0,
    PMNSTheta13 -> 0,
    PMNSTheta23 -> 0,
    PMNSDelta -> 0,
    PMNSAlpha1 -> 0,
    PMNSAlpha2 -> 0,
    alphaEm0 -> 1/137.035999074,
    Mh -> 125.09
};

fsHSSUSYDefaultInputParameters = {
   MSUSY -> 0,
   M1Input -> 0,
   M2Input -> 0,
   M3Input -> 0,
   MuInput -> 0,
   mAInput -> 0,
   MEWSB -> 0,
   AtInput -> 0,
   AbInput -> 0,
   AtauInput -> 0,
   TanBeta -> 0,
   LambdaLoopOrder -> 0,
   TwoLoopAtAs -> 0,
   TwoLoopAbAs -> 0,
   TwoLoopAtAb -> 0,
   TwoLoopAtauAtau -> 0,
   TwoLoopAtAt -> 0,
   DeltaEFT -> 0,
   msq2 -> {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
   msu2 -> {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
   msd2 -> {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
   msl2 -> {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
   mse2 -> {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

Options[FSHSSUSYOpenHandle] = {
    Sequence @@ fsDefaultSettings,
    Sequence @@ fsDefaultSMParameters,
    Sequence @@ fsHSSUSYDefaultInputParameters
};

FSHSSUSYOpenHandle[a___, (fsSettings | fsSMParameters | fsModelParameters) -> s_List, r___] :=
    FSHSSUSYOpenHandle[a, Sequence @@ s, r];

FSHSSUSYOpenHandle[OptionsPattern[]] :=
    FSHSSUSYOpenHandleLib[
        FSHSSUSYCheckIsNumeric /@ {
            (* spectrum generator settings *)
            OptionValue[precisionGoal],
            OptionValue[maxIterations],
            OptionValue[solver],
            OptionValue[calculateStandardModelMasses],
            OptionValue[poleMassLoopOrder],
            OptionValue[ewsbLoopOrder],
            OptionValue[betaFunctionLoopOrder],
            OptionValue[thresholdCorrectionsLoopOrder],
            OptionValue[higgs2loopCorrectionAtAs],
            OptionValue[higgs2loopCorrectionAbAs],
            OptionValue[higgs2loopCorrectionAtAt],
            OptionValue[higgs2loopCorrectionAtauAtau],
            OptionValue[forceOutput],
            OptionValue[topPoleQCDCorrections],
            OptionValue[betaZeroThreshold],
            OptionValue[forcePositiveMasses],
            OptionValue[poleMassScale],
            OptionValue[eftPoleMassScale],
            OptionValue[eftMatchingScale],
            OptionValue[eftMatchingLoopOrderUp],
            OptionValue[eftMatchingLoopOrderDown],
            OptionValue[eftHiggsIndex],
            OptionValue[calculateBSMMasses],
            OptionValue[thresholdCorrections],
            OptionValue[higgs3loopCorrectionRenScheme],
            OptionValue[higgs3loopCorrectionAtAsAs],
            OptionValue[higgs3loopCorrectionAbAsAs],
            OptionValue[higgs3loopCorrectionAtAtAs],
            OptionValue[higgs3loopCorrectionAtAtAt],
            OptionValue[parameterOutputScale],

            (* Standard Model input parameters *)
            OptionValue[alphaEmMZ],
            OptionValue[GF],
            OptionValue[alphaSMZ],
            OptionValue[MZ],
            OptionValue[mbmb],
            OptionValue[Mt],
            OptionValue[Mtau],
            OptionValue[Mv3],
            OptionValue[MW],
            OptionValue[Me],
            OptionValue[Mv1],
            OptionValue[Mm],
            OptionValue[Mv2],
            OptionValue[md2GeV],
            OptionValue[mu2GeV],
            OptionValue[ms2GeV],
            OptionValue[mcmc],
            OptionValue[CKMTheta12],
            OptionValue[CKMTheta13],
            OptionValue[CKMTheta23],
            OptionValue[CKMDelta],
            OptionValue[PMNSTheta12],
            OptionValue[PMNSTheta13],
            OptionValue[PMNSTheta23],
            OptionValue[PMNSDelta],
            OptionValue[PMNSAlpha1],
            OptionValue[PMNSAlpha2],
            OptionValue[alphaEm0],
            OptionValue[Mh]

            (* HSSUSY input parameters *)
            ,
            OptionValue[MSUSY],
            OptionValue[M1Input],
            OptionValue[M2Input],
            OptionValue[M3Input],
            OptionValue[MuInput],
            OptionValue[mAInput],
            OptionValue[MEWSB],
            OptionValue[AtInput],
            OptionValue[AbInput],
            OptionValue[AtauInput],
            OptionValue[TanBeta],
            OptionValue[LambdaLoopOrder],
            OptionValue[TwoLoopAtAs],
            OptionValue[TwoLoopAbAs],
            OptionValue[TwoLoopAtAb],
            OptionValue[TwoLoopAtauAtau],
            OptionValue[TwoLoopAtAt],
            OptionValue[DeltaEFT],
            OptionValue[msq2][[1,1]],
            OptionValue[msq2][[1,2]],
            OptionValue[msq2][[1,3]],
            OptionValue[msq2][[2,1]],
            OptionValue[msq2][[2,2]],
            OptionValue[msq2][[2,3]],
            OptionValue[msq2][[3,1]],
            OptionValue[msq2][[3,2]],
            OptionValue[msq2][[3,3]],
            OptionValue[msu2][[1,1]],
            OptionValue[msu2][[1,2]],
            OptionValue[msu2][[1,3]],
            OptionValue[msu2][[2,1]],
            OptionValue[msu2][[2,2]],
            OptionValue[msu2][[2,3]],
            OptionValue[msu2][[3,1]],
            OptionValue[msu2][[3,2]],
            OptionValue[msu2][[3,3]],
            OptionValue[msd2][[1,1]],
            OptionValue[msd2][[1,2]],
            OptionValue[msd2][[1,3]],
            OptionValue[msd2][[2,1]],
            OptionValue[msd2][[2,2]],
            OptionValue[msd2][[2,3]],
            OptionValue[msd2][[3,1]],
            OptionValue[msd2][[3,2]],
            OptionValue[msd2][[3,3]],
            OptionValue[msl2][[1,1]],
            OptionValue[msl2][[1,2]],
            OptionValue[msl2][[1,3]],
            OptionValue[msl2][[2,1]],
            OptionValue[msl2][[2,2]],
            OptionValue[msl2][[2,3]],
            OptionValue[msl2][[3,1]],
            OptionValue[msl2][[3,2]],
            OptionValue[msl2][[3,3]],
            OptionValue[mse2][[1,1]],
            OptionValue[mse2][[1,2]],
            OptionValue[mse2][[1,3]],
            OptionValue[mse2][[2,1]],
            OptionValue[mse2][[2,2]],
            OptionValue[mse2][[2,3]],
            OptionValue[mse2][[3,1]],
            OptionValue[mse2][[3,2]],
            OptionValue[mse2][[3,3]]
        }
];

Options[FSHSSUSYSet] = Options[FSHSSUSYOpenHandle];

FSHSSUSYSet[handle_Integer, a___, (fsSettings | fsSMParameters | fsModelParameters) -> s_List, r___] :=
    FSHSSUSYSet[handle, a, Sequence @@ s, r];

FSHSSUSYSet[handle_Integer, p:OptionsPattern[]] :=
    FSHSSUSYSetLib[
        handle,
        ReleaseHold[Hold[FSHSSUSYCheckIsNumeric /@ {
            (* spectrum generator settings *)
            OptionValue[precisionGoal],
            OptionValue[maxIterations],
            OptionValue[solver],
            OptionValue[calculateStandardModelMasses],
            OptionValue[poleMassLoopOrder],
            OptionValue[ewsbLoopOrder],
            OptionValue[betaFunctionLoopOrder],
            OptionValue[thresholdCorrectionsLoopOrder],
            OptionValue[higgs2loopCorrectionAtAs],
            OptionValue[higgs2loopCorrectionAbAs],
            OptionValue[higgs2loopCorrectionAtAt],
            OptionValue[higgs2loopCorrectionAtauAtau],
            OptionValue[forceOutput],
            OptionValue[topPoleQCDCorrections],
            OptionValue[betaZeroThreshold],
            OptionValue[forcePositiveMasses],
            OptionValue[poleMassScale],
            OptionValue[eftPoleMassScale],
            OptionValue[eftMatchingScale],
            OptionValue[eftMatchingLoopOrderUp],
            OptionValue[eftMatchingLoopOrderDown],
            OptionValue[eftHiggsIndex],
            OptionValue[calculateBSMMasses],
            OptionValue[thresholdCorrections],
            OptionValue[higgs3loopCorrectionRenScheme],
            OptionValue[higgs3loopCorrectionAtAsAs],
            OptionValue[higgs3loopCorrectionAbAsAs],
            OptionValue[higgs3loopCorrectionAtAtAs],
            OptionValue[higgs3loopCorrectionAtAtAt],
            OptionValue[parameterOutputScale],

            (* Standard Model input parameters *)
            OptionValue[alphaEmMZ],
            OptionValue[GF],
            OptionValue[alphaSMZ],
            OptionValue[MZ],
            OptionValue[mbmb],
            OptionValue[Mt],
            OptionValue[Mtau],
            OptionValue[Mv3],
            OptionValue[MW],
            OptionValue[Me],
            OptionValue[Mv1],
            OptionValue[Mm],
            OptionValue[Mv2],
            OptionValue[md2GeV],
            OptionValue[mu2GeV],
            OptionValue[ms2GeV],
            OptionValue[mcmc],
            OptionValue[CKMTheta12],
            OptionValue[CKMTheta13],
            OptionValue[CKMTheta23],
            OptionValue[CKMDelta],
            OptionValue[PMNSTheta12],
            OptionValue[PMNSTheta13],
            OptionValue[PMNSTheta23],
            OptionValue[PMNSDelta],
            OptionValue[PMNSAlpha1],
            OptionValue[PMNSAlpha2],
            OptionValue[alphaEm0],
            OptionValue[Mh]

            (* HSSUSY input parameters *)
            ,
            OptionValue[MSUSY],
            OptionValue[M1Input],
            OptionValue[M2Input],
            OptionValue[M3Input],
            OptionValue[MuInput],
            OptionValue[mAInput],
            OptionValue[MEWSB],
            OptionValue[AtInput],
            OptionValue[AbInput],
            OptionValue[AtauInput],
            OptionValue[TanBeta],
            OptionValue[LambdaLoopOrder],
            OptionValue[TwoLoopAtAs],
            OptionValue[TwoLoopAbAs],
            OptionValue[TwoLoopAtAb],
            OptionValue[TwoLoopAtauAtau],
            OptionValue[TwoLoopAtAt],
            OptionValue[DeltaEFT],
            OptionValue[msq2][[1,1]],
            OptionValue[msq2][[1,2]],
            OptionValue[msq2][[1,3]],
            OptionValue[msq2][[2,1]],
            OptionValue[msq2][[2,2]],
            OptionValue[msq2][[2,3]],
            OptionValue[msq2][[3,1]],
            OptionValue[msq2][[3,2]],
            OptionValue[msq2][[3,3]],
            OptionValue[msu2][[1,1]],
            OptionValue[msu2][[1,2]],
            OptionValue[msu2][[1,3]],
            OptionValue[msu2][[2,1]],
            OptionValue[msu2][[2,2]],
            OptionValue[msu2][[2,3]],
            OptionValue[msu2][[3,1]],
            OptionValue[msu2][[3,2]],
            OptionValue[msu2][[3,3]],
            OptionValue[msd2][[1,1]],
            OptionValue[msd2][[1,2]],
            OptionValue[msd2][[1,3]],
            OptionValue[msd2][[2,1]],
            OptionValue[msd2][[2,2]],
            OptionValue[msd2][[2,3]],
            OptionValue[msd2][[3,1]],
            OptionValue[msd2][[3,2]],
            OptionValue[msd2][[3,3]],
            OptionValue[msl2][[1,1]],
            OptionValue[msl2][[1,2]],
            OptionValue[msl2][[1,3]],
            OptionValue[msl2][[2,1]],
            OptionValue[msl2][[2,2]],
            OptionValue[msl2][[2,3]],
            OptionValue[msl2][[3,1]],
            OptionValue[msl2][[3,2]],
            OptionValue[msl2][[3,3]],
            OptionValue[mse2][[1,1]],
            OptionValue[mse2][[1,2]],
            OptionValue[mse2][[1,3]],
            OptionValue[mse2][[2,1]],
            OptionValue[mse2][[2,2]],
            OptionValue[mse2][[2,3]],
            OptionValue[mse2][[3,1]],
            OptionValue[mse2][[3,2]],
            OptionValue[mse2][[3,3]]
        }] /. HoldPattern[OptionValue[param_]] :> param /.
        { p } /.
        FSHSSUSYGetSettings[handle] /.
        FSHSSUSYGetSMInputParameters[handle] /.
        FSHSSUSYGetInputParameters[handle]]];
