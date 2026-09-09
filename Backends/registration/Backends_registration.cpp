//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Link-time registration translation unit for
///  the GAMBIT backends.
///
///  This file expands the generated
///  backend_rollcall.hpp (i.e. every frontend
///  header) in the in-core macro context, exactly
///  as gambit.hpp used to do inside the Core, but
///  from within a translation unit owned by the
///  Backends directory.  All backend functor
///  definitions, BackendIniBit module functors,
///  classloading bookkeeping and registration
///  calls produced by the backend macros are
///  therefore compiled into this object file, and
///  the registrations happen during static
///  initialisation, before main().
///
///  Unlike the per-Bit registration TUs, no
///  harvester change is involved: gambit.hpp
///  simply skips its #include of
///  backend_rollcall.hpp when the global
///  LINK_TIME_REGISTRATION compile definition is
///  set, and this TU includes it instead.
///
///  This file is only compiled into the main
///  gambit executable, and only when the CMake
///  option LINK_TIME_REGISTRATION is ON.  It must
///  NOT be compiled into the Backends object
///  library: standalone executables expand
///  backend_rollcall.hpp from their own main
///  translation unit via standalone_module.hpp
///  (with STANDALONE defined), and would suffer
///  duplicate-symbol errors.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Jun
///
///  *********************************************

#ifdef LINK_TIME_REGISTRATION

  /* The static members defined by static_members.hpp (pulled in via the in-core
     macros) are provided by the main gambit translation unit; defining them here
     too would break the link with duplicate definitions. */
  #define GAMBIT_NO_STATIC_MEMBER_DEFINITIONS 1

  #include "gambit/Backends/backend_rollcall.hpp"

#endif
