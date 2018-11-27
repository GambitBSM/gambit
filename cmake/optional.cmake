# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script to look for optional
#  things for GAMBIT.
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
#  \date 2015 May
#
#  \author Will Handley
#          (wh260@cam.ac.uk)
#  \date 2018 May
#
#************************************************

# Check for MPI libraries; disable manually with "cmake -DMPI=OFF .."
option(MPI "Compile with MPI enabled" ON)
if(MPI)
  find_package(MPI)
  # Do things for GAMBIT itself
  if(MPI_C_FOUND OR MPI_CXX_FOUND)
    message("${BoldYellow}-- MPI C/C++ libraries found. GAMBIT will be MPI-enabled.${ColourReset}")
    add_definitions(-DWITH_MPI)
    if(MPI_CXX_FOUND)
      include_directories(${MPI_CXX_INCLUDE_PATH})
      add_definitions(${MPI_CXX_COMPILE_FLAGS})
    endif()
    if(MPI_C_FOUND)
      include_directories(${MPI_C_INCLUDE_PATH})
      add_definitions(${MPI_C_COMPILE_FLAGS})
      if (NOT MPI_CXX_FOUND)
        message("${Red}-- Warning: C MPI libraries found, but not C++ MPI libraries.  Usually that's OK, but")
        message("   if you experience MPI linking errors, please install C++ MPI libraries as well.${CoulourReset}")
      endif()
    endif()
  else()
    message("${BoldRed}   Missing C MPI installation.  GAMBIT will not be MPI-enabled.${ColourReset}")
  endif()
  # Do things for Fortran backends and scanners
  if(MPI_Fortran_FOUND)
    if(MPI_C_FOUND)
      message("${BoldYellow}-- MPI Fortran libraries found. Fortran scanners will be MPI-enabled.${ColourReset}")
      # Includes
      foreach(dir ${MPI_Fortran_INCLUDE_PATH})
        set(GAMBIT_MPI_F_INC "${GAMBIT_MPI_F_INC} -I${dir}")
      endforeach()
      string(STRIP "${GAMBIT_MPI_F_INC}" GAMBIT_MPI_F_INC)
      set(BACKEND_Fortran_FLAGS_PLUS_MPI "${MPI_Fortran_COMPILE_FLAGS} ${BACKEND_Fortran_FLAGS} -DMPI ${GAMBIT_MPI_F_INC}")
      string(STRIP "${BACKEND_Fortran_FLAGS_PLUS_MPI}" BACKEND_Fortran_FLAGS_PLUS_MPI)
      # Libraries
      foreach(lib ${MPI_Fortran_LIBRARIES})
        set(GAMBIT_MPI_F_LIB "${GAMBIT_MPI_F_LIB} ${lib}")
      endforeach()
      if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(GAMBIT_MPI_F_LIB "-Wl,--no-as-needed ${GAMBIT_MPI_F_LIB}")
      endif()
      string(STRIP "${GAMBIT_MPI_F_LIB}" GAMBIT_MPI_F_LIB)
      set(CMAKE_Fortran_MPI_SO_LINK_FLAGS "${MPI_Fortran_LINK_FLAGS} ${GAMBIT_MPI_F_LIB}")
      string(STRIP "${CMAKE_Fortran_MPI_SO_LINK_FLAGS}" CMAKE_Fortran_MPI_SO_LINK_FLAGS)
    endif()
  else()
    message("${BoldRed}   Missing Fortran MPI installation.  Fortran scanners will not be MPI-enabled.${ColourReset}")
  endif()

  # Do things for C++ backends and scanners
  if(MPI_CXX_FOUND)
    if(MPI_C_FOUND)
      message("${BoldYellow}-- MPI C++ libraries found. C++ scanners will be MPI-enabled.${ColourReset}")
      # Includes
      foreach(dir ${MPI_CXX_INCLUDE_PATH})
        set(GAMBIT_MPI_CXX_INC "${GAMBIT_MPI_CXX_INC} -I${dir}")
      endforeach()
      string(STRIP "${GAMBIT_MPI_CXX_INC}" GAMBIT_MPI_CXX_INC)
      set(BACKEND_CXX_FLAGS_PLUS_MPI "${MPI_CXX_COMPILE_FLAGS} ${BACKEND_CXX_FLAGS} -DMPI ${GAMBIT_MPI_CXX_INC}")
      string(STRIP "${BACKEND_CXX_FLAGS_PLUS_MPI}" BACKEND_CXX_FLAGS_PLUS_MPI)
      # Libraries
      foreach(lib ${MPI_CXX_LIBRARIES})
        set(GAMBIT_MPI_CXX_LIB "${GAMBIT_MPI_CXX_LIB} ${lib}")
      endforeach()
      if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(GAMBIT_MPI_CXX_LIB "-Wl,--no-as-needed ${GAMBIT_MPI_CXX_LIB}")
      endif()
      string(STRIP "${GAMBIT_MPI_CXX_LIB}" GAMBIT_MPI_CXX_LIB)
      set(CMAKE_CXX_MPI_SO_LINK_FLAGS "${MPI_CXX_LINK_FLAGS} ${GAMBIT_MPI_F_LIB}")
      string(STRIP "${CMAKE_CXX_MPI_SO_LINK_FLAGS}" CMAKE_CXX_MPI_SO_LINK_FLAGS)
    endif()
  else()
    message("${BoldRed}   Missing C++ MPI installation.  C++ scanners will not be MPI-enabled.${ColourReset}")
  endif()
