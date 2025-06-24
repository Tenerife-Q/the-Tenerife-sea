#include <stdio.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 100
#define PRIME 13

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

// 除留余数法哈希函数
int divisionMethod(int key) {
    return key % PRIME;
}

// 初始化开放定址法哈希表
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

// 线性探测插入
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

// 线性探测查找
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

// 线性探测删除
int linearProbingDelete(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = linearProbingSearch(hashTable, key, hashFunc);
    if (index != -1) {
        hashTable->table[index].status = 2; // 标记为已删除
        hashTable->count--;
        return index;
    }
    return -1;
}

// 显示开放定址法哈希表
void displayOpenHashTable(OpenHashTable *hashTable) {
    printf("\n开放定址法哈希表内容：\n");
    for (int i = 0; i < hashTable->tableSize; i++) {
        if (hashTable->table[i].status == 1) {
            printf("位置 %d: %d\n", i, hashTable->table[i].key);
        } else if (hashTable->table[i].status == 2) {
            printf("位置 %d: 删除标记\n", i);
        } else {
            printf("位置 %d: 空闲\n", i);
        }
    }
}

// 释放开放定址法哈希表内存
void freeOpenHashTable(OpenHashTable *hashTable) {
    free(hashTable->table);
    free(hashTable);
}

// 主函数 - 测试示例
int main() {
    printf("=== 开放定址法哈希表测试程序 ===\n\n");
    
    // 创建并测试开放定址法哈希表
    OpenHashTable *openTable = initOpenHashTable(10);
    
    // 插入测试数据
    int testKeys[] = {15, 25, 35, 45, 55};
    printf("开放定址法插入测试：\n");
    for(int i = 0; i < 5; i++) {
        int pos = linearProbingInsert(openTable, testKeys[i], divisionMethod);
        printf("插入 %d 到位置 %d\n", testKeys[i], pos);
    }
    
    // 显示开放定址法哈希表
    displayOpenHashTable(openTable);
    
    // 查找测试
    printf("\n开放定址法查找测试：\n");
    int searchKeys[] = {25, 35, 99};
    for(int i = 0; i < 3; i++) {
        int pos = linearProbingSearch(openTable, searchKeys[i], divisionMethod);
        if(pos != -1) {
            printf("找到 %d，位置: %d\n", searchKeys[i], pos);
        } else {
            printf("未找到 %d\n", searchKeys[i]);
        }
    }
    
    // 删除测试
    printf("\n开放定址法删除测试：\n");
    int deleteKey = 35;
    int deletedPos = linearProbingDelete(openTable, deleteKey, divisionMethod);
    if(deletedPos != -1) {
        printf("删除 %d，位置: %d\n", deleteKey, deletedPos);
    } else {
        printf("未找到 %d，无法删除\n", deleteKey);
    }
    
    // 显示删除后的开放定址法哈希表
    displayOpenHashTable(openTable);
    
    // 释放开放定址法哈希表内存
    freeOpenHashTable(openTable);
    
    return 0;
}
    