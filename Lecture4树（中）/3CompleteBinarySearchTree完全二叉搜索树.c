/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1042972044192796674

04-树6 Complete Binary Search Tree （30 分）
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT. 
You are supposed to output the level order traversal sequence of this BST.

Input Specification:
Each input file contains one test case. 
For each case, the first line contains a positive integer N (≤1000). Then N distinct non-negative integer keys are given in the next line. 
All the numbers in a line are separated by a space and are no greater than 2000.

Output Specification:
For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. 
All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input:
10
1 2 3 4 5 6 7 8 9 0
Sample Output:
6 3 8 1 5 7 9 0 2 4
*/

/*
完全二叉搜索树 Complete Binary Search Tree
既是二叉搜索树，也是完全二叉树
由于元素固定，所以可以根据元素的数量确定完全树的高度
然后再对序列排序，依次放入树中

完全树用数组存储比较方便
*/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0
#define MAXVAL 2001
#define MAXSIZE 1001
#define Null -1

typedef struct {
    int *Data;
    int Top;
    int Len;
}Stack;
Stack CreateStack(int N);
void Push(Stack *ps, int val);
int Pop(Stack *ps);
int IsEmpty(Stack s);
void FreeStack(Stack s);

typedef struct {
    int *Data;
    int Len;
    int Depth;
}CBST;
CBST CreateCBST(int seq[], int N);
void PrintCBST(CBST cbst);

void Sort(int seq[], int N); //从小到大

int main(int argc, char const *argv[])
{
    // 先读取数组
    int N,i;
    scanf("%d", &N);
    int *seq = (int*)malloc(N*sizeof(int));
    for(i=0;i<N;i++){
        scanf("%d", seq+i);
    }

    // 对数组进行排序
    Sort(seq, N);
    if(DEBUG) for(i=0;i<N;i++) printf("%d ", seq[i]);

    // 把排序后的数组插入到CBST的对应位置
    CBST cbst = CreateCBST(seq, N);
    PrintCBST(cbst);
    return 0;
}

void Sort(int seq[], int N){
    //从小到大排序
    int i,j;
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            if(seq[j]<seq[i]){
                int tmp=seq[i];
                seq[i] = seq[j];
                seq[j] = tmp;
            }
        }
    }
}

Stack CreateStack(int N){
    Stack s = {
        .Data = (int *)malloc(N*sizeof(int)),
        .Top = Null,
        .Len = N,
    };
    return s;
}
void Push(Stack *ps, int val){
    if(ps->Top==ps->Len-1){
        printf("Stack full");
    }else{
        ps->Data[++ps->Top] = val;
    }
}
int Pop(Stack *ps){
    if(ps->Top==Null){
        printf("Stack empty");
        return Null;
    }else{
        return ps->Data[ps->Top--];
    }
}
int IsEmpty(Stack s){
    if(s.Top==Null) return 1;
    else return 0;
}
void FreeStack(Stack s){
    free(s.Data);
}

int log_2(int b){
    // return floor(loga(b))
    int ret = 0;
    int tmp=b;
    while(tmp>1){
        tmp /= 2;
        ret ++;
    }
    return ret;
}
CBST CreateCBST(int seq[], int N){
    int i;
    CBST cbst = {
        .Data = (int*)malloc(N*sizeof(int)),
        .Len = N+1,
        .Depth = 0,
    };
    cbst.Data[0] = MAXVAL;
    cbst.Depth = log_2(N)+1;

    // 完全二叉树的中序遍历 ， 堆栈实现
    i=0;
    Stack s = CreateStack(MAXSIZE);
    int idx=1;
    while(idx<=N || !IsEmpty(s)){
        while(idx<=N){
            Push(&s, idx);
            idx *= 2;
        }
        if(!IsEmpty(s)){
            idx = Pop(&s);
            cbst.Data[idx] = seq[i++];
            idx = idx*2+1;
        }
    }
    return cbst;
}
void PrintCBST(CBST cbst){
    int i;
    for(i=1;i<cbst.Len;i++){
        if(i==1) printf("%d", cbst.Data[i]);
        else printf(" %d", cbst.Data[i]);
    }
}