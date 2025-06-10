#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11   // 质数，便于除留余数法
#define PRIME 11

typedef struct ListNode {
    int key;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode **table;
    int size;
    int count;
} ChainHashTable;

// 除留余数法
int divisionMethod(int key) {
    return key % PRIME;
}

// 初始化链地址哈希表
ChainHashTable* initChainHashTable(int size) {
    ChainHashTable *hashTable = (ChainHashTable*)malloc(sizeof(ChainHashTable));
    hashTable->table = (ListNode**)malloc(size * sizeof(ListNode*));
    hashTable->size = size;
    hashTable->count = 0;
    for (int i = 0; i < size; i++) hashTable->table[i] = NULL;
    return hashTable;
}

// 插入
void chainInsert(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->size;
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    hashTable->count++;
}

// 查找，输出查找过程
int chainSearch(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->size;
    ListNode *cur = hashTable->table[index];
    int pos = 0;
    printf("查找%d过程：哈希地址=%d\n", key, index);
    while (cur) {
        printf("  比较第%d个节点，key=%d\n", pos+1, cur->key);
        if (cur->key == key) return pos+1; // 返回查找长度
        cur = cur->next;
        pos++;
    }
    return 0; // 未找到
}

// 打印哈希表
void printTable(ChainHashTable *hashTable) {
    printf("哈希表内容：\n");
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%2d]:", i);
        ListNode *cur = hashTable->table[i];
        while (cur) {
            printf(" %d", cur->key);
            cur = cur->next;
        }
        printf("\n");
    }
}

int main() {
    ChainHashTable *table = initChainHashTable(TABLE_SIZE);
    int keys[] = {21, 32, 43, 54, 65, 76, 87};
    int n = sizeof(keys)/sizeof(keys[0]);
    printf("插入：");
    for (int i = 0; i < n; i++) {
        chainInsert(table, keys[i], divisionMethod);
        printf("%d ", keys[i]);
    }
    printf("\n");
    printTable(table);

    // 查找演示
    int searchKeys[] = {43, 76, 99};
    for (int i = 0; i < 3; i++) {
        int asl = chainSearch(table, searchKeys[i], divisionMethod);
        if (asl)
            printf("查找%d结果：找到，查找长度%d\n", searchKeys[i], asl);
        else
            printf("查找%d结果：未找到\n", searchKeys[i]);
    }

    // 计算装填因子
    double alpha = (double)table->count / table->size;
    printf("装填因子α = %.3f\n", alpha);

    // 计算ASL（成功查找平均查找长度）
    int total = 0, found = 0;
    for (int i = 0; i < n; i++) {
        int asl = chainSearch(table, keys[i], divisionMethod);
        if (asl) { total += asl; found++; }
    }
    printf("成功查找ASL = %.3f\n", found ? (double)total/found : 0);

    // 释放内存
    for (int i = 0; i < table->size; i++) {
        ListNode *cur = table->table[i];
        while (cur) {
            ListNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(table->table);
    free(table);
    return 0;
}