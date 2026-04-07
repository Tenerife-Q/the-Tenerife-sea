# Stick Game

## Problem Description
Consider a game where two players remove sticks from a heap. The players move alternately, and the player who removes the last stick wins the game.
A set $P=\{p_1,p_2,\ldots,p_k\}$ determines the allowed moves. For example, if $P=\{1,3,4\}$, a player may remove 1, 3 or 4 sticks.
Your task is find out for each number of sticks $1,2,\dots,n$ if the first player has a winning or losing position.

考虑一个游戏：两名玩家轮流从一堆棍子中取走棍子。取走最后一根棍子的玩家获胜。
一个集合 $P=\{p_1,p_2,\ldots,p_k\}$ 决定了允许的取法。例如，如果 $P=\{1,3,4\}$，那么玩家每次只能取走 1、3 或 4 根棍子。
你的任务是找出当初始棍子数量为 $1,2,\dots,n$ 时，先手玩家是处于必胜态还是必败态。

## Input
The first input line has two integers $n$ and $k$: the number of sticks and moves.
The next line has $k$ integers $p_1,p_2,\dots,p_k$ that describe the allowed moves. All integers are distinct, and one of them is 1.

第一行输入包含两个整数 $n$ 和 $k$：棍子的总数 $n$ 与可用取法的数量 $k$。
第二行包含 $k$ 个整数 $p_1,p_2,\dots,p_k$，描述了允许取走的棍子数量。所有的整数都互不相同，并且其中必须有一个是 1。

## Output
Print a string containing $n$ characters: `W` means a winning position, and `L` means a losing position.

输出一个包含 $n$ 个字符的字符串：对于每种棍子数量，`W` 表示先手必胜态，`L` 表示先手必败态。

## Constraints
$1 \le n \le 10^6$
$1 \le k \le 100$
$1 \le p_i \le n$

## Example
**Input:**
```
10 3
1 3 4
```

**Output:**
```
WLWWWWLWLW
```


这是一道非常经典的**组合博弈论（Combinatorial Game Theory）**和**动态规划（Dynamic Programming）**的基础题。

下面我将从题目大意、核心逻辑、算法设计、样例推导以及代码实现五个方面为你进行详细解析。

---

### 一、 题目大意
**游戏规则**：有两个玩家轮流从一堆石子（或木棍）中取走一定数量的石子。每次可以取走的数量必须在给定的集合 $P = \{p_1, p_2, \dots, p_k\}$ 中。取走最后一根木棍的玩家获胜。
**输入**：木棍总数 $n$，以及允许取走的数量集合 $P$（其中一定包含 $1$）。
**输出**：对于从 $1$ 到 $n$ 的每一个初始木棍数，判断先手是处于**必胜态（W）**还是**必败态（L）**，输出一个长度为 $n$ 的字符串。

---

### 二、 核心逻辑（博弈论基础）
在公平组合游戏中，所有的状态可以分为两类：
1. **必胜态 (W - Winning Position)**：**只要存在一种合法的移动**，能够把局面变成“必败态”交给对手，那么当前局面就是必胜态。
2. **必败态 (L - Losing Position)**：**无论采取哪种合法的移动**，都会把“必胜态”交给对手，那么当前局面就是必败态。

**边界条件（Base Case）**：
* 当木棍数量为 $0$ 时，当前玩家无法进行任何操作，直接输掉游戏。所以 $0$ 个木棍是**必败态 (L)**。

---

### 三、 算法设计（动态规划）
由于我们需要求出 $1 \dots n$ 所有状态的结果，且大状态依赖于小状态，因此非常适合用**动态规划（DP）**来求解。

* **状态定义**：设 `dp[i]` 表示当有 $i$ 根木棍时，先手的胜负状态。`true` 表示必胜 (W)，`false` 表示必败 (L)。
* **初始化**：`dp[0] = false` （0个木棍是必败态）。
* **状态转移方程**：
  对于当前的木棍数 $i$，我们遍历集合 $P$ 中的每一个取法 $p_j$：
  如果存在某个 $p_j \le i$，使得 `dp[i - p_j] == false`，那么 `dp[i] = true`（找到了一条通往对手必败的路径，当前必胜）。
  如果遍历完所有的 $p_j$，都没有发现 `dp[i - p_j] == false`，则说明无论怎么取，留给对手的都是必胜态，那么 `dp[i] = false`。

