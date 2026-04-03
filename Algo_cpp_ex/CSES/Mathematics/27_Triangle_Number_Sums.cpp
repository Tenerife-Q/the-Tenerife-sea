/**
 * ============================================================================
 * CSES - Triangle Number Sums
 * ============================================================================
 * 
 * [ENGLISH VERSION]
 * ─────────────────
 * Time limit: 1.00 s
 * Memory limit: 512 MB
 * 
 * A triangle number is a positive integer of the form 1+2+...+k. 
 * The first triangle numbers are 1, 3, 6, 10 and 15.
 * 
 * Every positive integer can be represented as a sum of triangle numbers.
 * For example, 42=21+21 and 1337=1326+10+1.
 * 
 * Given a positive integer n, determine the smallest number of triangle 
 * numbers that sum to n.
 * 
 * Input:
 *   - First line: integer t (number of tests)
 *   - Next t lines: each contains a positive integer n
 * 
 * Output:
 *   For each test, print the smallest number of triangle numbers.
 * 
 * Constraints:
 *   - 1 ≤ t ≤ 100
 *   - 1 ≤ n ≤ 10^12
 * 
 * Example:
 *   Input:  5, 1, 2, 3, 42, 1337
 *   Output: 1, 2, 1, 2, 3
 * 
 * ─────────────────────────────────────────────────────────────────────────
 * 
 * [中文版本]
 * ─────────
 * 时间限制: 1.00 秒
 * 内存限制: 512 MB
 * 
 * 三角形数（Triangle Number）是形如 1+2+...+k 的正整数。
 * 最初的几个三角形数是 1, 3, 6, 10, 15。
 * 
 * 每个正整数都可以表示为多个三角形数的和。
 * 例如，42=21+21，1337=1326+10+1。
 * 
 * 给定正整数 n，求最少需要多少个三角形数相加得到 n。
 * 
 * 输入：
 *   - 第一行：整数 t（测试用例数）
 *   - 接下来 t 行：每行一个正整数 n
 * 
 * 输出：
 *   对于每个测试用例，输出最少需要的三角形数个数。
 * 
 * 约束：
 *   - 1 ≤ t ≤ 100
 *   - 1 ≤ n ≤ 10^12
 * 
 * 样例：
 *   输入：5, 1, 2, 3, 42, 1337
 *   输出：1, 2, 1, 2, 3
 * 
 * ============================================================================
 * 
 * [MATHEMATICAL INSIGHT]
 * 数学原理：
 * 
 * 三角形数定义：T_k = k(k+1)/2 = 1+2+...+k
 * 
 * 关键事实：任何正整数最多可以表示为 3 个三角形数的和
 * （由 Legendre 定理推广证明）
 * 
 * 判断 n 是否为三角形数的方法：
 *   n 是三角形数 ⟺ 8n+1 是完全平方数
 * 
 * 解题思路：
 *   1. 检验 n 本身是否为三角形数 → 答案为 1
 *   2. 枚举所有三角形数，检验能否作为分解中的一个 → 答案为 2
 *   3. 若前两步都不成立，根据定理答案为 3
 * 
 * ============================================================================
 */

#include<bits/stdc++.h>
using namespace std;

// Check if a number is a perfect square
bool isPerfectSquare(long long n) {
    if (n < 0) return false;
    long long sr = sqrt(n);
    // Check sr and sr±1 due to floating point precision
    return sr * sr == n || (sr + 1) * (sr + 1) == n;
}

// Check if n is a triangle number
// Triangle number T_k = k(k+1)/2
// To check: 8n + 1 should be a perfect square
// Because if k(k+1)/2 = n, then k^2 + k - 2n = 0
// k = (-1 + sqrt(1 + 8n)) / 2, so 8n + 1 must be perfect square
bool isTriangleNumber(long long n) {
    return isPerfectSquare(8 * n + 1);
}

// Find minimum number of triangle numbers that sum to n
int countMinTriangleNumbers(long long n) {
    // Case 1: n itself is a triangle number
    if (isTriangleNumber(n)) {
        return 1;
    }
    
    // Case 2: n can be represented as sum of 2 triangle numbers
    // Check all triangle numbers up to n
    for (long long k = 1; k * (k + 1) / 2 <= n; k++) {
        long long triangleK = k * (k + 1) / 2;
        if (isTriangleNumber(n - triangleK)) {
            return 2;
        }
    }
    
    // Case 3: By Legendre's theorem (generalized), every positive integer
    // can be represented as sum of at most 3 triangle numbers
    // If not 1 or 2, then it must be 3
    return 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        long long n;
        cin >> n;
        cout << countMinTriangleNumbers(n) << "\n";
    }
    
    return 0;
}
