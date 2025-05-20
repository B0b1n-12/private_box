@echo off
REM Kompilace programu lucky_json_program.exe
g++ main.cpp -o lucky_json_program.exe -I .

IF %ERRORLEVEL% NEQ 0 (
    echo Kompilace selhala.
    pause
    exit /b %ERRORLEVEL%
)

echo Kompilace probehla uspesne.
echo Spoustim program...
lucky_json_program.exe

pause

