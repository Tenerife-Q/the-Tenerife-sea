// hash_quadratic_probe.c
// 使用二次探测法实现开放地址哈希表
// 除留余数法

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11   // 4k+3的质数，k=2
#define PRIME 11        // 除留余数法模数

typedef struct {
    int key;
    int status; // 0:空闲, 1:已占用
} HashNode;

typedef struct {
    HashNode *table;
    int size;
    int count;
} OpenHashTable;

// 除留余数法
int divisionMethod(int key) {
    return key % PRIME;
}

// 初始化哈希表
OpenHashTable* initOpenHashTable(int size) {
    OpenHashTable *hashTable = (OpenHashTable*)malloc(sizeof(OpenHashTable));
    hashTable->table = (HashNode*)malloc(size * sizeof(HashNode));
    hashTable->size = size;
    hashTable->count = 0;
    for (int i = 0; i < size; i++) {
        hashTable->table[i].status = 0;
    }
    return hashTable;
}

// 二次探测插入
int quadraticProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->size) {
        printf("哈希表已满，无法插入！\n");
        return -1;
    }
    int index = hashFunc(key) % hashTable->size;
    int i = 0;
    while (hashTable->table[(index + i * i) % hashTable->size].status == 1) {
        i++;
        if (i >= hashTable->size) {
            printf("插入失败，找不到空闲位置！\n");
            return -1;
        }
    }
    int pos = (index + i * i) % hashTable->size;
    hashTable->table[pos].key = key;
    hashTable->table[pos].status = 1;
    hashTable->count++;
    return pos;
}

// 二次探测查找，输出详细过程
int quadraticProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->size;
    int i = 0;
    printf("查找%d过程：\n", key);
    while (hashTable->table[(index + i * i) % hashTable->size].status != 0) {
        int pos = (index + i * i) % hashTable->size;
        printf("  探测%d: 位置%d", i, pos);
        if (hashTable->table[pos].status == 1 && hashTable->table[pos].key == key) {
            printf("，找到！\n");
            return pos;
        } else {
            printf("，未找到\n");
        }
        i++;
        if (i >= hashTable->size) break;
    }
    printf("  查找失败，未找到%d\n", key);
    return -1;
}

// 打印哈希表
void printTable(OpenHashTable *hashTable) {
    printf("哈希表内容：\n");
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i].status == 1)
            printf("[%2d]: %d\n", i, hashTable->table[i].key);
        else
            printf("[%2d]: (空)\n", i);
    }
}

int main() {
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);
    int keys[] = {21, 32, 43, 54, 65, 76, 87};
    int n = sizeof(keys)/sizeof(keys[0]);

    printf("插入：");
    for (int i = 0; i < n; i++) {
        int pos = quadraticProbingInsert(table, keys[i], divisionMethod);
        printf("%d(位置%d) ", keys[i], pos);
    }
    printf("\n");
    printTable(table);

    // 查找演示
    int searchKeys[] = {43, 76, 99};
    for (int i = 0; i < 3; i++) {
        int pos = quadraticProbingSearch(table, searchKeys[i], divisionMethod);
        if (pos != -1)
            printf("查找%d结果：找到，位置%d\n", searchKeys[i], pos);
        else
            printf("查找%d结果：未找到\n", searchKeys[i]);
    }

    free(table->table);
    free(table);
    return 0;
}