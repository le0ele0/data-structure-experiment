#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_SIZE 1000000

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

// 快速排序的分区函数
int partition(int *data, int low, int high)
{
    int pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (data[j] < pivot)
        {
            i++;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    int temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;
    return i + 1;
}

// 快速排序函数
void quickSort(int *data, int low, int high)
{
    if (low < high)
    {
        int pi = partition(data, low, high);
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
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

// 生成随机数据用于测试
void generateRandomData(SeqList *list, int length)
{
    if (length > MAX_SIZE)
    {
        printf("数据长度超过最大容量\n");
        exit(EXIT_FAILURE);
    }
    list->length = length;
    for (int i = 0; i < length; i++)
    {
        list->data[i] = rand() % 100000; // 生成随机数
    }
}

// 测试快速排序性能
void testQuickSort()
{
    SeqList *list = (SeqList *)malloc(sizeof(SeqList));

    // 最好情况测试
    generateRandomData(list, 100000);
    quickSort(list->data, 0, list->length - 1);
    printf("最好情况: 排序完成\n");

    // 最坏情况测试 (已经排序的数据)
    quickSort(list->data, 0, list->length - 1);
    printf("最坏情况: 排序完成\n");

    // 平均情况测试 (随机数据)
    generateRandomData(list, 100000);
    quickSort(list->data, 0, list->length - 1);
    printf("平均情况: 排序完成\n");

    free(list);
}

// 主函数
int main()
{
    srand(time(NULL));

    int elements[] = {64, 34, 25, 12, 22, 11, 90};
    int length = sizeof(elements) / sizeof(elements[0]);

    SeqList *list = createSeqList(elements, length);

    printf("原始数据: ");
    printSeqList(list);

    // 测试快速排序
    quickSort(list->data, 0, list->length - 1);
    printf("快速排序结果: ");
    printSeqList(list);

    // 测试排序性能
    testQuickSort();

    free(list);
    return 0;
}
