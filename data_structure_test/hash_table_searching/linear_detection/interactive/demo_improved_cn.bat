@echo off
:: 设置控制台编码为UTF-8
chcp 65001 >nul
title 改进的哈希表测试数据演示

echo ==========================================
echo       改进的线性探测哈希表测试
echo ==========================================
echo.
echo 本次改进包括:
echo 1. 更随机的冲突分布模式
echo 2. 环形探测演示 (位置9→位置0)
echo 3. 多个分离的冲突链
echo 4. 更详细的性能统计信息
echo.
echo 新测试数据: 17, 30, 22, 48, 35, 61, 44, 19, 57
echo 冲突分析:
echo   - 17,30 冲突在位置4
echo   - 22,48,35,61 冲突在位置9 (形成环形探测)
echo   - 44,19,57 形成第三个冲突链
echo.

pause

echo.
echo 正在编译程序...
gcc -o hash_linear_detection.exe hash_linear_detection.c

if %ERRORLEVEL% EQU 0 (
    echo 编译成功！运行测试程序...
    echo.
    echo 观察要点:
    echo 1. 冲突链的分布是否更均匀
    echo 2. 环形探测从位置9到位置0
    echo 3. ASL值与理论预期的对比
    echo 4. 删除操作对性能的影响
    echo.
    pause
    hash_linear_detection.exe
) else (
    echo 编译失败！请检查代码。
    pause
)

echo.
echo 程序执行完成！
echo 查看 test_data_analysis.md 了解详细的改进分析
pause
