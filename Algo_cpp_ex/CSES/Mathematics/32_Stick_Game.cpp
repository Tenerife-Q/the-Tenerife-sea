/*
Stick Game

Consider a game where two players remove sticks from a heap. The players move alternately, and the player who removes the last stick wins the game.
A set P={p_1,p_2,...,p_k} determines the allowed moves. For example, if P={1,3,4}, a player may remove 1, 3 or 4 sticks.
Your task is find out for each number of sticks 1,2,...,n if the first player has a winning or losing position.

考虑一个游戏：两名玩家轮流从一堆棍子中取走棍子。取走最后一根棍子的玩家获胜。
一个集合 P={p_1,p_2,...,p_k} 决定了允许的取法。例如，如果 P={1,3,4}，那么玩家每次只能取走 1、3 或 4 根棍子。
你的任务是找出当初始棍子数量为 1,2,...,n 时，先手玩家是处于必胜态还是必败态。

Input
The first input line has two integers n and k: the number of sticks and moves.
The next line has k integers p_1,p_2,...,p_k that describe the allowed moves. All integers are distinct, and one of them is 1.
第一行输入包含两个整数 n 和 k：棍子的总数 n 与可用取法的数量 k。
第二行包含 k 个整数 p_1,p_2,...,p_k，描述了允许取走的棍子数量。所有的整数都互不相同，并且其中必须有一个是 1。

Output
Print a string containing n characters: W means a winning position, and L means a losing position.
输出一个包含 n 个字符的字符串：对于每种棍子数量，W 表示先手必胜态，L 表示先手必败态。

Constraints
1 <= n <= 10^6
1 <= k <= 100
1 <= p_i <= n

Example
Input:
10 3
1 3 4

Output:
WLWWWWLWLW
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    if (cin >> n >> k) {
        vector<int> p(k);
        for (int i = 0; i < k; ++i) {
            cin >> p[i];
        }
        
        string result(n, 'L');
        vector<bool> dp(n + 1, false); // dp[i] true if winning pos, false if losing
        
        for (int i = 1; i <= n; ++i) {
            bool can_win = false;
            for (int j = 0; j < k; ++j) {
                if (i >= p[j] && !dp[i - p[j]]) {
                    can_win = true;
                    break;
                }
            }
            dp[i] = can_win;
            if (can_win) {
                result[i - 1] = 'W';
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> move(k);
    for (int i = 0; i < k; i++) {
        cin >> move[i];
    }

    string pos(n + 1, 'L');
    for (int i = 1; i <= n; i++) {
        for (auto m : move) {
            if (i - m >= 0 && pos[i - m] == 'L') {
                pos[i] = 'W';
            }
        }
    }
    cout << pos.substr(1) << "\n";
    // 这里的 substr(1) 是为了去掉 pos 字符串开头的 'L'，只保留从索引 1 开始的部分，即对应 1 到 n 的棍子数量的结果。
}



#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> move(k);
    for (int i = 0; i < k; i++) {
        cin >> move[i];
    }

    string pos(n + 1, 'L');
    for (int i = 1; i <= n; i++ ) {
        for (int j = 0; j < k; j++) {
            if( i - move[j] >= 0 && pos[i - move[j]] == 'L') {
                pos[i] = 'W';
                break;
            }
        }
    }
    cout << pos.substr(1) << "\n";
}