// //   GAMBIT: Global and Modular BSM Inference Tool
// //   *********************************************
// ///  \file
// ///
// //
// ///  *********************************************
// ///
// ///  Authors:
// ///  <!-- add name and date if you modify -->
// ///
// ///  \author Ben Farmer
// ///          (benjamin.farmer@fysik.su.se)
// ///  \date 2015 Apr
// ///
// ///  \author Pat Scott
// ///          (p.scott@imperial.ac.uk)
// ///  \date 2016 Oct
// ///
// ///  *********************************************

// #include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
// #include "gambit/Elements/thdm_slhahelp.hpp"
// #include "gambit/Utils/util_functions.hpp"
// #include "gambit/Utils/variadic_functions.hpp"
// #include "gambit/Logs/logger.hpp"

// #include <math.h>
// #include <boost/lexical_cast.hpp>

// using namespace SLHAea;

// namespace Gambit
// {
//     /// @{ Constructors

//       /// Default Constructor
//       THDMSimpleSpec::THDMSimpleSpec(const THDMModel& p)
//       {
//         // set_pole_mass_uncertainties(uncert);
//       }

//       /// Constructor via SLHAea object
//       // THDMSimpleSpec::THDMSimpleSpec(const SLHAea::Coll& input, double uncert)
//       //   : SLHASimpleSpec(input)
//       // {
//       //   // set_pole_mass_uncertainties(uncert);
//       // }

//       /// Copy constructor: needed by clone function.
//       // THDMSimpleSpec::THDMSimpleSpec(const THDMSimpleSpec& other, double uncert)
//       //   : SLHASimpleSpec(other)
//       // {
//       //   // set_pole_mass_uncertainties(uncert);
//       // }

//       /// @}

//      /// Add SLHAea object to another
//       void THDMSimpleSpec::add_to_SLHAea(int slha_version, SLHAea::Coll& slha) const
//       {
//         // Add SPINFO data if not already present
//         SLHAea_add_GAMBIT_SPINFO(slha);

//         // All MSSM blocks
//         slhahelp::add_THDM_spectrum_to_SLHAea(*this, slha, slha_version);
//       }
// } // end Gambit namespace


