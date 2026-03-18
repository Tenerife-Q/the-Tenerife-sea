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

/*
 * ==============================================================================
 * CSES Problem Set - Next Prime
 * Category: Mathematics
 * 
 * 【核心原理解析 / Core Analysis】
 * 
 * 1. 为什么最外层寻找下一个素数的 while 循环不会超时？（素数间隙理论）
 *    根据素数定理 (Prime Number Theorem)，质数分布 π(n) ≈ n / log(n)。
 *    在 1 到 10^12 如此庞大的范围内，相邻两个素数之间的“最大间隙 (Prime Gap)”仅为 540。
 *    (发生在 738,832,927,927 和 738,832,928,467 之间)
 *    这意味着：哪怕你运气最差，从 n 开始往后找，最多只需做 540 次判断必定能遇到素数！
 * 
 * 2. 判断单个数是否为素数，为什么能这么快？（轮式因子分解 / Wheel Factorization）
 *    - 基础试除法：for (i = 2; i <= sqrt(n); i++)，时间复杂度 O(√n)。
 *    
 *    - 【官方标答思路】：“周长为 2 的轮子”
 *      既然除了 2 以外的素数全是奇数，我们一开始就排除偶数 (n % 2 == 0)。
 *      后续试除只从 3 开始，每次测试奇数即可 (i += 2)。
 *      运算量变为原来的 1/2。
 *    
 *    - 【进阶极致优化】：“周长为 6 的轮子” (即 6k±1 理论)
 *      任何自然数除以 6 的余数只可能是 0,1,2,3,4,5。
 *      其中 6k, 6k+2, 6k+3, 6k+4 全是 2 或 3 的倍数。
 *      所以不能被 2 和 3 整除的数，必定只能是 6k-1 或 6k+1 (即 i 和 i+2)。
 *      我们一开始排除 2 和 3，后续步长直接设为 6 (i += 6)。
 *      运算量变为原来的 1/3，常数极小，运行飞快！
 * 
 * ==============================================================================
 */

#include <iostream>

using namespace std;
using ll = long long;

// ==============================================================================
// 【方法一：官方标答解法】（已注释，供学习对比参考）
// 逻辑：只踢掉 2 的倍数，步长为 2 (3, 5, 7, 9, 11...)
// ==============================================================================
/*
bool is_prime_official(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    
    // 排除所有的偶数
    if (n % 2 == 0) return false;
    
    // 从 3 开始，只测奇数，步长为 2
    for (ll x = 3; x * x <= n; x += 2) {
        if (n % x == 0) return false;
    }
    return true;
}
*/

// ==============================================================================
// 【方法二：进阶极致优化】（当前使用的正解）
// 逻辑：同时踢掉 2 和 3 的倍数，步长为 6 (5, 7, 11, 13, 17...)
// ==============================================================================
bool is_prime_optimized(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true; // 处理 2 和 3
    
    // 瞬间排除所有 2 的倍数和 3 的倍数
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // 使用 6k±1 优化，步长进 6
    // i*i <= n 代替 sqrt(n)，避免浮点数精度丢失及额外耗时
    for (ll i = 5; i * i <= n; i += 6) {
        // i 是 6k-1, i+2 是 6k+1
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;
    
    // 题目要求 finding the next prime after it，即严格大于 n
    n++;
    
    // 不断向后寻找，最大不会循环超过 540 次
    while (!is_prime_optimized(n)) {
        n++;
    }
    
    cout << n << "\n";
}

int main() {
    // 优化 C++ 标准 I/O 速度（竞技编程必备）
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    // 读取测试用例数量
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}