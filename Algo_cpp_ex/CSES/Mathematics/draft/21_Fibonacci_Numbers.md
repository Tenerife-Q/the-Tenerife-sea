

---


# 算法进阶：大数斐波那契数列 (CSES - Fibonacci Numbers)

在算法竞赛中，处理极大的 $n$（如 $10^{18}$）时，传统的 $O(n)$ 递推会瞬间失效。本文将详细探讨如何利用数学对称性与矩阵运算，将复杂度降至 $O(\log n)$。

---

## 📝 题目背景
**题目链接**：[CSES - Fibonacci Numbers](https://cses.fi/problemset/task/1722)  
**任务**：计算第 $n$ 个斐波那契数 $F_n$，结果对 $10^9+7$ 取模。  
**约束**：$0 \le n \le 10^{18}$，时间限制 1.0s。

### 为什么 $O(n)$ 不可行？
当 $n = 10^{18}$ 时，即便计算机每秒运行 $10^8$ 次运算，完成计算也需要约 **317 年**。我们需要一种能够通过“跳跃”计算的算法，即**对数级复杂度 $O(\log n)$**。

---

## 🚀 方法一：矩阵快速幂 (Matrix Exponentiation)

### 1. 数学推导
斐波那契数列的递推式为 $F_{n} = F_{n-1} + F_{n-2}$。我们可以将其表示为线性代数中的矩阵转化形式：

$$
\begin{bmatrix} F_{n+1} \\ F_n \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} F_n \\ F_{n-1} \end{bmatrix}
$$

通过连续推导，我们可以得到**通项矩阵公式**：

$$
\begin{bmatrix} F_{n+1} \\ F_n \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n \begin{bmatrix} F_1 \\ F_0 \end{bmatrix}
$$

或者更直观地表示为矩阵的幂：

$$
\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n = \begin{bmatrix} F_{n+1} & F_n \\ F_n & F_{n-1} \end{bmatrix}
$$

**核心思想**：计算矩阵的 $n$ 次幂，可以使用**快速幂 (Binary Exponentiation)** 算法。就像计算 $a^n$ 可以在 $O(\log n)$ 时间内完成一样，矩阵的幂同样适用。

### 2. C++ 代码实现

```cpp
#include <iostream>
#include <vector>

using namespace std;

long long MOD = 1e9 + 7;

// 定义 2x2 矩阵结构
struct Matrix {
    long long mat[2][2];
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

// 矩阵乘法实现
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂
Matrix power(Matrix A, long long p) {
    Matrix res;
    res.mat[0][0] = 1; res.mat[1][1] = 1; // 初始化为单位矩阵 I
    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

int main() {
    long long n;
    cin >> n;
    if (n == 0) { cout << 0 << endl; return 0; }
    
    Matrix T;
    T.mat[0][0] = 1; T.mat[0][1] = 1;
    T.mat[1][0] = 1; T.mat[1][1] = 0;

    Matrix result = power(T, n);
    // 根据公式，矩阵的 [1][0] 位置即为 F_n
    cout << result.mat[1][0] << endl;
    return 0;
}
```

---

## ⚡ 方法二：快速倍增法 (Fast Doubling)

这是矩阵快速幂的一种变体，它去掉了矩阵的冗余计算，直接利用斐波那契数的性质进行递归。

### 1. 核心公式证明
基于矩阵乘法的性质 $M^{2k} = M^k \times M^k$，我们可以推导出以下两个神奇的公式：

1.  **$F_{2k} = F_k (2F_{k+1} - F_k)$**
2.  **$F_{2k+1} = F_{k+1}^2 + F_k^2$**

**推导简述**：
已知 $M^k = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix}$，则 $M^{2k}$ 即为该矩阵自乘。
通过计算 $M^{2k}$ 的第一行第二列元素，可得 $F_{2k} = F_{k+1}F_k + F_kF_{k-1}$。
由于 $F_{k-1} = F_{k+1} - F_k$，代入后即可得到上述公式 1。公式 2 同理。

### 2. C++ 代码实现

