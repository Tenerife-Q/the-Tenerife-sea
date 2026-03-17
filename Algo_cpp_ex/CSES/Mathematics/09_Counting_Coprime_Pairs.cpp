/*
Counting Coprime Pairs — Problem statement (English)

Given a list of n positive integers, your task is to count the number of pairs of integers
that are coprime (i.e., their greatest common divisor is one).

Input:
The first input line has an integer n: the number of elements.
The next line has n integers x1, x2, …, xn: the contents of the list.

Output:
Print one integer: the answer for the task (number of coprime pairs).

Constraints:
1 ≤ n ≤ 10^5
1 ≤ xi ≤ 10^6

Example:
Input:
8
5 4 20 1 16 17 5 15

Output:
19

Source: https://cses.fi/problemset/task/2417/
*/

/*
中文（翻译）：统计互质对

给定一个包含 n 个正整数的列表，计算列表中互质（最大公约数为 1）的整数对的数量。

输入：
第一行一个整数 n，表示元素个数。
第二行 n 个整数 x1, x2, …, xn，为列表元素。

输出：
输出一个整数：互质对的数量。

约束：
1 ≤ n ≤ 10^5
1 ≤ xi ≤ 10^6

样例：
输入：
8
5 4 20 1 16 17 5 15

输出：
19
*/


/*
超时版本：O(n^2) 枚举所有对，计算 gcd 判断是否互质。

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
	// 在此处实现解法，或用于粘贴/测试样例。
    int n;
    cin >> n;
    vector<ll> arr(n);
    for(int i = 0; i < n; i++ ) {
        cin >> arr[i];
    }

    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(gcd(arr[i], arr[j]) == 1) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
	return 0;
}
*/



#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_X = 1000005; // 元素最大值边界
int freq[MAX_X];           // 桶计数：记录每个数字出现的次数

// --- 莫比乌斯函数预处理组件 ---
int mu[MAX_X];
vector<int> primes;
bool is_prime[MAX_X];

void init_mobius() {
    fill(is_prime + 2, is_prime + MAX_X, true);
    mu[1] = 1; // 莫比乌斯函数的底座
    
    for (int i = 2; i < MAX_X; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1; // 单个质数，包含奇数个不同质因子，容斥系数为 -1
        }
        for (int p : primes) {
            if (i * p >= MAX_X) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                // p 已经是 i 的质因子了，i*p 必然包含 p^2（平方因子）
                mu[i * p] = 0; 
                break; // 欧拉筛的核心：保证每个数只被最小质因子筛掉
            } else {
                // 多了一个不同的质因子，容斥系数反转
                mu[i * p] = -mu[i]; 
            }
        }
    }
}

int main() {
    // 狂暴解除 C++ IO 封印，应对 10^5 级别的输入
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_mobius(); // 战前准备：预处理 mu

    int n;
    if (!(cin >> n)) return 0;
    
    // 我们不需要存原数组，直接丢进桶里！
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    ll ans = 0; // 互质对数极大，必须 long long
    
    // 调和级数大杀器：外层枚举可能的公约数 d
    for (int d = 1; d < MAX_X; d++) {
        if (mu[d] == 0) continue; // mu 为 0 的直接跳过，绝妙的剪枝！

        ll cnt = 0; 
        // 内层按步长 d 枚举 d 的所有倍数：d, 2d, 3d...
        // 这一步的总执行次数是 X/1 + X/2 + X/3 ... = X ln X，完美符合时间限制！
        for (int k = d; k < MAX_X; k += d) {
            cnt += freq[k];
        }

        // --- 致命除法守卫 && 容斥公式 ---
        // 从 cnt 个能被 d 整除的数中选出 2 个的组合数： C(cnt, 2)
        if (cnt >= 2) {
            ll pairs = cnt * (cnt - 1) / 2; 
            ans += mu[d] * pairs; // 根据莫比乌斯函数的奇加偶减性质，自动进行容斥加减！
        }
    }

    cout << ans << "\n";
    return 0;
}

// void get_primes_euler(int n) {
//     cnt = 0;
//     for(int i = 2; i <= n; i++) {
//         if(!st[i]) primes[cnt++] = i;
//         for(int j = 0; primes[j] * i <= n; j++ ) {
//             st[primes[j] * i] = true;
//             if(i % primes[j] == 0) break;
//         } 
//     }
// }


#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1000000;

int main() {
    vector<int> total(N + 1);

    int n;
    cin >> n;
    ll answer = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        vector<int> factors;
        for (int f = 2; f * f <= x; f++) {
            if (x % f == 0) {
                factors.push_back(f);
                while (x % f == 0) x /= f;
            }
        }
        if (x != 1) factors.push_back(x);

        int k = factors.size();
        for (int b = 1; b < (1 << k); b++) {
            int prod = 1;
            for (int i = 0; i < k; i++) {
                if (b & (1 << i)) prod *= factors[i];
            }

            int add = total[prod];
            // == 0 时偶数个质因子，容斥系数为 +1；== 1 时奇数个质因子，容斥系数为 -1
            if (__builtin_parity(b) == 0) add = -add;
            answer += add;
            total[prod]++;
        }
    }

    cout << (n * ll(n - 1) / 2) - answer << "\n";
}