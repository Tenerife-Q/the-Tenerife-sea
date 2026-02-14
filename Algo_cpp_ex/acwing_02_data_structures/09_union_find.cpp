/*
 * ============================================
 *   并查集 (Union-Find)
 *   题目来源: AcWing 836. 合并集合
 * ============================================
 * 
 * 【问题】
 *   一共有 n 个数，编号 1~n。支持：
 *   1. 合并两个集合
 *   2. 询问两个元素是否在同一个集合中
 * 
 * 【核心思路】
 *   - p[x]: 存储x的父节点
 *   - 核心操作 find(x): 返回x的祖宗节点 + 路径压缩
 *   - 合并: p[find(a)] = find(b)
 *   - 初始化: p[i] = i (每个点是自己的集合)
 * 
 * 【复杂度】
 *   - 近乎 O(1)
 */

#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int p[N];

// 返回x的祖宗节点 + 路径压缩
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i ++ ) p[i] = i;

    while (m -- ) {
        char op[2];
        int a, b;
        cin >> op >> a >> b;

        if (op[0] == 'M') p[find(a)] = find(b);
        else {
            if (find(a) == find(b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }

    return 0;
}
