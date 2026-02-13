#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 离散化 (Discretization) - 值域大但数据稀疏的"缩骨功"
 * 
 * ============ 通俗理解 ============
 * 
 * 想象一张 10亿 格的纸条，但你只在其中 3 个格子上画圈：
 *   第 5 格、第 88888 格、第 10亿 格
 * 
 * 如果真的开 int a[1000000000]，内存会爆炸！
 * 
 * 离散化就是"剪纸条"：把中间没用的空白剪掉，只留有用的格子
 *   原始位置: 5,    88888,    1000000000
 *   映射下标: 1,    2,        3
 * 
 * 这样只需要 int a[3] 就够了！
 * 
 * ============ 三步标准流程 (背下来!) ============
 * 
 * 1. 存 - 把所有用到的坐标都扔进 vector<int> alls
 *        重要：不只是操作位置，查询的 l 和 r 也要加进去！
 * 
 * 2. 排 & 去 - sort(alls) + unique(alls) 去重
 * 
 * 3. 查 - 用 lower_bound 找原坐标对应的新下标
 * 
 * ============ AcWing 802 题 ============
 * 
 * 在 [-10^9, 10^9] 的数轴上：
 *   - n 次操作: 在位置 x 加 c
 *   - m 次查询: 求 [l, r] 区间和
 *   - n, m <= 10^5
 * 
 * 朴素做法: int a[2000000000] - 爆内存
 * 离散化: 只开 3*10^5 的数组，配合前缀和
 */

typedef long long LL;
typedef pair<int, int> PII;

const int N = 300010;  // 为什么是30万？n个操作 + 2m个查询端点，最多10^5+2*10^5

int n, m;
vector<int> alls;      // 所有用到的坐标（新坐标系的"字典"）
vector<PII> add;       // 操作: (位置x, 增加的值c)
vector<PII> query;     // 查询: (左端点l, 右端点r)

int a[N];              // 离散化后的数组（用新下标存值）
LL s[N];               // 前缀和数组

// 核心映射函数: 原始坐标 x -> 新下标 k
// 例如: x=1000000000 -> k=3
// 为什么 +1？让下标从1开始，方便前缀和，不用处理 s[-1]
int find(int x) {
    // lower_bound 返回第一个 >= x 的迭代器
    // 减去 begin() 得到下标(0,1,2...), 再 +1 变成(1,2,3...)
    return lower_bound(alls.begin(), alls.end(), x) - alls.begin() + 1;
}

