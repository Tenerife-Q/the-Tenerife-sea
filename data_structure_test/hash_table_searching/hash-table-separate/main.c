// 测试代码
#include <stdio.h>
#include <stdlib.h>

// 包含上面两个文件的函数声明
extern int directAddressing(int key);
extern int digitAnalysis(int key);
extern int midSquare(int key);
extern int folding(int key);
extern int divisionMethod(int key);
extern int multiplicationMethod(int key);

extern OpenHashTable* initOpenHashTable(int size);
extern ChainHashTable* initChainHashTable(int size);
extern int linearProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int));
extern int linearProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int));
extern int quadraticProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int));
extern int quadraticProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int));
extern int chainInsert(ChainHashTable *hashTable, int key, int (*hashFunc)(int));
extern int chainSearch(ChainHashTable *hashTable, int key, int (*hashFunc)(int));
extern int doubleHashingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int));
extern int doubleHashingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int));

int main() {
    // 测试开放定址法 (线性探测)
    OpenHashTable *linearTable = initOpenHashTable(10);
    
    printf("开放定址法(线性探测)测试：\n");
    printf("插入: 12, 22, 32\n");
    linearProbingInsert(linearTable, 12, divisionMethod);
    linearProbingInsert(linearTable, 22, divisionMethod);
    linearProbingInsert(linearTable, 32, divisionMethod);
    
    printf("查找22：位置 = %d\n", linearProbingSearch(linearTable, 22, divisionMethod));
    printf("查找42：位置 = %d\n", linearProbingSearch(linearTable, 42, divisionMethod));
    
    // 测试开放定址法 (二次探测)
    OpenHashTable *quadraticTable = initOpenHashTable(10);
    
    printf("\n开放定址法(二次探测)测试：\n");
    printf("插入: 12, 22, 32\n");
    quadraticProbingInsert(quadraticTable, 12, divisionMethod);
    quadraticProbingInsert(quadraticTable, 22, divisionMethod);
    quadraticProbingInsert(quadraticTable, 32, divisionMethod);
    
    printf("查找22：位置 = %d\n", quadraticProbingSearch(quadraticTable, 22, divisionMethod));
    printf("查找42：位置 = %d\n", quadraticProbingSearch(quadraticTable, 42, divisionMethod));
    
    // 测试链地址法
    ChainHashTable *chainTable = initChainHashTable(10);
    
    printf("\n链地址法测试：\n");
    printf("插入: 12, 22, 32\n");
    chainInsert(chainTable, 12, divisionMethod);
    chainInsert(chainTable, 22, divisionMethod);
    chainInsert(chainTable, 32, divisionMethod);
    
    printf("查找22：%s\n", chainSearch(chainTable, 22, divisionMethod) ? "找到" : "未找到");
    printf("查找42：%s\n", chainSearch(chainTable, 42, divisionMethod) ? "找到" : "未找到");
    
    // 释放内存
    free(linearTable->table);
    free(linearTable);
    free(quadraticTable->table);
    free(quadraticTable);
    
    // 释放链地址法的内存
    for(int i = 0; i < chainTable->tableSize; i++) {
        ListNode *current = chainTable->table[i];
        while(current != NULL) {
            ListNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(chainTable->table);
    free(chainTable);
    
    return 0;
}