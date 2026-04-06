# Inversion Probability

## Problem Description
An array has n integers $x_1,x_2,\dots,x_n$, and each of them has been randomly chosen between 1 and $r_i$. An inversion is a pair $(a,b)$ where $a<b$ and $x_a>x_b$.
What is the expected number of inversions in the array?

一个数组有 $n$ 个整数 $x_1,x_2,\dots,x_n$，其中每个整数都是在 $1$ 到 $r_i$ 之间独立随机选择的。一个逆序对是指满足 $a<b$ 且 $x_a>x_b$ 的数据对 $(a,b)$。
求数组中逆序对的期望数量是多少？

## Input
The first input line contains an integer $n$: the size of the array.
The second line contains $n$ integers $r_1,r_2,\dots,r_n$: the range of possible values for each array position.

第一行输入包含一个整数 $n$：数组的大小。
第二行包含 $n$ 个整数 $r_1,r_2,\dots,r_n$：数组每个位置可能的取值范围（即第 $i$ 个数在 $1$ 到 $r_i$ 之间随机选择）。

## Output
Print the expected number of inversions rounded to six decimal places (rounding half to even).

输出逆序对的期望数量，保留六位小数（四舍六入五成双）。

## Constraints
$1 \le n \le 100$
$1 \le r_i \le 100$

## Example
**Input:**
```
3
5 2 7
```

**Output:**
```
1.057143
```


经历了前两道题的洗礼，你现在已经来到了概率期望类题目中**最核心、最通用**的一块阵地。

这道题非常经典，它不再有变态的底层精度陷阱，而是纯粹考验你对**期望的线性性质 (Linearity of Expectation)** 的理解。只要想通了这一点，代码写起来如丝般顺滑。

下面我为你详细解析。

---

### 1. 题目大意
* 给定一个长度为 $n$ 的数组 $x_1, x_2, \dots, x_n$。
* 数组里的每一个元素 $x_i$，都是在 $1$ 到 $r_i$ 之间**等概率随机选取**的一个整数。
* **逆序对**的定义是：对于下标 $i$ 和 $j$，如果满足 $i < j$ 并且 $x_i > x_j$，这就叫一个逆序对。
* **问题：** 求这个数组中**逆序对数量的期望值**。

**例子分析 ($n=3$, 范围是 `5 2 7`)：**
* $x_1$ 在 1~5 随机
* $x_2$ 在 1~2 随机
* $x_3$ 在 1~7 随机

---

### 2. 核心魔法：期望的线性性质

如果把整个数组所有可能的组合都列出来，总共有 $5 \times 2 \times 7 = 70$ 种情况，然后算出每种情况有几个逆序对再求平均，当 $n$ 稍微大一点时，组合数直接变成天文数字（$100^{100}$），绝无可能算出来。

**这时候就要祭出我们的老朋友了：“总期望 = 部分概率之和”**。
我们不需要关注整个数组，**我们只需要盯住每一对数字！**

在一个长度为 $n$ 的数组中，总共有 $\frac{n(n-1)}{2}$ 对数字 $(x_i, x_j)$ 满足 $i < j$。
对于任意一对数字，它要么构成逆序对（记为 1），要么不构成（记为 0）。
$$ E[\text{总逆序对}] = \sum_{i < j} P(x_i > x_j) $$

这句话的意思是：**你只需要把每一对 $(x_i, x_j)$ 产生逆序对的概率算出来，然后全部加起来，就是最终的答案！**

---

### 3. 数学推导：求一对数字 $P(x_i > x_j)$ 的概率

现在问题变得极其简单：已知 $x_i \in [1, r_i]$，$x_j \in [1, r_j]$，求 $x_i > x_j$ 的概率。
总的情况数是 $r_i \times r_j$。我们只需要数一数有**多少种组合满足 $x_i > x_j$**。

这里分两种情况：

#### 情况 1：$r_i \le r_j$ （前面的数上限小）
比如 $x_i \in [1, 5]$，$x_j \in [1, 7]$。
* 如果 $x_i = 1$，能比它小的 $x_j$ 有 0 个。
* 如果 $x_i = 2$，能比它小的 $x_j$ 有 1 个（就是 1）。
* 如果 $x_i = 3$，能比它小的 $x_j$ 有 2 个。
* ...
* 如果 $x_i = r_i$，能比它小的 $x_j$ 有 $r_i - 1$ 个。

根据等差数列求和公式，满足条件的组合数（好情况数）为：
$$ \text{Favorable} = 0 + 1 + 2 + \dots + (r_i - 1) = \frac{r_i \times (r_i - 1)}{2} $$

#### 情况 2：$r_i > r_j$ （前面的数上限大）
比如 $x_i \in [1, 5]$，$x_j \in [1, 2]$。
我们把 $x_i$ 的取值砍成两半看：
* **前半段 ($x_i \le r_j$)：** 这里和情况1一模一样。比如 $x_i$ 取 1, 2 时，满足条件的组合数是 $\frac{r_j \times (r_j - 1)}{2}$。
* **后半段 ($x_i > r_j$)：** 比如 $x_i$ 取 3, 4, 5。这时候，因为 $x_i$ 已经超过了 $x_j$ 的最大范围，所以 $x_j$ **随便取什么（共 $r_j$ 个可能）**，必定满足 $x_i > x_j$。
这一部分 $x_i$ 共有 $(r_i - r_j)$ 个选择，每个选择有 $r_j$ 种好情况。

总的组合数为：
$$ \text{Favorable} = \frac{r_j \times (r_j - 1)}{2} + (r_i - r_j) \times r_j $$

#### 计算概率
把上面算出来的 $\text{Favorable}$ 除以总可能数 $r_i \times r_j$，就是这一对构成逆序对的概率。

---

### 4. 竞赛级代码实现

这道题没有任何大指数运算，只是普通的加减乘除，所以使用标准的 `double` 就能完美解决，没有上一题那样的惊悚陷阱。

```cpp
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
    
    // 全局数组思想：由于 n <= 100 很小，用 vector 也很稳，
    // 当然如果你写 int r[105]; 在外面也是极好的习惯。
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    double expected_inversions = 0.0;

    // 两层循环，遍历所有可能的数字对 (i, j) 满足 i < j
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            
            double favorable = 0;
            
            if (r[i] <= r[j]) {
                // 情况 1：前者的范围较小
                favorable = (double)r[i] * (r[i] - 1) / 2.0;
            } else {
                // 情况 2：前者的范围较大
                favorable = (double)r[j] * (r[j] - 1) / 2.0 + (double)(r[i] - r[j]) * r[j];
            }
            
            // 总的组合数
            double total = (double)r[i] * r[j];
            
            // 把这一对产生逆序对的概率累加到总期望中
            expected_inversions += favorable / total;
        }
    }

    // 保留 6 位小数输出
    cout << fixed << setprecision(6) << expected_inversions << "\n";

    return 0;
}
```

### 5. 总结升华
1. **彻底掌握“线性期望”：** 以后只要看到让你求“总体之和的期望”（比如求期望逆序对数、期望连通块数、期望空格子数），**第一反应必须是：将其拆分为局部的个体概率，分别求解后求和！**
2. **复杂度降维打击：** 原始问题看似是 $O(R^N)$ 的天文级别计算，通过线性期望拆解后，直接变成了求两点概率 $O(N^2)$ 的级别。
3. **安全计算：** 这道题的公式全都是加法和正数除法，规避了浮点数相减（`a - b`）的精度地雷，可以直接放心大胆写。