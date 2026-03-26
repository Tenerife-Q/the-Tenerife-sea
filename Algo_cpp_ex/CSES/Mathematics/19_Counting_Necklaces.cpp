// 19 Counting Necklaces
// 19 计数项链
//
// Time limit: 1.00 s
// Memory limit: 512 MB
//
// Task:
// Your task is to count the number of different necklaces that consist of n pearls
// and each pearl has m possible colors. Two necklaces are considered to be different
// if it is not possible to rotate one of them so that they look the same.
//
// 任务：
// 给定 n 个珠子和 m 种颜色，计算不同项链的数量。
// 如果无法通过旋转将两个项链重合，则视为不同。
//
// Input / 输入：
// The only input line has two numbers n and m: the number of pearls and colors.
// 输入仅一行，包含两个整数 n 和 m，分别表示珠子数和颜色数。
//
// Output / 输出：
// Print one integer: the number of different necklaces modulo 10^9+7.
// 输出一个整数：不同项链的数量，对 10^9+7 取模。
//
// Constraints / 约束：
// 1 <= n, m <= 10^6
// 1 <= n, m <= 10^6
//
// Example / 示例：
// Input:
// 4 3
//
// Output:
// 24
//
// Note (方法提示)：
// Use Burnside's lemma (orbit-counting theorem):
// number = (1/n) * sum_{k=0..n-1} m^{gcd(n,k)} (mod 1e9+7).
// 使用 Burnside 引理：答案为 (1/n) * sum_{k=0..n-1} m^{gcd(n,k)}，对 1e9+7 取模。


#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;

// 快速幂算法：计算 (base^exp) % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// 求正整数 x 的欧拉函数 Φ(x)
long long get_phi(long long x) {
    long long res = x;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            // 将质因子 i 除干净
            while (x % i == 0) x /= i;
            // 欧拉函数公式推导：res = res * (1 - 1/i)
            res -= res / i;
        }
    }
    if (x > 1) res -= res / x;
    return res;
}

int main() {
    // 优化标准输入输出流，加快执行速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, m;
    if (!(cin >> n >> m)) return 0;

    long long ans = 0;
    
    // 枚举 n 的所有约数 d (只需枚举到 sqrt(n))
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            long long d1 = i;
            // 累加 d1 对应的部分：Φ(n/d1) * m^d1
            ans = (ans + get_phi(n / d1) % MOD * power(m, d1)) % MOD;
            
            long long d2 = n / i;
            // 如果 d1 和 d2 不相等（避免完全平方数时重复计算）
            if (d1 != d2) {
                // 累加 d2 对应的部分：Φ(n/d2) * m^d2
                ans = (ans + get_phi(n / d2) % MOD * power(m, d2)) % MOD;
            }
        }
    }

    // 最后除以 n，等价于乘以 n 的逆元 (n^(MOD-2) % MOD)
    ans = (ans * power(n, MOD - 2)) % MOD;
    
    cout << ans << "\n";
    
    return 0;
}