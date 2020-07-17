# Install script for directory: /home/cristian/gambitgit

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "None")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/cristian/gambitgit/contrib/pybind11/cmake_install.cmake")
  include("/home/cristian/gambitgit/Logs/cmake_install.cmake")
  include("/home/cristian/gambitgit/Utils/cmake_install.cmake")
  include("/home/cristian/gambitgit/Core/cmake_install.cmake")
  include("/home/cristian/gambitgit/Models/cmake_install.cmake")
  include("/home/cristian/gambitgit/Backends/cmake_install.cmake")
  include("/home/cristian/gambitgit/Elements/cmake_install.cmake")
  include("/home/cristian/gambitgit/Printers/cmake_install.cmake")
  include("/home/cristian/gambitgit/ScannerBit/cmake_install.cmake")
  include("/home/cristian/gambitgit/FlavBit/cmake_install.cmake")
  include("/home/cristian/gambitgit/SpecBit/cmake_install.cmake")
  include("/home/cristian/gambitgit/DecayBit/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/cristian/gambitgit/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
