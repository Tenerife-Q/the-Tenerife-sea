#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX 100

// ---------------------- 队列实现（必须包含） ----------------------
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
    if (!newNode) exit(1); // 内存分配失败
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

// ---------------------- 邻接表实现 ----------------------
typedef struct Node {
    int adjvex;
    struct Node* next;
} Node;

typedef struct {
    Node* vertices[MAX_VERTEX];
    int vexnum, edgenum;
} GraphList;

// 初始化邻接表
void initGraphList(GraphList* g) {
    printf("输入顶点数和边数：");
    scanf("%d %d", &g->vexnum, &g->edgenum);
    for (int i = 0; i < g->vexnum; i++) {
        g->vertices[i] = NULL;
    }
    printf("输入边（格式：起点 终点）：\n");
    for (int i = 0; i < g->edgenum; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        // 头插法添加边（无向图）
        Node* node1 = (Node*)malloc(sizeof(Node));
        node1->adjvex = v2;
        node1->next = g->vertices[v1];
        g->vertices[v1] = node1;

        Node* node2 = (Node*)malloc(sizeof(Node));
        node2->adjvex = v1;
        node2->next = g->vertices[v2];
        g->vertices[v2] = node2;
    }
}

// DFS遍历（递归）
void dfsList(GraphList* g, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    Node* p = g->vertices[v];
    while (p != NULL) {
        if (!visited[p->adjvex]) {
            dfsList(g, p->adjvex, visited);
        }
        p = p->next;
    }
}

// BFS遍历
void bfsList(GraphList* g, int start) {
    bool visited[MAX_VERTEX] = {false};
    Queue q;
    initQueue(&q);
    enqueue(&q, start);
    visited[start] = true;
    while (!isQueueEmpty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        Node* p = g->vertices[u];
        while (p != NULL) {
            if (!visited[p->adjvex]) {
                enqueue(&q, p->adjvex);
                visited[p->adjvex] = true;
            }
            p = p->next;
        }
    }
}

// 释放内存
void freeGraphList(GraphList* g) {
    for (int i = 0; i < g->vexnum; i++) {
        Node* p = g->vertices[i];
        while (p != NULL) {
            Node* temp = p;
            p = p->next;
            free(temp);
        }
    }
}

// 主函数测试
int main() {
    GraphList g;
    initGraphList(&g);
    bool visited[MAX_VERTEX] = {false};
    printf("\n邻接表DFS遍历结果：");
    dfsList(&g, 0, visited);
    printf("\n邻接表BFS遍历结果：");
    bfsList(&g, 0);
    freeGraphList(&g);
    return 0;
}