/*
题目：Sum of Divisors

描述（中）：令 σ(i) 表示整数 i 的所有正约数之和。例如 σ(12)=1+2+3+4+6+12=28。
给定 n，计算 S = sum_{i=1..n} σ(i) 和之前求一个数的所有约数之和的题目不同，这里是求 1 到 n 中每个数的约数之和的总和。
S = ∑_{i=1}^n σ(i) 
并输出 S mod 1e9+7。

Description (EN): Let σ(n) denote the sum of divisors of n. Given n, compute
S = \sum_{i=1}^n σ(i) modulo 10^9+7.

输入 (Input):
 - 单行一个整数 n。

输出 (Output):
 - 输出 \sum_{i=1}^n σ(i) modulo 10^9+7。

约束 (Constraints):
 - 1 ≤ n ≤ 10^12

示例 (Example):
输入:
5

输出:
21

提示：本题的关键是整除分块（quotient block / number theoretic block），能将复杂度降到 O(√n)。参见文件下方实现与注释。
*/

#include <iostream>

using namespace std;
using ll = long long;

// 常量定义
const ll M = 1000000007;     // 模数
const ll INV2 = 500000004;   // 2的模逆元，计算 (a/2 % M) 时使用 (a * INV2 % M)

/* =========================================================================
   🐢 SOLUTION 1: 线性遍历法 (暴力法)
   复杂度: O(N)
   状态: 已注释 (对于 10^12 会超时)
   -------------------------------------------------------------------------
int main_solution_1() {
    ll n;
    cin >> n;
    ll s = 0;
    for (ll k = 1; k <= n; k++) {
        // 直接计算每个约数 k 的贡献
        ll count = (n / k) % M;
        ll value = k % M;
        s = (s + (count * value) % M) % M;
    }
    cout << s << endl;
    return 0;
}
========================================================================= */

// 辅助函数：计算等差数列 [a, b] 的和：(a + b) * (b - a + 1) / 2
ll sum_range(ll a, ll b) {
    ll first_plus_last = (a + b) % M;       // (首项 + 末项)
    ll count = (b - a + 1) % M;             // 项数
    // 这里的 INV2 相当于 / 2
    return first_plus_last * count % M * INV2 % M;
}

/**
 * 🚀 SOLUTION 2: 根号分治 (整除分块优化)
 * 复杂度: O(sqrt(N))
 * 逻辑：将计算分为“小约数单独算”和“大约数按出现次数打包算”
 */
int main() {
    // 提升 I/O 效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    if (!(cin >> n)) return 0;

    ll total_sum = 0;

    // --- 第一部分：处理小约数 (k <= sqrt(n)) ---
    // 这里的 k 是约数本身。因为 sqrt(10^12) = 10^6，循环量很小。
    for (ll k = 1; k * k <= n; k++) {
        ll count = (n / k) % M;  // 约数 k 出现的次数
        ll value = k % M;        // 约数本身的值
        total_sum = (total_sum + (count * value) % M) % M;
    }

    // --- 第二部分：处理大约数 (打包计算) ---
    // 重点：这里的 k 代表“出现的次数”！
    // 我们寻找“哪些约数刚好出现了 k 次”，它们构成一个等差数列 [L, R]。
    for (ll k = 1; n / k > k; k++) {
        // R: 出现 k 次的最大约数是谁？
        ll R = n / k; 
        
        // L: 出现 k 次的最小约数是谁？
        // 逻辑：找出现 k+1 次的最大约数，然后 +1
        ll L = n / (k + 1) + 1; 

        // 举例：n=100, k=1时：
        // R = 100 / 1 = 100
        // L = 100 / (1+1) + 1 = 51
        // 说明 51~100 这些约数在 1~100 中都只出现了 1 次。

        // 计算这个区间内所有约数的总和
        ll block_sum = sum_range(L, R);
        
        // 这一坨约数每个都出现了 k 次
        ll contribution = (block_sum * (k % M)) % M;
        
        total_sum = (total_sum + contribution) % M;
    }

    cout << total_sum << "\n";

    return 0;
}