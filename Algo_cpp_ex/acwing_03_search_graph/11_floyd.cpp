/*
 * ============================================
 *   Floyd 算法 (Floyd-Warshall) - 多源最短路
 *   时间复杂度：O(N^3)
 *   
 *   【上帝视角】
 *   之前的 Dijkstra/SPFA 都是"单源"的（只能算从起点 1 去别人的距离）。
 *   Floyd 是"多源"的：它算完之后，你就拥有了上帝视角。
 *   你可以瞬间知道：
 *   - 3号 到 5号 多远？ d[3][5]
 *   - 2号 到 10号 多远？ d[2][10]
 *   
 *   【核心原理：动态规划】
 *   状态：d[i][j] 表示从 i 到 j 的最短距离。
 *   转移：我们尝试找一个中间人 k。
 *        "如果我们不仅仅直达，而是允许经过第 k 号点中转，路会不会变短？"
 *        d[i][j] = min(d[i][j], d[i][k] + d[k][j])
 * 
 *   【记忆口诀】
 *   "三层循环，k 在最外层。"
 *   (i, j 是起点和终点，k 是那个尝试插进来的中间人)
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210, INF = 1e9;

int n, m, Q; // Q: 询问次数
int d[N][N]; // 邻接矩阵：因为 N 比较小 (200左右)，可以直接存

void floyd()
{
    // [核心代码]
    // 只有短短 5 行，背下来！
    // 注意：k (中间人) 必须放在最外层循环！
    // 意义：第一轮 k=1，表示允许经过 1号点 中转。
    //      第二轮 k=2，表示允许经过 1,2号点 中转...
    //      直到 k=n，表示允许经过所有点中转，这就是最终的最短路。
    
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &Q);

    // [初始化]
    // 自己到自己距离是0，到别人是无穷大
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;

    // [读入边]
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        // 注意：因为是邻接矩阵，如果两点间有多条边，我们只保留最短的那条
        d[a][b] = min(d[a][b], c);
    }

    // [计算]
    floyd();

    // [处理询问]
    while (Q -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);

        // 如果 d[a][b] 还是很大（哪怕被减去了一点负权边），说明不可达
        if (d[a][b] > INF / 2) puts("impossible");
        else printf("%d\n", d[a][b]);
    }

    return 0;
}
