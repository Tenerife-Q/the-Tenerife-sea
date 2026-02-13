#include <iostream>
#include <algorithm>

using namespace std;

/*
 * AcWing 算法基础课 - 双指针算法 (Two Pointers)
 * 典型例题：最长连续不重复子序列
 * 
 * 核心思想：
 * 将双层循环 O(N^2) 优化为 O(N)。
 * 
 * 暴力做法：
 * for (int i = 0; i < n; i++)
 *     for (int j = 0; j <= i; j++)
 *         if (check(j, i)) res = max(res, i - j + 1);
 * 
 * 双指针做法：
 * 利用单调性。对于每一个 i，找到离它最远的左边界 j。
 * 当 i 向后移动时，j 只能向后移动，不可能回退（因为如果 j 在 i 时满足条件，i+1 时多了个新元素，j 只可能需要收缩，绝不需要扩张）。
 * 
 * 两个指针 i 和 j，i 负责猛冲，j 负责在后面收缩去重。
 */

const int N = 100010;
int n;
int a[N];
int s[N]; // 计数数组，s[x] 表示数字 x 在当前区间 [j, i] 中出现的次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "请输入数列长度 n: ";
    if (!(cin >> n)) return 0;

    cout << "请输入 " << n << " 个整数: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    int res = 0;
    
    // 双指针核心模板
    // i 是右边界，j 是左边界
    for (int i = 0, j = 0; i < n; i++) {
        // 1. i 进场：先把 a[i] 加入区间
        s[a[i]]++;
        
        // 2. j 收缩：如果刚加入的 a[i] 导致出现重复 (s[a[i]] > 1)
        // 就一直移动 j，把 j 指向的元素踢出区间，直到重复消失
        while (s[a[i]] > 1) {
            s[a[j]]--; // 踢出 a[j]
            j++;       // j 向前走
        }

        // 3. 更新答案：现在的 [j, i] 一定是不含重复元素的合法区间
        res = max(res, i - j + 1);
    }

    cout << "最长连续不重复子序列长度: " << res << endl;

    return 0;
}
