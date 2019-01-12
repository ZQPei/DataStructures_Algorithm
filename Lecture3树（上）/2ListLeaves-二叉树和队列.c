/*
原题链接: https://pintia.cn/problem-sets/1010070491934568448/problems/1040435498128044033

03-树2 List Leaves （25 分）
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤10) which is the total number of nodes in the tree 
-- and hence the nodes are numbered from 0 to N−1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. 
If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:
For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, 
and no extra space at the end of the line.

Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
Sample Output:
4 1 5
*/

/*
与上一题类似，用静态链表构建出树，然后按顺序找到叶子结点，顺序是从上到下，从左到右，即不同层的叶子结点，先输出上面的，同一层的叶子结点，从左到右。
方法1：可以考虑选择层序遍历方式，层序遍历需要用到队列。
方法2：也可以考虑先用前序遍历，记录下每个叶结点以及对应的层数。
考虑用方法1，顺便练一下队列,队列考虑用动态数组来表示。
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define Null -1

typedef struct {
    int Left;
    int Right;
}TreeNode;
typedef struct {
    TreeNode *ptrTreeNode;
    int rootIdx;
    int len;
}BinTree;

BinTree ReadBinTree();
int FindRootIdx(BinTree bt);
void PrintBinTree(BinTree bt);
void LevelOrderTraversal(BinTree bt);
void FreeBinTree(BinTree bt);

typedef struct {
    int *Data;
    int Head;
    int Tail;
    int len;
}Queue;

Queue NewQueue(int N);
int isEmpty(Queue q);
void EnterQueue(Queue *pq, int val);
int DeleteQueue(Queue *pq);
void FreeQueue(Queue q);

int main(int argc, char const *argv[])
{
    BinTree bt = ReadBinTree();
    // if(DEBUG) PrintBinTree(bt);
    LevelOrderTraversal(bt);
    FreeBinTree(bt);
    return 0;
}

BinTree ReadBinTree(){
    int N,i;
    char left, right;
    scanf("%d", &N);
    TreeNode *ptrTreeNode = (TreeNode *)malloc(N*sizeof(TreeNode));
    for(i=0;i<N;i++){
        scanf("\n%c %c", &left, &right);
        ptrTreeNode[i].Left = (left == '-')? Null : (int)(left-'0');
        ptrTreeNode[i].Right = (right=='-')? Null : (int)(right-'0');
    }
    BinTree bt={
        .ptrTreeNode = ptrTreeNode,
        .rootIdx = Null,
        .len = N,
    };
    bt.rootIdx = FindRootIdx(bt);
    if(DEBUG && bt.rootIdx == Null) printf("error found!");
    return bt;
}
int FindRootIdx(BinTree bt){
    int N,i;
    N=bt.len;
    int *check = (int *)malloc(N*sizeof(int));
    for(i=0;i<N;i++){
        check[i] = 0;
    }
    for(i=0;i<N;i++){
        int left = bt.ptrTreeNode[i].Left;
        int right = bt.ptrTreeNode[i].Right;
        if(left!=Null) check[left] = 1;
        if(right!=Null) check[right] = 1;
    }
    for(i=0;i<N;i++){
        if(check[i]==0){
            break;
        }
    }
    if(i==N){
        return Null;
    }
    free(check);
    return i;
}
void PrintBinTree(BinTree bt){
    int i;
    for(i=0;i<bt.len;i++){
        printf("%c %c\n", (bt.ptrTreeNode[i].Left==Null)? '-':'0'+(char)bt.ptrTreeNode[i].Left, 
                            (bt.ptrTreeNode[i].Right==Null)? '-':'0'+(char)bt.ptrTreeNode[i].Right);
    }
}
int isLeafNode(BinTree bt, int idx){
    if(bt.ptrTreeNode[idx].Left==Null && bt.ptrTreeNode[idx].Right==Null) return 1;
    else return 0;
}
void LevelOrderTraversal(BinTree bt){
    int N=bt.len;
    int i;
    int rootIdx = bt.rootIdx;
    
    Queue q = NewQueue(N);
    EnterQueue(&q, rootIdx);
    int first = 1;
    while(!isEmpty(q)){
        int idx = DeleteQueue(&q);
        if(isLeafNode(bt, idx)){
            if(first){
                printf("%d", idx);
                first = 0;
            }else{
                printf(" %d",idx);
            }
        }else{
            int leftIdx = bt.ptrTreeNode[idx].Left;
            int rightIdx = bt.ptrTreeNode[idx].Right;
            if(leftIdx!=Null) EnterQueue(&q, leftIdx);
            if(rightIdx!=Null) EnterQueue(&q, rightIdx);
        }
    }
}

void FreeBinTree(BinTree bt){
    free(bt.ptrTreeNode);
}

Queue NewQueue(int N){
    Queue q = {
        .Data = (int*)malloc((N+1)*sizeof(int)),
        .Head = 0,
        .Tail = 0,
        .len = N,
    };
    return q;
}
int isEmpty(Queue q){
    if(q.Head==q.Tail) return 1;
    else return 0;
}
void EnterQueue(Queue *pq, int val){
    if(pq->Tail == pq->len){
        printf("queue full");
    }else{
        pq->Data[pq->Tail++] = val;
    }
}
int DeleteQueue(Queue *pq){
    if(pq->Head==pq->Tail){
        printf("queue empty");
        return Null;
    }else{
        int ret = pq->Data[0];
        int i;
        for(i=1;i<pq->Tail;i++){
            pq->Data[i-1] = pq->Data[i];
        }
        pq->Tail--;
        return ret;
    }
}
void FreeQueue(Queue q){
    free(q.Data);
}
