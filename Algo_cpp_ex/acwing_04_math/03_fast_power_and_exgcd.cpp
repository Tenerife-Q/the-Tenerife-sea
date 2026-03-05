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
// 求 m^k mod p 的结果，时间复杂度 O(log k)
// 原理：将 k 写出二进制表示，例如 11 = (1011)_2
// 11 = 1 * 2^0 + 1 * 2^1 + 0 * 2^2 + 1 * 2^3
// $m^{11} = m^{2^0} \cdot m^{2^1} \cdot m^{2^3}$
// Cryptography: a^b mod m is the core operation in RSA encryption/decryption
typedef long long LL;

LL qmi(LL a, LL k, LL p) {
    LL res = 1;
    while (k) {
        if (k & 1) res = res * a % p;
        k >>= 1;   // 指数右移一位，相当于除以2
        a = a * a % p; // 自身平方，即 a 变成 a^2, a^4, a^8 ...
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
