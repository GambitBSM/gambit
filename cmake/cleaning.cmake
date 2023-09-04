# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script to add clean info
#  for GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#
#  \author Ben Farmer
#          (benjamin.farmer@fysik.su.se)
#  \date 2015 Feb
#
#************************************************

##### clean ########

# Get a list of all bits, including ditched ones.
retrieve_bits(ALL_GAMBIT_BITS ${PROJECT_SOURCE_DIR} "" "Quiet")

# Ensure that clean removes automatically-generated CMakeLists.txt files in modules
foreach(bit ${ALL_GAMBIT_BITS})
  set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/${bit}/CMakeLists.txt")
endforeach()
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Backends/CMakeLists.txt")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Printers/CMakeLists.txt")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Models/CMakeLists.txt")

# Make sure clean removes the scratch files indicating that the harvesters have been run.
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/modules_harvested")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/backends_harvested")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/models_harvested")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/printers_harvested")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/colliders_harvested")

# Arrange for removal of all generated headers upon "make clean".
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Models/include/gambit/Models/model_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Models/include/gambit/Models/model_types_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_functor_types.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Core/include/gambit/Core/module_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Elements/include/gambit/Elements/module_types_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Elements/include/gambit/Elements/module_functor_types.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Elements/include/gambit/Elements/elements_extras.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Printers/include/gambit/Printers/printer_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/cmake/include/gambit/cmake/cmake_variables.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/ScannerBit/include/gambit/ScannerBit/priors_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/ScannerBit/include/gambit/ScannerBit/test_function_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/ColliderBit/include/gambit/ColliderBit/ColliderBit_models_rollcall.hpp")
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/ColliderBit/include/gambit/ColliderBit/colliders/Pythia8/Py8Collider_typedefs.hpp")

# Arrange for the removal of generated source files with "make clean"
set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/Models/src/particle_database.cpp")
foreach(bit ${ALL_GAMBIT_BITS})
  set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/${bit}/examples/standalone_functors.cpp")
endforeach()

#Arrange for removal of other scanner-related generated files upon "make clean".
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  set(clean_files ${clean_files} "${PROJECT_BINARY_DIR}/linkedout.cmake")
  set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/scanbit_reqd_entries.yaml")
  set(clean_files ${clean_files} "${PROJECT_SOURCE_DIR}/scratch/build_time/scanbit_flags.yaml")
endif()

# Add all the clean files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${clean_files}")


##### distclean ########

# Add a true clean target that can have dependencies, to allow us to trigger cleaning of external projects (or run any other custom commands)
add_custom_target(distclean COMMAND ${MAKE_SERIAL} clean)

# Ensure that distclean cleans the backends (the entry for each backend will be added in backends.cmake)
add_custom_target(clean-backends)
add_dependencies(distclean clean-backends)

# Ensure that disclean cleans the scanners (the entry for each backend will be added in scanners.cmake)
add_custom_target(clean-scanners)
add_custom_target(clean-scanners-lib COMMAND ${CMAKE_COMMAND} -E remove * WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ScannerBit/lib)
add_dependencies(distclean clean-scanners clean-scanners-lib)

# Ensure that distclean sweeps out the scratch directory
add_custom_target(clean-scratch COMMAND ${CMAKE_COMMAND} -E remove_directory scratch WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_dependencies(distclean clean-scratch)

# Ensure that distclean sweeps out ScannerBit bin directory
add_custom_target(clean-scannerbit-bin COMMAND ${CMAKE_COMMAND} -E remove_directory bin WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ScannerBit)
add_dependencies(distclean clean-scannerbit-bin)

# Ensure that distclean removes .pyc files
add_custom_target(clean-pyc COMMAND ${CMAKE_COMMAND} -E remove *.pyc */*.pyc */*/*.pyc */*/*/*.pyc */*/*/*/*.pyc WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_dependencies(distclean clean-pyc)

# Ensure that distclean removes backup files
add_custom_target(clean-backup COMMAND ${CMAKE_COMMAND} -E remove *~ */*~ */*/*~ */*/*/*~ */*/*/*/*~ WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_dependencies(distclean clean-backup)

# Add clean targets for doxygen
add_custom_target(clean-docs WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                             COMMAND ${CMAKE_COMMAND} -E remove_directory doc/html
                             COMMAND ${CMAKE_COMMAND} -E remove doc/*.tmp)
add_dependencies(distclean clean-docs)


##### nuke ########

# Do everything in distclean and ensure that nuke sweeps out the backend and scanner download and install directories
add_custom_target(clean-backend-download COMMAND ${CMAKE_COMMAND} -E remove_directory Backends/downloaded WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_custom_target(clean-backend-install COMMAND ${CMAKE_COMMAND} -E remove_directory Backends/installed WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_custom_target(clean-scanner-download COMMAND ${CMAKE_COMMAND} -E remove_directory ScannerBit/downloaded WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_custom_target(clean-scanner-install COMMAND ${CMAKE_COMMAND} -E remove_directory ScannerBit/installed WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_custom_target(nuke-contrib)
add_custom_target(nuke-BOSS COMMAND ${CMAKE_COMMAND} -E remove_directory Backends/scripts/BOSS/castxml WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                            COMMAND ${CMAKE_COMMAND} -E remove Backends/scripts/BOSS/castxml*.tar.gz)
add_custom_target(nuke-backends DEPENDS clean-backend-download clean-backend-install)
add_custom_target(nuke-scanners DEPENDS clean-scanner-download clean-scanner-install)
add_custom_target(nuke-all DEPENDS distclean nuke-contrib nuke-backends nuke-scanners nuke-BOSS)
