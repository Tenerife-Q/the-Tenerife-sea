// quick_demo.c
// 快速演示交互式哈希表的功能

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11
#define PRIME 11

typedef struct {
    int key;
    int status; // 0:empty, 1:occupied, 2:deleted
} HashNode;

typedef struct {
    HashNode *table;
    int size;
    int count;
} OpenHashTable;

int divisionMethod(int key) {
    return key % PRIME;
}

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

int quadraticProbingInsert(OpenHashTable *hashTable, int key) {
    if (hashTable->count >= hashTable->size) {
        printf("Hash table is full!\n");
        return -1;
    }
    
    int index = divisionMethod(key) % hashTable->size;
    printf("Insert %d: initial position %d", key, index);
    
    int i = 0;
    while (hashTable->table[(index + i * i) % hashTable->size].status == 1) {
        int currentPos = (index + i * i) % hashTable->size;
        printf(" -> pos %d occupied", currentPos);
        i++;
        if (i >= hashTable->size) {
            printf(" -> failed!\n");
            return -1;
        }
    }
    
    int pos = (index + i * i) % hashTable->size;
    hashTable->table[pos].key = key;
    hashTable->table[pos].status = 1;
    hashTable->count++;
    
    if (i > 0) {
        printf(" -> inserted at pos %d after %d probes\n", pos, i);
    } else {
        printf(" -> inserted directly at pos %d\n", pos);
    }
    
    return pos;
}

int quadraticProbingSearch(OpenHashTable *hashTable, int key) {
    int index = divisionMethod(key) % hashTable->size;
    printf("Search %d: start at pos %d", key, index);
    
    int i = 0;
    while (i < hashTable->size) {
        int pos = (index + i * i) % hashTable->size;
        if (hashTable->table[pos].status == 0) {
            printf(" -> pos %d empty, not found\n", pos);
            return -1;
        } else if (hashTable->table[pos].status == 1 && hashTable->table[pos].key == key) {
            printf(" -> found at pos %d!\n", pos);
            return pos;
        }
        printf(" -> pos %d has %d", pos, hashTable->table[pos].key);
        i++;
    }
    printf(" -> not found\n");
    return -1;
}

void printTable(OpenHashTable *hashTable) {
    printf("\n=== Hash Table Status ===\n");
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%2d] ", i);
        if (hashTable->table[i].status == 1) {
            printf("key: %d (hash: %d)\n", hashTable->table[i].key, divisionMethod(hashTable->table[i].key));
        } else if (hashTable->table[i].status == 2) {
            printf("deleted\n");
        } else {
            printf("empty\n");
        }
    }
    printf("Load factor: %.2f\n\n", (float)hashTable->count / hashTable->size);
}

int main() {
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);
    
    printf("=== Interactive Hash Table Demo ===\n");
    printf("Hash Function: H(key) = key %% %d\n\n", PRIME);
    
    // 演示批量插入
    printf("=== Batch Insert Demo ===\n");
    int keys[] = {21, 32, 10, 43, 54, 65};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        quadraticProbingInsert(table, keys[i]);
    }
    
    printTable(table);
    
    // 演示查找
    printf("=== Search Demo ===\n");
    int searchKeys[] = {43, 76, 32};
    for (int i = 0; i < 3; i++) {
        quadraticProbingSearch(table, searchKeys[i]);
    }
    
    printf("\n=== Program Features ===\n");
    printf("The full interactive version supports:\n");
    printf("1. Manual insert with detailed collision resolution\n");
    printf("2. Interactive search with step-by-step probing\n");
    printf("3. Delete operation with lazy deletion\n");
    printf("4. Real-time table display\n");
    printf("5. Table reset functionality\n");
    printf("6. Batch insert of predefined test data\n");
    printf("7. Menu-driven interface\n");
    
    printf("\nTo run the full interactive version:\n");
    printf("Execute: .\\interactive_quadratic_probe_en.exe\n");
    
    free(table->table);
    free(table);
    return 0;
}
