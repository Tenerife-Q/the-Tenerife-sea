# Counting Divisors

## Problem Description
Given $Q$ queries, each provides an integer $X$. For each $X$, output the number of divisors of $X$.

给定 $Q$ 个查询，每个查询给出一个整数 $X$。对每个 $X$，输出 $X$ 的约数个数。

## Input
The first input line contains an integer $Q$: the number of queries.
After this, there are $Q$ lines, each containing an integer $X$.

第一行输入包含一个整数 $Q$，表示查询次数。
接下来 $Q$ 行：每行一个整数 $X$。

## Output
For each query, print the number of divisors of $X$.

对每个查询输出一行，表示 $X$ 的约数个数。

## Constraints
* $1 \le Q \le 10^5$
* $1 \le X \le 10^6$

## Example
**Input:**
```text
3
16
17
18
```

**Output:**
```text
5
2
6
```

---

## 核心考点与算法剖析

求解一个数的约数个数是一个非常经典的数论基础问题。在不同的数据范围博弈下，我们需要选取不同的策略。下面将详细介绍三种最常用的求解“约数个数”的算法，从数学原理到代码实现进行全面讲解。

### 赛场终极总结（什么时候用哪个方法？）
1. **若 $X$ 较小 ($X \le 10^7$) 且查询次数 $Q$ 极大 ($Q \ge 10^5$)**：
    👉 秒选 **【方法三：调和级数筛法】**。预处理 $O(X \log X)$，单次查询 $O(1)$，空间换时间的极致！**(本题的最优解)**。
2. **若 $X$ 极大 (如 $10^{12}$) 且查询次数 $Q$ 较小 (如 $100$)**：
    👉 选 **【方法二：配对试除法】** 或 **【方法一：质因数分解法】**。由于内存开不出 $10^{12}$ 的数组，只能对每个数进行 $O(\sqrt{X})$ 暴力计算。
3. **若不仅求“约数个数”，还要算“约数之和”**：
    👉 **【方法一：质因数分解法】** 有直接对应的数学求和公式，拓展性最强。

---

### 方法一：质因数分解法 (基于算术基本定理 / 唯一分解定理)

**数学原理推导：**
根据算术基本定理，任何一个大于 $1$ 的自然数 $N$ 都可以唯一地分解成质数的乘积形式：
$$N = p_1^{a_1} \times p_2^{a_2} \times \dots \times p_k^{a_k}$$
其中 $p_i$ 是质数，$a_i$ 是非负整数指数。
因为 $N$ 的任意一个约数 $d$ 必定可以表示为:
$$d = p_1^{b_1} \times p_2^{b_2} \times \dots \times p_k^{b_k}$$
其中对于所有的质因子 $p_i$，其约数中的指数受限于 $N$ 中的最高次幂，即满足 $0 \le b_i \le a_i$。
对于 $p_1$，它的指数 $b_1$ 有 $a_1 + 1$ 种可能的选择（从 $0$ 到 $a_1$）。根据**排列组合中的乘法原理**，所有不同质因子的可能取法乘在一起，得到正约数的总个数公式：
$$\text{Divisors Count} = (a_1 + 1) \times (a_2 + 1) \times \dots \times (a_k + 1)$$

**时间复杂度证明：**
在进行质因子分解时，我们只需枚举到 $\lfloor \sqrt{N} \rfloor$ 即可。原因在于，**一个数 $N$ 最多拥有一个严格大于 $\sqrt{N}$ 的素因子**。
*反证法：假设 $N$ 有两个质因子 $u, v$，且 $u > \sqrt{N}$ 和 $v > \sqrt{N}$，那么 $u \times v > \sqrt{N} \times \sqrt{N} = N$，但这与 $u, v$ 都是 $N$ 的因子矛盾。*
因此，当我们用 $O(\sqrt{N})$ 扫过前置范围后，如果剩下的数除净后仍 $> 1$，它就是这唯一一条“大尾巴质数”，它的次幂必为 $1$。
单次查询时间复杂度：$O(\sqrt{X})$。总时间复杂度：$O(Q \sqrt{X})$。
> **ICPC 避雷针**：千万别在内部开 `unordered_map` 或 `map` 来统计指数！哈希常数极大，会导致 TLE！直接用一个普通的循环变量累计 `count` 即可。

**代码实现：**
```cpp
long long get_divisors_count(int n) {
    long long res = 1;
    // 技巧：i * i <= n 防止除法运算由于常数开销导致效率降低
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int count = 0; // 记录当前质因数 p_i 的指数 a_i
            while (n % i == 0) {
                n /= i;
                count++;
            }
            res = res * (count + 1); // 乘法原理套用：*(a_i + 1)
        }
    }
    // 特判：剩下的那个大于 sqrt(n) 的质因子（最多只有一个），它的常数次幂为 1
    if (n > 1) res = res * (1 + 1); 
    return res;
}
```

---

### 方法二：$O(\sqrt{X})$ 暴力配对试除法

**数学原理推导：**
约数总是**成双成对**出现的。
假设有一数字 $k$ 属于 $X$ 的约数（即 $k \mid X$），那么显然可以得到一个与之配对的约数 $p = \frac{X}{k}$，使得 $k \times p = X$。
由于一对约数 $k, p$ 满足 $k \times p = X$，那么必定有以下三种情况之一：
1. $k < \sqrt{X}$ 且 $p > \sqrt{X}$
2. $k = p = \sqrt{X}$ （当 $X$ 为完全平方数）
3. $k > \sqrt{X}$ 且 $p < \sqrt{X}$

