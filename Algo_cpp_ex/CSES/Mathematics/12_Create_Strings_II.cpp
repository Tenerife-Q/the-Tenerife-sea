/*
Creating Strings II — 题目与算法分析（中英双语注释）

Problem (English)
------------------
Given a string, your task is to calculate the number of different strings that can be created using its characters.

Input
The only input line has a string of length n. Each character is between a–z.

Output
Print the number of different strings modulo 10^9 + 7.

Constraints
1 ≤ n ≤ 10^6

Example
Input: aabac
Output: 20

题目（中文）
------------------
给定一个字符串，你的任务是计算使用其字符可以组成多少种不同的字符串。

输入
唯一的一行输入包含一个长度为 n 的字符串。每个字符都是 a 到 z 之间的小写字母。

输出
打印可以组成的不同字符串的数量，结果对 10^9+7 取模。

样例
输入：
aabac

输出：
20

算法分析（要点）
------------------
1) 数学模型（多重集的全排列）
   设字符串长度为 n，字符 a 出现 c0 次，b 出现 c1 次，…，z 出现 c25 次。
   不同排列数为： n! / (c0! * c1! * ... * c25!)。

2) 模运算下的除法（乘法逆元）
   由于要求对 MOD = 10^9+7 取模，不能直接做除法。利用费马小定理，x^{-1} ≡ x^{MOD-2} (mod MOD)。

3) O(n) 预处理阶乘与逆元
   - 先正向计算 fact[i] = i! (mod MOD)。
   - 用快速幂计算 invFact[n] = (fact[n])^{MOD-2}。
   - 逆向递推得到 invFact[i-1] = invFact[i] * i (mod MOD)，从而得到所有阶乘的逆元。

4) 计算答案
   最终答案为 fact[n] 乘以每个字符计数的 invFact[count] 的乘积（模 MOD）。

复杂度
   时间：O(n) 预处理 + O(26) 统计与乘积，整体 O(n)。
   空间：O(n)（用于保存阶乘与逆元数组）。

下面保留原实现代码（已存在，不作改动）。
*/

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
