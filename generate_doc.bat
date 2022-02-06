@echo off

call .\scripts\cmake_cfg.bat


:run_cmake_cmd
if NOT EXIST %OPT_PROJECT_WS_DIR% (
    echo ::: 
    echo : could not find workspace
    echo : %OPT_PROJECT_WS_DIR%
    echo : run run_cmake.bat first
    echo ::: 
    goto :EOF
)    

echo ::: 
echo : running CMake in:
echo : %OPT_PROJECT_WS_DIR%
echo ::: 
%CMAKE_CMD% --build %OPT_PROJECT_WS_DIR% ^
    --target doc

:EOF
pause