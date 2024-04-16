//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Aldo Saavedra
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///  \date 2018 Jan
///  \date 2019 Jan
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///  \date 2017 Jun
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July
///
///  *********************************************

#pragma once

#define MODULE ColliderBit
#define REFERENCE GAMBIT:2017qxg
START_MODULE
#undef REFERENCE
#undef MODULE

#include "gambit/Elements/shared_types.hpp"
#include "gambit/ColliderBit/ColliderBit_types.hpp"
#include "gambit/ColliderBit/ColliderBit_Higgs_rollcall.hpp"
#include "gambit/ColliderBit/ColliderBit_LEP_rollcall.hpp"
#include "gambit/ColliderBit/ColliderBit_MC_rollcall.hpp"
#include "gambit/ColliderBit/ColliderBit_models_rollcall.hpp"
#include "gambit/ColliderBit/ColliderBit_measurements_rollcall.hpp"
