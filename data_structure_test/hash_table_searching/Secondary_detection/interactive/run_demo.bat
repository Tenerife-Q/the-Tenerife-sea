@echo off
:: 设置UTF-8编码避免乱码
chcp 65001 >nul
echo === Running Interactive Hash Table Demo ===
echo.
echo The program will demonstrate:
echo 1. Menu-driven interface
echo 2. Batch insertion of test data
echo 3. Interactive search and insert operations
echo 4. Collision resolution visualization
echo 5. Table status display
echo.

:: 检查程序文件是否存在
if exist interactive_quadratic_probe_en.exe (
    echo Found program: interactive_quadratic_probe_en.exe
) else (
    echo ERROR: Program file not found!
    echo Checking for other executable files:
    dir *.exe /b
    echo.
    echo Trying to compile the source file...
    if exist interactive_quadratic_probe_en.c (
        echo Source file found. Attempting to compile...
        gcc -o interactive_quadratic_probe_en.exe interactive_quadratic_probe_en.c
        
        if exist interactive_quadratic_probe_en.exe (
            echo Compilation successful!
        ) else (
            echo Compilation failed!
            echo Please make sure you have GCC installed and in your PATH.
            pause
            exit /b 1
        )
    ) else (
        echo Source file not found either.
        echo Please make sure you're running this batch file from the correct directory.
        pause
        exit /b 1
    )
)

echo.
echo Sample interaction sequence:
echo - Press 6 to batch insert test data: 21, 32, 10, 43, 54, 65, 76, 87, 98, 99, 11, 22, 33, 44
echo - Press 4 to display current hash table status
echo - Press 1 to manually insert a new number
echo - Press 2 to search for a specific number
echo - Press 3 to delete a number
echo - Press 5 to reset the table
echo - Press 7 to exit
echo.

echo Starting the program...
echo.
interactive_quadratic_probe_en.exe

echo.
echo Program execution completed.
pause
