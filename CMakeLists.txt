cmake_minimum_required(VERSION 3.10)
project(AutoComplete)

set(CMAKE_CXX_STANDARD 17)

# Set output directory for the executable to the project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(AutoComplete 
    SRC/main.cpp
    Utilities/Data_Structures/Trie.cpp
)
