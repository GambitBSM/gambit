//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Includes everything needed to use a GAMBIT
///  module as a standalone analysis code.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Feb
///
///  *********************************************

#ifndef __standalone_hpp__
#define __standalone_hpp__

#define STANDALONE

#include "gambit/Utils/standalone_utils.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Models/model_rollcall.hpp"
#include "gambit/Backends/backend_rollcall.hpp"
#include "gambit/Utils/static_members.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Elements/module_macros_incore.hpp"

using namespace Gambit;
using std::cout;
using std::endl;

#endif //__standalone_hpp__

