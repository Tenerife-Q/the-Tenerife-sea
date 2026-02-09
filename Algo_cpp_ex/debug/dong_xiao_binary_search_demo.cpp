#include <iostream>
#include <vector>
#include <algorithm> // for std::sort
using namespace std;

/**
 * ============================================================
 * 董晓算法 (Dong Xiao Algorithm) - 蓝红区域二分法
 * ============================================================
 * 
 * 核心逻辑 (The Core Logic):
 * 1. 把数组想象成两部分：左边是“蓝色区域”，右边是“红色区域”。
 * 2. 指针 L 永远停在蓝色区域，指针 R 永远停在红色区域。
 * 3. 初始时，L = -1 (假想的蓝色边界), R = n (假想的红色边界)。
 * 4. 循环结束时，L 和 R 相邻 (L + 1 == R)，此时：
 *    - L 指向蓝色区域的最后一个元素。
 *    - R 指向红色区域的第一个元素。
 * 
 * 优点 (Advantages):
 * - 不需要考虑 mid 加一还是减一 (l = mid, r = mid)。
 * - 不需要考虑 mid 计算时向上取整还是向下取整。
 * - 此时 mid = (l + r) / 2 永远不会陷入死循环，因为 r - l >= 2 (循环条件 l + 1 != r)。
 * - 能够自然处理空数组或答案不存在的情况 (L 停在 -1 或 R 停在 n)。
 */

const int N = 100010;
int q[N];

// 场景 1: 查找第一个 >= x 的数 (Find First >= x)
// 我们定义：
// 蓝色(左侧): q[i] < x
// 红色(右侧): q[i] >= x  <-- 我们要找的是红色的开端
int find_first_ge(int n, int x) {
    int l = -1, r = n; // 闭区间 [-1, n] 控制边界
    
    while (l + 1 != r) {
        int mid = l + (r - l) / 2; // (l+r)/2
        if (q[mid] < x) {
            l = mid; // mid 在蓝色区域，L 追过去
        } else {
            r = mid; // mid 在红色区域，R 追过去
        }
    }
    // 循环结束，L 是最后一个 < x 的，R 是第一个 >= x 的
    return r; // 返回红色起点
}

// 场景 2: 查找最后一个 <= x 的数 (Find Last <= x)
// 我们定义：
// 蓝色(左侧): q[i] <= x  <-- 我们要找的是蓝色的末尾
// 红色(右侧): q[i] > x
int find_last_le(int n, int x) {
    int l = -1, r = n;

    while (l + 1 != r) {
        int mid = l + (r - l) / 2;
        if (q[mid] <= x) {
            l = mid; // mid 在蓝色区域 (满足 <= x)
        } else {
            r = mid; // mid 在红色区域
        }
    }
    // 循环结束，L 是最后一个 <= x 的，R 是第一个 > x 的
    return l; // 返回蓝色终点
}

int main() {
    // 示例数据: 1, 2, 2, 3, 3, 4
    int raw_data[] = {1, 2, 2, 3, 3, 4};
    int n = 6;
    for(int i=0; i<n; i++) q[i] = raw_data[i];
    
    int target; 
    
    // 测试 1: 找 3 的起始位置 (第一个 >= 3)
    // 预期: Index 3 (数值 3)
    target = 3;
    int idx1 = find_first_ge(n, target);
    cout << "查找第一个 >= " << target << " 的位置: " << idx1 
         << " (值: " << (idx1 < n ? to_string(q[idx1]) : "None") << ")" << endl;

    // 测试 2: 找 2 的终止位置 (最后一个 <= 2)
    // 预期: Index 2 (数值 2)
    target = 2;
    int idx2 = find_last_le(n, target);
    cout << "查找最后一个 <= " << target << " 的位置: " << idx2 
         << " (值: " << (idx2 >= 0 ? to_string(q[idx2]) : "None") << ")" << endl;

    // 测试 3: 找不存在的数 (比如 5)
    // 预期: find_first_ge 返回 6 (n), find_last_le 返回 5 (最后一个 4)
    target = 5;
    cout << "查找 5 (不存在)..." << endl;
    cout << "第一个 >= 5: " << find_first_ge(n, target) << endl; 
    cout << "最后一个 <= 5: " << find_last_le(n, target) << endl;

    // 测试 4: 找比所有数都小的数 (比如 0)
    // 预期: find_first_ge 返回 0, find_last_le 返回 -1
    target = 0;
    cout << "查找 0 (比所有都小)..." << endl;
    cout << "第一个 >= 0: " << find_first_ge(n, target) << endl;
    cout << "最后一个 <= 0: " << find_last_le(n, target) << endl;

    return 0;
}
