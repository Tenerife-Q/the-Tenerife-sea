#include <stdio.h>
#include "binary_tree.h"

// 前序遍历的递归算法
void preorder_recursive(Node* root) {
    if (root == NULL) {
        return;
    }
    // 访问根节点
    printf("%d ", root->data);
    // 遍历左子树
    preorder_recursive(root->left);
    // 遍历右子树
    preorder_recursive(root->right);
}