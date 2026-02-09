/**
 * ============================================================
 * 场景 4：函数调用追踪 - 深入函数内部
 * ============================================================
 * 学习目标：学会用 F11 进入函数内部，追踪函数执行逻辑
 * 
 * 问题：主函数调用了 calculate()，但结果不对
 * 
 * 你应该做的：
 * 1. 按 Ctrl+F5 运行，看输出，发现结果不对
 * 2. 在第 30 行（result = calculate(a, b);）按 F9 设断点
 * 3. 按 F5 启动调试 → 停在该断点
 * 4. 按 F11 进入函数内部（光标进入 calculate 函数）
 * 5. 在 calculate 中再按 F9 在第 19 行（int sum = a + b;）设断点
 * 6. 按 F10 单步执行，看 sum 的值
 * 7. 发现 sum 计算有问题
 * 8. 退出调试（Shift+F5），修复 bug
 * ============================================================
 */

#include <iostream>
using namespace std;

// 计算两数之和与乘积
int calculate(int a, int b){
    // ❌ 问题在这里
    int sum = a * b;      // 应该是相加，不是相乘！
    int product = a + b;  // 应该是相乘，不是相加！
    
    cout << "In calculate: a=" << a << ", b=" << b << endl;
    cout << "sum=" << sum << ", product=" << product << endl;
    
    return sum;  // 返回 sum
}

int main(){
    int a = 5, b = 3;
    
    // 期望：sum = 5 + 3 = 8, product = 5 * 3 = 15
    // 实际：sum = 5 * 3 = 15, product = 5 + 3 = 8 (反了！)
    int result = calculate(a, b);
    
    cout << "Final result: " << result << endl;
    
    return 0;
}

/**
 * 调试步骤演示：
 * 
 * 第 31 行按 F9 设断点
 * 按 F5 启动调试
 * → 在第 31 行断点处，按 F11 进入 calculate 函数
 * → 光标跳到第 16 行（calculate 的开头）
 * → 再按 F9 在第 18 或 19 行设断点
 * → 按 F10 执行，看 sum 和 product 的值
 * → 发现 sum = 15（错了，应该是 8）
 * → 发现 product = 8（错了，应该是 15）
 * → 修复：第 18、19 行的计算符号反了
 * 
 * 修复方案：
 * 第 18 行：int sum = a + b;      （改 * 为 +）
 * 第 19 行：int product = a * b;  （改 + 为 *）
 */