* **复杂度分析**：
  外层循环遍历 $1 \dots n$，内层循环遍历 $k$ 个操作。
  时间复杂度：$O(n \times k)$。本题 $n \le 10^6, k \le 100$，最大运算量约为 $10^8$ 次，在C++ 1.00s 的时间限制内完全可以AC。
  空间复杂度：$O(n)$，用于存储DP数组。

---

### 四、 样例推导
**输入**：`n = 10`，`P = {1, 3, 4}`

| i (木棍数) | 可以转移到的状态 `(i - p_j)` | 转移状态的胜负 | 结论 `dp[i]` |
| :--- | :--- | :--- | :--- |
| **0** | (无) | - | **L** (初始化) |
| **1** | $1-1 = 0$ | $0$是**L** | **W** |
| **2** | $2-1 = 1$ | $1$是W | **L** |
| **3** | $3-1 = 2$, **$3-3 = 0$** | $2$是L, **$0$是L** | **W** (能到0) |
| **4** | $4-1=3, 4-3=1,$ **$4-4=0$** | $3$是W, $1$是W, **$0$是L** | **W** (能到0) |
| **5** | $5-1=4,$ **$5-3=2$**, $5-4=1$ | $4$是W, **$2$是L**, $1$是W| **W** (能到2) |
| **6** | $6-1=5, 6-3=3,$ **$6-4=2$** | $5$是W, $3$是W, **$2$是L**| **W** (能到2) |
| **7** | $7-1=6, 7-3=4, 7-4=3$ | $6$是W, $4$是W, $3$是W | **L** (全为W)|
| **8** | **$8-1=7$**, $8-3=5, 8-4=4$ | **$7$是L**, $5$是W, $4$是W | **W** (能到7)|
| **9** | $9-1=8,$ **$9-3=6$**, $9-4=5$ | $8$是W, **$6$是W** (等等，这里有错吗？再看 $9-1=8(W), 9-3=6(W), 9-4=5(W)$ 全部是W，所以9是L) | **L** (全为W)|
| **10** | **$10-1=9$**, $10-3=7, 10-4=6$| **$9$是L**, $7$是L, $6$是W | **W** (能到9)|

拼起来：1到10的结果为 `W L W W W W L W L W`，与样例输出完全一致！

---

### 五、 C++ 代码实现

这里提供一个高效且简洁的 C++ 代码模板。为了稍微优化一点常数时间，我们可以对 $P$ 数组进行排序，一旦发现 $p_j > i$ 就提前 `break`，因为后续的 $p_j$ 更大，肯定也不合法。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // 优化输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> p(k);
    for (int i = 0; i < k; i++) {
        cin >> p[i];
    }

    // 排序是为了在DP时可以提前break优化常数
    sort(p.begin(), p.end());

    // dp[i] 表示面对 i 根木棍时，先手是否必胜
    vector<bool> dp(n + 1, false);
    dp[0] = false; // 0根木棍必败

    string ans = "";

    // 递推 1 到 n 根木棍的状态
    for (int i = 1; i <= n; i++) {
        bool isWin = false;
        // 尝试每一种合法的取法
        for (int j = 0; j < k; j++) {
            if (i - p[j] < 0) {
                break; // 如果要取的木棍数大于剩余木棍数，直接结束内循环
            }
            // 如果取走 p[j] 后，留给对手的是必败态(false)
            if (!dp[i - p[j]]) {
                isWin = true; // 那么当前状态就是必胜态
                break;        // 只要找到一种必胜策略即可，无需继续尝试
            }
        }
        dp[i] = isWin;
        
        // 拼接答案
        if (dp[i]) {
            ans += 'W';
        } else {
            ans += 'L';
        }
    }

    // 输出最终结果
    cout << ans << "\n";

    return 0;
}
```

### 总结
这道题是学习**一维动态规划**和**基础博弈论**的完美结合点。掌握了 `当前必胜态 ↔ 能转移到至少一个必败态` 和 `当前必败态 ↔ 只能转移到必胜态` 这一核心思想，就能轻松解决大量类似的变种博弈题（例如 Nim 游戏的 SG 函数推导也源于此）。