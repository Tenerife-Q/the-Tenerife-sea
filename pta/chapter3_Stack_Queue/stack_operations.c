#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100  // 定义栈的最大容量

/* 顺序栈结构体定义 */
typedef struct {
    char data[MAX_SIZE];  // 存储栈元素的数组
    int top;              // 栈顶指针，初始为-1
} Stack;

/* 初始化栈 */
void initStack(Stack *s) {
    s->top = -1;         // 栈顶指针置为-1表示空栈
}

/* 判断栈是否为空 */
bool isEmpty(Stack *s) {
    return s->top == -1;
}

/* 入栈操作 */
void push(Stack *s, char c) {
    if (s->top < MAX_SIZE - 1) {  // 栈未满时允许入栈
        s->data[++s->top] = c;    // 栈顶指针先加1，再存入元素
    }
}

/* 出栈操作 */
char pop(Stack *s) {
    if (!isEmpty(s)) {            // 栈非空时允许出栈
        return s->data[s->top--]; // 返回栈顶元素，指针减1
    }
    return '\0';                  // 空栈返回空字符（理论上不会执行）
}

/* 括号匹配函数 */
bool isBalanced(char *str) {
    Stack s;
    initStack(&s);                // 初始化栈
    for (int i = 0; str[i] != '\0'; i++) {  // 遍历字符串
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {  // 左括号入栈
            push(&s, str[i]);
        } else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {  // 右括号检查
            if (isEmpty(&s)) {          // 栈空则无法匹配
                return false;
            }
            char top = pop(&s);         // 弹出栈顶左括号
            // 检查括号类型是否匹配
            if ((top == '(' && str[i] != ')') ||
                (top == '[' && str[i] != ']') ||
                (top == '{' && str[i] != '}')) {
                return false;
            }
        }
    }
    return isEmpty(&s);  // 遍历结束后栈空则匹配成功
}

/* 行编辑函数 */
void lineEditor(char *input) {
    Stack s;
    initStack(&s);                      // 初始化栈
    for (int i = 0; input[i] != '\0'; i++) {  // 处理每个字符
        if (input[i] == '#') {          // 退格符
            if (!isEmpty(&s)) {
                pop(&s);                // 删除前一个字符
            }
        } else if (input[i] == '@') {   // 清空符
            s.top = -1;                 // 直接重置栈顶指针
        } else {
            push(&s, input[i]);         // 普通字符入栈
        }
    }
    // 逆序输出栈内容
    char output[MAX_SIZE];
    int idx = 0;
    while (!isEmpty(&s)) {
        output[idx++] = pop(&s);        // 出栈存入临时数组
    }
    for (int i = idx - 1; i >= 0; i--) { // 逆序打印
        printf("%c", output[i]);
    }
    printf("\n");
}

/* 主函数：测试功能 */
int main() {
    // 测试括号匹配
    char test1[] = "{[()]}";
    printf("测试1: %s → %s\n", test1, isBalanced(test1) ? "正确" : "错误");  // 预期正确

    char test2[] = "([)]";
    printf("测试2: %s → %s\n", test2, isBalanced(test2) ? "正确" : "错误");  // 预期错误

    // 测试行编辑
    char input1[] = "ab#c@de";
    printf("行编辑输入: %s → 输出: ", input1);
    lineEditor(input1);  // 预期输出 "de"

    char input2[] = "a##b";
    printf("行编辑输入: %s → 输出: ", input2);
    lineEditor(input2);  // 预期输出 "b"
    return 0;
}