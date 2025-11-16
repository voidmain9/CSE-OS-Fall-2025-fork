cmake_minimum_required(VERSION 3.10)
project(GrooveOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(grooveos ${SRC_FILES})

target_include_directories(grooveos PRIVATE src)
