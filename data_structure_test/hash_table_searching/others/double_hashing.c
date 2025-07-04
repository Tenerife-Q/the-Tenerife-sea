// double_hashing.c
// 使用再哈希法实现开放地址哈希表

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 13         // 质数，适合再哈希法
#define PRIME 13              // 除留余数法模数
#define RANDOM_A 0.618        // 乘法散列法常数

// 哈希表节点结构
typedef struct {
    int key;                  // 关键字
    int status;               // 0:空闲, 1:已占用
} HashNode;

// 哈希表结构
typedef struct {
    HashNode *table;          // 哈希表数组
    int size;                 // 哈希表大小
    int count;                // 当前元素数量
} OpenHashTable;

// 除留余数法（主哈希函数）
int divisionMethod(int key) {
    return key % PRIME;       // 返回key除以PRIME的余数
}

// 乘法散列法（第二哈希函数，不能为0）
int multiplicationMethod(int key) {
    double product = key * RANDOM_A;           // key乘以常数
    double fraction = product - (int)product;  // 取小数部分
    int step = (int)(TABLE_SIZE * fraction);   // 放大到表长
    return step == 0 ? 1 : step;               // 步长不能为0
}

// 初始化哈希表
OpenHashTable* initOpenHashTable(int size) {
    OpenHashTable *hashTable = (OpenHashTable*)malloc(sizeof(OpenHashTable)); // 分配结构体空间
    hashTable->table = (HashNode*)malloc(size * sizeof(HashNode));            // 分配表空间
    hashTable->size = size;                                                   // 设置表长
    hashTable->count = 0;                                                     // 初始化元素数
    for (int i = 0; i < size; i++) hashTable->table[i].status = 0;            // 所有位置设为空闲
    return hashTable;
}

// 再哈希法插入
int doubleHashingInsert(OpenHashTable *hashTable, int key, int (*hashFunc1)(int), int (*hashFunc2)(int)) {
    if (hashTable->count >= hashTable->size) {                                // 表满
        printf("哈希表已满，无法插入！\n");
        return -1;
    }
    int index = hashFunc1(key) % hashTable->size;                             // 主哈希函数
    int step = hashFunc2(key) % hashTable->size;                              // 第二哈希函数
    if (step == 0) step = 1;                                                  // 步长不能为0
    int i = 0;
    while (hashTable->table[(index + i * step) % hashTable->size].status == 1) { // 线性探测
        i++;
        if (i >= hashTable->size) {
            printf("插入失败，找不到空闲位置！\n");
            return -1;
        }
    }
    int pos = (index + i * step) % hashTable->size;                           // 计算最终插入位置
    hashTable->table[pos].key = key;                                          // 存储key
    hashTable->table[pos].status = 1;                                         // 标记为已占用
    hashTable->count++;                                                       // 元素数+1
    return pos;
}

// 再哈希法查找，输出详细过程
int doubleHashingSearch(OpenHashTable *hashTable, int key, int (*hashFunc1)(int), int (*hashFunc2)(int)) {
    int index = hashFunc1(key) % hashTable->size;                             // 主哈希函数
    int step = hashFunc2(key) % hashTable->size;                              // 第二哈希函数
    if (step == 0) step = 1;                                                  // 步长不能为0
    int i = 0;
    printf("查找%d过程：\n", key);
    while (hashTable->table[(index + i * step) % hashTable->size].status != 0) { // 只要不是空闲
        int pos = (index + i * step) % hashTable->size;                       // 计算当前位置
        printf("  探测%d: 位置%d", i, pos);
        if (hashTable->table[pos].status == 1 && hashTable->table[pos].key == key) {
            printf("，找到！\n");
            return pos;
        } else {
            printf("，未找到\n");
        }
        i++;
        if (i >= hashTable->size) break;                                      // 防止死循环
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
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);                     // 初始化表
    int keys[] = {15, 28, 19, 20, 33, 12, 17};                               // 测试数据
    int n = sizeof(keys)/sizeof(keys[0]);
    printf("插入：");
    for (int i = 0; i < n; i++) {
        int pos = doubleHashingInsert(table, keys[i], divisionMethod, multiplicationMethod); // 插入
        printf("%d(位置%d) ", keys[i], pos);
    }
    printf("\n");
    printTable(table);

    // 查找演示
    int searchKeys[] = {19, 33, 99};
    for (int i = 0; i < 3; i++) {
        int pos = doubleHashingSearch(table, searchKeys[i], divisionMethod, multiplicationMethod); // 查找
        if (pos != -1)
            printf("查找%d结果：找到，位置%d\n", searchKeys[i], pos);
        else
            printf("查找%d结果：未找到\n", searchKeys[i]);
    }

    free(table->table);                                                       // 释放内存
    free(table);
    return 0;
}