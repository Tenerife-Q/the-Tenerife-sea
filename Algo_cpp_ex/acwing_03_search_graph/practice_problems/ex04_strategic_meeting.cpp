#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
const int MAXN = 100010;

// Problem 4: 战略会议 (树的重心 / 换根DP)
//
// 题目描述:
// 公司架构是一棵树，有 N 个节点。边有权值（距离）。
// 求一个节点 u，使得所有其他节点到 u 的距离之和最小。
// 输出最小的总距离。

struct Edge {
    int to;
    int weight;
};

vector<Edge> adj[MAXN];
int sz[MAXN]; // 子树大小
long long dist_sum[MAXN]; // 换根DP状态：以 i 为根的总距离
int n;
long long ans = INF;

// 第一次 DFS: 计算子树大小
void dfs1(int u, int p) {
    sz[u] = 1;
    for (auto& edge : adj[u]) {
        int v = edge.to;
        if (v == p) continue;
        
        dfs1(v, u);
        sz[u] += sz[v];
    }
}

// 辅助 DFS: 计算 dist_sum[1] (所有点到根节点 1 的距离)
void get_root_dist(int u, int p, long long current_dist) {
    dist_sum[1] += current_dist;
    for (auto& edge : adj[u]) {
        int v = edge.to;
        if (v == p) continue;
        get_root_dist(v, u, current_dist + edge.weight);
    }
}

// 第二次 DFS: 换根 DP
// 状态转移方程:
// 当根从 u 移动到 v (u -> v, 边权 w):
// v 子树内的点 (sz[v] 个) 到新根 v 的距离减少 w
// v 子树外的点 (n - sz[v] 个) 到新根 v 的距离增加 w
// dp[v] = dp[u] - sz[v] * w + (n - sz[v]) * w
//       = dp[u] + (n - 2 * sz[v]) * w
void dfs2(int u, int p) {
    ans = min(ans, dist_sum[u]);
    
    for (auto& edge : adj[u]) {
        int v = edge.to;
        int w = edge.weight;
        if (v == p) continue;
        
        dist_sum[v] = dist_sum[u] + (long long)(n - 2 * sz[v]) * w;
        dfs2(v, u);
    }
}

