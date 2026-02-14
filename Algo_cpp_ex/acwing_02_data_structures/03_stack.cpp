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
/*
 * 栈 (Stack) - "LIFO (Last In First Out)"
 * 
 * stk: 栈数组
 * tt: 栈顶指针 (Top of stack)
 * - 初始为0，表示栈空
 * - 数据从下标 1 开始存储
 * 
 * 执行图解 (push 10, push 20, pop):
 * 1. tt=0: [ ]
 * 2. tt=1: [ 10 ]
 * 3. tt=2: [ 10, 20 ]
 * 4. tt=1: [ 10 ] (实际上stk[2]还是20，只是逻辑删除了)
 */
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
            stk[ ++ tt] = x;    // 先移动指针，再填入数据
        }
        else if (op == "pop") {
            tt -- ;             // 指针回退，数据被"逻辑删除"
        }
        else if (op == "empty") {
            cout << (tt > 0 ? "NO" : "YES") << endl; // tt=0表示空
        }
        else if (op == "query") {
            cout << stk[tt] << endl;
        }
    }

    return 0;
}
