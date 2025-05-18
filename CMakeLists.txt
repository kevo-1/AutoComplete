cmake_minimum_required(VERSION 3.10)

project(AutoComplete)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set QT path (in case you're still using any Qt6 non-GUI modules later)
set(CMAKE_PREFIX_PATH "D:/QT/6.9.0/mingw_64/lib/cmake")

# Copy dictionary file to build directory at configure time
configure_file(
    ${CMAKE_SOURCE_DIR}/Storage/dictionary.txt
    ${CMAKE_BINARY_DIR}/dictionary.txt
    COPYONLY
)

# Recursively collect source files
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/SRC/*.cpp
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Structures/*.cpp
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Fetching/*.cpp
    ${CMAKE_SOURCE_DIR}/Utilities/Input_Handling/liveInput.cpp
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Structures
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Fetching
    ${CMAKE_SOURCE_DIR}/Utilities/Input_Handling
)

# Define the executable
add_executable(AutoComplete ${SRC_FILES})

# Post-build step to copy dictionary.txt to the output directory
add_custom_command(TARGET AutoComplete POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Storage/dictionary.txt
        $<TARGET_FILE_DIR:AutoComplete>/dictionary.txt
    COMMENT "Copying dictionary.txt to output directory"
)
