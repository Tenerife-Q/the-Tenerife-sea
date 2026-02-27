/*
 * ============================================
 *   染色法判断二分图
 *   
 * 题目描述：
 *   给定一个无向图，判断它是否是二分图。
 *  二分图的定义：如果一个图的顶点集合可以被划分成两个不相交的子集，使得图中的每条边都连接一个子集中的顶点和另一个子集中的顶点，那么这个图就是二分图。
 * 输入格式：
 *  第一行包含两个整数 n 和 m，分别表示图的顶点数和边数。
 * 第二行到第 m+1 行，每行包含两个整数 a 和 b，表示图中存在一条连接顶点 a 和顶点 b 的边。
 * 输出格式：
 * 如果图是二分图，输出 "Yes"；否则输出 "No"。
 * 输入样例：
 * 4 4
 * 1 2
 * 2 3
 * 3 4
 * 4 1
 * 输出样例：
 * No
 * 
 * 输入样例：
 *  4 4
    1 3
    1 4
    2 3
    2 4
   输出样例：
   Yes

 * 
 *   【递归执行堆栈图解：以 1-2-3-1 为例(三角形失败案例)】
 *   
 *   1. main() 循环到 i=1:
 *      -> 调用 dfs(1, 1) 【给1号染白色】
 *         color[1] = 1 (1号现在是白色)
 *         1号找邻居 -> 发现 2。
 *         
 *         2. -> 递归调用 dfs(2, 2) 【给2号染黑色】
 *            color[2] = 2 (2号现在是黑色)
 *            2号找邻居 -> 发现 3。
 *            
 *            3. -> 递归调用 dfs(3, 1) 【给3号染白色】
 *               color[3] = 1 (3号现在是白色)
 *               3号找邻居 -> 发现 1。
 *               
 *               检查 1号：
 *               color[1] 是多少？是 1 (白色)。
 *               我现在染的 3号 是多少？是 1 (白色)。
 *               【冲突！】
 *               dfs(3, 1) 返回 false！
 *            
 *            dfs(3,1) 返回 false，导致 dfs(2,2) 也返回 false。
 *         
 *         dfs(2,2) 返回 false，导致 dfs(1,1) 也返回 false。
 *      
 *   4. main() 收到 false，flag = false，break。
 *   5. 输出 "No"。
 * 
 *   【成功案例：1-2-3-4-1 (正方形)】
 *   dfs(1,1-白) -> dfs(2,2-黑) -> dfs(3,1-白) -> dfs(4,2-黑)
 *   此时 4号 的邻居是 1号。
 *   检查：color[4]=2(黑), color[1]=1(白)。
 *   【颜色不同，验证通过！】没有发生成环冲突。
 *   一层层 return true 回去。
 * ============================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = 200010; // 稀疏图用邻接表

int n, m;
int h[N], e[M], ne[M], idx; // 邻接表标准写法
int color[N]; // 0:未染色, 1:颜色1(A队), 2:颜色2(B队)

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

// DFS 递归函数 (图解版)
// u: 当前要处理的人
// c: 组织要给 u 安排的颜色 (1或2)
bool dfs(int u, int c)
{
    // 1. 【执行命令】给 u 穿上 c 颜色的队服
    color[u] = c; 

    // 2. 【审查关系】 u 的所有社会关系人 j
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i]; 
        
        // 情况A：j 还没被组织考察过 (color[j] == 0)
        if (!color[j])
        {
            // 既然 u 是 c色，那 j 绝对不能是 c色，必须是 (3-c)色。
            // 于是把任务派发给 j，让他去处理他的下线。
            // 如果 j 汇报说"不行，我的下线有冲突"，那我也搞不定了。
            if (!dfs(j, 3 - c)) return false;
        }
        // 情况B：j 已经被组织考察过了，穿好队服了
        else if (color[j] == c)
        {
            // 居然和我颜色一样！
            // u 和 j 认识(有边)，却穿同色队服？
            // 逻辑崩塌，报告上级：任务失败。
            return false;
        }
    }
    // 3. 【任务完成】所有邻居都安排得明明白白，且没有矛盾，向上级汇报成功。
    return true; 
}

/*
bool dfs(int u, int c) {
    color[u] = c;
    for(int i =h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if(!color[j]) {
            if(!dfs(j,3-c)) return false;
        } else if(color[j] == c) {
            return false;
        }
    }
    return true;
}
*/


int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);

    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        // 无向图！朋友关系是双向的
        add(a, b), add(b, a);
    }

    bool flag = true; // 假设一开始是成功的
    
    // 遍历每一个人
    // 为什么要循环？因为图可能不连通(有多个孤岛圈子)
    // 比如 1-2 是一个圈子，3-4-5 是另一个圈子。都要检查一遍。
    for (int i = 1; i <= n; i ++ )
    {
        // 如果 i 还没分组，说明找到了一个新的圈子
        if (!color[i])
        {
            // 从 i 开始，把它分到 1队(A队)，然后顺藤摸瓜分它的邻居
            // 如果 dfs 返回 false，说明这个圈子分不下去了
            if (!dfs(i, 1))
            {
                flag = false; // 哪怕有一个圈子分失败，整张图都失败
                break;
            }
        }
    }

    if (flag) puts("Yes");
    else puts("No");

    return 0;
}
