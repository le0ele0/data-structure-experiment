#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // 栈的最大容量
typedef int ElemType; // 栈中元素的数据类型

typedef struct
{
    ElemType data[MAXSIZE]; // 数组存储栈元素
    int top;                // 栈顶指针
} SqStack;
// 初始化stack
void InitStack(SqStack *S)
{
    S->top = -1; // 栈顶指针置为 -1，表示空栈
}
// 判断栈是否为空
int IsEmpty(SqStack S)
{
    return S.top == -1;
}
// 进栈
int Push(SqStack *S, ElemType e)
{
    if (S->top == MAXSIZE - 1)
    { // 栈满
        printf("Stack overflow!\n");
        return 0;
    }
    S->data[++S->top] = e; // 栈顶指针加1后存入元素
    return 1;
}
// 出栈
int Pop(SqStack *S, ElemType *e)
{
    if (IsEmpty(*S))
    { // 栈空
        printf("Stack underflow!\n");
        return 0;
    }
    *e = S->data[S->top--]; // 取出栈顶元素后栈顶指针减1
    return 1;
}
// 利用栈实现，将十进制数转换为任意进制（如二进制、八进制、十六进制）。
void DecimalToBase(int decimal, int base)
{
    SqStack S;
    InitStack(&S);

    // 将十进制数转换为目标进制
    while (decimal > 0)
    {
        Push(&S, decimal % base); // 将余数压栈
        decimal /= base;          // 更新商
    }

    // 依次弹出栈中元素，输出目标进制的数字
    printf("Converted number: ");
    while (!IsEmpty(S))
    {
        int digit;
        Pop(&S, &digit);
        // 输出十六进制时需特殊处理
        if (digit >= 10)
        {
            printf("%c", 'A' + digit - 10); // 十进制数字10-15对应A-F
        }
        else
        {
            printf("%d", digit);
        }
    }
    printf("\n");
}

int main()
{
    int decimal, base;

    printf("Enter a decimal number: ");
    scanf("%d", &decimal);

    printf("Enter the base to convert to (e.g., 2 for binary, 8 for octal, 16 for hexadecimal): ");
    scanf("%d", &base);

    if (base < 2 || base > 16)
    {
        printf("Base must be between 2 and 16.\n");
        return 1;
    }

    DecimalToBase(decimal, base);

    return 0;
}
