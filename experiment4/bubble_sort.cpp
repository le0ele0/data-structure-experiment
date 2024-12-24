#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_SIZE 1000

// 顺序表的存储结构
typedef struct
{
    int data[MAX_SIZE]; // 存储元素的数组
    int length;         // 当前顺序表的长度
} SeqList;

// 初始化顺序表
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

// 普通冒泡排序
void bubbleSort(SeqList *list)
{
    for (int i = 0; i < list->length - 1; i++)
    {
        for (int j = 0; j < list->length - i - 1; j++)
        {
            if (list->data[j] > list->data[j + 1])
            {
                int temp = list->data[j];
                list->data[j] = list->data[j + 1];
                list->data[j + 1] = temp;
            }
        }
    }
}

// 改进冒泡排序 1：加入标志位以检测提前完成排序
void improvedBubbleSort1(SeqList *list)
{
    for (int i = 0; i < list->length - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < list->length - i - 1; j++)
        {
            if (list->data[j] > list->data[j + 1])
            {
                int temp = list->data[j];
                list->data[j] = list->data[j + 1];
                list->data[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

// 改进冒泡排序 2：记录最后一次交换的位置，减少比较范围
void improvedBubbleSort2(SeqList *list)
{
    int n = list->length;
    while (n > 1)
    {
        int newN = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (list->data[i] > list->data[i + 1])
            {
                int temp = list->data[i];
                list->data[i] = list->data[i + 1];
                list->data[i + 1] = temp;
                newN = i + 1;
            }
        }
        n = newN;
    }
}

// 打印顺序表
void printSeqList(SeqList *list)
{
    for (int i = 0; i < list->length; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 主函数
int main()
{
    int elements[] = {64, 34, 25, 12, 22, 11, 90};
    int length = sizeof(elements) / sizeof(elements[0]);

    SeqList *list = createSeqList(elements, length);

    printf("原始数据: ");
    printSeqList(list);

    // 测试普通冒泡排序
    SeqList *list1 = createSeqList(elements, length);
    bubbleSort(list1);
    printf("普通冒泡排序: ");
    printSeqList(list1);

    // 测试改进冒泡排序 1
    SeqList *list2 = createSeqList(elements, length);
    improvedBubbleSort1(list2);
    printf("改进冒泡排序1: ");
    printSeqList(list2);

    // 测试改进冒泡排序 2
    SeqList *list3 = createSeqList(elements, length);
    improvedBubbleSort2(list3);
    printf("改进冒泡排序2: ");
    printSeqList(list3);

    free(list);
    free(list1);
    free(list2);
    free(list3);

    return 0;
}
