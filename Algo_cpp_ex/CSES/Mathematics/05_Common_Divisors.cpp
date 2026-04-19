/*
 * @Problem: Common Divisors
 * @Source: CSES - Mathematics
 * 
 * @Description (English):
 * Given an array of n positive integers, your task is to find two integers such that their greatest common divisor is as large as possible.
 * 
 * @Description (Chinese):
 * 给定包含 n 个正整数的数组，你的任务是从中找出两个整数，使得它们的最大公约数（GCD）尽可能大。
 * 
 * @Input:
 * The first input line has an integer n: the size of the array.
 * The second line has n integers x_1,x_2,\ldots,x_n: the contents of the array.
 * 第一行输入包含一个整数 n：数组的大小。
 * 第二行包含 n 个整数 x_1,x_2,\ldots,x_n：数组的内容。
 * 
 * @Output:
 * Print the maximum greatest common divisor.
 * 输出最大的最大公约数。
 * 
 * @Constraints:
 * 2 <= n <= 2 * 10^5
 * 1 <= x_i <= 10^6
 * 
 * @Example:
 * Input:
 * 5
 * 3 14 15 7 9
 * 
 * Output:
 * 7
 * 
 * @Algorithm:
 * Reverse Thinking / Harmonic Series (逆向枚举 / 调和级数筛法)
 * 复杂度：O(X log X)，其中 X=10^6 为值域上界。
 * 思路：破局之道在于逆向枚举 GCD 值 g。统计倍数出现次数，倒序从大到小枚举，第一个遇见的满足倍数个数 >=2 次的即为最优解。
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
            return 0;//标答是break; 但我觉得直接return更好，直接结束程序，拒绝后续无效的加法！
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


#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }
    for(int i = N; i >= 1; i--) {
        int total = 0;
        for(int j = i; j <= N; j += i) {
            total += count[j];
            if(total >= 2) {
                cout << i << "\n";
                return 0;
            }
        }
    }
}