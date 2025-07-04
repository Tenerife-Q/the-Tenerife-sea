// interactive_quadratic_probe_en.c
// Interactive Quadratic Probing Hash Table
// Support insert, search, delete, reset operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11   // Prime number 4k+3, k=2
#define PRIME 11        // Modulus for division method

typedef struct {
    int key;
    int status; // 0:empty, 1:occupied, 2:deleted
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
        hashTable->table[i].key = 0;
    }
    return hashTable;
}

// Reset hash table
void resetHashTable(OpenHashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        hashTable->table[i].status = 0;
        hashTable->table[i].key = 0;
    }
    hashTable->count = 0;
    printf("Hash table has been reset!\n");
}

// Quadratic probing insertion
int quadraticProbingInsert(OpenHashTable *hashTable, int key) {
    if (hashTable->count >= hashTable->size) {
        printf("Hash table is full, cannot insert!\n");
        return -1;
    }
    
    int index = divisionMethod(key) % hashTable->size;
    printf("Insert %d:\n", key);
    printf("  Initial hash position: %d\n", index);
    
    int i = 0;
    
    while (hashTable->table[(index + i * i) % hashTable->size].status == 1) {
        int currentPos = (index + i * i) % hashTable->size;
        if (hashTable->table[currentPos].key == key) {
            printf("  Error: Key %d already exists at position %d\n", key, currentPos);
            return -1;
        }
        printf("  Probe %d: position %d occupied (collision)\n", i, currentPos);
        i++;
        if (i >= hashTable->size) {
            printf("  Insertion failed: no free position found!\n");
            return -1;
        }
    }
    
    int pos = (index + i * i) % hashTable->size;
    hashTable->table[pos].key = key;
    hashTable->table[pos].status = 1;
    hashTable->count++;
    
    if (i > 0) {
        printf("  Inserted at position %d after %d quadratic probes\n", pos, i);
    } else {
        printf("  Directly inserted at position %d\n", pos);
    }
    
    return pos;
}

// Quadratic probing search
int quadraticProbingSearch(OpenHashTable *hashTable, int key) {
    int index = divisionMethod(key) % hashTable->size;
    printf("Search %d:\n", key);
    printf("  Initial hash position: %d\n", index);
    
    int i = 0;
    while (i < hashTable->size) {
        int pos = (index + i * i) % hashTable->size;
        printf("  Probe %d: position %d", i, pos);
        
        if (hashTable->table[pos].status == 0) {
            printf(" (empty) - search failed\n");
            break;
        } else if (hashTable->table[pos].status == 1 && hashTable->table[pos].key == key) {
            printf(" (target found)\n");
            printf("  Search successful: found %d at position %d\n", key, pos);
            return pos;
        } else if (hashTable->table[pos].status == 2) {
            printf(" (deleted) - continue searching\n");
        } else {
            printf(" (other key: %d) - continue searching\n", hashTable->table[pos].key);
        }
        i++;
    }
    
    printf("  Search failed: %d not found\n", key);
    return -1;
}

// Delete element
int deleteKey(OpenHashTable *hashTable, int key) {
    int pos = quadraticProbingSearch(hashTable, key);
    if (pos != -1) {
        hashTable->table[pos].status = 2; // Mark as deleted
        hashTable->count--;
        printf("Delete successful: key %d removed from position %d\n", key, pos);
        return pos;
    } else {
        printf("Delete failed: key %d not found\n", key);
        return -1;
    }
}

// Print hash table
void printTable(OpenHashTable *hashTable) {
    printf("\n=== Current Hash Table Status ===\n");
    printf("Index\tStatus\t\tKey\tHash Value\n");
    printf("-----\t--------\t---\t----------\n");
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%2d]\t", i);
        if (hashTable->table[i].status == 1) {
            int hashValue = divisionMethod(hashTable->table[i].key);
            printf("occupied\t%d\t%d\n", hashTable->table[i].key, hashValue);
        } else if (hashTable->table[i].status == 2) {
            printf("deleted\t\t-\t-\n");
        } else {
            printf("empty\t\t-\t-\n");
        }
    }
    printf("\nStored elements: %d/%d, Load factor: %.2f\n\n", 
           hashTable->count, hashTable->size, (float)hashTable->count / hashTable->size);
}

// Batch insert test data
void insertTestData(OpenHashTable *hashTable) {
    int keys[] = {21, 32, 10, 43, 54, 65, 76, 87, 98, 99, 11, 22, 33, 44};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    printf("=== Batch Insert Test Data ===\n");
    printf("Test data: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
    }
    printf("\n\n");
    
    for (int i = 0; i < n; i++) {
        printf("--- Step %d ---\n", i+1);
        int pos = quadraticProbingInsert(hashTable, keys[i]);
        if (pos == -1) {
            printf("Insertion interrupted!\n");
            break;
        }
        printf("\n");
    }
}

// Show menu
void showMenu() {
    printf("=====================================\n");
    printf("   Quadratic Probing Hash Table Menu\n");
    printf("=====================================\n");
    printf("1. Insert element\n");
    printf("2. Search element\n");
    printf("3. Delete element\n");
    printf("4. Display hash table\n");
    printf("5. Reset hash table\n");
    printf("6. Batch insert test data\n");
    printf("7. Exit program\n");
    printf("=====================================\n");
    printf("Please select operation (1-7): ");
}

int main() {
    OpenHashTable *table = initOpenHashTable(TABLE_SIZE);
    int choice, key, pos;
    
    printf("=== Interactive Quadratic Probing Hash Table Demo ===\n");
    printf("Hash Function: H(key) = key %% %d\n", PRIME);
    printf("Hash Table Size: %d\n\n", TABLE_SIZE);
    
    while (1) {
        showMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Input error, please enter a number!\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        switch (choice) {
            case 1: // Insert
                printf("\nEnter key to insert: ");
                if (scanf("%d", &key) == 1) {
                    printf("\n--- Insert Operation ---\n");
                    pos = quadraticProbingInsert(table, key);
                    if (pos != -1) {
                        printf("Insert successful!\n");
                    }
                } else {
                    printf("Input error!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 2: // Search
                printf("\nEnter key to search: ");
                if (scanf("%d", &key) == 1) {
                    printf("\n--- Search Operation ---\n");
                    pos = quadraticProbingSearch(table, key);
                } else {
                    printf("Input error!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 3: // Delete
                printf("\nEnter key to delete: ");
                if (scanf("%d", &key) == 1) {
                    printf("\n--- Delete Operation ---\n");
                    deleteKey(table, key);
                } else {
                    printf("Input error!\n");
                    while (getchar() != '\n');
                }
                break;
                
            case 4: // Display table
                printTable(table);
                break;
                
            case 5: // Reset
                printf("\n--- Reset Operation ---\n");
                resetHashTable(table);
                break;
                
            case 6: // Batch insert test data
                printf("\n");
                insertTestData(table);
                break;
                
            case 7: // Exit
                printf("\nProgram exit, thanks for using!\n");
                free(table->table);
                free(table);
                return 0;
                
            default:
                printf("\nInvalid choice, please enter 1-7!\n");
                break;
        }
        
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clear input buffer
        getchar(); // Wait for Enter
        printf("\n");
    }
    
    return 0;
}
