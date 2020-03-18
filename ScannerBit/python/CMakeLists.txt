
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include(cmake/scan_python_utils.cmake)
include(cmake/boost_python.cmake)
#include(cmake/yaml.cmake)

#find_package(NumPy)

if(PYTHONINTERP_FOUND)# AND PYTHONLIBS_FOUND)# AND NUMPY_FOUND)

    if(VERBOSE_SCAN_PYTHON)
        message("${BoldYellow}Python extensive module Python deps:${ColourReset}")
        message("-- Python version string: ${PYTHON_VERSION_STRING}")
        message("-- Python include dirs: ${PYTHON_INCLUDE_DIRS}")
        message("-- Python executable: ${PYTHON_EXECUTABLE}")
    endif(VERBOSE_SCAN_PYTHON)
    
    if(HDF5_FOUND)
        add_definitions(-DWITH_HDF5)
    endif(HDF5_FOUND)
    
    ############### scan_boost_python ###############
    
    set(scan_boost_module_libraries
        #${PYTHON_LIBRARIES}
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/boost_python/lib/libboost_python${PYTHON_VERSION_STRING}.so
        ${OpenMP_omp_LIBRARY}
        yaml-cpp
    )
    
     set(scan_boost_module_include_dirs
        ${GAMBIT_INCDIRS}
        ${mkpath_INCLUDE_DIR}
        ${MPI_C_INCLUDE_PATH}
        ${MPI_CXX_INCLUDE_PATH}
        ${yaml_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/ScannerBit/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/boost_python/include
    )
    
    set(scan_boost_module_headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include/interface.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/python_utils_boost.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/run_scan_boost.hpp
    )
    
    set(scan_boost_module_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/python_boost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/diagnostics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/run_scan.cpp
        $<TARGET_OBJECTS:ScannerBit>
        $<TARGET_OBJECTS:Printers>
        ${GAMBIT_BASIC_COMMON_OBJECTS}
    )
    
    set(scan_boost_module_rpaths
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/boost_python/lib
    )

    
    
    add_library(scan_boost_python SHARED ${scan_boost_module_sources} ${scan_boost_module_headers} )
    
    target_link_libraries(scan_boost_python ${scan_boost_module_libraries})

    if(APPLE)
        set_target_properties(scan_boost_python PROPERTIES 
                                            #CXX_VISIBILITY_PRESET default
                                            #VISIBILITY_INLINES_HIDDEN FALSE
                                            INSTALL_RPATH "${scan_boost_module_rpaths}"
                                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                            LIBRARY_OUTPUT_NAME "BoostScannerBit"
                                            INCLUDE_DIRECTORIES "${scan_boost_module_include_dirs}"
                                            LINKER_LANGUAGE CXX
                                            LINK_FLAGS "-undefined dynamic_lookup"
                                            PREFIX ""
                                            SUFFIX .so)
    else(APPLE)
        set_target_properties(scan_boost_python PROPERTIES 
                                            #CXX_VISIBILITY_PRESET default
                                            #VISIBILITY_INLINES_HIDDEN FALSE
                                            INSTALL_RPATH "${scan_boost_module_rpaths}"
                                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                            LIBRARY_OUTPUT_NAME "BoostScannerBit"
                                            INCLUDE_DIRECTORIES "${scan_boost_module_include_dirs}"
                                            LINKER_LANGUAGE CXX
                                            PREFIX ""
                                            SUFFIX .so)
    endif(APPLE)
                                    
    add_dependencies(scan_boost_python boost_python)
    add_gambit_deps(scan_boost_python)
    
    ################## scan_python ##################
    
    set(scan_module_libraries
        #${PYTHON_LIBRARIES}
        yaml-cpp
        ${OpenMP_omp_LIBRARY}
    )
    
    set(scan_module_include_dirs
        ${GAMBIT_INCDIRS}
        ${mkpath_INCLUDE_DIR}
        ${MPI_C_INCLUDE_PATH}
        ${MPI_CXX_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/contrib/pybind11/include
        ${yaml_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/ScannerBit/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    set(scan_module_headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include/interface.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/python_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/run_scan.hpp
    )
    
    set(scan_module_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/diagnostics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/run_scan.cpp
        $<TARGET_OBJECTS:ScannerBit>
        $<TARGET_OBJECTS:Printers>
        ${GAMBIT_BASIC_COMMON_OBJECTS}
    )
    
    set(scan_module_rpaths
    )

    add_library(scan_python SHARED ${scan_module_sources} ${scan_module_headers} )
    
    target_link_libraries(scan_python ${scan_module_libraries})

    if(APPLE)
        set_target_properties(scan_python PROPERTIES 
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
        set_target_properties(scan_python PROPERTIES 
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
                                    
    add_gambit_deps(scan_python)
    
    #################################################

else(PYTHONINTERP_FOUND)# AND PYTHONLIBS_FOUND)# AND NUMPY_FOUND)

    message("${BoldRed}-- The ScannerBit python interface requires python, the python libraries, and numpy ${ColourReset}")
    message("${Red}-- PYTHONINTERP_FOUND=${PYTHONINTERP_FOUND} ${ColourReset}")
    message("${Red}-- PYTHONLIBS_FOUND=${PYTHONLIBS_FOUND} ${ColourReset}")
    message("${Red}-- NUMPY_FOUND=${NUMPY_FOUND} ${ColourReset}")

endif(PYTHONINTERP_FOUND)# AND PYTHONLIBS_FOUND)# AND NUMPY_FOUND)
