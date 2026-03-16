// 08_inclusion_exclusion.cpp
// 题目：统计 1..n 中被至少一个给定质数整除的数的个数（容斥原理）
// 以下为题解说明 + 竞赛级安全实现（防溢出）

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
            if (set_bits % 2 == 1) ans += count; else ans -= count;
        }
    }

    cout << ans << '\n';
    return 0;
}
