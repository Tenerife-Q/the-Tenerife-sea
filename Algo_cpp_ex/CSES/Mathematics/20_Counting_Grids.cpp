// 20 Counting Grids
// 20 计数网格
//
// Time limit: 1.00 s
// Memory limit: 512 MB
//
// Task:
// Your task is to count the number of different n x n grids whose each square is
// black or white. Two grids are considered to be different if it is not possible
// to rotate one of them so that they look the same.
//
// 任务：
// 计算所有 n x n 网格的不同配色数，每个格子为黑或白。
// 如果无法通过旋转使两个网格重合，则视为不同。
//
// Input / 输入：
// The only input line has an integer n: the size of the grid.
// 输入仅一行，包含一个整数 n，表示网格的尺寸。
//
// Output / 输出：
// Print one integer: the number of grids modulo 10^9+7.
// 输出一个整数：不同网格的数量，对 10^9+7 取模。
//
// Constraints / 约束：
// 1 <= n <= 10^9
// 1 <= n <= 10^9
//
// Example / 示例：
// Input:
// 4
//
// Output:
// 16456
//
// Note (方法提示)：
// The counting is done modulo 1e9+7 and requires considering grid symmetries
// under rotations (0, 90, 180, 270 degrees). Burnside's lemma (orbit-counting)
// can be applied to count distinct grids by averaging the number of colorings
// fixed by each rotation. (No implementation provided here — this file contains
// only the bilingual problem statement comment.)
//

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

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    // 因为 n 最大是 10^9，n * n 最大是 10^18
    // 必须用 long long，不会溢出（long long 上限是 9.22 * 10^18）
    long long n2 = n * n;

    // 严格按照推导，计算出四种旋转下各自被分成的“组数”（即指数部分）
    long long e0 = n2;
    long long e180 = (n2 + 1) / 2;
    long long e90 = (n2 + 3) / 4;
    long long e270 = e90; // 270度与90度完全对称

    // 将四种情况保持不变的方案数相加，边加边取模
    long long sum = 0;
    
    sum = (sum + power(2, e0)) % MOD;
    sum = (sum + power(2, e180)) % MOD;
    sum = (sum + power(2, e90)) % MOD;
    sum = (sum + power(2, e270)) % MOD;

    // 最后的总和除以 4，等价于乘以 4 在模 10^9+7 下的乘法逆元：power(4, MOD - 2)
    long long ans = (sum * power(4, MOD - 2)) % MOD;

    cout << ans << "\n";

    return 0;
}





#include <iostream>
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    ll n2 = n * n;

    ll e0 = n2;
    ll e180 = (n2 + 1) / 2;
    ll e90 = (n2 + 3) / 4;
    ll e270 = e90;

    ll sum = 0;
    sum = (sum + power(2, e0)) % M;
    sum = (sum + power(2, e180)) % M;
    sum = (sum + power(2, e90)) % M;
    sum = (sum + power(2, e270)) % M;

    ll ans = (sum * power(4, M - 2)) % M;
    cout << ans << "\n";
    return 0;

}