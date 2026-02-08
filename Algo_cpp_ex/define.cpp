/**
 * ============================================================
 * C++ 宏 (Macro) 使用详解与避坑指南
 * ============================================================
 * 宏是在编译前进行简单的"文本替换"，它不想函数那样有类型检查。
 * 使用宏要非常小心！
 */

#include <iostream>
using namespace std;

// 1. 定义常量 (基本上被 const/constexpr 取代，但仍常见)
#define PI 3.14159
#define BUFFER_SIZE 1024

// 2. 带参数的宏 (函数宏)
// ⚠️ 关键规则：每一层参数都必须加括号 ()，否则会有优先级灾难
#define SQUARE(x) ((x) * (x))       // 正确：安全
#define BAD_SQUARE(x) x * x         // ❌ 错误：危险！

// 3. 简单的逻辑宏
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 4. 多行宏 (使用反斜杠 \ 连接)
#define LOG_USER(id, name) \
    cout << "--- User Info ---" << endl; \
    cout << "ID: " << id << endl; \
    cout << "Name: " << name << endl; \
    cout << "-----------------" << endl;

// 5. 条件编译 (开关控制)
#define DEBUG_MODE  // 注释掉这行，下面的调试代码就会消失

int main() {
    // --- 演示常量宏 ---
    cout << "1. Circle area (r=10): " << PI * 10 * 10 << endl;

    // --- 演示函数宏与陷阱 ---
    int a = 5;
    
    // 正常情况
    cout << "2. Square of 5: " << SQUARE(a) << endl;

    // ⚡ 陷阱演示：传入表达式时
    // SQUARE(a + 1)     展开为 ((a + 1) * (a + 1)) = 6 * 6 = 36 ✅
    // BAD_SQUARE(a + 1) 展开为 a + 1 * a + 1       = 5 + 5 + 1 = 11 ❌ (算错了！)
    cout << "   SQUARE(5+1): " << SQUARE(a + 1) << " (Correct)" << endl;
    cout << "   BAD_SQUARE(5+1): " << BAD_SQUARE(a + 1) << " (Wrong!)" << endl;

    // --- 演示多行宏 ---
    cout << "\n3. Macro function output:" << endl;
    LOG_USER(101, "Admin");

    // --- 演示条件编译 ---
    cout << "\n4. Debug info:" << endl;
#ifdef DEBUG_MODE
    cout << "[DEBUG] System is running in debug mode..." << endl;
    // 可以在这里打印详细日志，发布时注释掉 #define DEBUG_MODE 即可
#else
    cout << "System is running normally." << endl;
#endif

    // --- 现代 C++ 建议 ---
    // 尽量用 const int 代替 #define INT
    // 尽量用 inline 函数 代替 #define MACRO()
    
    return 0;
}
