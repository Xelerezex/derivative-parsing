cmake_minimum_required(VERSION 3.20.0)

project(derivative)

# Set flags for targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Debug mode: ON
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# Added folders for find other source files
include_directories(src)
include_directories(tests)
include_directories(main)

# Added folders for other CMakeLists.txt
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(main)

# Enable testing
include(CTest)

# enable_testing() doesn't works recursively -> it should be 
# added and in folder with tests and in root folder
enable_testing()
