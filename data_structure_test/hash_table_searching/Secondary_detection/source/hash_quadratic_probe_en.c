// hash_quadratic_probe_en.c
// Quadratic Probing Hash Table Implementation
// Division Method for Hash Function

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11   // Prime number 4k+3, k=2
#define PRIME 11        // Modulus for division method

typedef struct {
    int key;
    int status; // 0:empty, 1:occupied
} HashNode;

typedef struct {
    HashNode *table;
    int size;
    int count;
} OpenHashTable;

// Division method hash function
int divisionMethod(int key) {
    return key % PRIME;
}

// Initialize hash table
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

// Quadratic probing insertion with detailed output
int quadraticProbingInsert(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    if (hashTable->count >= hashTable->size) {
        printf("Hash table is full, cannot insert!\n");
        return -1;
    }
    int index = hashFunc(key) % hashTable->size;
    printf("Insert %d: initial position %d", key, index);
    
    int i = 0;
    while (hashTable->table[(index + i * i) % hashTable->size].status == 1) {
        int currentPos = (index + i * i) % hashTable->size;
        printf(" -> position %d occupied (collision)", currentPos);
        i++;
        if (i >= hashTable->size) {
            printf(" -> insertion failed, no free position!\n");
            return -1;
        }
    }
    int pos = (index + i * i) % hashTable->size;
    if (i > 0) {
        printf(" -> found position %d after %d quadratic probes\n", pos, i);
    } else {
        printf(" -> directly inserted at position %d\n", pos);
    }
    
    hashTable->table[pos].key = key;
    hashTable->table[pos].status = 1;
    hashTable->count++;
    return pos;
}

// Quadratic probing search with detailed output
int quadraticProbingSearch(OpenHashTable *hashTable, int key, int (*hashFunc)(int)) {
    int index = hashFunc(key) % hashTable->size;
    int i = 0;
    printf("Search %d process:\n", key);
    while (hashTable->table[(index + i * i) % hashTable->size].status != 0) {
        int pos = (index + i * i) % hashTable->size;
        printf("  Probe %d: position %d", i, pos);
        if (hashTable->table[pos].status == 1 && hashTable->table[pos].key == key) {
            printf(", found!\n");
            return pos;
        } else {
            printf(", not found\n");
        }
        i++;
        if (i >= hashTable->size) break;
    }
    printf("  Search failed, %d not found\n", key);
    return -1;
}

// Print hash table
void printTable(OpenHashTable *hashTable) {
    printf("\n=== Current Hash Table Status ===\n");
    printf("Index\tStatus\t\tKey\tHash Value\n");
    printf("-----\t------\t\t---\t----------\n");
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i].status == 1) {
            int hashValue = divisionMethod(hashTable->table[i].key);
            printf("[%2d]\toccupied\t%d\t%d\n", i, hashTable->table[i].key, hashValue);
        } else {
            printf("[%2d]\tempty\t\t-\t-\n", i);
        }
    }
    printf("\n");
}

int main() {
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);
    // Test data chosen to create many collisions
    // These keys will collide under division method (mod 11)
    int keys[] = {21, 32, 10, 43, 54, 65, 76, 87, 98, 99, 11, 22, 33, 44};
    int n = sizeof(keys)/sizeof(keys[0]);

    printf("=== Quadratic Probing Collision Resolution Demo ===\n");
    printf("Hash Function: Division Method H(key) = key %% %d\n\n", PRIME);
    
    printf("Insertion Process:\n");
    for (int i = 0; i < n; i++) {
        int hashValue = divisionMethod(keys[i]);
        printf("Step %d: ", i+1);
        int pos = quadraticProbingInsert(table, keys[i], divisionMethod);
        if (pos == -1) {
            printf("Insertion failed!\n");
            break;
        }
    }
    
    printTable(table);

    // Search demonstration - including existing and non-existing data
    printf("=== Search Demonstration ===\n");
    int searchKeys[] = {43, 76, 99, 100, 55};
    for (int i = 0; i < 5; i++) {
        int pos = quadraticProbingSearch(table, searchKeys[i], divisionMethod);
        if (pos != -1)
            printf("Search %d result: found at position %d\n\n", searchKeys[i], pos);
        else
            printf("Search %d result: not found\n\n", searchKeys[i]);
    }

    // Statistics
    printf("=== Statistics ===\n");
    printf("Hash table size: %d\n", table->size);
    printf("Stored elements: %d\n", table->count);
    printf("Load factor: %.2f\n", (float)table->count / table->size);

    free(table->table);
    free(table);
    return 0;
}
