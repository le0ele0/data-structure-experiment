#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义病人节点结构
typedef struct PatientNode
{
    char name[50];            // 病人姓名
    struct PatientNode *next; // 指向下一个病人的指针
} PatientNode;

// 定义链队列结构
typedef struct Queue
{
    PatientNode *front; // 队列头指针
    PatientNode *rear;  // 队列尾指针
} Queue;

// 初始化队列
void initQueue(Queue *q)
{
    q->front = q->rear = NULL;
}

// 判断队列是否为空
int isEmpty(Queue *q)
{
    return q->front == NULL;
}

// 入队操作
void enqueue(Queue *q, const char *name)
{
    PatientNode *newNode = (PatientNode *)malloc(sizeof(PatientNode));
    strcpy(newNode->name, name); // 复制病人姓名
    newNode->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("%s 排队成功！\n", name);
}

// 出队操作
void dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("队列为空，无法出队！\n");
        return;
    }

    PatientNode *temp = q->front;
    printf("%s 就诊！\n", temp->name);
    q->front = q->front->next;

    if (q->front == NULL)
    { // 如果队列为空
        q->rear = NULL;
    }

    free(temp);
}

// 查询排队情况
void displayQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("队列为空！\n");
        return;
    }

    printf("队列中的病人：\n");
    PatientNode *current = q->front;
    while (current != NULL)
    {
        printf("%s\n", current->name);
        current = current->next;
    }
}

// 显示菜单
void menu()
{
    printf("\n欢迎来到医院看病系统\n");
    printf("1. 排队\n");
    printf("2. 就诊\n");
    printf("3. 查询排队情况\n");
    printf("4. 退出\n");
}

int main()
{
    Queue queue;
    initQueue(&queue); // 初始化队列

    int choice;
    char name[50];

    while (1)
    {
        menu();
        printf("请输入您的选择 (1-4): ");
        scanf("%d", &choice);
        getchar(); // 吸收输入后的换行符

        switch (choice)
        {
        case 1:
            printf("请输入病人姓名：");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = '\0'; // 移除换行符
            enqueue(&queue, name);
            break;
        case 2:
            dequeue(&queue);
            break;
        case 3:
            displayQueue(&queue);
            break;
        case 4:
            printf("感谢使用医院看病系统！\n");
            return 0;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }

    return 0;
}
