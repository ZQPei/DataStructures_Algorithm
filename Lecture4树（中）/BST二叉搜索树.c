/*

二叉搜索树 Binary Search Tree
特点：
1.（以从小到大为例）某一结点的左侧所有结点都比该结点小，右侧的所有结点都比该结点大
2.最小值在树的最左端，最大值在树的最右端
3.二叉搜索树的查找效率取决于树的高度

操作：
0.查找某元素是否在树中
1.插入，往一颗二叉搜索树中插入新结点
2.删除
3.新建，基于已知序列新建二叉搜索树
4.输出搜索树最大值
5.输出搜索树最小值
6.计算搜索树的高度

TODO:
以上操作用链式存储来实现
*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int Val;
    struct TreeNode *Left, *Right;
};
typedef struct TreeNode * BinTree;
typedef BinTree BST;

BinTree NewTreeNode(int val);
void FreeTreeNode(BinTree node);
int FindBST(BinTree bst, int val);
void PrintBST_preorder(BinTree bst);
void PrintBST_inorder(BinTree bst);
BinTree InsertBST(BinTree bst, int val); // 插入
BinTree DeleteBST(BinTree bst, int val); // 删除
BinTree CreateBST(int seq[], int N);     //由给定序列新建二叉搜索树
BinTree FindBSTMax(BinTree bst); // 返回最大值结点
BinTree FindBSTMin(BinTree bst); // 返回最小值结点
int GetBSTMax(BinTree bst);      // 返回最大值
int GetBSTMin(BinTree bst);      // 返回最小值
int GetBSTHeight(BinTree bst);   // 返回搜索树的高度
void FreeBST(BinTree bst);

int main(int argc, char const *argv[])
{
    int seq[] = {4,6,9,8,2,3,7,10};
    int N=8;
    BinTree bst = CreateBST(seq, N);
    PrintBST_preorder(bst); printf("\n");
    PrintBST_inorder(bst); printf("\n");

    bst = DeleteBST(bst, 2);
    bst = DeleteBST(bst, 9);
    bst = DeleteBST(bst, 5);
    PrintBST_preorder(bst); printf("\n");
    PrintBST_inorder(bst); printf("\n");
    FreeBST(bst);
    return 0;
}

BinTree NewTreeNode(int val){
    BinTree newNode = (BinTree)malloc(sizeof(struct TreeNode));
    newNode->Val = val;
    newNode->Left = newNode->Right = NULL;
    return newNode;
}
void FreeTreeNode(BinTree node){
    free(node);
}
int FindBST(BinTree bst, int val){
    /*
    找到则输出1，没找到则输出0
    */
    if(bst==NULL){
        return 0;
    }else{
        if(bst->Val == val){
            return 1;
        }else if(bst->Val > val){
            return FindBST(bst->Left, val);
        }else if(bst->Val < val){
            return FindBST(bst->Right,val);
        }
    }
}
BinTree InsertBST(BinTree bst, int val){
    /*
    如果val值存在于搜索树中，则不做操作
    插入一定是作为叶结点
    */
    if(bst==NULL){
        bst = NewTreeNode(val);
    }else{
        if(bst->Val > val){
            bst->Left = InsertBST(bst->Left, val);
        }else if(bst->Val < val){
            bst->Right = InsertBST(bst->Right, val);
        }
    }
    return bst;
}
BinTree DeleteBST(BinTree bst, int val){
    /*
    val 不一定存在于树中，若不存在则打印不存在
    所以相当于先查找到该元素，再进行删除
    1.删除叶结点
    2.删除结点有一个子树
    3.删除结点有两个子树
    */
    if(bst==NULL){
        printf("val:%d not found\n", val);
    }else{
        if(bst->Val == val){
            BinTree tmpNode = bst;
            if(bst->Left && bst->Right){ 
                //结点度为2， 把右结点的最小值放入该结点,然后删除右结点的最小值， 或者把左结点的最大值放入该结点，然后删除左结点的最大值， 并不会对原树造成很大改动
                //还有一种思路是把左结点接上去，然后把右结点接到左结点的最大值的右侧，但是这种方法会对原搜索树造成较大的改动，不采取
                bst->Val = FindBSTMin(bst->Right)->Val;
                bst->Right = DeleteBST(bst->Right, bst->Val);
            }else{ // 结点度为1 或为叶结点
                if(bst->Left){ //左结点非空
                    bst = bst->Left;
                }else{
                    bst = bst->Right;
                }
                FreeTreeNode(tmpNode);
            }
        }else if(bst->Val > val){
            bst->Left = DeleteBST(bst->Left, val); // 未找到，从左子树递归删除
        }else if(bst->Val < val){
            bst->Right = DeleteBST(bst->Right, val); // 未找到，从右子树递归删除
        }
    }
    return bst;
}
BinTree CreateBST(int seq[], int N){
    int i;
    BinTree bst=NULL;
    for(i=0;i<N;i++){
        bst=InsertBST(bst, seq[i]);
    }
    return bst;
}
BinTree FindBSTMax(BinTree bst){
    BinTree tmpNode = bst;
    while(tmpNode->Right){
        tmpNode = tmpNode->Right;
    }
    return tmpNode;
}
BinTree FindBSTMin(BinTree bst){
    BinTree tmpNode = bst;
    while(tmpNode->Left){
        tmpNode = tmpNode->Left;
    }
    return tmpNode;
}
int GetBSTMax(BinTree bst){
    BinTree tmpNode = bst;
    while(tmpNode->Right){
        tmpNode = tmpNode->Right;
    }
    return tmpNode->Val;
}
int GetBSTMin(BinTree bst){
    BinTree tmpNode = bst;
    while(tmpNode->Left){
        tmpNode = tmpNode->Left;
    }
    return tmpNode->Val;
}
int GetBSTHeight(BinTree bst){
    if(bst==NULL){
        return 0;
    }else{
        int leftHeight = GetBSTHeight(bst->Left);
        int rightHeight = GetBSTHeight(bst->Right);
        return leftHeight>rightHeight ? leftHeight+1 : rightHeight+1;
    }
}
void FreeBST(BinTree bst){
    if(bst){
        FreeBST(bst->Left);
        FreeBST(bst->Right);
        FreeTreeNode(bst);
    }
}
void PrintBST_preorder(BinTree bst){
    static int isFirst=1;
    if(bst){
        if(isFirst){
            printf("%d", bst->Val); isFirst=0;
        }
        else printf(" %d", bst->Val);
        PrintBST_preorder(bst->Left);
        PrintBST_preorder(bst->Right);
    }
}
void PrintBST_inorder(BinTree bst){
    static int isFirst=1;
    if(bst){
        PrintBST_inorder(bst->Left);
        if(isFirst){
            printf("%d", bst->Val); isFirst=0;
        }
        else printf(" %d", bst->Val);
        PrintBST_inorder(bst->Right);
    }
}