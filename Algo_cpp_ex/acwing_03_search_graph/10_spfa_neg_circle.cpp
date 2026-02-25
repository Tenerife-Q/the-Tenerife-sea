/*
 * ============================================
 *   SPFA 判负环
 *   时间复杂度：平均 O(N)，最坏 O(N * M)
 *   
 *   【什么是负环？】
 *   就是环中所有边的权重之和小于 0。
 *   比如 A->B (2), B->C (-3), C->A (-1)。
 *   转一圈：2 - 3 - 1 = -2。
 *   转两圈：-4。
 *   只要在这个环里一直转，距离就会无限变小 (-∞)。
 * 
 *   【SPFA 如何判负环？】
 *   原理：抽屉原理。
 *   - 如果图有 n 个点，那么任何两点之间的最短路，最多通过 n-1 条边。
 *   - 如果某条路竟然经过了 n 条边甚至更多，说明什么？
 *   - 说明肯定有某个点被经过了至少两次 -> 说明有环！
 *   - 而且这个环既然能让路变短，那肯定是个【负环】。
 * 
 *   【代码实现】
 *   增加一个 cnt[x] 数组，记录到点 x 的最短路经过了多少条边。
 *   每次 dist[j] 更新时：
 *     cnt[j] = cnt[t] + 1;
 *     if (cnt[j] >= n) return true; // 发现负环
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
int cnt[N]; // 【关键】记录最短路经过的边数
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

bool spfa()
{
    // [注意点 1]
    // 判负环不需要初始化 dist 为无穷大。
    // 因为我们只关心有没有负环，不关心绝对距离是多少。
    // 甚至不需要 dist[1]=0。
    
    queue<int> q;

    // [注意点 2]
    // 必须把所有点都放进队列！
    // 为什么？因为负环可能不连通起点 1。
    // 如果负环在一个孤立的角落里，只把 1 加进队列是探测不到的。
    for (int i = 1; i <= n; i ++ )
    {
        st[i] = true;
        q.push(i);
    }

    while (q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1; // 既然 dist[j] 是通过 t 走过来的，那边数就是 t的边数+1

                // 如果经过的边数超过了 n，说明必定走了回头路(成环)
                // 且因为能松弛，说明是个负环
                if (cnt[j] >= n) return true;

                if (!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return false;
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

    if (spfa()) puts("Yes"); // 有负环
    else puts("No");

    return 0;
}
