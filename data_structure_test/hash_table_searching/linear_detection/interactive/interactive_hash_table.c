#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLE_SIZE 100
#define PRIME 13

// 开放定址法的哈希表结构
typedef struct {
    int key;           
    int status;        // 0:空闲, 1:已占用, 2:已删除
    int probeCount;    // 探测次数，用于计算ASL
} HashNode;

typedef struct {
    HashNode *table;   
    int tableSize;     
    int count;         
    int totalSearchLength; // 总查找长度，用于计算ASL
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
    hashTable->totalSearchLength = 0;
    
    for (int i = 0; i < size; i++) {
        hashTable->table[i].status = 0;
        hashTable->table[i].probeCount = 0;
    }
    return hashTable;
}

// 线性探测插入（带冲突检测）
int linearProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->tableSize) {
        printf("❌ 哈希表已满！\n");
        return -1;
    }
    
    int index = hashFunc(key) % hashTable->tableSize;
    int originalIndex = index;
    int probeCount = 1;
    
    printf("🔍 插入键值 %d：\n", key);
    printf("   初始哈希位置: %d (使用除留余数法: %d %% %d = %d)\n", index, key, PRIME, index);
    
    // 检查是否已存在
    int tempIndex = index;
    while (hashTable->table[tempIndex].status != 0) {
        if (hashTable->table[tempIndex].status == 1 && 
            hashTable->table[tempIndex].key == key) {
            printf("❌ 键值 %d 已存在！\n", key);
            return -1;
        }
        tempIndex = (tempIndex + 1) % hashTable->tableSize;
        if (tempIndex == originalIndex) break;
    }
    
    // 寻找插入位置
    while (hashTable->table[index].status == 1) {
        printf("   ⚠️  位置 %d 已被占用 (冲突！)，线性探测到下一位置\n", index);
        index = (index + 1) % hashTable->tableSize;
        probeCount++;
        if (index == originalIndex) {
            printf("❌ 无法插入，没有可用位置！\n");
            return -1;
        }
    }
    
    hashTable->table[index].key = key;
    hashTable->table[index].status = 1;
    hashTable->table[index].probeCount = probeCount;
    hashTable->count++;
    hashTable->totalSearchLength += probeCount;
    
    printf("   ✅ 成功插入到位置 %d (探测了 %d 次)\n", index, probeCount);
    return index;
}

// 线性探测查找（带效率统计）
int linearProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->tableSize;
    int originalIndex = index;
    int probeCount = 1;
    
    printf("🔍 查找键值 %d：\n", key);
    printf("   初始哈希位置: %d\n", index);
    
    while (hashTable->table[index].status != 0) {
        printf("   检查位置 %d", index);
        if (hashTable->table[index].status == 1 && 
            hashTable->table[index].key == key) {
            printf(" ✅ 找到！(探测了 %d 次)\n", probeCount);
            return index;
        } else if (hashTable->table[index].status == 1) {
            printf(" (值为 %d，不匹配)\n", hashTable->table[index].key);
        } else {
            printf(" (已删除标记)\n");
        }
        
        index = (index + 1) % hashTable->tableSize;
        probeCount++;
        if (index == originalIndex) break;
    }
    
    printf("   ❌ 未找到 (探测了 %d 次)\n", probeCount);
    return -1;
}

// 线性探测删除
int linearProbingDelete(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    printf("🗑️  删除键值 %d：\n", key);
    int index = linearProbingSearch(hashTable, key, hashFunc);
    if (index != -1) {
        hashTable->table[index].status = 2; // 标记为已删除
        hashTable->totalSearchLength -= hashTable->table[index].probeCount;
        hashTable->table[index].probeCount = 0;
        hashTable->count--;
        printf("   ✅ 成功删除位置 %d 的键值\n", index);
        return index;
    }
    printf("   ❌ 删除失败，键值不存在\n");
    return -1;
}

// 显示开放定址法哈希表
void displayOpenHashTable(OpenHashTable *hashTable) {
    printf("\n📊 当前哈希表状态：\n");
    printf("┌─────┬──────────┬────────┬──────────┐\n");
    printf("│位置 │   状态   │  键值  │ 探测次数 │\n");
    printf("├─────┼──────────┼────────┼──────────┤\n");
    
    for (int i = 0; i < hashTable->tableSize; i++) {
        printf("│ %2d  │", i);
        if (hashTable->table[i].status == 1) {
            printf("   已占用  │  %4d  │    %2d    │\n", 
                   hashTable->table[i].key, hashTable->table[i].probeCount);
        } else if (hashTable->table[i].status == 2) {
            printf("   已删除  │   --   │    --    │\n");
        } else {
            printf("    空闲   │   --   │    --    │\n");
        }
    }
    printf("└─────┴──────────┴────────┴──────────┘\n");
    
    // 显示统计信息
    printf("\n📈 统计信息：\n");
    printf("   已存储元素数量: %d\n", hashTable->count);
    printf("   哈希表大小: %d\n", hashTable->tableSize);
    printf("   装载因子: %.2f\n", (float)hashTable->count / hashTable->tableSize);
    if (hashTable->count > 0) {
        printf("   平均查找长度 (ASL): %.2f\n", (float)hashTable->totalSearchLength / hashTable->count);
    } else {
        printf("   平均查找长度 (ASL): 0.00\n");
    }
}

