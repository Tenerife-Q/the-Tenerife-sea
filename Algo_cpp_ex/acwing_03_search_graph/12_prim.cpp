/*
 * ============================================
 *   Prim 算法 (普里姆算法) - 最小生成树
 *   时间复杂度：O(N^2) (朴素版，适合稠密图)
 *   
 *   【也就是"最近邻居法"】
 *   想象我们是一个探险队，要修路把所有村庄连起来，费用要最低。
 *   
 *   集合 S: 已经修好路、通了网的村庄。
 *   集合 V: 还没通网的村庄。
 *   dist[i]: i号村庄 距离 "S集合" 最近的距离 (注意：不是距离起点的距离，是距离“已连接部分”的距离)
 *   
 *   【算法流程】
 *   1. 随便选个点(比如1号)作为起点，加入 S。
 *   2. 只要还有村庄没进 S：
 *      a. 找到 V 中距离 S 最近的一个村庄 t。
 *      b. 把 t 拉进 S (修这条最短的路)。
 *      c. 用 t 更新其他村庄到 S 的距离。
 *         (也许有个村庄 k，本来离 S 很远，但离 t 很近，现在 t 进来了，k 离 S 也近了)
 * 
 *   【对比 Dijkstra】
 *   长得非常像！唯一的区别是 dist 的定义：
 *   - Dijkstra: dist[i] 是到 "起点" 的距离 (累加的)。
 *   - Prim:     dist[i] 是到 "生成树集合" 的距离 (不累加，只看最近的那条边)。
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510, INF = 0x3f3f3f3f;

int n, m;
int g[N][N]; // 稠密图，用邻接矩阵存
int dist[N]; // dist[i] 表示 i 到 "当前生成树集合" 的最短距离
bool st[N];  // st[i] 表示 i 是否已经在生成树集合里了

int prim()
{
    // 1. 初始化距离为无穷大
    memset(dist, 0x3f, sizeof dist);
    
    int res = 0; // 存储最小生成树的所有边的总权重
    
    // 2. 迭代 n 次 (每次加入一个点)
    for (int i = 0; i < n; i ++ )
    {
        int t = -1;
        
        // 步骤a: 在还没加入生树的点中，找一个距离生成树最近的点 t
        for (int j = 1; j <= n; j ++ )
        {
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }

        // printf("Iter %d: Selected t=%d, dist[t]=%d\n", i, t, dist[t]); // Debug

        // 特判: 如果图是不连通的，找不到点连进来了，直接返回无穷大
        // i > 0 是因为第一次迭代时 t肯定是随便选的(通常是1)，距离肯定还没更新，dist是INF是正常的
        if (i && dist[t] == INF) return INF;

        // 步骤b: 把 t 加入生成树
        // 注意：第一次选点时，dist[t]是初始的INF(或者起点的0如果有设的话)，不要加进去(或者特判)
        // 更好的写法是：只有非起点才累加边权
        if (i) res += dist[t];
        st[t] = true;

        // 步骤c: 用 t 更新其他点到集合的距离
        // 注意这里！和 Dijkstra 的区别！
        // Dijkstra: dist[j] = min(dist[j], dist[t] + g[t][j]); (累加路径)
        // Prim:     dist[j] = min(dist[j], g[t][j]);           (只看边长)
        // 意思是：j 离生成树的距离，能不能通过 t 变得更近？
        for (int j = 1; j <= n; j ++ )
            dist[j] = min(dist[j], g[t][j]);
    }
    
    return res;
}

int main()
{
    // 输入点数和边数
    cin >> n >> m;

    // 初始化邻接矩阵
    memset(g, 0x3f, sizeof g);

    while (m -- )
    {
        int u, v, w;
        cin >> u >> v >> w;
        // 无向图：存两条边
        // 虽然题目可能给有向边数据，但最小生成树通常是针对无向图定义的
        // 如果题目说是无向图，要在两个方向都存，且处理重边取最小值
        g[u][v] = g[v][u] = min(g[u][v], w);
    }

    int t = prim();

    if (t == INF) puts("impossible");
    else printf("%d\n", t);

    return 0;
}
