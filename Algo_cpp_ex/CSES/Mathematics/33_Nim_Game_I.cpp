/*
Nim Game I

There are n heaps of sticks and two players who move alternately. On each move, a player chooses a non-empty heap and removes any number of sticks. The player who removes the last stick wins the game.
Your task is to find out who wins if both players play optimally.

有 n 堆棍子和两名轮流行动的玩家。在每一步行动中，玩家选择一个非空的堆并从中取走任意数量（至少一根）的棍子。取走最后一根棍子的玩家将赢得游戏。
你的任务是找出在双方都采用最优策略的情况下，谁会赢得游戏。

Input
The first input line contains an integer t: the number of tests. After this, t test cases are described:
The first line contains an integer n: the number of heaps.
The next line has n integers x_1,x_2,...,x_n: the number of sticks in each heap.
第一行输入包含一个整数 t：测试用例的数量。之后描述 t 个测试用例：
每个用例的第一行包含一个整数 n：堆的数量。
下一行包含 n 个整数 x_1,x_2,...,x_n：表示每一堆中的棍子数量。

Output
For each test case, print "first" if the first player wins the game and "second" if the second player wins the game.
对于每个测试用例，如果先手玩家赢得游戏则输出 "first" ，如果后手玩家赢得游戏则输出 "second" 。

Constraints
1 <= t <= 2 * 10^5
1 <= n <= 2 * 10^5
1 <= x_i <= 10^9
the sum of all n is at most 2 * 10^5

Example
Input:
3
4
5 7 2 5
2
4 1
3
3 5 6

Output:
first
first
second
*/

#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    int xor_sum = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        xor_sum ^= x;
    }
    
    if (xor_sum != 0) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
}

int main() {
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

    while (t--) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            sum ^= x;
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
