// interactive_chain_division.c
// 交互式链地址法哈希表实现，与线性探测和二次探测类似

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TABLE_SIZE 100
#define PRIME 13
#define LOG_FILE "hash_test_log.txt"

// 链地址法节点结构
typedef struct ListNode {
    int key;
    struct ListNode *next;
    int probeCount;    // 记录在链表中的位置，用于ASL计算
} ListNode;

// 链地址法哈希表结构
typedef struct {
    ListNode **table;   
    int tableSize;
    int count;         
    int totalSearchLength; // 总查找长度，用于计算ASL
} ChainHashTable;

// 除留余数法哈希函数
int divisionMethod(int key) {
    return key % PRIME;
}

// 初始化链地址法哈希表
ChainHashTable* initChainHashTable(int size) {
    ChainHashTable *hashTable = (ChainHashTable*)malloc(sizeof(ChainHashTable));
    hashTable->table = (ListNode**)malloc(size * sizeof(ListNode*));
    hashTable->tableSize = size;
    hashTable->count = 0;
    hashTable->totalSearchLength = 0;
    
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// 链地址法插入（带冲突可视化）
void chainInsert(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize * 3) { // 允许链表长度平均为3
        printf("❌ 哈希表已满！\n");
        return;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    
    printf("🔍 插入键值 %d：\n", key);
    printf("   初始哈希位置: %d (使用除留余数法: %d %% %d = %d)\n", index, key, PRIME, index);
    
    // 检查是否已存在
    ListNode *cur = hashTable->table[index];
    int probeCount = 1; // 从1开始计数
    while (cur) {
        if (cur->key == key) {
            printf("❌ 键值 %d 已存在于链表中！\n", key);
            return;
        }
        cur = cur->next;
        probeCount++;
    }
    
    // 创建新节点
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->probeCount = probeCount;
    
    // 如果该位置有冲突，显示冲突信息
    if (hashTable->table[index] != NULL) {
        printf("   ⚠️  位置 %d 已有节点 (冲突！)，使用链地址法添加到链表\n", index);
        printf("   ✅ 节点加入链表，链表位置: %d\n", probeCount);
    } else {
        printf("   ✅ 无冲突，直接插入位置 %d\n", index);
    }
    
    // 头插法插入新节点
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    
    hashTable->count++;
    hashTable->totalSearchLength += probeCount;
}

// 链地址法查找（带可视化）
int chainSearch(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int probeCount = 1;
    
    printf("🔍 查找键值 %d：\n", key);
    printf("   初始哈希位置: %d\n", index);
    
    if (hashTable->table[index] == NULL) {
        printf("   ❌ 位置 %d 为空链表，未找到\n", index);
        return -1;
    }
    
    ListNode *cur = hashTable->table[index];
    while (cur) {
        printf("   检查链表节点 %d: ", probeCount);
        if (cur->key == key) {
            printf("✅ 找到！(查找长度: %d)\n", probeCount);
            return probeCount;
        } else {
            printf("值为 %d，不匹配\n", cur->key);
        }
        
        cur = cur->next;
        probeCount++;
    }
    
    printf("   ❌ 遍历完链表未找到 (查找长度: %d)\n", probeCount-1);
    return -1;
}

// 链地址法删除
int chainDelete(ChainHashTable *hashTable, int key, int (*hashFunc)(int)) {
    printf("🗑️  删除键值 %d：\n", key);
    int index = hashFunc(key) % hashTable->tableSize;
    
    if (hashTable->table[index] == NULL) {
        printf("   ❌ 位置 %d 为空链表，无法删除\n", index);
        return -1;
    }
    
    // 特殊处理第一个节点
    if (hashTable->table[index]->key == key) {
        ListNode *toDelete = hashTable->table[index];
        hashTable->table[index] = toDelete->next;
        
        hashTable->totalSearchLength -= toDelete->probeCount;
        hashTable->count--;
        
        free(toDelete);
        printf("   ✅ 成功删除链表头部的键值\n");
        return 1;
    }
    
    // 处理其他节点
    ListNode *prev = hashTable->table[index];
    ListNode *cur = prev->next;
    int probeCount = 2; // 从第二个节点开始
    
    while (cur) {
        if (cur->key == key) {
            prev->next = cur->next;
            
            hashTable->totalSearchLength -= cur->probeCount;
            hashTable->count--;
            
            free(cur);
            printf("   ✅ 成功删除链表中的键值\n");
            return probeCount;
        }
        
        prev = cur;
        cur = cur->next;
        probeCount++;
    }
    
    printf("   ❌ 删除失败，键值不存在\n");
    return -1;
}

// 显示链地址法哈希表
void displayChainHashTable(ChainHashTable *hashTable) {
    printf("\n📊 当前哈希表状态：\n");
    printf("┌─────┬────────────────────┐\n");
    printf("│位置 │     链表内容       │\n");
    printf("├─────┼────────────────────┤\n");
    
    for (int i = 0; i < hashTable->tableSize; i++) {
        printf("│ %2d  │ ", i);
        
        if (hashTable->table[i] == NULL) {
            printf("空                │\n");
        } else {
            ListNode *cur = hashTable->table[i];
            int count = 0;
            while (cur) {
                if (count > 0) printf(", ");
                printf("%d", cur->key);
                cur = cur->next;
                count++;
                if (count >= 8) {
                    printf("...");
                    break;
                }
            }
            printf("%*s│\n", 17 - count*2 - (count > 8 ? 3 : 0), "");
        }
    }
    printf("└─────┴────────────────────┘\n");
    
    // 显示统计信息
    printf("\n📈 统计信息：\n");
    printf("   已存储元素数量: %d\n", hashTable->count);
    printf("   哈希表大小: %d\n", hashTable->tableSize);
    printf("   装载因子: %.2f\n", (float)hashTable->count / hashTable->tableSize);
    if (hashTable->count > 0) {
        printf("   平均查找长度 (ASL): %.2f\n", (float)hashTable->totalSearchLength / hashTable->count);
        printf("   理论ASL (1+α/2): %.2f\n", 1.0 + (float)hashTable->count / hashTable->tableSize / 2.0);
    } else {
        printf("   平均查找长度 (ASL): 0.00\n");
    }
}

// 重置哈希表
void resetHashTable(ChainHashTable *hashTable) {
    for (int i = 0; i < hashTable->tableSize; i++) {
        // 释放链表节点
        ListNode *cur = hashTable->table[i];
        while (cur) {
            ListNode *temp = cur;
            cur = cur->next;
            free(temp);
        }
        hashTable->table[i] = NULL;
    }
    hashTable->count = 0;
    hashTable->totalSearchLength = 0;
    printf("✅ 哈希表已重置！\n");
}

// 释放链地址法哈希表内存
void freeChainHashTable(ChainHashTable *hashTable) {
    resetHashTable(hashTable);
    free(hashTable->table);
    free(hashTable);
}

// 自动测试函数 - 随机冲突数据
void runRandomConflictTest(ChainHashTable *hashTable) {
    printf("🧪 执行随机冲突测试...\n\n");
    
    // 测试集1：集中冲突（同一初始位置）
    printf("=== 测试集1：集中冲突测试 ===\n");
    int concentratedKeys[] = {13, 26, 39, 52, 65}; // 都映射到位置0
    printf("插入键值集合: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", concentratedKeys[i]);
    }
    printf("\n这些键值都会映射到位置0，形成单一链表\n\n");
    
    for(int i = 0; i < 5; i++) {
        chainInsert(hashTable, concentratedKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayChainHashTable(hashTable);
    printf("\n按 Enter 键继续下一个测试...");
    getchar();
    
    // 测试集2：分散冲突（不同初始位置）
    printf("\n=== 测试集2：分散冲突测试 ===\n");
    resetHashTable(hashTable);
    
    int dispersedKeys[] = {14, 27, 41, 29, 16, 56, 69}; 
    // 14%13=1, 27%13=1, 41%13=2, 29%13=3, 16%13=3, 56%13=4, 69%13=4
    printf("插入键值集合: ");
    for(int i = 0; i < 7; i++) {
        printf("%d ", dispersedKeys[i]);
    }
    printf("\n这些键值会分散到不同位置，形成多个短链表\n\n");
    
    for(int i = 0; i < 7; i++) {
        chainInsert(hashTable, dispersedKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayChainHashTable(hashTable);
    printf("\n按 Enter 键继续下一个测试...");
    getchar();
    
    // 测试集3：混合模式（有规律的随机）
    printf("\n=== 测试集3：混合冲突测试 ===\n");
    resetHashTable(hashTable);
    
    int mixedKeys[] = {15, 28, 33, 46, 51, 64, 77, 82, 95}; 
    printf("插入键值集合: ");
    for(int i = 0; i < 9; i++) {
        printf("%d ", mixedKeys[i]);
    }
    printf("\n混合模式：既有连续冲突，也有分散冲突\n\n");
    
    for(int i = 0; i < 9; i++) {
        chainInsert(hashTable, mixedKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayChainHashTable(hashTable);
    printf("\n按 Enter 键继续查找测试...");
    getchar();
    
    // 查找效率测试
    printf("\n=== 查找效率对比测试 ===\n");
    int searchKeys[] = {15, 28, 46, 77, 95, 100}; // 包含存在和不存在的键
    
    for(int i = 0; i < 6; i++) {
        printf("\n");
        chainSearch(hashTable, searchKeys[i], divisionMethod);
    }
    
    printf("\n🎯 测试完成！观察链地址法对ASL的影响\n");
}

// 生成伪随机测试数据
void runPseudoRandomChainTest(ChainHashTable *hashTable) {
    printf("🎲 执行伪随机测试...\n\n");
    resetHashTable(hashTable);
    
    // 使用简单的线性同余生成器产生伪随机数
    int seed = 17;
    int testKeys[10];
    
    printf("生成的随机键值序列: ");
    for(int i = 0; i < 10; i++) {
        seed = (seed * 7 + 11) % 100 + 1; // 生成1-100的数
        testKeys[i] = seed;
        printf("%d ", testKeys[i]);
    }
    printf("\n\n");
    
    printf("开始插入随机数据：\n");
    for(int i = 0; i < 10; i++) {
        chainInsert(hashTable, testKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayChainHashTable(hashTable);
    
    // 随机查找测试
    printf("\n=== 随机查找测试 ===\n");
    int randomSearchKeys[] = {testKeys[2], testKeys[7], testKeys[9], 99, 50};
    
    for(int i = 0; i < 5; i++) {
        printf("\n");
        chainSearch(hashTable, randomSearchKeys[i], divisionMethod);
    }
}

// 显示菜单
void displayMenu() {
    printf("\n" "🎯 交互式链地址法哈希表操作菜单\n");
    printf("════════════════════════════════════════\n");
    printf("1. 📥 插入元素\n");
    printf("2. 🔍 查找元素\n");
    printf("3. 🗑️  删除元素\n");
    printf("4. 📊 显示哈希表\n");
    printf("5. 🔄 重置哈希表\n");
    printf("6. 🧪 随机冲突测试\n");
    printf("7. 🎲 伪随机数测试\n");
    printf("8. ❌ 退出程序\n");
    printf("════════════════════════════════════════\n");
    printf("请选择操作 (1-8): ");
}

// 获取用户输入
int getValidInput() {
    int value;
    char buffer[100];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1) {
                return value;
            }
        }
        printf("❌ 输入无效，请输入一个整数: ");
    }
}

// 主函数
int main() {
    printf("🎉 欢迎使用交互式链地址法哈希表程序！\n");
    printf("使用除留余数法 (模 %d) 和链地址法\n", PRIME);
    
    int tableSize;
    printf("\n请输入哈希表大小 (建议10-20): ");
    tableSize = getValidInput();
    
    if (tableSize <= 0 || tableSize > MAX_TABLE_SIZE) {
        printf("❌ 无效的表大小，使用默认大小 13\n");
        tableSize = 13;
    }
    
    ChainHashTable *hashTable = initChainHashTable(tableSize);
    int choice, key;
    
    while (1) {
        displayMenu();
        choice = getValidInput();
        
        printf("\n");
        
        switch (choice) {
            case 1:
                printf("请输入要插入的键值: ");
                key = getValidInput();
                chainInsert(hashTable, key, divisionMethod);
                break;
                
            case 2:
                printf("请输入要查找的键值: ");
                key = getValidInput();
                chainSearch(hashTable, key, divisionMethod);
                break;
                
            case 3:
                printf("请输入要删除的键值: ");
                key = getValidInput();
                chainDelete(hashTable, key, divisionMethod);
                break;
                
            case 4:
                displayChainHashTable(hashTable);
                break;
                
            case 5:
                resetHashTable(hashTable);
                break;
                
            case 6:
                runRandomConflictTest(hashTable);
                break;
                
            case 7:
                runPseudoRandomChainTest(hashTable);
                break;
                
            case 8:
                printf("👋 感谢使用，程序退出！\n");
                freeChainHashTable(hashTable);
                return 0;
                
            default:
                printf("❌ 无效选择，请输入 1-8 之间的数字！\n");
                break;
        }
        
        printf("\n按 Enter 键继续...");
        getchar(); // 等待用户按键
    }
    
    return 0;
}
