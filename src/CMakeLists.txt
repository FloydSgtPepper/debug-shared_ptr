#include(ToolChain.cmake)
cmake_minimum_required(VERSION 3.20)

find_package(Boost REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(utils)
add_subdirectory(inspect_shared_ptr)


target_link_libraries(inspect_shared_ptr
    INTERFACE
#        Boost::date_time
        Boost::headers
        #Boost::stacktrace
        UtilsIF
)

set_target_properties(inspect_shared_ptr
    PROPERTIES
        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
)

#target_compile_definitions(inspect_shared_ptr
#    PUBLIC
#        _WIN32_WINNT=0x0601
#)
