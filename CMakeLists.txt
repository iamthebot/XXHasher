cmake_minimum_required(VERSION 3.5)
project(XXHasher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        README.md xxhasher.cpp)

add_executable(XXHasher ${SOURCE_FILES})

target_link_libraries(XXHasher xxhash)