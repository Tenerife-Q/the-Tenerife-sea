#include <stdio.h>
#include "binary_tree.h"

// Function prototypes for traversal tests
void test_preorder_recursive(Node* root);
void test_inorder_recursive(Node* root);
void test_postorder_non_recursive(Node* root);
void test_levelorder_recursive(Node* root);
void test_levelorder_non_recursive(Node* root);

int main() {
    // Initialize the binary tree
    Node* root = NULL;

    // Insert nodes into the binary tree (example values)
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);

    // Test different traversal algorithms
    printf("Preorder Traversal:\n");
    test_preorder_recursive(root);

    printf("\nInorder Traversal:\n");
    test_inorder_recursive(root);

    printf("\nPostorder Traversal (Non-Recursive):\n");
    test_postorder_non_recursive(root);

    printf("\nLevel Order Traversal (Recursive):\n");
    test_levelorder_recursive(root);

    printf("\nLevel Order Traversal (Non-Recursive):\n");
    test_levelorder_non_recursive(root);

    // Free the binary tree (not shown here)
    return 0;
}