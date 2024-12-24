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

// 堆调整函数 (大顶堆)
void heapify(int *data, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && data[left] > data[largest])
    {
        largest = left;
    }

    if (right < n && data[right] > data[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        int temp = data[i];
        data[i] = data[largest];
        data[largest] = temp;
        heapify(data, n, largest);
    }
}

// 堆排序函数
void heapSort(int *data, int n)
{
    // 构建初始大顶堆
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(data, n, i);
    }

    // 逐步取出堆顶元素并调整堆
    for (int i = n - 1; i > 0; i--)
    {
        int temp = data[0];
        data[0] = data[i];
        data[i] = temp;
        heapify(data, i, 0);
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

// 测试堆排序性能
void testHeapSort()
{
    SeqList *list = (SeqList *)malloc(sizeof(SeqList));

    // 最好情况测试
    generateRandomData(list, 100000);
    heapSort(list->data, list->length);
    printf("最好情况: 排序完成\n");

    // 最坏情况测试 (已经排序的数据)
    heapSort(list->data, list->length);
    printf("最坏情况: 排序完成\n");

    // 平均情况测试 (随机数据)
    generateRandomData(list, 100000);
    heapSort(list->data, list->length);
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

    // 测试堆排序
    heapSort(list->data, list->length);
    printf("堆排序结果: ");
    printSeqList(list);

    // 测试排序性能
    testHeapSort();

    free(list);
    return 0;
}
