import os

location = "src/SusyLesHouches.cc"
temp_location = location + "_temp"

lines = open(location, 'r').readlines()

# Find where the GAMBIT patch ends.
linenum = 0
with open(location) as f:
    for num, line in enumerate(f, 1):
        if "(blockName == \"nmssmrun\") ifail=nmssmrun.set(linestream)" in line:
            linenum = num+1
            break

with open(temp_location, 'w') as f:
    # Write the stuff at the beginning...
    for i in range(linenum):
        f.write(lines[i])
    # Write the source specific to the model...
    f.write((
        "      // LH blocks added by GUM\n"
        "      if (blockName == \"kblh\") ifail=kblh.set(linestream);\n"
        "      if (blockName == \"kblw\") ifail=kblw.set(linestream);\n"
        "      if (blockName == \"kblz\") ifail=kblz.set(linestream);\n"
        "      if (blockName == \"kbrh\") ifail=kbrh.set(linestream);\n"
        "      if (blockName == \"kbrw\") ifail=kbrw.set(linestream);\n"
        "      if (blockName == \"kbrz\") ifail=kbrz.set(linestream);\n"
        "      if (blockName == \"ktlh\") ifail=ktlh.set(linestream);\n"
        "      if (blockName == \"ktlw\") ifail=ktlw.set(linestream);\n"
        "      if (blockName == \"ktlz\") ifail=ktlz.set(linestream);\n"
        "      if (blockName == \"ktrh\") ifail=ktrh.set(linestream);\n"
        "      if (blockName == \"ktrw\") ifail=ktrw.set(linestream);\n"
        "      if (blockName == \"ktrz\") ifail=ktrz.set(linestream);\n"
        "      if (blockName == \"kxlw\") ifail=kxlw.set(linestream);\n"
        "      if (blockName == \"kxrw\") ifail=kxrw.set(linestream);\n"
        "      if (blockName == \"kylw\") ifail=kylw.set(linestream);\n"
        "      if (blockName == \"kyrw\") ifail=kyrw.set(linestream);\n"
        "\n"
    ))
    # Then write the rest. Voila: the cheap man's patch.
    for i in range(len(lines)-linenum):
        f.write(lines[i+linenum])

os.remove(location)
os.rename(temp_location, location)

location = "include/Pythia8/SusyLesHouches.h"
temp_location = location + "_temp"

lines = open(location, 'r').readlines()

# Find where the GAMBIT patch ends.
linenum = 0
with open(location) as f:
    for num, line in enumerate(f, 1):
        if "LHmatrixBlock<5> imnmnmix;" in line:
            linenum = num
            break

with open(temp_location, 'w') as f:
    # Write the stuff at the beginning...
    for i in range(linenum):
        f.write(lines[i])
    # Write the stuff specific to the model.
    f.write((
        "  // LH blocks added by GUM\n"
        "  LHblock<double> kblh;\n"
        "  LHblock<double> kblw;\n"
        "  LHblock<double> kblz;\n"
        "  LHblock<double> kbrh;\n"
        "  LHblock<double> kbrw;\n"
        "  LHblock<double> kbrz;\n"
        "  LHblock<double> ktlh;\n"
        "  LHblock<double> ktlw;\n"
        "  LHblock<double> ktlz;\n"
        "  LHblock<double> ktrh;\n"
        "  LHblock<double> ktrw;\n"
        "  LHblock<double> ktrz;\n"
        "  LHblock<double> kxlw;\n"
        "  LHblock<double> kxrw;\n"
        "  LHblock<double> kylw;\n"
        "  LHblock<double> kyrw;\n"
        "\n"
    ))
    # Then write the rest. Voila: the cheap man's patch.
    for i in range(len(lines)-linenum):
        f.write(lines[i+linenum])

os.remove(location)
os.rename(temp_location, location)
