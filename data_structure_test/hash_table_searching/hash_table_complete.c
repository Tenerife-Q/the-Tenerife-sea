#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TABLE_SIZE 100
#define PRIME 13
#define RANDOM_A 0.618

// 开放定址法的哈希表结构
typedef struct {
    int key;           
    int status;        // 0:空闲, 1:已占用, 2:已删除
} HashNode;

typedef struct {
    HashNode *table;   
    int tableSize;     
    int count;         
} OpenHashTable;

// 链地址法的链表节点结构
typedef struct ListNode {
    int key;                   
    struct ListNode *next;     
} ListNode;

typedef struct {
    ListNode **table;          
    int tableSize;             
    int count;                 
} ChainHashTable;

// 哈希函数实现
int directAddressing(int key) {
    return key;
}

int digitAnalysis(int key) {
    return key % 10000;
}

int midSquare(int key) {
    long long square = (long long)key * key;
    return (square / 100) % 100;
}

int folding(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 1000;
        key /= 1000;
    }
    return sum;
}

int divisionMethod(int key) {
    return key % PRIME;
}

int multiplicationMethod(int key) {
    double product = key * RANDOM_A;
    return (int)(MAX_TABLE_SIZE * (product - (int)product));
}

// 初始化函数
OpenHashTable* initOpenHashTable(int size) {
    OpenHashTable *hashTable = (OpenHashTable*)malloc(sizeof(OpenHashTable));
    hashTable->table = (HashNode*)malloc(size * sizeof(HashNode));
    hashTable->tableSize = size;
    hashTable->count = 0;
    
    for (int i = 0; i < size; i++) {
        hashTable->table[i].status = 0;
    }
    return hashTable;
}

ChainHashTable* initChainHashTable(int size) {
    ChainHashTable *hashTable = (ChainHashTable*)malloc(sizeof(ChainHashTable));
    hashTable->table = (ListNode**)malloc(size * sizeof(ListNode*));
    hashTable->tableSize = size;
    hashTable->count = 0;
    
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// 冲突处理方法实现
int linearProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize) {
        printf("哈希表已满！\n");
        return -1;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    int originalIndex = index;
    
    while (hashTable->table[index].status == 1) {
        index = (index + 1) % hashTable->tableSize;
        if (index == originalIndex) {
            printf("无法插入，没有可用位置！\n");
            return -1;
        }
    }
    
    hashTable->table[index].key = key;
    hashTable->table[index].status = 1;
    hashTable->count++;
    return index;
}

int linearProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int originalIndex = index;
    
    while (hashTable->table[index].status != 0) {
        if (hashTable->table[index].status == 1 && 
            hashTable->table[index].key == key) {
            return index;
        }
        index = (index + 1) % hashTable->tableSize;
        if (index == originalIndex) break;
    }
    return -1;
}

// 主函数 - 测试示例
int main() {
    printf("=== 哈希表测试程序 ===\n\n");
    
    // 创建并测试开放定址法哈希表
    OpenHashTable *table = initOpenHashTable(10);
    
    // 插入测试数据
    int testKeys[] = {15, 25, 35, 45, 55};
    printf("插入测试：\n");
    for(int i = 0; i < 5; i++) {
        int pos = linearProbingInsert(table, testKeys[i], divisionMethod);
        printf("插入 %d 到位置 %d\n", testKeys[i], pos);
    }
    
    // 查找测试
    printf("\n查找测试：\n");
    int searchKeys[] = {25, 35, 99};
    for(int i = 0; i < 3; i++) {
        int pos = linearProbingSearch(table, searchKeys[i], divisionMethod);
        if(pos != -1) {
            printf("找到 %d，位置: %d\n", searchKeys[i], pos);
        } else {
            printf("未找到 %d\n", searchKeys[i]);
        }
    }
    
    // 释放内存
    free(table->table);
    free(table);
    
    return 0;
}