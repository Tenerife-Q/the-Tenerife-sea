/*
 * @Author: 
 * @Date: 2026-04-02
 * @LastEditors: 
 * @LastEditTime: 
 * @Description: 26. Sum of Four Squares / 四平方和
 * 
 * --------------------------------------------------------
 * Time limit: 1.00 s
 * Memory limit: 512 MB
 * 
 * A well known result in number theory is that every non-negative integer can be represented as the sum of four squares of non-negative integers.
 * 数论中一个著名的结果是，每个非负整数都可以表示为四个非负整数的平方和（拉格朗日四平方和定理）。
 * 
 * You are given a non-negative integer n. Your task is to find four non-negative integers a, b, c and d such that n = a^2 + b^2 + c^2 + d^2.
 * 给定一个非负整数 n。你的任务是找到四个非负整数 a, b, c 和 d，使得 n = a^2 + b^2 + c^2 + d^2 成立。
 * 
 * Input / 输入
 * The first line has an integer t: the number of test cases.
 * 第一行有一个整数 t：测试用例的数量。
 * 
 * Each of the next t lines has an integer n.
 * 接下来的 t 行中，每行有一个整数 n。
 * 
 * Output / 输出
 * For each test case, print four non-negative integers a, b, c and d that satisfy n = a^2 + b^2 + c^2 + d^2.
 * 对于每一个测试用例，打印满足 n = a^2 + b^2 + c^2 + d^2 的四个非负整数 a, b, c 和 d。
 * 
 * Constraints / 约束条件
 * 1 <= t <= 1000
 * 0 <= n <= 10^7
 * the sum of all n is at most 10^7 / 所有 n 的总和最多为 10^7
 * 
 * Example / 样例
 * Input:
 * 3
 * 5
 * 30
 * 322266
 * 
 * Output:
 * 2 1 0 0
 * 1 2 3 4
 * 314 159 265 358
 * --------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX_N = 10000000;
// sq1[i] 保存使得 i = a^2 + b^2 成立的某一个 a 值。
// 如果 i 不能被表示为两个平方数之和，则 sq1[i] 为 -1。
int sq1[MAX_N + 5];

void precompute() {
    // 将数组初始化为 -1
    memset(sq1, -1, sizeof(sq1));
    
    // 遍历所有可能的 a 和 b，使得 a^2 + b^2 <= 10^7
    // i * i 甚至不需要跑到 10^7，只需跑到 sqrt(10^7) 即 ~3162 即可
    for (long long a = 0; a * a <= MAX_N; ++a) {
        // b 从 a 开始，避免重复计算 (比如 a=1,b=2 和 a=2,b=1)
        for (long long b = a; a * a + b * b <= MAX_N; ++b) {
            sq1[a * a + b * b] = (int)a; 
        }
    }
}

void solve() {
    int n;
    cin >> n;
    
    // 枚举第一部分的和 i (相当于 a^2 + b^2)
    // 只需枚举到 n / 2 即可，因为 i 和 n-i 是对称的
    for (int i = 0; i <= n / 2; ++i) {
        int left_part = i;
        int right_part = n - i;
        
        // 如果两部分都能由两个平方数组成
        if (sq1[left_part] != -1 && sq1[right_part] != -1) {
            // 提取 left_part 的 a 和 b
            int a = sq1[left_part];
            int b = round(sqrt(left_part - a * a));
            
            // 提取 right_part 的 c 和 d
            int c = sq1[right_part];
            int d = round(sqrt(right_part - c * c));
            
            cout << a << " " << b << " " << c << " " << d << "\n";
            return; // 找到一组解后立即返回
        }
    }
}

int main() {
    // 加速 C++ 输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // 1. 程序启动时，先进行一次性预处理
    precompute();
    
    // 2. 处理所有查询
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}



// 空间换时间
#include <iostream>
#include <vector>
using namespace std;

// 题目规定的 n 的最大值 10^7
const int N = 10000000;

// 把数组开在全局变量区（堆区），防止爆栈
// can[x] 为 true 表示 x 可以表示为两个数的平方和
bool can[N + 1];
// first[x] 和 second[x] 记录具体的这两个数
int first_num[N + 1];
int second_num[N + 1];

void precompute() {
    // a 从 0 开始，a^2 不超过 N
    for (int a = 0; a * a <= N; a++) {
        // 优化点 1：b 从 a 开始枚举，避免 1^2+2^2 和 2^2+1^2 的重复计算
        for (int b = a; a * a + b * b <= N; b++) {
            int x = a * a + b * b;
            can[x] = true;
            first_num[x] = a;
            second_num[x] = b;
        }
    }
}

int main() {
    // 优化点 3：解除 C++ 输入输出的绑定，极大地提升读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 程序一开始，先打表预处理
    precompute();

    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            
            // 2. 核心逻辑：n = x + (n - x)
            // 优化点 2：只需遍历到 n / 2 即可，因为后面是对称的
            for (int x = 0; x <= n / 2; x++) {
                if (can[x] && can[n - x]) {
                    // x 拆出来的 a 和 b
                    cout << first_num[x] << " " << second_num[x] << " ";
                    // (n-x) 拆出来的 c 和 d
                    cout << first_num[n - x] << " " << second_num[n - x] << "\n";
                    break; // 找到后立即退出循环
                }
            }
        }
    }
    return 0;
}


/*
#include <iostream>
#include <vector>
using namespace std;

const int N  = 10000000;
bool can[N + 1];
int first[N + 1];
int second[N + 1];

void precompute() {
    for (int a = 0; a * a <= N; a++) {
        for (int b = a; a * a + b * b <= N; b++) {
            int x = a * a + b * b;
            can[x] = true;
            first[x] = a;
            second[x] = b;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            for (int x = 0; x <= n / 2; x++) {
                if (can[x] && can[n - x]) {
                    cout << first[x] << " " << second[x] << " " ;
                    cout << first[n - x] << " " << second[n - x] << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}
*/
