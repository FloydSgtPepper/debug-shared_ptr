#include(cmake/ToolChain.cmake)
cmake_minimum_required(VERSION 3.20)

set (OPT_CMAKE_INCL_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_ext")

# TO_CMAKE_PATH
file(TO_CMAKE_PATH ${OPT_CMAKE_INCL_PATH} THE_CMAKE_INCL_PATH )
list(APPEND CMAKE_MODULE_PATH ${THE_CMAKE_INCL_PATH})
include(cmake/ProjectUtils.cmake)

option(PROJECT_DEVELOP_BUILD "this build is for development" ON)
option(PROJECT_BUILD_TESTS "add the tests to the project" ON)
option(PROJECT_BUILD_DOC "add target to generate doxygen documentation" ON)

project (inspect_shared_ptr)

add_subdirectory (src)

if (PROJECT_DEVELOP_BUILD)
    add_compile_options(-W4)
    add_compile_options (/X)
    include_directories(AFTER SYSTEM "$ENV{VCToolsInstallDir}/include")
    include_directories(AFTER SYSTEM "$ENV{NETFXSDKDir}/include/um")
    include_directories(AFTER SYSTEM "$ENV{WindowsSdkDir}/include/$ENV{WindowsSDKVersion}/um")
    include_directories(AFTER SYSTEM "$ENV{WindowsSdkDir}/include/$ENV{WindowsSDKVersion}/shared")
    include_directories(AFTER SYSTEM "$ENV{WindowsSdkDir}/include/$ENV{WindowsSDKVersion}/ucrt") # only debug builds?
    add_library(std_includes INTERFACE "")
    target_include_directories(std_includes
        INTERFACE
            "$ENV{VCToolsInstallDir}/include"
    )
endif()
    

set_directory_properties(
    PROPERTIES
        VS_STARTUP_PROJECT inspect_shared_ptr
)

if (${PROJECT_BUILD_DOC})
    include(cmake/ProjectDoxygenCfg.cmake)
endif()

if (PROJECT_BUILD_TESTS)
    add_subdirectory(test)
endif()
