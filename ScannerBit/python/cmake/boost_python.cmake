include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(boost_python
    GIT_REPOSITORY https://github.com/boostorg/python.git
    GIT_PROGRESS TRUE
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/contrib/boost_python/build"
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/contrib/boost_python"
    PATCH_COMMAND cp ../../cmake/boost_python_install.cmake CMakeLists.txt
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -DPython3_EXECUTABLE=${Python3_EXECUTABLE} -DBoost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS} -DPython3_INCLUDE_DIRS=${Python3_INCLUDE_DIRS} -DPython3_LIBRARIES=${Python3_LIBRARIES} -DPython3_VERSION=${Python3_VERSION} -DNUMPY_INCLUDE_DIRS=${NUMPY_INCLUDE_DIRS} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} .. 
    BUILD_COMMAND make boost_python
    INSTALL_COMMAND ""
  )

add_custom_target(boost_python-distclean 
                                COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/contrib/boost_python"
                                COMMAND ${CMAKE_COMMAND} -E remove_directory "${PROJECT_BINARY_DIR}/ScannerBit/python/boost_python-prefix"
                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                )
                                 
