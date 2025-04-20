#include <stdio.h>

// 查找两个节点的最近公共祖先
int findCommonAncestor(int i, int j) {
    while (i != j) {
        if (i > j) {
            i /= 2;
        } else {
            j /= 2;
        }
    }
    return i;
}

int main() {
    int n;
    // 读取顺序存储的最大容量
    scanf("%d", &n);

    int tree[1001];
    // 读取二叉树节点的值
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tree[i]);
    }

    int i, j;
    // 读取要查找的两个节点编号
    scanf("%d %d", &i, &j);

    // 检查节点 i 是否为空节点
    if (tree[i] == 0) {
        printf("ERROR: T[%d] is NULL\n", i);
        return 0;
    }

    // 检查节点 j 是否为空节点
    if (tree[j] == 0) {
        printf("ERROR: T[%d] is NULL\n", j);
        return 0;
    }

    // 查找最近公共祖先
    int ancestor = findCommonAncestor(i, j);

    // 输出最近公共祖先的编号和值
    printf("%d %d\n", ancestor, tree[ancestor]);

    return 0;
}