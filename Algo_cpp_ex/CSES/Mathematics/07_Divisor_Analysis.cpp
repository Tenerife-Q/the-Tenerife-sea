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
