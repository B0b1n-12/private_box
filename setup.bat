
@echo off
g++ main.cpp -o lucky_json_program.exe -I .
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)
echo Compilation successful.
lucky_json_program.exe
pause
