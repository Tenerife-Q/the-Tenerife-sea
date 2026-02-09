/**
 * ============================================================
 * 场景 6：条件判断错误 - 逻辑分支追踪
 * ============================================================
 * 学习目标：学会用条件断点和单步执行追踪复杂的逻辑分支
 * 
 * 问题：程序对不同学生的成绩进行评估，但结果不对
 * 
 * 你应该做的：
 * 1. 按 Ctrl+F5 运行，看输出，找出哪个学生的评估不对
 * 2. 在第 35 行（if (score >= 60)）按 F9 设断点
 * 3. 按 F5 启动调试 → 停在第一个断点
 * 4. 看右侧 DEBUG 面板，找到 score 变量，注意其值
 * 5. 按 F10 单步执行，观察进入哪个 if 分支
 * 6. 按 Shift+F5 停止，重新在第 37 行（else if...）设条件断点
 * 7. 条件断点：在 F9 设置时，右键选择"编辑断点"，输入条件：score == 50
 * 8. 按 F5 再次运行，只在 score==50 时停止
 * 9. 找到逻辑错误
 * ============================================================
 */

#include <iostream>
using namespace std;

void evaluateScore(const char* name, int score){
    cout << name << " got " << score << " points: ";
    
    // ❌ 问题在这里的逻辑顺序
    if (score >= 60){
        cout << "Pass!" << endl;
    }
    else if (score >= 80){
        // ❌ 这行永远不会执行！为什么？
        cout << "Excellent!" << endl;
    }
    else if (score >= 90){
        // ❌ 这行也永远不会执行！为什么？
        cout << "Outstanding!" << endl;
    }
    else {
        cout << "Fail!" << endl;
    }
}

int main(){
    // 📌 在第 35 行（if (score >= 60)）设断点
    evaluateScore("Alice", 95);  // 应该输出 "Outstanding!" 但实际输出 "Pass!"
    evaluateScore("Bob", 85);    // 应该输出 "Excellent!" 但实际输出 "Pass!"
    evaluateScore("Charlie", 50);// 应该输出 "Fail!"
    
    return 0;
}

/**
 * 逻辑错误分析：
 * 
 * if-else if-else 是从上到下判断的：
 * 
 * Alice (95 分)：
 * - 检查 95 >= 60？是！进入第一个 if，输出 "Pass!"
 * - 后面的 else if 被跳过（已经进入 if 了）
 * - 结果错误！
 * 
 * 问题原因：
 * 第 35 行应该是更严格的条件，这样分数更高的才能进入
 * 现在的逻辑是从低到高，后面的条件永无执行机会
 * 
 * 修复方案：
 * 调整条件顺序，从高分到低分：
 * 
 * if (score >= 90){
 *     cout << "Outstanding!" << endl;
 * }
 * else if (score >= 80){
 *     cout << "Excellent!" << endl;
 * }
 * else if (score >= 60){
 *     cout << "Pass!" << endl;
 * }
 * else {
 *     cout << "Fail!" << endl;
 * }
 * 
 * 调试技巧：
 * - 条件断点：F9 右键 → "编辑断点" → 输入条件表达式
 * - 例如：score == 95 （只在 score 为 95 时停止）
 * - 这样可以快速定位特定数据的错误
 */