else()
  message("${BoldCyan} X MPI manually disabled. Executables will not be parallelised via MPI.${ColourReset}")
endif()

# Check for LAPACK.  Cmake native findLAPACK isn't very thorough, so we need to do a bit more work here.
if(NOT LAPACK_LINKLIBS)
  find_package(LAPACK)
  if(LAPACK_FOUND)
    # Check the libs for MKL
    string(FIND "${LAPACK_LIBRARIES}" "libmkl_" FOUND_MKL)
    foreach(lib ${LAPACK_LIBRARIES})
      string(REGEX REPLACE "^(.*)/(.*)\\..*$" "\\1" BLAS_LAPACK_LOCATION ${lib})
      if(NOT ${FOUND_MKL} EQUAL -1)
        # Add the silver-bullet SDL mkl_rt.so if possible.
        set(SDL "${BLAS_LAPACK_LOCATION}/libmkl_rt.so")
        if(EXISTS ${SDL})
          set(LAPACK_LINKLIBS "${LAPACK_LINKLIBS} ${SDL}")
        endif()
      endif()
      string(FIND "${lib}" ".framework" IS_FRAMEWORK)
      if(NOT ${IS_FRAMEWORK} EQUAL -1)
        string(REGEX REPLACE "^(.*)/(.*)\\.framework.*$" "-F\\1 -framework \\2" lib ${lib})
      endif()
      set(LAPACK_LINKLIBS "${LAPACK_LINKLIBS} ${lib}")
    endforeach()
    string(STRIP "${LAPACK_LINKLIBS}" LAPACK_LINKLIBS)
    message("   using the following LAPACK libraries: ${LAPACK_LINKLIBS}")
  endif()
else()
  message("${BoldCyan}   LAPACK linking commands provided by hand; skipping cmake search and assuming no LAPACK-dependent components need to be ditched.${ColourReset}")
endif()
string( REGEX MATCH "\\.l*a[:space:]*$" LAPACK_STATIC "${LAPACK_LINKLIBS}" )
if(LAPACK_STATIC OR (NOT LAPACK_LINKLIBS AND NOT LAPACK_FOUND))
  message(FATAL_ERROR "${BoldRed}LAPACK shared libraries are currently required in order to build GAMBIT.${ColourReset}")
  # In future MN and FS need to be ditched if lapack cannot be found, and the build allowed to continue.
  message("${BoldRed}   LAPACK shared library not found. Excluding FlexibleSUSY and MultiNest from GAMBIT configuration. ${ColourReset}")
endif()

# Check for ROOT.  Always look, in case the wise user has uninstalled it since last cmaking.
unset(ROOT_CONFIG_EXECUTABLE CACHE)
find_package(ROOT)
if (NOT ROOT_FOUND OR ROOT_VERSION VERSION_GREATER 6)
  # Excluding GreAT and RestFrames from GAMBIT
  if (NOT ROOT_FOUND)
    message("${BoldRed}   No ROOT installation found. Excluding GreAT and RestFrames from GAMBIT configuration. ${ColourReset}")
    set (EXCLUDE_ROOT TRUE)
    set (itch "${itch}" "great" "RestFrames")
  else()
    set (ROOT_6_OR_LATER_FOUND 1)
    include_directories(${ROOT_INCLUDE_DIR})
    set (EXCLUDE_ROOT FALSE)
  endif()
else()
  include_directories(${ROOT_INCLUDE_DIR})
  set (EXCLUDE_ROOT FALSE)
endif()

# Check for HDF5 libraries
find_package(HDF5 QUIET COMPONENTS C)
if(HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIR})  # for older versions of cmake
  include_directories(${HDF5_INCLUDE_DIRS}) # for newer cmake
  message("-- Found HDF5 libraries: ${HDF5_LIBRARIES}")
  if (VERBOSE)
    message(STATUS ${HDF5_INCLUDE_DIRS} ${HDF5_INCLUDE_DIR})
  endif()
else()
  message("${BoldRed}   No HDF5 C libraries found. Excluding hdf5printer and hdf5reader from GAMBIT configuration.${ColourReset}")
  set (itch "${itch}" "hdf5printer" "hdf5reader")
endif()

