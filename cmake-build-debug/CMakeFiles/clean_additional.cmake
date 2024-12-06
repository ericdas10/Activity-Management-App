# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\labcorect_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\labcorect_autogen.dir\\ParseCache.txt"
  "labcorect_autogen"
  )
endif()