/*
void dfs1(int u, int p) {
    sz[u] = 1;
    for(Edge& edge : adj[u]) {
        int v = edge.to;
        if(v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }
}

void get_root_dist(int u, int p, long long current_dist) {
    dist_sum[1] += current_dist;
    for(Edge& edge : adj[u]) {
        int v = edge.to;
        if(v == p) continue;
        get_root_dist(v, u, current_dist + edge.weight);
    }
}

void dfs2(int u, int p) {
    ans = min(ans, dist_sum[u]);
    for(Edge& edge : adj[u]) {
        int v = edge.to;
        int w = edge.weight;
        if( v == p ) continue;
        dist_sum[v] = dist_sum[u] + (long long)(n - 2 * sz[v]) * w;
        dfs2(v, u);
    }
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    if (cin >> n) {
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // 无向图
        }
        
        // 1. 初始化
        // 计算以节点 1 为根时的所有子树大小
        dfs1(1, 0); 
        
        // 计算 dist_sum[1] (所有点到 1 的距离和)
        dist_sum[1] = 0;
        get_root_dist(1, 0, 0);
        
        // 2. 换根 DP
        dfs2(1, 0);
        
        cout << ans << endl;
    } else {
        // 示例数据
        cout << "请输入 N (节点数) 和 N-1 条边 (u v w)..." << endl;
        // 构造一个简单的树
        // 1-2(1), 1-3(1), 2-4(1)
        // 重心显然在 1 或 2?
        // 1: 到2(1), 到3(1), 到4(2) -> 4
        // 2: 到1(1), 到3(2), 到4(1) -> 4
        // 3: 到1(1), 到2(2), 到4(3) -> 6
        // 4: 到1(2), 到2(1), 到3(3) -> 6
        cout << "示例输出: 4" << endl;
    }

    return 0;
}

/*
 * ==================================================================================
 * 【代码提纯解析：字段含义、防死环机制 与 递归逆向更新解构】
 * ==================================================================================
 * 
 * 一、 全局数据结构与字段含义
 * ----------------------------------------------------------------------------------
 * 1. vector<Edge> adj[MAXN]
 *    - 作用：图的邻接表存储。无向图中，每条边会在两个节点的邻接表里都出现一次。
 *    - 索引：adj[u] 表示节点 u 的所有边。
 *    - 元素：Edge {to, weight} 即连向的相邻节点 v 及边权 w。
 *    - 细节：1和2连通时，adj[1]里有2，adj[2]里有1。这是产生死循环的根源。
 * 
 * 2. int sz[MAXN]
 *    - 作用：存储子树的节点总数。
 *    - 索引：sz[u] 表示【以节点 1 为全局根节点时，以 u 为根的子树内包含的节点数量】。
 * 
 * 3. long long dist_sum[MAXN]
 *    - 作用：如果以节点 u 为会议中心，所有点走到 u 的绝对总距离。
 * 
 * 二、 核心解惑：`v == p` 的本质与“递归终止/逆向更新”机制
 * ----------------------------------------------------------------------------------
 * 
 * 【模块 1】 dfs1(int u, int p) —— 计算子树大小 (自底向上)
 * - 作用：求出以节点 1 为定根时，每个节点的子树大小。
 * - 参数：
 *   - u: 当前遍历到的节点。
 *   - p: 节点 u 的父节点。作用是防止通过无向图的边往回遍历（死循环）。
 * - 递归逻辑：
 *   对当前点 u 进行初始化 sz[u] = 1。然后遍历 u 的所有邻居，避开父节点 p 后，
 *   不断深入子节点 v，在子节点 v 的 sz[v] 计算完毕返回后，将其累加回父节点 sz[u]。
 * 
 * 【模块 2】 get_root_dist(int u, int p, long long current_dist) —— 计算基准解 (自顶向下)
 * - 作用：以节点 1 为根（基准点），求出全图所有点到节点 1 的距离总和，即 dist_sum[1]。
 * - 参数：
 *   - u: 当前遍历的节点。
 *   - p: 父节点（防死循环）。
 *   - current_dist: 从绝对根节点（点1）走到当前节点 u 的累计距离。
 * - 递归逻辑：
 *   走到某节点 u 时，直接把带有累计距离的 current_dist 累加到全局总账本 dist_sum[1] 中，
 *   然后带着 current_dist + w 继续往下传递给子节点 v。
 * 
 * 【模块 3】 dfs2(int u, int p) —— 换根状态转移 (核心)
 * - 作用：利用已知的父节点状态 dist_sum[u]，O(1) 速度推导出子节点状态 dist_sum[v]。
 * - 参数：
 *   - u: 旧根（当前会议中心），其 dist_sum[u] 已经是最终正确值。
 *   - p: 父节点。
 * - 核心状态转移方程剖析：
 *   代码：dist_sum[v] = dist_sum[u] + (long long)(n - 2 * sz[v]) * w;
 *   - dist_sum[u]: 父节点成为聚点时的全图总距离（已知）。
 *   - sz[v]: v 的子树内节点数。由于聚点从 u 移向 v，这些节点距离均缩短了 w，总缩减量为 sz[v] * w。
 *   - (n - sz[v]): 非 v 子树的节点数。聚点从 u 移向 v，这些节点的距离均增加了 w，总增加量为 (n - sz[v]) * w。
 *   - 合并：+ (n - sz[v]) * w - sz[v] * w  ==>  + (n - 2 * sz[v]) * w 
 * 
 * 
 * 【问题 1】`v == p` 是什么时候发生？这是不是递归的终止条件？
 * - 绝对不是终止条件！它是一个【防死查（剪枝）机制】。
 * - 发生时机：因为是无向图，程序从 1 下探到 2 时，传参变成了 `dfs(2, p=1)`。
 *   当程序遍历 `adj[2]` 的邻居时，必然会读到 1。此时 `v = 1`，恰好等于传进来的老爹 `p = 1`。
 * - 执行动作：触发 `if (v == p) continue;`，直接跳过 1，不往回搜！
 * - 真正的递归终止条件：是【把 for 循环跑完，自然结束函数】！
 *   当递归深潜到一个“叶子节点”（比如 3 这个点，它只和 2 相连）。
 *   进入 `dfs(3, p=2)` 时，遍历 `adj[3]` 只有 2 这个邻居，立刻触发 `v == p` 而 `continue`。
 *   循环结束，函数执行到底部大括号 `}`，这就叫**触底自然弹栈（终止并返回）**！
 * 
 * 【问题 2】怎么实现“逆向更新”（回溯 / 底部向上汇总）的？
 * - 靠的是【把变量赋值写在递归调用 `dfs()` 的后面】。
 * - 计算机的函数调用栈 (Call Stack) 机制决定了：写在 `dfs(v)` 后面的代码，
 *   必须等 `v` 及其所有的子子孙孙全部处理完、弹栈回来之后，才会被行！
 * 
 * 三、 三大核心模块的执行流剖析（自顶向下 vs 自底向上）
 * ----------------------------------------------------------------------------------
 * 
 * 【模块 1：dfs1(u, p) —— 自底向上计算子树大小】
 * ```cpp
 * void dfs1(int u, int p) {
 *     sz[u] = 1;                    // [前序处理] 刚进门，先把自己的 1 个名额算上
 *     for(auto& edge : adj[u]) {
 *         // ... 省略 v==p ...
 *         dfs1(v, u);               // [深潜] 暂停我当前的任务，等小弟 v 把名下所有人口查完
 *         sz[u] += sz[v];           // ★ [后序处理/逆向更新] 小弟回来了！把小弟的全部人头划入我的账下！
 *     }
 * }
 * ```
 * - 机制剖析：这里的赋值 `sz[u] += sz[v]` 完美实现了你所说的“逆向更新”。
 *   它的聚合方向是从最底层的叶子节点一路加回给上层节点，这就是经典的“后序遍历汇聚”。
 * 
 * 【模块 2：get_root_dist(u, p, current_dist) —— 自顶向下流水传播】
 * ```cpp
 * void get_root_dist(int u, int p, long long current_dist) {
 *     dist_sum[1] += current_dist;  // [前序处理] 刚到达 u，立刻把身上扛着的总里程数汇入老祖宗的总账
 *     for(auto& edge : adj[u]) {
 *         // ... 省略 v==p ...
 *         get_root_dist(v, u, current_dist + edge.weight); // [携带状态深潜] 
 *         // 没有后序处理！因为这只是个向下的派发过程。
 *     }
 * }
 * ```
 * - 机制剖析：注意！这里没有“逆向更新”。它的逻辑是“流水向下”。
 *   它把参数 `current_dist` 当作包裹，加上当前由于深入导致的距离加长 `edge.weight`，
 *   直接传递给下一层。
 * 
 * 【模块 3：dfs2(u, p) —— O(1)换根转移推导 (自顶向下逐层递推)】
 * ```cpp
 * void dfs2(int u, int p) {
 *     ans = min(ans, dist_sum[u]);  // 进来就打擂台，记录最小答案
 *     for(auto& edge : adj[u]) {
 *         // ... 省略 v==p ...
 *         
 *         // ★ [前序处理/状态转移]: 在还没跳到小弟 v 家之前，
 *         // 直接利用我自己(u)的满级总账，原地把小弟 v 成为根节点后的绝对总账算出来！
 *         dist_sum[v] = dist_sum[u] + (long long)(n - 2 * sz[v]) * w; 
 *         
 *         dfs2(v, u); // [带着算好的新账本深潜] 小弟拿到完整的账本后，继续向小弟的小弟去推导
 *     }
 * }
 * ```
 * - 机制剖析：这又是前序遍历（递推）。
 *   `dfs2` 的精妙之处在于：`u` 这个节点拥有的 `dist_sum[u]` 是必定正确的全局结果。
 *   只要它自身正确，通过上方 O(1) 的加减法算出来的 `dist_sum[v]` 就立刻是必定全局正确的！
 *   所以根本不需要“逆向更新”来帮忙，算法就像“推倒多米诺骨牌”一样，从点 1 一路把正确的账本顺着路**向下传递**给了所有的节点。
 * ==================================================================================
 */
