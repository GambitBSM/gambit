Print["================================"];
Print["FlexibleSUSY 2.0.1"];
Print["SingletDMZ3"];
Print["http://flexiblesusy.hepforge.org"];
Print["================================"];

libSingletDMZ3 = FileNameJoin[{Directory[], "models", "SingletDMZ3", "SingletDMZ3_librarylink.so"}];

FSSingletDMZ3GetSettings = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3GetSettings", LinkObject, LinkObject];
FSSingletDMZ3GetSMInputParameters = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3GetSMInputParameters", LinkObject, LinkObject];
FSSingletDMZ3GetInputParameters = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3GetInputParameters", LinkObject, LinkObject];
FSSingletDMZ3GetProblems = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3GetProblems", LinkObject, LinkObject];
FSSingletDMZ3GetWarnings = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3GetWarnings", LinkObject, LinkObject];
FSSingletDMZ3ToSLHA = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3ToSLHA", LinkObject, LinkObject];

FSSingletDMZ3OpenHandleLib = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3OpenHandle", {{Real,1}}, Integer];
FSSingletDMZ3CloseHandle = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3CloseHandle", {Integer}, Void];

FSSingletDMZ3SetLib = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3Set", {Integer, {Real,1}}, Void];

FSSingletDMZ3CalculateSpectrum = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3CalculateSpectrum", LinkObject, LinkObject];
FSSingletDMZ3CalculateObservables = LibraryFunctionLoad[libSingletDMZ3, "FSSingletDMZ3CalculateObservables", LinkObject, LinkObject];

FSSingletDMZ3CalculateSpectrum::error = "`1`";
FSSingletDMZ3CalculateSpectrum::warning = "`1`";

FSSingletDMZ3CalculateObservables::error = "`1`";
FSSingletDMZ3CalculateObservables::warning = "`1`";

FSSingletDMZ3::info = "`1`";
FSSingletDMZ3::nonum = "Error: `1` is not a numeric input value!";
FSSingletDMZ3Message[s_] := Message[FSSingletDMZ3::info, s];

FSSingletDMZ3CheckIsNumeric[a_?NumericQ] := a;
FSSingletDMZ3CheckIsNumeric[a_] := (Message[FSSingletDMZ3::nonum, a]; Abort[]);

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

fsSingletDMZ3DefaultInputParameters = {
   HiggsIN -> 0,
   LamSHInput -> 0,
   LamSInput -> 0,
   muSInput -> 0,
   mu3Input -> 0,
   QEWSB -> 0,
   Qin -> 0
};

Options[FSSingletDMZ3OpenHandle] = {
    Sequence @@ fsDefaultSettings,
    Sequence @@ fsDefaultSMParameters,
    Sequence @@ fsSingletDMZ3DefaultInputParameters
};

FSSingletDMZ3OpenHandle[a___, (fsSettings | fsSMParameters | fsModelParameters) -> s_List, r___] :=
    FSSingletDMZ3OpenHandle[a, Sequence @@ s, r];

FSSingletDMZ3OpenHandle[OptionsPattern[]] :=
    FSSingletDMZ3OpenHandleLib[
        FSSingletDMZ3CheckIsNumeric /@ {
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

            (* SingletDMZ3 input parameters *)
            ,
            OptionValue[HiggsIN],
            OptionValue[LamSHInput],
            OptionValue[LamSInput],
            OptionValue[muSInput],
            OptionValue[mu3Input],
            OptionValue[QEWSB],
            OptionValue[Qin]
        }
];

Options[FSSingletDMZ3Set] = Options[FSSingletDMZ3OpenHandle];

FSSingletDMZ3Set[handle_Integer, a___, (fsSettings | fsSMParameters | fsModelParameters) -> s_List, r___] :=
    FSSingletDMZ3Set[handle, a, Sequence @@ s, r];

FSSingletDMZ3Set[handle_Integer, p:OptionsPattern[]] :=
    FSSingletDMZ3SetLib[
        handle,
        ReleaseHold[Hold[FSSingletDMZ3CheckIsNumeric /@ {
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

            (* SingletDMZ3 input parameters *)
            ,
            OptionValue[HiggsIN],
            OptionValue[LamSHInput],
            OptionValue[LamSInput],
            OptionValue[muSInput],
            OptionValue[mu3Input],
            OptionValue[QEWSB],
            OptionValue[Qin]
        }] /. HoldPattern[OptionValue[param_]] :> param /.
        { p } /.
        FSSingletDMZ3GetSettings[handle] /.
        FSSingletDMZ3GetSMInputParameters[handle] /.
        FSSingletDMZ3GetInputParameters[handle]]];
