/*
 * ============================================
 *   单调栈 (Monotonic Stack)
 *   题目来源: AcWing 830. 单调栈
 * ============================================
 * 
 * 【问题】
 *   给定一个长度为 N 的整数数列，输出每个数左边第一个比它小的数，如果不存在则输出 -1。
 * 
 * 【核心思路】
 *   - 维护一个单调递增的栈。
 *   - 当新元素 x 进来时，如果栈顶元素 >= x，说明栈顶元素不再可能是“左边第一个比后面某个数小”的候选项（因为x更小且更靠右，优于栈顶），故弹出。
 *   - 弹出直到栈顶 < x 或栈空。
 *   - 此时栈顶即为答案。然后将 x 入栈。
 * 
 * 【复杂度】
 *   - 每个元素最多进栈一次、出栈一次，O(n)
 */

#include <iostream>

using namespace std;

const int N = 100010;

int n;
int stk[N], tt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    
    // 初始化栈（默认为0，但显式 tt=0 更清晰）
    tt = 0;
    
    for (int i = 0; i < n; i ++ ) {
        int x;
        cin >> x;
        
        // 当栈不为空 且 栈顶元素 >= 当前元素
        while (tt && stk[tt] >= x) tt -- ;
        
        if (tt) cout << stk[tt] << " ";
        else cout << "-1 ";
        
        stk[ ++ tt] = x;
    }
    
    cout << endl;

    return 0;
}
