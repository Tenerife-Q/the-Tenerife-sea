

# 算法经典：大数斐波那契数列 (CSES - Fibonacci Numbers)

## 📝 题目描述
计算第 $n$ 个斐波那契数 $F_n$，并将结果对 $10^9+7$ 取模。
* **定义**：$F_0 = 0, F_1 = 1, F_n = F_{n-1} + F_{n-2}$
* **约束条件**：$0 \le n \le 10^{18}$，时间限制 1.0s。

## 💡 为什么常规解法会失效？
常规的动态规划（或循环）推导斐波那契数列的时间复杂度为 $O(n)$。
当 $n = 10^{18}$ 时，即使计算机每秒执行 $10^8$ 次运算，也需要约 **317 年** 才能算完，必然导致 `TLE` (Time Limit Exceeded)。
**核心诉求**：我们必须寻找时间复杂度为 $O(\log n)$ 的算法。

---

## 🚀 方法一：矩阵快速幂 (Matrix Exponentiation)

### 1. 数学公式推导与证明
斐波那契数列的递推公式为：$F_{n+1} = F_n + F_{n-1}$。
我们将其写成矩阵转移形式：
$$
\begin{bmatrix} F_{n+1} \\ F_n \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} F_n \\ F_{n-1} \end{bmatrix}
$$

通过不断向下展开，可以得到**状态转移方程**：
$$
\begin{bmatrix} F_{n+1} \\ F_n \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n \begin{bmatrix} F_1 \\ F_0 \end{bmatrix}
$$

**核心性质（Q-Matrix）**：
定义转移矩阵 $M = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$，则其 $n$ 次幂满足：
$$
M^n = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n = \begin{bmatrix} F_{n+1} & F_n \\ F_n & F_{n-1} \end{bmatrix}
$$

**证明（数学归纳法）：**
1.  **基础情况 ($n=1$)**：
    $\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^1 = \begin{bmatrix} F_2 & F_1 \\ F_1 & F_0 \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$，由于 $F_2=1, F_1=1, F_0=0$，结论成立。
2.  **假设 $n=k$ 时成立**：即 $M^k = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix}$。
3.  **推导 $n=k+1$**：
    $$
    M^{k+1} = M^k \times M = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix} \times \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} = \begin{bmatrix} F_{k+1}+F_k & F_{k+1} \\ F_k+F_{k-1} & F_k \end{bmatrix} = \begin{bmatrix} F_{k+2} & F_{k+1} \\ F_{k+1} & F_k \end{bmatrix}
    $$
    证毕。因此，求 $F_n$ 转化为求矩阵的 $n$ 次方，利用**快速幂算法**可在 $O(\log n)$ 内解决。

### 2. C++ 代码实现
```cpp
#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

struct Matrix {
    long long mat[2][2];
    Matrix() { mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0; }
};

// 矩阵乘法：(A*B) % MOD
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
    return C;
}

// 矩阵快速幂：M^p
Matrix power(Matrix A, long long p) {
    Matrix res;
    res.mat[0][0] = 1; res.mat[1][1] = 1; // 初始化为单位矩阵
    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

int main() {
    long long n;
    if (!(cin >> n)) return 0;
    if (n == 0) { cout << 0 << endl; return 0; }
    
    Matrix T;
    T.mat[0][0] = 1; T.mat[0][1] = 1;
    T.mat[1][0] = 1; T.mat[1][1] = 0;
    
    Matrix res = power(T, n);
    // 根据推导，M^n 的 [0][1] 位置即为 F_n
    cout << res.mat[0][1] << endl;
    return 0;
}
```

---

## ⚡ 方法二：快速倍增法 (Fast Doubling)
*不使用显式矩阵，基于代数公式递归，常数更小。*

### 1. 数学公式推导
基于矩阵乘法的性质 $M^{2k} = M^k \times M^k$，展开后可得：
1.  **$F_{2k} = F_k (2F_{k+1} - F_k)$**
2.  **$F_{2k+1} = F_{k+1}^2 + F_k^2$**

**推导过程**：
已知 $M^k = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix}$，则 $M^{2k}$ 的第一行第二列元素为：
$F_{2k} = F_{k+1}F_k + F_kF_{k-1}$
代入 $F_{k-1} = F_{k+1} - F_k$：
$F_{2k} = F_k(F_{k+1} + F_{k+1} - F_k) = F_k(2F_{k+1} - F_k)$。

### 2. C++ 代码实现
```cpp
#include <iostream>
#include <utility>

using namespace std;

const long long MOD = 1e9 + 7;

// 返回值 pair: {F_n, F_{n+1}}
pair<long long, long long> fast_doubling(long long n) {
    if (n == 0) return {0, 1};

    pair<long long, long long> p = fast_doubling(n >> 1);
    long long fk = p.first;
    long long fk1 = p.second;

    // f2k = F_k * (2 * F_{k+1} - F_k)
    long long f2k = (fk * (2 * fk1 % MOD - fk + MOD) % MOD) % MOD;
    // f2k1 = F_k^2 + F_{k+1}^2
    long long f2k1 = (fk * fk % MOD + fk1 * fk1 % MOD) % MOD;

    if (n & 1) 
        return {f2k1, (f2k + f2k1) % MOD};
    else 
        return {f2k, f2k1};
}

int main() {
    long long n;
    if (cin >> n) cout << fast_doubling(n).first << endl;
    return 0;
}
```

---

## 🛠️ 核心避坑指南

### 1. 致命的“负数取模” (Negative Modulo)
在公式 `2 * fk1 - fk` 中，虽然数学上 $F_{2k}$ 必为正，但在同余运算中 `fk` 可能大于 `2 * fk1 % MOD`。
* **错误写法**：`(2 * fk1 - fk) % MOD` (结果可能为负)
* **正确写法**：`(2 * fk1 % MOD - fk + MOD) % MOD`

### 2. 乘法溢出 (Multiplication Overflow)
$MOD = 10^9+7$。在计算 `fk * fk` 时，最大值为 $10^{18}$ 级别。
* **int**：上限约 $2 \times 10^9$，**必爆**。
* **long long**：上限约 $9 \times 10^{18}$，可以安全承载。务必全量使用 `long long`。

### 3. 取模时机
**原则**：乘法后立刻取模，加法后立刻取模。
`C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;` 
这行代码中，`A*B` 的结果要先被 `long long` 承载，再与 `C.mat` 相加，最后统一取模，这在 $2 \times 2$ 规模下是安全的。
```

