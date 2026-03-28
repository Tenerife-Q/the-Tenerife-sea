这是一份为你量身定制的、符合 GitHub 仓库 `README.md` 标准格式的 Markdown 文档。

里面包含了**完整的数学证明推导**、**两种算法的进阶与对比**、**核心防坑指南（查缺补漏）**，以及**两套极致优化的 C++ 代码**。你可以直接将以下内容复制并作为你的学习笔记或开源项目的文档。

---

# 算法经典：大数斐波那契数列 (CSES - Fibonacci Numbers)



## 📝 题目描述
计算第 $n$ 个斐波那契数 $F_n$，并将结果对 $10^9+7$ 取模。
**约束条件**：$0 \le n \le 10^{18}$，时间限制 1.0s。

## 💡 为什么常规解法会失效？
常规的动态规划（或循环）推导斐波那契数列的时间复杂度为 $O(n)$。
当 $n = 10^{18}$ 时，即使计算机每秒执行 $10^8$ 次运算，也需要 **300 多年** 才能算完，必然导致 `TLE` (Time Limit Exceeded)。
**核心诉求**：我们必须寻找时间复杂度为 $\mathcal{O}(\log n)$ 的算法。

---

## 🚀 方法一：矩阵快速幂 (Matrix Exponentiation)

### 1. 数学公式推导与证明
斐波那契数列的递推公式为：$F_{n+1} = F_n + F_{n-1}$。
我们将其写成矩阵形式：
$$
\begin{bmatrix} F_{n+1} \\ F_n \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} F_n \\ F_{n-1} \end{bmatrix}
$$

通过不断向下展开，可以得到**通项矩阵公式**：
$$
\begin{bmatrix} F_{n+1} & F_n \\ F_n & F_{n-1} \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n
$$

**证明（数学归纳法）：**
1. **基础情况 ($n=1$)：**
   $\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^1 = \begin{bmatrix} F_2 & F_1 \\ F_1 & F_0 \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$，成立。
2. **假设 $n=k$ 时成立：** 即 $\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^k = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix}$。
3. **推导 $n=k+1$：**
   $$
   \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{k+1} = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix} \times \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} = \begin{bmatrix} F_{k+1}+F_k & F_{k+1} \\ F_k+F_{k-1} & F_k \end{bmatrix} = \begin{bmatrix} F_{k+2} & F_{k+1} \\ F_{k+1} & F_k \end{bmatrix}
   $$
   证毕。因此，求 $F_n$ 转化为求转换矩阵的 $n$ 次方，可用**快速幂算法**在 $O(\log n)$ 内解决。

### 2. C++ 代码实现 (完全展开矩阵乘法)
*抛弃晦涩的三层 `for` 循环，直接使用公式硬编码 $2 \times 2$ 矩阵乘法，极致易懂且常数更小。*

```cpp
#include <iostream>
using namespace std;

const long long MOD = 1e9 + 7;

struct Matrix {
    long long mat[2][2];
    Matrix() { mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0; }
};

// 展开的三层循环：纯数学公式直写
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    C.mat[0][0] = (A.mat[0][0] * B.mat[0][0] % MOD + A.mat[0][1] * B.mat[1][0] % MOD) % MOD;
    C.mat[0][1] = (A.mat[0][0] * B.mat[0][1] % MOD + A.mat[0][1] * B.mat[1][1] % MOD) % MOD;
    C.mat[1][0] = (A.mat[1][0] * B.mat[0][0] % MOD + A.mat[1][1] * B.mat[1][0] % MOD) % MOD;
    C.mat[1][1] = (A.mat[1][0] * B.mat[0][1] % MOD + A.mat[1][1] * B.mat[1][1] % MOD) % MOD;
    return C;
}

// 矩阵快速幂模板
Matrix power(Matrix A, long long p) {
    Matrix res;
    res.mat[0][0] = 1; res.mat[1][1] = 1; // 单位矩阵

    while (p > 0) {
        if (p % 2 == 1) res = multiply(res, A);
        A = multiply(A, A);
        p /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long n;
    if (cin >> n) {
        if (n == 0) { cout << 0 << "\n"; return 0; }
        Matrix T;
        T.mat[0][0] = 1; T.mat[0][1] = 1;
        T.mat[1][0] = 1; T.mat[1][1] = 0;
        
        Matrix res = power(T, n - 1); // 因为初始状态是 [F1, F0]
        cout << res.mat[0][0] << "\n"; // F_n
    }
    return 0;
}
```

---

## ⚡ 方法二：快速倍增法 (Fast Doubling)
*竞赛选手的最爱。不使用矩阵，代码极其精简，运行效率逼近极限。*

