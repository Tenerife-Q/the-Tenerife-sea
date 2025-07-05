@echo off
:: 设置UTF-8编码避免乱码
chcp 65001 >nul

echo ========================================
echo        链地址法哈希表自动测试
echo ========================================
echo.

:: 检查可执行文件是否存在
if not exist "interactive_chain_division.exe" (
    echo ❌ 可执行文件不存在，正在编译...
    gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wall -g -o interactive_chain_division.exe interactive_chain_division.c
    if %ERRORLEVEL% NEQ 0 (
        echo ❌ 编译失败！
        pause
        exit /b 1
    )
    echo ✅ 编译成功！
) else (
    echo ✅ 可执行文件已存在
)

echo.
echo 🧪 开始自动化测试...
echo.

:: 创建测试输入文件
echo 13> test_input.txt
echo 1>> test_input.txt
echo 26>> test_input.txt
echo 1>> test_input.txt
echo 39>> test_input.txt
echo 4>> test_input.txt
echo 6>> test_input.txt
echo 8>> test_input.txt

echo 📝 测试输入序列：
echo    1. 设置哈希表大小为 13
echo    2. 插入键值 26
echo    3. 插入键值 39
echo    4. 显示哈希表状态
echo    5. 执行随机冲突测试
echo    6. 退出程序
echo.

echo 🚀 运行测试...
interactive_chain_division.exe < test_input.txt

echo.
echo ✅ 测试完成！

:: 清理临时文件
del test_input.txt

:: 检查是否生成了日志文件
if exist "hash_test_log.txt" (
    echo.
    echo 📊 发现测试日志文件，最新记录：
    echo ----------------------------------------
    tail -10 hash_test_log.txt 2>nul || (
        echo 显示日志文件内容：
        type hash_test_log.txt
    )
    echo ----------------------------------------
)

echo.
echo 🎉 所有测试流程完成！
pause
