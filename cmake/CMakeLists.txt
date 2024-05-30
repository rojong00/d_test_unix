cmake_minimum_required(VERSION 3.0)
project(cmake_longTime LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

set(TARGET_LIB sum)
#include_directories(${CMAKE_SOURCE_DIR}/lib/hdr)
add_library(${TARGET_LIB} SHARED ./lib/sum.c)
target_include_directories(${TARGET_LIB} PRIVATE ${CMAKE_SOURCE_DIR}/lib/hdr)

set(TARGET_APP main)
add_executable(${TARGET_APP} ./src/main.c)
target_include_directories(${TARGET_APP} PRIVATE ./src/hdr ./lib/hdr)
target_link_libraries(${TARGET_APP} ${TARGET_LIB})


