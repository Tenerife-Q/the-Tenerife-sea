/**
 * 模块：第四讲 数学知识
 * 主题：基础数论 - 质数判定与欧拉筛法 (Primes & Sieve)
 * ICPC 考点与密码学：大素数的生成与验证是 RSA 等公钥密码算法的绝对核心。
 *                      在竞赛中，素数筛法常常被用作预处理，以在 $O(1)$ 时间判定素数。
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ==========================================
// 1. 试除法判定质数 - O(sqrt(n))
// 理论依据：若 n 是合数，则 n 必有一个小于等于 sqrt(n) 的因子。
// 适合单次判定一个数是否为质数。
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= n / i; i++) { // 注意：使用 i <= n / i 防止 i*i 溢出
        if (n % i == 0) return false;
    }
    return true;
}

// ==========================================
// 2. 试除法分解质因数 - O(sqrt(n))
// 理论依据：算术基本定理（任何大于1的整数都能唯一分解为有限个质数的乘积）。
// 输出: 质因数 p 以及对应的指数 c
// 密码学意义：整数分解问题是 RSA 的理论基础
void divide(int n) {
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) { // i 一定是质数，因为从小到大枚举，如果是合数，会被前面的质因子先除掉
            int s = 0;
            while (n % i == 0) {
                n /= i;
                s++;
            }
            cout << i << "^" << s << " ";
        }
    }
    // 特判：如果 n 还是大于 1 的话，说明 n 包含一个大于 sqrt(n) 的质因数
    if (n > 1) cout << n << "^" << 1 << " ";
    cout << endl;
}

// ==========================================
// 3. 全局变量与筛法基础
const int N = 1e6 + 10; // 范围
int primes[N], cnt;     // primes[] 存所有的质数, cnt 是质数个数
bool st[N];             // st[x] true 表示 x 是合数 (被筛掉), false 表示 x 是质数

// ==========================================
// 4. 埃氏筛法 (Sieve of Eratosthenes) - O(n log log n)
// 核心思想：每当找到一个质数 p，就将其所有的倍数 2p, 3p... 标记为合数。
// 瓶颈：会被重复筛选，例如 12 会被 2 和 3 同时标记。
void get_primes_eratosthenes(int n) {
    cnt = 0;
    // 重置数组 (如果是多次调用不同筛法)
    // for(int i=0; i<=n; i++) st[i] = false;

    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            // 优化：从 i * i 开始筛，因为 2*i, 3*i ... 已经被 2, 3 ... 的倍数筛过了
            // 注意：i * i 可能会溢出 int，可以使用 long long 或者判断 j <= n / i
            if ((long long)i * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    st[j] = true;
                }
            }
        }
    }
}

// ==========================================
// 5. 线性筛法 (欧拉筛法 Euler Sieve) - O(n)
// 竞赛必备！每个合数只会被其最小质因子筛掉一次，效率极高。
// 核心思想：确保每个合数仅被其“最小质因子”筛去。
void get_primes_euler(int n) {
    cnt = 0;
    // 重置数组
    // for(int i=0; i<=n; i++) st[i] = false;

    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        // 把当前已有的质数从小到大枚举
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            
            // 关键逻辑：
            // 1. 当 i % primes[j] != 0 时：primes[j] 是 primes[j] * i 的最小质因子。
            // 2. 当 i % primes[j] == 0 时：primes[j] 是 i 的最小质因子，也是 primes[j] * i 的最小质因子。
            //    如果不 break，继续枚举 j+1，合数 X = primes[j+1] * i。
            //    因为 i 是 primes[j] 的倍数，所以 X = primes[j+1] * (k * primes[j])。
            //    X 的最小质因子其实是 primes[j]，应该在 i 变大到 X/primes[j] 时被 primes[j] 筛掉。
            //    现在用 primes[j+1] 筛就是重复操作。
            if (i % primes[j] == 0) break;
        }
    }
}



int main() {
    // 基础功能测试
    cout << "=== 功能 1: 判定素数 (is_prime) ===" << endl;
    cout << "is_prime(17): " << (is_prime(17) ? "Yes" : "No") << endl;
    cout << "is_prime(20): " << (is_prime(20) ? "Yes" : "No") << endl;

    cout << "\n=== 功能 2: 分解质因数 (divide) ===" << endl;
    cout << "divide(360): ";
    divide(360);

    // 筛法测试
    int limit = 100;
    
    cout << "\n=== 功能 3: 埃氏筛法 (Eratosthenes) ===" << endl;
    // 重置全局变量 st
    for(int i=0; i<=limit; i++) st[i] = false;
    get_primes_eratosthenes(limit);
    cout << "Range [2, " << limit << "], Primes Count: " << cnt << endl;
    for (int i = 0; i < cnt; i++) cout << primes[i] << " ";
    cout << endl;

    cout << "\n=== 功能 4: 欧拉筛法 (Euler) ===" << endl;
    // 重置全局变量 st
    for(int i=0; i<=limit; i++) st[i] = false;
    get_primes_euler(limit);
    cout << "Range [2, " << limit << "], Primes Count: " << cnt << endl;
    for (int i = 0; i < cnt; i++) cout << primes[i] << " ";
    cout << endl;

    return 0;
}
