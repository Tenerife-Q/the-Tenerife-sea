/*
 * ============================================
 *   单调队列 (Monotonic Queue) - 滑动窗口
 *   题目来源: AcWing 154. 滑动窗口
 * ============================================
 * 
 * 【问题】
 *   给定一个大小为 n 的数组，有一个大小为 k 的滑动窗口从左移到右。
 *   求每时刻窗口内的最小值和最大值。
 * 
 * 【核心思路】
 *   - 使用双端队列（Deque）存储下标。
 *   - 求最小值：维护单调递增队列。
 *     1. 队头滑出窗口：if (hh <= tt && q[hh] < i - k + 1) hh++;
 *     2. 保持单调性：if (a[q[tt]] >= a[i]) tt--;
 *     3. 入队：q[++tt] = i;
 *     4. 输出：a[q[hh]];
 *   - 求最大值：维护单调递减队列（类似）。
 * 
 * 【复杂度】
 *   - O(n)，每个元素进队一次出队一次。
 */

#include <iostream>

using namespace std;

const int N = 1000010;

int n, k;
int a[N], q[N]; // q stores indices

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; i ++ ) cin >> a[i];

    // 求最小值
    int hh = 0, tt = -1;
    for (int i = 0; i < n; i ++ ) {
        // 判断队头是否已经滑出窗口
        if (hh <= tt && i - k + 1 > q[hh]) hh ++ ;
        
        // 维护这一段窗口内的单调性（递增）
        // 如果新来的数比队尾小，那么队尾就没用了
        while (hh <= tt && a[q[tt]] >= a[i]) tt -- ;
        q[ ++ tt] = i;
        
        // 当窗口完全形成后开始输出（i >= k-1）
        if (i >= k - 1) cout << a[q[hh]] << " ";
    }
    cout << endl;

    // 求最大值
    hh = 0, tt = -1;
    for (int i = 0; i < n; i ++ ) {
        if (hh <= tt && i - k + 1 > q[hh]) hh ++ ;
        
        // 递减
        while (hh <= tt && a[q[tt]] <= a[i]) tt -- ;
        q[ ++ tt] = i;

        if (i >= k - 1) cout << a[q[hh]] << " ";
    }
    cout << endl;

    return 0;
}
