/*
Stair Game

There is a staircase consisting of n stairs, numbered 1,2,...,n. Initially, each stair has some number of balls.
There are two players who move alternately. On each move, a player chooses a stair k where k != 1 and it has at least one ball. Then, the player moves any number of balls from stair k to stair k-1. The player who moves last wins the game.
Your task is to find out who wins the game when both players play optimally.
Note that if there are no possible moves at all, the second player wins.

有一个由 n 级台阶组成的楼梯，编号为 1,2,...,n。最初，每级台阶上都有一定数量的小球。
有两名轮流行动的玩家。在每一步行动中，玩家选择一个至少有一个小球的台阶 k（其中 k != 1）。
然后，该玩家将任意数量的小球从台阶 k 移动到台阶 k-1。最后移动的玩家赢得游戏。
你的任务是找出在双方都采用最优策略的情况下，谁会赢得游戏。
注意，如果一开始没有任何合法的移动，则后手玩家获胜。

Input
The first input line has an integer t: the number of tests. After this, t test cases are described:
The first line contains an integer n: the number of stairs.
The next line has n integers p_1,p_2,...,p_n: the initial number of balls on each stair.
第一行输入包含一个整数 t：测试用例的数量。之后描述 t 个测试用例：
每个用例的第一行包含一个整数 n：台阶的数量。
下一行包含 n 个整数 p_1,p_2,...,p_n：每级台阶上初始的小球数量。

Output
For each test, print "first" if the first player wins the game and "second" if the second player wins the game.
对于每个测试用例，如果先手玩家获胜则输出 "first"，如果后手玩家获胜则输出 "second"。

Constraints
1 <= t <= 2 * 10^5
1 <= n <= 2 * 10^5
0 <= p_i <= 10^9
the sum of all n is at most 2 * 10^5

Example
Input:
3
3
0 2 1
4
1 1 1 1
2
5 3

Output:
first
second
first
*/

#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    int xor_sum = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        // This is equivalent to Staircase Nim. 
        // Coins on distance i-1 from the end. Only even indexed steps (i.e. distance 1, 3, 5...) matter.
        if (i % 2 == 0) {
            xor_sum ^= x;
        }
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
