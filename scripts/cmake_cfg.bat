@echo off

set OPT_PROJECT_NAME=inspect_shared_ptr
set OPT_PROJECT_ROOT_DIR=.
set OPT_PROJECT_WS_DIR=build\build\x64-Debug
set OPT_PROJECT_TEST_SRC_DIR=test\src

set OPT_ADD_CMAKE_INCL_PATH=cmake_ext
set CMAKE_PATH=c:\Program Files\CMake

set CMAKE_CMD="%CMAKE_PATH%\bin\cmake.exe"
set CMAKE_TEST_CMD="%CMAKE_PATH%\bin\ctest.exe"


set MSVC_INSTALL=C:/Program Files/Microsoft Visual Studio/2022/Preview
set CMAKE_C_COMPILER="%MSVC_INSTALL%/VC/Tools/MSVC/14.30.30704/bin/Hostx64/x64/cl.exe"
set CMAKE_CXX_COMPILER="%MSVC_INSTALL%/VC/Tools/MSVC/14.30.30704/bin/Hostx64/x64/cl.exe"

set NINJA_INSTALL=C:/LegacyApp/ninja
set NINJA_EXECUTABLE=%NINJA_INSTALL%/ninja.exe
set CMAKE_MAKE_PROGRAM=%NINJA_EXECUTABLE%


set OPT_PROJECT_TEST_WS_DIR="%OPT_PROJECT_WS_DIR%\%OPT_PROJECT_TEST_SRC_DIR%"
call :get_absolute %OPT_ADD_CMAKE_INCL_PATH% OPT_CMAKE_INCL_PATH
call :get_absolute %OPT_PROJECT_ROOT_DIR% OPT_PROJECT_ROOT_DIR
call :get_absolute %OPT_PROJECT_WS_DIR% OPT_PROJECT_WS_DIR
call :get_absolute %OPT_PROJECT_TEST_WS_DIR% OPT_PROJECT_TEST_WS_DIR
call :get_absolute %OPT_PROJECT_TEST_SRC_DIR% OPT_PROJECT_TEST_SRC_DIR
call :test_cmake_cmd

:test_cmake_cmd
%CMAKE_CMD% --help > NUL 2>&1
if ERRORLEVEL 9009 (
    echo !! ERROR !!
    echo CMAKE not found - looked here %CMAKE_CMD%
    echo !! ERROR !!
    goto EOF
)

goto :EOF

:get_absolute
set %~2=%~f1
exit /b 0

:EOF
REM pause
