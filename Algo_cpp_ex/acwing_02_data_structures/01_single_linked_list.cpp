/*
 * ============================================
 *   单链表 (Single Linked List) - 数组模拟
 *   题目来源: AcWing 826. 单链表
 * ============================================
 * 
 * 【问题】
 *   实现一个单链表，支持以下操作：
 *   1. 向链表头插入一个数；
 *   2. 删除第 k 个插入的数后面的数；
 *   3. 在第 k 个插入的数后插入一个数。
 * 
 * 【核心思路】
 *   使用数组模拟链表（静态链表），速度快于动态 `new` 节点。
 *   - e[i]: 存储节点i的值
 *   - ne[i]: 存储节点i的next指针（下一节点的下标）
 *   - idx: 当前用到了哪个下标（内存池指针）
 *   - head: 头结点的下标，初始为-1
 * 
 * 【图解】
 *   idx:   0    1    2
 *   e:   [10] [20] [30] ...
 *   ne:  [ 1] [ 2] [-1] ...
 *   head -> 0 -> 1 -> 2 -> -1
 * 
 * 【复杂度】
 *   - 插入/删除: O(1)
 *   - 遍历: O(n)
 */

#include <iostream>

using namespace std;

const int N = 100010;

// head: 头结点的下标
// e[i]: 节点i的值
// ne[i]: 节点i的next指针
// idx: 当前已经用到了哪个点
int head, e[N], ne[N], idx;

// 初始化
void init() {
    head = -1;
    idx = 0;
}

// 将x查到头结点
/*
    1.head → [老头节点]
    2.head -.-> [新节点 idx] -.-> [老头节点]

    新节点（idx）成为了新的头节点。
    新节点的 ne（next）指针指向原来的老头节点。
    head 指针更新为指向新节点 idx。
*/
void add_to_head(int x) {
    e[idx] = x;
    ne[idx] = head;
    head = idx ++ ;
}

// 将x插入到下标为k的点后面
/*
    1.节点 k —(ne[k])→ 节点 B
    2.节点 k —(ne[k])→ [新节点 idx] —(ne[idx])→ 节点 B

    新节点（下标 idx）被插入到节点 k 与节点 B 之间。
    新节点的 next 指向原来的后继节点 B。
    节点 k 的 next 指向新节点 idx。
*/
void add(int k, int x) {
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx ++ ;
}

// 将下标为k的点后面的点删掉
/*
    删除节点 B 后，节点 k 的 next 指向节点 C
    1.节点 k —(ne[k])→ [节点 B] —(ne[ne[k]])→ 节点 C
    2.节点 k —(ne[k])→ 节点 C

    节点 k 的 next 指针直接指向原后继的后继（ne[ne[k]]）。
    节点 B 从链表中被逻辑删除——没有任何节点指向它，但它仍然占据内存，
        其 next 值也未被清除（在数组模拟链表中通常不清除）。
    若后续需要物理删除（释放内存），在支持动态内存的语言中应执行 delete；
        在静态数组模拟中，只需将其“跳过”即可。
*/
void remove(int k) {
    ne[k] = ne[ne[k]];
}

int main() {
    // 优化IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    int m;
    cin >> m;

    while (m -- ) {
        int k, x;
        char op;

        cin >> op;
        if (op == 'H') {
            cin >> x;
            add_to_head(x);
        }
        else if (op == 'D') {
            cin >> k;
            // 因为k是第k个插入的数，而我们idx是从0开始的，所以第k个插入的数下标是k-1
            if (k == 0) head = ne[head]; // 删除头结点的情况，有些题目可能定义k=0为删头
            else remove(k - 1);
        }
        else {
            cin >> k >> x;
            add(k - 1, x);
        }
    }

    for (int i = head; i != -1; i = ne[i]) {
        cout << e[i] << " ";
    }
    cout << endl;

    return 0;
}