```cpp
#include <iostream>
#include <utility>

using namespace std;

const long long MOD = 1e9 + 7;

// 返回值：{F_n, F_{n+1}}
pair<long long, long long> fast_doubling(long long n) {
    if (n == 0) return {0, 1}; // 基准情况: F_0, F_1

    // 递归计算 n/2
    pair<long long, long long> p = fast_doubling(n >> 1);
    long long fk = p.first;       // F_k
    long long fk1 = p.second;     // F_{k+1}

    // 使用公式计算 F_{2k} 和 F_{2k+1}
    // 注意：负数取模必须加 MOD
    long long f2k = fk * (2 * fk1 % MOD - fk + MOD) % MOD;
    long long f2k1 = (fk * fk % MOD + fk1 * fk1 % MOD) % MOD;

    if (n & 1) {
        // 如果 n 是奇数，返回 {F_{2k+1}, F_{2k+2}}
        // 其中 F_{2k+2} = F_{2k} + F_{2k+1}
        return {f2k1, (f2k + f2k1) % MOD};
    } else {
        // 如果 n 是偶数，直接返回 {F_{2k}, F_{2k+1}}
        return {f2k, f2k1};
    }
}

int main() {
    long long n;
    if (cin >> n) {
        cout << fast_doubling(n).first << endl;
    }
    return 0;
}
```

---

## 🛠️ 核心避坑指南 (Debugger's Checklist)

### 1. 致命的负数取模
在 C++ 中，`-1 % 10` 的结果是 `-1` 而非 `9`。
在公式 `2 * fk1 - fk` 中，虽然数学上结果为正，但由于 `fk` 可能在大数取模后显得比 `2*fk1` 大，计算结果可能为负。
> **修复方案**：始终使用 `(A - B + MOD) % MOD`。

### 2. 乘法溢出 (Long Long Overflow)
$MOD = 10^9+7$，两个接近 $MOD$ 的数相乘会达到 $10^{18}$ 级别。
* **不要使用 `int`**：`int` 的上限约为 $2 \times 10^9$，一旦相乘立即溢出。
* **强制 `long long`**：确保所有涉及中间运算的变量都是 `long long`。

### 3. 取模的时机
**原则**：乘法后立即取模，加法后立即取模。
* 错误：`(a * b + c * d) % MOD` （中间的加法可能先溢出了 long long）
* 正确：`((a * b % MOD) + (c * d % MOD)) % MOD`

---

## 📊 复杂度对比

| 方法 | 时间复杂度 | 空间复杂度 | 优点 |
| :--- | :--- | :--- | :--- |
| **递推法 (DP)** | $O(n)$ | $O(1)$ | 简单，但 $n > 10^8$ 时失效 |
| **矩阵快速幂** | $O(\log n)$ | $O(1)$ | 逻辑通用，易于扩展到其他线性递推 |
| **快速倍增法** | $O(\log n)$ | $O(\log n)$ | 常数极小，代码简洁，竞赛首选 |

---
```

---

### 我为你做了哪些修复与补充？

1.  **LaTeX 公式兼容性**：GitHub 的 Markdown 渲染器有时对 `$...$` 内部的空格很敏感。我统一使用了 `$$...$$` 来包裹矩阵公式，这样可以确保在 GitHub 网页上能正确渲染出精美的数学矩阵。
2.  **矩阵乘法的通用性**：在代码实现中，我使用了 `for` 循环嵌套来实现矩阵乘法，这比硬编码四个位置更具扩展性（例如如果你要算斐波那契的三阶变体，代码几乎不用改）。
3.  **位运算优化**：将 `n / 2` 替换为 `n >> 1`，将 `n % 2 == 1` 替换为 `n & 1`。虽然现代编译器会自动优化，但这符合算法竞赛的编写习惯。
4.  **详细的证明衔接**：补充了矩阵幂与斐波那契项的具体对应关系（如 `[1][0]` 位置对应 $F_n$），防止读者在实现时找错矩阵坐标。
5.  **表格对比**：增加了一个清晰的复杂度对比表格，一眼就能看出不同方案的优劣。

**接下来，你是否需要我为你生成一段针对该算法的单元测试（Unit Test）代码，以验证不同 $n$ 值下的准确性？**