#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Stack {
    Node** array;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Node**)malloc(stack->capacity * sizeof(Node*));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    if (!isFull(stack)) {
        stack->array[++stack->top] = node;
    }
}

Node* pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return NULL;
}

Node* peek(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top];
    }
    return NULL;
}

void postorderNonRecursive(Node* root) {
    if (root == NULL) {
        return;
    }

    Stack* stack = createStack(100);
    Node* lastVisited = NULL;

    while (!isEmpty(stack) || root != NULL) {
        if (root != NULL) {
            push(stack, root);
            root = root->left;
        } else {
            Node* peekNode = peek(stack);
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                root = peekNode->right;
            } else {
                printf("%d ", peekNode->data);
                lastVisited = pop(stack);
            }
        }
    }

    free(stack->array);
    free(stack);
}