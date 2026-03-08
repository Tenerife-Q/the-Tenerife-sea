/**
 * 模块：第四讲 数学知识
 * 主题：高阶数论与同余方程 - 密码学的算术基础
 * 包含：快速幂、乘法逆元、扩展欧几里得 (exgcd)
 *
 * 现代密码学算法 (如 RSA, Diffie-Hellman) 完全建立在这三大工具的基础之上：
 * 1. 快速幂求 $a^b \pmod p$ （指数超大）。
 * 2. 扩欧：常用于计算已知模量下的乘法逆元 (即 $ax \equiv 1 \pmod m$ 中的 x)。
 *    当 p 为质数时，还可以用费马小定理（结合快速幂）求逆元。
 */

#include <iostream>

using namespace std;

// ==========================================
// 1. 快速幂 (Fast Exponentiation)
// 核心目标：快速计算 a^k mod p 的结果。
// 时间复杂度：O(log k)
//
// 数学原理 (二进制拆分思想)：
// 任何能够表示为整数的指数 k，都可以用二进制形式唯一表示：
// k = (b_m ... b_1 b_0)_2 = b_0 * 2^0 + b_1 * 2^1 + ... + b_m * 2^m
// 其中 b_i ∈ {0, 1}。
// 
// 因此，a^k 可以转化为：
// a^k = a^(b_0 * 2^0 + b_1 * 2^1 + ... + b_m * 2^m)
//     = a^(b_0 * 2^0) * a^(b_1 * 2^1) * ... * a^(b_m * 2^m)
//
// 观察每一项 a^(2^i)：
// - a^(2^0) = a^1
// - a^(2^1) = (a^1)^2
// - a^(2^2) = (a^2)^2
// - ...
// - a^(2^i) = (a^(2^(i-1)))^2
// 每一项都是前一项的平方。我们只需要不断把底数平方（即反复平方法），就能依次得到 a^1, a^2, a^4, a^8...
//
// 算法流程：
// 该算法其实就是经典的“平方-乘算法”（Square-and-Multiply Algorithm）
// 也可以称为“模重复平方法”（Modular Exponentiation by Repeated Squaring）
// 两者本质上是一样的，只是由于取模操作的存在，每一次乘法后都要 % p。
//
// 案例代码流程详细模拟：求 3^11 mod p (p 取一个大数)
// 1. 初始：res = 1, a = 3, k = 11 (二进制 1011)
// 2. 第一轮 (k=11, 末位 1):
//    - if(k&1) 成立 -> res = res * a = 1 * 3 = 3
//    - a = a * a = 3^2 = 9
//    - k >>= 1，变为 5 (二进制 101)
// 3. 第二轮 (k=5, 末位 1):
//    - if(k&1) 成立 -> res = res * a = 3 * 9 = 27
//    - a = a * a = 9^2 = 81
//    - k >>= 1，变为 2 (二进制 10)
// 4. 第三轮 (k=2, 末位 0):
//    - if(k&1) 不成立 -> res 不变 (仍为 27)
//    - a = a * a = 81^2 = 6561
//    - k >>= 1，变为 1 (二进制 1)
// 5. 第四轮 (k=1, 末位 1):
//    - if(k&1) 成立 -> res = res * a = 27 * 6561 = 177147
//    - a = a * a = ... (后续不再需要)
//    - k >>= 1，变为 0
// 6. k=0，结束循环，返回 res (177147，实际上每一步都会 % p)
//
// 总结：
// - "平方"步骤 (Square): a = a * a，每一轮必定执行，负责构造 a^(2^i)
// - "乘"步骤 (Multiply): res = res * a，只有当 k 的二进制位为 1 时才执行
typedef long long LL;

LL qmi(LL a, LL k, LL p) {
    LL res = 1;
    // 对底数先取模，防止由 a 很大导致的 a*a 溢出
    a %= p; 
    while (k) {
        // "乘" (Multiply) 步骤: 如果 k 的当前末位是 1，则乘入结果
        if (k & 1) res = res * a % p;
        
        // k 右移一位，相当于 k / 2
        k >>= 1;
        
        // "平方" (Square) 步骤: 底数倍增，为下一位做准备
        a = a * a % p; 
    }
    return res;
}

