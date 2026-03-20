/*
Problem: Christmas Party

English:
There are n children at a Christmas party, and each of them has brought a gift. The idea is that everybody will get a gift brought by someone else.
In how many ways can the gifts be distributed?

Input
The only input line has an integer n: the number of children.

Output
Print the number of ways modulo 10^9+7.

Constraints
1 <= n <= 10^6

Example
Input:
4

Output:
9

中文：圣诞派对

题目描述：
有 n 个孩子参加圣诞派对，每个孩子都带来了一份礼物。要求每个人都得到别人带来的礼物（即没有人收到自己带来的礼物）。
问：礼物可以有多少种分配方式？

输入：
仅有一行，包含一个整数 n，表示孩子数量。

输出：
输出方案数对 10^9+7 取模的结果。

约束：
1 <= n <= 10^6

样例：
输入：
4

输出：
9

Remarks: This is counting derangements (subfactorials). Use recurrence D_n = n * D_{n-1} + (-1)^n.
*/

#include <iostream>

using namespace std;

int main() {
    // 优化输入输出流速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    long long MOD = 1e9 + 7;
    long long ans = 0; // 当 n = 1 时，错排数为 0
    
    for (int i = 2; i <= n; ++i) {
        ans = (ans * i) % MOD;
        // 根据公式 Dn = n * D_{n-1} + (-1)^n
        if (i % 2 == 0) {
            ans = (ans + 1) % MOD;
        } else {
            ans = (ans - 1 + MOD) % MOD; // 加上 MOD 防止出现负数求模的情况
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}

#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    ll MOD = 1e9 + 7;
    ll ans = 0;

    for(int i = 2; i <= n; ++i) {
        ans = (ans * i) % MOD;
        if(i % 2 == 0) {
            ans = (ans + 1) % MOD;
        } else {
            ans = (ans - 1 + MOD) % MOD;
        }
    }
    cout << ans << "\n";

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;
const int N = 1e6 + 5;
vector<ll> count(N);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    count[0] = 1; // D(0) = 1
    count[1] = 0; // D(1) = 0

    for(int i = 2; i <= n; ++i) {
        count[i] = (i * count[i - 1] + (i % 2 == 0 ? 1 : -1) + MOD) % MOD;
    }
    cout << count[n] << "\n";

    return 0;
}