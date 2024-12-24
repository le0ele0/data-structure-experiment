#include <stdio.h>
#include <stdlib.h>

// 二叉树节点的定义
typedef struct Node
{
    int data;           // 数据域
    struct Node *left;  // 左子树指针
    struct Node *right; // 右子树指针
} Node;

// 先序遍历
void preOrder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data); // 访问根节点
        preOrder(root->left);      // 遍历左子树
        preOrder(root->right);
    } // 遍历右子树
}

// 中序遍历
void inOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);       // 遍历左子树
    printf("%d ", root->data); // 访问根节点
    inOrder(root->right);      // 遍历右子树
}

// 后序遍历
void postOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);     // 遍历左子树
    postOrder(root->right);    // 遍历右子树
    printf("%d ", root->data); // 访问根节点
}

// 层次遍历
#include <queue> // 使用C++标准库的队列

void levelOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    std::queue<Node *> q; // 队列用于层次遍历
    q.push(root);         // 将根节点入队
    while (!q.empty())
    {
        Node *current = q.front(); // 获取队头元素
        printf("%d ", current->data);
        q.pop();                   // 出队
        if (current->left != NULL) // 如果有左子树，入队
            q.push(current->left);
        if (current->right != NULL) // 如果有右子树，入队
            q.push(current->right);
    }
}

// 计算树的深度
int treeDepth(Node *root)
{
    if (root == NULL)
    {
        return 0; // 空树的深度为0
    }
    int leftDepth = treeDepth(root->left);                        // 计算左子树的深度
    int rightDepth = treeDepth(root->right);                      // 计算右子树的深度
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1; // 取较大值并加1
}
// 计算叶子数
int countLeaves(Node *root)
{
    if (root == NULL)
    {
        return 0; // 空树没有叶子
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1; // 如果是叶子节点，返回1
    }
    return countLeaves(root->left) + countLeaves(root->right); // 递归统计左、右子树的叶子节点数
}

int main()
{
    // 创建一个简单的二叉树
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = 1;
    root->left = (Node *)malloc(sizeof(Node));
    root->left->data = 2;
    root->right = (Node *)malloc(sizeof(Node));
    root->right->data = 3;
    root->left->left = (Node *)malloc(sizeof(Node));
    root->left->left->data = 4;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->left->right = (Node *)malloc(sizeof(Node));
    root->left->right->data = 5;
    root->left->right->left = NULL;
    root->left->right->right = NULL;
    root->right->left = (Node *)malloc(sizeof(Node));
    root->right->left->data = 6;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = (Node *)malloc(sizeof(Node));
    root->right->right->data = 7;
    root->right->right->right = NULL;
    root->right->right->left = NULL;
    //===========================================
    // #####注意 一定要把叶子节点的左右子树置NULL
    // 不然遍历函数会遍历叶子的left和right （不知道为什么它俩不是NULL）
    // 不知道能不能省掉这一步操作
    //=============================================

    // 测试遍历方法
    printf("Pre-order Traversal: ");
    preOrder(root);
    printf("\n");

    printf("In-order Traversal: ");
    inOrder(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postOrder(root);
    printf("\n");

    printf("Level-order Traversal: ");
    levelOrder(root);
    printf("\n");

    // 计算树的深度
    printf("Tree Depth: %d\n", treeDepth(root));

    // 计算叶子节点数量
    printf("Leaf Nodes: %d\n", countLeaves(root));

    return 0;
}
