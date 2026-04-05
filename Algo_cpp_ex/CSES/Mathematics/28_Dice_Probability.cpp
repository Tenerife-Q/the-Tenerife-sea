/**
 * ============================================================================
 * CSES - Dice Probability
 * ============================================================================
 * 
 * [ENGLISH VERSION]
 * ─────────────────
 * Time limit: 1.00 s
 * Memory limit: 512 MB
 * 
 * You throw a dice n times, and every throw produces an outcome between 1 and 6. 
 * What is the probability that the sum of outcomes is between a and b?
 * 
 * Input:
 *   - The only input line contains three integers n, a and b.
 * 
 * Output:
 *   - Print the probability rounded to six decimal places (rounding half to even).
 * 
 * Constraints:
 *   - 1 ≤ n ≤ 100
 *   - 1 ≤ a ≤ b ≤ 6n
 * 
 * Example:
 *   Input:  2 9 10
 *   Output: 0.194444
 * 
 * ─────────────────────────────────────────────────────────────────────────
 * 
 * [中文版本]
 * ─────────
 * 时间限制: 1.00 秒
 * 内存限制: 512 MB
 * 
 * 投掷一个骰子 n 次，每次投掷产生 1 到 6 之间的一个结果。
 * 求所有投掷结果之和在 a 和 b 之间（包含 a 和 b）的概率是多少？
 * 
 * 输入：
 *   - 唯一的一行输入包含三个整数 n, a 和 b。
 * 
 * 输出：
 *   - 打印概率，保留六位小数。
 * 
 * 约束：
 *   - 1 ≤ n ≤ 100
 *   - 1 ≤ a ≤ b ≤ 6n
 * 
 * 样例：
 *   输入：  2 9 10
 *   输出：  0.194444
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <iomanip> // 用于格式化浮点数输出

using namespace std;

int main() {
    // 优化输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;
    if (!(cin >> n >> a >> b)) return 0;

    // dp[i][j] 表示投掷 i 个骰子后，点数之和为 j 的概率
    // i 的最大值是 n，j 的最大值是 6 * n
    vector<vector<double>> dp(n + 1, vector<double>(6 * n + 1, 0.0));

    // 初始状态 (Base Case)
    // 投掷 0 个骰子，和为 0 的概率是 100% (即 1.0)
    dp[0][0] = 1.0;

    // 动态规划：外层循环遍历骰子个数 1 到 n
    for (int i = 1; i <= n; i++) {
        // 中层循环遍历当前可能产生的所有点数和
        // i 个骰子的和最小是 i，最大是 6 * i
        for (int j = i; j <= 6 * i; j++) {
            // 内层循环遍历当前第 i 个骰子可能投出的点数 (1 到 6)
            for (int k = 1; k <= 6; k++) {
                // 如果前 i-1 个骰子的点数和合法 (大于等于 0)
                if (j - k >= 0) {
                    // 全概率公式累加
                    dp[i][j] += dp[i - 1][j - k] / 6.0;
                }
            }
        }
    }

    // 计算最终结果：把 [a, b] 范围内的概率加起来
    double result = 0.0;
    for (int j = a; j <= b; j++) {
        result += dp[n][j];
    }

    // 输出结果，保留 6 位小数
    cout << fixed << setprecision(6) << result << "\n";

    return 0;
}


#include <iostream>
using namespace std;

const int N = 100;
double p[N + 1][6 * N + 1];

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    p[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i; j <= 6 * i; j++) {
            for (int k = 1; k <= 6; k++) {
                p[i + 1][j + k] += p[i][j] / 6;
            }
        }
    }

    double answer = 0;
    for (int i = a; i <= b; i++) {
        answer += p[n][i];
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}