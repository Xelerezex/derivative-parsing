cmake_minimum_required(VERSION 3.20.0)

set(
    TEST_TARGET_NAME tests
)

add_executable(${TEST_TARGET_NAME} tests.cpp)

# Added included directories to target (real path in proj dir)
# Helps us remove full path to file in #include "smth/libs/somefile.hpp" to "somefile.hpp"
target_include_directories(
    ${TEST_TARGET_NAME} 
        PUBLIC
            ${PROJECT_SOURCE_DIR}/src
)

# Target often keeps in build/. Here we should set path to .a or .dll
# or to any source files
target_link_directories(
    ${TEST_TARGET_NAME} 
        PRIVATE 
            ${PROJECT_SOURCE_DIR}/src
)

# After adding directories paths, we should only added libs names
target_link_libraries(
    ${TEST_TARGET_NAME}
        PRIVATE
            sources
            gtest 
            gmock 
            pthread
)

# Enable testing
enable_testing()

# Added tests
add_test(
    NAME              TestToken
    COMMAND           ${TEST_TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

message("---> PATH IN PROJECT_SOURCE_DIR IS:"       ${PROJECT_SOURCE_DIR})
message("---> PATH IN CMAKE_CURRENT_SOURCE_DIR IS:" ${CMAKE_CURRENT_SOURCE_DIR})
message("---> PATH IN CMAKE_CURRENT_BINARY_DIR IS:" ${CMAKE_CURRENT_BINARY_DIR})