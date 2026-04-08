# Stair Game

## Problem Description
There is a staircase consisting of $n$ stairs, numbered $1,2,\dots,n$. Initially, each stair has some number of balls.
There are two players who move alternately. On each move, a player chooses a stair $k$ where $k \neq 1$ and it has at least one ball. Then, the player moves any number of balls from stair $k$ to stair $k-1$. The player who moves last wins the game.
Your task is to find out who wins the game when both players play optimally.
Note that if there are no possible moves at all, the second player wins.

有一个由 $n$ 级台阶组成的楼梯，编号为 $1,2,\dots,n$。最初，每级台阶上都有一定数量的小球。
有两名轮流行动的玩家。在每一步行动中，玩家选择一个至少有一个小球的台阶 $k$（其中 $k \neq 1$）。然后，该玩家将任意数量的小球从台阶 $k$ 移动到台阶 $k-1$。最后移动的玩家赢得游戏。
你的任务是找出在双方都采用最优策略的情况下，谁会赢得游戏。
注意，如果一开始没有任何合法的移动，则后手玩家获胜。

## Input
The first input line has an integer $t$: the number of tests. After this, $t$ test cases are described:
The first line contains an integer $n$: the number of stairs.
The next line has $n$ integers $p_1,p_2,\dots,p_n$: the initial number of balls on each stair.

第一行输入包含一个整数 $t$：测试用例的数量。之后描述 $t$ 个测试用例：
每个用例的第一行包含一个整数 $n$：台阶的数量。
下一行包含 $n$ 个整数 $p_1,p_2,\dots,p_n$：每级台阶上初始的小球数量。

## Output
For each test, print "first" if the first player wins the game and "second" if the second player wins the game.

对于每个测试用例，如果先手玩家获胜则输出 "first"，如果后手玩家获胜则输出 "second"。

## Constraints
$1 \le t \le 2 \cdot 10^5$
$1 \le n \le 2 \cdot 10^5$
$0 \le p_i \le 10^9$
the sum of all $n$ is at most $2 \cdot 10^5$

## Example
**Input:**
```
3
3
0 2 1
4
1 1 1 1
2
5 3
```

**Output:**
```
first
second
first
```


太牛了！你已经不知不觉刷到了博弈论中极其著名的一个进阶模型——**阶梯博弈（Staircase Nim）**。

如果你看懂了上一题中“学人精（镜像模仿）”和“黑洞（无效操作）”的概念，这道题你会觉得**爽到飞起**。因为它完全就是这两个概念的终极融合！

我们直接来扒掉这道题的底裤。

---

### 一、 核心结论（一秒破题）

别管它有多少级台阶，也别管上面的球怎么挪来挪去。
**你只需要把所有【偶数台阶】（第2、4、6、8...级）上的球的数量，全部异或起来！**
*   **异或和 $\neq 0$**：先手必胜（`first`）。
*   **异或和 $= 0$**：后手必胜（`second`）。

【奇数台阶】（第1、3、5、7...级）上的球？**全是障眼法，连看都不用看！**

---

### 二、 为什么？（底层逻辑：垃圾桶与学人精）

这道题的规则是：把球从第 $k$ 级挪到第 $k-1$ 级。最后挪不了的人输。
我们给这些台阶重新起个名字，你瞬间就能秒懂：

#### 1. 第 1 级台阶 = “垃圾桶”
题目说球挪到第 1 级就不能再动了。这意味着什么？
这意味着第 1 级台阶就是一个**“无底垃圾桶”**。任何球只要掉进这里，就等同于在游戏里**被彻底销毁了**。

#### 2. 第 2 级台阶 = “标准 Nim 游戏”
如果球在第 2 级，你一挪，它就掉进第 1 级（垃圾桶）销毁了。
这不就是标准的 Nim 游戏吗？**“从第 2 级挪走 $x$ 个球”，完美等价于“从石子堆里拿走 $x$ 颗石子扔掉”。**

#### 3. 第 3 级台阶 = “无用的障眼法”（学人精大显身手）
如果球在第 3 级，有人把它挪到了第 2 级。这相当于给第 2 级的 Nim 堆**增加**了石子！
等一下，标准的 Nim 游戏是不允许增加石子的，这怎么算？

这时候，**“学人精”防守策略**登场了！
假设你是高手，局面原本是必胜的。对手气急败坏，把 5 个球从第 3 级推到了第 2 级，企图打乱你的计划。
你该怎么做？
**你只需要当个“学人精快递员”，在你的回合，立刻把这 5 个球从第 2 级推到第 1 级（垃圾桶）里去！**

你看，对手从奇数推到偶数，你就顺手从偶数推到奇数（垃圾桶）。这一套连招下来，第 2 级台阶上的球数**根本没有变化**！对手白白浪费了一回合，而局面的胜负态完全没有改变。

#### 4. 推广到所有台阶
*   **偶数台阶（2, 4, 6...）**：把球从这里推到奇数台阶，就等于把球推进了“中转垃圾桶”。对手无法阻止。这才是**真正有杀伤力的 Nim 堆**。
*   **奇数台阶（1, 3, 5...）**：把球从这里推到偶数台阶，对手永远可以当“学人精”，立刻把这些球再推下一级。所以，奇数台阶上的球，**对胜负毫无影响，全是废球**。

**终极等效：**
这个花里胡哨的阶梯游戏，**完美等价于：只有偶数台阶上存在的普通 Nim 游戏！**

---

### 三、 样例推导验证

我们用你的“新眼睛”去看看题目的三个样例。

**Test 1**:
*   `n = 3`，台阶球数：`0 2 1` (分别是第1、2、3级)
*   只看偶数台阶：第 2 级有 `2` 个球。
*   异或和：`2`。不为 0。
*   **结果**：`first`。（一秒出答案，完全不需要管第3级的那个球）

**Test 2**:
*   `n = 4`，台阶球数：`1 1 1 1`
*   只看偶数台阶：第 2 级有 `1` 个，第 4 级有 `1` 个。
*   异或和：`1 ^ 1 = 0`。
*   **结果**：`second`。

**Test 3**:
*   `n = 2`，台阶球数：`5 3`
*   只看偶数台阶：第 2 级有 `3` 个。
*   异或和：`3`。不为 0。
*   **结果**：`first`。

样例全中，且毫无计算压力！

---

### 四、 C++ 代码实现

代码极致简单。因为只有偶数台阶有用，我们在读入的时候，只需要判断台阶的编号是不是偶数，如果是，就把它异或起来。

```cpp
#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    int xor_sum = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        // 核心魔法：只关注偶数级台阶！
        if (i % 2 == 0) {
            xor_sum ^= x;
        }
    }
    
    if (xor_sum != 0) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
}

int main() {
    // 快速 I/O 依然是处理大规模测试用例的必需品
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
```

### 五、 总结提升

这道题叫做 **Staircase Nim（阶梯博弈）**，是组合博弈论中除了普通 Nim 之外考得最多的变形之一。

它教会了我们博弈论中极为重要的一种降维思想：**寻找可抵消的操作**。

在复杂的博弈游戏中，很多操作看起来能改变状态，但如果这种操作能被对手**无损镜像复原**（就像把奇数台阶的球推到偶数，对手能立刻把它推回奇数），那么这种操作就是**伪操作**，产生这种操作的石子就是**废石子**。

把伪操作和废石子全部剔除，极其复杂的游戏瞬间就会现出它的原形——一个最基础的异或 Nim 游戏！