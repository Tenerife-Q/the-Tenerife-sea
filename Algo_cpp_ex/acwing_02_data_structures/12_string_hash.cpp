/*
 * ============================================
 *   字符串哈希 (String Hash)
 *   题目来源: AcWing 841. 字符串哈希
 * ============================================
 * 
 * 【问题】
 *   给定一个长度为 n 的字符串，查询两个子串是否完全相等。
 * 
 * 【核心思路】
 *   - 字符串前缀哈希法 (Rolling Hash / BKDRHash)
 *   - 把字符串看作 P 进制数。
 *   - h[i] = h[i-1] * P + str[i]
 *   - 区间 [l, r] 的哈希值: h[r] - h[l-1] * P^(r-l+1)
 *   - 经验值: P = 131 或 13331, Mod = 2^64 (unsigned long long自动溢出)
 * 
 * 【复杂度】
 *   - 预处理 O(n)
 *   - 查询 O(1)
 */

#include <iostream>

using namespace std;

typedef unsigned long long ULL;

const int N = 100010, P = 131;

int n, m;
char str[N];
ULL h[N], p[N]; // h是哈希数组，p是次方数组

// 获取区间 [l, r] 的哈希值
ULL get(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> (str + 1);

    p[0] = 1;
    for (int i = 1; i <= n; i ++ ) {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + str[i];
    }

    while (m -- ) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        if (get(l1, r1) == get(l2, r2)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}
