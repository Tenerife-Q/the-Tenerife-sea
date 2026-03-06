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
// 适合单次判定一个数是否为质数。
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= n / i; i++) { // 注意：使用 i <= n / i 防止 i*i 溢出
        if (n % i == 0) return false;
    }
    return true;
}


bool is_prime(int n) {
    if(n < 2) return false;
    for(int i = 2; i <= n / i; i++ ) {
        if(n % i == 0) return false;
    }
    return true;
}
// ==========================================
// 2. 试除法分解质因数 - O(sqrt(n))
// 输出: 质因数 p 以及对应的指数 c
// 密码学意义：整数分解问题是 RSA 的理论基础
void divide(int n) {
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
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


void divide(int n) {
    for(int i = 2; i <= n / i; i ++ ) {
        if(n % i == 0) {
            int s = 0;
            while(n % i == 0) {
                n /= i;
                s++;
            }
            cout << i << "^" << s << " ";
        }
    }
    if(n > 1) cout << n << "^1";
}
// ==========================================
// 3. 线性筛法 (欧拉筛法) 求 1~n 的质数 - O(n)
// 竞赛必备！每个合数只会被其最小质因子筛掉一次，效率极高。
const int N = 1e6 + 10;
int primes[N], cnt;     // primes[] 存所有的质数
bool st[N];             // st[x] 表示 x 是否被筛掉（如果被筛掉说明一定不是质数）

void get_primes(int n) {
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        // 把当前已有的质数从小到大枚举
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            // 当 i % primes[j] == 0 时，因为 primes[j] 是从小到大枚举的，
            // 此时 primes[j] 一定是 i 的最小质因子，这就意味着 primes[j] 也是 primes[j] * i 的最小质因子。
            // 为了保证每个数只被其最小质因子筛掉，这里必须 break。
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    int n, a;
    cout << "测试试除法分解质因数，输入测数个数和各数字: " << endl;
    if (cin >> n) {
        while (n--) {
            cin >> a;
            divide(a);
        }
    }

    cout << "测试线性筛法，预处理质数到 100 范围:" << endl;
    get_primes(100);
    for (int i = 0; i < cnt; i++) {
        cout << primes[i] << " ";
    }
    cout << endl;

    return 0;
}
