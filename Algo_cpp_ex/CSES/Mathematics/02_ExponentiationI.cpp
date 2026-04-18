#include <iostream>
using namespace std;

/*
 * @Problem: Exponentiation
 * @Source: CSES - Mathematics
 * 
 * @Description (English):
 * Your task is to efficiently calculate the value a^b modulo 10^9+7.
 * Note that in this task we assume that 0^0 = 1.
 * 
 * @Description (Chinese):
 * 你的任务是高效计算 a^b 对 10^9+7 取模的值。
 * 注意在本题中我们假定 0^0 = 1。
 * 
 * @Input:
 * The first input line contains an integer n: the number of calculations.
 * After this, there are n lines, each containing two integers a and b.
 * 第一行输入包含一个整数 n：计算次数。
 * 接下来 n 行，每行包含两个整数 a 和 b。
 * 
 * @Output:
 * Print each value a^b modulo 10^9+7.
 * 输出每个 a^b 对 10^9+7 取模的值。
 * 
 * @Constraints:
 * 1 <= n <= 2 * 10^5
 * 0 <= a, b <= 10^9
 * 
 * @Example:
 * Input:
 * 3
 * 3 4
 * 2 8
 * 123 123
 * 
 * Output:
 * 81
 * 256
 * 921450052
 * 
 * @Algorithm:
 * Modular Exponentiation / Fast Power (快速幂)
 */




/*
const int MOD = 1e9 + 7;

// 【核心模板】：快速幂计算 (base^exp) % mod
// 务必肌肉记忆，做到 30 秒内盲打无 Bug
long long qpow(long long base, long long exp) {
    long long res = 1;
    base %= MOD; // 防御性编程：防止输入的 base 已经大于 MOD
    
    while (exp > 0) {
        // 如果当前二进制最低位是 1，乘入结果
        if (exp & 1) res = (res * base) % MOD;
        
        // 底数平方，指数右移一位
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    // 竞程必备 IO 优化模板
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    while (n--) {
        long long a, b;
        cin >> a >> b;
        cout << qpow(a, b) << "\n";
    }
    return 0;
}
*/


#include <iostream>
using namespace std;
typedef long long ll;
const int p = 1e9 + 7;

ll qmi(ll a, ll k, ll p) {
    ll res = 1;
    a %= p;
    while(k) {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    while( n-- ) {
        ll a, k;
        cin >> a >> k;
        cout << qmi(a, k, p) << "\n";
    }
}



// recursive version
// 这里可以详见应用密码学封面模平方计算从左往右 上面那个算法更简单易懂 是从左往右
// #include <iostream>
// using namespace std;
// using ll = long long;

// int power(int a, int b, int m) {
//     if (b == 0) return 1 % m;
//     ll p = power(a, b / 2, m);
//     p = p * p % m;
//     if (b % 2 == 1) p = p * a % m;
//     return p;
// }

// int main() {
//     int n;
//     cin >> n;
//     for (int i = 1; i <= n; i++) {
//         int a, b;
//         cin >> a >> b;
//         cout << power(a, b, 1e9 + 7) << "\n";
//     }
// }