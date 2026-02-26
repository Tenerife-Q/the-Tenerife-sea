/*
 * ============================================
 *   Kruskal 算法 (克鲁斯卡尔算法) - 最小生成树
 *   时间复杂度：O(M log M) (主要是排序边的这一步)
 *   
 *   【核心思想：贪心 + 并查集】
 *   Prim 是"加点法" (就像 Dijkstra)，每次拉一个最近的点进圈子。
 *   Kruskal 是"加边法"。
 *   
 *   【算法流程】
 *   1. 把所有的边，按照权重从小到大排序。
 *   2. 从小到大依次拿出每一条边 (a, b, w)。
 *   3. 问：如果我们连上这条边，会形成环吗？
 *      - 怎么判断环？用并查集！
 *      - 如果 a 和 b 已经在同一个集合里了 (find(a) == find(b))，连上就会形成环 -> 跳过。
 *      - 如果不在同一个集合，那就连上！(把 a 和 b 的集合合并) -> 选中这条边。
 * 
 *   【适合场景】
 *   Prim 适合由于稠密图 (点少边多) O(N^2)。
 *   Kruskal 适合稀疏图 (点多边少) O(M log M)。
 * ============================================
 */

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010; // 点数 (可能需要大一点如果题目给的大)
const int M = 100010; // 边数

int n, m;
int p[N]; // 并查集的父节点数组

// 这里的边我们需要存下来排序，所以用结构体最方便
struct Edge
{
    int a, b, w;

    // 重载小于号，方便 sort 函数排序
    bool operator< (const Edge &W) const
    {
        return w < W.w;
    }
} edges[M];

// 并查集核心操作：查找祖宗 + 路径压缩
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);

    // 读入所有边
    for (int i = 0; i < m; i ++ )
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }

    // 1. 将所有边按权重从小到大排序
    sort(edges, edges + m);

    // 并查集初始化
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    int res = 0; // 最小生成树的总权重
    int cnt = 0; // 当前连了多少条边

    // 2. 枚举每条边
    for (int i = 0; i < m; i ++ )
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;

        a = find(a), b = find(b);

        // 如果两个点还不连通，说明这条边不会构成环，可以选！
        if (a != b)
        {
            p[a] = b; // 合并集合
            res += w;
            cnt ++ ;
        }
    }

    // N个点的树，应该有 N-1 条边。如果不够，说明图不连通。
    if (cnt < n - 1) puts("impossible");
    else printf("%d\n", res);

    return 0;
}
