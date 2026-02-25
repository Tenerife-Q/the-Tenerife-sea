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

int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    while(heap.size()) {
        PII t = heap.top();
        heap.pop();
        
        int distance = t.first, ver = t.second;
        
        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i =ne[i]) {
            int j = e[i];
            if(dist[j] > distance + w[i]) {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    return dist[n] == 0x3f3f3f3f ? -1 : dist[n];
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

/*
 * ==================================================================================
 * 【堆优化 Dijkstra 可视化图解：数据结构如何加速】
 * 
 * 场景：我们依然用 1->6 的例子。
 *      (初始: dist[1]=0, 其他=∞)
 * 
 * [小根堆 (Priority Queue)]
 * -----------------------------------------------------------
 * 变化过程 (Top element always min):
 * 
 * 1. 【刚开始】
 *    堆中: [{0, 1号}]
 *    => 弹出 {0, 1号}。确认 1号！
 *    => 1号 松弛邻居 (2号 dist=2, 3号 dist=4)。
 * 
 * 2. 【1号处理完】
 *    堆中: [{2, 2号}, {4, 3号}]   <-- 2号排在前面(因为它更近)
 *    => 弹出 {2, 2号}。确认 2号！
 *    => 2号 松弛邻居 (3号 dist=3, 4号 dist=4)。
 *       * 注意：此时堆里会同时存在两个3号的信息！旧的在下面，新的在上面。
 * 
 * 3. 【2号处理完】
 *    堆中: 
 *       Top -> {3, 3号}  (新! 2->3 的路)
 *              {4, 4号}  (2->4 的路)
 *              {4, 3号}  (旧! 1->3 的路 -> 废弃数据, 沉底了)
 *    
 *    => 弹出 {3, 3号}。确认 3号！
 *       (检查 st[3] 没访问过? 是的 -> 处理他)
 *    => 3号 松弛邻居 (5号 dist=6)。
 * 
 * 4. 【3号处理完】
 *    堆中: 
 *       Top -> {4, 4号}
 *              {4, 3号}  (旧! 垃圾数据)
 *              {6, 5号}
 * 
 *    => 弹出 {4, 4号}。确认 4号！
 *    => 4号 松弛邻居 (5号 dist=5, 6号 dist=6)。
 * 
 * 5. 【4号处理完】
 *    堆中:
 *       Top -> {4, 3号}  <-- ！！注意！！现在堆顶是这个旧数据。
 *              {5, 5号}  (新)
 *              {6, 5号}  (旧)
 *              {6, 6号}
 * 
 *    => 弹出 {4, 3号}。
 *       (检查 st[3]? 已经在第3步确认过了! st[3]=true!)
 *       => **直接 continue (扔进垃圾桶)**。
 * 
 *    => 再次弹出 Top -> {5, 5号}。确认 5号！
 *       ...以此类推...
 * 
 * ==================================================================================
 * 【核心优势】
 * 朴素版: 每次都要在整个数组里找最小值 -> O(N)
 * 堆优化: 最小值自动浮上来，直接拿 -> O(1) (调整堆 O(logN))
 * ==================================================================================
 */
