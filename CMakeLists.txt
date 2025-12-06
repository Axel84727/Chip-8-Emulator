cmake_minimum_required(VERSION 3.16)
project(chip_8_emulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all .cpp files under src (recursive) and build the executable
file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/src/*.cpp")

if(NOT SRCS)
    message(FATAL_ERROR "No .cpp sources found in src/ (expected src/main.cpp etc.)")
endif()

add_executable(${PROJECT_NAME} ${SRCS})

# Use the top-level include directory
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
