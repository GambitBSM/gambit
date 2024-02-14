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

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <mutex>
#include <unordered_set>

#include "gambit/Core/error_handlers.hpp"
#include "gambit/Core/cleanup.hpp"

namespace Gambit
{
	namespace cleanup
	{
		std::vector<std::function<void()>> cleanup_functions;
		std::unordered_set<std::string> cleanup_function_names;
		std::mutex prevent_data_race;

		void register_cleanup_function(std::string fcn_name, std::function<void()> fcn)
		{
			std::lock_guard<std::mutex> guard(prevent_data_race);

			if (cleanup_function_names.insert(fcn_name).second)
				cleanup_functions.push_back(fcn);
			else
				core_error().raise(LOCAL_INFO, "WARNING: register_cleanup_function() has already registered: " + fcn_name);
		}

		void run_cleanup()
		{
			static bool cleanDone = false;
			std::lock_guard<std::mutex> guard(prevent_data_race);

			if (cleanDone)
			{
				core_error().raise(LOCAL_INFO, "WARNING: run_cleanup() called multiple times, please call only once");
			}

			for (auto it = cleanup_functions.rbegin(); it != cleanup_functions.rend(); ++it)
				(*it)();

			cleanup_functions.clear();
			cleanup_function_names.clear();
			cleanDone = true;
		}
	}
}
