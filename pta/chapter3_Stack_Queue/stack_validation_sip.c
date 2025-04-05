#include<stdio.h>
#include<stdbool.h>
#define MAX_N 1008

// simple

bool isValidOutput(int m, int n, int output[]) {
    int Stack[MAX_N];  // 模拟栈的数组
    int top = -1;      // 栈顶指针，初始为 -1 表示栈为空
    int in = 1;        // 当前入栈的元素，从 1 开始

    for (int i = 0; i < n; i++) {  // 遍历给定的出栈序列
        int out = output[i];       // 当前想要出栈的数字

        // 入栈判断（当入栈的元素in <= n时，如果栈顶不是当前需要出栈的数字，就可以继续入栈，不要忘了栈为空时也可以入栈哦）
        while (in <= n && (top == -1 || Stack[top] != out)) {
            Stack[++top] = in;     // 将数字 in 入栈
            in++;                  // 准备入栈下一个数字

            if (top >= m) {        // 栈的容量不能超过 m
                return false;      // 超过了栈容量，序列不正确
            }
        }

        // 出栈判断
        if (Stack[top] == out) {  //当前栈顶就是要出栈的数字
            top--;  // 出栈操作
        }
        else {
            return false;  // 当前栈顶不是要出栈的数字，序列不正确
        }
    }

    return true;  // 如果遍历完出栈序列且没有问题
}

int main() {
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);  // 读取最大栈容量 m、入栈元素个数 n 和待检查序列数 k

    for (int i = 0; i < k; i++) {
        int output[MAX_N];  // 存储每次输入的出栈序列
        for (int j = 0; j < n; j++) {
            scanf("%d", &output[j]);  // 读取该序列的每个数字
        }

        // 判断该出栈序列是否合法
        if (isValidOutput(m, n, output)) {
            printf("YES\n");  // 合法输出 YES
        } else {
            printf("NO\n");  // 不合法输出 NO
        }
    }

    return 0;
}

