/*
TODO：

1. 二叉树的数据结构定义，及相关操作函数定义（链式存储）
2. 二叉树的四种遍历的递归实现和非递归实现
   前序遍历
   中序遍历
   后序遍历
   层序遍历
3. 由前序和中序重建二叉树
4. 计算树的结点数
5. 计算树的深度

*/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

typedef char ElementType;

typedef struct TreeNode *BinTree;
struct TreeNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
typedef BinTree BinTreeNode;

BinTree CreateBinTreeNode(ElementType val);
BinTree ReconstructBinTree(ElementType preOrder[], ElementType inOrder[], int a1, int a2, int len);

void PreOrderTraversal(BinTree bt);
void InOrderTraversal(BinTree bt);
void PostOrderTraversal(BinTree bt);

int CountTreeNode(BinTree bt);
int GetTreeDepth(BinTree bt);

int main(int argc, char const *argv[])
{
    ElementType preOrder[] = "ABDFECG";
    ElementType inOrder[] = "FDBEACG";
    int len = 7;
    if(DEBUG) printf("%s %s\n", preOrder, inOrder);
    BinTree bt = ReconstructBinTree(preOrder, inOrder, 0,0, len);

    PreOrderTraversal(bt); printf("\n");
    InOrderTraversal(bt); printf("\n");
    PostOrderTraversal(bt); printf("\n");

    printf("Number of tree nodes = %d\n", CountTreeNode(bt));
    printf("Depth of binary tree = %d\n", GetTreeDepth(bt));
    return 0;
}

BinTreeNode CreateBinTreeNode(ElementType val){
    BinTreeNode btnode = (BinTreeNode)malloc(sizeof(struct TreeNode));
    btnode->Data = val;
    btnode->Left = NULL;
    btnode->Right = NULL;
    return btnode;
}

BinTree ReconstructBinTree(ElementType preOrder[], ElementType inOrder[], int a1, int a2, int len){
    /*
    preorder = preorder[a1:a1+len]
    inorder = inorder[a2:a2+len]
    */
    if(DEBUG){
        int i;
        for(i=0;i<len;i++){
            printf("%c",*(preOrder+a1+i));
        }
        printf(" ");
        for(i=0;i<len;i++){
            printf("%c",*(inOrder+a2+i));
        }
        printf("\n");
    }
    if(len==1){
        if(preOrder[a1]!=inOrder[a2]) printf("Error Found!");
        return CreateBinTreeNode(preOrder[a1]);
    }else if(len==0){
        return NULL;
    }

    ElementType rootVal = preOrder[a1];
    int idx, lenLeft, lenRight;
    idx = lenLeft = lenRight = 0;
    for(idx=0;idx<len;idx++){
        if(inOrder[a2+idx] == rootVal){
            break;
        }
    }
    lenLeft = idx;
    lenRight = len-idx-1;
    BinTree rootNode = CreateBinTreeNode(rootVal);
    rootNode->Left = ReconstructBinTree(preOrder, inOrder, a1+1, a2, lenLeft);
    rootNode->Right = ReconstructBinTree(preOrder, inOrder, a1+1+lenLeft, a2+1+lenLeft, lenRight);
    return rootNode;
}

void PreOrderTraversal(BinTree bt){
    if(bt){
        printf("%c",bt->Data);
        PreOrderTraversal(bt->Left);
        PreOrderTraversal(bt->Right);
    }
}

void InOrderTraversal(BinTree bt){
    if(bt){
        InOrderTraversal(bt->Left);
        printf("%c",bt->Data);
        InOrderTraversal(bt->Right);
    }
}

void PostOrderTraversal(BinTree bt){
    if(bt){
        PostOrderTraversal(bt->Left);
        PostOrderTraversal(bt->Right);
        printf("%c",bt->Data);
    }
}

int CountTreeNode(BinTree bt){
    if(bt==NULL){
        return 0;
    }
    return CountTreeNode(bt->Left) + CountTreeNode(bt->Right) + 1;
}

int GetTreeDepth(BinTree bt){
    if(bt==NULL){
        return 0;
    }
    int leftDepth = GetTreeDepth(bt->Left);
    int rightDepth = GetTreeDepth(bt->Right);
    return leftDepth > rightDepth? leftDepth+1 : rightDepth+1;
}