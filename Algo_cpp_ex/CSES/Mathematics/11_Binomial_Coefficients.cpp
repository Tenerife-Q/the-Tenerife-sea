/*
 * @Problem: Binomial Coefficients
 * @Source: CSES - Mathematics
 * 
 * @Description (English):
 * Your task is to calculate n binomial coefficients modulo 10^9+7.
 * A binomial coefficient (a \choose b) can be calculated using the formula a! / (b!(a-b)!).
 * We assume that a and b are integers and 0 <= b <= a.
 * 
 * @Description (Chinese):
 * 你的任务是计算 n 个二项式系数（组合数）对 10^9+7 取模的结果。
 * 一个二项式系数 C(a, b) 可以使用公式 a! / (b!(a-b)!) 来计算。
 * 我们假设 a 和 b 都是整数并且 0 <= b <= a。
 * 
 * @Input:
 * The first input line contains an integer n: the number of calculations.
 * After this, there are n lines, each of which contains two integers a and b.
 * 第一行包含一个整数 n：计算的次数。
 * 接下来 n 行，每行包含两个整数 a 和 b。
 * 
 * @Output:
 * Print each binomial coefficient modulo 10^9+7.
 * 打印每个组合数对 10^9+7 取模的值。
 * 
 * @Constraints:
 * 1 <= n <= 10^5
 * 0 <= b <= a <= 10^6
 * 
 * @Example:
 * Input:
 * 3
 * 5 3
 * 8 1
 * 9 5
 * 
 * Output:
 * 10
 * 8
 * 126
 * 
 * @Algorithm:
 * Modular Multiplicative Inverse / Combinatorics (模乘法逆元 / 组合数学)
 * 极致预处理优化：顺推预处理阶乘，用费马小定理快速幂求最大阶乘逆元，倒推求所有逆元，O(1) 回答。
 */

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAX = 1e6;

// 全局数组存阶乘和阶乘的逆元 (开到最大范围 10^6 + 1)
ll fact[MAX + 1];
ll invFact[MAX + 1];

// 快速幂算法：计算 (base^exp) % MOD，时间复杂度 O(log exp)
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD; // 防止 base 初始过大
    while (exp > 0) {
        // 如果当前指数是奇数，累乘到结果中
        if (exp % 2 == 1) res = (res * base) % MOD;
        // 底数平方，指数减半
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// 预处理函数：O(MAX) 计算所有阶乘及其逆元
void precompute() {
    // 1. 预处理阶乘：fact[i] = i! % MOD
    fact[0] = 1; // 0! = 1
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    // 2. 预处理阶乘逆元：先算出最大阶乘 (10^6!) 的逆元
    invFact[MAX] = power(fact[MAX], MOD - 2);
    
    // 3. 倒推所有的阶乘逆元：invFact[i-1] = (invFact[i] * i) % MOD
    // 这样避免了对每个数都做一次快速幂，将 O(N log M) 优化为了 O(N)
    for (int i = MAX - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// 单次查询的求解函数
void solve() {
    int a, b;
    cin >> a >> b;
    
    // 如果 b > a（虽然题目给定 b <= a，这里写上为了严谨性）
    if (b > a || b < 0) {
        cout << 0 << "\n";
        return;
    }
    
    // 组合数计算：a! * (b!)^-1 * ((a-b)!)^-1 % MOD
    ll ans = fact[a];
    ans = (ans * invFact[b]) % MOD;
    ans = (ans * invFact[a - b]) % MOD;
    
    cout << ans << "\n";
}

int main() {
    // 必须加上这部分来优化 C++ I/O 速度，对于 10^5 级别的读取至关重要！
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // 1. 程序启动时，先执行预处理（仅一次）
    precompute();
    
    int n;
    // 2. 依次读取并处理每次查询
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }
    
    return 0;
}



#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAX = 1e6;

ll fact[MAX + 1];
ll invFact[MAX + 1];

ll power(ll a, ll b) {
    if(b == 0) return 1;
    ll res = power(a, b / 2);
    res = (res * res) % MOD;
    if(b % 2 == 1) res = (res * a) % MOD;
    return res;
}

void precompute() {
    fact[0] = 1;
    for(int i = 1; i <= MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[MAX] = power(fact[MAX], MOD - 2);
    for(int i = MAX -1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();

    int n;
    cin >> n;
    while(n--) {
        int a, b;
        cin >> a >> b;
        if(b > a || b < 0) {
            cout << 0 << "\n";
            continue;
        }

        ll ans = fact[a];
        ans = (ans * invFact[b]) % MOD;
        ans = (ans * invFact[a - b]) % MOD;
        cout << ans << "\n";
    }
    return 0;
}