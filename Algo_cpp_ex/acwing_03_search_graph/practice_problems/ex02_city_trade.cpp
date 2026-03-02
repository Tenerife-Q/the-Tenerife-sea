/*
 * 综合练习题2：城市贸易 (City Trade)
 * 难度：⭐⭐⭐
 * 
 * 【题目描述】
 * C 国有 N 个城市 (1~N)，城市间有 M 条单向道路。
 * 每个城市 i 都有一个商品价格 price[i]。
 * 你从城市 1 出发，最终要到达城市 N。
 * 途中你可以在【任意一个】城市买入一次商品，
 * 并在之后的【任意一个】城市卖出一次商品（先买后卖，只能交易一次）。
 * 求最大利润。如果无法获利或无法到达终点，输出 0。
 * 
 * 【数据范围】
 * N <= 100,000, M <= 500,000
 * price[i] <= 100
 * 
 * 【算法思路：双向 SPFA / Dijkstra】
 * 利润 = 卖出价格 - 买入价格
 * 假设我们在城市 k 进行交易，或者 k 分割了买和卖的路径。
 * 我们需要知道：
 * 1. d_min[k]: 从起点 1 走到 k 的过程中，经过的所有城市里，价格最低是多少？
 * 2. d_max[k]: 从 k 走到终点 N 的过程中，经过的所有城市里，价格最高是多少？
 * 
 * 最终答案就是枚举所有 k: max(d_max[k] - d_min[k])
 * 
 * 【实现细节】
 * 1. d_min[]: 从 1 号点出发跑一遍正向图的最短路（其实是"最小权值路"）。
 *    即 d_min[y] = min(d_min[y], d_min[x], price[y])。
 *    注意：这里不是求边权和，而是路径上的点权最小值，状态转移 slightly different。
 * 
 * 2. d_max[]: 从 N 号点出发跑一遍反向图（需要建反向图）。
 *    即 d_max[y] = max(d_max[y], d_max[x], price[y])。
 * 
 * 为什么用 SPFA？因为不是求边权和，Dijkstra 的贪心性质在这里需要仔细考量（如果只求最小值其实是可以的，类似于 Prim），
 * 但 SPFA 的队列更新逻辑天然适合这种"状态传递"。
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 100010, M = 500010; // 点多边多
const int INF = 0x3f3f3f3f;

int n, m;
int prices[N];

// 正向图 (求最小值)
int h[N], e[M], ne[M], idx;
// 反向图 (求最大值)
int rh[N], re[M], rne[M], ridx;

int dmin[N]; // dmin[i]: 1 -> i 路径上的最小价格
int dmax[N]; // dmax[i]: i -> N 路径上的最大价格
bool st[N];

void add(int *h, int *e, int *ne, int &idx, int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

// type 0: 正向求 min
// type 1: 反向求 max
void spfa(int start, int type) {
    queue<int> q;
    memset(st, 0, sizeof st);

    if (type == 0) {
        memset(dmin, 0x3f, sizeof dmin);
        dmin[start] = prices[start]; // 起点价格
        q.push(start);
        st[start] = true;
    } else {
        memset(dmax, -0x3f, sizeof dmax); // 求最大值初始化为负无穷(或0)
        dmax[start] = prices[start];
        q.push(start);
        st[start] = true;
    }

    while (q.size()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        // 遍历邻居
        // 正向用 h[], 反向用 rh[]
        int *cur_h = (type == 0) ? h : rh;
        int *cur_e = (type == 0) ? e : re;
        int *cur_ne = (type == 0) ? ne : rne;

        for (int i = cur_h[t]; i != -1; i = cur_ne[i]) {
            int j = cur_e[i];
            bool updated = false;

            if (type == 0) {
                // 正向：我要找路径上经过的更小的价格
                // dmin[j] 可以被更新，如果：
                // 1. 上一步 dmin[t] 比我小
                // 2. 或者我自己 prices[j] 就很小
                int new_min = min(dmin[t], prices[j]);
                if (dmin[j] > new_min) {
                    dmin[j] = new_min;
                    updated = true;
                }
            } else {
                // 反向：我要找路径上经过的更大的价格
                int new_max = max(dmax[t], prices[j]);
                if (dmax[j] < new_max) {
                    dmax[j] = new_max;
                    updated = true;
                }
            }

            if (updated) {
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

void spfa(int start, int type) {
    queue<int> q;
    memset(st, 0, sizeof st);
    if(type == 0) {
        memset(dmin, 0x3f, sizeof dmin);
        dmin[start] = prices[start];
        q.push(start);
        st[start] = true;
    } else {
        memset(dmax, -0x3f, sizeof dmax);
        dmax[start] = prices[start];
        q.push(start);
        st[start] = true;
    }

    while(q.size()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        int *cur_h = (type == 0) ? h : rh;
        int *cur_e = (type == 0) ? e : re;
        int *cur_ne = (type == 0) ? ne : rne;

        for(int i = cur_h[t]; i != -1; i = cur_ne[i]) {
            int j = cur_e[i];
            bool updated = false;
            if(type == 0 ) {
                int new_min = min(dmin[t], prices[j]);
                if(dmin[j] > new_min) {
                    dmin[j] = new_min;
                    updated = true;
                }
            } else {
                int new_max = max(dmax[t], prices[j]);
                if(dmax[j] < new_max) {
                    dmax[j] = new_max;
                    updated = true;
                }
            }
            if(updated) {
                if(!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &prices[i]);

    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);

    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        // 原题是 a->b 单向
        // c 是 1:单向 2:双向
        // 为简化模型，我们假设输入就是简单的 a->b
        // 实际题目中如果是双向边，就正反各加一次
        add(h, e, ne, idx, a, b);
        add(rh, re, rne, ridx, b, a); // 建反图
        if (c == 2) {
            add(h, e, ne, idx, b, a);
            add(rh, re, rne, ridx, a, b);
        }
    }

    // 1. 从起点 1 出发，算出 dmin[] (路过的最便宜价格)
    spfa(1, 0);

    // 2. 从终点 N 出发(在反图上跑)，算出 dmax[] (路过的最贵价格)
    spfa(n, 1);

    int res = 0;
    // 枚举每一个可能的交易中转点 i
    for (int i = 1; i <= n; i++) {
        res = max(res, dmax[i] - dmin[i]);
    }

    printf("%d\n", res);

    return 0;
}

/*
 * ==================================================================================
 * 【深度解析：STL vs 链式前向星 & 指针的奥秘】
 * ==================================================================================
 * 
 * 1. 为什么竞赛中不爱用 STL (vector<vector<int>>)?
 *    -------------------------------------------------------------------------------
 *    (A) 速度 (Speed):
 *        - vector 的动态扩容 (allocate -> copy -> deallocate) 在百万级操作下开销巨大。
 *        - vector 内存不一定连续，容易 Cache Miss。
 *        - 静态数组 (链式前向星) 是纯粹的 O(1) 数组访问，且内存连续，通常快 2-3 倍。
 *          对于 N=10^5, M=5*10^5 这种数据量，STL 很容易 TLE (Time Limit Exceeded)。
 *    
 *    (B) 内存 (Memory):
 *        - 真正的链表指针 (Node*) 在 64位机上占 8 字节。
 *        - 数组模拟的"指针" (int) 只占 4 字节。在大图存边时，内存节省一半。
 * 
 * 2. 代码中的"指针"到底是什么？
 *    -------------------------------------------------------------------------------
 *    代码里的 int *h, *e... 是 C++ 指针，用于传递数组。
 *    但在数据结构逻辑里：
 *    - h[u], ne[i] 存的那个整数 (idx)，我们叫它"指针"，但它本质是【数组下标】。
 *    - 这种写法叫【链式前向星】(Array-based Adjacency List)。
 *    
 *    物理结构：
 *    - idx:   边的身份证号 (第几条边)
 *    - e[idx]: 这条边去哪？ (Value)
 *    - ne[idx]: 这条边的【下一条兄弟边】的身份证号是多少？ (Next Pointer)
 *    - h[u]:  u 这个点的【第一条边】的身份证号是多少？ (Head Pointer)
 *    
 *    它完全模拟了链表 Head -> Node -> Node -> NULL 的行为，但所有数据都紧凑地躺在数组里。
 * 
 * 3. 核心代码逐行破译
 *    -------------------------------------------------------------------------------
 *    (A) 加边函数 (头插法链表)
 *        void add(..., int a, int b) {
 *            e[idx] = b;      // 1. 创建新边 node，终点是 b
 *            ne[idx] = h[a];  // 2. 新边的 next 指向原来的 head (断开旧 head，连上新边)
 *            h[a] = idx++;    // 3. update head，让 h[a] 指向这个新边
 *        }
 *        结果：Head -> New -> Old1 -> Old2 -> -1
 * 
 *    (B) 遍历邻居 (遍历链表)
 *        for (int i = h[t]; i != -1; i = ne[i]) { ... }
 *        - i = h[t]:  即 Node* p = head;
 *        - i != -1:   即 while (p != NULL)
 *        - i = ne[i]: 即 p = p->next;
 *        
 *    (C) 状态转移 (松弛)
 *        这题不是求最短路(和)，而是求路径上的最值(min/max)。
 *        - 正向 dmin[j] = min(dmin[t], prices[j]);  // 走到 j 的最低价 = min(上一步最低, j本身)
 *        - 反向 dmax[j] = max(dmax[t], prices[j]);  // 从 j 之后能卖的最高价 = max(后一步最高, j本身)
 * 
 * 4. SPFA 结构与队列模拟推演 (一步一步来)
 *    -------------------------------------------------------------------------------
 *    假设有一条单向路径：1 -> 2 -> 3 -> 4 -> 5. 
 *    每个城市商品价格 prices 数组为: [1:10, 2:12, 3:5, 4:20, 5:8]
 *    
 *    【核心字段含义】：
 *    - dmin[i]: 核心目标是记录从起点 1 号城市，沿着正向道路一直走到 i 号城市的时候，
 *               这一路上（包括 i 号城市自己）能遇到的【最低商品价格】。
 *    - dmax[i]: 核心目标是记录如果我站在 i 号城市，沿着正向道路继续往后走，一直走到终点 5 号城市，
 *               在未来的这一路上（包括 i 号城市自己）能遇到的【最高商品价格】。
 *               （因为是从未来推导现在，所以实际操作是：在反向图上从 5 号往 1 号走找最大值）。
 *    - queue q: SPFA 算法的传送带，用来把“我已经更新的更好状态”传递给我的所有邻居。
 *    - st[i]: (Status) 布尔数组，记录城市 i 当前是否正在 queue 中排队。防止一个城市在队列里出现多次浪费时间。
 * 
 *    【正向 SPFA 求 dmin 详细按步推演 (Type 0)】
 *    [初始化]: 
 *        目标是找最小值，所以把 dmin 数组全部填满 INF (即0x3f3f3f3f，代表极大的数)。
 *        把起点 1 的值放进去: dmin[1] = prices[1] = 10。
 *        把起点 1 推入队列排队: q = [1], 标记 st[1] = true。
 * 
 *    [第 1 轮循环]: 
 *        - t = 1 出队 (现在 q = []), 标记 st[1] = false。
 *        - 找 t=1 的邻居：发现通向城市 2 (prices[2] = 12)。
 *        - 状态传递 (松弛操作)：如果我们走到 2，一路上经历的最低价应该是多少呢？
 *          new_min = min(dmin[1], prices[2]) = min(10, 12) = 10。
 *        - 判断更新：系统发现原来的 dmin[2] 是 INF，现在的 new_min 是 10。
 *          因为 10 < INF，更新！dmin[2] 变成 10。
 *        - 邻居入队：因为 dmin[2] 发生了改变，2 需要去通知它的邻居，所以 2 被推入队列。
 *          此时: q = [2], st[2] = true。
 * 
 *    [第 2 轮循环]: 
 *        - t = 2 出队 (现在 q = []), 标记 st[2] = false。
 *        - 找 t=2 的邻居：发现通向城市 3 (prices[3] = 5)。
 *        - 状态传递：new_min = min(dmin[2], prices[3]) = min(10, 5) = 5。 
 *          (注意：在这里价格暴跌，变成了 5！)
 *        - 判断更新：5 < dmin[3](INF)，更新！dmin[3] 变成 5。
 *        - 邻居入队：3 发生改变，3 入队。
 *          此时: q = [3], st[3] = true。
 * 
 *    [第 3 轮循环]: 
 *        - t = 3 出队 (现在 q = []), 标记 st[3] = false。
 *        - 找 t=3 的邻居：发现通向城市 4 (prices[4] = 20，很贵)。
 *        - 状态传递：重点来了！new_min = min(dmin[3], prices[4]) = min(5, 20) = 5。
 *          (虽然 4 号城市卖得很贵，但 dmin 的含义是"一路上遇到过的最低价"，我只要记得我在 3 号遇到了 5 块钱的货就行)。
 *        - 判断更新：5 < dmin[4](INF)，更新！dmin[4] 变成 5。
 *        - 邻居入队：4 发生改变，4 入队。
 *          此时: q = [4], st[4] = true。
 * 
 *    以此类推，最终队列空了，循环结束。得到 dmin 数组: [10, 10, 5, 5, 5]
 * 
 *    【反向 SPFA 求 dmax 详细按步推演 (Type 1)】
 *    为了算 dmax，我们建了一张反过来的图：5 -> 4 -> 3 -> 2 -> 1。
 *    [初始化]: 
 *        目标是找最大值，所以把 dmax 数组全部填满 -INF (表示很小的数)。
 *        起点是物理上的终点 5: dmax[5] = prices[5] = 8。
 *        5 推入队列: q = [5], 标记 st[5] = true。
 * 
 *    [第 1 轮循环]: 
 *        - t = 5 出队，在反向图里，5 的邻居是 4 (prices[4]=20)。
 *        - 状态传递：dmax[4] = max(dmax[5], prices[4]) = max(8, 20) = 20。
 *        - 判断更新：20 > dmax[4](-INF)，更新！
 *        - 邻居入队：q = [4], st[4] = true。
 *          (物理含义：如果你站在 4 号，你本身能卖 20，退一步去 5 卖 8，最高能卖 20)
 * 
 *    [第 2 轮循环]: 
 *        - t = 4 出队，在反向图里，4 的邻居是 3 (prices[3]=5)。
 *        - 状态传递：重点又来了！dmax[3] = max(dmax[4], prices[3]) = max(20, 5) = 20。
 *          (物理含义：虽然我现在站在 3 号，东西只值 5 块，但我知道如果我不卖，继续走到 4 号，那个冤大头能出 20 块！
 *           所以从 3 往后算，最高卖价是 20)。
 *        - 判断更新：20 > dmax[3](-INF)，更新！dmax[3] = 20, 3 入队。
 * 
 *    以此类推...最终反图跑完，得到 dmax 数组: [20, 20, 20, 20, 8]
 * 
 *    【最后的利润收割战 (枚举 K)】
 *    既然我们知道了：
 *    dmin = [10, 10, 5, 5, 5]  (在这里及之前，最便宜能花多少买)
 *    dmax = [20, 20, 20, 20, 8]  (在这里及之后，最贵能卖多少钱)
 *    那我们就假设在城市 K 这个截点上，完成这笔“低买高卖”的交割：
 *    - 如果 K=1: 利润 = dmax[1] - dmin[1] = 20 - 10 = 10。
 *    - 如果 K=2: 利润 = dmax[2] - dmin[2] = 20 - 10 = 10。
 *    - 如果 K=3: 利润 = dmax[3] - dmin[3] = 20 - 5 = 15。 (此时发现差价最大！)
 *    - 如果 K=4: 利润 = dmax[4] - dmin[4] = 20 - 5 = 15。 (同样是最大)
 *    - 如果 K=5: 利润 = dmax[5] - dmin[5] = 8 - 5 = 3。
 *    最后把所有算出来的利润一比较，最大值就是 15。
 * 
 * 5. 核心答疑：枚举 K 包含自己，会不会导致"同城买卖"？
 *    -------------------------------------------------------------------------------
 *    你可能会问：如果 dmax[k] 和 dmin[k] 都取了 k 城市自身的价格，这不是变成"在同一个城市买然后立刻卖"了吗？
 *    
 *    (A) 算法允许"同城买卖"吗？
 *        答案是：【允许的】，在代码逻辑里这种推演完全可能发生。
 *        
 *    (B) 为什么允许？如果他真这么干了，利润是多少？
 *        如果一个商人在同一个城市买入并立刻卖出，利润 = prices[k] - prices[k] = 0。
 *        
 *    (C) 会影响最终求【最大利润】吗？
 *        绝不会！因为题目要求找的是"最大利润"，而同城买卖产生的利润是 0。
 *        只要你的图中存在哪怕一次微小的差价（比如赚了 1 块钱），这个 0 就会被立刻过滤掉。
 *        那如果整张图一直在跌价（完全没法赚钱）呢？
 *        那最大利润就是 0，代码输出 0。而这恰好完全符合题目要求："如果无法获利，输出 0"！
 *        
 *    结论：我们在划分 "k 的左边(含k)买" 和 "k 的右边(含k)卖" 时，故意包含了交叉点 k。
 *    这是一种极其优雅的设计：它不仅覆盖了所有真实的异地交易（在 k 左边真买了，在 k 右边真卖了），
 *    还顺带用合法利润 0 把"无法获利"的边界情况完美兜底了，不需要额外写半行代码去防范同城交易。
 * 
 * 6. 深入骨髓：双重判断 (updated / st[]) 的终极奥义
 *    -------------------------------------------------------------------------------
 *    在 SPFA 的核心代码中，有这样一段极其经典的入队逻辑：
 *    if (updated) {           // 判断 1：我的数值变好了吗？
 *        if (!st[j]) {        // 判断 2：我已经在队列里排着队了吗？
 *            q.push(j);
 *            st[j] = true;
 *        }
 *    }
 *    
 *    (A) updated (数值更新判断) 的作用：【是否有新闻要发？】
 *        - 只有当邻居 j 的最短路(或最小值)真真切切被我改写了，被【更新】了，
 *          才说明产生了"新情报"。
 *        - 如果我(t)去尝试更新邻居(j)，发现算出来的值还没有人家本来记录的值优秀，
 *          那说明我这条路是个"废情报"。
 *        - 只有拿着"新情报"的人(updated=true)，才有资格去通知他的下一家。
 *        
 *    (B) st[] 数组的作用：【防爆排队 / 去重】 (Status Array)
 *        - st[j] = true 表示："城市 j 正在队列 q 里面排着队等待发言呢"。
 *        - 为什么需要防爆？
 *          假设：A 更新了 C (C发现自己变好了，准备入队)。
 *          紧接着，B 也更新了 C (C发现自己变得【更好】了)。
 *          此时 C 的数值确实发生过两次 updated，但他需要去队列里排两次队吗？
 *          完全不需要！因为只要 C 最后一次排到队列头，他就会拿着他身上【最新的、最极品的那个数值】
 *          一次性去通知他所有的邻居。
 *        - 把 C 在队列里塞两次，非但没用，还会导致他的邻居也被唤醒两次，引发灾难性的指数级重复计算。
 * 
 *    (C) 连招解析：
 *        - if (updated)：说明邻居 j 拿到了更好的成绩。
 *        - 但是等一下！if (!st[j])：我得看看 j 是不是已经在这条排队的长龙里了。
 *        - 如果 st[j] == false：他不在队里！说明他本来觉得自己没啥事干在家躺着呢，
 *          赶紧把他拉起来塞进队尾 (q.push(j))，并挂上牌子 (st[j] = true)。
 *        - 如果 st[j] == true：他已经在队里排着了！那太好了，他的数值默默变好了，
 *          等会儿轮到他出队的时候（他会把自己的牌子摘掉 st=false），自然会拿着最新的极品数值去广播，
 *          不用再给他重排一个号了。
 * ==================================================================================
 */