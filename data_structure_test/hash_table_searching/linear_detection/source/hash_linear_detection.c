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
    printf("┌─────┬──────────┬────────────────┐\n");
    printf("│位置 │   状态   │      说明      │\n");
    printf("├─────┼──────────┼────────────────┤\n");
    
    int totalProbeCount = 0;
    int occupiedCount = 0;
    
    for (int i = 0; i < hashTable->tableSize; i++) {
        printf("│ %2d  │", i);
        if (hashTable->table[i].status == 1) {
            int originalPos = divisionMethod(hashTable->table[i].key) % hashTable->tableSize;
            int probeCount = i >= originalPos ? i - originalPos + 1 : i + hashTable->tableSize - originalPos + 1;
            totalProbeCount += probeCount;
            occupiedCount++;
            printf("   已占用  │ 键值:%2d 探测:%d次 │\n", hashTable->table[i].key, probeCount);
        } else if (hashTable->table[i].status == 2) {
            printf("   已删除  │   删除标记     │\n");
        } else {
            printf("    空闲   │     空位       │\n");
        }
    }
    printf("└─────┴──────────┴────────────────┘\n");
    
    // 性能统计
    printf("\n📊 性能统计信息：\n");
    printf("   总元素数量: %d\n", occupiedCount);
    printf("   表大小: %d\n", hashTable->tableSize);
    printf("   装载因子: %.2f\n", (float)occupiedCount / hashTable->tableSize);
    if (occupiedCount > 0) {
        float asl = (float)totalProbeCount / occupiedCount;
        printf("   平均查找长度(ASL): %.2f\n", asl);
        printf("   理论ASL (1+α/2): %.2f\n", 1.0 + (float)occupiedCount / hashTable->tableSize / 2.0);
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
    
    // 插入测试数据（随机分散冲突模式）
    int testKeys[] = {17, 30, 22, 48, 35, 61, 44, 19, 57}; 
    /* 哈希映射分析 (key % 13):
     * 17 % 13 = 4  → 位置4
     * 30 % 13 = 4  → 位置4冲突，探测到位置5
     * 22 % 13 = 9  → 位置9
     * 48 % 13 = 9  → 位置9冲突，探测到位置0
     * 35 % 13 = 9  → 位置9,0冲突，探测到位置1
     * 61 % 13 = 9  → 位置9,0,1冲突，探测到位置2
     * 44 % 13 = 5  → 位置5冲突，探测到位置6
     * 19 % 13 = 6  → 位置6冲突，探测到位置7
     * 57 % 13 = 5  → 位置5,6,7冲突，探测到位置8
     * 形成分散的冲突链：位置4-5, 位置9-0-1-2, 位置5-6-7-8
     */
    int n = sizeof(testKeys) / sizeof(testKeys[0]);
    
    printf("开放定址法插入测试（随机分散冲突）：\n");
    printf("测试数据: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", testKeys[i]);
    }
    printf("\n\n");
    
    for(int i = 0; i < n; i++) {
        int hashPos = divisionMethod(testKeys[i]) % openTable->tableSize;
        printf("插入 %d (初始哈希位置: %d) ", testKeys[i], hashPos);
        int pos = linearProbingInsert(openTable, testKeys[i], divisionMethod);
        if(pos != hashPos) {
            printf("→ 实际位置: %d (探测了 %d 次)\n", pos, pos >= hashPos ? pos - hashPos + 1 : pos + openTable->tableSize - hashPos + 1);
        } else {
            printf("→ 无冲突\n");
        }
    }
    
    // 显示开放定址法哈希表
    displayOpenHashTable(openTable);
    
    // 查找测试（包含随机分布的键值）
    printf("\n开放定址法查找测试：\n");
    int searchKeys[] = {30, 48, 19, 61, 75}; // 前4个存在，最后1个不存在
    for(int i = 0; i < 5; i++) {
        int hashPos = divisionMethod(searchKeys[i]) % openTable->tableSize;
        printf("查找 %d (初始哈希位置: %d) ", searchKeys[i], hashPos);
        int pos = linearProbingSearch(openTable, searchKeys[i], divisionMethod);
        if(pos != -1) {
            int probeCount = pos >= hashPos ? pos - hashPos + 1 : pos + openTable->tableSize - hashPos + 1;
            printf("→ 找到，位置: %d (探测了 %d 次)\n", pos, probeCount);
        } else {
            printf("→ 未找到\n");
        }
    }
    
    // 删除测试（选择分散位置的元素）
    printf("\n开放定址法删除测试：\n");
    int deleteKey = 61; // 选择一个在冲突链中间的元素
    printf("删除键值 %d ", deleteKey);
    int deletedPos = linearProbingDelete(openTable, deleteKey, divisionMethod);
    if(deletedPos != -1) {
        printf("→ 成功删除，位置: %d\n", deletedPos);
    } else {
        printf("→ 未找到，无法删除\n");
    }
    
    // 再删除一个元素测试连锁效应
    printf("删除键值 %d ", 17);
    deletedPos = linearProbingDelete(openTable, 17, divisionMethod);
    if(deletedPos != -1) {
        printf("→ 成功删除，位置: %d\n", deletedPos);
    } else {
        printf("→ 未找到，无法删除\n");
    }
    
    // 显示删除后的开放定址法哈希表
    displayOpenHashTable(openTable);
    
    // 释放开放定址法哈希表内存
    freeOpenHashTable(openTable);
    
    return 0;
}
