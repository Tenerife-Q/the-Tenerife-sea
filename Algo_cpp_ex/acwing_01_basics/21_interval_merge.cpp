#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 区间合并 (Interval Merging) - 贪心算法
 * 
 * ============ 核心思想（图解）============
 * 
 * 给定多个区间，合并所有有交集的区间
 * 
 * 三种情况（按左端点排序后）：
 * 
 * 1. 覆盖/跳过 - 新区间被当前区间包含
 *    st          ed
 *    ├───────────┤
 *       ├──┤ r         <- 新区间 [l, r]
 *          i
 *    处理: ed 不变，跳过
 * 
 * 2. 重叠 - 有交集，需要合并
 *    st      ed
 *    ├───────┤
 *          ├────┤ r    <- 新区间 [l, r]
 *          l    i
 *    处理: ed = max(ed, r) = r
 * 
 * 3. 相离 - 无交集，输出当前区间
 *    st  ed
 *    ├───┤
 *                ├──┤  <- 新区间 [l, r]
 *                l  r
 *    处理: 输出 [st, ed]，开始新区间 [l, r]
 * 
 * ============ 算法步骤 ============
 * 
 * 1. 按左端点排序
 * 2. 维护当前区间 [st, ed]
 * 3. 遍历每个区间 [l, r]:
 *    if (l <= ed)  合并: ed = max(ed, r)
 *    else          输出 [st, ed]，开始新区间
 * 
 * AcWing 803: 输出合并后区间个数
 * 洛谷 P1496: 输出合并后区间总长度
 */

typedef pair<int, int> PII;

const int N = 100010;
int n;
vector<PII> segs;  // 存储所有区间

// 合并区间，返回合并后的区间数组
vector<PII> merge(vector<PII> &segs) {
    vector<PII> res;
    
    // 步骤1: 按左端点排序（关键！）
    sort(segs.begin(), segs.end());
    
    // 步骤2: 初始化当前维护的区间 [st, ed]
    int st = -2e9, ed = -2e9;  // -2e9 作为哨兵（负无穷）
    
    // 步骤3: 贪心扫描
    for (auto seg : segs) {
        if (ed < seg.first) {
            // 情况3 - 相离：当前区间的右端点 < 新区间的左端点
            //   st  ed
            //   ├───┤      ├──┤ [seg.first, seg.second]
            // 处理: 输出 [st, ed]，开始新区间
            if (st != -2e9) res.push_back({st, ed});
            st = seg.first;
            ed = seg.second;
        } else {
            // 情况1+2 - 覆盖或重叠：有交集
            //   st      ed
            //   ├───────┤
            //      ├──┤ 或 ├────┤
            // 处理: 合并，取右端点最大值
            ed = max(ed, seg.second);
        }
    }
    
    // 别忘了最后一个区间！
    if (st != -2e9) res.push_back({st, ed});
    
    return res;
}

