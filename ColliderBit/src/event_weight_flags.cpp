#include<map>
#include<string>

namespace Gambit
{
  namespace ColliderBit
  {

  	// A string-bool map used to check that consistent choices are
  	// made for event weighting
  	// @todo This is really just a temporary fix until we have a system
  	//       that allows a module function to check which module function
  	//       supplied a given capability

    std::map<std::string,bool> event_weight_flags {
      std::make_pair("weight_by_cross_section" , false),
      std::make_pair("total_cross_section_from_MC" , false),
    };

  }
}

