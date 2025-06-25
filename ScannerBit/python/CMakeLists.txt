
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include(cmake/scannerbit_python_interface_utils.cmake)
include(cmake/boost_python.cmake)
#include(cmake/yaml.cmake)

if(PYTHONINTERP_FOUND)

    if(VERBOSE_SCANNERBIT_PYTHON_INTERFACE)
        message("${BoldYellow}Python extensive module Python deps:${ColourReset}")
        message("-- Python version string: ${PYTHON_VERSION_STRING}")
        message("-- Python include dirs: ${PYTHON_INCLUDE_DIRS}")
        message("-- Python executable: ${PYTHON_EXECUTABLE}")
    endif(VERBOSE_SCANNERBIT_PYTHON_INTERFACE)
    
    if(HDF5_FOUND)
        add_definitions(-DWITH_HDF5)
    endif(HDF5_FOUND)
    
    ################## ScannerBit_python_interface ##################
    
    set(scan_module_libraries
        #${PYTHON_LIBRARIES}
        yaml-cpp
        ${OpenMP_omp_LIBRARY}
    )
    
    set(scan_module_include_dirs
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
    
    set(scan_module_headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include/python.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/interface.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/python_utils.hpp
    )
    
    set(scan_module_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/diagnostics.cpp
        $<TARGET_OBJECTS:ScannerBit>
        $<TARGET_OBJECTS:Printers>
        ${GAMBIT_BASIC_COMMON_OBJECTS}
    )
    
    set(scan_module_rpaths
    )

    add_library(ScannerBit_python_interface SHARED ${scan_module_sources} ${scan_module_headers} )
    
    target_link_libraries(ScannerBit_python_interface ${scan_module_libraries})

    if(APPLE)
        set_target_properties(ScannerBit_python_interface PROPERTIES 
                                            #CXX_VISIBILITY_PRESET default
                                            #VISIBILITY_INLINES_HIDDEN FALSE
                                            INSTALL_RPATH "${scan_module_rpaths}"
                                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                            LIBRARY_OUTPUT_NAME "ScannerBit"
                                            INCLUDE_DIRECTORIES "${scan_module_include_dirs}"
                                            LINKER_LANGUAGE CXX
                                            LINK_FLAGS "-undefined dynamic_lookup"
                                            PREFIX ""
                                            SUFFIX .so)
    else(APPLE)
        set_target_properties(ScannerBit_python_interface PROPERTIES 
                                            #CXX_VISIBILITY_PRESET default
                                            #VISIBILITY_INLINES_HIDDEN FALSE
                                            INSTALL_RPATH "${scan_module_rpaths}"
                                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                            LIBRARY_OUTPUT_NAME "ScannerBit"
                                            INCLUDE_DIRECTORIES "${scan_module_include_dirs}"
                                            LINKER_LANGUAGE CXX
                                            PREFIX ""
                                            SUFFIX .so)
    endif(APPLE)
                                    
    add_gambit_deps(ScannerBit_python_interface)
    
    #################################################

else()

    message("${BoldRed}-- The ScannerBit python interface requires Python. ${ColourReset}")
    message("${Red}-- PYTHONINTERP_FOUND=${PYTHONINTERP_FOUND} ${ColourReset}")

endif()
