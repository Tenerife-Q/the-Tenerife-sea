/*
Grundy's Game

There is a heap of n coins and two players who move alternately. On each move, a player chooses a heap and divides into two nonempty heaps that have a different number of coins. The player who makes the last move wins the game.
Your task is to find out who wins if both players play optimally.

有一堆包含 n 枚硬币的硬币堆，两名玩家轮流行动。在每一步行动中，玩家选择一堆硬币并将其分成两个大小不同且非空的硬币堆。进行最后一次移动的玩家赢得游戏。
你的任务是找出在双方都采用最优策略的情况下，谁会赢得游戏。

Input
The first input line contains an integer t: the number of tests.
After this, there are t lines that describe the tests. Each line has an integer n: the number of coins in the initial heap.
第一行输入包含一个整数 t：测试用例的数量。
之后有 t 行描述测试用例。每行包含一个整数 n：初始硬币堆中的硬币数量。

Output
For each test case, print "first" if the first player wins the game and "second" if the second player wins the game.
对于每个测试用例，如果先手玩家获胜则输出 "first"，如果后手玩家获胜则输出 "second"。

Constraints
1 <= t <= 10^5
1 <= n <= 10^6

Example
Input:
3
6
7
8

Output:
first
second
first
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2000;
vector<int> g(MAXN + 1, 0);

// Precompute Grundy values up to MAXN.
// For n > 1222, the Grundy value G(n) is known to be greater than 0, 
// so the first player can always win. So we just need up to 2000.
void precompute() {
    for (int i = 1; i <= MAXN; ++i) {
        vector<bool> mex(MAXN + 1, false);
        for (int j = 1; j * 2 < i; ++j) {
            mex[g[j] ^ g[i - j]] = true;
        }
        int mex_val = 0;
        while (mex[mex_val]) {
            mex_val++;
        }
        g[i] = mex_val;
    }
}

void solve() {
    int n;
    cin >> n;
    if (n >= 2000) {
        cout << "first\n";
    } else {
        if (g[n] != 0) {
            cout << "first\n";
        } else {
            cout << "second\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute();
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}
