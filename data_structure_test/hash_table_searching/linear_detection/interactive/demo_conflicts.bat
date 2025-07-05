@echo off
chcp 65001 >nul 2>&1
title Hash Table Conflict Test Demo
color 0A

echo ========================================
echo     Hash Table Conflict Pattern Demo
echo ========================================
echo.
echo This demo will show:
echo 1. Concentrated conflicts - all keys map to same position
echo 2. Distributed conflicts - keys spread to different positions  
echo 3. Mixed conflicts - simulate real usage scenarios
echo 4. Pseudo-random test - random data performance test
echo.
echo Key observation points:
echo - Impact of different conflict patterns on ASL
echo - Linear probing working process
echo - Formation and distribution of conflict chains
echo.
pause

echo.
echo Compiling program...
gcc -o interactive_hash_table.exe interactive_hash_table.c

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Starting interactive hash table program...
    echo.
    echo Suggested test flow:
    echo 1. Set hash table size to 15
    echo 2. Choose option 6 for random conflict tests
    echo 3. Choose option 7 for pseudo-random tests
    echo 4. Manually test other functions
    echo.
    pause
    interactive_hash_table.exe
) else (
    echo Compilation failed! Please check the code.
    pause
)
