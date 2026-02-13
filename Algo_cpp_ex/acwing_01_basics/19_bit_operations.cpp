#include <iostream>

using namespace std;

/*
 * 位运算 - lowbit(x) 统计二进制中1的个数
 * 
 * ============ 数学原理 ============
 * 
 * 公式: lowbit(x) = x & (-x)
 * 作用: 提取最右侧的1
 * 
 * 原理解释:
 *   负数用补码表示: -x = ~x + 1
 *   
 *   例如 x = 12:
 *     x  = 0000 1100  (二进制)
 *     ~x = 1111 0011  (按位取反)
 *     -x = 1111 0100  (加1，这就是补码)
 *     
 *     x & (-x):
 *     0000 1100  (x)
 *   & 1111 0100  (-x)
 *     ─────────
 *     0000 0100  = 4  (提取出最右侧的1)
 * 
 * 为什么能统计1的个数?
 *   每次 x -= lowbit(x) 会去掉最右侧的1
 *   重复到 x = 0，执行的次数就是1的个数
 * 
 * AcWing 801 题：统计每个数二进制中1的个数
 */

// 核心函数：提取最右侧的1
int lowbit(int x) {
    return x & (-x);
}

// 统计1的个数
int count_ones(int x) {
    int count = 0;
    while (x) {
        x -= lowbit(x);
        count++;
    }
    return count;
}

// 简单演示：看看如何一步步消除1
void demo_process(int x) {
    cout << "\n=== 演示: 统计 " << x << " 中有多少个1 ===" << endl;
    
    int original = x;
    int step = 0;
    
    while (x > 0) {
        step++;
        int lb = lowbit(x);
        cout << "第" << step << "步: " << x << " - " << lb << " = " << (x - lb) << endl;
        x -= lb;
    }
    
    cout << "答案: " << original << " 的二进制中有 " << step << " 个1\n" << endl;
}

int main() {
    cout << "=== 位运算 - 统计二进制中1的个数 ===" << endl;
    cout << "原理: lowbit(x) = x & (-x) 每次消掉最右侧的1\n" << endl;
    
    while (true) {
        cout << "选择模式:" << endl;
        cout << "  1. 看演示过程 (输入一个数)" << endl;
        cout << "  2. AcWing 801 题目模式" << endl;
        cout << "  3. 退出" << endl;
        cout << "请选择: ";
        
        int choice;
        if (!(cin >> choice) || choice == 3) break;
        
        if (choice == 1) {
            // 演示模式
            cout << "请输入一个正整数: ";
            int x;
            cin >> x;
            demo_process(x);
            
        } else if (choice == 2) {
            // 题目模式
            cout << "请输入数字个数 N: ";
            int n;
            cin >> n;
            
            cout << "请输入 " << n << " 个整数: ";
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                cout << count_ones(x);
                if (i < n - 1) cout << " ";
            }
            cout << "\n" << endl;
        }
    }
    
    return 0;
}

/*
 * 测试示例：
 * 
 * 模式1 - 演示:
 *   输入: 12
 *   输出: 第1步: 12 - 4 = 8
 *        第2步: 8 - 8 = 0
 *        答案: 12 的二进制中有 2 个1
 * 
 * 模式2 - 题目:
 *   输入: 5
 *        1 2 3 4 5
 *   输出: 1 1 2 1 2
 * 
 * 知识点：
 * - lowbit(x) = x & (-x)
 * - 每次消除最右侧的1
 * - 应用: 树状数组、状态压缩DP
 */
