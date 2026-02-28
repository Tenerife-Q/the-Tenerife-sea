#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Problem 5: 犯罪团伙 (扩展域并查集 / 二分图判定)
//
// 题目描述:
// N 个罪犯，M 条线索。
// 线索有两种：
// 1. "F a b": a 和 b 是同伙 (Friend) -> 必须在同一个监狱
// 2. "E a b": a 和 b 是死敌 (Enemy) -> 必须在不同监狱
// 只有两个监狱。
// 判断这些线索是否自相矛盾。如果矛盾，输出第一条矛盾的线索编号。
// 如果所有线索都读完没有矛盾，输出 "OK"。

const int MAXN = 100010;
int parent[2 * MAXN]; // 开 2倍大小，i 表示自己，i+N 表示 i 的敌人(对立面)
int n, m;

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) parent[rootX] = rootY;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    if (cin >> n >> m) {
        for (int i = 1; i <= 2 * n; i++) parent[i] = i;
        
        bool conflict = false;
        int conflict_idx = -1;
        
        for (int i = 1; i <= m; i++) {
            char type;
            int u, v;
            cin >> type >> u >> v;
            
            if (conflict) continue; // 已经发现矛盾，把剩下的读完即可
            
            if (type == 'F') { // 同伙
                // 检查是否已经是死敌
                // 如果 u 和 v 的对立面 (v+n) 在一个集合，或者 u+n 和 v 在一个集合，说明之前标记为死敌
                if (find(u) == find(v + n) || find(u + n) == find(v)) {
                    conflict = true;
                    conflict_idx = i;
                } else {
                    // 没有矛盾，合并
                    // u 和 v 是同伙 -> merge(u, v)
                    // u的敌人 和 v的敌人 是同伙 -> merge(u+n, v+n)
                    unite(u, v);
                    unite(u + n, v + n);
                }
            } else if (type == 'E') { // 死敌
                // 检查是否已经是同伙
                if (find(u) == find(v) || find(u + n) == find(v + n)) {
                    conflict = true;
                    conflict_idx = i;
                } else {
                    // 没有矛盾，标记为死敌
                    // u 和 v 是死敌 -> u 和 v的敌人(v+n) 是一伙 -> merge(u, v+n)
                    // v 和 u 的敌人(u+n) 是一伙 -> merge(v, u+n)
                    unite(u, v + n);
                    unite(v, u + n);
                }
            }
        }
        
        if (conflict) {
            cout << conflict_idx << endl; // 输出第一条矛盾的编号
        } else {
            cout << "OK" << endl;
        }
    } else {
        // 示例
        cout << "示例输入演示:" << endl;
        cout << "3 3" << endl;
        cout << "F 1 2" << endl;
        cout << "E 1 3" << endl;
        cout << "F 2 3" << endl;
        
        // 1-2同伙, 1-3死敌 -> 2-3必须死敌. 
        // 第三句说 2-3同伙 -> 矛盾，输出 3.
        
        n = 3;
        for (int i=1; i<=2*n; i++) parent[i] = i;

        // 1. F 1 2
        unite(1, 2); unite(1+3, 2+3);
        // 2. E 1 3
        unite(1, 3+3); unite(3, 1+3);
        // 3. F 2 3
        // check 2, 3+3? find(2)==find(1)==find(3+3). YES conflict.
        cout << "示例输出: 3" << endl;
    }
    
    return 0;
}
