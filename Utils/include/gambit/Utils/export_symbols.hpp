//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper macro for controlling symbol visibility in shared libraries
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************

#ifndef __export_symbols_hpp__
#define __export_symbols_hpp__

/// \name Symbol visibility macro
#define EXPORT_SYMBOLS __attribute__ ((visibility ("default")))

#endif
