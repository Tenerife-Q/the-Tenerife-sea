#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 定义模数和数组的最大容量
const int MOD = 1e9 + 7;
const int MAXN = 1000005;

// fact 用来存储阶乘，invFact 用来存储阶乘的逆元
long long fact[MAXN];
long long invFact[MAXN];

// 快速幂算法：计算 (base^exp) % MOD
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
    // 优化标准输入输出流，极大提升读取速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    // 读取字符串，如果读取失败则退出
    if (!(cin >> s)) return 0;

    int n = s.length();
    
    // 1. 预处理 0 到 n 的阶乘
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    // 2. 预处理阶乘的逆元
    // 先利用费马小定理 (a^(p-2) % p) 通过快速幂求出 n! 的逆元
    invFact[n] = power(fact[n], MOD - 2);
    // 从后往前倒推，求出所有阶乘的逆元: 1/(i-1)! = (1/i!) * i
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
    
    // 3. 统计每个字符在字符串中出现的次数
    int counts[26] = {0};
    for (char c : s) {
        counts[c - 'a']++;
    }
    
    // 4. 计算多重集的全排列数
    // 公式: n! / (c_0! * c_1! * ... * c_25!)
    // 转换: n! * invFact[c_0] * invFact[c_1] * ... * invFact[c_25] % MOD
    long long ans = fact[n];
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            ans = (ans * invFact[counts[i]]) % MOD;
        }
    }
    
    // 5. 输出最终答案
    cout << ans << "\n";
    
    return 0;
}