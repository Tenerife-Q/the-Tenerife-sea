


没问题，CSES Mathematics 模块的第 12 道题是 **Distributing Apples**。

这道题在很多方面都与第 11 题 "Creating Strings II" 的核心思想（组合数学 + 乘法逆元取模）有着异曲同工之妙，不过它考察的是极其经典的**隔板法（Stars and Bars）**。

下面为你提供中英双语的题目描述、深入的代码解释分析，以及一份包含详尽注释的完整 C++ 满分代码。

---

### 🍏 Distributing Apples (分配苹果)

#### 📝 英文题目 (English Description)
There are $n$ children and $m$ apples that will be distributed to them. Your task is to count the number of ways this can be done.
For example, if $n=3$ and $m=2$, there are 6 ways: `[0,0,2]`, `[0,1,1]`, `[0,2,0]`, `[1,0,1]`, `[1,1,0]`, and `[2,0,0]`.

**Input**
The only input line has two integers $n$ and $m$.

**Output**
Print the number of ways modulo $10^9+7$.

**Constraints**
$1 \le n, m \le 10^6$

**Example**
Input: `3 2`
Output: `6`

#### 🇨🇳 中文题目 (Chinese Description)
有 $n$ 个孩子和 $m$ 个苹果，你需要将这些苹果分配给这些孩子。请计算有多少种不同的分配方式。
例如，如果 $n=3$ 且 $m=2$，有 6 种分配方式：`[0,0,2]`、`[0,1,1]`、`[0,2,0]`、`[1,0,1]`、`[1,1,0]` 和 `[2,0,0]`。

**输入**
唯一的一行包含两个整数 $n$ 和 $m$。

**输出**
输出不同的分配方式总数对 $10^9+7$ 取模的结果。

**数据范围**
$1 \le n, m \le 10^6$

**样例**
输入：`3 2`
输出：`6`

---

### 💡 题目分析与解法解释

#### 1. 经典组合数学模型：隔板法（Stars and Bars）
这道题要求我们将 $m$ 个相同的苹果分给 $n$ 个不同的孩子，且允许某个孩子分到 0 个苹果。
这对应了求方程的非负整数解个数：
$$ x_1 + x_2 + \dots + x_n = m \quad (x_i \ge 0) $$
我们可以用**隔板法**来解决这个问题。把 $m$ 个苹果想象成 $m$ 个星星（Stars）排列在一条直线上。为了将它们分成 $n$ 份（对应 $n$ 个孩子），我们需要在苹果之间插入 $n-1$ 块隔板（Bars）。
总共有 $m$ 个苹果和 $n-1$ 块隔板，它们的总位置数是 $m + n - 1$。
分配苹果的方案数就等同于**在这 $m + n - 1$ 个位置中，选出 $n - 1$ 个位置来放置隔板**的方法数（或者说选 $m$ 个位置放苹果）。

因此，答案就是组合数：
$$ 
\binom{n + m - 1}{n - 1} = \frac{(n + m - 1)!}{(n - 1)! \times m!} 
$$

例如，样例中 $n=3, m=2$，答案就是 $\binom{3+2-1}{3-1} = \binom{4}{2} = \frac{4!}{2! \times 2!} = 6$。

#### 2. 取模与逆元运算
因为答案可能会非常巨大，题目要求对 $10^9+7$ 取模。与上一题 "Creating Strings II" 完全一样，在模运算下我们不能直接除以分母，而是要乘以分母的**乘法逆元**：
$$ 
\text{Ans} = (n + m - 1)! \times \big((n-1)!\big)^{-1} \times (m!)^{-1} \pmod{10^9+7} 
$$
利用费马小定理：
$
a^{p-2} \equiv a^{-1} \pmod p
$（$p$ 为素数），我们可以用快速幂求出阶乘的逆元。

#### 3. 数组范围注意事项
题目给定 $n, m \le 10^6$，那么 $n + m - 1$ 的最大值大约是 $2 \times 10^6$。
因此，我们的阶乘预处理数组 `fact` 和逆元数组 `invFact` 的大小不能只是 $10^6$，必须开到 $2 \times 10^6 + 5$ 才能防止越界。

---

### 💻 完整 C++ 代码文件

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
// 注意：n和m最大都是10^6，组合数的上标 n+m-1 会达到 2 * 10^6，所以数组要开到2000005
const int MAXN = 2000005;

long long fact[MAXN];
long long invFact[MAXN];

// 快速幂算法计算 (base^exp) % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int total_elements = n + m - 1;

    // 1. 预处理 1 到 n+m-1 的阶乘
    fact[0] = 1;
    for (int i = 1; i <= total_elements; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    // 2. 预处理阶乘的逆元
    // 先用费马小定理通过快速幂算出最大的阶乘逆元
    invFact[total_elements] = power(fact[total_elements], MOD - 2);
    // 然后利用性质: 1/(i-1)! = (1/i!) * i，从大到小递推算出所有的阶乘逆元
    for (int i = total_elements - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    // 3. 计算组合数 C(n+m-1, n-1)
    // Ans = (n+m-1)! / ((n-1)! * m!) 
    //     = fact[n+m-1] * invFact[n-1] * invFact[m] (在模运算意义下)
    long long ans = fact[total_elements];
    ans = (ans * invFact[n - 1]) % MOD;
    ans = (ans * invFact[m]) % MOD;

    // 输出最终结果
    cout << ans << "\n";

    return 0;
}
```

### 📊 复杂度分析
*   **时间复杂度**：
    *   计算阶乘：我们需要循环遍历到 $n+m-1$，时间复杂度是 $O(n+m)$。
    *   计算最大逆元：使用快速幂，时间是 $O(\log(\text{MOD}))$。
    *   倒推逆元：循环遍历回 0，时间也是 $O(n+m)$。
    *   综合来看，算法的时间复杂度为 **$O(n+m)$**。最坏情况下 $n+m = 2 \cdot 10^6$，现代 CPU 执行百万级别的基本操作都在 $0.05$ 秒内即可跑完，完全符合题目要求的 $1.00\text{ s}$。
*   **空间 / 内存复杂度**：
    *   我们需要两个大小为 $2 \times 10^6$ 的 64位整型 (`long long`) 数组 `fact` 和 `invFact`。
    *   每个数组占用大约 $16 \text{ MB}$ 的内存，加在一起约 **$32 \text{ MB}$**。这远低于题目宽松的 $512 \text{ MB}$ 内存限制，非常安全。