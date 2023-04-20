cmake_minimum_required(VERSION 3.20.0)

# Enable testing
enable_testing()

set(LIST TESTS)

# Append files name in list
list(APPEND TESTS test_token_type)
list(APPEND TESTS test_token)
list(APPEND TESTS test_utils)

foreach(TARGET_NAME IN LISTS TESTS)

    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    # Added included directories to target (real path in proj dir)
    # Helps us remove full path to file in #include "smth/libs/somefile.hpp" to "somefile.hpp"
    target_include_directories(
        ${TARGET_NAME} 
            PUBLIC
                ${PROJECT_SOURCE_DIR}/src
    )

    # Target often keeps in build/. Here we should set path to .a or .dll
    # or to any source files
    target_link_directories(
        ${TARGET_NAME} 
            PRIVATE 
                ${PROJECT_SOURCE_DIR}/src
    )

    # After adding directories paths, we should only added libs names
    target_link_libraries(
        ${TARGET_NAME}
            PRIVATE
                sources
                gtest 
                gmock 
                pthread
    )
    
    # Added tests
    add_test(
        NAME              ${TARGET_NAME}
        COMMAND           ${TARGET_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

endforeach()
