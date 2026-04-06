/*
Candy Lottery

There are n children, and each of them independently gets a random integer number of candies between 1 and k.
What is the expected maximum number of candies a child gets?

有 n 个孩子，每个孩子都会独立地随机获得一个 1 到 k 范围内的整数个糖果。
求所有孩子中获得的最多糖果数的期望值是多少？

Input
The only input line contains two integers n and k.
唯一的一行输入包含两个整数 n 和 k。

Output
Print the expected number rounded to six decimal places (rounding half to even).
输出期望值，保留六位小数（四舍六入五成双）。

Constraints
1 <= n <= 100
1 <= k <= 100

Example
Input:
2 3

Output:
2.444444
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // 优化输入输出速度 (竞赛习惯)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    double expected_max = 0.0;

    // 枚举可能的最大值 x 从 1 到 k
    for (int x = 1; x <= k; x++) {
        // P(最大值 <= x)
        double p_le_x = pow((double)x / k, n);
        
        // P(最大值 <= x-1)
        double p_le_x_minus_1 = pow((double)(x - 1) / k, n);
        
        // P(最大值恰好等于 x)
        double p_exactly_x = p_le_x - p_le_x_minus_1;
        
        // 期望 E = sum(x * P(X = x))
        expected_max += x * p_exactly_x;
    }

    // 保留6位小数输出
    cout << fixed << setprecision(6) << expected_max << "\n";

    return 0;
}