cmake_minimum_required(VERSION 3.10)
project(AutoComplete)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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
${CMAKE_SOURCE_DIR}/Utilities/Input_Handling/*.cpp   
)

# Include directories for headers
include_directories(
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Structures
    ${CMAKE_SOURCE_DIR}/Utilities/Data_Fetching
    ${CMAKE_SOURCE_DIR}/Utilities/Input_Handling/   

    )
    
# Define the executable
add_executable(AutoComplete ${SRC_FILES})

add_custom_command(TARGET AutoComplete POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Storage/dictionary.txt
        $<TARGET_FILE_DIR:AutoComplete>/dictionary.txt
    COMMENT "Copying dictionary.txt to output directory"
)    