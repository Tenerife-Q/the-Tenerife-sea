/**
 * ============================================================
 * 第一讲：基础算法 - 归并排序 (Merge Sort)
 * ============================================================
 * 
 * 核心思想：分治 (Divide and Conquer)
 * 1. 确定分界点：mid = (l + r) / 2
 * 2. 递归排序：递归 sort left, sort right
 * 3. 归并 (Merge)：合二为一 (核心难点，双指针算法)
 * 
 * 常见应用：
 * - 排序 (稳定排序，O(N log N))
 * - 求逆序对的数量 (重要应用)
 */

#include <iostream>
using namespace std;

const int N = 100010;
int q[N];
int tmp[N]; // 归并排序需要一个辅助数组

// ⚡ 核心模板代码
void merge_sort(int q[], int l, int r) {
    if (l >= r) return; // 可不可以是 l == r ? 可以，但加上 >= 更保险

    // 1. 确定分界点
    int mid = l + r >> 1; // 相当于 (l + r) / 2
    // 为什么不用 (l + r) / 2 ? 因为可能会溢出
    // 但 l + (r - l) / 2 也可以避免溢出
    // 溢出的情况：当 l 和 r 都很大时，l + r 可能超过 int 范围
    // l + r >> 1 是怎么利用位运算的性质使其等价于 (l + r) / 2 的？
    // 妈的就是>>1 就是除以2 十进制与二进制的转换运算 可以提个2出来

    // 2. 递归排序左右两边
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    // 3. 归并 (重点)
    int k = 0; // tmp 数组的索引
    int i = l, j = mid + 1; // 双指针

    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    // 把剩余部分接上去
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    // 4. 物归原主：把 tmp 里的结果倒回原数组 q
    for (i = l, k = 0; i <= r; i++, k++) q[i] = tmp[k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    /*
        练习输入:
        5
        3 1 2 4 5
    */
    if(cin >> n) {
        for(int i = 0; i < n; i++) cin >> q[i];

        merge_sort(q, 0, n - 1);

        for(int i = 0; i < n; i++) cout << q[i] << " ";
        cout << endl;
    }

    return 0;
}
