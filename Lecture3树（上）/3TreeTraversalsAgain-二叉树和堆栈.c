/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1040435498128044034

03-树3 Tree Traversals Again （25 分）
An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.


Figure 1
Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

Output Specification:
For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
Sample Output:
3 4 2 6 5 1
*/

/*
已知中序遍历的非递归实现的堆栈进出栈表
首先要恢复出原二叉树，
然后要输出二叉树的后续遍历
方法一：由于堆栈的进出栈表可以得到前序和中序的遍历，把问题转为由前序和中序恢复二叉树的问题
方法二：直接由堆栈恢复出二叉树
选择方法二,当进行push操作，则连在栈顶的二叉树结点的左结点，当进行pop操作，则把下一次push的结点连在上一个pop的右结点上。
*/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1
#define Null -1

struct TreeNode{
    int Val;
    struct TreeNode *Left;
    struct TreeNode *Right;
};
typedef struct TreeNode *BinTree;
BinTree NewTreeNode(int val);
BinTree ReconstructBinTree();
void PostOrderTraversal(BinTree bt);
void FreeBinTree(BinTree bt);

typedef struct _stack{
    BinTree *Data;
    int top;
    int MAXSIZE;
}Stack;
Stack NewStack(int MAXSIZE);
void Push(Stack *ps, struct TreeNode *ptrTreeNode);
struct TreeNode * Pop(Stack *ps);
void FreeStack(Stack s);

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    BinTree bt = ReconstructBinTree(N);
    PostOrderTraversal(bt);
    FreeBinTree(bt);
    return 0;
}

BinTree NewTreeNode(int val){
    BinTree bt = (BinTree)malloc(sizeof(struct TreeNode));
    bt->Val = val;
    bt->Left = bt->Right = NULL;
    return bt;
}
BinTree ReconstructBinTree(int N){
    int i;
    char cmd[5] = {0,};
    int val;
    Stack s = NewStack(N);
    BinTree lastPopNode = NULL;
    BinTree Root = NULL;
    int lastCmdIsPush = 0;
    for(i=0;i<2*N;i++){
        scanf("%s", cmd);
        if(cmd[1]=='u'){
            scanf("%d", &val);
            BinTree tmpNode = NewTreeNode(val);
            if(Root==NULL){
                Root = tmpNode;
            }
            if(lastCmdIsPush){
                s.Data[s.top]->Left = tmpNode;
            }else if(lastPopNode!=NULL){
                lastPopNode->Right = tmpNode;
            }
            Push(&s, tmpNode);
            lastCmdIsPush = 1;
        }else{
            lastPopNode = Pop(&s);
            lastCmdIsPush = 0;
        }
    }
    FreeStack(s);
    return Root;
}
void PostOrderTraversal(BinTree bt){
    static int flag = 1;
    if(bt){
        PostOrderTraversal(bt->Left);
        PostOrderTraversal(bt->Right);
        if(flag){
            printf("%d", bt->Val);
            flag=0;
        }
        else printf(" %d", bt->Val);
    }
}
void FreeBinTree(BinTree bt){
    if(bt){
        FreeBinTree(bt->Left);
        FreeBinTree(bt->Right);
        free(bt);
    }
}


Stack NewStack(int MAXSIZE){
    Stack s={
        .Data = (BinTree *)malloc(MAXSIZE*sizeof(BinTree)),
        .top = Null,
        .MAXSIZE = MAXSIZE,
    };
    return s; 
}
int isEmptyStack(Stack s){
    return s.top==Null ? 1 : 0;
}
int isFullStack(Stack s){
    return s.top==s.MAXSIZE-1 ? 1 : 0;
}
void Push(Stack *ps, struct TreeNode *ptrTreeNode){
    if(isFullStack(*ps)) printf("Stack Full");
    else ps->Data[++ps->top] = ptrTreeNode;
}
struct TreeNode * Pop(Stack *ps){
    if(isEmptyStack(*ps)){
        printf("Stack Empty");
        return NULL;
    }
    else return ps->Data[ps->top--];
}
void FreeStack(Stack s){
    free(s.Data);
}
