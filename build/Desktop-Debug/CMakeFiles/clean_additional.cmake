# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/kursovaya11_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/kursovaya11_autogen.dir/ParseCache.txt"
  "kursovaya11_autogen"
  )
endif()
