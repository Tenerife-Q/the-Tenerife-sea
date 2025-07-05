@echo off
:: 设置控制台编码为UTF-8
chcp 65001 >nul
title 哈希表冲突测试演示

echo ==========================================
echo       哈希表冲突模式测试演示
echo ==========================================
echo.
echo 本演示将展示以下内容：
echo 1. 集中冲突测试 - 所有键值映射到同一位置
echo 2. 分散冲突测试 - 键值分散到不同位置  
echo 3. 混合冲突测试 - 模拟真实使用场景
echo 4. 伪随机数测试 - 随机数据性能测试
echo.
echo 观察要点：
echo - 不同冲突模式对ASL的影响
echo - 线性探测的工作过程
echo - 冲突链的形成和分布
echo.
pause

echo.
echo 正在编译程序...
gcc -o interactive_hash_table.exe interactive_hash_table.c

if %ERRORLEVEL% EQU 0 (
    echo 编译成功！启动交互式哈希表程序...
    echo.
    echo 建议测试流程：
    echo 1. 设置哈希表大小为 15
    echo 2. 选择选项 6 进行随机冲突测试
    echo 3. 选择选项 7 进行伪随机数测试
    echo 4. 手动测试其他功能
    echo.
    pause
    interactive_hash_table.exe
) else (
    echo 编译失败！请检查代码。
    pause
)
