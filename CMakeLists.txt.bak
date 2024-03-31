cmake_minimum_required (VERSION 3.10.2)
project (ST-3 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")

set(tool_dest "bin")
set(lib_dest "lib")
set(include_dest "include/")

add_subdirectory(src)
add_subdirectory(test)

add_executable(ST-3 src/TimedDoor.cpp)
target_include_directories(ST-3 PRIVATE include)

add_executable(tests test/tests.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE gtest gmock)
target_link_libraries(tests PRIVATE ST-3)