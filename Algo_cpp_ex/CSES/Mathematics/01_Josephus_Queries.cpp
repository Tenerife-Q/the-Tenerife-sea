#include <iostream>

using namespace std;

// 核心递归函数：求 n 个人中第 k 个出局的编号
int solve(int n, int k) {
    // 递归边界：只有1个人时，无论如何出局的只能是1
    if (n == 1) return 1;
    
    // 如果 k 落在第一圈
    if (k <= n / 2) {
        return 2 * k;
    }
    
    // c 是第一圈移除的人数
    int c = n / 2;
    
    // 如果 n 是偶数
    if (n % 2 == 0) {
        int idx = solve(n / 2, k - c);
        return 2 * idx - 1;
    } 
    // 如果 n 是奇数
    else {
        int idx = solve(n - c, k - c);
        if (idx == 1) {
            return n;
        } else {
            return 2 * idx - 3;
        }
    }
}

int main() {
    // 优化输入输出流（非常重要，因为有 10^5 次查询）
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    if (cin >> q) {
        while (q--) {
            int n, k;
            cin >> n >> k;
            cout << solve(n, k) << "\n";
        }
    }
    
    return 0;
}