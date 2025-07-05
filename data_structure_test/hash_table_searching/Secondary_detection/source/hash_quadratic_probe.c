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

// 二次探测插入，输出详细过程
int quadraticProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->size) {
        printf("哈希表已满，无法插入！\n");
        return -1;
    }
    int index = hashFunc(key) % hashTable->size;
    printf("插入%d: 初始位置%d", key, index);
    
    int i = 0;
    while (hashTable->table[(index + i * i) % hashTable->size].status == 1) {
        int currentPos = (index + i * i) % hashTable->size;
        printf(" -> 位置%d被占用(冲突)", currentPos);
        i++;
        if (i >= hashTable->size) {
            printf(" -> 插入失败，找不到空闲位置！\n");
            return -1;
        }
    }
    int pos = (index + i * i) % hashTable->size;
    if (i > 0) {
        printf(" -> 二次探测%d次后找到位置%d\n", i, pos);
    } else {
        printf(" -> 直接插入位置%d\n", pos);
    }
    
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
    printf("=== 当前哈希表状态 ===\n");
    printf("位置\t状态\t\t键值\t哈希值\n");
    printf("----\t----\t\t----\t------\n");
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i].status == 1) {
            int hashValue = divisionMethod(hashTable->table[i].key);
            printf("[%2d]\t已占用\t\t%d\t%d\n", i, hashTable->table[i].key, hashValue);
        } else {
            printf("[%2d]\t空闲\t\t-\t-\n", i);
        }
    }
    printf("\n");
}

int main() {
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);
    // 增加测试数据，特意选择会产生冲突的数据
    // 这些数据经过除留余数法(mod 11)会产生冲突
    int keys[] = {21, 32, 10, 43, 54, 65, 76, 87, 98, 99, 11, 22, 33, 44};
    int n = sizeof(keys)/sizeof(keys[0]);

    printf("=== 二次探测法冲突解决演示 ===\n");
    printf("哈希函数：除留余数法 H(key) = key %% %d\n\n", PRIME);
    
    printf("插入过程：\n");
    for (int i = 0; i < n; i++) {
        int hashValue = divisionMethod(keys[i]);
        printf("第%d步：", i+1);
        int pos = quadraticProbingInsert(table, keys[i], divisionMethod);
        if (pos == -1) {
            printf("插入失败！\n");
            break;
        }
    }
    
    printf("\n");
    printTable(table);

    // 查找演示 - 包含存在和不存在的数据
    printf("\n=== 查找演示 ===\n");
    int searchKeys[] = {43, 76, 99, 100, 55};
    for (int i = 0; i < 5; i++) {
        int pos = quadraticProbingSearch(table, searchKeys[i], divisionMethod);
        if (pos != -1)
            printf("查找%d结果：找到，位置%d\n\n", searchKeys[i], pos);
        else
            printf("查找%d结果：未找到\n\n", searchKeys[i]);
    }

    // 统计信息
    printf("=== 统计信息 ===\n");
    printf("哈希表大小：%d\n", table->size);
    printf("已存储元素：%d\n", table->count);
    printf("装载因子：%.2f\n", (float)table->count / table->size);

    free(table->table);
    free(table);
    return 0;
}