//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utility functions for DarkBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2015 May
///
///  *********************************************


#ifndef __DarkBit_utils_hpp__
#define __DarkBit_utils_hpp__

#include <vector>
#include <map>

#include "gambit/Utils/util_types.hpp"
#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/daFunk.hpp"


namespace Gambit
{

  namespace DarkBit
  {

    namespace DarkBit_utils
    {

      // Functions

      // Convert between mass and flavour eigenstate identifiers
      std::string str_flav_to_mass(const std::string& flav);
      std::string str_mass_to_flav(const std::string& mass);

      // Helper function for recursively importing decays and decays of resulting final states into a process catalog
      void ImportDecays(std::string pID, TH_ProcessCatalog &catalog,
                        std::set<std::string> &importedDecays,
                        const DecayTable* tbl, double minBranching,
                        std::vector<std::string> excludeDecays = std::vector<std::string>());

      /*! \brief Calculate kinematical limits for three-body final states.
      *
      * Notes:
      * - m0 = 0, E0 = Eg
      * - M_DM is half of center of mass energy
      * - returns E1_low or E1_high, or 0 if kinematically forbidden
      * - Template parameter 0(1) means lower (upper) limit of range.
      */
      template <int i>
      double gamma3bdy_limits(double Eg, double M_DM, double m1, double m2);
    }

  }

}

#endif // defined __DarkBit_utils_hpp__
