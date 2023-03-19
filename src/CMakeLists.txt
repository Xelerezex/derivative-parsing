cmake_minimum_required(VERSION 3.20.0)

set(
    SOURCE_TARGET_NAME sources
)

add_library(
    ${SOURCE_TARGET_NAME} 
        STATIC 
        token.cpp)
