#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct LNode {
    int data;
    struct LNode *next;
} *List;

// 读取链表函数
List read() {
    List head, L1;
    int num;
    // 创建头节点
    L1 = (List)malloc(sizeof(struct LNode));
    L1->next = NULL;
    head = L1;
    while (1) {
        scanf("%d", &num);
        if (num == -1)
            break;
        // 创建新节点
        List p = (List)malloc(sizeof(struct LNode));
        p->data = num;
        p->next = NULL;
        // 将新节点插入链表尾部
        L1->next = p;
        L1 = L1->next;
    }
    return head;
}

// 合并两个有序链表函数
List merge(List L1, List L2) {
    List head, p1, p2, L;
    // 创建合并后链表的头节点
    L = (List)malloc(sizeof(struct LNode));
    L->next = NULL;
    head = L;
    p1 = L1->next;
    p2 = L2->next;
    while (p1 && p2) {
        if (p1->data < p2->data) {
            L->next = p1;
            L = L->next;
            p1 = p1->next;
        } else {
            L->next = p2;
            L = L->next;
            p2 = p2->next;
        }
    }
    // 处理剩余节点
    if (p1) {
        L->next = p1;
    }
    if (p2) {
        L->next = p2;
    }
    // 释放原链表的头节点
    free(L1);
    free(L2);
    return head;
}

// 打印链表函数
void printL(List L) {
    L = L->next;
    if (!L) {
        printf("NULL");
        return;
    }
    while (L->next) {
        printf("%d ", L->data);
        L = L->next;
    }
    printf("%d", L->data);
}

int main() {
    List L1, L2, L3;
    L1 = read();
    L2 = read();
    L3 = merge(L1, L2);
    printL(L3);
    // 释放合并后链表的头节点
    free(L3);
    return 0;
}    