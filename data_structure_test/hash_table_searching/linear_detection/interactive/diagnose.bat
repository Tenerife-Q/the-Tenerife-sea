@echo off
chcp 65001 >nul

echo ========================================
echo           编译诊断脚本
echo ========================================
echo.

:: 检查当前目录
echo 1. 当前工作目录:
echo %CD%
echo.

:: 列出C文件
echo 2. 当前目录中的C文件:
if exist *.c (
    dir *.c /b
) else (
    echo 未找到C文件！
)
echo.

:: 检查特定文件
echo 3. 检查目标源文件:
if exist interactive_hash_table.c (
    echo ✓ interactive_hash_table.c 存在
    echo 文件大小: 
    dir interactive_hash_table.c | find ".c"
) else (
    echo ✗ interactive_hash_table.c 不存在！
)
echo.

:: 检查GCC
echo 4. 检查GCC编译器:
where gcc 2>nul
if %ERRORLEVEL% EQU 0 (
    echo ✓ 找到GCC编译器
    echo GCC路径:
    where gcc
    echo.
    echo GCC版本:
    gcc --version 2>nul | findstr gcc
) else (
    echo ✗ 未找到GCC编译器！
    echo.
    echo 常见GCC安装路径检查:
    if exist "C:\MinGW\bin\gcc.exe" echo ✓ 找到: C:\MinGW\bin\gcc.exe
    if exist "D:\mingw64\bin\gcc.exe" echo ✓ 找到: D:\mingw64\bin\gcc.exe
    if exist "C:\msys64\mingw64\bin\gcc.exe" echo ✓ 找到: C:\msys64\mingw64\bin\gcc.exe
    if exist "C:\Program Files\MinGW\bin\gcc.exe" echo ✓ 找到: C:\Program Files\MinGW\bin\gcc.exe
)
echo.

:: 如果文件存在且GCC可用，尝试编译
if exist interactive_hash_table.c (
    if %ERRORLEVEL% EQU 0 (
        echo 5. 尝试编译:
        echo 执行命令: gcc interactive_hash_table.c -o test.exe
        gcc interactive_hash_table.c -o test.exe
        if exist test.exe (
            echo ✓ 编译成功！
            del test.exe
        ) else (
            echo ✗ 编译失败！
        )
    )
)

echo.
echo ========================================
echo 如果上述检查都通过，请手动执行:
echo gcc interactive_hash_table.c -o interactive_hash_table.exe
echo ========================================
pause
