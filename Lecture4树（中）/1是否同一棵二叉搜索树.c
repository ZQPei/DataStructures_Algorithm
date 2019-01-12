/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1042972044192796672

04-树4 是否同一棵二叉搜索树 （25 分）
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。
于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。
最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
输出样例:
Yes
No
No
*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int Val;
    struct TreeNode *Left, *Right;
    int Flag; //用于判断是否同一棵二叉树的路径标记
};
typedef struct TreeNode * BinTree;
typedef BinTree BST;
BinTree NewTreeNode(int val);
void FreeTreeNode(BinTree node);
void FreeBST(BinTree bst);
void ResetFlag(BinTree bst);
BinTree InsertBST(BinTree bst, int val); // 插入
BinTree CreateBST(int N);     //读取序列并新建二叉搜索树, N是需要读取的序列的长度
int CheckBST(BinTree bst, int N);
int FindBST(BinTree bst, int val);

int main(int argc, char const *argv[])
{
    int N, K, i, k;
    BinTree bst1=NULL;
    scanf("%d", &N);
    while(N!=0){
        scanf("%d", &K);
        bst1 = CreateBST(N);
        for(k=0;k<K;k++){
            if(CheckBST(bst1, N)) printf("YES\n");
            else printf("NO\n");
            ResetFlag(bst1);
        }
        scanf("%d", &N);
    }
    FreeBST(bst1);
    return 0;
}
BinTree NewTreeNode(int val){
    BinTree newNode = (BinTree)malloc(sizeof(struct TreeNode));
    newNode->Val = val;
    newNode->Left = newNode->Right = NULL;
    newNode->Flag = 0;
    return newNode;
}
void ResetFlag(BinTree bst){
    if(bst){
        bst->Flag = 0;
        ResetFlag(bst->Left);
        ResetFlag(bst->Right);
    }
}
void FreeTreeNode(BinTree node){
    free(node);
}
void FreeBST(BinTree bst){
    if(bst){
        FreeBST(bst->Left);
        FreeBST(bst->Right);
        FreeTreeNode(bst);
    }
}
BinTree InsertBST(BinTree bst, int val){ // 插入
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
BinTree CreateBST(int N){     //读取序列并新建二叉搜索树, N是需要读取的序列的长度
    BinTree bst = NULL;
    int i,val;
    for(i=0;i<N;i++){
        scanf("%d", &val);
        bst = InsertBST(bst, val);
    }
    return bst;
}
int CheckBST(BinTree bst, int N){
    int val;
    int i;
    int res=1;
    for(i=0;i<N;i++){
        scanf("%d", &val);
        if(res==1 && !FindBST(bst, val)){
            res = 0;
        }
    }
    return res;
}
int FindBST(BinTree bst, int val){
    // 如果找val路径中经过的结点的flag不等于1，则返回 0
    BinTree tmpNode = bst;
    int res = 0;
    while(tmpNode){
        if(tmpNode->Val == val){
            tmpNode->Flag = 1;
            res = 1;
            break;
        }else{
            if(tmpNode->Flag == 0){
                res = 0;
                break;
            }else{
                if(tmpNode->Val > val){
                    tmpNode = tmpNode->Left;
                }else if(tmpNode->Val < val){
                    tmpNode = tmpNode->Right;
                }
            }
        }
    }
    return res;
}
