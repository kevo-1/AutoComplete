# cmake_minimum_required(VERSION 3.10)

# project(AutoComplete)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_PREFIX_PATH "D:/QT/6.9.0/mingw_64/lib/cmake")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# find_package(Qt6 COMPONENTS
#         Core
#         Gui
#         Widgets
#         REQUIRED)

# # Output directory for the executable

# configure_file(
#     ${CMAKE_SOURCE_DIR}/Storage/dictionary.txt
#     ${CMAKE_BINARY_DIR}/dictionary.txt
#     COPYONLY
# )

# target_link_libraries(${AutoComplete}
#     Qt6::Widgets
# )

# # Recursively collect source files
# file(GLOB_RECURSE SRC_FILES
# ${CMAKE_SOURCE_DIR}/SRC/*.cpp
# ${CMAKE_SOURCE_DIR}/GUI/*.cpp 
# ${CMAKE_SOURCE_DIR}/GUI/*.ui 
# ${CMAKE_SOURCE_DIR}/Utilities/Data_Structures/*.cpp 
# ${CMAKE_SOURCE_DIR}/Utilities/Data_Fetching/*.cpp  
# )

# # Include directories for headers
# include_directories(
#     ${CMAKE_SOURCE_DIR}/Utilities/Data_Structures
#     ${CMAKE_SOURCE_DIR}/Utilities/Data_Fetching
#     ${CMAKE_SOURCE_DIR}/GUI
# )
    
# # Define the executable
# add_executable(AutoComplete ${SRC_FILES})


# add_custom_command(TARGET AutoComplete POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#         ${CMAKE_SOURCE_DIR}/Storage/dictionary.txt
#         $<TARGET_FILE_DIR:AutoComplete>/dictionary.txt
#     COMMENT "Copying dictionary.txt to output directory"
# )    
cmake_minimum_required(VERSION 3.30)
project(AutoComplete)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_PREFIX_PATH "D:/QT/6.9.0/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

configure_file(
        ${CMAKE_SOURCE_DIR}/Storage/Dictionary.txt
        ${CMAKE_BINARY_DIR}/Dictionary.txt
        COPYONLY
)

add_executable(AutoComplete
        SRC/main.cpp
        Utilities/Data_Structures/Trie.cpp
        Utilities/Data_Fetching/DataFetcher.cpp
        Utilities/Input_Handling/liveInput.cpp
        SRC/BFF/BFF.cpp
        GUI/mainwindow.cpp
        GUI/mainwindow.ui
)

target_link_libraries(AutoComplete
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

add_custom_command(TARGET AutoComplete POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Storage/dictionary.txt
        $<TARGET_FILE_DIR:AutoComplete>/dictionary.txt
    COMMENT "Copying dictionary.txt to output directory"
)   

set_target_properties(AutoComplete PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)