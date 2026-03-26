

***

# 算法解析：Counting Grids (网格计数问题)

本文档解析 Burnside 引理在二维平面网格中的应用。通过分析正方形网格在旋转变换下的群作用，推导出本质不同着色方案数的计算公式。

## 一、 数学模型抽象

**问题描述**：
给定一个 $n \times n$ 的正方形网格，每个格子可涂成 $m$ 种颜色（本题 $m=2$）。若两个网格经旋转后一致，则视为同一种方案。求本质不同的方案数 $\pmod{10^9+7}$。

**抽象分析**：
- **置换群 $G$**：正方形的旋转群 $G = \{0^\circ, 90^\circ, 180^\circ, 270^\circ\}$，群阶 $|G| = 4$。
- **着色集合 $X$**：所有可能的着色方案，总数 $|X| = m^{n^2}$。
- **核心理论**：根据 Burnside 引理，本质不同的方案数为各置换下保持不变的方案数的平均值：
  $$\text{Ans} = \frac{1}{|G|} \sum_{g \in G} |X^g|$$



---

## 二、 旋转置换下的不动点计算

要在某种旋转后保持“不变”，必须满足属于同一个轨道（即旋转后互相交换位置的格子集合）的所有格子颜色相同。设某种旋转下格子被划分为 $c(g)$ 个循环（轨道），则该旋转下的不动点数为 $m^{c(g)}$。

### 1. 旋转 $0^\circ$
- **变换逻辑**：所有格子原地不动。
- **循环个数**：每个格子自成一个循环，共 $n^2$ 个。
- **不动点数**：$2^{n^2}$。

### 2. 旋转 $180^\circ$
- **变换逻辑**：点 $(x, y)$ 与 $(n-1-x, n-1-y)$ 互换。
- **循环个数计算**：
    - 若 $n$ 为偶数：所有格子两两配对，循环数为 $n^2 / 2$。
    - 若 $n$ 为奇数：中心点原地不动，其余 $n^2-1$ 个点两两配对，循环数为 $1 + (n^2-1)/2 = (n^2+1)/2$。
- **统一公式**：$c(180^\circ) = \lfloor \frac{n^2+1}{2} \rfloor$。
- **不动点数**：$2^{\lfloor \frac{n^2+1}{2} \rfloor}$。



### 3. 旋转 $90^\circ$ 与 $270^\circ$
- **变换逻辑**：一个格子需经过 4 次旋转回到原位。
- **循环个数计算**：
    - 若 $n$ 为偶数：所有格子每 4 个一组构成循环，循环数为 $n^2 / 4$。
    - 若 $n$ 为奇数：中心点不动（1 个循环），其余 $n^2-1$ 个点每 4 个一组，循环数为 $1 + (n^2-1)/4 = (n^2+3)/4$。
- **统一公式**：$c(90^\circ) = c(270^\circ) = \lfloor \frac{n^2+3}{4} \rfloor$。
- **不动点数**：$2 \times 2^{\lfloor \frac{n^2+3}{4} \rfloor}$。



---

## 三、 终极计算公式

综合上述四种情况，本质不同的网格总数为：

$$\text{Ans} = \frac{1}{4} \left( 2^{n^2} + 2^{\lfloor \frac{n^2+1}{2} \rfloor} + 2 \cdot 2^{\lfloor \frac{n^2+3}{4} \rfloor} \right) \pmod{10^9+7}$$

### 工程细节：指数处理
当 $n = 10^9$ 时，$n^2 = 10^{18}$。在模运算中，若指数非常大，根据费马小定理：
$$a^b \equiv a^{b \pmod{\phi(M)}} \pmod M$$
由于 $10^9+7$ 是质数，$\phi(M) = M-1 = 10^9+6$。因此在代码中，所有的指数应对 $10^9+6$ 取模，防止计算 `power` 时溢出或逻辑错误（尽管 `long long` 范围足以支撑 $10^{18}$ 的快速幂计算）。

---

## 四、 C++ 代码实现

```cpp
#include <iostream>

using namespace std;

/**
 * @brief 快速幂算法
 * 计算 (base^exp) % mod
 */
long long power(long long base, long long exp, long long mod = 1000000007) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    // 提升 I/O 效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    const int MOD = 1000000007;
    const int PHI = MOD - 1; // 费马小定理中的指数模数

    // 计算 n^2 对 PHI 取模后的结果，用于指数运算
    // 使用 __int128 确保 n*n 不会溢出 long long，或者直接对 PHI 取模
    long long n2_mod = (n % PHI) * (n % PHI) % PHI;
    
    // 计算各旋转置换下的轨道数 (指数)
    long long e0 = n2_mod;
    long long e180 = ((n % (2 * PHI)) * (n % (2 * PHI)) + 1) / 2 % PHI;
    long long e90 = ((n % (4 * PHI)) * (n % (4 * PHI)) + 3) / 4 % PHI;

    // 统计各置换下的不动点总数
    long long sum = 0;
    sum = (sum + power(2, e0)) % MOD;          // 0度
    sum = (sum + power(2, e180)) % MOD;        // 180度
    sum = (sum + 2 * power(2, e90)) % MOD;     // 90度和270度

    // 结果乘以 4 的乘法逆元
    long long inv4 = power(4, MOD - 2);
    long long ans = (sum * inv4) % MOD;

    cout << ans << endl;

    return 0;
}
```

### 验证示例
对于 $n = 4$：
1. $n^2 = 16$。
2. $0^\circ$ 不动点：$2^{16} = 65536$。
3. $180^\circ$ 不动点：$2^{(16+0)/2} = 2^8 = 256$。
4. $90^\circ/270^\circ$ 不动点：$2 \times 2^{16/4} = 2 \times 2^4 = 32$。
5. 总和：$65536 + 256 + 32 = 65824$。
6. 平均值：$65824 / 4 = 16456$。符合预期。

***
// 快速幂算法：计算 (base^exp) % MOD
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

    long long n;
    if (!(cin >> n)) return 0;

    // 因为 n 最大是 10^9，n * n 最大是 10^18
    // 必须用 long long，不会溢出（long long 上限是 9.22 * 10^18）
    long long n2 = n * n;

    // 严格按照公式推导，计算出四种旋转下，各自被分成的“组数”（即指数部分）
    long long e0 = n2;
    long long e180 = (n2 + 1) / 2;
    long long e90 = (n2 + 3) / 4;
    long long e270 = e90; // 270度与90度完全对称

    // 将四种情况保持不变的方案数相加，边加边取模
    long long sum = 0;
    
    // 注意：根据费马小定理，指数部分可以对 (MOD - 1) 取模来减小计算量
    // 即使不取模，直接把 10^18 丢进快速幂，由于是二分计算，循环也只要执行 60 次，完全不会超时。
    // 为了严谨，我们直接在指数上 %(MOD - 1)
    sum = (sum + power(2, e0 % (MOD - 1))) % MOD;
    sum = (sum + power(2, e180 % (MOD - 1))) % MOD;
    sum = (sum + power(2, e90 % (MOD - 1))) % MOD;
    sum = (sum + power(2, e270 % (MOD - 1))) % MOD;

    // 最后的总和除以 4，等价于乘以 4 的乘法逆元：power(4, MOD - 2)
    long long ans = (sum * power(4, MOD - 2)) % MOD;

    cout << ans << "\n";

    return 0;
}