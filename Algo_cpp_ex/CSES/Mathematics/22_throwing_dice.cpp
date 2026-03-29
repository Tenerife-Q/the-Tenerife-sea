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

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 MOD = 1000000007LL;

using Matrix = array<array<int64,6>,6>;

Matrix mul(const Matrix &A, const Matrix &B){
    Matrix C{};
    for(int i=0;i<6;++i){
        for(int k=0;k<6;++k){
            if (A[i][k]==0) continue;
            __int128 av = A[i][k];
            for(int j=0;j<6;++j){
                if (B[k][j]==0) continue;
                C[i][j] = (C[i][j] + (int64)((av * B[k][j]) % MOD)) % MOD;
            }
        }
    }
    return C;
}

Matrix matPow(Matrix base, unsigned long long exp){
    Matrix R{};
    for(int i=0;i<6;++i) R[i][i]=1;
    while(exp){
        if(exp&1) R = mul(R, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    if(!(cin>>n)) return 0;

    // Build transition matrix M (6x6)
    Matrix M{};
    // first row: a_{t+1} = sum a_t..a_{t-5}
    for(int j=0;j<6;++j) M[0][j]=1;
    // shift rows
    for(int i=1;i<6;++i) M[i][i-1]=1;

    // v0 = [a0, a_{-1},...,a_{-5}]^T = [1,0,0,0,0,0]
    // a_n is first element of M^n * v0, which equals (M^n)[0][0]
    Matrix P = matPow(M, n);
    cout << (P[0][0] % MOD + MOD) % MOD << '\n';
    return 0;
}
