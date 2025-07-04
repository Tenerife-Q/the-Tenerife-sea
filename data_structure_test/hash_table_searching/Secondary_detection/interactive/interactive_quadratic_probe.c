// interactive_quadratic_probe.c
// 交互式二次探测法哈希表
// 支持插入、查找、删除、重置等操作

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11   // 4k+3的质数，k=2
#define PRIME 11        // 除留余数法模数

typedef struct {
    int key;
    int status; // 0:空闲, 1:已占用, 2:已删除
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
        hashTable->table[i].key = 0;
    }
    return hashTable;
}

// 重置哈希表
void resetHashTable(OpenHashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        hashTable->table[i].status = 0;
        hashTable->table[i].key = 0;
    }
    hashTable->count = 0;
    printf("哈希表已重置！\n");
}

// 二次探测插入
int quadraticProbingInsert(OpenHashTable *hashTable, int key) {
    if (hashTable->count >= hashTable->size) {
        printf("哈希表已满，无法插入！\n");
        return -1;
    }
    
    int index = divisionMethod(key) % hashTable->size;
    printf("插入 %d:\n", key);
    printf("  初始哈希位置: %d\n", index);
    
    int i = 0;
    int originalPos = index;
    
    while (hashTable->table[(index + i * i) % hashTable->size].status == 1) {
        int currentPos = (index + i * i) % hashTable->size;
        if (hashTable->table[currentPos].key == key) {
            printf("  错误：键值 %d 已存在于位置 %d\n", key, currentPos);
            return -1;
        }
        printf("  探测 %d: 位置 %d 被占用 (冲突)\n", i, currentPos);
        i++;
        if (i >= hashTable->size) {
            printf("  插入失败：找不到空闲位置！\n");
            return -1;
        }
    }
    
    int pos = (index + i * i) % hashTable->size;
    hashTable->table[pos].key = key;
    hashTable->table[pos].status = 1;
    hashTable->count++;
    
    if (i > 0) {
        printf("  经过 %d 次二次探测后插入到位置 %d\n", i, pos);
    } else {
        printf("  直接插入到位置 %d\n", pos);
    }
    
    return pos;
}

// 二次探测查找
int quadraticProbingSearch(OpenHashTable *hashTable, int key) {
    int index = divisionMethod(key) % hashTable->size;
    printf("查找 %d:\n", key);
    printf("  初始哈希位置: %d\n", index);
    
    int i = 0;
    while (i < hashTable->size) {
        int pos = (index + i * i) % hashTable->size;
        printf("  探测 %d: 位置 %d", i, pos);
        
        if (hashTable->table[pos].status == 0) {
            printf(" (空闲) - 查找失败\n");
            break;
        } else if (hashTable->table[pos].status == 1 && hashTable->table[pos].key == key) {
            printf(" (找到目标)\n");
            printf("  查找成功：在位置 %d 找到 %d\n", pos, key);
            return pos;
        } else if (hashTable->table[pos].status == 2) {
            printf(" (已删除) - 继续查找\n");
        } else {
            printf(" (其他键值: %d) - 继续查找\n", hashTable->table[pos].key);
        }
        i++;
    }
    
    printf("  查找失败：未找到 %d\n", key);
    return -1;
}

// 删除元素
int deleteKey(OpenHashTable *hashTable, int key) {
    int pos = quadraticProbingSearch(hashTable, key);
    if (pos != -1) {
        hashTable->table[pos].status = 2; // 标记为已删除
        hashTable->count--;
        printf("删除成功：键值 %d 已从位置 %d 删除\n", key, pos);
        return pos;
    } else {
        printf("删除失败：未找到键值 %d\n", key);
        return -1;
    }
}

// 打印哈希表
void printTable(OpenHashTable *hashTable) {
    printf("\n=== 当前哈希表状态 ===\n");
    printf("位置\t状态\t\t键值\t哈希值\n");
    printf("----\t--------\t----\t------\n");
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%2d]\t", i);
        if (hashTable->table[i].status == 1) {
            int hashValue = divisionMethod(hashTable->table[i].key);
            printf("已占用\t\t%d\t%d\n", hashTable->table[i].key, hashValue);
        } else if (hashTable->table[i].status == 2) {
            printf("已删除\t\t-\t-\n");
        } else {
            printf("空闲\t\t-\t-\n");
        }
    }
    printf("\n已存储元素：%d/%d，装载因子：%.2f\n\n", 
           hashTable->count, hashTable->size, (float)hashTable->count / hashTable->size);
}

// 批量插入测试数据
void insertTestData(OpenHashTable *hashTable) {
    int keys[] = {21, 32, 10, 43, 54, 65, 76, 87, 98, 99, 11, 22, 33, 44};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    printf("=== 批量插入测试数据 ===\n");
    printf("测试数据：");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
    }
    printf("\n\n");
    
    for (int i = 0; i < n; i++) {
        printf("--- 第 %d 步 ---\n", i+1);
        int pos = quadraticProbingInsert(hashTable, keys[i]);
        if (pos == -1) {
            printf("插入中断！\n");
            break;
        }
        printf("\n");
    }
}

// 显示菜单
void showMenu() {
    printf("=====================================\n");
    printf("     二次探测法哈希表操作菜单\n");
    printf("=====================================\n");
    printf("1. 插入元素\n");
    printf("2. 查找元素\n");
    printf("3. 删除元素\n");
    printf("4. 显示哈希表\n");
    printf("5. 重置哈希表\n");
    printf("6. 批量插入测试数据\n");
    printf("7. 退出程序\n");
    printf("=====================================\n");
    printf("请选择操作 (1-7): ");
}

int main() {
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);
    int choice, key, pos;
    
    printf("=== 二次探测法哈希表交互式演示 ===\n");
    printf("哈希函数：H(key) = key %% %d\n", PRIME);
    printf("哈希表大小：%d\n\n", TABLE_SIZE);
    
    while (1) {
        showMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("输入错误，请输入数字！\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }
        
        switch (choice) {
            case 1: // 插入
                printf("\n请输入要插入的键值: ");
                if (scanf("%d", &key) == 1) {
                    printf("\n--- 插入操作 ---\n");
                    pos = quadraticProbingInsert(table, key);
                    if (pos != -1) {
                        printf("插入成功！\n");
                    }
                } else {
                    printf("输入错误！\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2: // 查找
                printf("\n请输入要查找的键值: ");
                if (scanf("%d", &key) == 1) {
                    printf("\n--- 查找操作 ---\n");
                    pos = quadraticProbingSearch(table, key);
                } else {
                    printf("输入错误！\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 3: // 删除
                printf("\n请输入要删除的键值: ");
                if (scanf("%d", &key) == 1) {
                    printf("\n--- 删除操作 ---\n");
                    deleteKey(table, key);
                } else {
                    printf("输入错误！\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 4: // 显示哈希表
                printTable(table);
                break;
                
            case 5: // 重置
                printf("\n--- 重置操作 ---\n");
                resetHashTable(table);
                break;
                
            case 6: // 批量插入测试数据
                printf("\n");
                insertTestData(table);
                break;
                
            case 7: // 退出
                printf("\n程序退出，感谢使用！\n");
                free(table->table);
                free(table);
                return 0;
                
            default:
                printf("\n无效选择，请输入 1-7 之间的数字！\n");
                break;
        }
        
        printf("\n按回车键继续...");
        while (getchar() != '\n'); // 清空输入缓冲区
        getchar(); // 等待回车
        printf("\n");
    }
    
    return 0;
}
