@echo off
:: 设置UTF-8编码避免乱码
chcp 65001 >nul

echo 正在编译 C 语言源文件...
gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 -o interactive_chain_division.exe interactive_chain_division.c

if %ERRORLEVEL% NEQ 0 (
    echo ❌ 编译失败！
    pause
    exit /b
)

echo ✅ 编译成功！
echo.

echo 启动程序进行基本测试...
(echo 13 & echo 8) | interactive_chain_division.exe
echo.
echo 测试完成！
pause
