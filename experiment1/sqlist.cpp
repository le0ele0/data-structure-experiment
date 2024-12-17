// 算法描述 流程图
// 调试过程 怎么调试的
// 1. 采用递增有序的顺序表表示集合，求解两个集合的交集、并集和差集
// （1）定义顺序表的存储结构；
// （2）实现存储递增有序集合的顺序表的建立、求交集、并集和差集等运算；
// （3）要求算法的时间性能在线性时间复杂度内；
// （4）和采用无序顺序表所表示的集合的有关运算的时间性能进行比较。
#include <stdio.h>
#include <malloc.h>
#define Max_size 50
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
    } while (La.length > i && Lb.length > j);

    for (j; j < Lb.length; j++)
        InsertOrdered(Lc, Lb.data[j]);
    for (i; i < La.length; i++)
        InsertOrdered(Lc, La.data[i]);
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
void Difference(const SqList &La, const SqList &Lb, SqList &Lc)
{
    int i = 0, j = 0;
    InitList(Lc); // 初始化 Lc 为空列表

    while (i < La.length && j < Lb.length)
    {
        if (La.data[i] == Lb.data[j])
        {
            // 如果元素相等，则跳过这个元素，因为它不是差集的一部分
            i++;
            j++;
        }
        else if (La.data[i] < Lb.data[j])
        {
            // 如果 La 中的元素小于 Lb 中的元素，那么它不在 Lb 中，应该加入到 Lc
            InsertOrdered(Lc, La.data[i++]);
        }
        else
        {
            // 如果 La 中的元素大于 Lb 中的元素，增加 j 来继续比较
            j++;
        }
    }

    // 将 La 中剩余的元素添加到 Lc，因为这些元素肯定不在 Lb 中
    while (i < La.length)
    {
        InsertOrdered(Lc, La.data[i++]);
    }
}
int main()
{
    int a[5] = {9, 5, 3, 1, 7};
    int b[5] = {2, 4, 1, 6, 7};
    printf("集合a：");
    for (int i = 0; i < 5; i++)
        printf(" %d", a[i]);
    printf("\n集合b：");
    for (int i = 0; i < 5; i++)
        printf(" %d", b[i]);
    SqList La, Lb, Lc, Ld, Le;
    // 初始化样例
    InitList(La);
    InitList(Lb);
    // 创建待操作的集合
    for (int i = 0; i < 5; i++)
        InsertOrdered(La, a[i]);
    for (int i = 0; i < 5; i++)
        InsertOrdered(Lb, b[i]);
    // 调用合并、相交、差集函数
    Union(La, Lb, Lc);
    Intersection(La, Lb, Ld);
    Difference(La, Lb, Le);
    printf("\n并集：");
    for (int i = 0; i < Lc.length; i++)
        printf(" %d", Lc.data[i]);
    printf("\n交集：");
    for (int i = 0; i < Ld.length; i++)
        printf(" %d", Ld.data[i]);
    printf("\n差集：");
    for (int i = 0; i < Le.length; i++)
        printf(" %d", Le.data[i]);
}
