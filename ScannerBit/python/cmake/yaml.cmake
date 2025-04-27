include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(yaml
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_PROGRESS TRUE
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/contrib/yaml-cpp"
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/contrib/yaml-cpp/build"
    PATCH_COMMAND ${CMAKE_COMMAND} -E make_directory build
    CONFIGURE_COMMAND  ${CMAKE_COMMAND} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DBUILD_SHARED_LIBS=ON .. 
    BUILD_COMMAND make yaml-cpp
    INSTALL_COMMAND ""
  )

add_custom_target(yaml-distclean COMMAND ${CMAKE_COMMAND} -E remove_directory "contrib/yaml-cpp" 
                                 COMMAND ${CMAKE_COMMAND} -E remove_directory "${PROJECT_BINARY_DIR}/yaml-prefix" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
