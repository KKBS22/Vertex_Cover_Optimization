cmake_minimum_required(VERSION 2.8)
project(a2ece650)

## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)

file(GLOB LIB_SOURCES GraphList/*.cpp)
file(GLOB LIB_HEADERS GraphList/*.h)
add_library( GraphLib ${LIB_SOURCES} ${LIB_HEADERS} )

# create the main executable
## add additional .cpp files if needed
add_executable(a2ece650 a2ece650.cpp )
add_executable(a3ece650 a3ece650.cpp )
add_executable(rgen random.cpp )
target_link_libraries(a2ece650 GraphLib)

# create the executable for tests
add_executable(tests test.cpp)
install(PROGRAMS a1ece650.py Graph.py Edge.py Streets.py StreetUtil.py Vertex.py DESTINATION bin)
install(TARGETS a2ece650 a3ece650 rgen RUNTIME DESTINATION bin)
