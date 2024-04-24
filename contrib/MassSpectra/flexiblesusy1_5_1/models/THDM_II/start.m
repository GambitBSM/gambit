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
Print["Starting model: ", ToString[HoldForm[Start["THDM_II"]]]];

Start["THDM_II"];

MakeFlexibleSUSY[InputFile -> FileNameJoin[{"models/THDM_II","FlexibleSUSY.m"}],
                 OutputDirectory -> "models/THDM_II",
                 DebugOutput -> False];
