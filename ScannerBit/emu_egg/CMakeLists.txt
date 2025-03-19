
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")



################## ScannerBit_python_interface ##################

set(scan_emu_libraries
    #${PYTHON_LIBRARIES}
    yaml-cpp
    ${OpenMP_omp_LIBRARY}
    ${MPI_C_LIBRARIES}
    ${MPI_CXX_LIBRARIES}
    ${MPI_Fortran_LIBRARIES}
)

set(scan_emu_include_dirs
    ${GAMBIT_INCDIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${mkpath_INCLUDE_DIR}
    ${MPI_C_INCLUDE_PATH}
    ${MPI_CXX_INCLUDE_PATH}
    ${SQLite3_INCLUDE_DIRS}
    ${HDF5_INCLUDE_DIR}
    ${HDF5_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/contrib/pybind11/include
    ${yaml_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/ScannerBit/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(scan_emu_headers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/egg.hpp
)

set(scan_emu_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/egg.cpp
    #$<TARGET_OBJECTS:ScannerBit>
    #$<TARGET_OBJECTS:Printers>
    #${GAMBIT_BASIC_COMMON_OBJECTS}
)

set(scan_emu_rpaths
)

add_executable(ScannerBit_emu_egg ${scan_emu_sources} ${scan_emu_headers} )
target_link_libraries(ScannerBit_emu_egg ${scan_emu_libraries})

if(APPLE)
    set_target_properties(ScannerBit_emu_egg PROPERTIES 
                                        #CXX_VISIBILITY_PRESET default
                                        #VISIBILITY_INLINES_HIDDEN FALSE
                                        INSTALL_RPATH "${scan_emu_rpaths}"
                                        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/ScannerBit/bin"
                                        RUNTIME_OUTPUT_NAME "emu_egg"
                                        INCLUDE_DIRECTORIES "${scan_emu_include_dirs}"
                                        LINKER_LANGUAGE CXX
                                        LINK_FLAGS "-undefined dynamic_lookup")
else(APPLE)
    set_target_properties(ScannerBit_emu_egg PROPERTIES 
                                        #CXX_VISIBILITY_PRESET default
                                        #VISIBILITY_INLINES_HIDDEN FALSE
                                        INSTALL_RPATH "${scan_emu_rpaths}"
                                        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/ScannerBit/bin"
                                        RUNTIME_OUTPUT_NAME "emu_egg"
                                        INCLUDE_DIRECTORIES "${scan_emu_include_dirs}"
                                        LINKER_LANGUAGE CXX)
endif(APPLE)
                                
#add_gambit_deps(ScannerBit_python_interface)
