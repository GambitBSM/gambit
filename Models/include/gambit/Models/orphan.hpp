//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base lineage for starting orphan models.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Aug
///
///  *********************************************

#ifndef __orphan_hpp__
#define __orphan_hpp__


//#include "gambit/Utils/util_types.hpp" // Obsolete dependence?

#include <vector>
#include <string>

namespace Gambit
{
          
  namespace Models
  {  

    namespace PARENT
    {
      // Base lineage that all parentless models copy
      const std::vector<std::string> lineage;
    }
         
  }

}

#endif /* defined(__orphan_hpp__) */

