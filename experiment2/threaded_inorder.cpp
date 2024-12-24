#include <stdio.h>
#include <stdlib.h>

// 定义二叉线索树节点
typedef struct ThreadNode
{
    char data;                 // 数据域
    struct ThreadNode *lchild; // 左孩子指针
    struct ThreadNode *rchild; // 右孩子指针
    int lTag;                  // 左标志位：0表示左孩子，1表示前驱
    int rTag;                  // 右标志位：0表示右孩子，1表示后继
} ThreadNode, *ThreadTree;

ThreadNode *pre = NULL; // 前驱节点

// 中序线索化递归函数
void InThreading(ThreadTree node)
{
    if (node != NULL)
    {
        // 递归线索化左子树
        InThreading(node->lchild);

        // 处理当前节点
        if (node->lchild == NULL)
        {                       // 如果左子树为空
            node->lTag = 1;     // 设置左指针为前驱
            node->lchild = pre; // 指向前驱
        }
        else
        {
            node->lTag = 0; // 保持左孩子标志
        }
        if (pre != NULL && pre->rchild == NULL)
        {                       // 如果前驱的右子树为空
            pre->rTag = 1;      // 设置右指针为后继
            pre->rchild = node; // 前驱的后继指向当前节点
        }
        pre = node; // 更新前驱节点

        // 递归线索化右子树
        InThreading(node->rchild);
    }
}

// 创建中序线索树
void CreateInThread(ThreadTree tree)
{
    pre = NULL; // 初始化前驱节点为 NULL
    if (tree != NULL)
    { // 如果树不为空，进行中序线索化
        InThreading(tree);
        if (pre != NULL)
        {
            pre->rTag = 1; // 处理最后一个节点
            pre->rchild = NULL;
        }
    }
}

// 在中序线索树中，可以根据线索直接遍历树，避免递归调用。
void InOrderTraversal(ThreadTree tree)
{
    ThreadNode *current = tree;
    while (current != NULL)
    {
        // 找到中序遍历的起点
        while (current->lTag == 0)
        {
            current = current->lchild;
        }

        // 输出当前节点
        printf("%c ", current->data);

        // 根据线索遍历后继节点
        while (current->rTag == 1 && current->rchild != NULL)
        {
            current = current->rchild;
            printf("%c ", current->data);
        }

        // 移动到右孩子
        current = current->rchild;
    }
}

// 创建一个测试树节点
ThreadTree CreateTestTree()
{
    ThreadNode *nodeA = (ThreadNode *)malloc(sizeof(ThreadNode));
    ThreadNode *nodeB = (ThreadNode *)malloc(sizeof(ThreadNode));
    ThreadNode *nodeC = (ThreadNode *)malloc(sizeof(ThreadNode));
    ThreadNode *nodeD = (ThreadNode *)malloc(sizeof(ThreadNode));
    ThreadNode *nodeE = (ThreadNode *)malloc(sizeof(ThreadNode));

    nodeA->data = 'A';
    nodeB->data = 'B';
    nodeC->data = 'C';
    nodeD->data = 'D';
    nodeE->data = 'E';

    nodeA->lchild = nodeB;
    nodeA->rchild = nodeC;
    nodeB->lchild = nodeD;
    nodeB->rchild = nodeE;
    nodeC->lchild = nodeC->rchild = NULL;
    nodeD->lchild = nodeD->rchild = NULL;
    nodeE->lchild = nodeE->rchild = NULL;

    return nodeA; // 返回树的根节点
}

int main()
{
    // 创建测试树
    ThreadTree tree = CreateTestTree();

    // 中序线索化
    CreateInThread(tree);

    // 中序遍历
    printf("中序遍历结果：\n");
    InOrderTraversal(tree);

    return 0;
}
