@echo off
:: Set UTF-8 encoding to avoid garbled characters
chcp 65001 >nul

:: Check if GCC is available in the environment
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ========================================
    echo              ERROR
    echo ========================================
    echo GCC compiler not found!
    echo Please ensure MinGW-w64 or TDM-GCC is properly installed
    echo and its bin directory is added to system PATH.
    echo.
    echo Common installation paths:
    echo 1. D:\mingw64\bin
    echo 2. C:\TDM-GCC-64\bin
    echo.
    echo You can:
    echo 1. Download MinGW-w64: https://sourceforge.net/projects/mingw-w64/
    echo 2. Or install TDM-GCC: https://jmeubank.github.io/tdm-gcc/
    echo.
    pause
    exit /b 1
)

echo ========================================
echo     Chain Address Hash Table Demo
echo ========================================
echo.
echo This program demonstrates:
echo 1. Chain address method for hash collisions
echo 2. Visualization of collision resolution with linked lists
echo 3. ASL calculation for different test data
echo 4. Comparison of various collision patterns
echo.
echo Features:
echo * Visualized linked list formation
echo * Automatic ASL calculation
echo * Same interface as linear/quadratic probing
echo * Multiple collision pattern tests
echo.
pause

echo.
echo Compiling program...

:: Try compilation with warnings and debug info
gcc -Wall -g -o interactive_chain_division.exe interactive_chain_division.c 2>compile_error.txt
set COMPILE_STATUS=%ERRORLEVEL%

if %COMPILE_STATUS% EQU 0 (
    echo Compilation successful! Starting program...
    echo.
    echo Suggested test sequence:
    echo 1. Set hash table size to 13
    echo 2. Select option 6 for random conflict tests
    echo 3. Select option 7 for pseudo-random tests
    echo 4. Manually test other functions
    echo.
    echo Observation points:
    echo - Linked list formation process
    echo - ASL differences compared to linear/quadratic probing
    echo - Collision handling efficiency of chain addressing
    echo.
    pause
    interactive_chain_division.exe
) else (
    echo ========================================
    echo         COMPILATION FAILED
    echo ========================================
    echo Compilation errors occurred, details:
    type compile_error.txt
    echo.
    echo Possible solutions:
    echo 1. Check source code for syntax errors
    echo 2. Ensure all necessary header files exist
    echo 3. Check file encoding (recommend UTF-8 without BOM)
    echo.
    echo You can try manual compilation with:
    echo gcc -Wall -g -o interactive_chain_division.exe interactive_chain_division.c
    echo.
    echo If problems persist, check:
    echo - Source file completeness
    echo - Required header files inclusion
    echo - Syntax errors in code
    echo ========================================
    pause
    del compile_error.txt
)