// 演示合并过程
void demo_merge(vector<PII> &segs) {
    cout << "\n=== 合并演示 ===" << endl;
    
    // 原始区间
    cout << "原始区间 (" << segs.size() << " 个):" << endl;
    for (auto seg : segs) {
        cout << "  [" << seg.first << ", " << seg.second << "]" << endl;
    }
    
    // 排序
    sort(segs.begin(), segs.end());
    cout << "\n排序后:" << endl;
    for (auto seg : segs) {
        cout << "  [" << seg.first << ", " << seg.second << "]" << endl;
    }
    
    // 逐步合并
    cout << "\n合并过程:" << endl;
    int st = -2e9, ed = -2e9;
    int step = 0;
    vector<PII> result;
    
    for (auto seg : segs) {
        step++;
        cout << "步骤" << step << ": [" << seg.first << ", " << seg.second << "] ";
        
        if (ed < seg.first) {
            // 相离
            if (st != -2e9) {
                cout << "-> 相离，输出 [" << st << ", " << ed << "]" << endl;
                result.push_back({st, ed});
            }
            st = seg.first;
            ed = seg.second;
            if (step == 1) cout << "-> 初始区间" << endl;
            else cout << "-> 开新区间" << endl;
        } else {
            // 重叠或覆盖
            int old_ed = ed;
            ed = max(ed, seg.second);
            if (old_ed != ed) {
                cout << "-> 重叠，扩展到 [" << st << ", " << ed << "]" << endl;
            } else {
                cout << "-> 覆盖，跳过" << endl;
            }
        }
    }
    
    // 最后一个区间
    if (st != -2e9) {
        cout << "\n输出最后区间: [" << st << ", " << ed << "]" << endl;
        result.push_back({st, ed});
    }
    
    // 结果
    cout << "\n合并后 (" << result.size() << " 个):" << endl;
    for (auto seg : result) {
        cout << "  [" << seg.first << ", " << seg.second << "]" << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== 区间合并 (AcWing 803) ===" << endl;
    cout << "算法: 排序 + 贪心扫描\n" << endl;
    
    while (true) {
        cout << "选择模式:" << endl;
        cout << "  1. 详细演示（看合并过程）" << endl;
        cout << "  2. 题目模式（只输出个数）" << endl;
        cout << "  3. 预设示例" << endl;
        cout << "  4. 退出" << endl;
        cout << "请选择: ";
        
        int choice;
        if (!(cin >> choice) || choice == 4) break;
        
        if (choice == 1) {
            // 详细演示
            cout << "\n请输入区间个数 N: ";
            if (!(cin >> n) || n <= 0) {
                cout << "输入无效。" << endl;
                continue;
            }
            
            segs.clear();
            for (int i = 0; i < n; i++) {
                int l, r;
                cin >> l >> r;
                segs.push_back({l, r});
            }
            
            demo_merge(segs);
            
        } else if (choice == 2) {
            // 题目模式
            cout << "\n请输入区间个数 N: ";
            if (!(cin >> n) || n <= 0) {
                cout << "输入无效。" << endl;
                continue;
            }
            
            segs.clear();
            for (int i = 0; i < n; i++) {
                int l, r;
                cin >> l >> r;
                segs.push_back({l, r});
            }
            
            vector<PII> res = merge(segs);
            cout << "合并后的区间个数: " << res.size() << "\n" << endl;
            
        } else if (choice == 3) {
            // 预设示例
            cout << "\n=== 预设示例 ===" << endl;
            segs = {{1, 2}, {2, 4}, {5, 6}, {7, 8}, {7, 9}};
            demo_merge(segs);
        }
    }
    
    return 0;
}

/*
 * 测试用例：
 * 
 * 示例1 - AcWing 803 原题:
 * 输入:
 *   5
 *   1 2
 *   2 4
 *   5 6
 *   7 8
 *   7 9
 * 
 * 输出:
 *   3
 * 
 * 解释:
 *   排序后: [1,2], [2,4], [5,6], [7,8], [7,9]
 *   合并 [1,2] 和 [2,4] -> [1,4]
 *   [5,6] 独立
 *   合并 [7,8] 和 [7,9] -> [7,9]
 *   最终: [1,4], [5,6], [7,9]，共3个区间
 * 
 * 示例2 - 全部重叠:
 * 输入:
 *   3
 *   1 10
 *   2 3
 *   4 5
 * 
 * 输出:
 *   1
 * 
 * 解释:
 *   [2,3] 和 [4,5] 都被 [1,10] 包含
 *   合并后只有 [1,10]
 * 
 * 示例3 - 完全不重叠:
 * 输入:
 *   3
 *   1 2
 *   4 5
 *   7 8
 * 
 * 输出:
 *   3
 * 
 * 解释:
 *   三个区间互不相交，无法合并
 * 
 * 示例4 - 边界情况（相邻但不重叠）:
 * 输入:
 *   2
 *   1 2
 *   3 4
 * 
 * 输出:
 *   2
 * 
 * 解释:
 *   [1,2] 和 [3,4] 不重叠（2 < 3）
 *   注意：如果题目要求相邻也算重叠，需修改判断条件为 ed < seg.first - 1
 * 
 * 知识扩展：
 * 
 * 1. 区间合并的变种：
 *    - 输出合并后的所有区间（而非只输出个数）
 *    - 计算合并后区间的总长度
 *    - 判断某个点是否在合并后的区间中
 * 
 * 2. 相关算法：
 *    - 区间覆盖问题（贪心）
 *    - 区间选点问题
 *    - 活动安排问题
 * 
 * 3. 关键点：
 *    - 必须先按左端点排序
 *    - 合并时要取右端点的最大值 ed = max(ed, r)
 *    - 不要忘记最后一个区间的处理
 * 
 * 4. 判断两个区间是否有交集：
 *    设区间1: [a, b]，区间2: [c, d]
 *    - 有交集: max(a, c) <= min(b, d)
 *    - 无交集: b < c 或 d < a
 * 
 * 5. 时间复杂度分析：
 *    - 排序: O(n log n)
 *    - 扫描: O(n)
 *    - 总时间: O(n log n)
 * 
 * 6. 空间复杂度：O(n)
 */
