
if (PYTHON_EXECUTABLE)
    execute_process (
            COMMAND ${PYTHON_EXECUTABLE} -c import\ numpy\;\ print\(numpy.get_include\(\)\)\;
            ERROR_VARIABLE NUMPY_INCLUDE_ERROR
            RESULT_VARIABLE NUMPY_INCLUDE_RETURN
            OUTPUT_VARIABLE NUMPY_INCLUDE_DIRS
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )
    execute_process (
            COMMAND ${PYTHON_EXECUTABLE} -c import\ numpy\;\ print\(numpy.__version__\);
            ERROR_VARIABLE NUMPY_VERSION_ERROR
            RESULT_VARIABLE NUMPY_VERSION_RESULT
            OUTPUT_VARIABLE NUMPY_VERSION_STRING
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )
    if (EXISTS ${NUMPY_INCLUDE_DIRS})
        SET(NUMPY_FOUND TRUE)
    else (EXISTS ${NUMPY_INCLUDE_DIRS})
        SET(NUMPY_FOUND FALSE)
    endif (EXISTS ${NUMPY_INCLUDE_DIRS})
else (PYTHON_EXECUTABLE)
    SET(NUMPY_FOUND FALSE)
endif(PYTHON_EXECUTABLE)
