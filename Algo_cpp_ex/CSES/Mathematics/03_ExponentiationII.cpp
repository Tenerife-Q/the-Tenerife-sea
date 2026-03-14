/*
题目：Exponentiation II

描述（中）：给定 n 次查询，每次给出三个整数 a, b, c，计算 a^{b^c} mod 10^9+7。
数据范围：0 ≤ a,b,c ≤ 10^9，1 ≤ n ≤ 10^5。注意题目中的边界约定（如 0^0 的处理）。

Description (EN): Given n queries, each with integers a, b, c, compute a^{b^c} modulo 10^9+7.
Constraints: 0 ≤ a,b,c ≤ 10^9, 1 ≤ n ≤ 10^5. Pay attention to corner cases such as 0^0.

来源：CSES — Exponentiation II (Mathematics)

下面给出精炼的模板代码与核心注释（ICPC/竞赛友好，便于盲打）
*/

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

const int64 MOD = 1000000007LL;
const int64 PHI = MOD - 1; // 因为 MOD 是质数，phi(MOD)=MOD-1

// 快速幂：计算 (base^exp) % mod
int64 mod_pow(int64 base, int64 exp, int64 mod) {
    base %= mod;
    int64 res = 1 % mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// 处理单次查询：计算 a^{b^c} mod MOD
// 核心思路：利用费马小定理对指数降模（对 MOD 降到 MOD-1），并注意 a==0 的特判
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    while (n--) {
        int64 a, b, c;
        cin >> a >> b >> c;

        // 特判底数为 0 的情形（非常重要）：
        // 真实值是 a^{b^c}；当 a==0 时，需要区分 b^c 是否为 0
        if (a == 0) {
            // 若 b == 0 且 c > 0，则 b^c = 0 -> a^{0} = 0^0，按题约定视为 1
            if (b == 0 && c > 0) {
                cout << 1 << '\n';
            } else {
                // 其余情况：要么 b^c > 0（结果 0^{正数}=0），要么 b==0&&c==0（b^c=1 -> 0^1=0）
                cout << 0 << '\n';
            }
            continue;
        }

        // 计算 exp = b^c mod (MOD-1)
        // 注意：使用 mod_pow 计算 b^c % PHI 即可（费马小定理）
        int64 exp_mod = mod_pow(b % PHI, c, PHI);

        // 当 b==0 且 c==0 时，mod_pow 会返回 1（0^0 按题约定为 1），
        // 这与我们在 a==0 时的特判逻辑保持一致。

        // 最终计算 a^{exp_mod} mod MOD
        int64 ans = mod_pow(a % MOD, exp_mod, MOD);
        cout << ans << '\n';
    }

    return 0;
}

/*
核心注释小结：
- 对于 a^{b^c}，因 MOD 为质数，可用费马小定理将指数对 (MOD-1) 取模：exp = b^c % (MOD-1)，再计算 a^exp % MOD。
- 但需注意 a==0 的特殊情况：若 a==0 且 b==0 且 c>0，则 b^c=0，导致 0^0（按题约定为 1），所以需单独处理。
- 模板采用可盲打的 `mod_pow(base, exp, mod)`，并在实现中使用 __int128 避免乘法溢出。

复杂度：每次查询 O(log b + log a) 时间，满足 n ≤ 1e5 的要求。
*/