### 1. 数学公式推导与证明 (极其巧妙！)
我们在上面已经证明了：$M^n = \begin{bmatrix} F_{n+1} & F_n \\ F_n & F_{n-1} \end{bmatrix}$

**如果我们要求 $M^{2k}$ 呢？根据指数法则：$M^{2k} = M^k \times M^k$**
我们将矩阵代入：
$$
\begin{bmatrix} F_{2k+1} & F_{2k} \\ F_{2k} & F_{2k-1} \end{bmatrix} = \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix} \times \begin{bmatrix} F_{k+1} & F_k \\ F_k & F_{k-1} \end{bmatrix}
$$

我们只看结果矩阵的第一行：
1. **求 $F_{2k}$ (第一行第二列)：**
   $$F_{2k} = F_{k+1}F_k + F_kF_{k-1}$$
   因为 $F_{k-1} = F_{k+1} - F_k$，代入上式：
   $$F_{2k} = F_k(F_{k+1} + F_{k+1} - F_k) = \mathbf{F_k(2F_{k+1} - F_k)}$$
2. **求 $F_{2k+1}$ (第一行第一列)：**
   $$F_{2k+1} = \mathbf{F_{k+1}^2 + F_k^2}$$

**神级结论诞生：** 我们只需知道 $F_k$ 和 $F_{k+1}$，就能以 $O(1)$ 的代价直接跳跃求出 $F_{2k}$ 和 $F_{2k+1}$。通过类似二分查找的递归，完美实现 $O(\log n)$。

### 2. C++ 代码实现 (基于 `std::pair`)

```cpp
#include <iostream>
#include <utility>
using namespace std;

const long long MOD = 1e9 + 7;

// 返回值 pair: {F_n, F_{n+1}}
pair<long long, long long> fast_doubling(long long n) {
    if (n == 0) return {0, 1}; // F_0 = 0, F_1 = 1

    // 递归求 n/2 时的 {F_k, F_{k+1}}
    pair<long long, long long> p = fast_doubling(n >> 1); // n >> 1 等同于 n / 2
    long long fk = p.first;
    long long fk1 = p.second;

    // 核心公式计算
    // f2k = F_k * (2 * F_k+1 - F_k)
    long long f2k = fk * (2 * fk1 % MOD - fk + MOD) % MOD;
    
    // f2k1 = F_k^2 + F_k+1^2
    long long f2k1 = (fk * fk % MOD + fk1 * fk1 % MOD) % MOD;

    if (n % 2 == 0) {
        return {f2k, f2k1};
    } else {
        // 如果 n 是奇数，F_n 就是 F_{2k+1}
        // F_{n+1} 等于 F_{2k} + F_{2k+1}
        return {f2k1, (f2k + f2k1) % MOD};
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long n;
    if (cin >> n) {
        cout << fast_doubling(n).first << "\n";
    }
    return 0;
}
```

---

## 🛠️ 查缺补漏：核心避坑指南

在这类高精度计算题目中，往往逻辑写对了但由于细节没掌控好导致 `WA (Wrong Answer)`。请仔细检查以下三点：

### 1. 致命的“负数取模”问题 (Negative Modulo)
在快速倍增的公式中，有一步是：`2 * fk1 - fk`。
在数学上这是个正数，但在计算机的同余运算中，由于 `fk1` 和 `fk` 都在上一轮被取模了，`2 * fk1 % MOD` 完全有可能 **小于** `fk`，导致相减后产生**负数**！
> **错误写法：** `(2 * fk1 % MOD - fk) % MOD` （C++的取模保留负号，会算出负数结果）
> **正确写法：** `(2 * fk1 % MOD - fk + MOD) % MOD` （加上 `MOD` 强制转换为正数范围）

### 2. 乘法溢出问题 (Multiplication Overflow)
取模值 $MOD = 10^9+7$。
在运算 `fk * fk` 时，最大可能的数值接近 $10^{18}$。
*   32位整数 (`int`) 的上限约 $2 \times 10^9$，**一定会爆**。
*   64位整数 (`long long`) 的上限约 $9 \times 10^{18}$，可以安全容纳两个取模后的数相乘。
> **总结：** 凡是涉及矩阵乘法、快速倍增的中间变量，**强制全部声明为 `long long`**，千万不要图省事用 `int`。

### 3. 取模的时机 (When to Modulo)
不要企图等整个公式算完再取模！
例如：`(A * B + C * D)` 如果等加完再取模，即使 `A * B` 在 `long long` 范围内，两项相加可能就会突破 `long long` 的极限产生溢出。
> **原则：** 乘完立刻取模，加完立刻取模。步步为营。`( (A * B % MOD) + (C * D % MOD) ) % MOD`。