/*
 * ============================================
 *   SPFA 算法 (Shortest Path Faster Algorithm)
 *   时间复杂度：平均 O(N)，最坏 O(N * M)
 *   
 *   【核心思想】
 *   SPFA 是 Bellman-Ford 的队列优化版。
 *   - Bellman-Ford 很傻：不管哪个点更新了，下一轮它都要把所有边都遍历一遍。
 *   - SPFA 很聪明：只有 "变短了的点" 只要才有可能让它的邻居变短。
 *   
 *   【类似 BFS？】
 *   是的！结构非常像 BFS。
 *   区别在于：
 *   - BFS: 一个点进队列一次，出来后就永远确立了（因为它只处理边权=1）。
 *   - SPFA: 一个点可能反反复复进出队列（因为它可能被多次更新变短）。
 * 
 *   【适用场景】
 *   1. 负权边：必须用 SPFA (Dijkstra 不行)。
 *   2. 判断负环：SPFA 可以判断图里有没有负环（转圈圈就能无限刷距离）。
 *   3. 绝大多数正权图：如果不被卡数据，SPFA 跑得比 Dijkstra 还快。
 *      (但在竞赛中，出题人经常故意造数据卡 SPFA，让它退化成 Bellman-Ford)
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx; // 邻接表存图
int dist[N];
bool st[N]; // 【关键】st[i]=true 表示点 i 当前在队列中 (防止重复入队)

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1);
    st[1] = true; // 1号点入队了

    while (q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false; // 它可以再次入队，所以出队后标记为 false

        // 遍历 t 的所有邻居
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            
            // 如果能通过 t 让 j 变短
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                
                // 【核心优化】
                // 只有当 j 变短了，它才有资格去更新它的邻居。
                // 如果 j 已经在队列里排队了，就不用再加一次了 (没必要)。
                if (!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);

    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    int t = spfa();

    if (t == 0x3f3f3f3f) puts("impossible");
    else printf("%d\n", t);

    return 0;
}
