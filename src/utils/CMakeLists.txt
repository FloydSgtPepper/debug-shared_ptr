cmake_minimum_required(VERSION 3.20)

add_library(UtilsIF INTERFACE "")

set_target_properties(UtilsIF
    PROPERTIES
        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
)


set(LOCAL_SOURCE
 )
 
set(LOCAL_HEADER
)

set(PUBLIC_HEADER
    ${CMAKE_CURRENT_LIST_DIR}/architecture.h
)

set(LOCAL_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
)

get_filename_component(INTERFACE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

#target_compile_options(UtilsIF
#    PRIVATE /W4)
    
target_sources(UtilsIF
    PRIVATE
        ${LOCAL_SOURCE}
    PRIVATE
        ${LOCAL_HEADER}
    PUBLIC
        ${PUBLIC_HEADER})
   
target_include_directories(UtilsIF
    INTERFACE
        ${INTERFACE_INCLUDE_DIRS}
)

ide_file_structure(UtilsIF " ")
