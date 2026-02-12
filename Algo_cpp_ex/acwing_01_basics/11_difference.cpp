#include <iostream>
using namespace std;

/*
 * AcWing 算法基础课 - 一维差分
 * 核心思想：差分是前缀和的逆运算
 * 
 * 定义：
 * 构造一个数组 B，使得 A 是 B 的前缀和。
 * 即：A[i] = B[1] + B[2] + ... + B[i]
 * 
 * 核心操作：
 * 如果我们要让原数组 A 在区间 [l, r] 上每个数都加上 c
 * 只需要操作差分数组 B:
 * B[l] += c
 * B[r + 1] -= c
 * 
 * 这样做的好处：
 * 将 O(N) 的区间修改操作降低为 O(1)。
 * 最后只需要对 B 求一遍前缀和，就能还原出修改后的 A。
 */

const int N = 100010;
int n, m;
int a[N], b[N];

// 核心插入函数
// 实际上，初始化 a[i] 也可以看作是在 [i, i] 区间插入了 a[i]
void insert(int l, int r, int c) {
    b[l] += c;
    b[r + 1] -= c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "请输入数组长度 n 和操作次数 m: ";
    if (!(cin >> n >> m)) return 0;

    cout << "请输入 " << n << " 个初始整数: ";
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        // 构造差分数组 B
        // 我们可以把初始数组看作是一次次在 [i, i] 范围插入 a[i]
        insert(i, i, a[i]);
    }

    cout << "请输入 " << m << " 组操作 (l r c) - 表示将区间 [l,r] 加上 c:" << endl;
    while (m--) {
        int l, r, c;
        cin >> l >> r >> c;
        insert(l, r, c);
    }

    // 还原数组 A
    // B 的前缀和就是 A
    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1]; // 此时 b[i] 变成了前缀和，即修改后的 a[i]
        cout << b[i] << " ";
    }
    cout << endl;

    return 0;
}
