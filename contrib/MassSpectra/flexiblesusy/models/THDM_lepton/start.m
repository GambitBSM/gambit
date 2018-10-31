AppendTo[$Path, FileNameJoin[{Directory[], "meta"}]];

Needs["SARAH`"];
Needs["FlexibleSUSY`", FileNameJoin[{Directory[], "meta", "FlexibleSUSY.m"}]];

workingDirectory = Directory[];
SARAH`SARAH[OutputDirectory] = FileNameJoin[{workingDirectory, "Output"}];
SARAH`SARAH[InputDirectories] = {
    FileNameJoin[{workingDirectory, "sarah"}],
    ToFileName[{$sarahDir, "Models"}]
};

Print["Current working directory: ", workingDirectory];
Print["SARAH output directory: ", SARAH`SARAH[OutputDirectory]];
Print["Starting model: ", ToString[HoldForm[Start["THDM_lepton"]]]];

Start["THDM_lepton"];

MakeFlexibleSUSY[InputFile -> FileNameJoin[{"models/THDM_lepton","FlexibleSUSY.m"}],
                 OutputDirectory -> "models/THDM_lepton",
                 DebugOutput -> False];
