/*
Prime Multiples — CSES (plain text)

Problem (English):
Given k distinct prime numbers a1, a2, ..., ak and an integer n, count how many
integers between 1 and n (inclusive) are divisible by at least one of the given primes.

Input:
First line: two integers n and k.
Second line: k primes a1 a2 ... ak.

Output:
One integer: the number of integers in 1..n divisible by at least one given prime.

Key constraints:
- n ≤ 10^18 (watch out for 64-bit multiplication overflow).
- k ≤ 20 (enumeration over subsets with O(2^k) is feasible).

Example:
Input:
20 2
2 5
Output:
12

Implementation notes (engineering highlights):
- Use the inclusion–exclusion principle: sum floor(n / product(S)) over all non-empty
    subsets S, with sign + for odd |S| and - for even |S|.
- Enumerate subsets with bitmasks from 1 to (1<<k)-1; use __builtin_popcount(mask)
    to get the parity of |S|.
- To avoid overflow when computing product(S), use a division guard: before doing
    current_prod *= p, check if (n / current_prod < p). If true, the product would
    exceed n (or overflow), so the subset contributes 0 and can be skipped.

中文说明（纯文本）：
题目：约数倍数（CSES）
给定 k 个互不相同的质数 a1,a2,...,ak 和整数 n，计算 1..n 范围内至少被其中一个质数整除的整数个数。

输入：第一行 n 和 k；第二行 k 个质数。
输出：一个整数，为满足条件的个数。

要点：n 可达 10^18，需防止 long long 乘法溢出；k ≤ 20，适合枚举子集。

实现提示：使用容斥原理与二进制状态压缩，计算每个子集的贡献时用除法守卫
(if (n / current_prod < p) 则跳过) 来避免溢出并进行剪枝。

*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 开启极速 I/O，竞赛基本素养
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    int k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> primes(k);
    for (int i = 0; i < k; ++i) {
        cin >> primes[i];
    }

    long long ans = 0;

    // 二进制状态压缩：从 1 枚举到 2^k - 1 (包含了所有非空子集)
    int total_masks = 1 << k;
    for (int mask = 1; mask < total_masks; ++mask) {
        long long current_prod = 1; // 记录当前子集的质数乘积
        bool overflow = false;      // 溢出标记

        // __builtin_popcount 计算二进制中有多少个 1，即当前子集选了几个质数
        int set_bits = __builtin_popcount(mask);

        // 遍历当前状态 mask 下，选中了哪些质数
        for (int i = 0; i < k; ++i) {
            if ((mask >> i) & 1) {
                // 【除法守卫】避免 current_prod * primes[i] 溢出
                if (current_prod > 0 && n / current_prod < primes[i]) {
                    overflow = true;
                    break; // 一旦乘上去必然 > n，对答案贡献为 0
                }
                current_prod *= primes[i];
            }
        }

        if (!overflow) {
            long long count = n / current_prod; // 当前子集的倍数个数
            if (set_bits % 2 == 1) ans += count; 
            else ans -= count;
        }
    }

    cout << ans << '\n';
    return 0;
}


#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ll n;
    int k;
    cin >> n >> k;

    vector<ll> primes(k);
    for (int i = 0; i < k; i++) {
        cin >> primes[i];
    }

    ll answer = 0;
    for (int b = 1; b < (1 << k); b++) {
        ll prod = 1;
        bool fail = false;

        for (int i = 0; i < k; i++) {
            if (b & (1 << i)) {
                if (primes[i] > n / prod) fail = true;
                prod *= primes[i];
            }
        }

        if (fail) continue;

        ll add = n / prod;
        if (__builtin_parity(b) == 0) add = -add;
        answer += add;
    }

    cout << answer << "\n";
}