LL qmi(LL a, LL k, LL p) {
    LL res = 1;
    a %= p;
    while(k) {
        if(k & 1) res = res * a % p;
        k = k >> 1;
        a = a * a % p;
    }
    return res;
}

// 乘法逆元 (Multiplicative Inverse using Fermat's Little Theorem)
// 费马小定理内容：如果 p 是质数且 a % p != 0，则 a^(p-1) == 1 (mod p) -> a * a^(p-2) == 1 (mod p)
// 结论：当 p 为质数时，a 在模 p 意义下的乘法逆元就是 a^(p-2) (mod p)。如果在代码里 a%p==0，无逆元。
void get_inv(LL a, LL p) {
    if (a % p == 0) puts("impossible"); // 不互质，且 p 为质数，此时无逆元
    else printf("%lld\n", qmi(a, p - 2, p));
}

// ==========================================
// 2. 扩展欧几里得算法 (Extended Euclidean Algorithm)
// 求解贝祖等式 (Bézout's identity) $ax + by = gcd(a, b)$
// 并返回 gcd(a, b) 的值。
// Cryptography: 通过 eax + phi_n_y = 1 得出 d (解密私钥)。
int exgcd(int a, int b, int &x, int &y) {
    // 递归边界：b = 0 时，gcd 显然是 a.
    // 此时 ax + by = a 成立的平凡解是 x = 1, y = 0.
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    // gcd(a, b) == gcd(b, a % b)
    // 假设已经递归求出了 bx1 + (a % b)y1 == d 里的 x1 和 y1 
    int d = exgcd(b, a % b, y, x); 

    // 根据等价变换：
    // y 翻转到了第一位（x1 位置），x 待求出第二位（y1 位置）
    // 当前需要 a 的系数和 b 的系数：
    // b * (原 y1，由于这里传参翻转，变成了形参 x 的值) + (a - a/b*b) * x1 (现在的 y 的值)
    //  = ay + b(x - (a / b) * y)
    y -= a / b * x;

    return d;
}

// 扩欧求一元线性同余方程 $ax \equiv b \pmod m$
// 它等价于存在整数 y 使得 $ax + my = b$。
// 根据裴蜀定理，方程有解当且仅当 gcd(a, m) | b。
// 我们先通过 `exgcd(a, m, x, y)` 求出 $ax0 + my0 = gcd(a, m)$
// 再将等式同乘 $b / gcd$ 即可得到 x 的特解 $x = x0 * (b/gcd)$。
bool linear_congruence(int a, int b, int m, int &x) {
    int _x, _y;
    int d = exgcd(a, m, _x, _y);
    if (b % d) return false; // 无解
    
    // x = _x * (b / d)
    // 防止 C++ 负数取模向 0 取整带来错误：(res % m + m) % m。
    x = (LL)_x * (b / d) % m; // 将解转移到 [0, m) 区间
    return true;
}

int main() {
    // 快速幂测算: 3^5 mod 13 = 243 % 13 = 9
    cout << "3^5 mod 13 = " << qmi(3, 5, 13) << endl;

    // 费马求逆元：求 3 在模 13 下的逆元 (结果应是 9。因为 3 * 9 = 27 = 2 * 13 + 1 -> 27=1 mod 13)
    cout << "3 mod 13 的乘法逆元: " << qmi(3, 13 - 2, 13) << endl;

    // 扩展欧几里得测算: a = 12, b = 8 => gcd = 4
    int x, y;
    int g = exgcd(12, 8, x, y);
    cout << "exgcd(12, 8): gcd = " << g << ", 12*(" << x << ") + 8*(" << y << ") = " << g << endl;

    // 线性同余测试: a=2, b=4, m=6  即 2 * x = 4 (mod 6) => x = 2
    int res_x;
    if (linear_congruence(2, 4, 6, res_x)) {
        cout << "2 * " << res_x << " = 4 (mod 6) [可能有多个解, 这里给出一个特解]" << endl;
    }

    return 0;
}
