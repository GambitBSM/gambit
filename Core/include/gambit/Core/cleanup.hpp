//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  allows us to record cleanup functions to be 
///  called after the scan is done. for cleaning up
///  backend memory
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author A.S. Woodcock
///  \date 2020 Mar
///
///  *********************************************

#ifndef __cleanup_hpp__
#define __cleanup_hpp__

#include <functional>
#include <string>

namespace Gambit
{
	namespace cleanup
	{
		void register_cleanup_function(std::string fcn_name, std::function<void()> fcn);

		void run_cleanup();
	}
}

#endif // __cleanup_hpp__
