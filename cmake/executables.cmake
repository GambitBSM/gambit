# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration script for final executables
#  of GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#        2015 Feb
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#
#************************************************

# Add the module standalones
add_custom_target(standalones)
include(cmake/standalones.cmake)

# Add the main GAMBIT executable
if(EXISTS "${PROJECT_SOURCE_DIR}/Core/")
  if (NOT EXCLUDE_FLEXIBLESUSY)
    set(gambit_XTRA ${flexiblesusy_LDFLAGS})
  endif()
  if (NOT EXCLUDE_ROOT)
    set(gambit_XTRA ${gambit_XTRA} ${ROOT_LIBRARIES})
    if (NOT EXCLUDE_RESTFRAMES)
      set(gambit_XTRA ${gambit_XTRA} ${RESTFRAMES_LDFLAGS})
    endif()
  endif()
  if (NOT EXCLUDE_HEPMC)
    set(gambit_XTRA ${gambit_XTRA} ${HEPMC_LDFLAGS})
  endif()
  add_gambit_executable(${PROJECT_NAME} "${gambit_XTRA}"
                        SOURCES ${PROJECT_SOURCE_DIR}/Core/src/gambit.cpp
                                ${GAMBIT_ALL_COMMON_OBJECTS}
                                ${GAMBIT_BIT_OBJECTS}
                                $<TARGET_OBJECTS:Core>
                                $<TARGET_OBJECTS:Printers>
  )
  set_target_properties(gambit PROPERTIES EXCLUDE_FROM_ALL 0)
  # EXPERIMENTAL: Linking against Electric Fence for heap corruption debugging
  #target_link_libraries(gambit PUBLIC efence) # just segfaults. Be good if it could be made to work though.
  # If Mathematica is present and the system is OS X, absolutize paths to avoid dylib errors
  if (${HAVE_MATHEMATICA} AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    Mathematica_ABSOLUTIZE_LIBRARY_DEPENDENCIES(gambit)
  endif()
endif()

# Add the ScannerBit standalone executable
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  if(EXISTS "${PROJECT_SOURCE_DIR}/Elements/")
    if (NOT EXCLUDE_FLEXIBLESUSY)
      set(ScannerBit_XTRA ${flexiblesusy_LDFLAGS})
    endif()
  endif()
  add_gambit_executable(ScannerBit_standalone "${ScannerBit_XTRA}"
                        SOURCES ${PROJECT_SOURCE_DIR}/ScannerBit/examples/ScannerBit_standalone.cpp
                                $<TARGET_OBJECTS:ScannerBit>
                                $<TARGET_OBJECTS:Printers>
                                ${GAMBIT_BASIC_COMMON_OBJECTS}
  )
  if(EXISTS "${PROJECT_SOURCE_DIR}/Elements/")
    if (NOT EXCLUDE_FLEXIBLESUSY)
      add_dependencies(ScannerBit_standalone flexiblesusy)
    endif()
  else()
    # Make sure the printers compile OK if the rest of GAMBIT is missing
    target_compile_definitions(Printers PRIVATE SCANNER_STANDALONE)
  endif()
  add_dependencies(standalones ScannerBit_standalone)
endif()

# Add C++ hdf5 combine tool, if we have HDF5 libraries
# There are a lot of annoying peripheral dependencies on GAMBIT things here, would be good to try and decouple things better
if(HDF5_FOUND)
  if(EXISTS "${PROJECT_SOURCE_DIR}/Printers/")
    if(EXISTS "${PROJECT_SOURCE_DIR}/Utils/")
       add_gambit_executable(hdf5combine ${HDF5_LIBRARIES}
                        SOURCES ${PROJECT_SOURCE_DIR}/Printers/standalone/manual_hdf5_combine.cpp
                                $<TARGET_OBJECTS:Printers>
                                ${GAMBIT_BASIC_COMMON_OBJECTS}
                                )
       set_target_properties(hdf5combine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Printers/bin")
    endif()
  endif()
endif()


