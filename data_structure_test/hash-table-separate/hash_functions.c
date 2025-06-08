// 散列函数构建方法的实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1. 直接定址法
int directAddressing(int key) {
    return key;  // 简单示例，实际应用中可能需要线性变换 H(key) = a*key + b
}

// 2. 数字分析法 (示例: 取身份证号码的后四位)
int digitAnalysis(int key) {
    return key % 10000;  // 假设key是身份证号码，取后四位作为哈希地址
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
#define PRIME 13  // 通常选择小于等于哈希表大小的素数
int divisionMethod(int key) {
    return key % PRIME;
}

// 6. 乘法散列法
#define RANDOM_A 0.618  // 黄金分割比
int multiplicationMethod(int key) {
    double product = key * RANDOM_A;
    double fraction = product - (int)product;
    return (int)(100 * fraction);  // 假设哈希表大小为100
}    