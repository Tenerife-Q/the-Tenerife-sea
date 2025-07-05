@echo off
chcp 65001 >nul

echo 简化版编译脚本
echo 当前目录: %CD%

:: 列出所有C文件
echo.
echo 当前目录中的C文件:
dir *.c

echo.
echo 尝试编译...

:: 最简单的编译命令
gcc interactive_hash_table.c -o interactive_hash_table.exe

if exist interactive_hash_table.exe (
    echo 编译成功！
    echo 启动程序...
    interactive_hash_table.exe
) else (
    echo 编译失败！
    echo.
    echo 请手动尝试以下命令:
    echo gcc interactive_hash_table.c -o interactive_hash_table.exe
    echo.
    echo 或者使用完整路径:
    echo D:\mingw64\bin\gcc.exe interactive_hash_table.c -o interactive_hash_table.exe
)

pause
