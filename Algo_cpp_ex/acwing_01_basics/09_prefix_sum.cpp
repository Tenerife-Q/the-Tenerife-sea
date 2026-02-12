#include <iostream>
#include <vector>

using namespace std;

/*
 * AcWing 算法基础课 - 前缀和
 * 核心公式：S[i] = S[i-1] + a[i]
 * 区间查询：sum[l, r] = S[r] - S[l-1]
 * 
 * 注意：为了处理方便，通常让数组下标从 1 开始。
 */

const int N = 100010;
int n, m;
int a[N], s[N]; // a是原数组, s是前缀和数组

int main() {
    // 提升 cin/cout 速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 输入格式通常是：n个元素，m次查询
    // 例如：
    // 5 3
    // 2 1 3 6 4
    // 1 2
    // 1 3
    // 2 4
    
    cout << "请输入数组长度 n 和查询次数 m: ";
    if (!(cin >> n >> m)) return 0;

    cout << "请输入 " << n << " 个整数: ";
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        // 核心步骤：构造前缀和数组
        // S[i] = S[i-1] + a[i]
        s[i] = s[i - 1] + a[i];
    }

    cout << "前缀和构造完成。请输入 " << m << " 组查询 (l r):" << endl;
    while (m--) {
        int l, r;
        cin >> l >> r;
        // 核心步骤：O(1) 查询区间和
        // 区间 [l, r] 的和 = S[r] - S[l-1]
        cout << "区间 [" << l << ", " << r << "] 的和为: " << s[r] - s[l - 1] << endl;
    }

    return 0;
}
