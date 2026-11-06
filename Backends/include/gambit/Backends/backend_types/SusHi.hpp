//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of container classes for the
///  SusHi 1.7.0 backend.
///
///  These structs mirror, member by member and in
///  the same order, the Fortran COMMON blocks that
///  SusHi's SLHA reader (src/sushi/readslha.f and
///  src/sushi/slhablocks.f) fills when it parses an
///  input file.  The GAMBIT frontend writes directly
///  into these blocks via BE_VARIABLE, so that no
///  per-point SLHA file has to be written and read.
///
///  Block layouts are taken from
///  src/commons/common-slha.f and
///  src/commons/common-inputoutput.f of SusHi 1.7.0.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///  \date 2026 Nov
///
///  *********************************************


#ifndef __SusHi_types_hpp__
#define __SusHi_types_hpp__

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

  /// common /slhaparam/ : real-valued SLHA block entries (plus PDF set names)
  struct SusHi_slhaparam_type
  {
    Farray<Fdouble,1,100>     sminputs;       // Block SMINPUTS
    Farray<Fdouble,1,100>     minpar;         // Block MINPAR
    Fdouble                   slhaalpha;      // Block ALPHA
    Farray<Fdouble,1,100>     gauge;          // Block GAUGE
    Farray<Fdouble,1,100>     sushipar;       // Block SUSHI
    Farray<Fdouble,1,10>      yukawafac;      // Block FACTORS (Yukawa coupling factors: 1=c, 2=t, 3=b, 4=st, 5=sb)
    Farray<Fdouble,1,10>      fourgen;        // Block 4GEN
    Farray<Fdouble,1,30>      scalespar;      // Block SCALES
    Fdouble                   frgghmin;       // Block SCALES, entry 101
    Fdouble                   frgghmax;       // Block SCALES, entry 101
    Fdouble                   frgghmintab;    // Block SCALES, entry 102
    Fdouble                   frgghmaxtab;    // Block SCALES, entry 102
    Farray<Fdouble,1,10>      renormbotpar;   // Block RENORMBOT
    Farray<Fdouble,1,10>      renormsbotpar;  // Block RENORMSBOT
    Farray<Fdouble,1,60>      distribpar;     // Block DISTRIB
    Fdouble                   twohdmpar;      // Block 2HDM
    Farray<Fdouble,1,30,0,3>  dim5par;        // Block DIM5
    Farray<Fdouble,-1,99>     feynhiggspar;   // Block FEYNHIGGS
    Farray<Fdouble,-1,99>     thdmcpar;       // Block 2HDMC
    Farray<Fdouble,1,80>      extpar;         // Block EXTPAR
    Farray<Fdouble,1,80>      imextpar;       // Block IMEXTPAR
    FstringArray<50,1,4>      pdfname;        // Block PDFSPEC, entries 1-4 (LO, NLO, NNLO, N3LO PDF set names)
    FstringArray<50,1,1>      extfilepar;     // Block EXTFILE
  };

  /// common /slhamass/ : Block MASS entries
  struct SusHi_slhamass_type
  {
    Farray<Fdouble,1,100>     smassbo;        // PDG codes 1-100 (Higgs bosons: 25, 35, 36, ...)
    Farray<Fdouble,1,100>     smassfe1;       // PDG codes 1000001-1000100 (minus 1000000)
    Farray<Fdouble,1,100>     smassfe2;       // PDG codes 2000001-2000100 (minus 2000000)
  };

  /// common /slhamix/ : mixing-matrix blocks
  struct SusHi_slhamix_type
  {
    Farray<Fdouble,1,2,1,2>   stopmix;        // Block STOPMIX
    Farray<Fdouble,1,100>     hmix;           // Block HMIX
    Farray<Fdouble,1,2,1,2>   sbotmix;        // Block SBOTMIX
    Farray<Fdouble,1,10,1,10> nmhmix;         // Block NMHMIX
    Farray<Fdouble,1,10,1,10> nmamix;         // Block NMAMIX
    Farray<Fdouble,1,10,1,10> nmamixr;        // Block NMAMIXR
  };

  /// common /slhaint/ : integer-valued SLHA block entries
  struct SusHi_slhaint_type
  {
    Farray<Finteger,1,20>     vegaspar;       // Block VEGAS
    Farray<Finteger,1,20>     pdfspecpar;     // Block PDFSPEC, entries >= 5 (PDF set members)
    Farray<Finteger,1,15>     fhflagspar;     // Block FEYNHIGGSFLAGS
    Farray<Finteger,1,20,1,3> gghsoftpar;     // Block GGHSOFT
    Farray<Finteger,-1,99>    gghmtpar;       // Block GGHMT
    Finteger                  frgghstep;      // Block SCALES, entry 102
    Farray<Finteger,1,10>     qqhint;         // Block QQH, entries 1-10
    Farray<Finteger,1,10>     tmpint;         // Block TMP, entries 1-10
    Finteger                  dim5runpar;     // Block DIM5, entry 0
  };

  /// common /slhareal/ : further real-valued entries
  struct SusHi_slhareal_type
  {
    Farray<Fdouble,1,10>      gghmtreal;      // Block GGHMT, entry 9
    Farray<Fdouble,1,5>       qqhreal;        // Block QQH, entries > 10 (minus 10)
    Farray<Fdouble,1,10>      tmpreal;        // Block TMP, entries > 10
  };

  /// common /slhalogical/ : "this entry was given in the input" flags.
  /// SusHi only uses an entry of the blocks above if the matching flag here
  /// is set; otherwise it falls back to its built-in default or stops with
  /// an "undefined" error.  Fortran LOGICALs are 4 bytes in gfortran.
  struct SusHi_slhalogical_type
  {
    Farray<Flogical,1,10>      ltmpint;
    Farray<Flogical,1,10>      ltmpreal;
    Farray<Flogical,1,100>     lsmassbo;
    Farray<Flogical,1,100>     lsmassfe1;
    Farray<Flogical,1,100>     lsmassfe2;
    Farray<Flogical,1,100>     lsminputs;
    Farray<Flogical,1,100>     lminpar;
    Farray<Flogical,1,2,1,2>   lstopmix;
    Farray<Flogical,1,100>     lhmix;
    Farray<Flogical,1,100>     lgauge;
    Flogical                   lslhaalpha;
    Farray<Flogical,1,2,1,2>   lsbotmix;
    Farray<Flogical,1,20>      lvegaspar;
    Farray<Flogical,1,100>     lsushipar;
    Farray<Flogical,1,10>      lyukawafac;
    Farray<Flogical,1,10>      lfourgen;
    Farray<Flogical,1,30>      lscalespar;
    Farray<Flogical,1,10>      lrenormbotpar;
    Farray<Flogical,1,10>      lrenormsbotpar;
    Farray<Flogical,1,60>      ldistribpar;
    Farray<Flogical,-1,100>    lfeynhiggspar;  // NB: one element longer than feynhiggspar
    Farray<Flogical,-1,99>     lthdmcpar;
    Farray<Flogical,1,80>      lextpar;
    Farray<Flogical,1,20>      lpdfspecpar;
    Flogical                   ltwohdmpar;
    Farray<Flogical,1,10,1,10> lnmhmix;
    Farray<Flogical,1,10,1,10> lnmamix;
    Farray<Flogical,1,10,1,10> lnmamixr;
    Farray<Flogical,1,15>      lfhflags;
    Farray<Flogical,1,30,0,3>  ldim5par;
    Farray<Flogical,1,20>      lgghsoftpar;
    Farray<Flogical,-1,99>     lgghmtpar;
    Farray<Flogical,1,10>      lgghmtreal;
    Farray<Flogical,1,4>       lpdfname;
    Farray<Flogical,1,10>      lqqhint;
    Farray<Flogical,1,5>       lqqhreal;
    Farray<Flogical,1,2>       lmurscanpar;
    Flogical                   ldim5runpar;
    Farray<Flogical,1,80>      limextpar;
    Farray<Flogical,1,1>       lextfilepar;
  };

  /// common /fileinfileout/ : SusHi's input and output file names.
  /// Not used for I/O by the GAMBIT frontend (no files are written or read),
  /// but SusHi derives e.g. the name of its optional muR-scan output from
  /// jfnameact, so the frontend gives it a harmless value.
  struct SusHi_fileinfileout_type
  {
    Fstring<60> jfilein;
    Fstring<60> jfnameact;
  };

  // Sizes of the corresponding common-block symbols in libsushi.so (nm -S), 
  // to catch size mismatch at compile time.
  // 
  static_assert(sizeof(SusHi_slhaparam_type)     == 8400, "SusHi_slhaparam_type does not match common /slhaparam/");
  static_assert(sizeof(SusHi_slhamass_type)      == 2400, "SusHi_slhamass_type does not match common /slhamass/");
  static_assert(sizeof(SusHi_slhamix_type)       == 3264, "SusHi_slhamix_type does not match common /slhamix/");
  static_assert(sizeof(SusHi_slhaint_type)       ==  952, "SusHi_slhaint_type does not match common /slhaint/");
  static_assert(sizeof(SusHi_slhareal_type)      ==  200, "SusHi_slhareal_type does not match common /slhareal/");
  static_assert(sizeof(SusHi_slhalogical_type)   == 7808, "SusHi_slhalogical_type does not match common /slhalogical/");
  static_assert(sizeof(SusHi_fileinfileout_type) ==  120, "SusHi_fileinfileout_type does not match common /fileinfileout/");

}

#endif // defined __SusHi_types_hpp__
