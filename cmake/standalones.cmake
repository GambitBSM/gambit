# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration script for standalone
#  programs that use some GAMBIT libraries.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2016
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@partner.kit.edu)
#  \date 2020
#  \date 2024
#
#  \author Anders Kvellestad
#          (anders.kvellestad@fys.uio.no)
#  \date 2023
#
#  \author Pengxuan Zhu
#          (pengxuan.zhu@adelaide.edu.au)
#  \date 2026 Aug
#
#************************************************

# Add some programs that use the GAMBIT physics libraries but not GAMBIT itself.
add_standalone(ExampleBit_A_standalone SOURCES ExampleBit_A/examples/ExampleBit_A_standalone_example.cpp MODULES ExampleBit_A)
add_standalone(DarkBit_standalone_MSSM SOURCES DarkBit/examples/DarkBit_standalone_MSSM.cpp MODULES DarkBit)
add_standalone(DarkBit_standalone_ScalarSingletDM_Z2 SOURCES DarkBit/examples/DarkBit_standalone_ScalarSingletDM_Z2.cpp MODULES DarkBit)
add_standalone(DarkBit_standalone_WIMP SOURCES DarkBit/examples/DarkBit_standalone_WIMP.cpp MODULES DarkBit DEPENDENCIES pybind11)
add_standalone(3bithit SOURCES DecayBit/examples/3bithit.cpp MODULES DecayBit SpecBit PrecisionBit)
add_standalone(FlavBit_standalone SOURCES FlavBit/examples/FlavBit_standalone_example.cpp MODULES FlavBit)
add_standalone(NeutrinoBit_standalone SOURCES NeutrinoBit/examples/NeutrinoBit_standalone.cpp MODULES NeutrinoBit)
add_standalone(NeutrinoBit_standalone_RHN SOURCES NeutrinoBit/examples/NeutrinoBit_standalone_RHN.cpp MODULES NeutrinoBit)

if(";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  # This library is intentionally CBS-specific. It must precede RestFrames in
  # the link order so its constructor can quiet RestFrames for CBS CLI paths.
  add_library(cbs_preload SHARED
    "${PROJECT_SOURCE_DIR}/ColliderBit/examples/cbs_preload.cpp")
  set_target_properties(cbs_preload PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/contrib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/contrib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/contrib")
  add_standalone(CBS
    SOURCES ColliderBit/examples/solo.cpp ColliderBit/examples/solo_cli.cpp
            ColliderBit/examples/solo_input.cpp ColliderBit/examples/solo_batch.cpp
            ColliderBit/examples/solo_output.cpp
    LIBRARIES cbs_preload
    MODULES ColliderBit
    DEPENDENCIES hepmc pybind11 nulike_1.0.9)
  if(TARGET CBS AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Retain the constructor-only shared library under GNU ld's --as-needed.
    target_link_options(CBS PRIVATE "-Wl,--no-as-needed")
  endif()
endif()

if(TARGET CBS AND CBS_USE_LLD)
  target_link_options(CBS PRIVATE -fuse-ld=lld)
endif()

if(TARGET CBS AND NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release" AND NOT ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
  add_custom_command(
    TARGET CBS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "-- You have built CBS with CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}. For best performance we recommend building CBS in Release mode. You can do this by rerunning cmake with the option -DCMAKE_BUILD_TYPE=Release and then rebuild CBS."
  )
endif()
