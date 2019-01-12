/*
自平衡二叉搜索树  由Adelson-Velskii and Landis提出，所以叫AVL

自平衡二叉树的目的是使二叉搜索树的平均查找长度最小，因为插入或删除元素后，二叉树可能会变得不平衡

平衡二叉树的定义：
任意结点左子树和右子树的高度差不超过1， 即|hL-hR| <= 1
结点的平衡因子 Balance Factor,  BF = hL-hR

特点：
自平衡二叉搜索树具有搜索树的性质外，还具有自平衡性，即对于每个新插入的元素，或是删除某个元素，
自平衡二叉树能够保证树高度始终不超过结点个数N的 log2(N)

TODO：
在平衡二叉树的基础上实现
1.自平衡插入
2.自平衡删除
*/

#include <stdio.h>
#include <stdlib.h>

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

AVLTree CreateAVL(int seq[], int N);
void PrintAVL_preorder(AVLTree avl);
void PrintAVL_inorder(AVLTree avl);

int main(int argc, char const *argv[])
{
    int seq[] = {4,6,9,8,2,3,7,10};
    int N=8;
    AVLTree avl = CreateAVL(seq, N);
    PrintAVL_preorder(avl); printf("\n");
    PrintAVL_inorder(avl); printf("\n");

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

AVLTree CreateAVL(int seq[], int N){
    int i;
    AVLTree avl = NULL;
    for(i=0;i<N;i++){
        avl = InsertAVL(avl, seq[i]);
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