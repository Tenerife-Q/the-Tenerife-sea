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
            q[ ++ tt] = x;
        }
        else if (op == "pop") {
            hh ++ ;
        }
        else if (op == "empty") {
            cout << (hh <= tt ? "NO" : "YES") << endl;
        }
        else if (op == "query") {
            cout << q[hh] << endl;
        }
    }

    return 0;
}
