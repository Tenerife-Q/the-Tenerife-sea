#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

void levelOrderRecursiveHelper(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else {
        levelOrderRecursiveHelper(root->left, level - 1);
        levelOrderRecursiveHelper(root->right, level - 1);
    }
}

int height(Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
}

void levelOrderRecursive(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        levelOrderRecursiveHelper(root, i);
    }
}