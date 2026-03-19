/*
🍏 Distributing Apples (分配苹果)

English Description:
There are n children and m apples that will be distributed to them. Your task is to count the number of ways this can be done.
For example, if n = 3 and m = 2, there are 6 ways: [0,0,2], [0,1,1], [0,2,0], [1,0,1], [1,1,0], and [2,0,0].

Input
The only input line has two integers n and m.

Output
Print the number of ways modulo 10^9+7.

Constraints
1 <= n, m <= 10^6

Example
Input: 3 2
Output: 6

中文说明：
有 n 个孩子和 m 个苹果，你需要将这些苹果分配给这些孩子。请计算有多少种不同的分配方式。
例如，如果 n=3 且 m=2，有 6 种分配方式： [0,0,2]、[0,1,1]、[0,2,0]、[1,0,1]、[1,1,0]、[2,0,0]。

输入
唯一的一行包含两个整数 n 和 m。

输出
输出不同的分配方式总数对 10^9+7 取模的结果。

数据范围
1 <= n, m <= 10^6

样例
输入：3 2
输出：6

思路（简要）：
使用“星与杠”组合公式：将 m 个不可区分的物品分配到 n 个容器，答案为组合数 C(n+m-1, n-1)。
在模意义下通过预处理阶乘和逆元快速计算组合数。
*/

// #include <iostream>
// #include <vector>

// using namespace std;

// const int MOD = 1e9 + 7;
// // 注意：n和m最大都是10^6，组合数的上标 n+m-1 会达到 2 * 10^6，所以数组要开到2000005
// const int MAXN = 2000005;


// long long fact[MAXN];
// long long invFact[MAXN];

// // 快速幂算法计算 (base^exp) % MOD
// long long power(long long base, long long exp) {
//     long long res = 1;
//     base %= MOD;
//     while (exp > 0) {
//         if (exp % 2 == 1) res = (res * base) % MOD;
//         base = (base * base) % MOD;
//         exp /= 2;
//     }
//     return res;
// }

// int main() {
//     // 优化输入输出流
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m;
//     if (!(cin >> n >> m)) return 0;

//     int total_elements = n + m - 1;

//     // 1. 预处理 1 到 n+m-1 的阶乘
//     fact[0] = 1;
//     for (int i = 1; i <= total_elements; i++) {
//         fact[i] = (fact[i - 1] * i) % MOD;
//     }

//     // 2. 预处理阶乘的逆元
//     // 先用费马小定理通过快速幂算出最大的阶乘逆元
//     invFact[total_elements] = power(fact[total_elements], MOD - 2);
//     // 然后利用性质: 1/(i-1)! = (1/i!) * i，从大到小递推算出所有的阶乘逆元
//     for (int i = total_elements - 1; i >= 0; i--) {
//         invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
//     }

//     // 3. 计算组合数 C(n+m-1, n-1)
//     // Ans = (n+m-1)! / ((n-1)! * m!) 
//     //     = fact[n+m-1] * invFact[n-1] * invFact[m] (在模运算意义下)
//     long long ans = fact[total_elements];
//     ans = (ans * invFact[n - 1]) % MOD;
//     ans = (ans * invFact[m]) % MOD;

//     // 输出最终结果
//     cout << ans << "\n";

//     return 0;
// }



#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXN = 2000005;


ll fact[MAXN];
ll invFact[MAXN];

ll power(ll a, ll b) {
    if(b == 0) return 1;
    ll res = power(a, b / 2);
    res = (res * res) % MOD;
    if(b % 2 == 1) res = (res * a) % MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int total = n + m - 1;
    fact[0] = 1;
    for(int i = 1; i <= total; i++ ) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[total] = power(fact[total], MOD -2);
    for(int i = total - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    ll ans = fact[total] % MOD;
    ans = (ans * invFact[m]) % MOD;
    ans = (ans * invFact[n - 1]) % MOD;

    cout << ans << "\n";
    
    return 0;
}