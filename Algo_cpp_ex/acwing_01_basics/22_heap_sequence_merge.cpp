/*
 * ============================================
 *   序列合并 - 堆/优先队列 + 多路归并
 *   Luogu P1631 序列合并
 *   核心算法: 小根堆 + N路归并
 * ============================================
 * 
 * 【问题】
 * 给两个长度为 N 的递增序列 A, B
 * 计算 A[i] + B[j] 的所有组合（共 N² 个）
 * 求其中最小的 N 个和
 * 
 * 【为什么暴力不行】
 * - N ≤ 10⁵，则 N² = 10¹⁰ (100亿)
 * - 内存：10¹⁰ × 4字节 = 40GB
 * - 时间：排序 O(N²logN²) 无法接受
 * 
 * 【核心思想：N路归并的矩阵模型】
 * 
 * 把所有可能的和想象成 N×N 矩阵：
 * 
 *           B[1]  B[2]  B[3]  B[4]
 *         ┌─────┬─────┬─────┬─────┐
 *   A[1]  │ 4  →│ 6  →│ 7  →│ 8   │  行1 (递增)
 *         ├─────┼─────┼─────┼─────┤
 *   A[2]  │ 6  →│ 8  →│ 9  →│ 10  │  行2 (递增)
 *         ├─────┼─────┼─────┼─────┤
 *   A[3]  │ 7  →│ 9  →│ 10 →│ 11  │  行3 (递增)
 *         ├─────┼─────┼─────┼─────┤
 *   A[4]  │ 9  →│ 11 →│ 12 →│ 13  │  行4 (递增)
 *         └─────┴─────┴─────┴─────┘
 *          ↑
 *        起点都在第一列
 * 
 * 【关键观察】
 * 1. 每一行从左到右递增（因为 B 有序）
 * 2. 全局最小值一定在某一行的开头
 * 3. 类比：N个赛道，每个赛道选手按速度排队
 *    - 全场最快的必在 N 个赛道的第一名中
 *    - 拿走一个选手，该赛道的下一名补位
 * 
 * 【算法流程】
 * 1. 初始化：把每行的首元素 A[i]+B[1] 放入小根堆
 * 2. 循环 N 次：
 *    a) 取出堆顶（当前最小）并输出
 *    b) 让该行的下一个元素 A[i]+B[j+1] 入堆
 * 
 * 【数据结构】
 * priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>
 * - pair.first: 和的值
 * - pair.second: 行号（标识来自哪个 A[i]）
 * - greater: 小根堆（默认是大根堆）
 * 
 * 【复杂度】
 * - 时间：O(N log N) —— N 次堆操作，每次 O(log N)
 * - 空间：O(N) —— 堆中始终只有 N 个元素
 * vs. 暴力 O(N²logN²) 和 O(N²)，巨大提升！
 * 
 * 【扩展应用】
 * - 合并 K 个有序链表 (LeetCode 23)
 * - 超级丑数 (LeetCode 313)
 * - 查找和最小的 K 对数字 (LeetCode 373)
 */

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100005;
int n;
int a[N], b[N];
int id[N]; // id[i]: 第 i 行目前用到 B 的第几个数（指针）

// 小根堆：存 {和的值, 行号}
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

