/*
Moving Robots

Each square of an 8 x 8 chessboard has a robot. Each robot independently moves k steps, and there can be many robots on the same square.
On each turn, a robot moves one step left, right, up or down, but not outside the board. It randomly chooses a direction among those where it can move.
Your task is to calculate the expected number of empty squares after k turns.

在一个 8 x 8 的棋盘上，每个方格中都有一个机器人。每个机器人独立移动 k 步，并且同一个方格上可以有多个机器人。
在每一回合中，一个机器人可以向左、向右、向上或向下移动一步，但不能移出棋盘。它会在它可以移动的方向中随机选择一个方向。
你的任务是计算 k 回合后空方格的期望数量。

Input
The only input line has an integer k.
包含一个整数 k。

Output
Print the expected number of empty squares rounded to six decimal places (rounding half to even).
输出 k 回合后空方格的期望数量，保留六位小数（四舍六入五成双）。

Constraints
1 <= k <= 100

Example
Input:
10

Output:
23.120740
*/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// 定义四个移动方向：下，上，右，左
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    if (!(cin >> k)) return 0;

    // empty_prob[x][y] 记录 (x, y) 格子最终没有机器人的概率
    // 初始状态下概率为 1.0 (因为我们要做乘法)
    vector<vector<double>> empty_prob(8, vector<double>(8, 1.0));

    // 遍历每一个机器人的初始位置 (sx, sy)
    for (int sx = 0; sx < 8; sx++) {
        for (int sy = 0; sy < 8; sy++) {
            
            // dp[x][y] 表示当前机器人当前步数在 (x, y) 的概率
            vector<vector<double>> dp(8, vector<double>(8, 0.0));
            dp[sx][sy] = 1.0; // 第0步在起点的概率为1

            // 模拟移动 k 步
            for (int step = 0; step < k; step++) {
                // next_dp 存储走下一步后在各个格子的概率
                vector<vector<double>> next_dp(8, vector<double>(8, 0.0));
                
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        if (dp[x][y] > 0) {
                            // 计算当前格子有多少个合法的移动方向
                            int valid_moves = 0;
                            for (int d = 0; d < 4; d++) {
                                int nx = x + dx[d];
                                int ny = y + dy[d];
                                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                                    valid_moves++;
                                }
                            }
                            
                            // 将当前格子的概率平分给相邻的合法格子
                            for (int d = 0; d < 4; d++) {
                                int nx = x + dx[d];
                                int ny = y + dy[d];
                                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                                    next_dp[nx][ny] += dp[x][y] / valid_moves;
                                }
                            }
                        }
                    }
                }
                // 滚动数组，将下一步的状态赋值给当前状态
                dp = next_dp;
            }

            // 对于目标格子 (x, y)，当前机器人最终不在 (x, y) 的概率是 (1.0 - dp[x][y])
            // 将所有 64 个机器人的情况乘起来
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    empty_prob[x][y] *= (1.0 - dp[x][y]);
                }
            }
        }
    }

    // 根据期望的线性性质，总空格数的期望等于各个格子为空的概率之和
    double expected_empty_squares = 0.0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            expected_empty_squares += empty_prob[x][y];
        }
    }

    // 按要求保留6位小数输出，C++ 的 fixed 默认使用的是四舍五入(严格说是 round half to even)
    cout << fixed << setprecision(6) << expected_empty_squares << "\n";

    return 0;
}




// 官方解法，使用了四维数组来存储每一步每个格子上机器人的概率，最后计算期望值。
#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
const int K = 100;
double p[K + 1][N * N][N][N];

int main() {
    int k;
    cin >> k;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            p[0][i * N + j][i][j] = 1;
        }
    }

    for (int m = 0; m < k; m++) {
        for (int r = 0; r < N * N; r++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    vector<pair<int, int>> moves;
                    // emplace_back 作用：在 vector 末尾添加元素，避免不必要的拷贝
                    if (i > 0) moves.emplace_back(i - 1, j);
                    if (j > 0) moves.emplace_back(i, j - 1);
                    if (i + 1 < N) moves.emplace_back(i + 1, j);
                    if (j + 1 < N) moves.emplace_back(i, j + 1);
                    double add = p[m][r][i][j] / moves.size();
                    for (auto d : moves) {
                        p[m + 1][r][d.first][d.second] += add;
                    }
                }
            }
        }
    }

    double answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double e = 1;
            for (int r = 0; r < N * N; r++) {
                e *= (1 - p[k][r][i][j]);
            }
            answer += e;
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";

    return 0;
}