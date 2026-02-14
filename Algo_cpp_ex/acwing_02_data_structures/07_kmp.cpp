/*
 * ============================================
 *   KMP字符串匹配 (Knuth-Morris-Pratt)
 *   题目来源: AcWing 831. KMP字符串
 * ============================================
 * 
 * 【问题】
 *   给定模式串 P 和长文本串 S，求 P 在 S 中出现的所有位置。
 * 
 * 【核心思路】
 *   - 此模板下标从 1 开始。
 *   - next[i] (ne[i]): P[1...i] 的最长相等前后缀长度。
 *   - 匹配过程：利用 ne[] 数组在失配时跳跃，避免回溯。
 *   
 * 【模板细节】
 *   1. 求 Next 数组：也就是 P 匹配 P 自身。
 *   2. 真正的匹配：S 匹配 P。
 * 
 * 【复杂度】
 *   - O(N + M)
 */

#include <iostream>

using namespace std;

const int N = 100010, M = 1000010;

int n, m;
char p[N], s[M];
int ne[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 下标从1开始
    cin >> n >> (p + 1);
    cin >> m >> (s + 1);

    // 求next数组
    // i从2开始，j从0开始（j代表前缀末尾下标，i代表后缀末尾下标）
    for (int i = 2, j = 0; i <= n; i ++ ) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j ++ ;
        ne[i] = j;
    }

    // kmp匹配
    for (int i = 1, j = 0; i <= m; i ++ ) {
        // s[i] 和 p[j+1] 尝试匹配
        while (j && s[i] != p[j + 1]) j = ne[j];
        
        if (s[i] == p[j + 1]) j ++ ;
        
        if (j == n) {
            // 匹配成功，输出起始位置（下标从0开始算的话就是 i-n）
            cout << i - n << " ";
            // 继续寻找下一个匹配，相当于此次匹配结束后，j跳回ne[j]
            j = ne[j]; 
        }
    }

    return 0;
}
