# GAMBIT: Global and Modular BSM Inference Tool  
#************************************************
# \file                                          
#                                                
#  Cmake configuration script for things needed
#  for the main GAMBIT executable.
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
#  \date 2015 Apr
#                                               
#************************************************

# set include directores for GAMBIT
set(GAMBIT_INCDIRS ${GAMBIT_INCDIRS} "${PROJECT_SOURCE_DIR}/Printers/include"
                                     "${PROJECT_SOURCE_DIR}/Core/include"
                                     "${PROJECT_SOURCE_DIR}/Logs/include"
                                     "${PROJECT_SOURCE_DIR}/Utils/include"
                                     "${PROJECT_SOURCE_DIR}/Elements/include"
                                     "${PROJECT_SOURCE_DIR}/Models/include"
                                     "${PROJECT_SOURCE_DIR}/cmake/include"
                                     "${PROJECT_SOURCE_DIR}/Backends/include")

#set include directores for GAMBIT modules
retrieve_bits(GAMBIT_BITS ${PROJECT_SOURCE_DIR} "${itch}" "Quiet")
foreach(bit ${GAMBIT_BITS})
  set(GAMBIT_INCDIRS ${GAMBIT_INCDIRS} "${PROJECT_SOURCE_DIR}/${bit}/include")
endforeach()

