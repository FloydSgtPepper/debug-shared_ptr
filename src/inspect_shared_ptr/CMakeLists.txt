cmake_minimum_required(VERSION 3.20)

add_library(inspect_shared_ptr INTERFACE "")

set_target_properties(inspect_shared_ptr
    PROPERTIES
        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
)


set(LOCAL_SOURCE
 )
 
set(LOCAL_HEADER
)

set(PUBLIC_HEADER
    ${CMAKE_CURRENT_LIST_DIR}/inspect_shared_ptr.hpp
    ${CMAKE_CURRENT_LIST_DIR}/detail/enable_shared_from_this.hpp
    ${CMAKE_CURRENT_LIST_DIR}/detail/inspect_shared_ptr_def.h
    ${CMAKE_CURRENT_LIST_DIR}/detail/PtrBase.hpp
    ${CMAKE_CURRENT_LIST_DIR}/detail/RefCounter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/detail/RefTrack.h
    ${CMAKE_CURRENT_LIST_DIR}/detail/shared_ptr.hpp
    ${CMAKE_CURRENT_LIST_DIR}/detail/weak_ptr.hpp
)

set(LOCAL_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
)

get_filename_component(INTERFACE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

#target_compile_options(data_api
#    PRIVATE /W4)
    
target_sources(inspect_shared_ptr
    PRIVATE
        ${LOCAL_SOURCE}
    PRIVATE
        ${LOCAL_HEADER}
    PUBLIC
        ${PUBLIC_HEADER})
   
target_include_directories(inspect_shared_ptr
    INTERFACE
        ${INTERFACE_INCLUDE_DIRS}
)

ide_file_structure(inspect_shared_ptr " ")
