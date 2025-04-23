# Binary Tree Traversal

This project implements various binary tree traversal algorithms in C. The main purpose of this project is to demonstrate the different methods of traversing a binary tree, including both recursive and non-recursive approaches.

## Project Structure

```
binary-tree-traversal
├── src
│   ├── main.c                  # Entry point of the program, initializes the binary tree and tests traversal algorithms.
│   ├── binary_tree.h           # Header file containing the structure definition and function declarations for binary tree operations.
│   ├── binary_tree.c           # Implementation of basic binary tree operations such as insertion and deletion.
│   ├── traversals
│   │   ├── preorder_recursive.c  # Implementation of the recursive preorder traversal algorithm.
│   │   ├── inorder_recursive.c    # Implementation of the recursive inorder traversal algorithm.
│   │   ├── postorder_non_recursive.c # Implementation of the non-recursive postorder traversal algorithm using a stack.
│   │   ├── levelorder_recursive.c # Implementation of the recursive level order traversal algorithm.
│   │   └── levelorder_non_recursive.c # Implementation of the non-recursive level order traversal algorithm using a queue.
├── Makefile                     # Makefile for compiling the project.
└── README.md                    # Documentation for the project.
```

## Traversal Algorithms

1. **Preorder Traversal (Recursive)**: Visits the root node first, then recursively visits the left subtree, followed by the right subtree.

2. **Inorder Traversal (Recursive)**: Recursively visits the left subtree first, then visits the root node, followed by the right subtree.

3. **Postorder Traversal (Non-Recursive)**: Uses a stack to simulate the recursive process, visiting the left and right subtrees before the root node.

4. **Level Order Traversal (Recursive)**: Visits nodes level by level, starting from the root and moving downwards.

5. **Level Order Traversal (Non-Recursive)**: Uses a queue to traverse the tree level by level.

## Usage

To compile the project, navigate to the project directory and run:

```
make
```

This will compile all the source files and create an executable. You can then run the program to see the traversal results.

## Conclusion

This project serves as a practical demonstration of binary tree traversal algorithms in C. It provides a clear understanding of how different traversal methods work and their implementations.