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




/*
3.
    vector 常规实现，代码量较大，性能一般：


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
*/






/*
4. 标答

官方题解中使用了 struct 来封装矩阵，直接在栈区分配数据，比 vector 快上百倍。以下是官方题解的代码实现：
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

template <int N>
struct Matrix {
    ll m[N][N];

    static Matrix<N> ident() {
        Matrix<N> r{};
        for (int i = 0; i < N; i++) r.m[i][i] = 1;
        return r;
    }

    Matrix<N> operator*(Matrix<N> b) {
        Matrix<N> r{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    r.m[i][j] += m[i][k] * b.m[k][j];
                    r.m[i][j] %= M;
                }
            }
        }
        return r;
    }

    Matrix<N> power(ll b) {
        if (b == 0) return ident();
        auto a = *this;
        return b & 1 ? a.power(b - 1) * a : (a * a).power(b / 2);
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    Matrix<101> g{};
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g.m[a][b]++;
    }

    auto p = g.power(k);
    cout << p.m[1][n] << "\n";
}
*/






/*
1.

    优化后的代码 没有空间浪费，且性能极佳，但是代码量较大，书写较麻烦。


#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 105;

struct Matrix {
    int n; // 动态记录当前的矩阵大小，杜绝循环浪费
    
    // 【现代 C++ 魔法】：加上 ={}，创建时自动全初始化为 0，告别 memset！
    ll m[MAXN][MAXN] = {}; 

    // 构造函数：只需传入 n 即可，数组 m 已经被自动清零了
    Matrix(int _n) {
        n = _n;
    }

    // 重载乘法运算符 (加入 const 和引用，避免 80KB 拷贝开销)
    Matrix operator*(const Matrix& b) const {
        Matrix res(n); // 创建结果矩阵，内部 m 自动全为 0
        
        // 【不浪费算力】：只循环真实的 n 次，且顺序为 i -> k -> j 保护 CPU 缓存
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                // 【常数剪枝】：遇到 0 直接跳过
                if (m[i][k] == 0) continue; 
                
                for (int j = 0; j < n; ++j) {
                    res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j]) % MOD;
                }
            }
        }
        return res;
    }

    // 快速幂封装
    Matrix power(ll p) const {
        Matrix res(n);
        // 初始化为单位矩阵
        for (int i = 0; i < n; i++) res.m[i][i] = 1; 
        
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
    // 提速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll k;
    if (!(cin >> n >> m >> k)) return 0;

    // 动态传入节点数 n
    Matrix g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // 【回归 0-based 索引】：节点编号转为 0 到 n-1
        u--; v--; 
        g.m[u][v]++;
    }

    // 面向对象式调用
    Matrix ans = g.power(k);

    // 【精准提取】：因为采用了 0-based，起点是 0，终点是 n-1
    cout << ans.m[0][n - 1] << "\n";

    return 0;
}
*/





/*
2.
    综合标答的代码 书写更简洁
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

// 【保留官方优点】：使用模板，优雅且自包含
template <int N>
struct Matrix {
    ll m[N][N];

    // 【保留官方优点】：生成单位矩阵，利用 {} 自动初始化为 0
    static Matrix<N> ident() {
        Matrix<N> r{};
        for (int i = 0; i < N; i++) r.m[i][i] = 1;
        return r;
    }

    // 【融合优化 3】：使用 const 和引用 (&)，避免 80KB 的内存拷贝！
    Matrix<N> operator*(const Matrix<N>& b) const {
        Matrix<N> r{}; // 自动全初始化为 0，替代 memset
        
        // 【融合优化 2】：循环顺序改为 i -> k -> j，对 CPU 缓存极其友好
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                // 【融合优化 1】：常数级剪枝，遇到 0 直接跳过
                if (m[i][k] == 0) continue; 
                
                for (int j = 0; j < N; ++j) {
                    r.m[i][j] += m[i][k] * b.m[k][j];
                    r.m[i][j] %= MOD;
                }
            }
        }
        return r;
    }

    // 【融合优化 4】：将迭代版快速幂封装在结构体内，既优雅又不爆栈
    Matrix<N> power(ll p) const {
        Matrix<N> res = ident(); // 初始为单位矩阵
        Matrix<N> a = *this;     // 复制当前矩阵进行自乘
        
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

    // 【保留官方优点】：实例化大小为 101 的矩阵，使用 1-based 索引，直接契合题目
    Matrix<101> g{};
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.m[u][v]++; // 处理重边
    }

    // 面向对象式调用，极致清爽
    Matrix<101> ans = g.power(k);

    cout << ans.m[1][n] << "\n";

    return 0;
}
*/

// 这里采取第二种
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;

template <int N>
struct Matrix {
    ll m[N][N];

    static Matrix<N> ident() {
        Matrix<N> r{};
        for (int i = 0; i< N; i++) r.m[i][i] = 1;
        return r;
    }

    Matrix<N> operator*(const Matrix<N>& b) const {
        Matrix<N> r{};
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                if (m[i][k] == 0) continue; 
                for (int j = 0; j < N; ++j) {
                    r.m[i][j] = (r.m[i][j] + m[i][k] * b.m[k][j]) % MOD;
                }
            }
        }
        return r;
    }

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

    int n, m;
    ll k;
    if (!(cin >> n >> m >> k)) return 0;

    Matrix<101> g{};
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // 这里没有转换为 0-based 索引，即没有 u--, v--, 因为官方题解直接使用了 1-based 索引，直接存储在 g.m[u][v] 中
        // 因为N是101很大 >> n，所以直接使用1-based索引不会有问题，反而更直观地对应题目中的节点编号
        // 这里如果转换为0-based索引，也没问题，只是后续访问时就需要调整为g.m[u-1][v-1]，反而增加了代码复杂度和出错风险
        g.m[u][v]++;
    }

    Matrix<101> ans = g.power(k);
    // 注意：因为使用了 1-based 索引，所以起点是 1，终点是 n
    cout << ans.m[1][n] << "\n";

    return 0;
}