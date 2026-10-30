# Copy an extracted archive into its source tree without changing file mtimes.
# Autotools release packages rely on generated files being newer than inputs.
cmake_minimum_required(VERSION 3.16.3)

if(NOT DEFINED SOURCE_DIR OR NOT IS_DIRECTORY "${SOURCE_DIR}" OR
   NOT DEFINED DESTINATION_DIR OR "${DESTINATION_DIR}" STREQUAL "")
  message(FATAL_ERROR
    "copy_extracted_sources.cmake requires an existing -DSOURCE_DIR= and -DDESTINATION_DIR=")
endif()

# The trailing slash copies contents, including hidden files, rather than adding
# a container directory. file(COPY) preserves timestamps, permissions and links;
# cmake -E copy_directory replaces mtimes with the time each file was copied.
file(COPY "${SOURCE_DIR}/" DESTINATION "${DESTINATION_DIR}")
