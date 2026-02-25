/*
 * ============================================
 *   Bellman-Ford 算法 - 处理负权边 & 限制边数
 *   时间复杂度：O(N * M)
 *   
 *   【为什么需要它？】
 *   Dijkstra 有个致命缺陷：它假设"边权都是正的"，一旦有负数（倒贴钱的路），
 *   它的贪心策略就会失效。Bellman-Ford 可以处理负权边。
 * 
 *   【核心思想】
 *   暴力松弛！
 *   - Dijkstra 是"每次选一个确定的点"去松弛邻居。
 *   - Bellman-Ford 是"不管三七二十一，每轮把所有边都松弛一遍"。
 * 
 *   【特殊功能：k 步限制】
 *   有些题目会问：从起点到终点，最多经过 k 条边，最短距离是多少？
 *   这是 Dijkstra 做不到的，只有 Bellman-Ford 能做。
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510, M = 10010;

int n, m, k; // k: 最多允许经过 k 条边
int dist[N];
int backup[N]; // 【关键】备份数组，防止串联更新

// 因为这一章我们要遍历所有边，不需要用邻接表那么麻烦
// 直接用结构体数组存每一条边即可
struct Edge
{
    int a, b, w;
} edges[M];

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // 循环 k 次
    // 意义：第 i 次循环，表示"经过不超过 i 条边"到达各点的最短距离
    for (int i = 0; i < k; i ++ )
    {
        // 【备份】
        // 为什么要备份？
        // 比如我们想算"只经过1条边"。
        // 如果不备份，更新了 dist[2] 之后，马上用新的 dist[2] 去更新 dist[3]，
        // 那 dist[3] 实际上就用了 2 条边（1->2 和 2->3）。
        // 用备份的话，大家读取的都是上一轮的数据，保证了"只多走1条边"。
        memcpy(backup, dist, sizeof dist);

        // 遍历所有边 (a -> b, 权重 w)
        for (int j = 0; j < m; j ++ )
        {
            int a = edges[j].a;
            int b = edges[j].b;
            int w = edges[j].w;

            // 松弛操作
            dist[b] = min(dist[b], backup[a] + w);
        }
    }

    // 这里不能只判断 == 0x3f3f3f3f
    // 因为如果有负权边，无穷大稍微减去一个具体数值，会变成 "无穷大-5"，它已经不是 0x3f3f3f3f 了
    // 但它依然代表不可达。所以我们判断 > 0x3f3f3f3f / 2 即可。
    if (dist[n] > 0x3f3f3f3f / 2) return -0x3f3f3f3f; // 返回一个特殊标记
    return dist[n];
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = {a, b, c};
    }

    int t = bellman_ford();

    if (t == -0x3f3f3f3f) puts("impossible"); // 题目要求这种情况下输出 impossible
    else printf("%d\n", t);

    return 0;
}
