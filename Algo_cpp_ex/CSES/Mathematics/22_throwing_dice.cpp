// Throwing Dice / 掷骰子
//
// English:
// Task
// Your task is to calculate the number of ways to get a sum n by throwing dice.
// Each throw yields an integer between 1 ... 6.
// For example, if n=10, some possible ways are 3+3+4, 1+4+1+4 and 1+1+6+1+1.
// Input
// The only input line contains an integer n.
// Output
// Print the number of ways modulo 10^9+7.
// Constraints
// 1 <= n <= 10^18
// Example
// Input:
// 8
// Output:
// 125
//
// 中文：
// 题目：掷骰子
// 任务：计算通过掷骰子得到和为 n 的方案数。每次掷出一个在 1 到 6 之间的整数。
// 例如，当 n=10 时，一些有效的方案有 3+3+4、1+4+1+4、1+1+6+1+1 等。
// 输入：仅包含一个整数 n。
// 输出：输出方案数，对 10^9+7 取模。
// 约束：1 <= n <= 10^18
// 样例：
// 输入：
// 8
// 输出：
// 125

/*
   说明（实现要点）:
   - 这是一个线性递推：a_n = a_{n-1} + a_{n-2} + ... + a_{n-6}, a_0 = 1
   - 因为 n 可达 10^18，需要用矩阵快速幂（6x6 转移矩阵）求解。
   - 代码实现关注性能与取模安全（用 __int128 做中间乘法）。
*/

// #include <iostream>
// #include <vector>

// using namespace std;

// const long long MOD = 1e9 + 7;

// // 定义 6x6 矩阵类型
// typedef vector<vector<long long>> Matrix;

// // 矩阵乘法函数
// Matrix multiply(const Matrix& A, const Matrix& B) {
//     Matrix C(6, vector<long long>(6, 0));
//     for (int i = 0; i < 6; ++i) {
//         for (int k = 0; k < 6; ++k) {
//             // 优化：如果 A[i][k] 为 0，跳过内层循环
//             if (A[i][k] == 0) continue; 
//             for (int j = 0; j < 6; ++j) {
//                 C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
//             }
//         }
//     }
//     return C;
// }

// // 矩阵快速幂函数
// Matrix power(Matrix A, long long p) {
//     // 初始化为单位矩阵 (Identity Matrix)
//     Matrix res(6, vector<long long>(6, 0));
//     for (int i = 0; i < 6; ++i) {
//         res[i][i] = 1;
//     }
    
//     // 二进制拆分求幂
//     while (p > 0) {
//         if (p & 1) {
//             res = multiply(res, A);
//         }
//         A = multiply(A, A);
//         p >>= 1;
//     }
//     return res;
// }

// int main() {
//     // 优化输入输出流
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     long long n;
//     if (!(cin >> n)) return 0;
    
//     // 构建基础转移矩阵 M
//     Matrix M(6, vector<long long>(6, 0));
//     for (int j = 0; j < 6; ++j) M[0][j] = 1;
//     for (int i = 1; i < 6; ++i) M[i][i - 1] = 1;
    
//     // 计算 M^n
//     Matrix Mn = power(M, n);
    
//     // 初始列向量 V_0 = [1, 0, 0, 0, 0, 0]^T
//     // 答案 f(n) 即为 Mn 乘以 V_0 后的第一行元素，等价于 Mn[0][0] * 1
//     cout << Mn[0][0] << "\n";
    
//     return 0;
// }

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