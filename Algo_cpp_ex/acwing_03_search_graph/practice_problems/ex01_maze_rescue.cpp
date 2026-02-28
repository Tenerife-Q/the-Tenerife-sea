/*
 * 综合练习题1：迷宫救援 (Maze Rescue)
 * 难度：⭐⭐⭐
 * 
 * 【题目描述】
 * 一个 R x C 的迷宫。
 * 'S': 起点
 * 'E': 终点
 * '.': 空地
 * '#': 墙壁
 * 'a'-'e': 钥匙 (捡起后可以打开对应的门)
 * 'A'-'E': 门 (必须有对应的钥匙才能通过)
 * 
 * 求从起点走到终点的最少步数。如果无法到达，输出 -1。
 * 
 * 【算法思路：BFS + 状态压缩】
 * 普通的 BFS 状态是 (x, y)。
 * 但这里如果只记录 (x, y)，可能会出现：
 * 你走到了 (x, y) 面前是一个门 A，你没钥匙。你得回去找钥匙 a，然后再回来。
 * 如果只记录 visited[x][y]，那么你回去的路就被标记为"已访问"，走不通了。
 * 
 * 所以状态必须包含"你手里有哪些钥匙"。
 * 用一个整数 mask (二进制) 表示钥匙状态。
 * 第 0 位为 1 表示有钥匙 a，第 1 位为 1 表示有钥匙 b...
 * 
 * state: (x, y, key_mask)
 * dist[x][y][key_mask]: 记录在该状态下的最小步数。
 * 
 * 队列元素: struct Node { int x, y, mask; }
 * 
 * 转移规则：
 * 1. 遇到 '.': dist[nx][ny][mask] = dist[x][y][mask] + 1
 * 2. 遇到 'a'-'e': 新状态 mask | (1 << (char - 'a'))
 * 3. 遇到 'A'-'E': 检查 mask & (1 << (char - 'A')) 是否为真。是则通行，否则不能走。
 */

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 55;
char g[N][N];
int dist[N][N][1 << 5]; // 最多5把钥匙 a-e
int R, C;

struct Node {
    int x, y, mask;
};

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, -1, sizeof dist);
    queue<Node> q;
    
    // 初始状态：(sx, sy, 0)
    q.push({sx, sy, 0});
    dist[sx][sy][0] = 0;

    while (q.size()) {
        Node t = q.front();
        q.pop();

        if (t.x == ex && t.y == ey) return dist[t.x][t.y][t.mask];

        for (int i = 0; i < 4; i++) {
            int nx = t.x + dx[i];
            int ny = t.y + dy[i];

            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            char c = g[nx][ny];
            if (c == '#') continue;

            // 计算新的 mask (默认和原来一样，除非捡到钥匙)
            int next_mask = t.mask;

            // 1. 遇到门
            if (c >= 'A' && c <= 'E') {
                int door_id = c - 'A';
                if (! (t.mask >> door_id & 1)) continue; // 没钥匙，过不去
            }
            // 2. 遇到钥匙
            else if (c >= 'a' && c <= 'e') {
                int key_id = c - 'a';
                next_mask = t.mask | (1 << key_id);
            }

            // 更新距离
            if (dist[nx][ny][next_mask] == -1) {
                dist[nx][ny][next_mask] = dist[t.x][t.y][t.mask] + 1;
                q.push({nx, ny, next_mask});
            }
        }
    }
    return -1;
}

int main() {
    cin >> R >> C;
    int sx, sy, ex, ey;

    for (int i = 0; i < R; i++) {
        cin >> g[i]; // 读入一行字符串
        for (int j = 0; j < C; j++) {
            if (g[i][j] == 'S') {
                sx = i, sy = j;
            } else if (g[i][j] == 'E') {
                ex = i, ey = j;
                g[i][j] = '.'; // 把终点视为可行走的空地, 方便处理
            }
        }
    }

    /*
     * 测试输入:
     * 5 5
     * S...A
     * .###.
     * .a#..
     * ###..
     * ....E
     * 
     * 门 A 需要钥匙 a。钥匙 a 在 (2, 1)。
     * 路径：S(0,0) -> (2,0) -> a(2,1)捡钥匙 -> 返回(0,0) -> 门A(0,4) -> E
     */

    cout << bfs(sx, sy, ex, ey) << endl;

    return 0;
}
