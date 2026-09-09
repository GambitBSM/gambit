//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Link-time registration translation unit for
///  ColliderBit.
///
///  This file expands ColliderBit's rollcall
///  header tree (including the sub-rollcall
///  headers and the generated
///  ColliderBit_models_rollcall.hpp) in the
///  in-core macro context, exactly as the
///  generated module_rollcall.hpp would do inside
///  the Core, but from within a translation unit
///  owned by the module itself.  All functor
///  definitions and registration calls produced by
///  the in-core macros are therefore compiled into
///  this object file, and the registrations happen
///  during static initialisation, before main().
///
///  This file is only compiled into the main gambit
///  executable, and only when the CMake option
///  LINK_TIME_REGISTRATION is ON (in which case the
///  module harvester omits ColliderBit's rollcall
///  header from module_rollcall.hpp).  It must NOT
///  be compiled into the ColliderBit object
///  library: standalone executables (CBS) obtain
///  equivalent functor definitions from their own
///  main translation unit via standalone_module.hpp,
///  and would suffer duplicate-symbol errors.
///
///  The conditional-compilation guards used in the
///  ColliderBit rollcall headers (HAVE_PYBIND11,
///  EXCLUDE_HEPMC, EXCLUDE_YODA) all come from the
///  generated cmake_variables.hpp, so this TU sees
///  exactly the same configuration as the module's
///  own object files and the legacy in-core
///  expansion.
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

  #include "gambit/Elements/module_macros_incore.hpp"
  #include "gambit/ColliderBit/ColliderBit_rollcall.hpp"

#endif
