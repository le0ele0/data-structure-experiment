#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // ջ���������
typedef int ElemType; // ջ��Ԫ�ص���������

typedef struct
{
    ElemType data[MAXSIZE]; // ����洢ջԪ��
    int top;                // ջ��ָ��
} SqStack;
// ��ʼ��stack
void InitStack(SqStack *S)
{
    S->top = -1; // ջ��ָ����Ϊ -1����ʾ��ջ
}
// �ж�ջ�Ƿ�Ϊ��
int IsEmpty(SqStack S)
{
    return S.top == -1;
}
// ��ջ
int Push(SqStack *S, ElemType e)
{
    if (S->top == MAXSIZE - 1)
    { // ջ��
        printf("Stack overflow!\n");
        return 0;
    }
    S->data[++S->top] = e; // ջ��ָ���1�����Ԫ��
    return 1;
}
// ��ջ
int Pop(SqStack *S, ElemType *e)
{
    if (IsEmpty(*S))
    { // ջ��
        printf("Stack underflow!\n");
        return 0;
    }
    *e = S->data[S->top--]; // ȡ��ջ��Ԫ�غ�ջ��ָ���1
    return 1;
}
// ����ջʵ�֣���ʮ������ת��Ϊ������ƣ�������ơ��˽��ơ�ʮ�����ƣ���
void DecimalToBase(int decimal, int base)
{
    SqStack S;
    InitStack(&S);

    // ��ʮ������ת��ΪĿ�����
    while (decimal > 0)
    {
        Push(&S, decimal % base); // ������ѹջ
        decimal /= base;          // ������
    }

    // ���ε���ջ��Ԫ�أ����Ŀ����Ƶ�����
    printf("Converted number: ");
    while (!IsEmpty(S))
    {
        int digit;
        Pop(&S, &digit);
        // ���ʮ������ʱ�����⴦��
        if (digit >= 10)
        {
            printf("%c", 'A' + digit - 10); // ʮ��������10-15��ӦA-F
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
