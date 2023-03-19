cmake_minimum_required(VERSION 3.20.0)

set(
    MAIN_TARGET_NAME derivsolver
)

add_executable(${MAIN_TARGET_NAME} main.cpp)

# Added included directories to target (real path in proj dir)
# Helps us remove full path to file in #include "smth/libs/somefile.hpp" to "somefile.hpp"
target_include_directories(
    ${MAIN_TARGET_NAME} 
        PUBLIC
            ${PROJECT_SOURCE_DIR}/src
)

# Target often keeps in build/. Here we should set path to .a or .dll
# or to any source files
target_link_directories(
    ${MAIN_TARGET_NAME} 
        PRIVATE 
            ${PROJECT_SOURCE_DIR}/src
)

# After adding directories paths, we should only added libs names
target_link_libraries(
    ${MAIN_TARGET_NAME} 
        sources
)
