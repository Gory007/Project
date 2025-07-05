# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VocabularyTrainer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VocabularyTrainer_autogen.dir\\ParseCache.txt"
  "VocabularyTrainer_autogen"
  )
endif()
