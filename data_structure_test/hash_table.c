#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TABLE_SIZE 100
#define PRIME 13      // 用于除留余数法的素数
#define RANDOM_A 0.618 // 用于乘法散列法的常数

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

// 六种哈希函数构建方法
// 1. 直接定址法
int directAddressing(int key) {
    return key;  // 简单示例，实际应用中可能需要线性变换
}

// 2. 数字分析法 (示例: 取身份证号码的后四位)
int digitAnalysis(int key) {
    return key % 10000;  // 假设key是身份证号码，取后四位
}

// 3. 平方取中法
int midSquare(int key) {
    long long square = (long long)key * key;
    // 假设哈希表大小是100，取平方结果中间两位
    int digits = 0;
    long long temp = square;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    int mid = digits / 2;
    int result = 0;
    temp = square;
    for (int i = 0; i < mid - 1; i++) {
        temp /= 10;
    }
    result = temp % 100;  // 取中间两位
    return result;
}

// 4. 折叠法 (示例: 移位叠加)
int folding(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 1000;  // 每次取三位
        key /= 1000;
    }
    return sum;
}

// 5. 除留余数法
int divisionMethod(int key) {
    return key % PRIME;
}

// 6. 乘法散列法
int multiplicationMethod(int key) {
    double product = key * RANDOM_A;
    double fraction = product - (int)product;
    return (int)(MAX_TABLE_SIZE * fraction);
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
        hashTable->table[i].key = 0;
    }
    
    return hashTable;
}

// 开放定址法的插入操作 (线性探测)
int linearProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize) {
        printf("哈希表已满，无法插入！\n");
        return 0;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    int start = index;
    
    do {
        if (hashTable->table[index].status != 1) {
            hashTable->table[index].key = key;
            hashTable->table[index].status = 1;
            hashTable->count++;
            return 1;
        }
        index = (index + 1) % hashTable->tableSize;
    } while (index != start);
    
    printf("插入失败，找不到空闲位置！\n");
    return 0;
}

// 开放定址法的查找操作 (线性探测)
int linearProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int start = index;
    
    do {
        if (hashTable->table[index].status == 0) {
            return -1;  // 未找到
        }
        if (hashTable->table[index].status == 1 && hashTable->table[index].key == key) {
            return index;  // 找到
        }
        index = (index + 1) % hashTable->tableSize;
    } while (index != start);
    
    return -1;  // 未找到
}

// 初始化链地址法的哈希表
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

// 链地址法的插入操作
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

// 链地址法的查找操作
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

// 测试代码
int main() {
    // 测试开放定址法 (线性探测)
    OpenHashTable *openTable = initOpenHashTable(10);
    
    printf("开放定址法插入测试：\n");
    linearProbingInsert(openTable, 12, divisionMethod);
    linearProbingInsert(openTable, 22, divisionMethod);
    linearProbingInsert(openTable, 32, divisionMethod);
    
    printf("查找22：%d\n", linearProbingSearch(openTable, 22, divisionMethod));
    printf("查找42：%d\n", linearProbingSearch(openTable, 42, divisionMethod));
    
    // 测试链地址法
    ChainHashTable *chainTable = initChainHashTable(10);
    
    printf("\n链地址法插入测试：\n");
    chainInsert(chainTable, 12, divisionMethod);
    chainInsert(chainTable, 22, divisionMethod);
    chainInsert(chainTable, 32, divisionMethod);
    
    printf("查找22：%d\n", chainSearch(chainTable, 22, divisionMethod));
    printf("查找42：%d\n", chainSearch(chainTable, 42, divisionMethod));
    
    return 0;
}    