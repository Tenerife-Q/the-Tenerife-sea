/*
 * ==============================================================================
 * CSES Problem Set - Next Prime
 * Category: Mathematics
 * 
 * 【题目描述 / Problem Description】
 * 给定一个正整数 n，找到严格大于 n 的最小素数。
 * Given a positive integer n, find the next prime number after it.
 * 
 * 【输入 / Input】
 * 第一行包含一个整数 t：测试用例的数量。
 * 随后 t 行，每行包含一个正整数 n。
 * The first line has an integer t: the number of tests.
 * After that, each line has a positive integer n.
 * 
 * 【输出 / Output】
 * 对于每个测试用例，打印出 n 之后的下一个素数。
 * For each test, print the next prime after n.
 * 
 * 【数据范围 / Constraints】
 * 1 <= t <= 20
 * 1 <= n <= 10^12
 * 
 * 【时间 & 空间限制 / Limits】
 * Time limit: 1.00 s
 * Memory limit: 512 MB
 * 
 * 【解题思路 / Solution Idea】
 * 1. 在 10^12 范围内，相邻素数的最大间隙极小（远低于 600）。
 * 2. 所以我们只需要从 n+1 开始向后逐个判断是否为素数，绝大部分非素数会瞬间被淘汰。
 * 3. 判定单个素数采用 O(√n) 的试除法。由于只需处理到 10^6，且所有素数必然满足 6k±1，
 *    我们可以直接跳过 2 和 3 的倍数，步长设为 6，极大降低常数项时间复杂度。
 * ==============================================================================
 */

#include <iostream>

using namespace std;

// 高效判断一个数是否为素数，时间复杂度 O(√n)
bool is_prime(long long n) {
    // 0 和 1 不是素数
    if (n <= 1) return false;
    // 2 和 3 是素数
    if (n <= 3) return true;
    
    // 排除掉所有 2 和 3 的倍数
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // 6k±1 优化：从 5 开始，每次步长进 6 (即判断 5, 7, 11, 13...)
    // 条件 i*i <= n 可以避免使用 sqrt() 带来的浮点数精度问题和性能损耗
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

void solve() {
    long long n;
    cin >> n;
    
    // 题目要求 finding the next prime after it，即严格大于 n
    long long p = n + 1;
    
    // 不断向后寻找，直到遇到素数
    while (!is_prime(p)) {
        p++;
    }
    
    cout << p << "\n";
}

int main() {
    // 优化标准 C++ 的 I/O 速度，防止在读写大量数据时超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}