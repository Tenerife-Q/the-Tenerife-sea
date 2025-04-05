#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 常规算法

// 定义栈的最大容量
#define maxsize 35

// 定义栈指针类型
typedef struct SNode* stack;
// 定义栈结点结构体
struct SNode
{
    // 用于存储栈中的数据，类型为 double
    double data[maxsize];
    // 栈顶指针，初始值为 -1 表示栈为空
    int top;
};

// 创建一个新的栈
stack creat()
{
    // 为栈分配内存
    stack s = (stack)malloc(sizeof(struct SNode));
    // 初始化栈顶指针
    s->top = -1;
    return s;
}

// 入栈操作
void push(stack s, double x)
{
    // 栈顶指针加 1，并将元素 x 存入栈中
    s->data[++s->top] = x;
}

// 出栈操作
double pop(stack s)
{
    // 返回栈顶元素，并将栈顶指针减 1
    return s->data[s->top--];
}

// 根据运算符对两个操作数进行计算，并将结果入栈
void calculate(stack s, double op1, double op2, char str)
{
    switch (str) {
    case '+':
        // 执行加法运算，并将结果入栈
        push(s, op1 + op2);
        break;
    case '-':
        // 执行减法运算，并将结果入栈
        push(s, op1 - op2);
        break;
    case '*':
        // 执行乘法运算，并将结果入栈
        push(s, op1 * op2);
        break;
    case '/':
        // 执行除法运算，并将结果入栈
        push(s, op1 / op2);
        break;
    default:
        break;
    }
}

// 用于存储输入的前缀表达式
char a[maxsize];
int main()
{
    // 读取输入的前缀表达式
    gets(a);
    // 计算输入表达式的长度
    int l = strlen(a);
    // 创建一个新的栈
    stack s = creat();
    // 从右向左遍历前缀表达式
    for (int i = l - 1; i >= 0; i--)
    {
        // 如果当前字符是数字
        if (a[i] >= '0' && a[i] <= '9')
        {
            // 将字符转换为对应的数字
            double x = a[i] - '0';
            // 用于处理小数部分
            double m = 10;
            // 向前移动一个字符
            i = i - 1;
            // 继续向前遍历，处理多位数或小数
            for (; i >= 0; i--)
            {
                if (a[i] >= '0' && a[i] <= '9')
                {
                    // 处理多位数，将当前数字累加到 x 中
                    x += m * (a[i] - '0');
                    // 增大倍数，用于处理更高位的数字
                    m *= 10;
                }
                else if (a[i] == '.')
                {
                    // 处理小数部分，将 x 转换为小数
                    x /= m;
                    // 重置倍数
                    m = 1;
                }
                else if (a[i] == '-')
                {
                    // 处理负数，将 x 变为负数
                    x = -x;
                }
                else break;
            }
            // 将处理好的数字入栈
            push(s, x);
        }
        // 如果当前字符是运算符
        else if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
        {
            // 从栈中弹出两个操作数
            double op1 = pop(s);
            double op2 = pop(s);
            // 检查是否为除数为 0 的情况
            if (a[i] == '/' && op2 == 0)
            {
                // 输出错误信息并终止程序
                printf("ERROR");
                return 0;
            }
            // 进行计算并将结果入栈
            calculate(s, op1, op2, a[i]);
        }
    }
    // 检查栈中是否只有一个元素，即最终结果
    if (s->top == 0)
        // 输出最终结果，保留一位小数
        printf("%.1f\n", pop(s));
    else
        // 输出错误信息
        printf("ERROR");
    return 0;
}    