// ========== 演示模式：可视化堆的运作过程 ==========
void demo_merge() {
    cout << "\n=== 多路归并演示 ===" << endl;
    
    // 显示输入
    cout << "A 数组: ";
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\nB 数组: ";
    for (int i = 1; i <= n; i++) cout << b[i] << " ";
    cout << "\n" << endl;
    
    // 显示矩阵
    cout << "所有可能的和（矩阵视图）：" << endl;
    cout << "     ";
    for (int j = 1; j <= n; j++) {
        printf("B[%d]=%d  ", j, b[j]);
    }
    cout << endl;
    
    for (int i = 1; i <= n; i++) {
        printf("A[%d]=%d ", i, a[i]);
        for (int j = 1; j <= n; j++) {
            printf("%4d  ", a[i] + b[j]);
        }
        cout << endl;
    }
    cout << endl;
    
    // 初始化堆
    cout << "【初始化】将每行的首元素入堆：" << endl;
    while (!q.empty()) q.pop(); // 清空
    for (int i = 1; i <= n; i++) {
        id[i] = 1;
        q.push({a[i] + b[1], i});
        cout << "  行" << i << ": A[" << i << "]+B[1] = " 
             << a[i] << "+" << b[1] << " = " << (a[i] + b[1]) << endl;
    }
    
    // 逐步取出前 N 小
    cout << "\n【多路归并过程】：" << endl;
    vector<int> result;
    int cnt = n;
    while (cnt--) {
        auto top = q.top();
        q.pop();
        
        int val = top.first;
        int row = top.second;
        
        result.push_back(val);
        
        cout << "步骤" << (n - cnt) << ": ";
        cout << "取出堆顶 " << val << " (来自行" << row << ": A[" << row << "]+B[" << id[row] << "])";
        
        // 替补进场
        id[row]++;
        if (id[row] <= n) {
            int next_val = a[row] + b[id[row]];
            q.push({next_val, row});
            cout << " -> 行" << row << "下一个入堆: " << next_val 
                 << " (A[" << row << "]+B[" << id[row] << "])" << endl;
        } else {
            cout << " -> 行" << row << "已用完" << endl;
        }
    }
    
    // 输出结果
    cout << "\n最小的 " << n << " 个和: ";
    for (int x : result) cout << x << " ";
    cout << "\n" << endl;
}

// ========== 题目模式：直接输出答案 ==========
void solve() {
    // 初始化堆
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        id[i] = 1;
        q.push({a[i] + b[1], i});
    }
    
    // 取前 N 小
    for (int cnt = 0; cnt < n; cnt++) {
        auto top = q.top();
        q.pop();
        
        cout << top.first;
        if (cnt < n - 1) cout << " ";
        
        int row = top.second;
        id[row]++;
        if (id[row] <= n) {
            q.push({a[row] + b[id[row]], row});
        }
    }
    cout << endl;
}

int main() {
    cout << "=== 序列合并 (Luogu P1631) ===" << endl;
    cout << "算法: 小根堆 + N路归并\n" << endl;
    
    while (true) {
        cout << "选择模式:" << endl;
        cout << "  1. 详细演示（看合并过程）" << endl;
        cout << "  2. 题目模式（只输出答案）" << endl;
        cout << "  3. 预设示例" << endl;
        cout << "  4. 退出" << endl;
        cout << "请选择: ";
        
        int choice;
        if (!(cin >> choice) || choice == 4) break;
        
        if (choice == 1) {
            // 详细演示
            cout << "\n输入 N: ";
            if (!(cin >> n) || n <= 0) {
                cout << "输入无效。" << endl;
                continue;
            }
            
            cout << "输入 A 数组 " << n << " 个数: ";
            for (int i = 1; i <= n; i++) cin >> a[i];
            
            cout << "输入 B 数组 " << n << " 个数: ";
            for (int i = 1; i <= n; i++) cin >> b[i];
            
            demo_merge();
            
        } else if (choice == 2) {
            // 题目模式
            cout << "\n输入 N: ";
            if (!(cin >> n) || n <= 0) {
                cout << "输入无效。" << endl;
                continue;
            }
            
            cout << "输入 A 数组: ";
            for (int i = 1; i <= n; i++) cin >> a[i];
            
            cout << "输入 B 数组: ";
            for (int i = 1; i <= n; i++) cin >> b[i];
            
            solve();
            
        } else if (choice == 3) {
            // 预设示例
            cout << "\n=== 预设示例 ===" << endl;
            n = 4;
            int A[] = {0, 1, 3, 4, 6}; // 下标从1开始
            int B[] = {0, 3, 5, 6, 7};
            
            for (int i = 1; i <= n; i++) {
                a[i] = A[i];
                b[i] = B[i];
            }
            
            demo_merge();
        }
    }
    
    return 0;
}
