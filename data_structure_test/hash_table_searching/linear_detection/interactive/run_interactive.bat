@echo off
:: 设置UTF-8编码
chcp 65001 >nul

:: 设置工作目录
cd /d "%~dp0"

:: 检查GCC是否安装
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo 错误：未找到GCC编译器！
    echo 请确保已安装MinGW并将其添加到系统PATH中。
    echo 通常路径为：C:\MinGW\bin 或 D:\mingw64\bin
    pause
    exit /b 1
)

echo 正在编译交互式哈希表程序...
echo 当前目录: %CD%
echo GCC版本信息:
gcc --version

:: 检查源文件是否存在
if not exist "%~dp0interactive_hash_table.c" (
    echo 错误：源文件 interactive_hash_table.c 不存在！
    echo 查找路径: %~dp0interactive_hash_table.c
    echo.
    echo 当前目录中的文件列表:
    dir "%~dp0*.c" /b
    pause
    exit /b 1
)

echo 源文件存在，开始编译...
echo 完整编译命令: gcc -Wall -g -o "%~dp0interactive_hash_table.exe" "%~dp0interactive_hash_table.c"

:: 使用完整路径和详细编译选项，显示详细错误信息
gcc -Wall -g -o "%~dp0interactive_hash_table.exe" "%~dp0interactive_hash_table.c" 2>&1

if %ERRORLEVEL% EQU 0 (
    echo 编译成功！正在启动程序...
    echo.
    "%~dp0interactive_hash_table.exe"
) else (
    echo 编译失败！可能的原因：
    echo 1. 源文件不存在
    echo 2. 代码中有语法错误
    echo 3. 编译器无法访问指定路径
    echo.
    echo 当前目录: %CD%
    echo 源文件路径: %~dp0interactive_hash_table.c
    echo 目标文件: %~dp0interactive_hash_table.exe
    echo.
    echo 请检查以上信息并修复问题。
    pause
    exit /b 1
)
