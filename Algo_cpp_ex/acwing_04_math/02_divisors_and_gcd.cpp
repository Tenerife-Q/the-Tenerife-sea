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

vector<int> get_divisors(int n) {
    vector<int> res;
    for(int i = 1; i <= n / i; i++) {
        if(n % i == 0) {
            res.push_back(i);
            if(i != n / i) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

// ==========================================
// 2. 算术基本定理推论 - 约数个数与约数之和
// 理论基础: 算术基本定理
// 任何一个大于 1 的正整数 N 都可以唯一分解为有限个质数的乘积:
// N = p1^a1 * p2^a2 * ... * pk^ak
//
// 推论 1: 约数个数
// N 的任意一个约数 d，其质因子分解形式必定为:
// d = p1^b1 * p2^b2 * ... * pk^bk
// 其中 0 <= bi <= ai
// 对于 p1，指数 b1 有 (0 ~ a1) 共 a1+1 种取法
// 对于 p2，指数 b2 有 (0 ~ a2) 共 a2+1 种取法
// ...
// 乘法原理：约数总个数 = (a1+1) * (a2+1) * ... * (ak+1)
//
// 推论 2: 约数之和
// N 的所有约数之和 = (p1^0 + p1^1 + ... + p1^a1) * (p2^0 + p2^1 + ... + p2^a2) * ... * (pk^0 + ... + pk^ak)
// 证明：将上式展开，每一项都是 p1^b1 * p2^b2 * ... * pk^bk 的形式，且完全覆盖了所有可能的约数组合。

long long get_divisors_count(int n) {
    if (n == 1) return 1;
    // 使用哈希表存储质因子及其指数
    unordered_map<int, int> primes;
    
    // 试除法分解质因数
    for (int i = 2; i <= n / i; i++) {
        while (n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if (n > 1) primes[n]++;

    long long res = 1;
    for (auto p : primes) {
        // p.second 是指数 ai
        // 公式：res = (a1+1) * (a2+1) * ...
        res = res * (p.second + 1) % mod;
    }
    return res;
}

// 约数之和计算
long long get_divisors_sum(int n) {
    if (n == 1) return 1;
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
        // 计算等比数列求和: t = (a^0 + a^1 + ... + a^b)
        // 方法 1: 秦九韶算法思想 (这种写法很巧妙，避免了多次快速幂)
        // t = 1
        // t = t * a + 1 -> a + 1
        // t = t * a + 1 -> a^2 + a + 1
        long long t = 1;
        while (b--) t = (t * a + 1) % mod;
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
    // 强制使用 UTF-8 输出以避免乱码 (Windows PowerShell)
    system("chcp 65001");
    
    int n = 36;
    vector<int> divs = get_divisors(n);
    cout << n << " 的所有约数是: ";
    for (int x : divs) cout << x << " ";
    cout << endl;

    // 因为 get_divisors_count 内部重新计算了质因数，所以这里我们必须传入一个新的 map 或者在函数内部新建
    // 当前实现是在函数内部新建局部 map，所以直接调用即可。
    cout << n << " 的约数个数: " << get_divisors_count(n) << " 约数之和: " << get_divisors_sum(n) << endl;

    cout << "gcd(18, 24) = " << gcd(18, 24) << endl;

    return 0;
}
