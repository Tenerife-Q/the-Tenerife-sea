/*
 * @Problem: Another Game
 * @Source: CSES - Mathematics
 * 
 * @Description (English): 
 * There are n heaps of coins and two players who move alternately. On each move, 
 * a player selects some of the nonempty heaps and removes one coin from each heap. 
 * The player who removes the last coin wins the game.
 * Your task is to find out who wins if both players play optimally.
 * 
 * @Description (Chinese):
 * 有 n 堆硬币，两名玩家轮流行动。在每一步行动中，玩家选择一些非空的硬币堆，
 * 并从选中的每一堆中移除一枚硬币。取走最后一枚硬币的玩家赢得游戏。
 * 你的任务是找出在双方都采用最优策略的情况下，谁会赢得游戏。
 * 
 * @Algorithm:
 * Game Theory / Parity (博弈论 / 奇偶性)
 * If all heaps have an even number of coins, the second player can always mirror 
 * the first player's move to keep all heaps even until they reach 0 -> second wins.
 * If there is at least one odd heap, the first player can pick exactly 1 coin 
 * from all odd heaps, making all heaps even for the second player -> first wins.
 * (只要所有堆都是偶数，先手无论怎么取，后手都可以模仿取相同的堆，保持所有堆是偶数，后手赢；
 *  只要存在至少一堆是奇数，先手就可以一次性把所有奇数堆各取1个，变成全偶数态抛给后手，先手赢。)
 */

#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;
    bool has_odd = false;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        // 如果我们遇到任何一个奇数
        if (x % 2 != 0) {
            has_odd = true;
        }
    }
    
    // 如果存在至少一个奇数堆，先手必胜；如果全是偶数堆，后手必胜
    if (has_odd) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
}

int main() {
    // 优化标准 C++ I/O 操作以提高读取速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}



#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        bool win = false;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x % 2 == 1) win = true;
        }
        cout << (win ? "first" : "second") << "\n";
    }
}