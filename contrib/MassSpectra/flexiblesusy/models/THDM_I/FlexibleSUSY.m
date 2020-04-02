FSModelName = "THDM_I";
FSEigenstates = SARAH`EWSB;
FSDefaultSARAHModel = "THDM_I";

OnlyLowEnergyFlexibleSUSY = True;

(* input parameters *)

MINPAR = {
    {11, Lambda1IN},
    {12, Lambda2IN},
    {13, Lambda3IN},
    {14, Lambda4IN},
    {15, Lambda5IN},
    {16, Lambda6IN},
    {17, Lambda7IN},
    {18, M122IN},
    {3, TanBeta}
};

EXTPAR = {
    {0, Qin}
};

EWSBOutputParameters = { M112, M222 };

SUSYScale = Qin;

SUSYScaleFirstGuess = Qin;

SUSYScaleInput = {
    {Lambda1, Lambda1IN},
    {Lambda2, Lambda2IN},
    {Lambda3, Lambda3IN},
    {Lambda4, Lambda4IN},
    {Lambda5, Lambda5IN},
    {Lambda6, Lambda6IN},
    {Lambda7, Lambda7IN},
    {M122,    M122IN}
};

LowScale = LowEnergyConstant[MZ];

LowScaleFirstGuess = LowEnergyConstant[MZ];

LowScaleInput = {
    {v1, 2 MZMSbar / Sqrt[GUTNormalization[g1]^2 g1^2 + g2^2] Cos[ArcTan[TanBeta]]},
    {v2, 2 MZMSbar / Sqrt[GUTNormalization[g1]^2 g1^2 + g2^2] Sin[ArcTan[TanBeta]]},
    {Yu, Automatic},
    {Yd, Automatic},
    {Ye, Automatic}
};

InitialGuessAtLowScale = {
    {v1, LowEnergyConstant[vev] Cos[ArcTan[TanBeta]]},
    {v2, LowEnergyConstant[vev] Sin[ArcTan[TanBeta]]},
    {Yu, Automatic},
    {Yd, Automatic},
    {Ye, Automatic}
};

SMParticles = {
    Electron, TopQuark, BottomQuark,
    VectorP, VectorZ, VectorG, VectorW, Neutrino
};

DefaultPoleMassPrecision = MediumPrecision;
HighPoleMassPrecision    = {hh, Ah, Hpm};
MediumPoleMassPrecision  = {};
LowPoleMassPrecision     = {};

ExtraSLHAOutputBlocks = {
    {EFFHIGGSCOUPLINGS, NoScale,
            {{1, FlexibleSUSYObservable`CpHiggsPhotonPhoton},
             {2, FlexibleSUSYObservable`CpHiggsGluonGluon},
             {3, FlexibleSUSYObservable`CpPseudoScalarPhotonPhoton},
             {4, FlexibleSUSYObservable`CpPseudoScalarGluonGluon} } }
};
