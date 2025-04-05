#include <stdio.h>
#include <stdbool.h>
#define MAX_N 1008

// 复杂

// 判断给定的出栈序列是否合法
bool isValidOutput(int m, int n, int output[]) {
    // 用于模拟栈的数组，栈顶指针初始化为 -1 表示栈为空
    int stack[MAX_N];
    int top = -1;
    // 当前要入栈的元素，从 1 开始
    int in = 1;

    // 遍历出栈序列中的每个元素
    for (int i = 0; i < n; i++) {
        int out = output[i];
        // 持续入栈，直到栈顶元素等于当前要出栈的元素或者入栈元素全部处理完
        while (in <= n && (top == -1 || stack[top] != out)) {
            // 将当前元素入栈
            stack[++top] = in++;
            // 检查栈的容量是否超过最大限制
            if (top >= m) {
                return false;
            }
        }
        // 如果栈顶元素等于当前要出栈的元素，进行出栈操作
        if (stack[top] == out) {
            top--;
        } else {
            // 栈顶元素不等于要出栈的元素，说明序列不合法
            return false;
        }
    }
    // 遍历完整个出栈序列且没有问题，序列合法
    return true;
}

int main() {
    int m, n, k;
    // 读取最大栈容量 m、入栈元素个数 n 和待检查序列数 k
    if (scanf("%d %d %d", &m, &n, &k) != 3) {
        fprintf(stderr, "输入格式错误\n");
        return 1;
    }

    // 循环处理 k 个出栈序列
    for (int i = 0; i < k; i++) {
        int output[MAX_N];
        // 读取当前出栈序列的每个元素
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &output[j]) != 1) {
                fprintf(stderr, "输入格式错误\n");
                return 1;
            }
        }
        // 判断当前出栈序列是否合法
        if (isValidOutput(m, n, output)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}    
