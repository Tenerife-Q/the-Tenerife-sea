/*
题目：Counting Divisors

描述（中）：给定 Q 个查询，每个查询给出一个整数 X（1 ≤ X ≤ 10^6），输出 X 的约数个数。

Description (EN): Given Q queries, each provides an integer X (1 ≤ X ≤ 10^6). For each X, output the number of divisors of X.

输入 (Input):
 - 第一行：整数 Q，表示查询次数（1 ≤ Q ≤ 1e5）。
 - 接下来 Q 行：每行一个整数 X（1 ≤ X ≤ 1e6）。

输出 (Output):
 - 对每个查询输出一行，表示 X 的约数个数。

示例 (Example):
输入:
3
16
17
18

输出:
5
2
6

关于 Q 与 X 的关系与复杂度：
 - 设 MAX_X 为 X 的上界（本题 MAX_X = 1e6）。使用“调和级数筛法”预处理需 O(MAX_X log MAX_X) 时间和 O(MAX_X) 内存，随后每次查询 O(1)。
 - 总时间：O(MAX_X log MAX_X + Q)。因此当 Q 很大且 MAX_X 不大时（例如本题），预处理法最优。
 - 若 X 很大（例如 1e12）且 Q 很小，使用每次 O(sqrt(X)) 的试除/质因数分解法更合适，总时间约 O(Q * sqrt(X))。
*/

/*
#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;

long long get_divisors_count(int n) {
    if(n == 1) return 1;
    unordered_map<int, int> primes;
    for(int i = 2; i <= n / i; i++) {
        while(n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if(n > 1) primes[n]++;

    long long res = 1;
    for (auto p : primes) {
        res = res * (p.second + 1);
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        int x;
        cin >> x;
        cout << get_divisors_count(x) << "\n";
    }
    return 0;
}
*/


/*
#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            count[j]++;
        }
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << count[x] << "\n";
    }
}
*/


/*
================================================================================
【ICPC 数论基础模板与思维剖析】：求约数个数 (Counting Divisors)
 核心考点：数据范围博弈、调和级数筛法、唯一分解定理、配对试除法
================================================================================

 🏆 赛场终极总结（什么时候用哪个方法？）：
 1. 若 X 较小 (<= 10^7)，查询次数 Q 极大 (>= 10^5)：
    👉 秒选【方法三：调和级数筛法】。预处理 O(X log X)，查询 O(1)，空间换时间的极致！(本题最优解)
 2. 若 X 极大 (如 10^12)，查询次数 Q 较小 (如 100)：
    👉 选【方法二：配对试除法】或【方法一：质因数分解法】。由于开不出 10^12 的数组，只能对每个数进行 O(sqrt(X)) 暴力算。
 3. 若不仅求“约数个数”，还要算“约数和”：
    👉 【方法一：质因数分解法】有直接对应的数学求和公式，拓展性极强。

================================================================================
【方法一：质因数分解法 (唯一分解定理)】- (已注释)
 数学原理：N = p1^a1 * p2^a2 * ... * pk^ak，约数个数 = (a1+1)*(a2+1)*...*(ak+1)
 复杂度：单次 O(sqrt(X))。
 ICPC 避雷针：千万别在内部开 unordered_map 统计指数！哈希常数极大，会导致 TLE！
================================================================================
long long get_divisors_count(int n) {
    long long res = 1;
    // 技巧：i * i <= n 防止除法带来的常数开销
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            int count = 0; // 记录当前质因子的指数
            while(n % i == 0) {
                n /= i;
                count++;
            }
            res = res * (count + 1); // 直接套公式
        }
    }
    // 特判：剩下的那个大于 sqrt(n) 的质数（如果存在）
    if(n > 1) res = res * 2; 
    return res;
}
*/


/*
================================================================================
【方法二：O(sqrt(X)) 暴力配对试除法】- (已注释)
 数学原理：约数总是成对出现的，如果 k 是 x 的约数，那 x/k 也是。
 复杂度：单次 O(sqrt(X))。
 ICPC 避雷针：必须特判 k == x/k 的情况（即完全平方数），防止将平方根计算两次！
================================================================================
int count(int x) {
    int c = 0;
    for (int k = 1; k * k <= x; k++) {
        if (x % k == 0) {
            c++; // 约数 k
            if (k != x / k) {
                c++; // 配对的约数 x/k
            }
        }
    }
    return c;
}
*/


/*
================================================================================
【方法三：调和级数筛法 (Harmonic Sieve)】- (本文件的激活代码，本题最优解)
 数学原理：反向思考，不问“x 有哪些约数”，而求“i 是哪些数的约数”。
 用 i 遍历 1~X，把 i 所有的倍数 (i, 2i, 3i...) 的约数个数全部 +1。
 复杂度：预处理 O(X log X)，单次查询 O(1)。
================================================================================
*/

#include <iostream>
#include <vector>

using namespace std;

// 预处理的最大值：10^6 (题目给定的 x 最大值)
const int MAX_X = 1000000;

// d[i] 记录数字 i 的约数个数
// 全局数组默认初始化为 0
int d[MAX_X + 5];

// 调和级数筛法预处理
// 必须在处理任何输入前调用！
void precompute() {
    // 外层循环：枚举可能成为约数的数字 i
    for (int i = 1; i <= MAX_X; i++) {
        // 内层循环：枚举 i 的倍数 j (j = i, 2i, 3i...)
        // 既然 i 能整除 j，那么 j 的约数个数就要 +1
        // 注意步长是 i，这就是为什么总循环次数是 X*(1 + 1/2 + 1/3 +...) = X log X
        for (int j = i; j <= MAX_X; j += i) {
            d[j]++;
        }
    }
}

int main() {
    // ICPC 竞程必备 IO 优化：解除 C/C++ 缓冲同步，极大提升读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 第一步：在处理任何查询前，先打表预处理！(耗时约十几毫秒)
    precompute();

    int n;
    cin >> n;
    
    // 第二步：O(1) 极速回应每次查询，绝不超时
    while (n--) {
        int x;
        cin >> x;
        cout << d[x] << "\n";
    }

    return 0;
}