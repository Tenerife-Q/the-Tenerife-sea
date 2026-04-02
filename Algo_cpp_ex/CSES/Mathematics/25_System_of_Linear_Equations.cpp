/*
 * @Author: 
 * @Date: 2026-04-02
 * @LastEditors: 
 * @LastEditTime: 
 * @Description: 25. System of Linear Equations / 线性方程组
 * 
 * --------------------------------------------------------
 * Time limit: 1.00 s
 * Memory limit: 512 MB
 * 
 * You are given n*(m+1) coefficients a_{i,j} and b_i which form the following n linear equations:
 * 给定 n*(m+1) 个系数 a_{i,j} 和 b_i，它们构成以下 n 个线性方程：
 * 
 * a_{1,1}x_1 + a_{1,2}x_2 + ... + a_{1,m}x_m = b_1 (mod 10^9 + 7)
 * a_{2,1}x_1 + a_{2,2}x_2 + ... + a_{2,m}x_m = b_2 (mod 10^9 + 7)
 * ...
 * a_{n,1}x_1 + a_{n,2}x_2 + ... + a_{n,m}x_m = b_n (mod 10^9 + 7)
 * 
 * Your task is to find any m integers x_1, x_2, ..., x_m that satisfy the given equations.
 * 你的任务是找到满足给定方程的任意 m 个整数 x_1, x_2, ..., x_m。
 * 
 * Input / 输入
 * The first line has two integers n and m: the number of equations and variables.
 * 第一行有两个整数 n 和 m：方程的数量和变量的数量。
 * 
 * The next n lines each have m+1 integers a_{i,1}, a_{i,2}, ..., a_{i,m}, b_i: the coefficients of the i-th equation.
 * 接下来的 n 行每行有 m+1 个整数 a_{i,1}, a_{i,2}, ..., a_{i,m}, b_i：第 i 个方程的系数。
 * 
 * Output / 输出
 * Print m integers x_1, x_2,..., x_m: the values of the variables that satisfy the equations. 
 * The values must also satisfy 0 <= x_i < 10^9 + 7. You can print any valid solution. If no solution exists print only -1.
 * 打印 m 个整数 x_1, x_2,..., x_m：满足方程的变量的值。
 * 这些值还必须满足 0 <= x_i < 10^9 + 7。你可以打印任何有效的解决方案。如果不存在解决方案，只打印 -1。
 * 
 * Constraints / 约束条件
 * 1 <= n, m <= 500
 * 0 <= a_{i,j}, b_i < 10^9 + 7
 * 
 * Example / 样例
 * Input:
 * 3 3
 * 2 0 1 7
 * 1 2 0 0
 * 1 3 1 2
 * 
 * Output:
 * 2 1000000006 3
 * --------------------------------------------------------
 */

// #include <iostream>
// #include <vector>

// using namespace std;

// const int MOD = 1e9 + 7;

// // 快速幂计算逆元
// long long power(long long base, long long exp) {
//     long long res = 1;
//     base %= MOD;
//     while (exp > 0) {
//         if (exp % 2 == 1) res = (res * base) % MOD;
//         base = (base * base) % MOD;
//         exp /= 2;
//     }
//     return res;
// }

// long long inverse(long long n) {
//     return power(n, MOD - 2);
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m;
//     if (!(cin >> n >> m)) return 0;

//     vector<vector<long long>> a(n, vector<long long>(m + 1));
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j <= m; ++j) {
//             cin >> a[i][j];
//             a[i][j] %= MOD;
//         }
//     }

//     int r = 0; // 当前处理的行数 (秩)
//     vector<int> pivot_col;

//     for (int c = 0; c < m; ++c) {
//         // 找到当前列的绝对值非零的行
//         int pivot = r;
//         while (pivot < n && a[pivot][c] == 0) {
//             pivot++;
//         }
        
//         if (pivot == n) continue; // 该列全为0，是自由变量

//         // 交换到当前行
//         swap(a[r], a[pivot]);

//         // 化当前主元为1
//         long long inv = inverse(a[r][c]);
//         for (int j = c; j <= m; ++j) {
//             a[r][j] = (a[r][j] * inv) % MOD;
//         }

//         // 消去其他行的当前列
//         for (int i = 0; i < n; ++i) {
//             if (i != r && a[i][c] != 0) {
//                 long long factor = a[i][c];
//                 for (int j = c; j <= m; ++j) {
//                     a[i][j] = (a[i][j] - factor * a[r][j]) % MOD;
//                     if (a[i][j] < 0) a[i][j] += MOD;
//                 }
//             }
//         }

//         pivot_col.push_back(c);
//         r++;
//     }

//     // 检查是否有解
//     for (int i = r; i < n; ++i) {
//         if (a[i][m] != 0) {
//             cout << -1 << "\n";
//             return 0;
//         }
//     }

//     // 提取特解，自由变量全部设为0
//     vector<long long> ans(m, 0);
//     for (int i = 0; i < r; ++i) {
//         ans[pivot_col[i]] = a[i][m];
//     }

//     for (int c = 0; c < m; ++c) {
//         cout << ans[c] << (c == m - 1 ? "" : " ");
//     }
//     cout << "\n";

//     return 0;
// }

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int M = 1000000007;

// 快速幂求逆元 (费马小定理)
ll inverse(ll x) {
    ll power = M - 2;
    ll result = 1;
    while (power > 0) {
        if (power & 1) result = result * x % M;
        x = x * x % M;
        power /= 2;
    }
    return result;
}

vector<vector<ll>> matrix;

// 第 row 行所有元素乘以 x (用于把主元化为 1)
void multiply(int row, int m, ll x) {
    for (int i = 0; i <= m; i++) {
        matrix[row][i] = matrix[row][i] * x % M;
    }
}

// row2 = row2 - row1 * x (用于消去其他行的对应变量)
void subtract(int row1, int row2, int m, ll x) {
    for (int i = 0; i <= m; i++) {
        matrix[row2][i] -= matrix[row1][i] * x % M;
        matrix[row2][i] = (matrix[row2][i] % M + M) % M;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(m + 1);
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
        cin >> matrix[i][m];
    }

    // chosen[i] 记录第 i 个方程（行）选择的“主元列”（也就是确定了求解哪个变量）
    vector<int> chosen(n, -1);
    
    for (int i = 0; i < n; i++) {
        bool found = false;
        // 寻找第 i 行第一个系数不为 0 的变量
        for (int j = 0; j < m; j++) {
            if (matrix[i][j]) {
                chosen[i] = j;  // 将该列作为第 i 行的主元
                multiply(i, m, inverse(matrix[i][j])); // 将主元系数化为 1
                found = true;
                break;
            }
        }

        // 全 0 行，但常数项非零，方程无解
        if (!found && matrix[i][m]) {
            cout << "-1\n";
            return 0;
        }

        // 用这个已经归一化的主元，消掉其他所有方程 (即其他行) 中第 chosen[i] 列的系数
        if (found) {
            for (int j = 0; j < n; j++) {
                if (i == j || !matrix[j][chosen[i]]) continue;
                subtract(i, j, m, matrix[j][chosen[i]]);
            }
        }
    }

    // 检查并输出结果
    for (int i = 0; i < m; i++) {
        bool found = false;
        // 查找第 i 个变量是否在某一行中被作为主元解出
        for (int j = 0; j < n; j++) {
            if (chosen[j] == i) {
                cout << matrix[j][m] << " ";
                found = true;
                break;
            }
        }
        // 如果没有被当做主元，说明是自由变量，直接赋特解 0
        if (!found) cout << 0 << " ";
    }
    cout << "\n";
    return 0;
}