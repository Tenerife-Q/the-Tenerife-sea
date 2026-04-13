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

这道题是数论中的经典算法题。从暴力的 $O(n^2)$ 到进阶的 $O(n \sqrt{X})$，再到最优的调和级数 $O(X \log X)$，完美展现了算法的时间复杂度渐进优化过程，极大考验了选手的**逆向思维（Reverse Thinking）**。

### 方法一：暴力正向穷举 (Brute Force) - 必然 TLE
最直观的想法是：枚举数组中所有的数对 $(x_i, x_j)$，然后使用欧几里得算法计算它们的最大公约数，最后取全体组合中的最大值。
- **时间复杂度**：选出两对的数量级是 $O(n^2)$。求解单次 GCD 为 $O(\log X)$。总时间复杂度为 $O(n^2 \log X)$。由于 $n = 2 \cdot 10^5$，显然 $n^2 = 4 \cdot 10^{10}$。
- **评测结论**：运算量远超普通 CPU 每秒 $10^8 \sim 10^9$ 次的极限，这必然会导致**严重超时 (TLE)**。

### 方法二：正向因子分解计数法 - $O(n \sqrt{X})$ - 勉强 / 卡常 AC 边缘
既然两两组合不行，第二种思路是**单独拆解每一个数字**。
- **核心逻辑**：基于前一题提到的理论，一个数 $x_i$ 所有的约数都可以用 $O(\sqrt{X})$ 的试除法对偶求出。我们可以遍历输入数组的**每一个数** $x_i$，用 $O(\sqrt{X})$ 找出它所有的约数，并将这些约数在一个全局频率数组 `cnt[d]` 中频次 $+1$。全部遍历完成后，我们**从大到小**（$X \dots 1$）去检查 `cnt` 数组。第一个满足 `cnt[d] >= 2` 的最大公约数 $d$，必然就是所求的最优解。
- **时间复杂度**：求解每一个数字的所有因子需要 $O(\sqrt{x_i})$，一共 $n$ 个数，时间为 $O(n \sqrt{X})$。最后扫描一次值域需要 $O(X)$。总时间复杂度为 $O(n \sqrt{X} + X)$。
- **评测结论**：当 $n = 2 \cdot 10^5$ 且 $X = 10^6$ 时，$n\sqrt{X} = 2 \cdot 10^5 \times 10^3 = 2 \cdot 10^8$。这个计算量在竞赛 $1.0s$ 时限内恰好处于“擦边球”的危险边缘。若 `#pragma GCC optimize("O3")` 等常数优化做得好或许能 AC，但稍有不慎或是数据刁钻依然会 TLE。

### 方法三：逆向思维与调和级数筛法 - $O(X \log X)$ - 降维打击，本题最优解
与其每次都去问“你这 $10^6$ 到底有哪几个特定的因子？”，我们不如倒转矛头反推：
**“对于某一个假定的公约数 $g$，在原数组中有没有至少两个数是它的倍数？”**

只要数组中存在至少两个数是 $g$ 的倍数，那么 $g$ 就**有资格**成为一个合法的公约数。
既然要求**最大**公约数，我们只需要把可能的 $g$ 值从大到小（即从值域的上限 $X = 10^6$ 开始往下）枚举。第一个由于自己倍数“凑够了这两人”的 $g$，毫无疑问就是全体数组中能拿出的最大的 GCD！

---

## 算法流程与时间复杂度推导 (针对最优解法三)

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