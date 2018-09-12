Print["================================"];
Print["FlexibleSUSY 2.0.1"];
Print["THDM_II"];
Print["http://flexiblesusy.hepforge.org"];
Print["================================"];

libTHDM_II = FileNameJoin[{Directory[], "models", "THDM_II", "THDM_II_librarylink.so"}];

FSTHDM_IIGetSettings = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIGetSettings", LinkObject, LinkObject];
FSTHDM_IIGetSMInputParameters = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIGetSMInputParameters", LinkObject, LinkObject];
FSTHDM_IIGetInputParameters = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIGetInputParameters", LinkObject, LinkObject];
FSTHDM_IIGetProblems = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIGetProblems", LinkObject, LinkObject];
FSTHDM_IIGetWarnings = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIGetWarnings", LinkObject, LinkObject];
FSTHDM_IIToSLHA = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIToSLHA", LinkObject, LinkObject];

FSTHDM_IIOpenHandleLib = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IIOpenHandle", {{Real,1}}, Integer];
FSTHDM_IICloseHandle = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IICloseHandle", {Integer}, Void];

FSTHDM_IISetLib = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IISet", {Integer, {Real,1}}, Void];

FSTHDM_IICalculateSpectrum = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IICalculateSpectrum", LinkObject, LinkObject];
FSTHDM_IICalculateObservables = LibraryFunctionLoad[libTHDM_II, "FSTHDM_IICalculateObservables", LinkObject, LinkObject];

FSTHDM_IICalculateSpectrum::error = "`1`";
FSTHDM_IICalculateSpectrum::warning = "`1`";

FSTHDM_IICalculateObservables::error = "`1`";
FSTHDM_IICalculateObservables::warning = "`1`";

FSTHDM_II::info = "`1`";
FSTHDM_II::nonum = "Error: `1` is not a numeric input value!";
FSTHDM_IIMessage[s_] := Message[FSTHDM_II::info, s];

FSTHDM_IICheckIsNumeric[a_?NumericQ] := a;
FSTHDM_IICheckIsNumeric[a_] := (Message[FSTHDM_II::nonum, a]; Abort[]);

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

fsTHDM_IIDefaultInputParameters = {
   Lambda1IN -> 0,
   Lambda2IN -> 0,
   Lambda3IN -> 0,
   Lambda4IN -> 0,
   Lambda5IN -> 0,
   Lambda6IN -> 0,
   Lambda7IN -> 0,
   M122IN -> 0,
   TanBeta -> 0,
   Qin -> 0
};

Options[FSTHDM_IIOpenHandle] = {
    Sequence @@ fsDefaultSettings,
    Sequence @@ fsDefaultSMParameters,
    Sequence @@ fsTHDM_IIDefaultInputParameters
};

FSTHDM_IIOpenHandle[a___, (fsSettings | fsSMParameters | fsModelParameters) -> s_List, r___] :=
    FSTHDM_IIOpenHandle[a, Sequence @@ s, r];

FSTHDM_IIOpenHandle[OptionsPattern[]] :=
    FSTHDM_IIOpenHandleLib[
        FSTHDM_IICheckIsNumeric /@ {
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

            (* THDM_II input parameters *)
            ,
            OptionValue[Lambda1IN],
            OptionValue[Lambda2IN],
            OptionValue[Lambda3IN],
            OptionValue[Lambda4IN],
            OptionValue[Lambda5IN],
            OptionValue[Lambda6IN],
            OptionValue[Lambda7IN],
            OptionValue[M122IN],
            OptionValue[TanBeta],
            OptionValue[Qin]
        }
];

Options[FSTHDM_IISet] = Options[FSTHDM_IIOpenHandle];

FSTHDM_IISet[handle_Integer, a___, (fsSettings | fsSMParameters | fsModelParameters) -> s_List, r___] :=
    FSTHDM_IISet[handle, a, Sequence @@ s, r];

FSTHDM_IISet[handle_Integer, p:OptionsPattern[]] :=
    FSTHDM_IISetLib[
        handle,
        ReleaseHold[Hold[FSTHDM_IICheckIsNumeric /@ {
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

            (* THDM_II input parameters *)
            ,
            OptionValue[Lambda1IN],
            OptionValue[Lambda2IN],
            OptionValue[Lambda3IN],
            OptionValue[Lambda4IN],
            OptionValue[Lambda5IN],
            OptionValue[Lambda6IN],
            OptionValue[Lambda7IN],
            OptionValue[M122IN],
            OptionValue[TanBeta],
            OptionValue[Qin]
        }] /. HoldPattern[OptionValue[param_]] :> param /.
        { p } /.
        FSTHDM_IIGetSettings[handle] /.
        FSTHDM_IIGetSMInputParameters[handle] /.
        FSTHDM_IIGetInputParameters[handle]]];
