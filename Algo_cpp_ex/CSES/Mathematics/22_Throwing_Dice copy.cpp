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


#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const ll MOD = 1000000007;

struct Matrix {
    ll m[6][6];
    Matrix() {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                m[i][j] = 0;
            }
        }
    }

    static Matrix ident() {
        Matrix res;
        for (int i = 0; i < 6; ++i) res.m[i][i] = 1;
        return res;
    }

    Matrix operator*(const Matrix& b) const {
        Matrix res;
        for (int i = 0; i < 6; ++i) {
            for (int k = 0; k < 6; ++k) {
                if (m[i][k] == 0) continue; 
                for (int j = 0; j < 6; ++j) {
                    res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j]) % MOD;
                }
            }
        }
        return res;
    }

    Matrix power(ll p) const {
        Matrix res = ident();
        Matrix a = *this;

        while (p > 0) {
            if (p & 1) res = res * a;
            a = a * a;
            p >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    Matrix M;
    for (int j = 0; j < 6; ++j) {
        M.m[0][j] = 1;
    }
    for (int i = 1; i < 6; ++i) {
        M.m[i][i - 1] = 1;
    }
    Matrix p = M.power(n);
    cout << p.m[0][0] << "\n";

    return 0;
}
//{{{1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 0},
// {0, 1, 0, 0, 0, 0},
// {0, 0, 1, 0, 0, 0},
// {0, 0, 0, 1, 0, 0},
// {0, 0, 0, 0, 1, 0}}}