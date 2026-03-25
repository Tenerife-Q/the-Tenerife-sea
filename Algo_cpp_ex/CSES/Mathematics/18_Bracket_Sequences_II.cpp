/*
Bracket Sequences II  /  括号序列 II

Task:
Your task is to calculate the number of valid bracket sequences of length n when a prefix of the sequence is given.

Time limit: 1.00 s
Memory limit: 512 MB

Input:
The first input line has an integer n.
The second line has a string of k characters: the prefix of the sequence.

Output:
Print the number of sequences modulo 10^9+7.

Constraints:
1 <= k <= n <= 10^6

Example:
Input:
6
(()

Output:
2

Explanation: There are two possible sequences: (())() and (()()).


中文说明：
任务：给定括号序列长度 n 以及一个长度为 k 的前缀，计算在该前缀固定的情况下，合法括号序列的数量。

时间限制：1.00 秒
内存限制：512 MB

输入：第一行一个整数 n。第二行是长度为 k 的字符串，表示序列的前缀。

输出：对 10^9+7 取模的合法序列数。

约束：1 <= k <= n <= 10^6

示例：
输入：
6
(()

输出：
2

说明：可行序列为 (())() 和 (()())。

来源: CSES — Bracket Sequences II（题目已按中英双语整理，仅供注释与学习使用）
*/

// 标题：Bracket Sequences II - 广义选票定理与路径反射法
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

const int MOD = 1000000007;

// 快速幂算法：用于计算 (base^exp) % MOD
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = res * base % MOD;
        base = base * base % MOD;
        exp /= 2;
    }
    return res;
}

// 费马小定理求逆元
ll modInverse(ll n) {
    return power(n, MOD - 2);
}

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    string prefix;
    cin >> prefix;

    // 1. 奇数长度不可能合法
    if (n % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }

    // 2. 验证前缀合法性并统计现有括号数量
    int open = 0, close = 0;
    for (char c : prefix) {
        if (c == '(') open++;
        else close++;
        
        // 任意时刻右括号的数量绝不能超过左括号
        if (close > open) {
            cout << 0 << "\n";
            return 0;
        }
    }

    // 3. 左右括号的总需求量均为 n/2，不能透支
    if (open > n / 2 || close > n / 2) {
        cout << 0 << "\n";
        return 0;
    }

    // 4. 计算剩余还需要添加的左括号 L 和右括号 R
    int L = n / 2 - open;
    int R = n / 2 - close;

    // 5. 预处理阶乘数组 (O(N) 复杂度)
    // 根据推导公式，我们需要用到的最大阶乘索引可能达到 max(L+R, R+1) <= n
    // 为保险起见开 n + 2 的大小
    vector<ll> fac(n + 2, 1);
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    // 6. 应用化简后的广义选票定理公式: 
    // Ans = (L+R)! * (R - L + 1) / (L! * (R+1)!)
    
    ll total_len = L + R;
    
    // 分子: (L+R)! * (R - L + 1)
    ll numerator = fac[total_len] * (R - L + 1) % MOD;
    
    // 分母: L! * (R+1)!
    ll denominator = fac[L] * fac[R + 1] % MOD;

    // 最终结果: 分子 * 分母的逆元 % MOD
    ll ans = numerator * modInverse(denominator) % MOD;

    cout << ans << "\n";

    return 0;
}



#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    ll res = 1;
    a %= M;
    while (b > 0) {
        if (b & 1) res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res;
}

ll modInverse(ll a) {
    return power(a, M - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    string pre;
    cin >> pre;

    if (n % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }

    int open = 0, close = 0;
    for (char c : pre) {
        if(c == '(') open ++;
        else close ++;
        if (close > open) {
            cout << 0 << "\n";
            return 0;
        }
    }

    if (open > n / 2 || close > n / 2) {
        cout << 0 << "\n";
        return 0;
    }

    int L = n / 2 - open;
    int R = n / 2 - close;

    vector<ll> fact(n + 2, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % M;
    }

    ll fz = fact[L + R] * (R - L + 1) % M;
    ll fm = (fact[L] * fact[R + 1]) % M;
    ll ans = (fz * modInverse(fm)) % M;
    cout << ans << "\n";

    return 0;
}