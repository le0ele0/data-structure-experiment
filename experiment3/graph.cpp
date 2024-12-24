#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100 // 队列的最大容量

// 定义邻接表的节点结构
typedef struct Node
{
    int vertex;        // 邻接点的顶点编号
    struct Node *next; // 指向下一个邻接点
} Node;

// 定义图的结构
typedef struct Graph
{
    int numVertices; // 图的顶点数
    Node **adjLists; // 邻接表数组
} Graph;

// 定义队列结构
typedef struct Queue
{
    int items[MAX_QUEUE_SIZE];
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
    if (queue->rear == MAX_QUEUE_SIZE - 1)
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

// 创建图
Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// 创建一个节点
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// 添加边（无向图）
void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 深度优先遍历的辅助函数
void DFS(Graph *graph, int vertex, bool *visited)
{
    visited[vertex] = true;
    printf("%d ", vertex);

    Node *adjList = graph->adjLists[vertex];
    while (adjList != NULL)
    {
        int adjacentVertex = adjList->vertex;
        if (!visited[adjacentVertex])
        {
            DFS(graph, adjacentVertex, visited);
        }
        adjList = adjList->next;
    }
}

// 深度优先遍历
void dfsTraversal(Graph *graph, int startVertex)
{
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
    {
        visited[i] = false;
    }

    printf("深度优先遍历: ");
    DFS(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// 广度优先遍历
void bfsTraversal(Graph *graph, int startVertex)
{
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
    {
        visited[i] = false;
    }

    Queue *queue = createQueue();

    visited[startVertex] = true;
    enqueue(queue, startVertex);

    printf("广度优先遍历: ");
    while (!isEmpty(queue))
    {
        int vertex = dequeue(queue);
        printf("%d ", vertex);

        Node *adjList = graph->adjLists[vertex];
        while (adjList != NULL)
        {
            int adjacentVertex = adjList->vertex;
            if (!visited[adjacentVertex])
            {
                visited[adjacentVertex] = true;
                enqueue(queue, adjacentVertex);
            }
            adjList = adjList->next;
        }
    }
    printf("\n");

    free(visited);
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
