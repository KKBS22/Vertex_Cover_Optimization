cmake_minimum_required(VERSION 2.8)
project(ece650-a2)

## ECE650 Specific configuration start here
## Project specific configurations go here
file(GLOB LIB_SOURCES GraphList/*.cpp)
file(GLOB LIB_HEADERS GraphList/*.h)
add_library( GraphLib ${LIB_SOURCES} ${LIB_HEADERS} )



# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# create the main executable
## add additional .cpp files if needed
add_executable(ece650-a2 ece650-a2.cpp )
target_link_libraries(ece650-a2 GraphLib)
# create the executable for tests
add_executable(tests test.cpp)
