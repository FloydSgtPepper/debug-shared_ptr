cmake_minimum_required(VERSION 3.20)

project (inspect_shared_ptr_test)

to_windows_path("${CMAKE_SOURCE_DIR}/test/test_input")
set(PRJ_TEST_INPUT_DIR "${TO_WINDOWS_PATH_RESULT}")

#add_executable(unittest "")

#set_target_properties(unittest
#    PROPERTIES
#        CXX_STANDARD 17
##        CXX_STANDARD_REQUIRED ON
#)


#add_subdirectory(ut)
add_subdirectory(inspect_shared_ptr)

#target_link_libraries(unittest
#    PRIVATE
#        Catch2
#)
