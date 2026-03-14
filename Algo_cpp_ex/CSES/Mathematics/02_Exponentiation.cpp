#include <iostream>
using namespace std;

/*
题目：Exponentiation

描述（中）：高效计算 a^b mod (1e9+7)。
输入第一行给出 n 表示计算次数，接下来 n 行每行给出两个整数 a 和 b，输出每个 a^b (模 1e9+7) 的值。假定 0^0 = 1。

Description (EN): Efficiently calculate a^b modulo 10^9+7. 
The first line contains integer n, the number of calculations. 
Then follow n lines each with integers a and b. Print each a^b modulo 10^9+7. Note that 0^0 = 1.

Input:
 - First line: integer n (1 ≤ n ≤ 2·10^5)
 - Next n lines: integers a, b (0 ≤ a, b ≤ 10^9)

Output:
 - For each pair, print a^b mod 1e9+7 on its own line.
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