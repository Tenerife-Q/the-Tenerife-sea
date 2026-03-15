
/*
太棒了！理解约数之和定理的推导，是吃透这道题最核心的一步。


---

一、 约数之和的数学原理推导

假设一个数字 $N$ 被质因数分解为：
$$N = p_1^{k_1} \times p_2^{k_2} \times \dots \times p_n^{k_n}$$

1. 约数是怎么长出来的？
任何一个约数 $d$ 都是从质因数中挑选组合得到：
$$d = p_1^{a_1} \times p_2^{a_2} \times \dots \times p_n^{a_n},\quad 0 \le a_i \le k_i.$$ 

2. 见证奇迹的乘法分配律
要求的是所有可能组成的约数之和。通过乘法分配律可以打包为：
$$\sigma(N) = (1 + p_1 + p_1^2 + \dots + p_1^{k_1}) (1 + p_2 + p_2^2 + \dots + p_2^{k_2}) \dots (1 + p_n + \dots + p_n^{k_n}).$$

---

二、 结合代码：如何计算 $(1 + p + p^2 + \dots + p^k)$？

目标是快速计算 $S = 1 + p + p^2 + \dots + p^k \pmod M$。
两种常见思路：等比数列法 与 秦九韶算法（Horner）。

方法 A：等比数列求和公式（代码中使用的极速解法）
$$S = \frac{p^{k+1} - 1}{p - 1} \pmod M.$$ 
在模 $M$ 下将除法替换为乘以逆元（费马小定理）：$a^{-1} \equiv a^{M-2} \pmod M$。

对应代码实现要点：
1) 计算分子：`(modPow(p, k+1, MOD) - 1 + MOD) % MOD`。
2) 计算分母逆元：`modInverse(p-1, MOD)`。
3) 乘入总和：`sum = sum * term_sum % MOD`。

复杂度：快速幂和逆元均为 $O(\log k)$，对 $k\le10^9$ 极快。

方法 B：秦九韶算法（Horner）
将多项式写成迭代形式：
```
ll term_sum = 1;
for (int j = 1; j <= k; j++) {
    term_sum = (term_sum * p + 1) % MOD;
}
```

---
- 等比数列+逆元：$O(\log k)$，适用于本题（$M$ 为素数）。
- 秦九韶算法：$O(k)$，仅在 $k$ 较小或无法使用逆元时适用。

拓展：若模数不是素数或逆元不存在，可用分治法计算等比数列和以达到 $O(\log k)$。
/*
说明：约数之和的推导与两种求和方法（等比公式 vs 秦九韶），已按小节整理以便阅读。

一、因子分解与约数形式
 设 N = p1^k1 * p2^k2 * ... * pn^kn
 任一约数 d 的形式为 d = p1^a1 * p2^a2 * ... * pn^an, 其中 0 <= ai <= ki

二、乘法分配律与约数之和
 由分配律可得：
     sigma(N) = Π_{i=1..n} (1 + p_i + p_i^2 + ... + p_i^{k_i})
 示例：N = 12 = 2^2 * 3^1
     (1+2+4) * (1+3) = 1+3+2+6+4+12 = 28

三、如何计算单个括号 S = 1 + p + p^2 + ... + p^k (mod M)
 方法 A：等比数列公式（推荐，题中使用）
     S = (p^{k+1} - 1) / (p - 1)  （在模 M 下使用逆元）
     代码要点：
         ll num = (modPow(p, k + 1, MOD) - 1 + MOD) % MOD;
         ll den = modInverse(p - 1, MOD);
         ll term_sum = num * den % MOD;
     复杂度：O(log k)

 方法 B：秦九韶（Horner）
     term_sum = 1; for (j = 1..k) term_sum = (term_sum * p + 1) % MOD;
     复杂度：O(k)，当 k 很大（如 1e9）会 TLE

四、结论
    当 MOD = 1e9+7（素数）时，优先使用等比公式+费马求逆元，能在 O(log k) 内完成。
    若 MOD 非素数或逆元不存在，可考虑分治法计算等比和以达 O(log k) 复杂度。
*/



// 约数之积数学原理推导以及公式见draft



#include <iostream>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;        // 普通的模数 M
const ll MOD_EXP = 1000000006;    // 指数的模数 M - 1

// 快速幂算法: (base^exp) % mod
ll modPow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// 计算逆元: 根据费马小定理 a^(M-2) % M
ll modInverse(ll n, ll mod) {
    return modPow(n, mod - 2, mod);
}

