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
