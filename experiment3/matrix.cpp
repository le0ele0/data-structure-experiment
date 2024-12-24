#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10
#define INF 0

// 定义图的结构
typedef struct Graph
{
    int numVertices;                           // 顶点数
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵
} Graph;

// 创建图
Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->adjMatrix[i][j] = INF; // 初始化为0（无边）
        }
    }

    return graph;
}

// 添加边
void addEdge(Graph *graph, int src, int dest)
{
    graph->adjMatrix[src][dest] = 1; // 无权图，边的权值设置为1
    graph->adjMatrix[dest][src] = 1; // 无向图对称赋值
}

// 深度优先遍历的辅助函数
void DFS(Graph *graph, int vertex, bool *visited)
{
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->adjMatrix[vertex][i] && !visited[i])
        {
            DFS(graph, i, visited);
        }
    }
}

// 深度优先遍历
void dfsTraversal(Graph *graph, int startVertex)
{
    bool visited[MAX_VERTICES] = {false};
    printf("\n深度优先遍历: ");
    DFS(graph, startVertex, visited);
    printf("\n");
}

// 队列定义（用于广度优先遍历）
typedef struct Queue
{
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

// 创建队列
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// 检查队列是否为空
bool isEmpty(Queue *queue)
{
    return queue->front == -1;
}

// 入队
void enqueue(Queue *queue, int value)
{
    if (queue->rear == MAX_VERTICES - 1)
    {
        printf("队列已满\n");
        return;
    }
    if (queue->front == -1)
    {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// 出队
int dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("队列为空\n");
        return -1;
    }
    int item = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear)
    {
        queue->front = -1;
        queue->rear = -1;
    }
    return item;
}

// 广度优先遍历
void bfsTraversal(Graph *graph, int startVertex)
{
    bool visited[MAX_VERTICES] = {false};
    Queue *queue = createQueue();

    visited[startVertex] = true;
    enqueue(queue, startVertex);

    printf("\n广度优先遍历: ");

    while (!isEmpty(queue))
    {
        int vertex = dequeue(queue);
        printf("%d ", vertex);

        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjMatrix[vertex][i] && !visited[i])
            {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
    printf("\n");
}

// 主函数
int main()
{
    int vertices = 6;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    dfsTraversal(graph, 0);
    bfsTraversal(graph, 0);

    return 0;
}
