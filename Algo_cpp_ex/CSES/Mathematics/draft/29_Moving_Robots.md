# Moving Robots

## Problem Description
Each square of an 8 \times 8 chessboard has a robot. Each robot independently moves k steps, and there can be many robots on the same square.
On each turn, a robot moves one step left, right, up or down, but not outside the board. It randomly chooses a direction among those where it can move.
Your task is to calculate the expected number of empty squares after k turns.

在一个 8 \times 8 的棋盘上，每个方格中都有一个机器人。每个机器人独立移动 k 步，并且同一个方格上可以有多个机器人。
在每一回合中，一个机器人可以向左、向右、向上或向下移动一步，但不能移出棋盘。它会在它可以移动的方向中随机选择一个方向。
你的任务是计算 k 回合后空方格的期望数量。

## Input
The only input line has an integer k.

包含一个整数 k。

## Output
Print the expected number of empty squares rounded to six decimal places (rounding half to even).

输出 k 回合后空方格的期望数量，保留六位小数（四舍六入五成双）。

## Constraints
$1 \le k \le 100$

## Example
**Input:**
```
10
```

**Output:**
```
23.120740
```

这是一道经典的**概率与期望 + 动态规划 (DP)** 的题目，出自 CSES 题库。下面我将为你详细分析这道题的解法，并提供清晰的讲解。

### 1. 题目分析

**题意简述：**
* 有一个 $8 \times 8$ 的国际象棋棋盘，一开始每个格子上都有一个机器人（共 64 个）。
* 每个机器人都会**独立地**移动 $k$ 步。多个机器人可以停留在同一个格子上。
* 每一步，机器人可以选择上、下、左、右四个方向之一移动，但不能走出棋盘。机器人会在**合法的方向中等概率随机选择**一个方向移动。（例如：在角落只有 2 个合法方向，每个方向概率为 $1/2$；在边界有 3 个合法方向，每个为 $1/3$；在中间有 4 个合法方向，每个为 $1/4$）。
* **目标：** 求出 $k$ 步之后，棋盘上**空格子**的期望数量。

**数据范围：**
* $1 \le k \le 100$
* 时间限制 $1.00s$

---

### 2. 核心数学思想：期望的线性性质 (Linearity of Expectation)

这道题如果直接去算“有 1 个空格的概率”、“有 2 个空格的概率”是极其复杂的，因为 64 个机器人的状态组合是个天文数字。

这里必须用到概率论中非常强大的工具——**期望的线性性质**：
$$ E[\text{总空格数}] = \sum_{S \in \text{所有格子}} P(\text{格子 } S \text{ 是空的}) $$
这句话的意思是：**我们不需要考虑全局的状态，只需要求出每一个特定格子最终是“空的”概率，然后把这 64 个格子的概率加起来，就是总空格数的期望值。**

---

### 3. 如何计算“某个格子是空的”概率？

题目提到：每个机器人是**独立移动**的。
一个格子 $S$ 最终是空的，意味着：
* 1 号机器人最后不在格子 $S$ 上
* **并且** 2 号机器人最后不在格子 $S$ 上
* ...
* **并且** 64 号机器人最后不在格子 $S$ 上

因为独立，所以“同时发生”的概率等于各自概率的乘积：
$$ P(\text{格子 } S \text{ 为空}) = \prod_{R=1}^{64} \Big(1 - P(\text{机器人 } R \text{ 最终走到格子 } S)\Big) $$

所以，问题的关键转化为：**求每一个机器人，在走 $k$ 步之后，停在某一个格子上的概率。**

---

### 4. 动态规划 (DP) 求解单机器人概率

对于某一个初始位置为 $(start\_x, start\_y)$ 的机器人，我们可以用 DP 来模拟它走 $k$ 步的概率分布。

**状态定义：**
设 `dp[step][x][y]` 表示该机器人走了 `step` 步之后，位于坐标 `(x, y)` 的概率。

**初始状态：**
第 0 步时，它肯定在起点：`dp[0][start_x][start_y] = 1.0`，其它位置全为 `0.0`。

**状态转移：**
对于第 `step` 步在 `(x, y)` 的概率 `dp[step][x][y]`，它可以平分给相邻的合法格子。
假设 `(x, y)` 有 `C` 个合法的相邻格子（`C` 可能是 2, 3, 4），那么对于它的每一个相邻合法格子 `(nx, ny)`：
`dp[step+1][nx][ny] += dp[step][x][y] / C`

走完 $k$ 步后，`dp[k][x][y]` 就是这个起始于 $(start\_x, start\_y)$ 的机器人最终停在 $(x, y)$ 的概率。

---

### 5. 算法整体流程

1. 初始化一个 $8 \times 8$ 的数组 `empty_prob[8][8]`，全部设为 `1.0`。这个数组用来存储每个格子最终为空的概率。
2. 遍历棋盘上 64 个格子的每一个作为起点 $(start\_x, start\_y)$（代表 64 个机器人）：
   * 对当前机器人做 $k$ 步的 DP，求出它最终停在各个格子 $(x, y)$ 的概率 `dp[x][y]`。
   * 遍历所有的格子 $(x, y)$，将它为空的概率乘上该机器人不到达这里的概率：
     `empty_prob[x][y] *= (1.0 - dp[x][y])`
3. 把所有的 `empty_prob[x][y]` 加起来，得到的结果就是期望的空格数。
4. 按要求保留 6 位小数输出。

**复杂度分析：**
* 64 个机器人。
* 每个机器人走 $k$ 步 ($k \le 100$)。
* 每一步更新 64 个格子。
* 总操作数大约是 $64 \times 100 \times 64 = 409,600$ 次运算。
这个计算量极其微小，在 1.0s 内瞬间就能跑完，所以算法非常高效。

---

### 6. C++ 代码实现与注释

```cpp
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
```

### 总结
1. **拆解目标**：将求“全局剩余空格”转化为求“单个格子为空”的概率之和。
2. **利用独立性**：将“单个格子为空”拆解为“64 个机器人都不来这个格子”的概率之积。
3. **状态模拟**：用 DP 枚举每个机器人的起点，求出走 $k$ 步的概率扩散分布图。 
这正是典型的“期望转概率”问题在算法竞赛中的完美应用。