// 重置哈希表
void resetHashTable(OpenHashTable *hashTable) {
    for (int i = 0; i < hashTable->tableSize; i++) {
        hashTable->table[i].status = 0;
        hashTable->table[i].probeCount = 0;
    }
    hashTable->count = 0;
    hashTable->totalSearchLength = 0;
    printf("✅ 哈希表已重置！\n");
}

// 释放开放定址法哈希表内存
void freeOpenHashTable(OpenHashTable *hashTable) {
    free(hashTable->table);
    free(hashTable);
}

// 自动测试函数 - 随机冲突数据
void runRandomConflictTest(OpenHashTable *hashTable) {
    printf("🧪 执行随机冲突测试...\n\n");
    
    // 测试集1：集中冲突（同一初始位置）
    printf("=== 测试集1：集中冲突测试 ===\n");
    int concentratedKeys[] = {13, 26, 39, 52, 65}; // 都映射到位置0
    printf("插入键值集合: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", concentratedKeys[i]);
    }
    printf("\n这些键值都会映射到位置0，形成连续冲突链\n\n");
    
    for(int i = 0; i < 5; i++) {
        linearProbingInsert(hashTable, concentratedKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayOpenHashTable(hashTable);
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
    printf("\n这些键值会分散到不同位置，形成多个小冲突链\n\n");
    
    for(int i = 0; i < 7; i++) {
        linearProbingInsert(hashTable, dispersedKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayOpenHashTable(hashTable);
    printf("\n按 Enter 键继续下一个测试...");
    getchar();
    
    // 测试集3：混合模式（有规律的随机）
    printf("\n=== 测试集3：混合冲突测试 ===\n");
    resetHashTable(hashTable);
    
    int mixedKeys[] = {15, 28, 33, 46, 51, 64, 77, 82, 95}; 
    // 产生不同程度的冲突，有些连续，有些分散
    printf("插入键值集合: ");
    for(int i = 0; i < 9; i++) {
        printf("%d ", mixedKeys[i]);
    }
    printf("\n混合模式：既有连续冲突，也有分散冲突\n\n");
    
    for(int i = 0; i < 9; i++) {
        linearProbingInsert(hashTable, mixedKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayOpenHashTable(hashTable);
    printf("\n按 Enter 键继续查找测试...");
    getchar();
    
    // 查找效率测试
    printf("\n=== 查找效率对比测试 ===\n");
    int searchKeys[] = {15, 28, 46, 77, 95, 100}; // 包含存在和不存在的键
    
    for(int i = 0; i < 6; i++) {
        printf("\n");
        linearProbingSearch(hashTable, searchKeys[i], divisionMethod);
    }
    
    printf("\n🎯 测试完成！观察不同冲突模式对ASL的影响\n");
}

// 生成伪随机测试数据
void runPseudoRandomTest(OpenHashTable *hashTable) {
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
        linearProbingInsert(hashTable, testKeys[i], divisionMethod);
        printf("\n");
    }
    
    displayOpenHashTable(hashTable);
    
    // 随机查找测试
    printf("\n=== 随机查找测试 ===\n");
    int randomSearchKeys[] = {testKeys[2], testKeys[7], testKeys[9], 99, 50};
    
    for(int i = 0; i < 5; i++) {
        printf("\n");
        linearProbingSearch(hashTable, randomSearchKeys[i], divisionMethod);
    }
}

// 显示菜单
void displayMenu() {
    printf("\n" "🎯 交互式哈希表操作菜单\n");
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
    printf("🎉 欢迎使用交互式哈希表程序！\n");
    printf("使用除留余数法 (模 %d) 和线性探测法\n", PRIME);
    
    int tableSize;
    printf("\n请输入哈希表大小 (建议10-20): ");
    tableSize = getValidInput();
    
    if (tableSize <= 0 || tableSize > MAX_TABLE_SIZE) {
        printf("❌ 无效的表大小，使用默认大小 13\n");
        tableSize = 13;
    }
    
    OpenHashTable *hashTable = initOpenHashTable(tableSize);
    int choice, key;
    
    while (1) {
        displayMenu();
        choice = getValidInput();
        
        printf("\n");
        
        switch (choice) {
            case 1:
                printf("请输入要插入的键值: ");
                key = getValidInput();
                linearProbingInsert(hashTable, key, divisionMethod);
                break;
                
            case 2:
                printf("请输入要查找的键值: ");
                key = getValidInput();
                linearProbingSearch(hashTable, key, divisionMethod);
                break;
                
            case 3:
                printf("请输入要删除的键值: ");
                key = getValidInput();
                linearProbingDelete(hashTable, key, divisionMethod);
                break;
                
            case 4:
                displayOpenHashTable(hashTable);
                break;
                
            case 5:
                resetHashTable(hashTable);
                break;
                
            case 6:
                runRandomConflictTest(hashTable);
                break;
                
            case 7:
                runPseudoRandomTest(hashTable);
                break;
                
            case 8:
                printf("👋 感谢使用，程序退出！\n");
                freeOpenHashTable(hashTable);
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
