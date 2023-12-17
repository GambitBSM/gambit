# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script that checks if
#  the necessary Python modules are installed
#  for the different Python scanners in GAMBIT 
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Gregory Martinez
#          (gregory.david.martinez@gmail.com)
#  \date 2023 Jul
#
#  \author Anders Kvellestad
#          (anders.kvellestad@fys.uio.no)
#  \date 2023 Nov
#
#************************************************

# A macro for printing info messages about modules missing for Python scanners.
# Note that in some cases the pip package name differs from the module name,
# hence the need for both a "modules" and a "packages" argument.
macro(check_python_scanner_modules name modules packages)

  set(_modules ${modules} ${ARGN})
  string (REPLACE "," ";" _modules "${_modules}")
  string (REPLACE " " "" _modules "${_modules}")

  set(_packages ${packages} ${ARGN})
  string (REPLACE "," ";" _packages "${_packages}")
  string (REPLACE " " "" _packages "${_packages}")

  list(LENGTH _modules list_length)
  math(EXPR range_limit "${list_length} - 1")

  foreach(index RANGE ${range_limit})
    list(GET _modules ${index} module)
    list(GET _packages ${index} package)
    if (NOT DEFINED PY_${module}_FOUND)
      gambit_find_python_module(${module})
      if (NOT PY_${module}_FOUND)
        set(PY_${module}_FOUND FALSE)
      endif()
    endif()
    if (NOT PY_${module}_FOUND)
      set(packages_missing_${name} "${packages_missing_${name}},${package}" )
    endif()
  endforeach()

  if(packages_missing_${name})
    string (REPLACE "," " " missing "${packages_missing_${name}}")
    message("   To enable the scanner ${name}, please install the following Python packages:${missing}")
  endif()

endmacro()


# Run checks for all Python scanner plugins
message("${Yellow}-- Checking modules required by Python scanner plugins. ${ColourReset}")
check_python_scanner_modules(static_dynesty "dynesty,numpy" "dynesty,numpy")
check_python_scanner_modules(dynamic_dynesty "dynesty,numpy" "dynesty,numpy")
check_python_scanner_modules(emcee "emcee,numpy,h5py" "emcee,numpy,h5py")
check_python_scanner_modules(nautilus "nautilus,numpy" "nautilus-sampler,numpy")
check_python_scanner_modules(nessai_flow_sampler "nessai,numpy" "nessai,numpy")
check_python_scanner_modules(pocomc "pocomc,numpy" "pocomc,numpy")
check_python_scanner_modules(scipy_dual_annealing "scipy,numpy" "scipy,numpy")
check_python_scanner_modules(scipy_basin_hopping "scipy,numpy" "scipy,numpy")
check_python_scanner_modules(scipy_differential_evolution "scipy,numpy" "scipy,numpy")
check_python_scanner_modules(scipy_direct "scipy,numpy" "scipy,numpy")
check_python_scanner_modules(scipy_shgo "scipy,numpy" "scipy,numpy")
check_python_scanner_modules(scipy_minimize "scipy,numpy" "scipy,numpy")
check_python_scanner_modules(reactive_ultranest "ultranest,numpy,packaging" "ultranest,numpy,packaging")
check_python_scanner_modules(zeus "zeus,numpy" "zeus-mcmc,numpy")

