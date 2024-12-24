#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // 顺序表的最大容量

// 顺序表的存储结构
typedef struct
{
    int data[MAX_SIZE]; // 存储元素的数组
    int length;         // 当前顺序表的长度
} SeqList;

// 创建顺序表并初始化
SeqList *createSeqList(int *elements, int length)
{
    SeqList *list = (SeqList *)malloc(sizeof(SeqList));
    if (length > MAX_SIZE)
    {
        printf("顺序表长度超过最大容量\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < length; i++)
    {
        list->data[i] = elements[i];
    }
    list->length = length;
    return list;
}

// 二分查找实现
int binarySearch(SeqList *list, int key)
{
    int left = 0;
    int right = list->length - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // 防止溢出

        if (list->data[mid] == key)
        {
            return mid; // 找到元素，返回索引
        }
        else if (list->data[mid] < key)
        {
            left = mid + 1; // 在右半部分查找
        }
        else
        {
            right = mid - 1; // 在左半部分查找
        }
    }
    return -1; // 未找到
}

// 主函数
int main()
{
    int elements[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int length = sizeof(elements) / sizeof(elements[0]);

    SeqList *list = createSeqList(elements, length);

    printf("顺序表中的元素: ");
    for (int i = 0; i < list->length; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");

    int key;
    printf("请输入要查找的元素: ");
    scanf("%d", &key);

    int result = binarySearch(list, key);
    if (result != -1)
    {
        printf("元素 %d 在顺序表中的索引为 %d\n", key, result);
    }
    else
    {
        printf("元素 %d 不在顺序表中\n", key);
    }

    free(list);
    return 0;
}

/*
理解判定树与平均查找长度：
1. 判定树：
   - 判定树是用于分析二分查找过程的二叉树。
   - 树的每个节点表示一次关键字的比较。
   - 左子树表示关键字小于目标值，右子树表示关键字大于目标值。

2. 平均查找长度：
   - 假设顺序表有n个元素，查找成功时的平均查找长度为每次查找所需比较次数的平均值：
     ASL_success = (1/n) * Σ(level_i * p_i)，其中level_i是元素的判定树深度，p_i是查找成功概率。
   - 查找失败时，平均查找长度为判定树中叶子节点路径的平均深度。
*/
