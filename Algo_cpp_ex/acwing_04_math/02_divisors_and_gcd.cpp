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

long long get_divisors_count(int n) {
    if(n == 1) return 1;
    unordered_map<int, int> primes;
    for(int i = 2; i <= n / i; i++) {
        while(n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if(n > 1) primes[n]++;

    long long res = 1;
    for (auto p : primes) {
        res = res * (p.second + 1);
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
        // 目标：计算约数之和公式中该质因子对应的等比数列求和项
        // Sum = (p1^0 + p1^1 + ... + p1^a1) * (p2^0 + p2^1 + ... + p2^a2) * ...
        // 本次循环计算的是其中一项: t = (p^0 + p^1 + ... + p^b)
        // 
        // 传统方法：使用等比数列求和公式 S = (p^(b+1) - 1) / (p - 1)
        // - 缺点：涉及除法运算，在模运算 (mod) 下除法需要求“乘法逆元”，比较麻烦且容易出错。
        //
        // 巧妙方法：秦九韶算法 (Horner's Method) 思想变换
        // 我们可以把多项式 p^b + p^(b-1) + ... + p^1 + 1 改写成层层嵌套的形式：
        // Sum = (...((1 * p + 1) * p + 1) * p + ... + 1)
        // 
        // 流程推导 (例如求 1 + p + p^2 + p^3, 即 b=3)：
        // - 初始 t = 1
        // - 第一次循环 (b=3 -> 2): t = t * p + 1 = p + 1
        // - 第二次循环 (b=2 -> 1): t = t * p + 1 = (p + 1) * p + 1 = p^2 + p + 1
        // - 第三次循环 (b=1 -> 0): t = t * p + 1 = (p^2 + p + 1) * p + 1 = p^3 + p^2 + p + 1
        // 
        // 为什么要 % mod？
        // 1. 现实限制与算法考察重心：
        //    约数之和随着 N 的增大呈现爆炸式增长。例如 N 较大时，其约数之和可能有数百位甚至数千位。
        //    C++ 的 long long (64位) 无法存储这么大的数。
        //    如果不取模，这也题目就会变成考察“高精度大整数运算”的繁琐代码实现，而非考察“数论推导”的核心逻辑。
        //
        // 2. 验证算法正确性 (Hash 思想)：
        //    题目不需要知道那个几千位的天文数字具体是多少，只需要验证你的算法逻辑对不对。
        //    取模相当于保留了该数字的“特征值”或“指纹”。如果你的算法逻辑正确，算出的余数一定是一样的。
        //
        // 3. 模运算性质：
        //    (A + B) % M = ((A % M) + (B % M)) % M
        //    (A * B) % M = ((A % M) * (B % M)) % M
        //    我们在每一步迭代中都取模，保证中间结果 t 始终在 [0, mod-1] 范围内，从而避免了溢出，且保证最终结果符合模运算规则。
        long long t = 1;
        while (b--) t = (t * a + 1) % mod;
        res = res * t % mod;
    }
    return res;
}

long long get_divisors_sum(int n) {
    if(n == 1) return 1;
    unordered_map<int, int> primes;
    for(int i = 2; i <= n / i; i++) {
        while(n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if(n > 1) primes[n]++;

    long long res = 1;
    for(auto p : primes) {
        int a = p.first, b = p.second;
        long long t = 1;
        while(b--) t = t * a + 1;
        res = res * t;
    }
    return res;
}

// ==========================================
// 3. 最大公约数 (GCD) - 欧几里得算法 (Euclidean Algorithm) 辗转相除法
// 
// 核心原理 (GCD 递归定理): gcd(a, b) = gcd(b, a % b)
// 证明:
// 设 a > b，且 a = k * b + r，其中 r = a % b。
// 假设 d 是 a 和 b 的任意公约数，即 d|a 且 d|b。
// 由于 r = a - k * b，如果 d 整除 a 和 b，那么 d 必整除 (a - k*b)，即 d|r。
// 反之，如果 d 是 b 和 r 的公约数，即 d|b 且 d|r，由于 a = k * b + r，则 d 必整除 a。
// 结论：a 和 b 的公约数集合，与 b 和 r 的公约数集合是完全相同的。
// 因此它们的最大公约数也必然相同。不断递归，直到 r=0，此时 b 即为 GCD。
int gcd(int a, int b) {
    // 终止条件：当 b 为 0 时，a 就是最大公约数（因为任何非零整数都是 0 的约数）
    // 递归步骤：gcd(a, b) = gcd(b, a % b)
    // 模拟演示：gcd(24, 18) -> gcd(18, 6) -> gcd(6, 0) -> 返回 6
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