由此可见，如果存在一个大于 $\sqrt{X}$ 的约数，它必然早在这个因数小于 $\sqrt{X}$ 时就在配对中被发现了！因此，搜索范围被严格限制在了闭区间 $[1, \lfloor \sqrt{X} \rfloor]$ 里。我们每碰到一个 $k$，就能立即得到 $X/k$ 作为第二个约数直接计入。

**时间复杂度证明：**
枚举恰好执行 $\lfloor \sqrt{X} \rfloor$ 次大循环，内部 `if` 判定均是常数极低的 $O(1)$ 级四则运算。
单次查询纯时间复杂度：$O(\sqrt{X})$。总时间复杂度：$O(Q \sqrt{X})$。
> **ICPC 避雷针**：必须特判 $k = X/k$ 的情况（即完全平方数 $X = k^2$。例如 $X=16$ 时，因子 $4$ 会配对给出另一个因数 $4$），防止同一对因子因为值相同被错误地算作两个不同的约数！

**代码实现：**
```cpp
int count(int x) {
    int c = 0;
    for (int k = 1; k * k <= x; k++) {
        if (x % k == 0) {
            c++; // 约小半边的因子 k 
            if (k != x / k) {
                c++; // 约大半边的因子 x/k (特判防重)
            }
        }
    }
    return c;
}
```

---

### 方法三：调和级数筛法 (Harmonic Sieve) - 本题最优解

前两种方法在面对查询量 $Q = 10^5$ 和 $X = 10^6$ 的极限数据时，总运算次数会逼近 $Q \cdot \sqrt{X} = 10^5 \times 10^3 = 10^8$，很容易被卡在超时的边缘。为了做到极致的效率，我们可以彻底抛包并转换思路：采用**空间换时间，一次预处理全局打表**的策略。

**数学原理及算法思路转换：**
原来的暴力查询思路属于**正向询问**：“对于每一个询问 $X$，我怎样去寻找能整除你的数？”
调和级数筛法属于“我全都要的”**逆向散播**：“我让 $i$ 遍历 $1 \dots X$，然后我就散播给所有的 $i$ 的倍数们（$j = i, 2i, 3i, \dots$），宣告我 $i$ 是你们每个人的约数，你们的约数总数全部统统 $+1$！”

**时间复杂度推导：**
因为算法里有两个循环嵌套（外层 $i$，内层 $j$）。我们需要准确计算内层循环在这个过程中到底**总共执行了多少次**：
- 当 $i=1$ 时，内层执行了 $\lfloor\frac{X}{1}\rfloor$ 次。
- 当 $i=2$ 时，内层执行了 $\lfloor\frac{X}{2}\rfloor$ 次。
- 当 $i=k$ 时，内层执行了 $\lfloor\frac{X}{k}\rfloor$ 次。
总的操作执行次数 $S$ 为：
$$S = \sum_{i=1}^{X} \left\lfloor\frac{X}{i}\right\rfloor \approx X \sum_{i=1}^{X} \frac{1}{i}$$

注意到右边就是大名鼎鼎的**调和级数（Harmonic Series）**！根据高等数学相关的极限与积分公式可知：
$$\sum_{i=1}^{X} \frac{1}{i} = \ln{X} + C$$
（其中 $\ln$ 随 $X$ 的增长速度比自然对数稍大，且 $C \approx 0.5772 \dots$ 为欧拉-马斯刻若尼常数）。
因此总体计算的执行次数 $S \approx X \cdot \ln{X} \approx O(X \log X)$。

* **预处理时间复杂度：** $O(X \log X)$。对于 $X = 10^6$，其实仅仅只运行了 $10^6 \times 13.8155 \approx 1381 万$ 次循环体，在现代 C++（每秒 3 亿次量级起步）耗时只要短短十几毫秒就能完成构建！
* **单次查询时间复杂度：** 查数组寻址，天然无条件 $O(1)$！
* **整体时间复杂度：** $O(X \log X + Q)$。此方案完美粉碎一切题目中的常数和查询限制。

**代码实现：**
```cpp
#include <iostream>
#include <vector>

using namespace std;

// 预处理的最大值：10^6 (题目给定的 x 最大值)
const int MAX_X = 1000000;

// d[i] 记录数字 i 的约数个数
// 全局变量默认初始化为 0
int d[MAX_X + 5];

// 调和级数筛法预处理
// 必须在处理任何输入前调用！
void precompute() {
    // 外层循环：枚举可能成为约数的数字 i
    for (int i = 1; i <= MAX_X; i++) {
        // 内层循环：枚举 i 的倍数 j (j = i, 2i, 3i...)
        // 既然 i 能整除 j，那么 j 的约数个数就要 +1
        for (int j = i; j <= MAX_X; j += i) {
            d[j]++;
        }
    }
}

int main() {
    // ICPC 竞程必备 IO 优化：解除 C/C++ 缓冲同步，极大提升读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 第一步：在处理任何查询前，先打表预处理！(耗时约十几毫秒)
    precompute();

    int n;
    cin >> n;
    
    // 第二步：O(1) 极速回应每次查询，绝不超时
    while (n--) {
        int x;
        cin >> x;
        cout << d[x] << "\n";
    }

    return 0;
}
```