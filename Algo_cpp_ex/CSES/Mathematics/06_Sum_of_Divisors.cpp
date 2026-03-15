/*
题目：Sum of Divisors

描述（中）：令 σ(n) 表示整数 n 的所有正约数之和。例如 σ(12)=1+2+3+4+6+12=28。
给定 n，计算 S = sum_{i=1..n} σ(i) 并输出 S mod 1e9+7。

Description (EN): Let σ(n) denote the sum of divisors of n. Given n, compute
S = \sum_{i=1}^n σ(i) modulo 10^9+7.

输入 (Input):
 - 单行一个整数 n。

输出 (Output):
 - 输出 \sum_{i=1}^n σ(i) modulo 10^9+7。

约束 (Constraints):
 - 1 ≤ n ≤ 10^12

示例 (Example):
输入:
5

输出:
21

提示：本题的关键是整除分块（quotient block / number theoretic block），能将复杂度降到 O(√n)。参见文件下方实现与注释。
*/

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

const int64 MOD = 1000000007LL;
const int64 INV2 = 500000004LL; // inverse of 2 modulo MOD

// safe modular multiplication using 128-bit intermediate
inline int64 mod_mul(int64 a, int64 b) {
    return (int64)((__int128)a * b % MOD);
}

// sum of integers in [l, r] modulo MOD
inline int64 sum_range_mod(int64 l, int64 r) {
    int64 cnt = (r - l + 1) % MOD;
    int64 sum_lr = ((l % MOD) + (r % MOD)) % MOD;
    return mod_mul(mod_mul(sum_lr, cnt), INV2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    if (!(cin >> n)) return 0;

    int64 total = 0;

    // quotient-block loop: iterate over blocks where floor(n/d) is constant
    for (long long l = 1, r; l <= n; l = r + 1) {
        long long q = n / l;        // value of floor(n/d) for d in [l, r]
        r = n / q;                  // right end of block

        int64 q_mod = q % MOD;
        int64 block_sum = sum_range_mod(l, r); // sum of d over [l,r] mod MOD

        total += mod_mul(q_mod, block_sum);
        if (total >= MOD) total -= MOD;
    }

    cout << total % MOD << '\n';
    return 0;
}