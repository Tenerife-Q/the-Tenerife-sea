/**
 * ============================================================
 * 第一讲：基础算法 - 高精度乘法 (High Precision Multiplication)
 * ============================================================
 * 
 * 场景：大整数 A × 小整数 b (b 一般在 int 范围内)
 * 核心思想：
 * 1. 把小整数 b 看作一个整体，去乘大整数 A 的每一位。
 * 2. 也是模拟竖式：
 *    - t = A[i] * b + t (当前位 * b + 上一位进位)
 *    - 当前位保留 t % 10
 *    - 进位更新为 t / 10
 * 3. 循环结束后，如果 t 还不为 0，继续 push_back(t % 10) 直到 t 为 0。
 * 4. 注意处理前导零（例如 A * 0 的情况）。
 */

#include <iostream>
#include <vector>

using namespace std;

// ⚡ 核心模板代码：C = A * b
vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    int t = 0; // 进位，这个 t 可能会很大，不只是 0-9
    
    // 这里的循环条件把 t != 0 也放进去了，代码更紧凑
    // i < A.size() 还没乘完，或者 t != 0 还有进位没处理完
    for (int i = 0; i < A.size() || t; i++) {
        if (i < A.size()) t += A[i] * b; // 加上当前位乘积
        
        C.push_back(t % 10);
        t /= 10;
    }

    // 去掉前导零 (主要针对 b = 0 的情况，结果 vector 可能会有多个 0 或者 00)
    // 严谨点：如果结果是 0，只留一个 0
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}

/**
 * ============================================================
 * 💡 进阶：高精度 × 高精度 (BigInt * BigInt) - 董晓算法模板
 * ============================================================
 * 
 * ❓ 区别在哪里？
 * 上面的 mul 函数是 "大数 × 小数(int)"，复杂度 O(N)。
 * 这里是 "大数 × 大数(string)"，复杂度 O(N * M)。
 * 
 * ❓ 数学原理 (核心下标 i + j 的由来)：
 * 其实就是多项式乘法 (卷积) 的模拟。
 * 设 A = a[0]*10^0 + a[1]*10^1 + ... + a[i]*10^i
 * 设 B = b[0]*10^0 + b[1]*10^1 + ... + b[j]*10^j
 * 
 * 当我们计算 A * B 时，a[i] (代表 i 位的值) 和 b[j] (代表 j 位的值) 相乘：
 * (a[i] * 10^i) * (b[j] * 10^j) = (a[i] * b[j]) * 10^(i+j)
 * 
 * 结论：a[i] * b[j] 的结果应该加到结果数组 C 的第 (i + j) 位上。
 * 
 * ❓ 为什么可以实时进位？
 * c[i+j] 可能会因为后续的累加再次超过 10，没关系。
 * 我们在计算 c[i+j] 的时候，顺手把它的进位加到 c[i+j+1]。
 * 即使 c[i+j] 后面又变大了，下次循环或者内层循环自然会再次处理进位。
 * 最终每一位都会被"熨平"成 0-9。
 */
/*
// 全局开大数组防止栈溢出
const int LEN = 10005;
int a[LEN], b[LEN], c[LEN];

void mul_high_high(string sa, string sb) {
    // 1. 初始化
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));

    int la = sa.size(), lb = sb.size();
    
    // 2. 倒序存储 (~i 是 i!=-1 的简写，等价于 i >= 0)
    for(int i = la - 1; i >= 0; i--) a[la - 1 - i] = sa[i] - '0';
    for(int i = lb - 1; i >= 0; i--) b[lb - 1 - i] = sb[i] - '0';
    
    // 3. 核心计算
    // 结果的最大位数是 la + lb
    for(int i = 0; i < la; i++) {
        for(int j = 0; j < lb; j++) {
            c[i + j] += a[i] * b[j];       // 累加乘积到对应位
            c[i + j + 1] += c[i + j] / 10; // 处理进位到下一位
            c[i + j] %= 10;                // 当前位保留个位
        }
    }
    
    // 4. 去除前导零
    int lc = la + lb; // 预估最大位数
    // while(lc > 0 && c[lc] == 0) lc--; // 经典写法
    while(lc && c[lc] == 0) lc--; // 董晓写法，lc 非 0 且最高位是 0 就退位
    
    // 5. 输出
    for(int i = lc; i >= 0; i--) cout << c[i];
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a;
    int b;
    // cout << "Input a large number and an int: ";
    if (cin >> a >> b) {
        vector<int> A;
        for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');

        auto C = mul(A, b);

        for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
        cout << endl;
    }

    return 0;
}
