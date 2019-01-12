/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1042972044192796673

04-树5 Root of AVL Tree （25 分）
An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; 
if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.

  
  

Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.
Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤20) which is the total number of keys to be inserted. 
Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the root of the resulting AVL tree in one line.

Sample Input 1:
5
88 70 61 96 120
Sample Output 1:
70
Sample Input 2:
7
88 70 61 96 120 90 65
Sample Output 2:
88
*/


#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

struct AVLNode{
    int Val;
    struct AVLNode *Left, *Right;
    int Height; //每个结点的高度
};
typedef struct AVLNode *AVLTree;

AVLTree NewTreeNode(int val);
int GetNodeHeight(AVLTree A);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree SingleRightRotation(AVLTree A);
AVLTree LeftRightRotation(AVLTree A);
AVLTree RightLeftRotation(AVLTree A);
AVLTree InsertAVL(AVLTree avl, int val);
void FreeAVL(AVLTree avl);

AVLTree CreateAVL(int N);
void PrintAVL_preorder(AVLTree avl);
void PrintAVL_inorder(AVLTree avl);

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    AVLTree avl = CreateAVL(N);
    if(DEBUG){
        PrintAVL_preorder(avl); printf("\n");
        PrintAVL_inorder(avl); printf("\n");
    }
    printf("%d\n",avl->Val);
    FreeAVL(avl);
    return 0;
}

int Max ( int a, int b )
{
    return a > b ? a : b;
}
AVLTree NewTreeNode(int val){
    AVLTree newNode = (AVLTree)malloc(sizeof(struct AVLNode));
    newNode->Val = val;
    newNode->Left = newNode->Right = NULL;
    newNode->Height = 1;
    return newNode;
}
int GetNodeHeight(AVLTree A){
    if(A==NULL) return 0;
    else return A->Height;
    // else {
    //     A->Height = Max(GetNodeHeight(A->Left), GetNodeHeight(A->Right)) +1;
    //     return A->Height;
    // }
}
AVLTree SingleLeftRotation(AVLTree A){
    /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */     
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetNodeHeight(A->Right), GetNodeHeight(A->Left)) +1;
    B->Height = Max(GetNodeHeight(B->Left), GetNodeHeight(A)) +1;
    return B;
}
AVLTree SingleRightRotation(AVLTree A){
    /* 注意：A必须有一个右子结点B */
    /* 将A与B做右单旋，更新A与B的高度，返回新的根结点B */     
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetNodeHeight(A->Left), GetNodeHeight(A->Right)) +1;
    B->Height = Max(GetNodeHeight(A), GetNodeHeight(B->Right)) +1;
    return B;
}
AVLTree LeftRightRotation(AVLTree A){
    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */
     
    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    return SingleLeftRotation(A);;
}
AVLTree RightLeftRotation(AVLTree A){
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}
AVLTree InsertAVL(AVLTree avl, int val){
    if(avl==NULL){
        avl = NewTreeNode(val);
    }else if( avl->Val >val){ // 插入左子树
        avl->Left = InsertAVL(avl->Left, val);
        if( GetNodeHeight(avl->Left) - GetNodeHeight(avl->Right) == 2){
            if( avl->Left->Val > val){ // LL，左旋
                avl = SingleLeftRotation(avl);
            }else{                // LR，左右旋
                avl = LeftRightRotation(avl);
            }
        }
    }else if( avl->Val <val){ // 插入右子树
        avl->Right = InsertAVL(avl->Right, val);
        if( GetNodeHeight(avl->Left) - GetNodeHeight(avl->Right) == -2){
            if( avl->Right->Val < val){ // RR，右旋
                avl = SingleRightRotation(avl);
            }else{                // RL，右左旋
                avl = RightLeftRotation(avl);
            }
        }
    }
    //更新树高
    avl->Height = Max(GetNodeHeight(avl->Left), GetNodeHeight(avl->Right)) +1;
    return avl;
}

AVLTree CreateAVL(int N){
    int i;
    int val;
    AVLTree avl = NULL;
    for(i=0;i<N;i++){
        scanf("%d", &val);
        avl = InsertAVL(avl, val);
    }
    return avl;
}
void PrintAVL_preorder(AVLTree avl){
    static int isFirst=1;
    if(avl){
        if(isFirst){
            printf("%d", avl->Val); isFirst=0;
        }
        else printf(" %d", avl->Val);
        PrintAVL_preorder(avl->Left);
        PrintAVL_preorder(avl->Right);
    }
}
void PrintAVL_inorder(AVLTree avl){
    static int isFirst=1;
    if(avl){
        PrintAVL_inorder(avl->Left);
        if(isFirst){
            printf("%d", avl->Val); isFirst=0;
        }
        else printf(" %d", avl->Val);
        PrintAVL_inorder(avl->Right);
    }
}
void FreeAVL(AVLTree avl){
    if(avl){
        FreeAVL(avl->Left);
        FreeAVL(avl->Right);
        free(avl);
    }
}