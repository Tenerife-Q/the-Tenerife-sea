/*
 * @Problem: Christmas Party
 * @Source: CSES - Mathematics
 * 
 * @Description (English):
 * There are n children at a Christmas party, and each of them has brought a gift. The idea is that everybody will get a gift brought by someone else.
 * In how many ways can the gifts be distributed?
 * 
 * @Description (Chinese):
 * 有 n 个孩子参加圣诞派对，每个孩子都带来了一份礼物。要求每个人都得到别人带来的礼物（即没有人收到自己带来的礼物）。
 * 问：礼物可以有多少种分配方式？
 * 
 * @Input:
 * The only input line has an integer n: the number of children.
 * 仅有一行，包含一个整数 n，表示孩子数量。
 * 
 * @Output:
 * Print the number of ways modulo 10^9+7.
 * 输出方案数对 10^9+7 取模的结果。
 * 
 * @Constraints:
 * 1 <= n <= 10^6
 * 
 * @Example:
 * Input:
 * 4
 * 
 * Output:
 * 9
 * 
 * @Algorithm:
 * Derangements / Subfactorials (错排问题)
 * 利用错排递推公式：D(n) = (n - 1) * (D(n-1) + D(n-2)) 
 * 或是更简化的迭代：D(n) = n * D(n-1) + (-1)^n，以 O(N) 动态规划解决。
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

    count[1] = 0; 
    count[2] = 1;

    for(int i = 3; i <= n; ++i) {
        count[i] = (i - 1) * (count[i - 1] + count[i - 2]) % MOD;
    }
    cout << count[n] << "\n";

    return 0;
}