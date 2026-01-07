<h1 align="center">
GAMBIT
</h1>
<br>
<div align="center">
<img src="https://gambitbsm.org/gambit_logo.png" width="200"/>
<br>
 <br>
<i>The Global And Modular BSM Inference Tool</i>
</div>
<br>
<div align="center">
<img alt="Static Badge" src="https://img.shields.io/badge/arXiv-1705.07908-blue?link=https%3A%2F%2Farxiv.org%2Fabs%2F1705.07908">
</div>
<br>


GAMBIT (the Global And Modular BSM Inference Tool) is a software code for performing statistical global fits of generic physics models using a wide range of particle physics and astrophysics data, built by the [GAMBIT Collaboration](https://gambitbsm.org/). It consists of a series of modules that provide native simulations of collider and astrophysics experiments, a flexible system for interfacing external codes (the "backend" system), a fully featured statistical and parameter scanning framework, and a host of tools for implementing and using hierarchical models.

Quickstart
--

You can build and run a minimal program by e.g.,
```bash
sudo apt install build-essential gfortran cmake git python3-yaml libboost-all-dev libgsl-dev libeigen3-dev liblapack-dev pkg-config
git clone https://github.com/GambitBSM/gambit
cd gambit
mkdir build
cd build
cmake -Ditch="DarkBit;ColliderBit;CosmoBit;FlavBit;PrecisionBit;NeutrinoBit;ObjectivesBit;DecayBit;SpecBit" ..
make -j4 scanners
cmake ..
make -j4 gambit
cd ..
gambit -f yaml_files/spartan.yaml
```
Check out the [tutorials](https://gambitbsm.org/documentation/tutorials/the_gambit_interface/) for more examples.

Documentation
--

Please see the [manual](https://arxiv.org/abs/1705.07908) for the main documentation on the design and use of the GAMBIT Core and modules. Further details on the code are available [here](https://gambitbsm.org/).

Tooling
--

We maintain
- [gambit-light](https://github.com/GambitBSM/gambit_light_1.0), a light-weight GAMBIT without any built-in physics computations, intended as a general fitting/optimisation package
- [gambit-plot](https://github.com/GambitBSM/gambit_plotting_tools) for analyzing and plotting GAMBIT results using `matplotlib`
- [gambit-style](https://github.com/GambitBSM/gambit-style) for formatting the GAMBIT codebase using e.g., `clang-format` and `clang-tidy`
- [gambit-test](https://github.com/GambitBSM/gambit-test) for testing GAMBIT using [BATS](https://bats-core.readthedocs.io/)
- [TWalkReader](https://github.com/GambitBSM/TWalkReader/) for reading TWalk MCMC results into [ArViZ](https://python.arviz.org/en/stable/)

Supported compilers and dependencies
--

GAMBIT is built using the [CMake](https://cmake.org/) system. GAMBIT depends on the following librarires and packages:

### Compulsory

 - gcc >= 9 / llvm clang >= 10 / AppleClang >= 13 / icc >= 15.0.2
 - gfortran >= 9 / ifort >=15.0.2
 - CMake 3.2.3 or greater
 - Python 3
 - Python modules: yaml, future, os, re, datetime, sys, getopt, shutil and itertools.
 - git
 - Boost 1.48 or greater
 - GNU Scientific Library (GSL) 2.1 or greater
 - Eigen 3.1.0 or greater
 - LAPACK
 - pkg-config


On Debian-based systems, they can be installed by

    sudo apt install build-essential gfortran cmake git python3-yaml libboost-all-dev libgsl-dev libeigen3-dev liblapack-dev pkg-config

### Optional

 - HDF5 (for use of the hdf5 printer)
 - MPI (required for parallel sampling)
 - axel (speeds up downloads of backends and scanners)
 - graphviz (required for model hierarchy and dependency tree plots)

On Debian-based systems, they can be installed by
    
    sudo apt install libhdf5-dev libopenmpi-dev axel graphviz

#### ROOT

[ROOT](https://root.cern/) is required for RestFrames support in ColliderBit, or the GreAT scanner from ScannerBit. See [here](https://root.cern/install/) for installation instructions.

#### GUM & Mathematica

 - Mathematica 7.0 or greater (required for the use of Mathematica backends and GUM)
 - UUID (required for the use of the WSTP interface for Mathematica backends and GUM)
 - X11 development libraries (required for the use of GUM)
 - Boost compiled libraries (required for the use of GUM):
    - Boost.Python
    - Boost.Filesystem
    - Boost.System
  
Other than Mathematica, on Debian-based systems, they can be installed by
    
    sudo apt install libx11-dev uuid-dev libboost-python-dev libboost-filesystem-dev libboost-system-dev
  
#### Python

   - cython (required for using the classy and contur backends)
   - scipy (required for using the MontePython, DarkAges and Acropolis backends)
   - numpy 1.12 or greater (required for using any python backend)
   - dill (required for using the DarkAges backend)
   - six (required for using the classy backend)
   - pandas, numexpr (required for using the MontePython backend)
   - h5py (required to use hdf5 utilities located in gambit/Printers/scripts and the backend pbarlike)
   - pyhf (required for use of the ATLAS_FullLikes backend)
   - numba (required for using the Acropolis backend)
   - configobj, pandas and matplotlib (required for using the contur backend)
   - tensorflow and iminuit (required for using the pbarlike backend)

They can be installed through pip by

    pip install -r optional.txt

To ensure that the the h5py Python module and hdf5 library are compatible, we recommend you install h5py using the --no-binary flag by

     pip install --no-binary=h5py h5py

This will happen automatically if you install Python dependencies by our optional.txt file.

Memory requirements
--

For building the entirety of GAMBIT without optimisation, at least 10 GB of RAM is required. The build can be completed with less RAM than this if enough modules are ditched when running CMake, with e.g. `cmake -Ditch="ColliderBit;DarkBit" ..`, etc. See the Core paper ("GAMBIT: The Global and Modular Beyond-the-Standard-Model Inference Tool", the first link at the top of this README file) for further details of how to ditch components. For a list of commonly used CMake options, see the file CMAKE_FLAGS.md.

Building with optimisation enabled (e.g. using `-DCMAKE_BUILD_TYPE=Release`) may require more than 20 GB of RAM, depending on the compiler in use and precisely which optimisations it employs. Interprocedural optimisation in particular requires very large amounts of RAM. In general, Release mode is only intended for performance-critical applications, such as when running on supercomputer architectures.  It is not advised for laptops.


Building GAMBIT
--

The basic build instructions are below.  GAMBIT supports Linux and Mac OSX.  On Windows, you can run it thorugh the Linux subsystem or Cygwin.  A full walkthrough of how to install all dependencies and build GAMBIT with AppleClang on OSX can be found in the file README_OSX.md.

Note that CMake will fail to find some dependencies on some systems without guidance. If you encounter problems configuring or building GAMBIT, have a look [here](BUILD_OPTIONS.md) for a list of commonly used build options.

More information about the GAMBIT CMake system is provided in the Core paper. Configuration examples for specific computing clusters are available via gambit.hepforge.org.



Assuming that you have retrieved the git repository or the tarball and unpacked it:

```bash
  cd gambit
  mkdir build
  cd build
  cmake ..
  make -jn scanners (where n specifies the desired number of cores for the build, e.g. 4)
  cmake ..
  make -jn gambit
```

To build all backend codes:
```bash
  make -jn backends
```

If you don't want to wait for all backends to build, or if one fails to compile on your system for whatever reason, you can also build individual backends using:
```bash
  make -jn <backend name>
```

and clean them with:
```bash
  make clean-<backend name>
```

Running GAMBIT
--

For complete documentation on running GAMBIT, please see the Core and module papers (the latter include examples for both running within the full GAMBIT framework, and running standalone module examples). Here we provide a few basic examples.

To see which backends and scanners have been installed correctly, do:

```bash
  gambit backends
  gambit scanners
```

To run the GAMBIT spartan example, do
```bash
  gambit -f yaml_files/spartan.yaml
```

To run an example GAMBIT MSSM7 scan, do:
```bash
  gambit -f yaml_files/MSSM7.yaml
```

Other examples are provided in the yaml_files folder.  Further readmes and documentation can also be found in the doc folder.

Running GUM
--

For a detailed description on how to use GUM please see the [GUM paper](https://arxiv.org/abs/2107.00030) (reference below). To run the simple model described in the tutorial, the MDMSM, do:

```bash
  gum -f Tutorial/MDMSM.gum
```

To revert the changes to the GAMBIT code brought upon by GUM run GUM in revert mode:

```bash
  gum -r mug_files/MDMSM.mug
```

Besides the tutorial model, other example models can be found in the gum_files directory.


Citations
--

Please cite the following GAMBIT papers, depending on your use of different modules:

 - GAMBIT Collaboration: P. Athron, et al., **GAMBIT**: The Global and Modular Beyond-the-Standard-Model Inference Tool, Eur. Phys. J. C 77 (2017) 784, [arXiv:1705.07908](https://arxiv.org/abs/1705.07908)
 - GAMBIT Collider Workgroup: C. Balazs, et al., **ColliderBit**: A GAMBIT module for the calculation of high energy collider observables and likelihoods, Eur. Phys. J. C 77 (2017) 795, [arXiv:1705.07919](https://arxiv.org/abs/1705.07919)
 - GAMBIT Models Workgroup: P. Athron, et al., **SpecBit, DecayBit and PrecisionBit**: GAMBIT modules for computing mass spectra, particle decay rates and precision observables, Eur. Phys. J. C 78 (2018) 22, [arXiv:1705.07936](https://arxiv.org/abs/1705.07936)
 - GAMBIT Flavour Workgroup: F. U. Bernlochner, et al., **FlavBit**: A GAMBIT module for computing flavour observables and likelihoods, Eur. Phys. J. C 77 (2017) 786, [arXiv:1705.07933](https://arxiv.org/abs/1705.07933)
 - GAMBIT Scanner Workgroup: G. D. Martinez, et al., Comparison of statistical sampling methods with **ScannerBit**, the GAMBIT scanning module, Eur. Phys. J. C 77 (2017) 761, [arXiv:1705.07959](https://arxiv.org/abs/1705.07959)
 - GAMBIT Dark Matter Workgroup: T. Bringmann, et al., **DarkBit**: A GAMBIT module for computing dark matter observables and likelihoods, Eur. Phys. J. C 77 (2017) 831, [arXiv:1705.07920](https://arxiv.org/abs/1705.07920)
 - **NeutrinoBit**: M. Chrzaszcz, M. Drewes, T. Gonzalo, J. Harz, S. Krishnamurthy, C. Weniger, A frequentist analysis of three right-handed neutrinos with GAMBIT, Eur. Phys. J. C 80 (2020) 569, [arXiv:1908.02302](https://arxiv.org/abs/1908.02302)
 - GAMBIT Cosmology Workgroup: J. J. Renk, et al., **CosmoBit**: A GAMBIT module for computing cosmological observables and likelihoods, JCAP 02 (2021) 022, [arXiv:2009.03286](https://arxiv.org/abs/2009.03286)
 - **GUM**: S. Bloor, T. Gonzalo, P. Scott, C. Chang, A. Raklev, J-E. Camargo-Molina, A. Kvellestad, J. Renk, P. Athron, C. Balázs, The GAMBIT Universal Model Machine: from Lagrangians to Likelihoods, Eur. Phys. J. C 81 (2021) 1103, [arXiv:2107.00030](https://arxiv.org/abs/2107.00030).

GAMBIT contains interfaces to various external codes, along with scripts for downloading and configuring them. Please cite as appropriate if you use those codes:

 - **Acropolis:** **(i)** M. Hufnagel, K. Schmidt-Hoberg, S. Wild, BBN constraints on MeV-scale dark sectors. Part II. Electromagnetic decays, JCAP 11 (2018) 032, [arXiv:1808.09324](https://arxiv.org/abs/1808.09324), **(ii)** P. F. Depta, M. Hufnagel, K. Schmidt-Hoberg, ACROPOLIS: A generiC fRamework fOr Photodisintegration Of LIght elementS, JCAP 03 (2021) 061, [arXiv:2011.06518](https://arxiv.org/abs/2011.06518), **(iii)** P. F. Depta, M. Hufnagel, K. Schmidt-Hoberg, Updated BBN constraints on electromagnetic decays of MeV-scale particles, JCAP 04 (2021) 011, [arXiv:2011.06519](https://arxiv.org/abs/2011.06519).
 - **AlterBBN:** **(i)** A. Arbey, AlterBBN: A program for calculating the BBN abundances of the elements in alternative cosmologies, Comput. Phys. Commun. 183 (2012) 1822, [arXiv:1106.1363](https://arxiv.org/abs/1106.1363) **(ii)** A. Arbey, J. Auffinger, K. P. Hickerson and E. S. Jenssen, AlterBBN v2: A public code for calculating Big-Bang nucleosynthesis constraints in alternative cosmologies, [arXiv:1806.11095](https://arxiv.org/abs/1806.11095).
 - **CalcHEP:** **(i)** A. Pukhov, CalcHEP 2.3: MSSM, structure functions, event generation, batchs, and generation of matrix elements for other packages, [arXiv:hep-ph/0412191](https://arxiv.org/abs/hep-ph/0412191), **(ii)** A. Belyaev, N. D. Christensen, and A. Pukhov, CalcHEP 3.4 for collider physics within and beyond the Standard Model, Comp. Phys. Comm. 184 (2013) 1729–1769, [arXiv:1207.6082](https://arxiv.org/abs/1207.6082).
 - **Capt'n General:** **(i)** GAMBIT Collaboration: P. Athron, C. Balazs, et al., Global analyses of Higgs portal singlet dark matter models using GAMBIT, Eur. Phys. J. C 79 (2019) 38, [arXiv:1808.10465](https://arxiv.org/abs/1808.10465), **(ii)** N. Avis Kozar, A. Caddell, L. Fraser-Leach, P. Scott, and A. C. Vincent, Capt’n General: A generalized stellar dark matter capture and heat transport code, (2021), [arXiv:2105.06810](https://arxiv.org/abs/2105.06810).
 - **CLASS:** **(i)** D. Blas, J. Lesgourgues, T. Tram, The Cosmic Linear Anisotropy Solving System (CLASS) II: Approximation schemes, JCAP 07 (2011) 034, [arXiv: 1104.2933](https://arxiv.org/abs/1104.2933), **(ii)** M. Lucca, N. Schöneberg, D. C. Hooper, J. Lesgourgues, J. Chluba, The synergy between CMB spectral distortions and anisotropies, JCAP 02 (2020) 026, [arXiv:1910.04619](https://arxiv.org/abs/1910.04619).
 - **Contur:** J. M. Butterworth, D. Grellscheid, M. Krämer, B. Sarrazin, D. Yallup, Constraining new physics with collider measurements of Standard Model signatures, JHEP 03 (2017), 078, [arXiv: 1606.05296](https://arxiv.org/abs/1606.05296) [hep-ph]
 - **DarkAges:** P. Stoecker, M. Krämer, J. Lesgourgues, V. Poulin, Exotic energy injection with ExoCLASS: Application to the Higgs portal model and evaporating black holes, JCAP 03 (2018) 018, [arXiv:1801.01871](https://arxiv.org/abs/1801.01871)
 - **DarkCast:** P. Ilten, Y. Soreq, M. Williams, W. Xue, Serendipity in dark photon searches, JHEP 06 (2018) 004, [arXiv:1801.04847](https://arxiv.org/abs/1801.04847)
 - **DarkSUSY:** **(i)** P. Gondolo, J. Edsjo, et al., DarkSUSY: computing supersymmetric dark matter properties numerically, JCAP 7 (2004) 8, [arXiv: astro-ph/0406204](https://arxiv.org/abs/astro-ph/0406204) **(ii)** T. Bringmann, J. Edsjö, P. Gondolo, P. Ullio and L. Bergström, DarkSUSY 6: An Advanced Tool to Compute Dark Matter Properties Numerically, JCAP 1807 (2018) 033, [arXiv:1802.03399](https://arxiv.org/abs/1802.03399),
 - **DDCalc:** **(i)** GAMBIT Collaboration: P. Athron, C. Balazs, et al. Global analyses of Higgs portal singlet dark matter models using GAMBIT, EPJC 79 (2019) 38, [arxiv:1808.10465](https://arxiv.org/abs/1808.10465) **(ii)** P. Athron, J. M. Cornell, F. Kahlhoefer, J. Mckay, P. Scott, Impact of vacuum stability, perturbativity and XENON1T on global fits of Z_2​ and Z_3​ scalar singlet dark matter, EPJC 78 (2018) 1830, [arxiv:1806.11281](https://arxiv.org/abs/1806.11281) **(iii)** GAMBIT Dark Matter Workgroup: T. Bringmann, J. Conrad, et al., DarkBit: A GAMBIT module for computing dark matter observables and likelihoods, Eur. Phys. J. C 77 (2017) 831, [arXiv:1705.07920](https://arxiv.org/abs/1705.07920)
 - **DirectDM:** **(i)** F. Bishara, J. Brod, B. Grinstein, and J. Zupan, DirectDM: a tool for dark matter direct detection, [arXiv:1708.02678](https://arxiv.org/abs/1708.02678). **(ii)** J. Brod, A. Gootjes-Dreesbach, M. Tammaro, and J. Zupan, Effective Field Theory for Dark Matter Direct Detection up to Dimension Seven, JHEP 10 (2018) 065, [arXiv:1710.10218](https://arxiv.org/abs/1710.10218).
 - **exoCLASS:** P. Stoecker, M. Krämer, J. Lesgourgues, V. Poulin, Exotic energy injection with ExoCLASS: Application to the Higgs portal model and evaporating black holes, JCAP 03 (2018) 018, [arXiv:1801.01871](https://arxiv.org/abs/1801.01871)
 - **FeynHiggs:** **(i)** H. Bahl, W. Hollik, Precise prediction for the light MSSM Higgs boson mass combining effective field theory and fixed-order calculations, Eur. Phys. J. C 76 (2016) 499,  [arXiv:1608.01880](https://arxiv.org/abs/1608.01880), **(ii)** T. Hahn, S. Heinemeyer, W. Hollik, H. Rzehak, G. Weiglein, High-precision predictions for the light CP-even Higgs Boson Mass of the MSSM, Phys. Rev. Lett. 112 (2014) 141801, [arXiv:1312.4937](https://arxiv.org/abs/1312.4937), **(iii)** M. Frank, T. Hahn, S. Heinemeyer, W. Hollik, H. Rzehak, G. Weiglein, The Higgs Boson Masses and Mixings of the Complex MSSM in the Feynman-Diagrammatic Approach, JHEP 0702 (2007) 047, [arXiv:hep-ph/0611326](https://arxiv.org/abs/hep-ph/0611326), **(iv)** G. Degrassi, S. Heinemeyer, W. Hollik, P. Slavich, G. Weiglein, Towards High-Precision Predictions for the MSSM Higgs Sector, Eur. Phys. J. C 28 (2003) 133, [arXiv:hep-ph/0212020](https://arxiv.org/abs/hep-ph/0212020), **(v)** S. Heinemeyer, W. Hollik, G. Weiglein, The Masses of the Neutral CP-even Higgs Bosons in the MSSM: Accurate Analysis at the Two-Loop Level, Eur.Phys.J.C9:343-366 (1999), [arXiv:hep-ph/9812472](https://arxiv.org/abs/hep-ph/9812472), **(vi)** S. Heinemeyer, W. Hollik, G. Weiglein, FeynHiggs: a program for the calculation of the masses of the neutral CP-even Higgs bosons in the MSSM, Comput. Phys. Commun. 124 (2000) 76, [arXiv:hep-ph/9812320](https://arxiv.org/abs/hep-ph/9812320)
 - **FeynRules:** **(i)** N. D. Christensen and C. Duhr, FeynRules - Feynman rules made easy, Comput. Phys. Commun. 180 (2009) 1614–1641, [arXiv:0806.4194](https://arxiv.org/abs/0806.4194), **(ii)** N. D. Christensen, P. de Aquino, et. al., A Comprehensive approach to new physics simulations, Eur. Phys. J. C71 (2011) 1541, [arXiv:0906.2474](https://arxiv.org/abs/0906.2474), **(iii)** N. D. Christensen, C. Duhr, B. Fuks, J. Reuter, and C. Speckner, Introducing an interface between WHIZARD and FeynRules, Eur. Phys. J. C72 (2012) 1990, [arXiv:1010.3251](https://arxiv.org/abs/1010.3251), **(iv)** A. Alloul, N. D. Christensen, C. Degrande, C. Duhr, and B. Fuks, FeynRules 2.0 - A complete toolbox for tree-level phenomenology, Comput. Phys. Commun. 185 (2014) 2250–2300, [arXiv:1310.1921](https://arxiv.org/abs/1310.1921).
 - **FlexibleSUSY:** P. Athron, J.-h. Park, D. Stöckinger, and A. Voigt, FlexibleSUSY - A spectrum generator generator for supersymmetric models, Comp. Phys. Comm. 190 (2015) 139, [arXiv:1406.2319](https://arxiv.org/abs/1406.2319)
 - **GamLike:** GAMBIT Dark Matter Workgroup: T. Bringmann, J. Conrad, et al., DarkBit: A GAMBIT module for computing dark matter observables and likelihoods, Eur. Phys. J. C 77 (2017) 831, [arXiv:1705.07920](https://arxiv.org/abs/1705.07920)
 - **GM2Calc:** P. Athron, et al., GM2Calc: precise MSSM prediction for (g-2) of the muon, Eur. Phys. J. C 76 (2016) 62, [arXiv:1510.08071](https://arxiv.org/abs/1510.08071)
 - **HepLike:** J. Bhom, M. Chrzaszcz, HEPLike: an open source framework for experimental likelihood evaluation, Comput.Phys.Commun. 254 (2020) 107235, [arXiv:2003.03956](https://arxiv.org/abs/2003.03956).
 - **HiggsBounds:** **(i)** P. Bechtle, O. Brein, S. Heinemeyer, G. Weiglein, and K. E. Williams, HiggsBounds: Confronting Arbitrary Higgs Sectors with Exclusion Bounds from LEP and the Tevatron, Comp. Phys. Comm. 181 (2010) 138, [arXiv:0811.4169](https://arxiv.org/abs/0811.4169), **(ii)** P. Bechtle, O. Brein, S. Heinemeyer, G. Weiglein, and K. E. Williams, HiggsBounds 2.0.0: Confronting Neutral and Charged Higgs Sector Predictions with Exclusion Bounds from LEP and the Tevatron, Comp. Phys. Comm. 182 (2011) 2605, [arXiv:1102.1898](https://arxiv.org/abs/1102.1898), **(iii)** P. Bechtle, O. Brein, et al., HiggsBounds - 4: Improved Tests of Extended Higgs Sectors against Exclusion Bounds from LEP, the Tevatron and the LHC, Eur. Phys. J. C 74 (2014) 2693, [arXiv:1311.0055](https://arxiv.org/abs/1311.0055)
 - **HiggsSignals:** P. Bechtle, S. Heinemeyer, O. Stal, T. Stefaniak, and G. Weiglein, HiggsSignals: Confronting arbitrary Higgs sectors with measurements at the Tevatron and the LHC, Eur. Phys. J. C 74 (2014) 2711, [arXiv:1305.1933](https://arxiv.org/abs/1305.1933)
 - **MadGraph 5:** **(i)** T. Stelzer and W. F. Long, Automatic generation of tree level helicity amplitudes, Comput. Phys. Commun. 81 (1994) 357–371, [arXiv:hep-ph/9401258](https://arxiv.org/abs/hep-ph/9401258), **(ii)** F. Maltoni and T. Stelzer, MadEvent: Automatic event generation with MadGraph, JHEP 02 (2003) 027, [arXiv:hep-ph/0208156](https://arxiv.org/abs/hep-ph/0208156), **(iii)** J. Alwall, P. Demin, et. al., MadGraph/MadEvent v4: The New Web Generation, JHEP 09 (2007)
028, [arXiv:0706.2334](https://arxiv.org/abs/0706.2334), **(iv)** J. Alwall, M. Herquet, F. Maltoni, O. Mattelaer, and T. Stelzer, MadGraph 5 : Going Beyond, JHEP 06 (2011) 128, [arXiv:1106.0522](https://arxiv.org/abs/1106.0522).
 - **MicrOmegas:** G. Belanger, F. Boudjema, A. Pukhov, A. Semenov, micrOMEGAs4.1: Two dark matter candidates, Comp. Phys. Comm. 192 (2015) 322, [arXiv:1407.6129](https://arxiv.org/abs/1407.6129)
 - **MontePython:** **(i)** B. Audren, J. Lesgourgues, K. Benabed, S. Prunet, Conservative Constraints on Early Cosmology: an illustration of the Monte Python cosmological parameter inference code, JCAP 02 (2013) 001, [arXiv:1210.7183](https://arxiv.org/abs/1210.7183) **(ii)** T. Brinckmann, J. Lesgourgues, MontePython 3: boosted MCMC sampler and other features, Phys.Dark Univ. 24 (2019) 100260, [arXiv:1804.07261](https://arxiv.org/abs/1804.07261)
 - **MultiModeCode:** L. C. Price, J. Frazer, J. Xu, H. V. Peiris, R. Easther, MultiModeCode: An efficient numerical solver for multifield inflation, JCAP 03 (2015) 005, [arXiv: 1410.0685](https://arxiv.org/abs/1410.0685)
 - **Multinest:** F. Feroz, M. P. Hobson, M. Bridges, MULTINEST: an efficient and robust Bayesian inference tool for cosmology and particle physics, MNRAS 398 (2009) 1601–1614, [arXiv:0809.3437](https://arxiv.org/abs/0809.3437)
 - **nulike:** **(i)** IceCube Collaboration: M. G. Aartsen et al., Improved limits on dark matter annihilation in the Sun with the 79-string IceCube detector and implications for supersymmetry, JCAP 04 (2016) 022, [arXiv:1601.00653](https://arxiv.org/abs/1601.00653), **(ii)** P. Scott, C. Savage, J. Edsjo the IceCube Collaboration: R. Abbasi et al., Use of event-level neutrino telescope data in global fits for theories of new physics, JCAP 11 (2012) 57, [arXiv:1207.0810](https://arxiv.org/abs/1207.0810)
 - **obscura:** T. Emken, obscura: A modular C++ tool and library for the direct detection of (sub-GeV) dark matter via nuclear and electron recoils, J. Open Source Softw. 6 (2021) 3725, [arXiv:2112.01489](https://arxiv.org/abs/2112.01489)
 - **pbarlike:** S. Balan, F. Kahlhoefer, M. Korsmeier, S. Manconi, K. Nippel, Fast and accurate AMS-02 antiproton likelihoods for global dark matter fits, [arXiv: 2303.07362](https://arxiv.org/abs/2303.07362) [hep-ph]
 - **PolyChord:** W. J. Handley, M. P. Hobson, M. P. A. N. Lasenby, POLYCHORD: next-generation nested sampling, MNRAS 453 (2015) 4384, [arXiv:1506.00171](https://arxiv.org/abs/1506.00171)
 - **pyhf:** L. Heinrich, M. Feickert, G. Stark, K. Cranmer,  pyhf: pure-Python implementation of HistFactory statistical models, [J.Open Source Softw. 6 (2021) 58, 2823](https://joss.theoj.org/papers/10.21105/joss.02823)
 - **Pythia 8:** **(i)** T. Sjostrand, S. Ask, et al., An Introduction to PYTHIA 8.2, Comp. Phys. Comm. 191 (2015) 159, [arXiv:1410.3012](https://arxiv.org/abs/1410.3012), **(ii)**  T. Sjostrand, Stephen Mrenna, Peter Skands, Pythia 6.4 Physics and Manual, JHEP 0605 (2006) 026, [arXiv:hep-ph/0603175](https://arxiv.org/abs/hep-ph/0603175)
 - **Rivet:** C. Bierlich, A. Buckley, J. Butterworth, C. H. Christensen, L. Corpe, D. Grellscheid, J. F. Grosse-Oetringhaus, C. Gutschow, P. Karczmarczyk, J. Klein, L. Lönnblad, C. S. Pollard, P. Richardson, H. Schulz, F. Siegert , Robust Independent Validation of Experiment and Theory: Rivet version 3, SciPost Phys. 8 (2020), 026, [arXiv: 1912.05451](https://arxiv.org/abs/1912.05451) [hep-ph]
 - **SARAH:**  **(i)** F. Staub, SARAH, [arXiv:0806.0538](https://arxiv.org/abs/0806.0538), **(ii)** F. Staub, Automatic Calculation of Supersymmetric Renormalization Group Equations and Self Energies, Comp. Phys. Comm. 182 (2011) 808–833, [arXiv:1002.0840](https://arxiv.org/abs/1002.0840), **(iii)** F. Staub, SARAH 3.2: Dirac Gauginos, UFO output, and more, Comp. Phys. Comm. 184 (2013) 1792–1809, [arXiv:1207.0906](https://arxiv.org/abs/1207.0906), **(iv)** F. Staub, SARAH 4 : A tool for (not only SUSY) model builders, Comp. Phys. Comm. 185 (2014) 1773–1790, [arXiv:1309.7223](https://arxiv.org/abs/1309.7223), **(v)** F. Staub, Exploring new models in all detail with SARAH, Adv. High Energy Phys. 2015 (2015) 840780, [arXiv:1503.04200](https://arxiv.org/abs/1503.04200).
 - **SPheno:** **(i)** W. Porod, SPheno, a program for calculating supersymmetric spectra, SUSY particle decays and SUSY particle production at e+ e- colliders, Comput. Phys. Commun. 153 (2003) 275, [arXiv:hep-ph/0301101](https://arxiv.org/abs/hep-ph/0301101), **(ii)** W. Porod, F. Staub,  SPheno 3.1: extensions including flavour, CP-phases and models beyond the MSSM, Comp. Phys. Comm. 183 (2012) 2458, [arXiv:1104.1573](https://arxiv.org/abs/1104.1573)
 - **SuperIso:** **(i)** F. Mahmoudi, SuperIso: A Program for calculating the isospin asymmetry of B -> K\* gamma in the MSSM, Comp. Phys. Comm. 178 (2008) 745, [arXiv:0710.2067](https://arxiv.org/abs/0710.2067), **(ii)** F. Mahmoudi, SuperIso v2.3: A Program for calculating flavor physics observables in Supersymmetry, Comp. Phys. Comm. 180 (2009) 1579, [arXiv:0808.3144](https://arxiv.org/abs/0808.3144), **(iii)** F. Mahmoudi, SuperIso v3.0, flavor physics observables calculations: Extension to NMSSM, [Comp. Phys. Comm. 180 (2009) 1718](https://www.sciencedirect.com/science/article/pii/S0010465509001489).
 - **SUSY-HD:** J. P. Vega, G. Villadoro, SusyHD: Higgs mass Determination in Supersymmetry, JHEP 07 (2015) 159, [arXiv:1504.05200](https://arxiv.org/abs/1504.05200)
 - **SUSY-HIT:** A. Djouadi, M. M. Mühlleitner M. Spira, Decays of supersymmetric particles: The Program SUSY-HIT (SUspect-SdecaY-Hdecay-InTerface), Acta Phys. Polon. 38 (2007) 635, [arXiv: hep-ph/0609292](https://arxiv.org/abs/hep-ph/0609292)
 - **Vevacious:** J. E. Camargo-Molina, B. O’Leary, W. Porod, and F. Staub, Vevacious: A Tool For Finding The Global Minima Of One-Loop Effective Potentials With Many Scalars, Eur. Phys. J. C73 (2013)
2588, [arXiv:1307.1477](https://arxiv.org/abs/1307.1477).

