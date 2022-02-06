cmake_minimum_required(VERSION 3.6)

macro(ide_file_structure myTarget prefix)
    get_target_property(targetSourceFiles ${myTarget} SOURCES)
    if (${prefix} STREQUAL " ")
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
            FILES ${targetSourceFiles}
        )
     else ()
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
            PREFIX ${prefix}
            FILES ${targetSourceFiles}
        )
     endif ()
endmacro()

macro(ide_file_structure_header myTarget)
    get_target_property(targetSourceFiles ${myTarget} SOURCES)
  
    foreach(f ${targetSourceFiles}) 

    #convert source file to absolute
#    get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
    # Get the directory of the absolute source file
#    get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
    # Remove common directory prefix to make the group
#    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    # Make sure we are using windows slashes
#    string(REPLACE "/" "\\" GROUP "${GROUP}")
    # Group into "Source Files" and "Header Files"
    set(GROUP "__not_grouped__")
    if ("${f}" MATCHES ".*\\.cpp")
        set(GROUP "src")
    elseif("${f}" MATCHES ".*\\.h")
        set(GROUP "")
    endif()
    source_group("${GROUP}" FILES "${f}")
    endforeach()
endmacro()

macro(ide_file_structure_source myTarget)
    get_target_property(targetSourceFiles ${myTarget} SOURCES)
  
    foreach(f ${targetSourceFiles}) 
    set(GROUP "__not_grouped__")
    if ("${f}" MATCHES ".*\\.cpp")
        set(GROUP "")
    elseif("${f}" MATCHES ".*\\.h")
        set(GROUP "header")
    endif()
    source_group("${GROUP}" FILES "${f}")
    endforeach()
endmacro()

macro(target_compile_option_std_latest target)    
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            target_compile_options(${target}
                PRIVATE "/std:c++latest")
        endif()
    endif() 
endmacro()

macro(target_compile_option_std_17 target)    
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_std_17_flag_supported)
        if (_cpp_std_17_flag_supported)
            target_compile_options(${target}
                PRIVATE "/std:c++17")
        endif()
    endif() 
endmacro()

macro(target_compile_option_std_14 target)    
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++14" _cpp_std_14_flag_supported)
        if (_cpp_std_14_flag_supported)
            target_compile_options(${target}
                PRIVATE "/std:c++14")
        endif()
    endif() 
endmacro()

macro(to_windows_path cmake_path)
    file(TO_NATIVE_PATH "/" NATIVE_SEP)
    get_filename_component(absolute_path ${cmake_path} ABSOLUTE)
    file(TO_NATIVE_PATH ${absolute_path} native_path)
    
    string(REPLACE "${NATIVE_SEP}" "${NATIVE_SEP}${NATIVE_SEP}" TO_WINDOWS_PATH_RESULT "${native_path}")
endmacro()
