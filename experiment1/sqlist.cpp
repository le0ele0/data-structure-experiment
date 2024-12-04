#include <stdio.h>
#include <malloc.h>
#define Max_size 50
// 算法描述 流程图
// 调试过程 怎么调试的
// 1. 采用递增有序的顺序表表示集合，求解两个集合的交集、并集和差集
// （1）定义顺序表的存储结构；
// （2）实现存储递增有序集合的顺序表的建立、求交集、并集和差集等运算；
// （3）要求算法的时间性能在线性时间复杂度内；
// （4）和采用无序顺序表所表示的集合的有关运算的时间性能进行比较。
typedef int ElemType;
typedef struct
{
    ElemType data[Max_size];
    int length;
} SqList;
void InitList(SqList &L)
{
    L.length = 0;
}
bool InsertOrdered(SqList &L, ElemType e)
{
    // 考虑被插入的有序表的长度溢出的处理
    if (L.length >= Max_size)
        return false;
    int i;
    // 所有大于e的元素后移
    for (i = L.length - 1; i >= 0 && L.data[i] > e; i--)
        L.data[i + 1] = L.data[i];
    L.data[i + 1] = e; // 插入
    L.length++;        // 更新长度
    return true;
}
void Union(const SqList &La, const SqList &Lb, SqList &Lc)
{
    InitList(Lc); // 初始化结果表
    int i = 0, j = 0, q = 0;
    do
    {
        if (La.data[i] < Lb.data[j])
            InsertOrdered(Lc, La.data[i++]);
        else if (La.data[i] > Lb.data[j])
            InsertOrdered(Lc, Lb.data[j++]);
        else
        {
            InsertOrdered(Lc, La.data[i++]);
            j++;
            q++;
        }
    } while (Lc.length < La.length + Lb.length - q);
}
void Intersection(const SqList &La, const SqList &Lb, SqList &Lc)
{
    int i = 0, j = 0, q = 0;
    InitList(Lc);
    do
    {
        if (La.data[i] == Lb.data[j])
        {
            InsertOrdered(Lc, La.data[i++]);
            j++;
            q++;
        }
        else if (La.data[i] < Lb.data[j])
            i++;
        else
            j++;
    } while (i < La.length && j < Lb.length);
}

int main()
{
    printf("hello world\n主函数开始运行");
    int a[7] = {9, 5, 3, 1, 7};
    int b[5] = {2, 4, 6, 7};
    // 112223455679
    SqList La, Lb, Lc, Ld;
    // 初始化样例
    InitList(La);
    InitList(Lb);
    // 创建待合并、橡胶的集合
    for (int i = 0; i < 5; i++)
        InsertOrdered(La, a[i]);
    for (int i = 0; i < 4; i++)
        InsertOrdered(Lb, b[i]);
    // 调用合并、相交函数
    Union(La, Lb, Lc);
    Intersection(La, Lb, Ld);
    for (int i = 0; i < Lc.length; i++)
        printf("%d", Lc.data[i]);
    printf("\n");
    for (int i = 0; i < Ld.length; i++)
        printf("%d", Ld.data[i]);
}
