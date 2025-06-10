// 冲突处理方法的实现
#include <stdio.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 100

// 开放定址法的哈希表结构
typedef struct {
    int key;           // 关键字
    int status;        // 0:空闲, 1:已占用, 2:已删除
} HashNode;

typedef struct {
    HashNode *table;   // 哈希表数组
    int tableSize;     // 哈希表大小
    int count;         // 当前元素数量
} OpenHashTable;

// 链地址法的链表节点结构
typedef struct ListNode {
    int key;                   // 关键字
    struct ListNode *next;     // 指向下一个节点的指针
} ListNode;

typedef struct {
    ListNode **table;          // 哈希表数组，每个元素是一个链表头指针
    int tableSize;             // 哈希表大小
    int count;                 // 当前元素数量
} ChainHashTable;

// 1. 开放定址法 - 线性探测
int linearProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize) {
        printf("哈希表已满，无法插入！\n");
        return 0;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    int originalIndex = index;
    
    while (hashTable->table[index].status == 1) {
        index = (index + 1) % hashTable->tableSize;
        if (index == originalIndex) {
            printf("插入失败，找不到空闲位置！\n");
            return 0;  // 循环回到原点，表已满
        }
    }
    
    hashTable->table[index].key = key;
    hashTable->table[index].status = 1;
    hashTable->count++;
    return 1;
}

int linearProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int originalIndex = index;
    
    while (hashTable->table[index].status != 0) {
        if (hashTable->table[index].status == 1 && 
            hashTable->table[index].key == key) {
            return index;  // 找到
        }
        index = (index + 1) % hashTable->tableSize;
        if (index == originalIndex) {
            break;
        }
    }
    return -1;  // 未找到
}

// 2. 开放定址法 - 二次探测
int quadraticProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize) {
        printf("哈希表已满，无法插入！\n");
        return 0;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    int i = 1;
    
    while (hashTable->table[index].status == 1) {
        index = (index + i * i) % hashTable->tableSize;  // 二次探测
        i++;
        
        if (i > hashTable->tableSize / 2) {
            printf("插入失败，找不到空闲位置！\n");
            return 0;
        }
    }
    
    hashTable->table[index].key = key;
    hashTable->table[index].status = 1;
    hashTable->count++;
    return 1;
}

int quadraticProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int i = 1;
    int start = index;
    
    while (hashTable->table[index].status != 0) {
        if (hashTable->table[index].status == 1 && hashTable->table[index].key == key) {
            return index;  // 找到
        }
        
        index = (index + i * i) % hashTable->tableSize;  // 二次探测
        i++;
        
        if (i > hashTable->tableSize / 2 || index == start) {
            break;
        }
    }
    
    return -1;  // 未找到
}

// 3. 链地址法
ChainHashTable* initChainHashTable(int size) {
    ChainHashTable *hashTable = (ChainHashTable*)malloc(sizeof(ChainHashTable));
    hashTable->table = (ListNode**)malloc(size * sizeof(ListNode*));
    hashTable->tableSize = size;
    hashTable->count = 0;
    
    // 初始化所有链表头指针为NULL
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    
    return hashTable;
}

int chainInsert(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    
    // 创建新节点
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    hashTable->count++;
    
    return 1;
}

int chainSearch(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    ListNode *current = hashTable->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return 1;  // 找到
        }
        current = current->next;
    }
    
    return 0;  // 未找到
}

// 4. 再哈希法
#define MAX_REHASH_FUNCTIONS 5

int rehashFunctions[MAX_REHASH_FUNCTIONS][2] = {
    {3, 5},   // 第一个再哈希函数: (key + 3) % 5
    {7, 11},  // 第二个再哈希函数: (key + 7) % 11
    {1, 13},  // 第三个再哈希函数: (key + 1) % 13
    {5, 7},   // 第四个再哈希函数: (key + 5) % 7
    {9, 17}   // 第五个再哈希函数: (key + 9) % 17
};

int doubleHashingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize) {
        printf("哈希表已满，无法插入！\n");
        return 0;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    int i = 0;
    
    while (hashTable->table[index].status == 1) {
        // 使用再哈希函数计算步长
        int step = rehashFunctions[i % MAX_REHASH_FUNCTIONS][0];
        int mod = rehashFunctions[i % MAX_REHASH_FUNCTIONS][1];
        int hashStep = (key + step) % mod;
        
        if (hashStep == 0) hashStep = 1;  // 确保步长不为0
        
        index = (index + hashStep) % hashTable->tableSize;
        i++;
        
        if (i > hashTable->tableSize) {
            printf("插入失败，找不到空闲位置！\n");
            return 0;
        }
    }
    
    hashTable->table[index].key = key;
    hashTable->table[index].status = 1;
    hashTable->count++;
    return 1;
}

int doubleHashingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int i = 0;
    int start = index;
    
    while (hashTable->table[index].status != 0) {
        if (hashTable->table[index].status == 1 && hashTable->table[index].key == key) {
            return index;  // 找到
        }
        
        // 使用再哈希函数计算步长
        int step = rehashFunctions[i % MAX_REHASH_FUNCTIONS][0];
        int mod = rehashFunctions[i % MAX_REHASH_FUNCTIONS][1];
        int hashStep = (key + step) % mod;
        
        if (hashStep == 0) hashStep = 1;  // 确保步长不为0
        
        index = (index + hashStep) % hashTable->tableSize;
        i++;
        
        if (i > hashTable->tableSize || index == start) {
            break;
        }
    }
    
    return -1;  // 未找到
}

// 初始化开放定址法的哈希表
OpenHashTable* initOpenHashTable(int size) {
    OpenHashTable *hashTable = (OpenHashTable*)malloc(sizeof(OpenHashTable));
    hashTable->table = (HashNode*)malloc(size * sizeof(HashNode));
    hashTable->tableSize = size;
    hashTable->count = 0;
    
    // 初始化所有位置为空闲
    for (int i = 0; i < size; i++) {
        hashTable->table[i].status = 0;
    }
    
    return hashTable;
}