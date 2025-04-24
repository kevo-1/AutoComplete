cmake_minimum_required(VERSION 3.10)
project(AutoComplete)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Recursively collect source files
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/SRC/*.cpp
    ${CMAKE_SOURCE_DIR}/Utilities/**/*.cpp
)

# Include directories for headers
include_directories(
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Structures
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Fetcher
)

# Define the executable
add_executable(AutoComplete ${SRC_FILES})
