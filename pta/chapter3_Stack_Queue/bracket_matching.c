#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 200
#define MAX_INPUT_SIZE 1000

// 读取输入字符串
int read_input(char *input) {
    int i = 0;
    char c;
    int flag = 0;

    while (1) {
        if (scanf("%c", &c) != 1) {
            break;
        }
        if (flag == 0 && c == '\n') {
            break;
        }
        if (i >= MAX_INPUT_SIZE - 1) {
            fprintf(stderr, "输入过长！\n");
            return -1;
        }
        input[i++] = c;
        if (c == '.') {
            flag = 0;
        } else {
            flag = 1;
        }
    }
    input[i] = '\0';
    return i;
}

// 检查括号和注释是否匹配
int check_matching(const char *input) {
    char stack[MAX_STACK_SIZE];
    int top = -1;
    char matching[256] = {0};
    matching[')'] = '(';
    matching[']'] = '[';
    matching['}'] = '{';

    for (int i = 0; input[i] != '\0'; i++) {
        //处理左符号
        if (input[i] == '/') {
            if (input[i + 1] == '*') {
                if (top >= MAX_STACK_SIZE - 1) {
                    fprintf(stderr, "栈溢出！\n");
                    return -1;
                }
                stack[++top] = '<';  //先将top指针加一，再将'<'压入栈中
                i++;   //因为用'<'代替了'/*',所以跳过'*'的遍历
            }
        } else if (input[i] == '(' || input[i] == '[' || input[i] == '{') {
            if (top >= MAX_STACK_SIZE - 1) {
                fprintf(stderr, "栈溢出！\n");
                return -1;
            }
            stack[++top] = input[i];
        } 
        //处理右符号
        else if (input[i] == '*') {
            if (input[i + 1] == '/') {
                if (top == -1 || stack[top] != '<') {
                    printf("NO\n");
                    if (top == -1) {
                        printf("?-*/\n");
                    } else {
                        char c = stack[top];
                        if (c == '<') {
                            printf("/*-?\n");
                        } else {
                            printf("%c-?\n", c);
                        }
                    }
                    return 0;
                }
                top--;
                i++;
            }
        } else if (input[i] == ')' || input[i] == ']' || input[i] == '}') {
            if (top == -1 || stack[top] != matching[(unsigned char)input[i]]) {
                printf("NO\n");
                if (top == -1) {
                    printf("?-%c\n", input[i]);
                } else {
                    char c = stack[top];
                    if (c == '<') {
                        printf("/*-?\n");
                    } else {
                        printf("%c-?\n", c);
                    }
                }
                return 0;
            }
            top--;
        }
    }

    if (top == -1) {
        printf("YES\n");
        return 1;
    } else {
        printf("NO\n");
        char c = stack[top];
        if (c == '<') {
            printf("/*-?\n");
        } else {
            printf("%c-?\n", c);
        }
        return 0;
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    int len = read_input(input);
    if (len < 0) {
        return 1;
    }
    check_matching(input);
    return 0;
}    