#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX 100

// 邻接矩阵图结构
typedef struct {
    int matrix[MAX_VERTEX][MAX_VERTEX];
    int vexnum, edgenum;  // 顶点数和边数
} GraphMatrix;

// 队列结构（用于BFS）
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 初始化队列
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// 入队
void enqueue(Queue* q, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 出队
int dequeue(Queue* q) {
    if (q->front == NULL) return -1;
    QueueNode* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return data;
}

// 判断队列是否为空
bool isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// 初始化邻接矩阵
void initGraphMatrix(GraphMatrix* g) {
    printf("输入顶点数和边数：");
    scanf("%d %d", &g->vexnum, &g->edgenum);
    // 初始化矩阵为全0
    for (int i = 0; i < g->vexnum; i++) {
        for (int j = 0; j < g->vexnum; j++) {
            g->matrix[i][j] = 0;
        }
    }
    printf("输入边（格式：起点 终点）：\n");
    for (int i = 0; i < g->edgenum; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        g->matrix[v1][v2] = 1;
        g->matrix[v2][v1] = 1; // 无向图
    }
}

// DFS遍历（栈实现）
void dfsMatrix(GraphMatrix* g, int start) {
    int stack[MAX_VERTEX], top = -1;
    bool visited[MAX_VERTEX] = {false};
    stack[++top] = start;
    visited[start] = true;
    while (top != -1) {
        int u = stack[top--];
        printf("%d ", u);
        // 逆序入栈保证遍历顺序与递归一致
        for (int i = g->vexnum - 1; i >= 0; i--) {
            if (g->matrix[u][i] && !visited[i]) {
                stack[++top] = i;
                visited[i] = true;
            }
        }
    }
}

// BFS遍历
void bfsMatrix(GraphMatrix* g, int start) {
    Queue q;
    initQueue(&q);
    bool visited[MAX_VERTEX] = {false};
    enqueue(&q, start);
    visited[start] = true;
    while (!isQueueEmpty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        for (int i = 0; i < g->vexnum; i++) {
            if (g->matrix[u][i] && !visited[i]) {
                enqueue(&q, i);
                visited[i] = true;
            }
        }
    }
}

// 测试代码
int main() {
    GraphMatrix g;
    initGraphMatrix(&g);
    printf("\n邻接矩阵DFS遍历结果：");
    dfsMatrix(&g, 0);
    printf("\n邻接矩阵BFS遍历结果：");
    bfsMatrix(&g, 0);
    return 0;
}