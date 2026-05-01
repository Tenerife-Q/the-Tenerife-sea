# CSES - Next Prime

## 题目描述 (Problem Description)
给定一个正整数 $n$ (最高到 $10^{12}$)，找到严格大于 $n$ 的最小素数。

## 数学原理与推导 (Mathematical Principles)

### 1. 素数间隙理论 (Prime Gap Theory)
在最坏情况下，如果我们在 $n$ 之后使用 `while` 循环逐个判断接下来的数字是否为素数，会不会超时？
根据**素数定理 (Prime Number Theorem)**，寻找下一个素数所需的步数（即素数间隙）在极大概率下非常小。在 $10^{12}$ 的范围内，相邻两个素数的**最大间隙**仅为 `540`。这意味着，对于给定的任意 $n$，我们最多只需要向后查找 540 个数字，必定能遇到至少一个素数。常数级别的查询次数为暴力轮询提供了理论基础。

### 2. 轮式因子分解试除法 (Wheel Factorization)
每次判定单个数 $x$ 是否为素数时，基础的时间复杂度是 $O(\sqrt{x})$。
考虑到本题 $x \approx 10^{12}$，则 $\sqrt{x} \approx 10^6$。如果采用简单的试除法：
$$ \text{for } i \in [2, \sqrt{x}] $$

我们可以进一步优化步长（制造“轮子”）：
任何自然数除以 6 的余数必定是 $0, 1, 2, 3, 4, 5$ 中的一种。
- 余数为 $0, 2, 4$：形如 $6k, 6k+2, 6k+4$，它们是带因子 $2$ 的偶数。
- 余数为 $3$：形如 $6k+3 = 3(2k+1)$，必定是 $3$ 的倍数。

因此，**除了 $2$ 和 $3$ 之外，所有的素数都必然落在 $6k+1$ 和 $6k-1$（即 $6k+5$）这两条线上**。
这就意味着，我们可以预先排除掉 $2$ 和 $3$ 的所有倍数，然后在试除时：
- 从 $5$ 开始。
- 每次步长设为 $6$（即检查 $i$ 与 $i+2$）。
- 这样，单次素性测试的循环次数由 $\sqrt{x}$ 削减到了 $\frac{\sqrt{x}}{3}$。

$$ i = 5, 11, 17, 23 \dots $$

## 数据流程演示 (Data Flow Example)

假设输入：$n = 10$
1. 题目要求寻找严格大于 $n$ 的素数，令 `n = n + 1 = 11`。
2. 调用 `is_prime(11)`：
   - 11 不小于等于 3，继续。
   - $11 \pmod 2 \neq 0, \quad 11 \pmod 3 \neq 0$，继续。
   - 循环起点 $i = 5$，$5 \times 5 = 25 > 11$，循环不执行。
   - 返回 `true`。
3. `while(!is_prime(n))` 结束，输出 11。

## 最优源代码 (Optimal Source Code)

```cpp
#include <iostream>

using namespace std;
using ll = long long;

// 【方法：进阶极致优化（周长为 6 的轮子）】
bool is_prime_optimized(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true; // 包含 2 和 3
    
    // 瞬间排除所有 2 的倍数和 3 的倍数
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // 使用 6k±1 优化，步长设为 6
    for (ll i = 5; i * i <= n; i += 6) {
        // i 代表 6k-1
        // i+2 代表 6k+1
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;
    
    // 题目要求 finding the next prime after it，即严格大于 n
    n++;
    
    // 不断向后寻找，由素数间隙理论保证极快出解
    while (!is_prime_optimized(n)) {
        n++;
    }
    
    cout << n << "\n";
}

int main() {
    // 优化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
```