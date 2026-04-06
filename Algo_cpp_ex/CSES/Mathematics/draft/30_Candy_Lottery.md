# Candy Lottery

## Problem Description
There are n children, and each of them independently gets a random integer number of candies between 1 and k.
What is the expected maximum number of candies a child gets?

有 $n$ 个孩子，每个孩子都会独立地随机获得一个 1 到 $k$ 范围内的整数个糖果。
求所有孩子中获得的最多糖果数的期望值是多少？

## Input
The only input line contains two integers n and k.

唯一的一行输入包含两个整数 $n$ 和 $k$。

## Output
Print the expected number rounded to six decimal places (rounding half to even).

输出期望值，保留六位小数（四舍六入五成双）。

## Constraints
$1 \le n \le 100$
$1 \le k \le 100$

## Example
**Input:**
```
2 3
```

**Output:**
```
2.444444
```

这道题是 CSES 题库里一道非常经典的**离散概率与期望数学题**。

和上一道题不同，这道题不需要用到复杂的 DP（动态规划）或者巨大的全局数组。这道题的精髓在于**一个极其优雅的概率论数学推导**。只要你想通了这个数学逻辑，代码连 20 行都不到，而且完全不需要开数组。

下面我为你抽丝剥茧，一步步推导这道题。

---

### 1. 题目大意
* 有 $n$ 个小孩。
* 每个小孩都会**独立地、随机地**获得 $1$ 到 $k$ 颗糖果。（获得 $1, 2, \dots, k$ 的概率都是相等的，即 $1/k$）。
* **问题：** 求这 $n$ 个小孩中，**拿到最多糖果数量**（即最大值）的**期望值**。

**例子分析 ($n=2, k=3$)：**
有 2 个小孩，糖果数是 1 到 3。
小孩 A 和 B 的糖果组合 (A, B) 共有 $3 \times 3 = 9$ 种情况：
(1,1)->最大1; (1,2)->最大2; (1,3)->最大3
(2,1)->最大2; (2,2)->最大2; (2,3)->最大3
(3,1)->最大3; (3,2)->最大3; (3,3)->最大3
总共有：1 个“最大1”，3 个“最大2”，5 个“最大3”。
期望值 = $(1\times1 + 2\times3 + 3\times5) / 9 = 22 / 9 \approx 2.444444$。与样例输出完美吻合。

---

### 2. 核心数学思想：如何求最大值的概率？

根据期望的定义：
$$ E[\text{最大值}] = \sum_{x=1}^{k} x \cdot P(\text{最大值恰好等于 } x) $$

现在的难点是：**怎么算“最大值恰好等于 $x$”的概率？**

如果直接算“恰好等于 $x$”，非常麻烦，因为你需要保证至少有一个小孩拿到 $x$，且其他小孩不能超过 $x$。

**这里有一个概率论中求最大值的标准套路（破局点）：**
不要直接求“恰好等于 $x$”，而是先求**“最大值小于等于 $x$ ($\le x$)”**的概率！

**第一步：求最大值 $\le x$ 的概率**
如果这 $n$ 个小孩手中的最大值 $\le x$，这意味着什么？
**意味着：每一个小孩拿到的糖果数都 $\le x$。**
因为每个小孩是独立的：
* 1 个小孩拿到 $\le x$ 颗糖的概率是 $\frac{x}{k}$。
* $n$ 个小孩**都**拿到 $\le x$ 颗糖的概率，就是把它们乘起来：
$$ P(\text{最大值 } \le x) = \left(\frac{x}{k}\right)^n $$

**第二步：用差分求“恰好等于 $x$”的概率**
既然我们知道了“$\le x$”的概率，也知道了“$\le x-1$”的概率。
那么：
$$ P(\text{恰好等于 } x) = P(\text{最大值 } \le x) - P(\text{最大值 } \le x-1) $$
这就好比，考 60 分以下的有一大波人，考 59 分以下的也有一大波人。两者一减，剩下的就是**恰好考了 60 分**的人。

代入公式：
$$ 
  P(\text{最大值恰好 } = x) = \left(\frac{x}{k}\right)^n - \left(\frac{x-1}{k}\right)^n 
$$

**第三步：算出期望**
把上面的概率代入期望公式，搞定！
$$
 E = \sum_{x=1}^{k} x \cdot \left[ \left(\frac{x}{k}\right)^n - \left(\frac{x-1}{k}\right)^n \right] 
$$

---

### 3. 代码实现与防溢出技巧

这道题有了公式之后，代码极其简单，只需要一个 for 循环。
但是在写代码时，有一个**致命的细节（也是算法竞赛中常见的坑）**：

**错误写法：** `pow(x, n) / pow(k, n)`
为什么错？如果 $n=100, x=100$，$100^{100}$ 是一个天文数字，C++ 中的 `double` 最大只能存大概 $10^{308}$，虽然这里没爆，但如果再大一点点就会产生巨大的精度丢失甚至上溢（Overflow）。

**正确写法：** `pow((double)x / k, n)`
我们先把 $x/k$ 算出来，这是一个位于 $[0, 1]$ 之间的小数。小数不管怎么做次方，结果都还在 $[0, 1]$ 之间，**绝对不会溢出**，而且精度极高。

### 4. C++ 标答代码

```cpp
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
```

### 总结

1. **题目不需要数组：** 就像我上一条回答提到的，竞赛中如果需要存状态就开“全局大数组”。但面对这种**纯数学推导题**，连数组都不需要开，时间复杂度 $O(k)$，空间复杂度 $O(1)$。
2. **记住这个黄金概率模型：** 在概率题中，**求最大值的期望**，永远不要直接去硬算“等于某个数”的组合，而是转化为求 **“所有人都 $\le x$” 的概率减去 “所有人都 $\le x-1$” 的概率**。这个技巧在面试和算法竞赛中会反复出现！
