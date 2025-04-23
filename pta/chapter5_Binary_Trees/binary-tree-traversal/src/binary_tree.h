// This file contains the definition of the binary tree structure and function declarations for basic operations.

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function declarations
Node* createNode(int data);
Node* insert(Node* root, int data);
void freeTree(Node* root);
void preorderTraversal(Node* root);
void inorderTraversal(Node* root);
void postorderTraversal(Node* root);
void levelOrderTraversal(Node* root);

#endif // BINARY_TREE_H