/*
 * ============================================
 *   Dijkstra (堆优化版) - 单源最短路
 *   适用场景：点非常多(N=10^5)，但边没有填满(稀疏图)。
 *   时间复杂度：O(M * logN)
 *   
 *   【核心区别】
 *   1. 存图：不再用二维数组 g[N][N]，改用邻接表 (h, e, ne, w)。
 *      因为 N=10万时，二维数组开不下 (10万*10万 * 4字节 = 40GB内存，爆炸)。
 * 
 *   2. 找最近点：不再用 for 循环扫描所有点。
 *      而是用 "优先队列 (小根堆)"，谁距离最近，谁自动浮到堆顶。
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue> // 必须引入队列头文件

using namespace std;

// PII = Pair<int, int>
// 用于在堆里存数据：{距离, 编号}
// 例如 {5, 2} 表示：到 2号点的距离是 5。
// 注意：把距离放在第一位，因为 pair 排序默认先比第一位，我们需要按距离排序。
typedef pair<int, int> PII;

const int N = 100010; // 点数可以很大
const int M = 100010; // 边数，假设同级

// 邻接表四件套
int n, m;
int h[N], e[M], ne[M], w[M], idx; // w[M] 存边的权重(Weight)
int dist[N];
bool st[N];

// 邻接表加边函数
void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c; // 这条边有多长
    ne[idx] = h[a];
    h[a] = idx ++ ;
}

int dijkstra()
{
    // [初始化]
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    // [定义小根堆]
    // priority_queue 默认是大根堆，加上 greater 变成小根堆
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    
    // 把起点放进去：距离0，编号1
    heap.push({0, 1});

    while (heap.size())
    {
        // [模块 1: 选点]
        // 以前是循环找，现在直接弹出来就是最近的
        PII t = heap.top();
        heap.pop();

        int distance = t.first; // 这个点离起点的距离
        int ver = t.second;     // 这个点的编号 (vertex)

        // [重点] 冗余备份处理
        // 因为无法直接修改堆里的元素，我们每次更新距离都会 push 一个新的进去。
        // 所以堆里可能有 {5, 2}, {3, 2} 这种同一个点的多个版本。
        // 如果弹出来的是旧版本（已经处理过 st[ver]=true），直接扔掉。
        if (st[ver]) continue;
        
        // [模块 2: 打卡]
        st[ver] = true;

        // [模块 3: 松弛]
        // 遍历 ver 的所有邻居
        // i 是边的编号 (idx)
        // j 是邻居的城市编号 (e[i])
        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            
            // 如果通过 ver 去 j 更近
            if (dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                // 把更新后的结果扔进堆里 (不用管旧的，旧的距离大，沉在堆底，以后弹出来也会被 continue 掉)
                heap.push({dist[j], j});
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);

    // 邻接表初始化
    memset(h, -1, sizeof h);

    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); // 这里的重边不需要特判，因为Dijkstra会自动选最短的
    }

    printf("%d\n", dijkstra());

    return 0;
}
