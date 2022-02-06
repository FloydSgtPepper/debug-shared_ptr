cmake_minimum_required(VERSION 3.6)

set(LOCAL_UT ut_inspect_shared_ptr)

add_executable(${LOCAL_UT} "")

target_link_libraries(${LOCAL_UT}
    PRIVATE
        Catch2
        inspect_shared_ptr
)

add_test(NAME ${LOCAL_UT}
    COMMAND ${LOCAL_UT} "--reporter xml")

set_target_properties(${LOCAL_UT}
    PROPERTIES
        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
)

add_compile_definitions(
    PRJ_TEST_INPUT_DIR="${PRJ_TEST_INPUT_DIR}"
)

set(LOCAL_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/ut_inspect_shared_ptr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ut_enable_shared_from_this.cpp
    #${CMAKE_CURRENT_LIST_DIR}/ut_inspect_weak_ptr.cpp
)

set(LOCAL_HEADER
)

set(LOCAL_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(${LOCAL_UT}
    PRIVATE
        ${LOCAL_SOURCE}
    PRIVATE
        ${LOCAL_HEADER}
)

target_include_directories(${LOCAL_UT}
    PRIVATE
        ${LOCAL_INCLUDE_DIRS}
)

ide_file_structure_source(${LOCAL_UT} "ut")
