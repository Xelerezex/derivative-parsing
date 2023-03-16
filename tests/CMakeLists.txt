cmake_minimum_required(VERSION 3.20.0)

project(tests)

enable_testing()

add_executable(tests tests.cpp)

target_include_directories(
    ${PROJECT_NAME} 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR/src} 
)

target_link_libraries(tests sources gtest gmock pthread)