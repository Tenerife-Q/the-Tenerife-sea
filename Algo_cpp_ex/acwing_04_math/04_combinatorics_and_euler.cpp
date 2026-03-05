/**
 * 模块：第四讲 数学知识
 * 主题：组合数学与欧拉函数 (Combinatorics & Euler's Function)
 * ICPC 核心考点：快速计算组合数 $C_a^b \pmod p$、容斥原理以及与互质相关的计数。
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int mod = 1e9 + 7;

// ==========================================
// 1. 求单个数的欧拉函数 Euler's Totient Function \phi(N)
// 定义：1~N 中与 N 互质的数的个数。
// 公式：\phi(N) = N \times (1 - 1/p1) \times (1 - 1/p2) \dots (1 - 1/pk)
// 结论：欧拉函数是积性函数；若 $a, n$ 互质，欧拉定理知 $a^{\phi(n)} \equiv 1 \pmod n$。
int phi(int n) {
    int res = n;
    // 类似于分解质因数
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            // (1 - 1/p) = (p - 1) / p
            res = res / i * (i - 1); // 保证先除再乘不损失精度
            while (n % i == 0) n /= i;
        }
    }
    // 最后如果还有一个大于 sqrt(n) 的质因数
    if (n > 1) res = res / n * (n - 1);
    return res;
}

// 线性筛法求 1~N 阶的欧拉函数
// O(N) 预处理，适合多组询问或前缀和查询。
const int N = 100010;
int primes[N], cnt;
bool st[N];
int euler[N]; // euler[i] 表示 \phi(i)

void get_eulers(int n) {
    euler[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            euler[i] = i - 1; // 质数 i 的欧拉函数是 i - 1
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) {
                // p[j] 是 i 的最小质因子，所以 i 包含了 p[j] 所有质因子。
                // $\phi(p_j * i) = \phi(i) * p_j$
                euler[primes[j] * i] = euler[i] * primes[j];
                break;
            }
            // p[j] 和 i 互质（并且 p[j] 是 p[j]*i 的最小质因子）
            // 因为欧拉是积性函数 $\phi(ab) = \phi(a)\phi(b)$ 且 a, b 互质。
            // 故 $\phi(p_j * i) = \phi(i) * \phi(p_j) = \phi(i) * (p_j - 1)$
            euler[primes[j] * i] = euler[i] * (primes[j] - 1);
        }
    }
}

// ==========================================
// 2. 组合数计算 (Combinatorics Calculation)
// 求 $C_a^b \pmod p$ 的三种常用计算方式

// 类型 I： $a,b \le 2000$ (数据范围较小)，适用于频繁的预处理查询 O(N^2)
int c[2010][2010]; 
void init_C() {
    for (int i = 0; i <= 2000; i++) {
        for (int j = 0; j <= i; j++) {
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
}

// 类型 II： $a,b \le 10^5$，可以预处理阶乘及其逆元 O(N log p)，查询 O(1)
int fact[N], infact[N]; // 阶乘与阶乘逆元

LL qmi_inv(LL a, LL k, LL p) {
    LL res = 1;
    while (k) {
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

void init_fact() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi_inv(i, mod - 2, mod) % mod;
    }
}

// O(1) 求 C(a, b) = a! / (b! * (a-b)!) % mod
int C(int a, int b) {
    if (a < b || a < 0 || b < 0) return 0;
    return (LL)fact[a] * infact[b] % mod * infact[a - b] % mod;
}

// 卢卡斯定理 (Lucas Theorem)：用于 $a,b \le 10^{18}$ 且质数 $p \le 10^5$
// 在密码系统或极大的离散对数计算经常出现。

int main() {
    cout << "phi(12) = 1 ~ 12 之间互质的个数 = " << phi(12) << endl; 
    // 互质的是 {1, 5, 7, 11} -> 4.

    get_eulers(20);
    cout << "线性筛结果 euler[12] = " << euler[12] << endl;

    init_fact();
    cout << "组合数计算: C(5, 2)  = " << C(5, 2) << endl;

    return 0;
}
