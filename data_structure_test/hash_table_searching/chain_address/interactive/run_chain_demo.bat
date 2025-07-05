@echo off
:: 设置UTF-8编码避免乱码
chcp 65001 >nul

:: 检查 GCC 是否在环境变量中
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ========================================
    echo              错误提示
    echo ========================================
    echo GCC编译器未找到！
    echo 请确保已正确安装 MinGW-w64 或 TDM-GCC，
    echo 并将其 bin 目录添加到系统环境变量 PATH 中。
    echo.
    echo 常见安装位置：
    echo 1. D:\mingw64\bin
    echo 2. C:\TDM-GCC-64\bin
    echo.
    echo 您可以：
    echo 1. 下载安装 MinGW-w64：https://sourceforge.net/projects/mingw-w64/
    echo 2. 或安装 TDM-GCC：https://jmeubank.github.io/tdm-gcc/
    echo.
    pause
    exit /b 1
)

echo ========================================
echo     链地址法哈希表交互式演示程序
echo ========================================
echo.
echo 本程序将演示：
echo 1. 链地址法解决哈希冲突
echo 2. 冲突可视化和链表形成过程 
echo 3. 各种测试数据的ASL计算
echo 4. 多种冲突模式的比较
echo.
echo 特点：
echo * 可视化链表冲突
echo * 自动计算平均查找长度
echo * 与线性探测、二次探测相同的操作界面
echo * 包含多种冲突模式测试
echo.
pause

echo.
echo 正在编译程序...

:: 尝试编译（添加所有警告和调试信息）
gcc -Wall -g -o interactive_chain_division.exe interactive_chain_division.c 2>compile_error.txt
set COMPILE_STATUS=%ERRORLEVEL%

if %COMPILE_STATUS% EQU 0 (
    echo 编译成功！正在启动程序...
    echo.
    echo 建议测试流程：
    echo 1. 设置哈希表大小为 13
    echo 2. 选择选项 6 进行随机冲突测试
    echo 3. 选择选项 7 进行伪随机数测试
    echo 4. 手动测试其他功能
    echo.
    echo 特别观察：
    echo - 链表的形成过程
    echo - ASL与线性/二次探测的区别
    echo - 链地址法对冲突的处理效果
    echo.
    pause
    interactive_chain_division.exe
) else (
    echo ========================================
    echo              编译失败
    echo ========================================
    echo 编译过程中出现错误，详细信息：
    type compile_error.txt
    echo.
    echo 可能的解决方案：
    echo 1. 检查源代码是否有语法错误
    echo 2. 确保所有必要的头文件都存在
    echo 3. 检查文件编码是否正确（建议使用UTF-8无BOM）
    echo.
    echo 您可以尝试使用以下命令手动编译：
    echo gcc -Wall -g -o interactive_chain_division.exe interactive_chain_division.c
    echo.
    echo 如果问题持续，请检查：
    echo - 源文件是否完整
    echo - 是否包含了所有必要的头文件
    echo - 代码中是否有语法错误
    echo ========================================
    pause
    del compile_error.txt
)
