#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 声明 exp 函数，用于计算前缀表达式的值
double exp();

int main()
{
    // 调用 exp 函数计算前缀表达式的值，并以保留一位小数的格式输出
    printf("%.1f", exp());
    return 0;
}

// 定义 exp 函数，递归计算前缀表达式的值
double exp()
{
    // 用于存储从输入读取的字符序列
    char a[10];
    // 读取一个字符串到数组 a 中
    scanf("%s", a);

    // 如果输入的字符串只有一个字符
    if (!a[1]) 
    {
        // 根据该字符进行不同的操作
        switch (a[0])
        {
        case '+':
            // 递归调用 exp 函数计算两个子表达式的值并相加
            return exp() + exp();
        case '-':
            // 递归调用 exp 函数计算两个子表达式的值并相减
            return exp() - exp();
        case '*':
            // 递归调用 exp 函数计算两个子表达式的值并相乘
            return exp() * exp();
        case '/':
        {
            // 递归调用 exp 函数计算分子的值
            double fenzi = exp(); 
            // 递归调用 exp 函数计算分母的值
            double fenmu = exp(); 
            // 检查分母是否不为 0
            if (fenmu != 0) return fenzi / fenmu;
            else
            {
                // 若分母为 0，输出错误信息并终止程序
                printf("ERROR");
                exit(0);
            }
        }
        default:
            // 如果不是运算符，将字符串转换为 double 类型并返回
            return atof(a);
        }
    }
    else
    {
        // 如果输入的字符串不止一个字符，且第一个字符是正负号
        if (a[0] == '-' || a[0] == '+')
        {
            // 记录正负号
            char flag = a[0];
            int i = 0;
            // 将字符串整体前移一位，去掉正负号
            while (a[i])
            {
                a[i] = a[i + 1];
                i++;
            }
            // 如果是负号，将转换后的数值取负返回
            if (flag == '-')
                return 0 - atof(a);
            else return atof(a);
        }
        else 
            // 如果第一个字符不是正负号，直接将字符串转换为 double 类型并返回
            return atof(a);
    }
}    