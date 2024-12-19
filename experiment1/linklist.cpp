
// 2. 采用递增有序的链表表示集合，求解两个集合的交集、并集和差集
// （1）定义链表的存储结构；
// （2）实现存储递增有序集合的链表的建立、求交集、并集和差集等运算；
// （3）要求算法的时间性能在线性时间复杂度内；
// （4）和采用无序链表所表示的集合的有关运算的时间性能进行比较。
#include <stdio.h>
#include <malloc.h>
#define Max_size 50
typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

void CreatNodeR(Node *&L, ElemType a[], int n)
{ // 创建一个单链表
    Node *s, *r;
    L = (Node *)malloc(sizeof(Node));
    r = L;
    for (int i = 0; i < n; i++)
    {
        s = (Node *)malloc(sizeof(Node));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
}
void Union(const LinkList a, const LinkList b, LinkList &c)
{
}
int main()
{

    return 0;
}
