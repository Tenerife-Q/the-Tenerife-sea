# CSES 26 - Sum of Four Squares (四平方和) 深度解析

这道题是非常著名的数学定理：**拉格朗日四平方和定理 (Lagrange's Four-Square Theorem)**，该定理指出：**任何一个非负整数都可以表示为四个整数的平方和**。

虽然数学上保证了必然有解，但如果在代码中使用四个嵌套的 `for` 循环暴力枚举 $a, b, c, d$，时间复杂度会达到 $\mathcal{O}(n^2)$（因为每个变量最大到 $\sqrt{n}$），对于最大 $n = 10^7$ 来说绝对会超时（TLE）。

下面为你提供一种**非常优雅且极速**的预处理解法，并详细讲解其背后的算法思想。

---

### 💡 核心思路：折半查找 (Meet in the Middle)

既然直接找四个数太慢，我们可以把公式拆成两半：

$$n = (a^2 + b^2) + (c^2 + d^2)$$

令 $X = a^2 + b^2$，$Y = c^2 + d^2$。
则问题转化为了：**寻找两个数 $X$ 和 $Y$，使得 $X + Y = n$，并且 $X$ 和 $Y$ 都可以表示为两个完全平方数之和。**

#### 🚀 第一步：预处理 (Precomputation)
题目提示“所有测试用例的 $n$ 之和不超过 $10^7$”，最大值 $n \le 10^7$。这强烈暗示我们可以开辟一个数组，提前把 $\le 10^7$ 的所有“两数平方和”记录下来。

我们创建一个数组 `sq1[10000001]`，初始值全设为 `-1`。
* 如果某个数 $k$ 能表示为 $a^2 + b^2$，我们就把 $a$ 的值记录在 `sq1[k]` 中，即 `sq1[k] = a`。
* 这样一来，给定一个 $k$，只要 `sq1[k] \neq -1`，我们就立刻知道它符合要求，且其中一个数是 $a = sq1[k]$，另一个数 $b$ 直接可以通过 $b = \sqrt{k - a^2}$ 算出来！

#### 🚀 第二步：极速查询 (O(1) 级别)
给出目标 $n$ 后，我们只需用一个循环枚举 $X$ (从 $0$ 到 $n/2$)：
* 令 $Y = n - X$。
* 检查 `sq1[X]` 和 `sq1[Y]` 是否都不是 `-1`。
* 如果都不是 `-1`，说明找到了！直接输出对应的 $a, b, c, d$ 即可跳出。

---

### 💻 C++ 满分解法代码

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX_N = 10000000;
// sq1[i] 保存使得 i = a^2 + b^2 成立的某一个 a 值。
// 如果 i 不能被表示为两个平方数之和，则 sq1[i] 为 -1。
int sq1[MAX_N + 5];

void precompute() {
    // 将数组初始化为 -1
    memset(sq1, -1, sizeof(sq1));
    
    // 遍历所有可能的 a 和 b，使得 a^2 + b^2 <= 10^7
    // i * i 甚至不需要跑到 10^7，只需跑到 sqrt(10^7) 即 ~3162 即可
    for (long long a = 0; a * a <= MAX_N; ++a) {
        // b 从 a 开始，避免重复计算 (比如 a=1,b=2 和 a=2,b=1)
        for (long long b = a; a * a + b * b <= MAX_N; ++b) {
            sq1[a * a + b * b] = (int)a; 
        }
    }
}

void solve() {
    int n;
    cin >> n;
    
    // 枚举第一部分的和 i (相当于 a^2 + b^2)
    // 只需枚举到 n / 2 即可，因为 i 和 n-i 是对称的
    for (int i = 0; i <= n / 2; ++i) {
        int left_part = i;
        int right_part = n - i;
        
        // 如果两部分都能由两个平方数组成
        if (sq1[left_part] != -1 && sq1[right_part] != -1) {
            // 提取 left_part 的 a 和 b
            int a = sq1[left_part];
            int b = round(sqrt(left_part - a * a));
            
            // 提取 right_part 的 c 和 d
            int c = sq1[right_part];
            int d = round(sqrt(right_part - c * c));
            
            cout << a << " " << b << " " << c << " " << d << "\n";
            return; // 找到一组解后立即返回
        }
    }
}

int main() {
    // 加速 C++ 输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // 1. 程序启动时，先进行一次性预处理
    precompute();
    
    // 2. 处理所有查询
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
```

---

### 📊 复杂度与原理解析

1. **预处理时间复杂度：**
   `precompute()` 中的嵌套循环计算所有的 $a^2 + b^2 \le 10^7$。这相当于在一个半径为 $\sqrt{10^7}$ 的 $1/8$ 圆周区域内枚举整点。总循环次数约为 $\frac{\pi \times 10^7}{8} \approx 3.9 \times 10^6$ 次。对于现代 CPU 来说，几百万次运算只需要不到 `0.01` 秒，极其迅速。

2. **查询时间复杂度：**
   对于每个 $n$，最坏情况下循环看起来会跑到 $n/2$。但实际上，“可以表示为两数平方和的数”在数轴上的分布非常密集。**根据数学统计，往往在循环的最初几十次内就能必然碰到合法解。** 所以每次查询时间几乎可看作 $\mathcal{O}(1)$，即使查询 $1000$ 次也毫无压力。

3. **空间复杂度 (Memory Limit)：**
   题目给了奢侈的 `512 MB`。我们的核心是一个 `int` 数组 `sq1`，大小为 $10^7$。
   空间消耗为：$10^7 \times 4 \text{ Bytes} \approx 40 \text{ MB}$，完全在限制范围内。

4. **处理精度 (`sqrt` 与 `round`)**
   对于不超过 $10^7$ 的完美平方数，C++ 的 `sqrt(double)` 不会出现任何浮点精度丢失问题。配合 `round`（或者直接强转为 `int`），可以 $100\%$ 确保准确还原出另一个平方根 $b$ 和 $d$。