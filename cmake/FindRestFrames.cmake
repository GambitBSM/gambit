# - Finds the RestFrames library
# This module defines the following variables:
#   RestFrames_FOUND  -  if the RestFrames library is found
#

# Look for RestFrames-1.0.1
# TODO: Look for RestFrames in other places than just contrib/
set(ver "1.0.1")
set(dir "${PROJECT_SOURCE_DIR}/contrib/RestFrames-${ver}")
unset(RestFrames_LIBRARY CACHE)
find_library(RestFrames_LIBRARY RestFrames ${dir}/lib/)
if(RestFrames_LIBRARY STREQUAL "RestFrames_LIBRARY-NOTFOUND")
  set(RestFrames_FOUND FALSE)
else()
  set(RestFrames_FOUND TRUE)
endif()
