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