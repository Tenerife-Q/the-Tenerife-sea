/*
 * ============================================================================
 * CSES Problem Set - Graph Paths II
 * Problem #24
 * ============================================================================
 * 
 * 【中文题意】
 * 给定一个有向加权图，它有n个节点和m条边。
 * 你的任务是计算从节点1到节点n恰好经过k条边的最小路径长度。
 * 
 * 【英文题意】
 * Consider a directed weighted graph having n nodes and m edges. Your task 
 * is to calculate the minimum path length from node 1 to node n with exactly 
 * k edges.
 * 
 * ============================================================================
 * 
 * 【输入格式】
 * 第一行包含三个整数 n, m 和 k：
 *   - n：节点的数量
 *   - m：边的数量
 *   - k：路径的长度（边数）
 * 节点编号为 1, 2, ..., n
 * 
 * 接下来的m行描述边。每行包含三个整数 a, b 和 c：
 *   - 从节点a到节点b有一条权重为c的边
 * 
 * 【Input Format】
 * The first input line contains three integers n, m and k: the number of 
 * nodes and edges, and the length of the path. The nodes are numbered 
 * 1, 2, ..., n.
 * 
 * Then, there are m lines describing the edges. Each line contains three 
 * integers a, b and c: there is an edge from node a to node b with weight c.
 * 
 * ============================================================================
 * 
 * 【输出格式】
 * 输出从节点1到节点n恰好k条边的最小路径长度。
 * 如果不存在这样的路径，输出 -1。
 * 
 * 【Output Format】
 * Print the minimum path length. If there are no such paths, print -1.
 * 
 * ============================================================================
 * 
 * 【约束条件】
 * - 1 ≤ n ≤ 100
 * - 1 ≤ m ≤ n(n-1)
 * - 1 ≤ k ≤ 10^9
 * - 1 ≤ a, b ≤ n
 * - 1 ≤ c ≤ 10^9
 * 
 * 【Constraints】
 * - 1 ≤ n ≤ 100
 * - 1 ≤ m ≤ n(n-1)
 * - 1 ≤ k ≤ 10^9
 * - 1 ≤ a, b ≤ n
 * - 1 ≤ c ≤ 10^9
 * 
 * ============================================================================
 * 
 * 【示例】
 * 输入：
 * 3 4 8
 * 1 2 5
 * 2 3 4
 * 3 1 1
 * 3 2 2
 * 
 * 输出：
 * 27
 * 
 * 【Example】
 * Input:
 * 3 4 8
 * 1 2 5
 * 2 3 4
 * 3 1 1
 * 3 2 2
 * 
 * Output:
 * 27
 * 
 * ============================================================================
 * 
 * 【解题思路】
 * 
 * 这个问题需要用到矩阵快速幂的变体，使用"最小加"代数：
 * 
 * 1. 构建邻接矩阵D，其中D[i][j]表示从i到j的边的权重
 *    - 如果不存在边，则设为无穷大（INF）
 * 2. 矩阵乘法改为"最小加"运算：
 *    C[i][j] = min(A[i][k] + B[k][j]) for all k
 *    而不是普通的矩阵乘法（求和与求积）
 * 3. D^k的第一行第n列元素就是从节点1到节点n恰好k条边的最小路径长度
 * 4. 使用快速幂算法高效计算D^k，时间复杂度为O(n^3 * log k)
 * 5. 如果结果是INF，则输出-1，表示不存在这样的路径
 * 
 * 【Solution Approach】
 * 
 * This problem requires a variant of matrix exponentiation using "min-plus" 
 * algebra (tropical semiring):
 * 
 * 1. Build an adjacency matrix D where D[i][j] represents the weight of 
 *    the edge from node i to node j
 *    - If no edge exists, set it to infinity (INF)
 * 2. Replace matrix multiplication with "min-plus" operation:
 *    C[i][j] = min(A[i][k] + B[k][j]) for all k
 *    instead of normal matrix multiplication (sum and product)
 * 3. The element at position [0][n-1] in D^k gives the minimum path 
 *    length from node 1 to node n with exactly k edges
 * 4. Use fast exponentiation to efficiently compute D^k with time complexity 
 *    O(n^3 * log k)
 * 5. If the result is INF, output -1, indicating no such path exists
 * 
 * Time Complexity: O(n^3 * log k)
 * Space Complexity: O(n^2)
 * 
 * ============================================================================
 */



// 1. npc
// #include <bits/stdc++.h>
// using namespace std;

// const long long INF = 1e18;

