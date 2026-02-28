#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

// Problem 3: 繁忙的物流 (0/1分数规划 + 最小生成树)
//
// 题目描述:
// 有 N 个物流中心，M 条可能的连接道路。
// 每条道路有两个属性：建设成本 C 和 维护成本 V。
// 我们需要选择 N-1 条道路将所有中心连通（即形成生成树）。
// 目标是让总建设成本 / 总维护成本 的比值最小。
// 即 minimize (Sum(C) / Sum(V))
//
// 输入格式:
// 第一行 N, M (1 <= N <= 1000, 1 <= M <= 10000)
// 接下来 M 行，每行 u, v, c, v_cost (1 <= c, v_cost <= 100)
//
// 输出格式:
// 输出最小的比值，保留 2 位小数。

const int MAXN = 1010;
const int MAXM = 10010;

struct Edge {
    int u, v;
    double c, v_cost; // construction cost, maintenance cost
    double weight; // temporary weight for Kruskal: c - x * v_cost
    
    // 按权重排序
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
} edges[MAXM];

int parent[MAXN];
int n, m;

// 并查集查找
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

// 检查是否存在一种方案使得 (Sum(C) / Sum(V)) <= x
// 变换不等式: Sum(C) <= x * Sum(V) => Sum(C) - x * Sum(V) <= 0
// => Sum(C - x * V) <= 0
// 即：如果把每条边的权值设为 w = c - x * v，
// 它的最小生成树的总权值是否 <= 0
bool check(double x) {
    // 1. 重新计算每条边的权重
    for (int i = 0; i < m; i++) {
        edges[i].weight = edges[i].c - x * edges[i].v_cost;
    }
    
    // 2. 按新权重排序 (Kruskal)
    sort(edges, edges + m);
    
    // 3. 计算 MST 权值和
    for (int i = 1; i <= n; i++) parent[i] = i;
    
    double sum_weight = 0;
    int edges_count = 0;
    
    for (int i = 0; i < m; i++) {
        int root_u = find(edges[i].u);
        int root_v = find(edges[i].v);
        
        if (root_u != root_v) {
            parent[root_u] = root_v;
            sum_weight += edges[i].weight;
            edges_count++;
        }
    }
    
    // 如果无法连通所有点（通常题目保证图连通，但为了稳健性检查）
    if (edges_count < n - 1) return false; // 无法构成生成树
    
    return sum_weight <= 0;
}

int main() {
    // 优化 IO
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    if (cin >> n >> m) {
        for (int i = 0; i < m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].c >> edges[i].v_cost;
        }

        // 二分答案
        // 最小比值范围 [0, 100] (因为 C, V <= 100, max C / min V = 100/1)
        // 实际上可以更大，设稍微大一点比如 10000 也没问题
        double l = 0, r = 10000; 
        
        // 二分很多次保证精度，或者用 while(r - l > 1e-8)
        for (int i = 0; i < 100; i++) {
            double mid = (l + r) / 2;
            if (check(mid)) {
                r = mid; // 如果可行，尝试更小的比值
            } else {
                l = mid; // 不可行，说明比值太小了
            }
        }
        
        cout << fixed << setprecision(2) << l << endl;
    } else {
        // 提供默认测试数据演示
        cout << "请输入数据 (N M, 然后 M 行 u v c v_cost)..." << endl;
        cout << "示例输入:" << endl; 
        cout << "3 3" << endl;
        cout << "1 2 10 2" << endl;
        cout << "2 3 20 5" << endl;
        cout << "1 3 30 8" << endl;
        
        // 硬编码跑一次示例
        n = 3; m = 3;
        edges[0] = {1, 2, 10, 2};
        edges[1] = {2, 3, 20, 5};
        edges[2] = {1, 3, 30, 8};
        
        double l = 0, r = 10000;
        for(int i=0; i<100; i++) {
            double mid = (l + r) / 2;
            if(check(mid)) r = mid;
            else l = mid;
        }
        cout << "示例输出: " << fixed << setprecision(2) << l << endl; 
    }
    
    return 0;
}
