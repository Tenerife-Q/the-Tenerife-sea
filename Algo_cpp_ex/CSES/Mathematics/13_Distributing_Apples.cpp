#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
// 注意：n和m最大都是10^6，组合数的上标 n+m-1 会达到 2 * 10^6，所以数组要开到2000005
const int MAXN = 2000005;

/*
Distributing Apples — 题目摘要（中英双语）

English (summary):
Given n recipients and m identical apples, count the number of ways to distribute all m apples among the n recipients. A recipient may receive zero apples. Output the number of distributions modulo 10^9+7.
Formula (stars and bars): answer = C(n + m - 1, n - 1) (equivalently C(n + m - 1, m)).

中文（摘要）：
给定 n 个接收者和 m 个不可区分的苹果，计算将全部 m 个苹果分配给这 n 个接收者的方法数。允许接收者分到 0 个苹果。结果对 10^9+7 取模。
组合学公式（星与杠）：答案 = C(n + m - 1, n - 1)（等价于 C(n + m - 1, m)）。

示例：n=3, m=2 → C(4,2)=6
*/

long long fact[MAXN];
long long invFact[MAXN];

// 快速幂算法计算 (base^exp) % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int total_elements = n + m - 1;

    // 1. 预处理 1 到 n+m-1 的阶乘
    fact[0] = 1;
    for (int i = 1; i <= total_elements; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    // 2. 预处理阶乘的逆元
    // 先用费马小定理通过快速幂算出最大的阶乘逆元
    invFact[total_elements] = power(fact[total_elements], MOD - 2);
    // 然后利用性质: 1/(i-1)! = (1/i!) * i，从大到小递推算出所有的阶乘逆元
    for (int i = total_elements - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    // 3. 计算组合数 C(n+m-1, n-1)
    // Ans = (n+m-1)! / ((n-1)! * m!) 
    //     = fact[n+m-1] * invFact[n-1] * invFact[m] (在模运算意义下)
    long long ans = fact[total_elements];
    ans = (ans * invFact[n - 1]) % MOD;
    ans = (ans * invFact[m]) % MOD;

    // 输出最终结果
    cout << ans << "\n";

    return 0;
}