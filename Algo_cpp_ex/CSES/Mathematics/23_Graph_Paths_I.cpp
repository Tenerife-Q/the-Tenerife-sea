/*
 * ============================================================================
 * CSES Problem Set - Graph Paths I
 * Problem #23
 * ============================================================================
 * 
 * 【中文题意】
 * 给定一个有向图，它有n个节点和m条边。
 * 你的任务是计算从节点1到节点n恰好经过k条边的路径数量。
 * 
 * 【英文题意】
 * Consider a directed graph that has n nodes and m edges. Your task is to 
 * count the number of paths from node 1 to node n with exactly k edges.
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
 * 接下来的m行描述边。每行包含两个整数 a 和 b：
 *   - 从节点a到节点b有一条边
 * 
 * 【Input Format】
 * The first input line contains three integers n, m and k: the number of 
 * nodes and edges, and the length of the path. The nodes are numbered 
 * 1, 2, ..., n.
 * 
 * Then, there are m lines describing the edges. Each line contains two 
 * integers a and b: there is an edge from node a to node b.
 * 
 * ============================================================================
 * 
 * 【输出格式】
 * 输出从节点1到节点n恰好k条边的路径数量，对10^9+7取模。
 * 
 * 【Output Format】
 * Print the number of paths modulo 10^9+7.
 * 
 * ============================================================================
 * 
 * 【约束条件】
 * - 1 ≤ n ≤ 100
 * - 1 ≤ m ≤ n(n-1)
 * - 1 ≤ k ≤ 10^9
 * - 1 ≤ a, b ≤ n
 * 
 * 【Constraints】
 * - 1 ≤ n ≤ 100
 * - 1 ≤ m ≤ n(n-1)
 * - 1 ≤ k ≤ 10^9
 * - 1 ≤ a, b ≤ n
 * 
 * ============================================================================
 * 
 * 【示例】
 * 输入：
 * 3 4 8
 * 1 2
 * 2 3
 * 3 1
 * 3 2
 * 
 * 输出：
 * 2
 * 
 * 【Example】
 * Input:
 * 3 4 8
 * 1 2
 * 2 3
 * 3 1
 * 3 2
 * 
 * Output:
 * 2
 * 
 * ============================================================================
 * 
 * 【解释说明】
 * 路径为：
 * - 1 → 2 → 3 → 1 → 2 → 3 → 1 → 2 → 3
 * - 1 → 2 → 3 → 2 → 3 → 2 → 3 → 2 → 3
 * 
 * 【Explanation】
 * The paths are:
 * - 1 → 2 → 3 → 1 → 2 → 3 → 1 → 2 → 3
 * - 1 → 2 → 3 → 2 → 3 → 2 → 3 → 2 → 3
 * 
 * ============================================================================
 * 
 * 【解题思路】
 * 
 * 这个问题可以通过矩阵快速幂求解：
 * 
 * 1. 构建邻接矩阵A，其中A[i][j]表示是否存在从i到j的边
 * 2. A^k的第一行第n列元素就是从节点1到节点n恰好k条边的路径数量
 * 3. 这是因为矩阵乘法的性质：(A^k)[i][j]表示从i到j恰好k条边的路径数
 * 4. 由于k很大（最大10^9），需要使用快速幂算法来高效计算A^k
 * 5. 所有计算过程中要对10^9+7取模
 * 
 * 时间复杂度：O(n^3 * log k)
 * 空间复杂度：O(n^2)
 * 
 * 【Solution Approach】
 * 
 * This problem can be solved using matrix exponentiation:
 * 
 * 1. Build an adjacency matrix A where A[i][j] indicates whether there is 
 *    an edge from node i to node j
 * 2. The element at position [0][n-1] in A^k gives the number of paths
 *    from node 1 to node n with exactly k edges
 * 3. This works because (A^k)[i][j] represents the number of paths from 
 *    i to j using exactly k edges
 * 4. Since k can be very large (up to 10^9), we use fast exponentiation 
 *    to efficiently compute A^k
 * 5. All calculations should be done modulo 10^9+7
 * 
 * Time Complexity: O(n^3 * log k)
 * Space Complexity: O(n^2)
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

// 使用 vector 嵌套定义矩阵
typedef vector<vector<long long>> Matrix;

// 矩阵乘法函数
Matrix multiply(const Matrix &A, const Matrix &B, int n) {
    // 初始化一个 n*n 全为 0 的矩阵
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (A[i][k] == 0) continue; // 常数级优化：如果为0直接跳过，加快运算
            for (int j = 0; j < n; j++) {
                // 计算乘积并取模，注意要在加法后立即取模防止越界
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂函数
Matrix power(Matrix A, long long p, int n) {
    // res 初始化为单位矩阵 (主对角线为1，其余为0)
    // 单位矩阵的作用相当于普通数字快速幂中的 1
    Matrix res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    
    // 经典的二进制快速幂框架
    while (p > 0) {
        if (p % 2 == 1) {
            res = multiply(res, A, n); // 如果当前末位为1，乘入结果矩阵
        }
        A = multiply(A, A, n);         // 矩阵平方
        p /= 2;                        // 指数右移
    }
    return res;
}

int main() {
    // 优化输入输出流速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;
    
    // 构建图的初始邻接矩阵
    Matrix adj(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 将 1-based 节点编号转换为 0-based
        adj[u][v]++; // 因为图中可能有重边，因此这里用 ++ 累加边数
    }
    
    // 计算邻接矩阵的 k 次幂
    Matrix res = power(adj, k, n);
    
    // 我们要求的是从节点 1 (索引0) 到节点 n (索引n-1) 的路径数
    cout << res[0][n-1] << "\n";
    
    return 0;
}