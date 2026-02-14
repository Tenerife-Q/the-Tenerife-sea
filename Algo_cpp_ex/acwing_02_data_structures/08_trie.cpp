/*
 * ============================================
 *   Trie字典树 (Prefix Tree)
 *   题目来源: AcWing 835. Trie字符串统计
 * ============================================
 * 
 * 【问题】
 *   维护一个字符串集合，支持：
 *   1. 插入一个字符串
 *   2. 查询一个字符串出现的次数
 * 
 * 【核心思路】
 *   - son[p][u]:以此节点p为父节点，u字符为边的子节点下标。
 *   - cnt[p]:以节点p结尾的字符串个数。
 *   - idx:当前用到的节点下标，0是根节点。
 * 
 * 【复杂度】
 *   - 插入/查询: O(len)
 */

#include <iostream>

using namespace std;

const int N = 100010;

// son[N][26] 存储树中每个节点的子节点
// cnt[N] 存储以每个节点结尾的单词数量
// idx 当前用到了哪个下标
int son[N][26], cnt[N], idx;
char str[N];

void insert(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i ++ ) {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++ ;
}

int query(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i ++ ) {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    while (n -- ) {
        char op[2];
        cin >> op >> str;
        if (*op == 'I') insert(str);
        else cout << query(str) << endl;
    }

    return 0;
}
