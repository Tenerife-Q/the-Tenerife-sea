#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体，并将指向该结构体的指针类型重命名为 Tree
typedef struct TreeNode *Tree;
// 二叉树节点结构体，包含节点数据以及左右子树指针
struct TreeNode {
    int data;
    Tree left;
    Tree right;
};

/**
 * 根据中序遍历和前序遍历序列构建二叉树
 * @param inorder 中序遍历序列数组
 * @param preorder 前序遍历序列数组
 * @param inStart 中序遍历序列的起始索引
 * @param inEnd 中序遍历序列的结束索引
 * @param preStart 前序遍历序列的起始索引
 * @param preEnd 前序遍历序列的结束索引
 * @return 构建好的二叉树的根节点指针
 */
Tree buildTree(int inorder[], int preorder[], int inStart, int inEnd, int preStart, int preEnd) {
    // 如果中序遍历序列的起始索引大于结束索引，说明当前子树为空，返回 NULL
    if (inStart > inEnd) {
        return NULL;
    }

    // 前序遍历的第一个元素是当前子树的根节点的值
    int rootData = preorder[preStart];
    // 为根节点分配内存
    Tree root = (Tree)malloc(sizeof(struct TreeNode));
    // 将根节点的值赋给节点的 data 字段
    root->data = rootData;
    // 初始化根节点的左右子树指针为 NULL
    root->left = root->right = NULL;

    int inRootIndex;
    // 在中序遍历序列中找到根节点的位置
    for (inRootIndex = inStart; inRootIndex <= inEnd; inRootIndex++) {
        if (inorder[inRootIndex] == rootData) {
            break;
        }
    }

    // 计算左子树的节点数量
    int leftLength = inRootIndex - inStart;
    // 递归构建左子树
    root->left = buildTree(inorder, preorder, inStart, inRootIndex - 1, preStart + 1, preStart + leftLength);
    // 递归构建右子树
    root->right = buildTree(inorder, preorder, inRootIndex + 1, inEnd, preStart + leftLength + 1, preEnd);

    return root;
}

/**
 * 对二叉树进行镜面反转
 * @param root 二叉树的根节点指针
 */
void mirror(Tree root) {
    // 如果根节点为空，直接返回
    if (root == NULL) {
        return;
    }

    // 交换根节点的左右子树
    Tree temp = root->left;
    root->left = root->right;
    root->right = temp;

    // 递归对左子树进行镜面反转
    mirror(root->left);
    // 递归对右子树进行镜面反转
    mirror(root->right);
}

/**
 * 对二叉树进行层序遍历
 * @param root 二叉树的根节点指针
 */
void levelOrderTraversal(Tree root) {
    // 如果根节点为空，直接返回
    if (root == NULL) {
        return;
    }

    // 定义一个队列用于层序遍历，队列最大容量为 30
    Tree queue[30];
    // 队列的头指针和尾指针
    int front = 0, rear = 0;

    // 将根节点入队
    queue[rear++] = root;

    // 当队列不为空时，继续遍历
    while (front < rear) {
        // 出队一个节点
        Tree node = queue[front++];
        // 如果该节点有左子树，将左子树节点入队
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        // 如果该节点有右子树，将右子树节点入队
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
        // 如果是第一个出队的节点，直接输出节点值
        if (front == 1) {
            printf("%d", node->data);
        } 
        // 否则，在节点值前加一个空格再输出
        else {
            printf(" %d", node->data);
        }
    }
}

int main() {
    int N;
    // 读取二叉树的节点数量
    scanf("%d", &N);

    // 定义中序遍历和前序遍历序列数组，最大容量为 30
    int inorder[30], preorder[30];
    // 读取中序遍历序列
    for (int i = 0; i < N; i++) {
        scanf("%d", &inorder[i]);
    }
    // 读取前序遍历序列
    for (int i = 0; i < N; i++) {
        scanf("%d", &preorder[i]);
    }

    // 根据中序遍历和前序遍历序列构建二叉树
    Tree root = buildTree(inorder, preorder, 0, N - 1, 0, N - 1);
    // 对构建好的二叉树进行镜面反转
    mirror(root);
    // 对反转后的二叉树进行层序遍历并输出结果
    levelOrderTraversal(root);

    return 0;
}