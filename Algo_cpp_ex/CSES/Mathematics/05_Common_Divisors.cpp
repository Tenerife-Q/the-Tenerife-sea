/*
第 5 题：Common Divisors (CSES - 1081)

题目大意：
给定 n 个正整数，你需要从这 n 个数中选出两个数，使得它们的最大公约数（GCD）最大。
数据范围：2 ≤ n ≤ 2e5，每个整数 1 ≤ x_i ≤ 1e6。

思路与详解（反向思维 + 调和级数）：

1) 直观的正向穷举：枚举所有对 (i,j) 并计算 GCD，时间 O(n^2)，对于 n=2e5 必然 TLE。

2) 破局之道：逆向枚举 GCD 值 g。
   - 设 cnt[v] 为值 v 在数组中出现的次数。
   - 如果某个 g 存在至少两个数组元素为 g 的倍数，那么 g 有资格成为候选 GCD。
   - 只需从大到小枚举 g，统计其倍数 g,2g,3g,... 在数组中出现的总次数，若 >=2 则直接输出 g（因为倒序枚举，第一个满足的即为最大）。

3) 复杂度分析：
   - 枚举所有 g 的倍数总工作量为 X * (1 + 1/2 + 1/3 + ... + 1/X) ≈ X log X，其中 X = 1e6（题目上界）。
   - 实际操作约 1.4e7 次，加上 I/O 优化，C++ 可瞬间完成。

4) 代码（ICPC 竞赛友好、可盲打）：
*/

#include <iostream>
#include <vector>

using namespace std;

// 题目给定的最大值 10^6
const int MAX_X = 1000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> cnt(MAX_X + 5, 0);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x; cnt[x]++;
    }

    for (int g = MAX_X; g >= 1; --g) {
        int multiples_count = 0;
        for (int k = g; k <= MAX_X; k += g) {
            multiples_count += cnt[k];
            if (multiples_count >= 2) {
                cout << g << '\n';
                return 0;
            }
        }
    }

    return 0;
}

/*
教练话语总结：
这道题的核心是“枚举答案并验证”的逆向思维，结合调和级数的复杂度分析将原本 O(n^2) 的问题转化为 O(X log X) 的可行算法。
掌握此类贡献/倒序枚举技巧，对后续的数论题（如 Sum of Divisors、Common Divisors 的变体）极其重要。
*/
