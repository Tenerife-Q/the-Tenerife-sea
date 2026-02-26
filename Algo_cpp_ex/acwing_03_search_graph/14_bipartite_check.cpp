/*
 * ============================================
 *   染色法判断二分图 (Bipartite Graph Check)
 *   时间复杂度：O(N + M) (DFS/BFS 遍历一次图)
 *   
 *   【什么是二分图？】
 *   能不能把所有点分成两堆（左边一堆，右边一堆），
 *   使得所有的边，都是从左堆连向右堆的？
 *   (也就是说，没有一条边是在"堆内部"连的)
 *   
 *   【核心性质】
 *   一个图是二分图 <==> 图中不含"奇数环" (节点数为奇数的环)。
 *   比如三角形(3个点)就是奇数环，肯定没法二分，必然会有内部连线。
 *   四边形(4个点)就是偶数环，可以二分。
 *   
 *   【算法流程：DFS染色】
 *   1. 准备颜色数组 color[N]：0表示未染色，1表示白色，2表示黑色。
 *   2. 遍历所有点，如果没染过色，就开始DFS。
 *   3. DFS逻辑：
 *      - 把当前点 u 染成 c (比如1)。
 *      - 遍历 u 的所有邻居 j：
 *        - 如果 j 没染过色：把 j 染成 3-c (1变2，2变1)，并继续DFS递归。
 *          如果递归发现冲突(返回false)，那我也返回false。
 *        - 如果 j 染过色了：
 *          必须保证 j 的颜色和 u 不一样 (color[j] != c)。
 *          要是 j 和 u 颜色一样，说明冲突了！(出现奇数环)，返回 false。
 * 
 *   【比喻】
 *   从这里开始，我们要把人群分成"男人"和"女人"。
 *   每一条边代表"谈恋爱"。
 *   如果我们发现一个人既和男人谈，又和女人谈，或者两个男人谈恋爱了，
 *   那就说明这个图不是二分图（在这个简化的异性恋模型下）。
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = 200010; // 稀疏图用邻接表

int n, m;
int h[N], e[M], ne[M], idx; // 邻接表标准写法
int color[N]; // 0:未染色, 1:颜色1, 2:颜色2

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

// u: 当前节点
// c: 当前节点要染的颜色 (1或2)
bool dfs(int u, int c)
{
    color[u] = c; // 先把自己染了

    // 遍历所有邻居
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        
        // 情况1：邻居 j 还没染色
        if (!color[j])
        {
            // 尝试把 j 染成相反的颜色 (3-c: 1->2, 2->1)
            // 如果递归下去发现冲突，那整个图就不是二分图
            if (!dfs(j, 3 - c)) return false;
        }
        // 情况2：邻居 j 已经染过色了
        else if (color[j] == c)
        {
            // 坏了！邻居和我颜色一样！冲突！
            // 说明出现了奇数环。
            return false;
        }
    }
    return true; // 既然所有邻居都没问题，那我也没问题
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);

    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        // 无向图！边是双向的，所以加两次
        add(a, b), add(b, a);
    }

    bool flag = true;
    
    // 遍历所有点 (防止图不连通，有多个连通块)
    for (int i = 1; i <= n; i ++ )
    {
        // 如果 i 还没染色，就从它开始染 (染成颜色1)
        if (!color[i])
        {
            if (!dfs(i, 1))
            {
                flag = false;
                break;
            }
        }
    }

    if (flag) puts("Yes");
    else puts("No");

    return 0;
}
