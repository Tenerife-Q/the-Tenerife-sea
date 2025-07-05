@echo off
chcp 65001 >nul

:: 检查并编译
if not exist "interactive_chain_division.exe" (
    echo ⚠️  未找到程序，正在尝试编译...
    gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 -o interactive_chain_division.exe interactive_chain_division.c
    if %ERRORLEVEL% NEQ 0 (
        echo ❌ 编译失败!
        pause
        exit /b
    )
    echo ✅ 编译成功!
)

echo.

echo 正在测试程序运行状态...
echo.

:: 简单测试：检查程序是否能启动并接受输入
echo 测试1: 程序启动测试
(echo 13 & echo 8) | interactive_chain_division.exe >test_output.txt 2>&1

if %ERRORLEVEL% EQU 0 (
    echo ✅ 程序可以正常启动和退出
) else (
    echo ❌ 程序运行时出现错误
)

echo.
echo 程序输出预览:
type test_output.txt | head -20 2>nul || type test_output.txt

echo.
echo 测试完成，详细输出保存在 test_output.txt
pause

:: 清理
del test_output.txt
