#include <iostream>

using namespace std;

int main() {
    // 优化输入输出流速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    long long MOD = 1e9 + 7;
    long long ans = 0; // 当 n = 1 时，错排数为 0
    
    for (int i = 2; i <= n; ++i) {
        ans = (ans * i) % MOD;
        // 根据公式 Dn = n * D_{n-1} + (-1)^n
        if (i % 2 == 0) {
            ans = (ans + 1) % MOD;
        } else {
            ans = (ans - 1 + MOD) % MOD; // 加上 MOD 防止出现负数求模的情况
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}