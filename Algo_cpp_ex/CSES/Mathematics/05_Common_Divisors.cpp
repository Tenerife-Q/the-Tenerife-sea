/*
第 5 题：Common Divisors (CSES - 1081)

题目大意：
给定 n 个正整数，你需要从这 n 个数中选出两个数，使得它们的最大公约数（GCD）最大。
数据范围：2 ≤ n ≤ 2e5，每个整数 1 ≤ x_i ≤ 1e6。

思路与详解（反向思维 + 调和级数）：

1) 直观的正向穷举：枚举所有对 (i,j) 并计算 GCD，时间 O(n^2)，对于 n=2e5 必然 TLE。

2) 破局之道：逆向枚举 GCD 值 g。
   - 设 cnt[v] 为值 v 在数组中出现的次数。
   - 如果某个 g 存在至少两个数组元素为 g 的倍数，那么 g 有资格成为候选 GCD。
   - 只需从大到小枚举 g，统计其倍数 g,2g,3g,... 在数组中出现的总次数，若 >=2 则直接输出 g（因为倒序枚举，第一个满足的即为最大）。

3) 复杂度分析：
   - 枚举所有 g 的倍数总工作量为 X * (1 + 1/2 + 1/3 + ... + 1/X) ≈ X log X，其中 X = 1e6（题目上界）。
   - 实际操作约 1.4e7 次，加上 I/O 优化，C++ 可瞬间完成。

4) 代码（ICPC 竞赛友好、可盲打）：
*/

#include <iostream>
#include <vector>

using namespace std;

// 题目给定的最大值 10^6
const int MAX_X = 1000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> cnt(MAX_X + 5, 0);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x; cnt[x]++;
    }

    for (int g = MAX_X; g >= 1; --g) {
        int multiples_count = 0;
        for (int k = g; k <= MAX_X; k += g) {
            multiples_count += cnt[k];
            if (multiples_count >= 2) {
                cout << g << '\n';
                return 0;
            }
        }
    }

    return 0;
}

/*
教练话语总结：
这道题的核心是“枚举答案并验证”的逆向思维，结合调和级数的复杂度分析将原本 O(n^2) 的问题转化为 O(X log X) 的可行算法。
掌握此类贡献/倒序枚举技巧，对后续的数论题（如 Sum of Divisors、Common Divisors 的变体）极其重要。
*/





#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    for (int i = N; i >= 1; i--) {
        int total = 0;
        for (int j = i; j <= N; j += i) {
            total += count[j];
        }
        if (total >= 2) {
            cout << i << "\n";
            break;
        }
    }
}




#include <iostream>
#include <vector>

using namespace std;

// 定义最大可能的值域 10^6
const int N = 1000000;

int main() {
    // 【优化 1：Fast I/O】
    // 斩断 cin/cout 和 stdio 的同步，极大地提升大规模数据的读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 桶数组：记录每个数值出现的次数
    // 局部 vector 自动分配在堆区，N+1 防越界，默认初始化为 0
    vector<int> count(N + 1, 0);

    int n;
    // 即使在没有更多输入的情况下，这种写法也能防止意外
    if (!(cin >> n)) return 0;

    // 读入所有数字并放入对应值域的“桶”中
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    // 【核心算法：逆向枚举最大公约数】
    // 从最大的可能公约数 N 开始往下枚举，第一个找到的满足条件的必然是最大的
    for (int i = N; i >= 1; i--) {
        int total = 0;
        
        // 枚举 i 的所有倍数 j
        for (int j = i; j <= N; j += i) {
            total += count[j]; // 累加该倍数在原数组中出现的次数
            
            // 【优化 2：Early Exit (提早剪枝)】
            // 只要凑够 2 个，说明存在两个数的最大公约数是 i
            // 立刻输出，并直接结束整个程序，拒绝后续无效的加法！
            if (total >= 2) {
                cout << i << "\n";
                return 0; 
            }
        }
    }

    return 0;
}