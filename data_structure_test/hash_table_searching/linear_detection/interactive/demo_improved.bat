@echo off
chcp 65001 >nul 2>&1
title Improved Hash Table Test Demo
color 0B

echo ========================================
echo     Improved Linear Probing Hash Table Test
echo ========================================
echo.
echo Improvements include:
echo 1. More random conflict distribution pattern
echo 2. Circular probing demo (position 9 to position 0)
echo 3. Multiple separate conflict chains
echo 4. More detailed performance statistics
echo.
echo New test data: 17, 30, 22, 48, 35, 61, 44, 19, 57
echo Conflict analysis:
echo   - 17,30 conflict at position 4
echo   - 22,48,35,61 conflict at position 9 (forming circular probe)
echo   - 44,19,57 form the third conflict chain
echo.

pause

echo.
echo Compiling program...
gcc -o hash_linear_detection.exe hash_linear_detection.c

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Running test program...
    echo.
    echo Key observation points:
    echo 1. More uniform distribution of conflict chains
    echo 2. Circular probing from position 9 to position 0
    echo 3. ASL comparison with theoretical expectation
    echo 4. Impact of deletion operations on performance
    echo.
    pause
    hash_linear_detection.exe
) else (
    echo Compilation failed! Please check the code.
    pause
)

echo.
echo Program execution completed!
echo Check test_data_analysis.md for detailed improvement analysis
pause
