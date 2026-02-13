/*
 * ============================================
 *   模拟栈 (Stack) - 数组模拟
 *   题目来源: AcWing 828. 模拟栈
 * ============================================
 * 
 * 【问题】
 *   实现一个栈，支持 push, pop, empty, query 操作。
 * 
 * 【核心思路】
 *   - stk[N]: 数组存储元素
 *   - tt: 栈顶指针，初始为0
 *   - 插入: stk[++tt] = x
 *   - 弹出: tt--
 *   - 判空: tt > 0 ? not empty : empty
 * 
 * 【复杂度】
 *   - 所有操作 O(1)
 */

#include <iostream>
#include <string>

using namespace std;

const int N = 100010;

int m;
int stk[N], tt = 0;

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
            stk[ ++ tt] = x;
        }
        else if (op == "pop") {
            tt -- ;
        }
        else if (op == "empty") {
            cout << (tt > 0 ? "NO" : "YES") << endl;
        }
        else if (op == "query") {
            cout << stk[tt] << endl;
        }
    }

    return 0;
}
