CMAKE_MINIMUM_REQUIRED(VERSION 2.8.10 FATAL_ERROR)
 
FIND_PACKAGE(PythonInterp REQUIRED)
FIND_PACKAGE(PythonLibs)
FIND_PACKAGE(NumPy) 
FIND_PACKAGE(Boost 1.41)

SET(BOOST_PYTHON_SRCS
                ${CMAKE_CURRENT_SOURCE_DIR}/src/list.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/long.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/dict.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/tuple.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/str.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/slice.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/converter/from_python.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/converter/registry.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/converter/type_id.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/enum.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/class.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/function.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/inheritance.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/life_support.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/pickle_support.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/errors.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/module.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/converter/builtin_converters.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/converter/arg_to_python_base.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/iterator.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/stl_iterator.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object_protocol.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object_operators.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/import.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/exec.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/object/function_doc_signature.cpp
)

SET(BOOST_NUMPY_SRCS
                ${BOOST_PYTHON_SRCS}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/numpy/dtype.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/numpy/matrix.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/numpy/ndarray.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/numpy/numpy.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/numpy/scalars.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/numpy/ufunc.cpp
)

SET(BOOST_PYTHON_FLAGS
                "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS} -O3 -DBOOST_ALL_NO_LIB"
)

SET(BOOST_PYTHON_INCLUDE_DIRS
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${Boost_INCLUDE_DIRS}
                ${PYTHON_INCLUDE_DIRS}
)

SET(BOOST_NUMPY_INCLUDE_DIRS
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${Boost_INCLUDE_DIRS}
                ${PYTHON_INCLUDE_DIRS}
                ${NUMPY_INCLUDE_DIRS}
)

ADD_LIBRARY(boost_python SHARED ${BOOST_PYTHON_SRCS})

TARGET_LINK_LIBRARIES(boost_python pthread ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES( boost_python
                       PROPERTIES
                       COMPILE_FLAGS "${BOOST_PYTHON_FLAGS}"
                       INCLUDE_DIRECTORIES "${BOOST_PYTHON_INCLUDE_DIRS}"
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                       LIBRARY_OUTPUT_NAME "boost_python${PYTHON_VERSION_STRING}"
                       SUFFIX .so)
                       
ADD_LIBRARY(boost_numpy SHARED ${BOOST_NUMPY_SRCS})

TARGET_LINK_LIBRARIES(boost_numpy pthread ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES( boost_numpy
                       PROPERTIES
                       COMPILE_FLAGS "${BOOST_PYTHON_FLAGS}"
                       INCLUDE_DIRECTORIES "${BOOST_NUMPY_INCLUDE_DIRS}"
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                       LIBRARY_OUTPUT_NAME "boost_numpy${PYTHON_VERSION_STRING}"
                       SUFFIX .so)
                       
