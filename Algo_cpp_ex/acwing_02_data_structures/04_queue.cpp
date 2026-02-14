/*
 * ============================================
 *   模拟队列 (Queue) - 数组模拟
 *   题目来源: AcWing 829. 模拟队列
 * ============================================
 * 
 * 【问题】
 *   实现一个队列，支持 push, pop, empty, query 操作。
 * 
 * 【核心思路】
 *   - q[N]: 数组存储元素
 *   - hh: 队头指针，初始 0
 *   - tt: 队尾指针，初始 -1
 *   - 插入: q[++tt] = x
 *   - 弹出: hh++
 *   - 判空: hh <= tt
 * 
 * 【复杂度】
 *   - 所有操作 O(1)
 */

#include <iostream>
#include <string>

using namespace std;

const int N = 100010;

int m;
/*
 * 队列 (Queue) - "FIFO (First In First Out)"
 * 
 * q: 队列数组
 * hh: 队头指针 (Head) - 指向当前队头元素
 * tt: 队尾指针 (Tail) - 指向当前队尾元素
 * 
 * - 初始状态: hh = 0, tt = -1 (表示空，因为 hh > tt)
 * - 判空条件: hh <= tt
 * 
 * 执行图解 (push 10, push 20, pop):
 * 1. hh=0, tt=-1 : [ ]
 * 2. hh=0, tt=0  : [ 10 ]
 * 3. hh=0, tt=1  : [ 10, 20 ]
 * 4. hh=1, tt=1  : [ (10), 20 ] (10被逻辑出队，永远留在了数组前端)
 */
int q[N], hh = 0, tt = -1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m;
    while (m -- ) {
        string op;
        int x;

        cin >> op;
        if (op == "push") {
            cin >> x;
            q[ ++ tt] = x; // 队尾指针后移，新人入队
        }
        else if (op == "pop") {
            hh ++ ; // 队头指针后移，老队员出局
        }
        else if (op == "empty") {
            cout << (hh <= tt ? "NO" : "YES") << endl; // hh > tt 时为空
        }
        else if (op == "query") {
            cout << q[hh] << endl;
        }
    }

    return 0;
}