// // Function to perform "min-plus" matrix multiplication
// // 执行"最小加"矩阵乘法
// vector<vector<long long>> matmul(const vector<vector<long long>>& A, 
//                                   const vector<vector<long long>>& B, 
//                                   int n) {
//     vector<vector<long long>> C(n, vector<long long>(n, INF));
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             for (int k = 0; k < n; k++) {
//                 // Instead of C[i][j] = sum(A[i][k] * B[k][j])
//                 // We do: C[i][j] = min(A[i][k] + B[k][j])
//                 // 不是C[i][j] = sum(A[i][k] * B[k][j])
//                 // 而是：C[i][j] = min(A[i][k] + B[k][j])
//                 if (A[i][k] != INF && B[k][j] != INF) {
//                     C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
//                 }
//             }
//         }
//     }
//     return C;
// }

// // Function to compute A^k using fast exponentiation with "min-plus" operation
// // 快速幂函数：计算A^k（使用"最小加"运算）
// vector<vector<long long>> matpow(vector<vector<long long>>& A, 
//                                   long long k, 
//                                   int n) {
//     vector<vector<long long>> result(n, vector<long long>(n, INF));
//     // Initialize result as identity matrix (distance from node to itself is 0)
//     // 将result初始化为单位矩阵（节点到自身的距离为0）
//     for (int i = 0; i < n; i++) {
//         result[i][i] = 0;
//     }
    
//     while (k > 0) {
//         if (k & 1) {
//             result = matmul(result, A, n);
//         }
//         A = matmul(A, A, n);
//         k >>= 1;
//     }
    
//     return result;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
    
//     int n, m;
//     long long k;
//     cin >> n >> m >> k;
    
//     // Build adjacency matrix with INF as initial values
//     // 构建邻接矩阵，初始值为INF
//     vector<vector<long long>> adj(n, vector<long long>(n, INF));
    
//     // Distance from a node to itself is 0 in the initial setup
//     // 初始化时，节点到自身的距离为INF（因为至少需要一条边）
//     // for (int i = 0; i < n; i++) {
//     //     adj[i][i] = 0;  // This would be wrong for path with k edges
//     // }
    
//     for (int i = 0; i < m; i++) {
//         int a, b;
//         long long c;
//         cin >> a >> b >> c;
//         a--; b--;  // Convert to 0-indexed
//         // Keep the minimum weight if there are multiple edges between same pair
//         // 如果同一对节点间有多条边，保留最小权重
//         adj[a][b] = min(adj[a][b], c);
//     }
    
//     // Compute A^k using fast exponentiation
//     // 计算A^k
//     vector<vector<long long>> result = matpow(adj, k, n);
    
//     // The answer is result[0][n-1]
//     // 答案是result[0][n-1]
//     long long ans = result[0][n - 1];
    
//     if (ans == INF) {
//         cout << -1 << endl;
//     } else {
//         cout << ans << endl;
//     }
    
//     return 0;
// }




/*
#include <iostream>
#include <algorithm> // 为了使用 min

using namespace std;
using ll = long long;

const ll INF = 4e18; // 使用一个足够大的数代表无穷，防止加法溢出
const int MAXN = 105;

struct Matrix {
    int n;
    ll m[MAXN][MAXN];

    // 构造函数：初始化大小并用 INF 填充
    Matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m[i][j] = INF;
            }
        }
    }

    // 【核心修改点 1】：重定义矩阵乘法为 (min, +)
    Matrix operator*(const Matrix& b) const {
        Matrix res(n); // res 构造时已自动填充 INF
        
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                // 如果从 i 到 k 没有路，则跳过，这是一个关键剪枝
                if (m[i][k] == INF) continue; 
                
                for (int j = 0; j < n; ++j) {
                    if (b.m[k][j] == INF) continue; // 如果从 k 到 j 没路，也跳过
                    
                    // 新的乘法法则
                    res.m[i][j] = min(res.m[i][j], m[i][k] + b.m[k][j]);
                }
            }
        }
        return res;
    }

    // 快速幂封装
    Matrix power(ll p) const {
        Matrix res(n);
        // 【核心修改点 2】：新的单位矩阵，对角线为 0
        for (int i = 0; i < n; i++) res.m[i][i] = 0; 
        
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll k;
    if (!(cin >> n >> m >> k)) return 0;

    Matrix g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        u--; v--; 
        
        // 【核心修改点 3】：处理重边时，取权值最小的那条
        g.m[u][v] = min(g.m[u][v], c);
    }

    Matrix ans = g.power(k);

    ll result = ans.m[0][n - 1];

    // 【核心修改点 4】：如果结果依然是 INF，说明没有路径
    if (result == INF) {
        cout << -1 << "\n";
    } else {
        cout << result << "\n";
    }

    return 0;
}
*/




#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 2e18;

template <int N>
struct Matrix {
    ll m[N][N];

    // 【为什么这里必须手写构造函数？】
    // 本题求最短路径，矩阵的默认初始状态应该是无穷大（INF），否则在做 min() 运算时会全错。
    // 由于 C++ 的 {} 语法只能清零，无法一键填充 INF，
    // 因此必须手写带有默认参数的构造函数：传参时（如 Matrix<N> g(INF)）全填INF，不传参时默认填0。
    Matrix<N>(ll x = 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                m[i][j] = x;
            }
        }
    }

    static Matrix<N> ident() {
        Matrix<N> r(INF);
        for (int i = 0; i < N; i++) r.m[i][i] = 0;
        return r;
    }

    Matrix<N> operator*(const Matrix<N> &b) const {
        Matrix<N> r(INF);
        // 这里还是应该采用 i -> k -> j 的循环顺序，完美契合 CPU 缓存，详见md文讲解
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    r.m[i][j] = min(r.m[i][j], m[i][k] + b.m[k][j]);
                }
            }
        }
        return r;
    }

    // 这里使用递归版本的快速幂，代码更简洁
    // Matrix<N> power(ll b) const {
    //     Matrix<N> res = ident();
    //     Matrix<N> a = *this;
    //     while (b > 0) {
    //         if (b & 1) res = res * a;
    //         a = a * a;
    //         b >>= 1;
    //     }
    //     return res;
    // }
    Matrix<N> power(ll b) {
        if (b == 0) return ident();
        auto a = *this;
        return b & 1 ? a.power(b - 1) * a : (a * a).power(b / 2);
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    Matrix<101> g(INF);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.m[a][b] = min(g.m[a][b], (ll)c);
    }

    auto p = g.power(k);
    ll answer = p.m[1][n];
    if (answer == INF) answer = -1;
    cout << answer << "\n";
}