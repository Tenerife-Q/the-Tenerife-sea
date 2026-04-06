/*
Inversion Probability

An array has n integers x_1,x_2,...,x_n, and each of them has been randomly chosen between 1 and r_i. An inversion is a pair (a,b) where a<b and x_a>x_b.
What is the expected number of inversions in the array?

一个数组有 n 个整数 x_1,x_2,...,x_n，其中每个整数都是在 1 到 r_i 之间独立随机选择的。一个逆序对是指满足 a<b 且 x_a>x_b 的数据对 (a,b)。
求数组中逆序对的期望数量是多少？

Input
The first input line contains an integer n: the size of the array.
The second line contains n integers r_1,r_2,...,r_n: the range of possible values for each array position.
第一行输入包含一个整数 n：数组的大小。
第二行包含 n 个整数 r_1,r_2,...,r_n：数组每个位置可能的取值范围（即第 i 个数在 1 到 r_i 之间随机选择）。

Output
Print the expected number of inversions rounded to six decimal places (rounding half to even).
输出逆序对的期望数量，保留六位小数（四舍六入五成双）。

Constraints
1 <= n <= 100
1 <= r_i <= 100

Example
Input:
3
5 2 7

Output:
1.057143
*/

// #include <iostream>
// #include <vector>
// #include <iomanip>

// using namespace std;

// int main() {
//     // 竞速级 IO 优化
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n;
//     if (!(cin >> n)) return 0;
    
//     // 全局数组思想：由于 n <= 100 很小，用 vector 也很稳，
//     // 当然如果你写 int r[105]; 在外面也是极好的习惯。
//     vector<int> r(n);
//     for (int i = 0; i < n; i++) {
//         cin >> r[i];
//     }

//     double expected_inversions = 0.0;

//     // 两层循环，遍历所有可能的数字对 (i, j) 满足 i < j
//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
            
//             double favorable = 0;
            
//             if (r[i] <= r[j]) {
//                 // 情况 1：前者的范围较小
//                 favorable = (double)r[i] * (r[i] - 1) / 2.0;
//             } else {
//                 // 情况 2：前者的范围较大
//                 favorable = (double)r[j] * (r[j] - 1) / 2.0 + (double)(r[i] - r[j]) * r[j];
//             }
            
//             // 总的组合数
//             double total = (double)r[i] * r[j];
            
//             // 把这一对产生逆序对的概率累加到总期望中
//             expected_inversions += favorable / total;
//         }
//     }

//     // 保留 6 位小数输出
//     cout << fixed << setprecision(6) << expected_inversions << "\n";

//     return 0;
// }

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // 竞速级 IO 优化
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    vector<long double> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    // 必须使用 long double (80位/128位超高精度)
    long double expected_inversions = 0.0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            
            long double favorable = 0.0;
            
            if (r[i] <= r[j]) {
                // 注意这里的 1.0L 和 2.0L，带上 L 强制编译器不去做降维 double 计算
                favorable = r[i] * (r[i] - 1.0L) / 2.0L;
            } else {
                favorable = r[j] * (r[j] - 1.0L) / 2.0L + (r[i] - r[j]) * r[j];
            }
            
            long double total = r[i] * r[j];
            
            // 累加
            expected_inversions += favorable / total;
        }
    }

    // 完美契合出题人的输出结果
    cout << fixed << setprecision(6) << expected_inversions << "\n";

    return 0;
}