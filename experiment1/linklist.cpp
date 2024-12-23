
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
// 判断某个元素是否已经在链表中
int IsExist(LinkList L, ElemType e)
{
    Node *p = L->next;
    while (p)
    {
        if (p->data == e)
        {
            return 1; // 元素存在
        }
        p = p->next;
    }
    return 0; // 元素不存在
}
// 尾插法
void InsertNode(LinkList &L, ElemType e)
{
    Node *s = (Node *)malloc(sizeof(Node));
    s->data = e;
    s->next = NULL;

    Node *r = L;
    while (r->next)
    {
        r = r->next;
    }
    r->next = s;
}
void PrintList(LinkList L)
{
    Node *p = L->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void Union(LinkList L1, LinkList L2, LinkList &L3)
{
    Node *p = L1->next;
    while (p)
    {
        if (!IsExist(L3, p->data))
        {
            InsertNode(L3, p->data);
        }
        p = p->next;
    }

    p = L2->next;
    while (p)
    {
        if (!IsExist(L3, p->data))
        {
            InsertNode(L3, p->data);
        }
        p = p->next;
    }
}
void Intersection(LinkList L1, LinkList L2, LinkList &L3)
{
    Node *p = L1->next;
    while (p)
    {
        if (IsExist(L2, p->data) && !IsExist(L3, p->data))
        {
            InsertNode(L3, p->data);
        }
        p = p->next;
    }
}

void Difference(LinkList L1, LinkList L2, LinkList &L3)
{
    Node *p = L1->next;
    while (p)
    {
        if (!IsExist(L2, p->data) && !IsExist(L3, p->data))
        {
            InsertNode(L3, p->data);
        }
        p = p->next;
    }
}

int main()
{
    ElemType a[] = {1, 2, 3, 4, 5};
    ElemType b[] = {4, 5, 6, 7, 8};

    LinkList L1, L2, L3;
    L3 = (LinkList)malloc(sizeof(Node));
    L3->next = NULL; // 初始化空链表

    CreatNodeR(L1, a, 5);
    CreatNodeR(L2, b, 5);

    printf("集合1: ");
    PrintList(L1);

    printf("集合2: ");
    PrintList(L2);

    // 并集
    LinkList LUnion = (LinkList)malloc(sizeof(Node));
    LUnion->next = NULL;
    Union(L1, L2, LUnion);
    printf("并集: ");
    PrintList(LUnion);

    // 交集
    LinkList LIntersection = (LinkList)malloc(sizeof(Node));
    LIntersection->next = NULL;
    Intersection(L1, L2, LIntersection);
    printf("交集: ");
    PrintList(LIntersection);

    // 差集
    LinkList LDifference = (LinkList)malloc(sizeof(Node));
    LDifference->next = NULL;
    Difference(L1, L2, LDifference);
    printf("差集 (L1 - L2): ");
    PrintList(LDifference);

    return 0;
}