int main() {
    cout << "=== 离散化 - 大坐标压缩技巧 ===" << endl;
    cout << "原理: 把 10^9 范围的坐标压缩到 1,2,3...\n" << endl;
    
    while (true) {
        cout << "选择模式:" << endl;
        cout << "  1. 原理演示 (看压缩过程)" << endl;
        cout << "  2. AcWing 802 (区间和题目)" << endl;
        cout << "  3. 退出" << endl;
        cout << "请选择: ";
        
        int choice;
        if (!(cin >> choice) || choice == 3) break;
        
        if (choice == 1) {
            // 演示模式
            cout << "\n=== 原理演示 ===" << endl;
            cout << "假设用到这些坐标: 1000000, 5, 234567, 5, 8\n" << endl;
            
            vector<int> coords = {1000000, 5, 234567, 5, 8};
            
            cout << "步骤1 - 原始坐标:" << endl;
            cout << "  ";
            for (int x : coords) cout << x << " ";
            cout << "\n" << endl;
            
            // 排序
            sort(coords.begin(), coords.end());
            cout << "步骤2 - 排序后:" << endl;
            cout << "  ";
            for (int x : coords) cout << x << " ";
            cout << "\n" << endl;
            
            // 去重
            coords.erase(unique(coords.begin(), coords.end()), coords.end());
            cout << "步骤3 - 去重后:" << endl;
            cout << "  ";
            for (int x : coords) cout << x << " ";
            cout << "\n" << endl;
            
            // 映射
            cout << "步骤4 - 映射关系:" << endl;
            for (size_t i = 0; i < coords.size(); i++) {
                cout << "  " << coords[i] << " -> " << (i + 1) << endl;
            }
            cout << endl;
            
        } else if (choice == 2) {
            // 题目模式
            cout << "\n=== AcWing 802 题目 ===" << endl;
            cout << "输入格式:" << endl;
            cout << "  第1行: N M (N个操作, M个查询)" << endl;
            cout << "  接下来N行: x c (在位置x加c)" << endl;
            cout << "  接下来M行: l r (查询[l,r]的和)\n" << endl;
            
            cout << "请输入 N M: ";
            if (!(cin >> n >> m)) {
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            
            // 清空
            alls.clear();
            add.clear();
            query.clear();
            for (int i = 0; i < N; i++) a[i] = 0, s[i] = 0;
            
            // 步骤1: 收集所有用到的坐标
            // 读 n 个操作
            for (int i = 0; i < n; i++) {
                int x, c;
                cin >> x >> c;
                add.push_back({x, c});
                alls.push_back(x);  // 这个坐标用到了！
            }
            
            // 读 m 个查询 (关键: l 和 r 也要存进去！)
            for (int i = 0; i < m; i++) {
                int l, r;
                cin >> l >> r;
                query.push_back({l, r});
                alls.push_back(l);  // 左端点用到了！
                alls.push_back(r);  // 右端点用到了！
            }
            
            // 步骤2: 排序 + 去重
            sort(alls.begin(), alls.end());
            alls.erase(unique(alls.begin(), alls.end()), alls.end());
            
            // 步骤3: 在新坐标系上执行操作
            // (1) 处理加值操作
            for (auto op : add) {
                int x = find(op.first);  // 原坐标 -> 新下标
                a[x] += op.second;       // 在新数组上加值
            }
            
            // (2) 预处理前缀和（标准板子）
            for (size_t i = 1; i <= alls.size(); i++) {
                s[i] = s[i - 1] + a[i];
            }
            
            // (3) 回答查询
            cout << "\n结果:" << endl;
            for (int i = 0; i < m; i++) {
                int l = find(query[i].first);   // 原始范围 -> 新下标
                int r = find(query[i].second);
                cout << s[r] - s[l - 1] << endl; // 区间和公式
            }
            cout << endl;
        }
    }
    
    return 0;
}

/*
 * ============ 测试用例（手动推导过程）============
 * 
 * 案例1 - AcWing 802 原题
 * 
 * 输入:
 *   3 3         (3个操作, 3个查询)
 *   1 2         (在x=1处加2)
 *   3 6         (在x=3处加6)
 *   7 5         (在x=7处加5)
 *   1 3         (查询[1,3]的和)
 *   4 6         (查询[4,6]的和)
 *   7 8         (查询[7,8]的和)
 * 
 * 手动推导:
 *   第1步 - 收集坐标: {1, 3, 7, 1, 3, 4, 6, 7, 8}
 *   第2步 - 排序去重: {1, 3, 4, 6, 7, 8}
 *   第3步 - 建立映射:
 *     原坐标 1 -> 新下标 1
 *     原坐标 3 -> 新下标 2
 *     原坐标 4 -> 新下标 3
 *     原坐标 6 -> 新下标 4
 *     原坐标 7 -> 新下标 5
 *     原坐标 8 -> 新下标 6
 *   
 *   执行操作:
 *     a[1] += 2  -> a[1] = 2
 *     a[2] += 6  -> a[2] = 6
 *     a[5] += 5  -> a[5] = 5
 *   
 *   前缀和:
 *     s[0] = 0
 *     s[1] = 0 + 2 = 2
 *     s[2] = 2 + 6 = 8
 *     s[3] = 8 + 0 = 8
 *     s[4] = 8 + 0 = 8
 *     s[5] = 8 + 5 = 13
 *     s[6] = 13 + 0 = 13
 *   
 *   回答查询:
 *     查询[1,3]: find(1)=1, find(3)=2 -> s[2]-s[0] = 8
 *     查询[4,6]: find(4)=3, find(6)=4 -> s[4]-s[2] = 0
 *     查询[7,8]: find(7)=5, find(8)=6 -> s[6]-s[4] = 5
 * 
 * 输出:
 *   8
 *   0
 *   5
 * 
 * 案例2 - 极端坐标
 * 输入: 2 1
 *       -1000000000 10
 *       1000000000 20
 *       -1000000000 1000000000
 * 输出: 30
 * 
 * ============ 离散化万能板子 ============
 * 
 * 遇到"值域大但数据稀疏"的题，直接套：
 * 
 * // 1. 存坐标
 * vector<int> alls;
 * // 把所有 x, l, r 都 push_back 进去
 * 
 * // 2. 排序 + 去重
 * sort(alls.begin(), alls.end());
 * alls.erase(unique(alls.begin(), alls.end()), alls.end());
 * 
 * // 3. 映射函数
 * int find(int x) {
 *     return lower_bound(alls.begin(), alls.end(), x) - alls.begin() + 1;
 * }
 * 
 * // 4. 在新数组上操作
 * // 用 find(x) 获取新下标，然后操作 a[] 和 s[]
 * 
 * ============ 关键函数 ============
 * 
 * unique(v.begin(), v.end())
 *   - 去除相邻重复元素，返回去重后的尾后迭代器
 *   - 必须先 sort()！
 * 
 * lower_bound(v.begin(), v.end(), x)
 *   - 二分查找第一个 >= x 的位置，O(log n)
 * 
 * 为什么必须离散化？
 *   - int a[1000000000] 会爆内存（4GB+）
 *   - 但实际只用到约30万个位置
 *   - 离散化把这30万个坑紧凑排列，忽略中间空地
 */
