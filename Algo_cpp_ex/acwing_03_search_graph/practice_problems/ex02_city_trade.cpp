/*
 * 综合练习题2：城市贸易 (City Trade)
 * 难度：⭐⭐⭐
 * 
 * 【题目描述】
 * C 国有 N 个城市 (1~N)，城市间有 M 条单向道路。
 * 每个城市 i 都有一个商品价格 price[i]。
 * 你从城市 1 出发，最终要到达城市 N。
 * 途中你可以在【任意一个】城市买入一次商品，
 * 并在之后的【任意一个】城市卖出一次商品（先买后卖，只能交易一次）。
 * 求最大利润。如果无法获利或无法到达终点，输出 0。
 * 
 * 【数据范围】
 * N <= 100,000, M <= 500,000
 * price[i] <= 100
 * 
 * 【算法思路：双向 SPFA / Dijkstra】
 * 利润 = 卖出价格 - 买入价格
 * 假设我们在城市 k 进行交易，或者 k 分割了买和卖的路径。
 * 我们需要知道：
 * 1. d_min[k]: 从起点 1 走到 k 的过程中，经过的所有城市里，价格最低是多少？
 * 2. d_max[k]: 从 k 走到终点 N 的过程中，经过的所有城市里，价格最高是多少？
 * 
 * 最终答案就是枚举所有 k: max(d_max[k] - d_min[k])
 * 
 * 【实现细节】
 * 1. d_min[]: 从 1 号点出发跑一遍正向图的最短路（其实是"最小权值路"）。
 *    即 d_min[y] = min(d_min[y], d_min[x], price[y])。
 *    注意：这里不是求边权和，而是路径上的点权最小值，状态转移 slightly different。
 * 
 * 2. d_max[]: 从 N 号点出发跑一遍反向图（需要建反向图）。
 *    即 d_max[y] = max(d_max[y], d_max[x], price[y])。
 * 
 * 为什么用 SPFA？因为不是求边权和，Dijkstra 的贪心性质在这里需要仔细考量（如果只求最小值其实是可以的，类似于 Prim），
 * 但 SPFA 的队列更新逻辑天然适合这种"状态传递"。
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 100010, M = 500010; // 点多边多
const int INF = 0x3f3f3f3f;

int n, m;
int prices[N];

// 正向图 (求最小值)
int h[N], e[M], ne[M], idx;
// 反向图 (求最大值)
int rh[N], re[M], rne[M], ridx;

int dmin[N]; // dmin[i]: 1 -> i 路径上的最小价格
int dmax[N]; // dmax[i]: i -> N 路径上的最大价格
bool st[N];

void add(int *h, int *e, int *ne, int &idx, int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

// type 0: 正向求 min
// type 1: 反向求 max
void spfa(int start, int type) {
    queue<int> q;
    memset(st, 0, sizeof st);

    if (type == 0) {
        memset(dmin, 0x3f, sizeof dmin);
        dmin[start] = prices[start]; // 起点价格
        q.push(start);
        st[start] = true;
    } else {
        memset(dmax, -0x3f, sizeof dmax); // 求最大值初始化为负无穷(或0)
        dmax[start] = prices[start];
        q.push(start);
        st[start] = true;
    }

    while (q.size()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        // 遍历邻居
        // 正向用 h[], 反向用 rh[]
        int *cur_h = (type == 0) ? h : rh;
        int *cur_e = (type == 0) ? e : re;
        int *cur_ne = (type == 0) ? ne : rne;

        for (int i = cur_h[t]; i != -1; i = cur_ne[i]) {
            int j = cur_e[i];
            bool updated = false;

            if (type == 0) {
                // 正向：我要找路径上经过的更小的价格
                // dmin[j] 可以被更新，如果：
                // 1. 上一步 dmin[t] 比我小
                // 2. 或者我自己 prices[j] 就很小
                int new_min = min(dmin[t], prices[j]);
                if (dmin[j] > new_min) {
                    dmin[j] = new_min;
                    updated = true;
                }
            } else {
                // 反向：我要找路径上经过的更大的价格
                int new_max = max(dmax[t], prices[j]);
                if (dmax[j] < new_max) {
                    dmax[j] = new_max;
                    updated = true;
                }
            }

            if (updated) {
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &prices[i]);

    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);

    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        // 原题是 a->b 单向
        // c 是 1:单向 2:双向
        // 为简化模型，我们假设输入就是简单的 a->b
        // 实际题目中如果是双向边，就正反各加一次
        add(h, e, ne, idx, a, b);
        add(rh, re, rne, ridx, b, a); // 建反图
        if (c == 2) {
            add(h, e, ne, idx, b, a);
            add(rh, re, rne, ridx, a, b);
        }
    }

    // 1. 从起点 1 出发，算出 dmin[] (路过的最便宜价格)
    spfa(1, 0);

    // 2. 从终点 N 出发(在反图上跑)，算出 dmax[] (路过的最贵价格)
    spfa(n, 1);

    int res = 0;
    // 枚举每一个可能的交易中转点 i
    for (int i = 1; i <= n; i++) {
        res = max(res, dmax[i] - dmin[i]);
    }

    printf("%d\n", res);

    return 0;
}
