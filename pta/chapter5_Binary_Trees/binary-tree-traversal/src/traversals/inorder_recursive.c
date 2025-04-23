#include "binary_tree.h"
#include <stdio.h>

void inorder_recursive(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder_recursive(root->left);
    printf("%d ", root->data);
    inorder_recursive(root->right);
}