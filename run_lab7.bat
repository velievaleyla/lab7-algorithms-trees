@echo off
echo Compiling Lab 7 (Trees)...
"C:\Program Files\CodeBlocks\MinGW\bin\g++.exe" -static -std=c++17 -Wall main.cpp -o lab7.exe
if %ERRORLEVEL% equ 0 (
    echo Compilation successful! Running lab7.exe...
    lab7.exe
) else (
    echo Compilation failed!
)
pause
