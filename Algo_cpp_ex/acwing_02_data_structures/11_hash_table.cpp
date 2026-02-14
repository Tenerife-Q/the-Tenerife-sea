/*
 * ============================================
 *   哈希表 (Hash Table) - 拉链法
 *   题目来源: AcWing 840. 模拟散列表
 * ============================================
 * 
 * 【问题】
 *   维护一个集合，支持操作：
 *   1. I x: 插入一个整数 x
 *   2. Q x: 询问整数 x 是否在集合中出现了
 * 
 * 【核心思路】
 *   - 模数 N 取质数，且尽量离 2 的幂远，冲突概率小。
 *   - h[k]: 存储哈希值为 k 的链表头结点下标。
 *   - 链表存储: e[idx], ne[idx], idx.
 *   - Hash函数: (x % N + N) % N (保证正数)
 * 
 * 【复杂度】
 *   - 期望 O(1)
 */

#include <iostream>
#include <cstring>

using namespace std;

// 选取由主要质数组成的模数
const int N = 100003;

int h[N], e[N], ne[N], idx;

void insert(int x) {
    int k = (x % N + N) % N;
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx ++ ;
}

bool find(int x) {
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i]) {
        if (e[i] == x) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(h, -1, sizeof h);

    int n;
    cin >> n;
    while (n -- ) {
        char op[2];
        int x;
        cin >> op >> x;
        if (*op == 'I') insert(x);
        else {
            if (find(x)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }

    return 0;
}
