#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 创建新节点
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 前序递归遍历
void preorderRecursive(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

// 中序递归遍历
void inorderRecursive(TreeNode* root) {
    if (root == NULL) return;
    inorderRecursive(root->left);
    printf("%d ", root->data);
    inorderRecursive(root->right);
}

// 后序非递归遍历
void postorderNonRecursive(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 >= 0) {
        TreeNode* node = stack1[top1--];
        stack2[++top2] = node;
        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }

    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->data);
    }
}

// 层序非递归遍历
void levelOrderNonRecursive(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;
    while (front < rear) {
        TreeNode* node = queue[front++];
        printf("%d ", node->data);
        if (node->left) queue[rear++] = node->left;
        if (node->right) queue[rear++] = node->right;
    }
}

// 构造二叉树（示例）
TreeNode* constructTree() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    return root;
}

int main() {
    TreeNode* root = constructTree();

    printf("前序递归遍历: ");
    preorderRecursive(root);
    printf("\n");

    printf("中序递归遍历: ");
    inorderRecursive(root);
    printf("\n");

    printf("后序非递归遍历: ");
    postorderNonRecursive(root);
    printf("\n");

    printf("层序非递归遍历: ");
    levelOrderNonRecursive(root);
    printf("\n");

    return 0;
}