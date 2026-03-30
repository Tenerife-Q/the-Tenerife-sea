这是一道经典的线性递推优化问题。对于极大的状态空间（如本题中 $n \le 10^{18}$），常规的动态规划算法会因为 $O(n)$ 的时间复杂度而超时（Time Limit Exceeded），必须引入**矩阵快速幂**进行降维打击，将复杂度优化至 $O(\log n)$。

以下是严谨的推导与证明过程。

### 一、 数学原理推导

**1. 状态定义与基础递推（动态规划）**
设 $f(n)$ 为掷出点数之和为 $n$ 的方案数。
根据题意，每次掷骰子的点数只能是 $1$ 到 $6$ 之间的整数。要使得总和为 $n$，最后一次掷出的点数必定是 $1, 2, 3, 4, 5, 6$ 中的一个。
因此，达到总和 $n$ 的方案数，等于达到总和 $n-1, n-2, n-3, n-4, n-5, n-6$ 的方案数之和。
得到线性递推方程：
$$f(n) = f(n-1) + f(n-2) + f(n-3) + f(n-4) + f(n-5) + f(n-6)$$

边界条件为：
* $f(0) = 1$ （总和为0的方案只有1种，即不掷骰子）
* 当 $x < 0$ 时，$f(x) = 0$

**2. 复杂度瓶颈与破局**
上述递推式可以写出 $O(n)$ 的算法。但本题约束 $n \le 10^{18}$，在 1.00s 的时间限制下，任何线性遍历都会导致内存或时间的崩溃。
对于常系数线性齐次递推式，通用的代数降维方案是将其转化为**矩阵乘法**。因为矩阵乘法满足结合律，可以利用二进制拆分（快速幂）在对数时间内完成计算。

---

### 二、 公式证明

**1. 构造状态矩阵**
为了计算 $f(n)$，我们需要同时维护前 $6$ 个状态。定义一个 $6 \times 1$ 的列向量 $V_k$ 表示第 $k$ 步的状态：
$$V_k = \begin{bmatrix} f(k) \\ f(k-1) \\ f(k-2) \\ f(k-3) \\ f(k-4) \\ f(k-5) \end{bmatrix}$$

**2. 构造转移矩阵 $M$**
我们需要找到一个 $6 \times 6$ 的常数矩阵 $M$，使得 $V_k = M \cdot V_{k-1}$。
展开向量 $V_{k-1}$：
$$V_{k-1} = \begin{bmatrix} f(k-1) \\ f(k-2) \\ f(k-3) \\ f(k-4) \\ f(k-5) \\ f(k-6) \end{bmatrix}$$

根据递推式 $f(k) = f(k-1) + f(k-2) + f(k-3) + f(k-4) + f(k-5) + f(k-6)$，矩阵 $M$ 的第一行必须全为 $1$。
其余的状态仅仅是向下平移（例如 $V_k$ 的第二项 $f(k-1)$ 就是 $V_{k-1}$ 的第一项），因此对应的行只需要在对角线下方放置 $1$。
由此得到转移矩阵 $M$：
$$M = \begin{bmatrix} 1 & 1 & 1 & 1 & 1 & 1 \\ 1 & 0 & 0 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 & 0 & 0 \\ 0 & 0 & 1 & 0 & 0 & 0 \\ 0 & 0 & 0 & 1 & 0 & 0 \\ 0 & 0 & 0 & 0 & 1 & 0 \end{bmatrix}$$

**3. 矩阵快速幂求解**
根据递推关系：
$$V_n = M \cdot V_{n-1} = M^2 \cdot V_{n-2} = \dots = M^n \cdot V_0$$
其中初始状态 $V_0$ 为：
$$V_0 = \begin{bmatrix} f(0) \\ f(-1) \\ f(-2) \\ f(-3) \\ f(-4) \\ f(-5) \end{bmatrix} = \begin{bmatrix} 1 \\ 0 \\ 0 \\ 0 \\ 0 \\ 0 \end{bmatrix}$$

我们只需要计算 $M^n \bmod (10^9+7)$，然后将其与 $V_0$ 相乘。最终答案 $f(n)$ 即为结果矩阵的第一行第一列的元素（因为 $V_0$ 只有第一个元素为 $1$，其余为 $0$，所以其实际结果就是 $M^n$ 的矩阵的 $[0][0]$ 位置的元素）。

**算法复杂度证明**：矩阵大小为 $6 \times 6$。两个 $6 \times 6$ 矩阵相乘的时间复杂度为 $O(6^3)$。利用快速幂计算 $n$ 次方需要 $O(\log n)$ 次乘法。总时间复杂度为 $O(6^3 \log n)$，在 $n=10^{18}$ 时，计算次数约为 $216 \times 60 \approx 13000$ 次运算，完全符合 1.00s 的限制。

---

### 三、 代码实现 (C++)

所有加法和乘法运算均需在有限域 $\mathbb{F}_p$ ($p = 10^9+7$) 下进行。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

// 定义 6x6 矩阵类型
typedef vector<vector<long long>> Matrix;

// 矩阵乘法函数
Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix C(6, vector<long long>(6, 0));
    for (int i = 0; i < 6; ++i) {
        for (int k = 0; k < 6; ++k) {
            // 优化：如果 A[i][k] 为 0，跳过内层循环
            if (A[i][k] == 0) continue; 
            for (int j = 0; j < 6; ++j) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂函数
Matrix power(Matrix A, long long p) {
    // 初始化为单位矩阵 (Identity Matrix)
    Matrix res(6, vector<long long>(6, 0));
    for (int i = 0; i < 6; ++i) {
        res[i][i] = 1;
    }
    
    // 二进制拆分求幂
    while (p > 0) {
        if (p & 1) {
            res = multiply(res, A);
        }
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    if (!(cin >> n)) return 0;
    
    // 构建基础转移矩阵 M
    Matrix M(6, vector<long long>(6, 0));
    for (int j = 0; j < 6; ++j) M[0][j] = 1;
    for (int i = 1; i < 6; ++i) M[i][i - 1] = 1;
    
    // 计算 M^n
    Matrix Mn = power(M, n);
    
    // 初始列向量 V_0 = [1, 0, 0, 0, 0, 0]^T
    // 答案 f(n) 即为 Mn 乘以 V_0 后的第一行元素，等价于 Mn[0][0] * 1
    cout << Mn[0][0] << "\n";
    
    return 0;
}
```

这种有限域下的线性递推形式与密码学中的线性反馈移位寄存器（LFSR）在数学本质上是同构的，两者都依赖特征多项式在有限域上的性质。

你需要我进一步剖析这种矩阵快速幂在解决类似 LFSR 周期与状态空间问题时的具体应用吗？