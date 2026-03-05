/**
 * 模块：第四讲 数学知识
 * 主题：基础数论 - 约数、公约数 (Divisors & GCD)
 * ICPC 考点：求解所有约数，最大公约数 (GCD) 是欧拉定理、贝祖等式的前置。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int mod = 1e9 + 7;

// ==========================================
// 1. 试除法求一个数的所有约数 - O(sqrt(n) + sqrt(n)*log(sqrt(n)))
// 配合容斥原理、多重背包常常用到
vector<int> get_divisors(int n) {
    vector<int> res;
    for (int i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            res.push_back(i);
            // 要注意平方数的处理，比如 n = 36 时，i = 6 时只需存一次
            if (i != n / i) res.push_back(n / i);
        }
    }
    // 排序后约数是有序的
    sort(res.begin(), res.end());
    return res;
}

// ==========================================
// 2. 算术基本定理推论 - 约数个数与约数之和
// 假设 n = p1^a1 * p2^a2 * ... * pk^ak
// 约数个数： (a1+1) * (a2+1) * ... * (ak+1)
// 约数之和： (p1^0 + p1^1 + ... + p1^a1) * ... * (pk^0 + pk^1 + ... + pk^ak)
// 应用：求 N! 中质因数个数
long long get_divisors_count(int n) {
    unordered_map<int, int> primes;
    for (int i = 2; i <= n / i; i++) {
        while (n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if (n > 1) primes[n]++;

    long long res = 1;
    for (auto p : primes) res = res * (p.second + 1) % mod;
    return res;
}

// 约数之和计算
// (p^0 + p^1 + ... + p^c) 计算
long long get_divisors_sum(int n) {
    unordered_map<int, int> primes;
    for (int i = 2; i <= n / i; i++) {
        while (n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if (n > 1) primes[n]++;

    long long res = 1;
    for (auto p : primes) {
        int a = p.first, b = p.second;
        long long t = 1;  // 开始计算 p^0 + p^1 + ... + p^b
        while (b--) t = (t * a + 1) % mod; // 利用秦九韶算法思想，等价于 (t*a)+1 -> a^2+a+1 -> a^3+a^2+a+1
        res = res * t % mod;
    }
    return res;
}

// ==========================================
// 3. 最大公约数 (GCD) - 欧几里得算法辗转相除法
// Cryptography: 用于计算模逆的前置与两数互质鉴定。
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// C++17 自带 std::gcd 和 std::lcm (<numeric> 库)

int main() {
    int n = 36;
    vector<int> divs = get_divisors(n);
    cout << n << " 的所有约数是: ";
    for (int x : divs) cout << x << " ";
    cout << endl;

    cout << n << " 的约数个数: " << get_divisors_count(n) << " 约数之和: " << get_divisors_sum(n) << endl;

    cout << "gcd(18, 24) = " << gcd(18, 24) << endl;

    return 0;
}
