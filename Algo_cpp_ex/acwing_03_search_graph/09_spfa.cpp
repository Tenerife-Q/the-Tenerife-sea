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
    e[idx] = b; 
    w[idx] = c; // 这条边的权重
    ne[idx] = h[a];
    h[a] = idx ++ ;
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

        /*
         * ============================================
         * 【关于 "反复入队" 的奥妙】
         * Q: 为什么 BFS 只入队一次，SPFA 可以反复入队？
         * 
         * A: 因为它们的目标不同。
         * - BFS (权值为1的图):
         *   谁先被访问到，谁就是最短的。
         *   比如 A->B, A->C->B。BFS 肯定先通过 A->B 访问到 B。
         *   既然第一次访问就是最短路，以后再访问肯定更远，所以不用再谈。
         * 
         * - SPFA (带权图，可能有负权):
         *   第一次访问到 B，距离可能是 10。
         *   过了一会儿，发现 A->C->...->D->B 这条路虽然绕，但有一段超级负权边。
         *   结果总距离变成了 5。
         *   B 变短了！那 B 的邻居们（比如 E, F）原来是基于 B=10 算的，
         *   现在 B 变 5 了，E 和 F 也能跟着变短！
         *   所以 B 必须【再次入队】，去通知它的邻居们：“哥们，我变强了，你们也能变更强！”
         * ============================================
         */

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

/*
int spfa() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1);
    st[1] = true;

    while(q.size()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if(dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if(!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return dist[n];
}
*/


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

/*
 * =========================================================================
 * 【单源最短路算法大比拼：SPFA vs Dijkstra vs Bellman-Ford】
 * 
 * 1. 核心逻辑 (心法)
 *    - Dijkstra: 【贪心】 "只看未确定的最近点"。
 *      假设：路越走越远 (无负权)。如果找到了最近的点，那它肯定就是定局了。
 *      特点：一个点一旦出列，就不可能再回来。
 * 
 *    - Bellman-Ford: 【暴力】 "全部都给我松一遍"。
 *      假设：可能有负权。
 *      特点：每轮循环无脑遍历所有边，一共做 k 轮。
 * 
 *    - SPFA: 【精准打击】 "谁变短了，谁就去通知邻居"。
 *      假设：可能有负权。
 *      特点：用队列维护"变了的点"。类似于"带有反悔机制"的 BFS。
 *            一个点可能反反复复入队 (因为可能被多条路先后更新变短)。
 * 
 * 2. 数据结构 (兵器)
 *    - Dijkstra (堆优化): 优先队列 (priority_queue)。
 *      时刻把最小的距离浮上来。
 * 
 *    - Bellman-Ford: 结构体数组 (struct Edge)。
 *      只要能存所有的边就行，不需要邻接表。
 * 
 *    - SPFA: 普通队列 (queue) + 邻接表。
 *      像处理任务列表一样，谁有变动就把谁加到任务列表末尾。
 * 
 * 3. 效率对比 (战力)
 *    - Dijkstra: O(M log N)。 非常稳定，正权图王者。
 *    - Bellman-Ford: O(N * M)。 非常慢，但能处理"限制经过k条边"。
 *    - SPFA: 平均 O(kM) (k约等于2)，最坏 O(NM)。
 *      平时跑得比 Dijkstra 还快，但容易被设计好的网格图卡死 (退化成 Bellman)。
 * 
 * 4. 总结：什么时候用谁？
 *    - 有负权边？ -> SPFA。
 *    - 限制步数？ -> Bellman-Ford。
 *    - 都是正权？ -> Dijkstra (堆优化)。
 *    - 判断负环？ -> SPFA。
 * =========================================================================
 */
