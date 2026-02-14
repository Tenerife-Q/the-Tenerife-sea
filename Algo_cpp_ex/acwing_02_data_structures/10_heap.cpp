/*
 * ============================================
 *   堆 (Heap) - 这里的模拟堆
 *   题目来源: AcWing 838. 堆排序
 * ============================================
 * 
 * 【问题】
 *   输入一个长度为 n 的整数数列，从小到大输出前 m 小的数。
 * 
 * 【核心思路】
 *   - 使用数组模拟小根堆。
 *   - h[N]: 存储堆元素，下标从1开始。
 *   - sz: 堆的大小。
 *   - down(u): 下沉操作，O(log n)
 *   - up(u): 上浮操作，O(log n)
 *   - 建堆: 从 n/2 处开始 down 到 1，O(n)
 * 
 * 【图解】
 *      1
 *    /   \
 *   2     3
 * 
 * 【复杂度】
 *   - 插入/删除: O(log n)
 *   - 获取最小值: O(1)
 */

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
int h[N], sz;

void down(int u) {
    int t = u; // t存储三个点（u, 2u, 2u+1）中最小值的下标
    if (u * 2 <= sz && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= sz && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t) {
        swap(h[u], h[t]);
        down(t);
    }
}

void up(int u) {
    while (u / 2 && h[u / 2] > h[u]) {
        swap(h[u / 2], h[u]);
        u /= 2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) cin >> h[i];
    sz = n;

    // 建堆：从倒数第二层开始down，时间复杂度 O(n)
    for (int i = n / 2; i; i -- ) down(i);

    while (m -- ) {
        cout << h[1] << " ";
        h[1] = h[sz];
        sz -- ;
        down(1);
    }
    cout << endl;

    return 0;
}
