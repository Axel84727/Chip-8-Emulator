cmake_minimum_required(VERSION 3.16)
project(chip_8_emulator VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files from src directory
file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Verify source files exist
if(NOT SRCS)
    message(FATAL_ERROR "No .cpp source files found in src/ directory")
endif()

# Create executable
add_executable(${PROJECT_NAME} ${SRCS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"
)

# Find and link Raylib library
find_package(raylib QUIET)
if(raylib_FOUND)
    message(STATUS "Found raylib package")
    target_link_libraries(${PROJECT_NAME} raylib)
else()
    message(STATUS "Raylib package not found, attempting direct linking")
    target_link_libraries(${PROJECT_NAME} raylib)
endif()

# Platform-specific linking
if(APPLE)
    # macOS frameworks required for Raylib
    target_link_libraries(${PROJECT_NAME} 
        "-framework OpenGL" 
        "-framework Cocoa" 
        "-framework IOKit" 
        "-framework CoreVideo"
    )
elseif(UNIX AND NOT APPLE)
    # Linux libraries
    target_link_libraries(${PROJECT_NAME} 
        GL 
        m 
        pthread 
        dl 
        rt 
        X11
    )
elseif(WIN32)
    # Windows libraries
    target_link_libraries(${PROJECT_NAME} 
        opengl32 
        gdi32 
        winmm
    )
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Print configuration summary
message(STATUS "CHIP-8 Emulator Configuration:")
message(STATUS "  Project Name: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Source Files: ${SRCS}")
message(STATUS "  Include Directory: ${CMAKE_SOURCE_DIR}/include")
