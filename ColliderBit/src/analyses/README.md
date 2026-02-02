# ColliderBit event analyses

This readme collects information on the ColliderBit event-loop
analysis system and the analyses implemented in it.


## Analysis writing and registration

The analysis system is somewhat inspired by Rivet, but much simplified
for speed and to reflect the less precise/sensitive nature of most
reco-level search analyses as compared to unfolded
precision-measurements.

Analysis codes are all implemented in the `Gambit::ColliderBit`
namespace, and inherit from the `Analysis` base class. They are
implemented in single `.cpp` source files, with a uniform class and
file naming, structured like
`Analysis_<EXPT>_<SQRTS>TeV_<SIG>_<INTLUMI>invfb` where EXP, SQRTS,
SIG, and INTLUMI are (fairly obviously) respectively the experiment
name, the centre of mass energy of the corresponding run in TeV, a
terse description of the targeted event signature, and the
corresponding integrated luminosity in inverse femtobarns.

Rather than a dynamic runtime loading system like Rivet, the ColliderBit
analyses are compiled into ColliderBit. This is done by registering each
analysis class in the `AnalysisContainer.cpp` source file, using some
preprocessor macros to reduce boilerplate code.

The best approach to writing and registering analyses is to copy and
extend an existing similar analysis.


## Analysis info syntax

Each analysis code should also have a `.info` metadata file in YAML
format, with the same name stem as its C++ source file (and class
name). This metadata contains more precise versions of the experiment
and run names, the CoM energy, the integrated luminosity, etc.

It also contains a structured mini-language for summarising the
signal-region (and in future possibly control regions') final-state
signatures, under the `Signatures` key. This metadata entry is a list
of structured strings, each qualitatively describing an SR selection
in the following scheme:

- Each string is separated by `+` symbols into a set of independent
  event-selection requirements, combined with logical AND. The
  ordering is unimportant.

- Each requirement consists of a quantity specifier and a type. Most
  requirement types are framed as counts of physics objects, but some
  are boolean event characteristics.

- Quantity specifiers are generally numeric inequalities, e.g. `3`, `=2`,
  `<4`, or `>=1`. A simple numeric count such as `2` means the same as the
  "exactly equal" requirement, `=2`. Absence of a quantity spec for a
  physics-object type is interpreted as `>=1`. A special `!` quantity is
  a synonym for `0`, for more intuitive use with boolean requirements.

- Physics-object requirement types, in all cases implying a context-dependent
  "significant energy" threshold, are:
  - `L|L2`, `L3`: charged leptons, by default meaning electrons and muons. `L3` variants specifically refer to all three generations, including taus; `L2` specifically limits to e+mu;
  - `E`, `M`: electrons and muons specifically;
  - `TH`: hadronic taus. Leptonic taus are treated as final-state electrons and muons;
  - `SSL|SSL2`, `OSL|OSL2`, + 3-flavour variants: same-sign and opposite-sign leptons. `2` and `3` suffixes can be attached again, defaulting to `2`. The count is the number of leptons, not number of groups;
  - `OSSF|OSSF2`, `SSSF|SSSF2`, `OSOF|OSOF2`, `SSOF|SSOF2`, + 3-flavour variants: pairs of opposite-sign, same-flavour etc. leptons. `2` and `3` suffixes can be attached again, though `3` will be uncommon. The count is the number of pairs, not number of leptons;
  - `DY`: reconstructed candidate photon/Z decay to same-flavour fermions, peaking around the Z or photon pole masses. Probably via leptons. Needed since OSSF doesn't focus on those mass ranges, which are often specifically excluded;
  - `P`, `J`, `JJ`, `JB|B`, `JC|C`, `JL`: photons, jets, large-R/reclustered jets, and b-, c-, and light-jets;
  - `W`, `Z`, `T`, `H`, `PP`: numbers of Standard Model EW resonances -- W, Z, top, Higgs, and photon-propagator -- reconstructed by implied & context-dependent methods (which are not ambiguous and not final-state, so these are discouraged).

- Boolean event-characteristic requirement types, which can be negated
  to favour lower-scale events by using a `!` prefix, are:
  - `MET|MPT|PTMISS`: synonyms for significantly large missing transverse momentum; no absolute number is implied, other than non-zero;
  - `MT`, `MT2`: high (s)transverse mass between the MET vector and a context-dependent visible physics object;
  - `MLL`, `MJJ`: presence of high-mass object pairs;
  - `HT`, `MEFF`: high general scale of scalar event energy.

- *Reserved syntax for numeric-cuts:* We reserve for expansion a
  syntax with brackets immediately following the requirement-type
  term, to permit more detailed specification of cut variables and
  values, e.g. `MET{100} + HT(< 1000)`, or `3J[PT > 100]`.

  Note that several types of bracket and several syntaxes for their
  content are illustrated here: this is just to indicate that this is
  not a currently fixed aspect of the format and users should avoid
  any ad hoc uses that could clash with it. If you are in that
  situation or need/want to specify numerical values within the
  signature syntax, please contact us to discuss the design!


### Examples

- `=2L + OSSF + 1DY + >=2J + MET + MT2`: exactly two leptons (e/mu) in an opposite-sign, same-flavour pair, consistent with Drell-Yan gamma or Z poles, at least two jets, and requiring large missing momentum and stransverse mass;
- `2L + !DY + >=2J + MET + !MJJ`: exactly two e/mu, not from Drell-Yan dilepton masses if same-flavour, at least two jets, significant missing momentum, small dijet mass;
- `=1L + 2B + !TH + MET + MT + H`: exactly one e/mu, exactly two b-jets, no hadronic taus, significant MET and transverse mass, event compatible with a Higgs;
- `>=2SSL + >=2B + >=6J + MET`: at least two same-sign lepton pairs, at least two b-jets, at least 6 jets, and significant missing momentum.
