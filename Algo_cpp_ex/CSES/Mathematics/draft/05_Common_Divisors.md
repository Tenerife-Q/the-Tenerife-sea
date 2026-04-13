# Common Divisors

## Problem Description
Given an array of $n$ positive integers. Your task is to find two integers such that their greatest common divisor (GCD) is as large as possible.

给定一个包含 $n$ 个正整数的数组，你需要从中选出两个数，使得它们的最大公约数（GCD）最大。

## Input
The first input line contains an integer $n$: the size of the array.
The second line has $n$ integers $x_1, x_2, \ldots, x_n$: the contents of the array.

第一行包含一个整数 $n$：数组的大小。
第二行包含 $n$ 个整数 $x_1, x_2, \ldots, x_n$：数组的内容。

## Output
Print the maximum greatest common divisor.

输出最大的最大公约数。

## Constraints
* $2 \le n \le 2 \cdot 10^5$
* $1 \le x_i \le 10^6$

## Example
**Input:**
```text
5
3 14 15 7 9
```

**Output:**
```text
7
```
*(Explanation: The two numbers $14$ and $7$ share a greatest common divisor of $7$.)*

---

## 核心考点与算法剖析

这道题是数论中的经典题，极大考验了选手的**逆向思维（Reverse Thinking）**和对**调和级数（Harmonic Series）**复杂度模型的掌握。

### 一、 为什么不能正向穷举？(Brute Force 分析)
最直观的想法是：枚举数组中所有的数对 $(x_i, x_j)$，然后使用欧几里得算法 $O(\log(\min(x_i, x_j)))$ 计算它们的最大公约数，最后取最大值。
- **时间复杂度**：选出两对的数量级是 $O(n^2)$。当 $n = 2 \cdot 10^5$ 时，$n^2 = 4 \cdot 10^{10}$。
- **结论**：这必然会导致**超时 (TLE)**，因为竞赛通常要求运算量在 $10^8$ 左右。

### 二、 破局之道：逆向思维枚举答案
与其去问“这两个特定数字的 GCD 是多少？”，我们不如反过来问：
**“对于某一个假定的公约数 $g$，在原数组中有没有至少两个数是它的倍数？”**

只要数组中存在至少两个数是 $g$ 的倍数，那么 $g$ 就**有资格**成为一个合法的公约数。
既然要求**最大**公约数，我们只需要把可能的 $g$ 值从大到小（即从值域的上限 $X = 10^6$ 开始往下）枚举。第一个满足“存在至少两个倍数”的 $g$，毫无疑问就是最大的 GCD！

---

## 数学原理推导与时间复杂度证明

### 算法流程：
1. **开桶计数**：设定一个频数数组 `count`，大小为 $X+1$（$X$ 为数字最大值 $10^6$）。遍历输入数组，将每个元素的出现次数记录在 `count` 里。
2. **倒序验证**：令候选约数 $i$ 从 $X$ 递减到 $1$。
3. **倍数累加**：对于当前的 $i$，我们去统计它的所有倍数（$i, 2i, 3i, 4i \dots$）在数组中出现的总次数 `total`。
   $$total = count[i] + count[2i] + count[3i] + \dots$$
4. **提前终结**：如果在累加过程中发现 $total \ge 2$，立刻停止程序并输出 $i$。

### 时间复杂度证明：
外层循环变量 $i$ 会从 $X$ 遍历到 $1$。
内层循环变量 $j$ 每次以步长 $i$ 进行递增，即 $i, 2i, 3i, \dots, \lfloor \frac{X}{i} \rfloor \cdot i$。
因此，内层循环对于给定的 $i$ 会执行 $\lfloor \frac{X}{i} \rfloor$ 次。

总循环执行次数 $S$ 计算如下：
$$S = \sum_{i=1}^{X} \left\lfloor\frac{X}{i}\right\rfloor \approx X \sum_{i=1}^{X} \frac{1}{i}$$

正如我们在前一道题《Counting Divisors》中论证过的，连加的部分构成**调和级数 (Harmonic Series)**，其渐进和趋近于 $\ln X + C$。
$$S \approx X \cdot \ln{X}$$

- **时间复杂度**：$O(X \log X)$，这里 $X \le 10^6$。代入数据计算约执行 $10^6 \times 13.81 \approx 1.38 \cdot 10^7$ 次循环。配合提早剪枝，甚至远远跑不满，C++ 可以瞬间通过。
- **空间复杂度**：$O(X)$，预开一个大小为 $10^6$ 的 `vector` 计数器即可。

---

## 极致优化的代码实现与细节讲解

在这里我们给出不仅能 AC，还能打败大部分同行的究极可盲打 ICPC 模板代码：

```cpp
#include <iostream>
#include <vector>

using namespace std;

// 定义最大可能的值域 10^6 (由题目条件决定)
const int N = 1000000;

int main() {
    // 【优化 1：Fast I/O】
    // 斩断 cin/cout 和 stdio 的同步，极大地提升大规模数据的读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 桶数组：记录每个数值出现的次数
    // N+1 防越界，默认初始化为 0
    vector<int> count(N + 1, 0);

    int n;
    // 保护性输入，避免由于测试数据末尾格式奇异而崩溃
    if (!(cin >> n)) return 0;

    // 读入所有数字并放入对应值域的“桶”中
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    // 【核心算法：逆向倒序枚举最大公约数 i】
    // 从最大的可能公约数 N 开始往下枚举，第一个找到满足条件的，必然是“最大”的
    for (int i = N; i >= 1; i--) {
        int total = 0;
        
        // 枚举 i 的所有倍数 j (j = i, 2i, 3i...)
        for (int j = i; j <= N; j += i) {
            total += count[j]; // 累加该倍数在原数组中出现的频次
            
            // 【优化 2：Early Exit (提早剪枝)】
            // 只要凑够 2 个，说明存在两个数的最大公约数是此时的 i
            // 立刻输出，并直接整个程序 return 0; 
            // 拒绝后续由于无效的加法带来的性能浪费！
            if (total >= 2) {
                cout << i << "\n";
                return 0; 
            }
        }
    }

    return 0;
}
```

### 教练话语总结
这道题是展现**“以值域为锚点进行状态反串”**与**“调和级数分析模型”**最经典的例题之一。将 $O(n^2)$ 的两两暴力关系匹配，转换为 $O(X \log X)$ 空间换时间的集合属性查找，是通关后续无数进阶数论题 (如 Sum of Divisors, Coprime Arrays 等) 的核心心法！