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

/*
做法1 精度缺失出错 具体看draft

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
*/


/*
做法2 使用了黄金期望等式：E = sum( 1 - (i/k)^n ) , i 从 0 到 k-1 但是还是有错
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // 使用 long double 保证绝不翻车
    long double expected_max = 0.0;

    // 根据黄金期望等式：E = sum( 1 - (i/k)^n ) , i 从 0 到 k-1
    for (int i = 0; i < k; i++) {
        // (long double) 强转保证除法和乘方在超高精度下进行
        expected_max += 1.0 - pow((long double)i / k, n);
    }

    // C++ 中 fixed + setprecision 默认就是题目要求的 rounding half to even (四舍六入五成双)
    cout << fixed << setprecision(6) << (double)expected_max << "\n";

    return 0;
}



// 换掉 pow() 函数，直接用循环乘法来计算 (i/k)^n，还是报错
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // 优化 IO 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    double expected_max = 0.0;

    // 黄金期望公式：E = sum( 1 - (i/k)^n )
    for (int i = 0; i < k; i++) {
        double p = 1.0;
        
        // 【核心修改】：用循环乘法代替 pow()，完美避开底层的精度丢失
        for (int j = 0; j < n; j++) {
            p *= (double)i / k;
        }
        
        expected_max += 1.0 - p;
    }

    // fixed 配合 setprecision(6) 自动执行银行家舍入
    cout << fixed << setprecision(6) << expected_max << "\n";

    return 0;
}
*/

// 没招了 都是错的
#include <bits/stdc++.h>

using namespace std;

int N, K;
double ans, a, b;

int main(){
    scanf("%d %d", &N, &K);
    for(int i = 1; i <= K; i++){
        a = b = 1.0;
        for(int j = 1; j <= N; j++){
            a *= (double) i / K;
            b *= (double) (i-1) / K;
        }
        ans += (a-b) * i;
    }
    printf("%.6f\n", ans);
}