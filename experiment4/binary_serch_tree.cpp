#include <stdio.h>
#include <stdlib.h>

// 定义二叉链表的存储结构
typedef struct TreeNode
{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建一个新节点
TreeNode *createNode(int key)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入节点
TreeNode *insert(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    return root;
}

// 查找节点
TreeNode *search(TreeNode *root, int key)
{
    if (root == NULL || root->key == key)
    {
        return root;
    }
    if (key < root->key)
    {
        return search(root->left, key);
    }
    return search(root->right, key);
}

// 找到最小值节点
TreeNode *findMin(TreeNode *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// 删除节点
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // 找到节点
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        TreeNode *temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// 中序遍历
void inorderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// 理解二叉排序树的平均查找长度：
// 平均查找长度与树的高度相关，较平衡的树能够提供较低的平均查找长度。

// 理解平衡二叉树的概念：
// 平衡二叉树如AVL树或红黑树通过调整树的结构，保证每个子树高度差不超过一定范围，从而提高查找性能。

int main()
{
    TreeNode *root = NULL;
    int elements[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(elements) / sizeof(elements[0]);

    // 构建二叉排序树
    for (int i = 0; i < n; i++)
    {
        root = insert(root, elements[i]);
    }

    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");

    // 查找节点
    int key = 40;
    TreeNode *found = search(root, key);
    if (found)
    {
        printf("找到节点: %d\n", found->key);
    }
    else
    {
        printf("未找到节点: %d\n", key);
    }

    // 删除节点
    key = 30;
    root = deleteNode(root, key);
    printf("删除节点 %d 后的中序遍历: ", key);
    inorderTraversal(root);
    printf("\n");

    return 0;
}
