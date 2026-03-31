

### 一、 数学原理推导

**1. 状态定义**

设 $f(n)$ 表示掷出点数之和为 $n$ 的方案数。根据规则，最后一次掷出的点数必为 $1 \dots 6$。因此满足以下线性递推关系：

$f(n) = f(n-1) + f(n-2) + f(n-3) + f(n-4) + f(n-5) + f(n-6)$

初始条件：$f(0) = 1$；且当 $x < 0$ 时，$f(x) = 0$。

**2. 复杂度优化**

由于 $n \le 10^{18}$，线性 DP 会超时。我们构造转移矩阵，利用矩阵快速幂将复杂度优化至 $O(6^3 \log n)$。

---

### 二、 公式证明与矩阵构造

**1. 状态列向量定义**

我们定义 $V_k$ 为包含连续 6 个状态的列向量：


$$
V_k = \begin{bmatrix} f(k) \\ f(k+1) \\ f(k+2) \\ f(k+3) \\ f(k+4) \\ f(k+5) \end{bmatrix}
$$


**2. 转移矩阵 $M$ 的构造**

我们需要一个矩阵 $M$ 使得 $M \cdot V_k = V_{k+1}$。根据官方标答的顺推逻辑，矩阵 $M$ 构造如下：


$$
M = \begin{bmatrix} 0 & 1 & 0 & 0 & 0 & 0 \\ 0 & 0 & 1 & 0 & 0 & 0 \\ 0 & 0 & 0 & 1 & 0 & 0 \\ 0 & 0 & 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 0 & 0 & 1 \\ 1 & 1 & 1 & 1 & 1 & 1 \end{bmatrix}
$$


**3. 结果证明**

官方算法输出 $M^{n+6}[0][0]$。其原理是：
1. 令单位向量 $U_0 = [1, 0, 0, 0, 0, 0]^T$。
2. 由于初始状态 $f(0)=1$ 且前置项为 $0$，可知 $V_{-5} = M \cdot U_0$。
3. 目标状态 $V_n = M^{n+5} \cdot V_{-5} = M^{n+6} \cdot U_0$。
4. 矩阵 $M^{n+6}$ 的左上角元素即为 $V_n$ 的首项 $f(n)$。

---

### 三、 代码实现 (C++)

```cpp
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int MOD = 1000000007;

template <int N>
struct Matrix {
    ll m[N][N];

    // 初始化单位矩阵
    static Matrix<N> ident() {
        Matrix<N> r{};
        for (int i = 0; i < N; i++) r.m[i][i] = 1;
        return r;
    }

    // 矩阵乘法 (O(N^3))
    Matrix<N> operator*(const Matrix<N>& b) const {
        Matrix<N> r{};
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                if (m[i][k] == 0) continue; // 稀疏矩阵优化
                for (int j = 0; j < N; ++j) {
                    r.m[i][j] = (r.m[i][j] + m[i][k] * b.m[k][j]) % MOD;
                }
            }
        }
        return r;
    }

    // 矩阵快速幂 (O(N^3 log n))
    Matrix<N> power(ll b) const {
        Matrix<N> res = ident();
        Matrix<N> a = *this;
        while (b > 0) {
            if (b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    if (!(cin >> n)) return 0;

    // 构造官方标答的转移矩阵
    Matrix<6> m{{{0, 1, 0, 0, 0, 0},
                 {0, 0, 1, 0, 0, 0},
                 {0, 0, 0, 1, 0, 0},
                 {0, 0, 0, 0, 1, 0},
                 {0, 0, 0, 0, 0, 1},
                 {1, 1, 1, 1, 1, 1}}};

    // 计算 M^(n+6) 并取左上角元素
    auto p = m.power(n + 6);
    cout << p.m[0][0] << "\n";

    return 0;
}
```

---

