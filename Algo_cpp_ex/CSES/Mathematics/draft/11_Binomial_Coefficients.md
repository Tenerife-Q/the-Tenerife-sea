# CSES - Binomial Coefficients

## 题目描述 (Problem Description)
给定 $n$ 次查询（$n \le 10^5$），每次给定整数 $a$ 和 $b$（$0 \le b \le a \le 10^6$），要求计算并输出组合数 $C(a, b) \pmod{10^9+7}$ 的值。

## 数学原理与推导 (Mathematical Principles)

### 1. 组合数基础定义
二项式系数（组合数）的代数定义为：
$$ C(a, b) = \binom{a}{b} = \frac{a!}{b!(a-b)!} $$

由于涉及巨大的阶乘运算以及最终需要对 $10^9+7$（一个质数，我们设为 $P$）取模，我们**绝不能直接计算出具体的阶乘数值再做实数除法**。
而在同余算术中，除以一个数等价于乘以该数的**乘法逆元 (Modular Multiplicative Inverse)**。

### 2. 费马小定理与乘法逆元
因为 $P = 10^9+7$ 是质数，根据**费马小定理 (Fermat's Little Theorem)**，对于任意与 $P$ 互质的数 $x$，有：
$$ x^{P-1} \equiv 1 \pmod P $$
两边同乘 $x^{-1}$，我们得到乘法逆元的计算公式：
$$ x^{-1} \equiv x^{P-2} \pmod P $$

即：我们可以使用**快速幂 (Fast Exponentiation)** 在 $O(\log P)$ 的时间内求出常数对应的逆元。

### 3. $O(N)$ 逆推优化求逆元
本题有 $10^5$ 次查询，最大数字达到 $10^6$。如果我们对每个数单独执行 $O(\log P)$ 快速幂求逆元，计算量约为 $10^6 \times 30$，大概勉强能在1.00s内擦边通过。但我们可以采用 $O(N)$ 线性预处理的方法，将查询时间降至 $O(1)$！

**步骤推导**：
1. 计算前向阶乘：
   $$ \text{fact}[i] = (\text{fact}[i-1] \times i) \pmod P $$
2. 先通过快速幂计算出**最大的那个阶乘的逆元**：
   $$ \text{invFact}[10^6] = (\text{fact}[10^6])^{P-2} \pmod P $$
3. 利用阶乘和逆元的代数共性，**从后往前倒推**其余阶乘的逆元：
   我们知道：
   $$ \frac{1}{(i-1)!} = \frac{1}{i!} \times i $$
   转化为模意义下的乘法：
   $$ \text{invFact}[i-1] = (\text{invFact}[i] \times i) \pmod P $$

通过这个倒退，我们可以省略大量的重复快速幂运算，在完美的线性时间内补全整个逆元数组！

计算组合数的时候只需：
$$ C(a,b) = \text{fact}[a] \times \text{invFact}[b] \times \text{invFact}[a-b] \pmod P $$

## 数据流程演示 (Data Flow Example)

假设 $P = 10^9+7$, 查询 $a=5$, $b=3$:
1. $a = 5$ 时，调取 $\text{fact}[5] = 120$。
2. 调取 $\text{invFact}[3]$ (即 $6^{-1} \pmod P$)。
3. 调取 $\text{invFact}[5-3] = \text{invFact}[2]$ (即 $2^{-1} \pmod P$)。
4. 计算：$120 \times 6^{-1} \times 2^{-1} \pmod P = 10 \pmod P$。
5. 返回 10。

## 最优源代码 (Optimal Source Code)

```cpp
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAX = 1e6;

ll fact[MAX + 1];
ll invFact[MAX + 1];

// 快速幂计算逆元：(base^exp) % MOD
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD; 
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// 线性预处理阶乘与逆元
void precompute() {
    // 1. 正向预处理阶乘
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    // 2. 利用快速幂单独求出最大阶乘的逆元
    invFact[MAX] = power(fact[MAX], MOD - 2);
    
    // 3. 从后往前倒推出所有的阶乘逆元
    for (int i = MAX - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// O(1) 处理单次询问
void solve() {
    int a, b;
    cin >> a >> b;
    
    if (b > a || b < 0) {
        cout << 0 << "\n";
        return;
    }
    
    ll ans = fact[a];
    ans = (ans * invFact[b]) % MOD;
    ans = (ans * invFact[a - b]) % MOD;
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute(); // 全局只需执行一次预处理
    
    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }
    
    return 0;
}
```