int main() {
    // 提升 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    ll count = 1;              // 约数个数
    ll sum = 1;                // 约数之和
    ll prod = 1;               // 约数之积
    
    // 用于“约数之积”递推中，维护前 i 个质数的约数个数
    // 注意：这里的乘法是在指数层面上进行的，所以必须对 MOD_EXP (10^9+6) 取模！
    ll div_cnt_mod_exp = 1;    

    for (int i = 0; i < n; i++) {
        ll p, k;
        cin >> p >> k;

        // ==========================================
        // 1. 维护约数个数 (Number of Divisors)
        // ==========================================
        count = count * (k + 1) % MOD;

        // ==========================================
        // 2. 维护约数之和 (Sum of Divisors)
        // ==========================================
        // 分子：(p^(k+1) - 1) % MOD
        ll num = (modPow(p, k + 1, MOD) - 1 + MOD) % MOD;
        // 分母的逆元：(p - 1)^(-1) % MOD
        ll den = modInverse(p - 1, MOD);
        // 当前质数因子的贡献：分子 * 逆元 % MOD
        ll term_sum = num * den % MOD;
        sum = sum * term_sum % MOD;

        // ==========================================
        // 3. 维护约数之积 (Product of Divisors)
        // ==========================================
        // 第一部分：旧的乘积被重复计算了 (k+1) 次
        ll term1 = modPow(prod, k + 1, MOD);
        
        // 第二部分：新质数 p 贡献的指数
        // 公式：k*(k+1)/2 * 之前的约数个数
        // k <= 10^9，k*(k+1) 约等于 10^18，刚好在 long long 范围内不溢出
        ll power_of_p = (k * (k + 1) / 2) % MOD_EXP;
        ll total_power = (power_of_p * div_cnt_mod_exp) % MOD_EXP;
        ll term2 = modPow(p, total_power, MOD);
        
        // 合并生成新的乘积
        prod = term1 * term2 % MOD;

        // 更新用于指数层面的旧约数个数 (对 MOD_EXP 取模)
        div_cnt_mod_exp = div_cnt_mod_exp * (k + 1) % MOD_EXP;
    }

    cout << count << " " << sum << " " << prod << "\n";

    return 0;
}



#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MOD_EXP = 1e9 + 6; // 指数层面的模数 (M-1)

// 快速幂：计算 (a^b) % m
ll power(ll a, ll b, ll m = MOD) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = (res * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return res;
}

// 模逆元：用于计算约数之和的分母部分
ll modInverse(ll n) {
    return power(n, MOD - 2);
}

int main() {
    // 提升大规模数据下的 I/O 效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
    }

    // 1. 计算约数个数 (Number of Divisors)
    ll cnt = 1;
    for (int i = 0; i < n; i++) {
        cnt = (cnt * (k[i] + 1)) % MOD;
    }

    // 2. 计算约数之和 (Sum of Divisors)
    ll sum = 1;
    for (int i = 0; i < n; i++) {
        // 公式: (x^(k+1)-1) / (x-1)
        ll num = (power(x[i], k[i] + 1) - 1 + MOD) % MOD;
        ll den = modInverse(x[i] - 1);
        ll term = (num * den) % MOD;
        sum = (sum * term) % MOD;
    }

    // 3. 计算约数之积 (Product of Divisors)
    // 难点在于指数 d(N)/2 % (MOD-1) 的处理
    ll prod = 1;
    ll div_cnt_for_exp = 1;
    bool has_even_k_plus_1 = false;

    // 判定是否为完全平方数，并处理指数项
    for (int i = 0; i < n; i++) {
        if (!has_even_k_plus_1 && (k[i] + 1) % 2 == 0) {
            // 找到第一个偶数项 (ki+1)，除以 2 解决 d(N)/2 的整数问题
            div_cnt_for_exp = (div_cnt_for_exp * ((k[i] + 1) / 2)) % MOD_EXP;
            has_even_k_plus_1 = true;
        } else {
            div_cnt_for_exp = (div_cnt_for_exp * (k[i] + 1)) % MOD_EXP;
        }
    }

    if (has_even_k_plus_1) {
        // 情况 A: N 不是完全平方数，直接用 N^(d(N)/2)
        for (int i = 0; i < n; i++) {
            ll base = power(x[i], k[i]);
            prod = (prod * power(base, div_cnt_for_exp)) % MOD;
        }
    } else {
        // 情况 B: N 是完全平方数，所有的 k[i] 都是偶数
        // 此时 div_cnt_for_exp 是 d(N)，公式变为 (sqrt(N))^d(N)
        for (int i = 0; i < n; i++) {
            ll base = power(x[i], k[i] / 2); // sqrt(xi^ki) = xi^(ki/2)
            prod = (prod * power(base, div_cnt_for_exp)) % MOD;
        }
    }

    cout << cnt << " " << sum << " " << prod << "\n";

    return 0;
}