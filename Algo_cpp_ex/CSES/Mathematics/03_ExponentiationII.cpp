/*
题目：Exponentiation II

描述（中）：给定 n 次查询，每次给出三个整数 a, b, c，计算 a^{b^c} mod 10^9+7。
数据范围：0 ≤ a,b,c ≤ 10^9，1 ≤ n ≤ 10^5。注意题目中的边界约定（如 0^0 的处理）。

Description (EN): Given n queries, each with integers a, b, c, compute a^{b^c} modulo 10^9+7.
Constraints: 0 ≤ a,b,c ≤ 10^9, 1 ≤ n ≤ 10^5. Pay attention to corner cases such as 0^0.

来源：CSES — Exponentiation II (Mathematics)

下面给出精炼的模板代码与核心注释（ICPC/竞赛友好，便于盲打）
*/


/*
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
*/


/*
核心注释小结：
- 对于 a^{b^c}，因 MOD 为质数，可用费马小定理将指数对 (MOD-1) 取模：exp = b^c % (MOD-1)，再计算 a^exp % MOD。
- 但需注意 a==0 的特殊情况：若 a==0 且 b==0 且 c>0，则 b^c=0，导致 0^0（按题约定为 1），所以需单独处理。
- 模板采用可盲打的 `mod_pow(base, exp, mod)`，并在实现中使用 __int128 避免乘法溢出。

复杂度：每次查询 O(log b + log a) 时间，满足 n ≤ 1e5 的要求。
*/

/*
作为一个备赛 ICPC 负责数学的选手，问出“为什么”是非常好的习惯！在数论里，知其然不知其所以然，到了赛场上稍微变形就会吃大亏。

这里之所以可以对**指数**取模（降幂），其核心基石是数论中的绝对重要定理：**费马小定理（Fermat's Little Theorem）**。

我来为你从数学推导的角度，把这个降幂的过程彻底扒开：

1. 理论基础：费马小定理
定理内容：如果 $p$ 是一个质数，且整数 $a$ 不是 $p$ 的倍数（即 $\gcd(a, p) = 1$），那么：
$$a^{p-1} \equiv 1 \pmod p$$

在这道题里，模数 $p = 10^9+7$ 是一个著名的质数。
所以，对于任何不是 $10^9+7$ 倍数的底数 $a$，都有：
$$a^{10^9+6} \equiv 1 \pmod{10^9+7}$$

2. 数学推导：如何利用定理降幂？
我们要算的是 $a^X \pmod p$，这里的巨大指数 $X = b^c$。

我们可以把这个巨大的指数 $X$，除以 $(p-1)$，得到商 $k$ 和余数 $r$。
写成带余除法的形式就是：
$$X = k \cdot (p-1) + r$$
其中，余数 $r = X \pmod{p-1}$。

现在，我们把这个式子代回到原来的底数 $a$ 上：
$$a^X = a^{k \cdot (p-1) + r}$$

根据指数运算的乘法法则，拆开它：
$$a^X = a^{k \cdot (p-1)} \cdot a^r$$
$$a^X = (a^{p-1})^k \cdot a^r$$

在 $\pmod p$ 的意义下，根据费马小定理，$(a^{p-1})$ 等价于 $1$。
所以：
$$(a^{p-1})^k \cdot a^r \equiv 1^k \cdot a^r \equiv a^r \pmod p$$

3. 得出结论（降幂公式）
经过上面的推导，我们证明了：
$$a^X \equiv a^{X \pmod{p-1}} \pmod p$$

也就是说：在底数对 $p$ 取模的运算中，如果 $p$ 是质数，那么它的指数可以每 $(p-1)$ 作为一个循环节砍掉。这就叫“降幂”。

对应到这道题：你要算 $a^{b^c} \pmod{10^9+7}$。你就可以先算余数 $r = b^c \pmod{10^9+6}$。然后再算 $a^r \pmod{10^9+7}$。

---

进阶注意（ICPC 数学选手必读）：

坑点 1：费马小定理的局限性
注意前提：$\gcd(a,p)=1$。如果 $a$ 是 $p$ 的倍数（例如本题中的 $a=0$），费马小定理不适用，直接套公式会导致错误（例如把真实的 $0^{positive}$ 误判为 $0^0$）。因此必须对 $a==0$ 进行特判。

坑点 2：模数不是质数时的处理
当模数 $m$ 不是质数时，应使用欧拉定理（Euler）：$a^{\phi(m)} \equiv 1 \pmod m$（前提 $\gcd(a,m)=1$），此时对指数取模应以 $\phi(m)$ 为周期。若连互质条件不满足，则需使用更复杂的“扩展欧拉/无限降幂”技巧。

总结：现在你应该完全理解为什么对指数取模、为什么模 $10^9+6$、以及何时需要谨慎特判了。
*/


#include <iostream>
using namespace std;
using ll = long long;
const ll p = 1'000'000'007LL;

// 改造后的快速幂：计算 (base^exp) % mod
ll qpow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    
    // 【ICPC级边界特判】：如果底数是 0
    if (a == 0) {
        if (b == 0 && c > 0) cout << 1 << "\n"; // b^c = 0^c = 0，所以 a^(b^c) = 0^0 = 1
        else cout << 0 << "\n";                 // 其他情况下 a 的正数次方全是 0
        return;
    }
    
    // 第一步：计算指数对 10^9+6 取模 (费马小定理降幂)
    ll exp = qpow(b, c, p - 1); // 因为 10^9+7 是质数，所以 phi(10^9+7) = 10^9+6
    
    // 第二步：计算底数对 10^9+7 取模
    ll ans = qpow(a, exp, p);
    
    cout << ans << "\n";
}

int main() {
    // 竞程必备 IO 优化
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}


// 依旧recursive
// #include <iostream>
// using namespace std;
// using ll = long long;

// int power(int a, int b, int m) {
//     if (b == 0) return 1 % m;
//     ll p = power(a, b / 2, m);
//     p = p * p % m;
//     if (b % 2 == 1) p = p * a % m;
//     return p;
// }

// int main() {
//     int n;
//     cin >> n;
//     for (int i = 1; i <= n; i++) {
//         int a, b, c;
//         cin >> a >> b >> c;
//         cout << power(a, power(b, c, 1e9 + 6), 1e9 + 7) << "\n";
//     }
// }