/*
Bracket Sequences I  /  括号序列 I

Task:
Your task is to calculate the number of valid bracket sequences of length n.
当 n=6 时，序列数为 5，例如：
()()()
()(())
(())()
((()))
(()())

Time limit: 1.00 s
Memory limit: 512 MB

Input:
The only input line has an integer n.
输入: 单行整数 n。

Output:
Print the number of sequences modulo 10^9+7.
输出: 对 10^9+7 取模的答案。

Constraints:
1 <= n <= 10^6

Example:
Input:
6

Output:
5

*/

// #include <iostream>

// using namespace std;

// // 定义题目要求的模数
// const int MOD = 1000000007;

// // 快速幂算法：计算 (base^exp) % MOD
// // 用于求模逆元
// long long modPow(long long base, long long exp) {
//     long long res = 1;
//     base %= MOD;
//     while (exp > 0) {
//         if (exp % 2 == 1) res = (res * base) % MOD;
//         base = (base * base) % MOD;
//         exp /= 2;
//     }
//     return res;
// }

// // 利用费马小定理求逆元：a^(-1) ≡ a^(p-2) (mod p)
// long long modInverse(long long n) {
//     return modPow(n, MOD - 2);
// }

// int main() {
//     // 优化标准输入输出流，提升运行速度
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n;
//     // 如果没有输入直接返回
//     if (!(cin >> n)) return 0;

//     // 奇数长度不可能构成匹配的括号序列（左右括号数量无法相等）
//     if (n % 2 != 0) {
//         cout << 0 << "\n";
//         return 0;
//     }

//     // k 是左括号和右括号各自的数量
//     int k = n / 2;

//     long long fact_2k = 1;  // 用于保存 (2k)!
//     long long fact_k = 1;   // 用于保存 k!
//     long long fact_k1 = 1;  // 用于保存 (k+1)!

//     // 一次循环同时计算出所需的三个阶乘结果并取模
//     for (int i = 1; i <= n; i++) {
//         fact_2k = (fact_2k * i) % MOD;
//         if (i == k) {
//             fact_k = fact_2k;
//         }
//         if (i == k + 1) {
//             fact_k1 = fact_2k;
//         }
//     }

//     // 卡特兰数公式：C_k = (2k)! / ( k! * (k+1)! )
//     // 在模运算下，除法等于乘以分母的逆元
    
//     // 1. 计算分母：k! * (k+1)!
//     long long denominator = (fact_k * fact_k1) % MOD;

//     // 2. 计算最终结果：分子 * 分母的逆元 % MOD
//     long long ans = (fact_2k * modInverse(denominator)) % MOD;

//     // 输出结果
//     cout << ans << "\n";

//     return 0;
// }


// 标答虽然最简 但是我认为还是上面有助于公式推导与理解
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    ll res = 1;
    a %= M;
    while (b > 0) {
        if (b & 1) res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res;
}

ll modInverse(ll a) {
    return power(a, M - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    if (n % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }

    int k = n / 2;
    ll fact_n = 1;
    ll fact_k = 1;

    for (int i = 1; i <= n; i++) {
        fact_n = (fact_n * i) % M;
        if (i == k) {
            fact_k = fact_n;
        }
    }

    ll fm = (fact_k * fact_k) % M;
    fm = (fm * (n + 2)) % M;

    ll fz = 2 * fact_n % M;
    ll ans = (fz * modInverse(fm)) % M;
    cout << ans << "\n";
}