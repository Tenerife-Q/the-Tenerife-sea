/*
题目：Josephus Queries (约瑟夫问题查询)

描述（中）：给定 n 个人围成一圈，从某个方向开始按固定规则每轮删除若干人。对于给定的 k，求第 k 个被删除的人在原始编号中的序号。

Description (EN): Given n people in a circle, repeatedly remove people according to a fixed pattern. For a query k, find the label of the k-th removed person in the original numbering (CSES — Josephus Queries).

说明：本文件包含若干实现，末尾附有“神级解法”及其逐行讲解（注释）。
*/
// #include <iostream>

// using namespace std;

// // 核心递归函数：求 n 个人中第 k 个出局的编号
// int solve(int n, int k) {
//     // 递归边界：只有1个人时，无论如何出局的只能是1
//     if (n == 1) return 1;
    
//     // 如果 k 落在第一圈
//     if (k <= n / 2) {
//         return 2 * k;
//     }
    
//     // c 是第一圈移除的人数
//     int c = n / 2;
    
//     // 如果 n 是偶数
//     if (n % 2 == 0) {
//         int idx = solve(n / 2, k - c);
//         return 2 * idx - 1;
//     } 
//     // 如果 n 是奇数
//     else {
//         int idx = solve(n - c, k - c);
//         if (idx == 1) {
//             return n;
//         } else {
//             return 2 * idx - 3;
//         }
//     }
// }

// int main() {
//     // 优化输入输出流（非常重要，因为有 10^5 次查询）
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int q;
//     if (cin >> q) {
//         while (q--) {
//             int n, k;
//             cin >> n >> k;
//             cout << solve(n, k) << "\n";
//         }
//     }
    
//     return 0;
// }

#include <iostream>
using namespace std;
int Josephus(int n, int k) {
    if(n == 1) return 1;
    if(k <= n / 2) return 2*k;

    int c = n / 2;
    if(n % 2 == 0) {
        int idx = Josephus(n / 2, k - c);
        return 2*idx-1;
    }
    else {
        int idx = Josephus(n - c, k - c);
        if(idx == 1) {
            return n;
        } else {
            return 2*idx-3;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    if (cin >> q) {
        while(q--) {
            int n, k;
            cin >> n >> k;
            cout << Josephus(n, k) << "\n";
        }
    }
}


// 神级解法
// #include <iostream>
// using namespace std;

// int child(int n, int k, int p) {
//     int r = (n + p) / 2;
//     if (k <= r) return k * 2 - p;
//     int u = n % 2 == 0 ? p : 1 - p;
//     return child(n - r, k - r, u) * 2 - 1 + p;
// }

// int main() {
//     int q;
//     cin >> q;

//     for (int qi = 1; qi <= q; qi++) {
//         int n, k;
//         cin >> n >> k;
//         cout << child(n, k, 0) << "\n";
//     }
// }

/*
这是一份非常高级、极其优雅的代码！

如果你看懂了或者写出了这段代码，说明你的数学抽象能力非常强。这段代码比我之前给你的基础版还要巧妙得多。

它通过引入一个参数 `p`（表示“偏移量”或“奇偶性”），完美地统一了所有的奇偶情况，避免了“把最后一个人强行移到最前面”那种稍微有点繁琐的讨论。

我来为你详细拆解一下这段“神仙代码”的绝妙之处：

核心魔法：参数 `p` 的含义
在这段代码中，`p` 只有两个取值：`0` 或 `1`。
    - 当 `p = 0` 时：代表我们在这一圈要删除偶数位置的人（第 2, 4, 6... 个）。这也是最开始（第一圈）的状态。
    - 当 `p = 1` 时：代表我们在这一圈要删除奇数位置的人（第 1, 3, 5... 个）。

代码逐行解析：

int child(int n, int k, int p) {
    - `n`: 当前圈里还剩几个人。
    - `k`: 我们还要找第几个出局的人。
    - `p`: 当前圈的出局规则（0=删偶数，1=删奇数）。

int r = (n + p) / 2;
    - 这行在算：当前这一圈会淘汰掉多少人？
        * 如果 `p = 0` (删偶数)，淘汰人数就是 n/2（向下取整）。
        * 如果 `p = 1` (删奇数)，淘汰人数就是 (n+1)/2（向上取整）。
        * `r = (n + p) / 2` 这一句非常巧妙地把两种情况用一个数学式子统一了。

if (k <= r) return k * 2 - p;
    - 这行在算：如果 k 在这一圈就被淘汰了，他是几号？
        * 如果 `p = 0`（删偶数），出局的依次是 2,4,6... 返回的就是 2k。公式 k*2 - 0 刚好成立。
        * 如果 `p = 1`（删奇数），出局的依次是 1,3,5... 返回的就是 2k-1。公式 k*2 -1 也刚好成立。

int u = n % 2 == 0 ? p : 1 - p;
    - 这行最神！它在算：下一圈的规则 `u` 是什么？
        * 如果当前人数 `n` 是偶数：这一圈删完后，下一圈的规则不变，所以 `u = p`。
        * 如果当前人数 `n` 是奇数：这一圈删完后，会“错位”，下一圈的规则会反转，`1 - p` 就是极其优雅的反转操作（0变1，1变0）。

return child(n - r, k - r, u) * 2 - 1 + p;
    - 这行在进行状态还原：递归去下一圈找答案（人数 n-r，找第 k-r 人，规则 u），拿到结果后把编号还原回本圈。
    - 如果本圈 p = 0（删偶数，活下来的是奇数），还原公式是 `编号*2 - 1`。
    - 如果本圈 p = 1（删奇数，活下来的是偶数），还原公式是 `编号*2`。
    - 作者把两者合并为 `编号*2 - 1 + p`，非常巧妙。

评价总结：
 1. 时间复杂度：O(log n)。
 2. 空间复杂度：O(log n)（递归栈）。
 3. 代码风格：极其精练，是这道题的顶级解法之一。

小建议：
由于 q 高达 10^5，建议在 `main` 开头加入输入输出加速：
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

如果你理解了参数 `p` 的设计思路，那么这道题已经完全掌握了！
*/