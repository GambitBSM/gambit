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
#          (tomas.gonzalo@monash.edu)
#  \date 2020
#
#  \author Anders Kvellestad
#          (anders.kvellestad@fys.uio.no)
#  \date 2023
#
#************************************************

# Add some programs that use the GAMBIT physics libraries but not GAMBIT itself.
add_standalone(ExampleBit_A_standalone SOURCES ExampleBit_A/examples/ExampleBit_A_standalone_example.cpp MODULES ExampleBit_A)
add_standalone(CBS SOURCES ColliderBit/examples/solo.cpp MODULES ColliderBit DEPENDENCIES hepmc)
add_standalone(DarkBit_standalone_MSSM SOURCES DarkBit/examples/DarkBit_standalone_MSSM.cpp MODULES DarkBit)
add_standalone(DarkBit_standalone_ScalarSingletDM_Z2 SOURCES DarkBit/examples/DarkBit_standalone_ScalarSingletDM_Z2.cpp MODULES DarkBit)
add_standalone(DarkBit_standalone_WIMP SOURCES DarkBit/examples/DarkBit_standalone_WIMP.cpp MODULES DarkBit)
add_standalone(3bithit SOURCES DecayBit/examples/3bithit.cpp MODULES DecayBit SpecBit PrecisionBit)
add_standalone(FlavBit_standalone SOURCES FlavBit/examples/FlavBit_standalone_example.cpp MODULES FlavBit)

# Add a message that is only shown if CBS is built 
# and -O3 level compiler optimisations are not activated.
if((NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release") AND (NOT ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo"))
  add_custom_command(
    TARGET CBS POST_BUILD
    COMMENT "\n${BoldYellow}-- You have built CBS with CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}. For best performance we recommend building CBS in 'Release' mode. You can do this by rerunning cmake with the option -DCMAKE_BUILD_TYPE=Release and then rebuild CBS. ${ColourReset}\n\n"
  )
endif()
