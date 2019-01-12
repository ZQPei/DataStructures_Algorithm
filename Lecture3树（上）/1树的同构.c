/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1040435498128044032

03-树1 树的同构 （25 分）
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。
而图2就不是同构的。

现给定两棵树，请你判断它们是否是同构的。
输入格式:
输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，
给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。
注意：题目保证每个结点中存储的字母是不同的。

输出格式:
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2（对应图2）：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No
*/

/*
二叉树的静态链表的实现
选择前序遍历
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define Null -1

struct TreeNode{
    char Data;
    char LeftIdx;
    char RightIdx;
};
typedef struct{
    struct TreeNode *ptrTreeNode;
    int rootIdx;
    int len;
}BinTree;

BinTree ReadBinTree();
int FindRootIdx(BinTree bt);
// void SwapTreeNode(BinTree bt, int a1, int a2);
// void SortBinTree(BinTree bt);
int Isomerism(BinTree bt1, BinTree bt2, int idx1, int idx2);
void PrintBinTree(BinTree bt);
void FreeBinTree(BinTree bt);

int main(int argc, char const *argv[])
{
    BinTree bt1 = ReadBinTree();
    BinTree bt2 = ReadBinTree();
    if(DEBUG){
        PrintBinTree(bt1);
        PrintBinTree(bt2);
    }
    int res = Isomerism(bt1,bt2,bt1.rootIdx,bt2.rootIdx);
    if(res) printf("YES");
    else printf("NO");
    FreeBinTree(bt1);
    FreeBinTree(bt2);
    return 0;
}

BinTree ReadBinTree(){
    int N,i;
    scanf("%d",&N);
    BinTree bt = {.ptrTreeNode = (struct TreeNode *)malloc(N*sizeof(struct TreeNode)), 
                .rootIdx = Null,
                .len = N};
    for(i=0;i<N;i++){
        scanf("\n%c %c %c", &(bt.ptrTreeNode[i].Data), &(bt.ptrTreeNode[i].LeftIdx), &(bt.ptrTreeNode[i].RightIdx));
    }
    bt.rootIdx = FindRootIdx(bt);
    return bt;
}

void PrintBinTree(BinTree bt){
    int i;
    for(i=0;i<bt.len;i++){
        printf("%c %c %c\n", bt.ptrTreeNode[i].Data, bt.ptrTreeNode[i].LeftIdx, bt.ptrTreeNode[i].RightIdx);
    }
}

int FindRootIdx(BinTree bt){
    int N = bt.len;
    int *check = (int*)malloc(N*sizeof(int));
    int i;
    for(i=0;i<N;i++){
        check[i] = 0;
    }
    for(i=0;i<N;i++){
        int Left = (bt.ptrTreeNode[i].LeftIdx!='-') ? (int)(bt.ptrTreeNode[i].LeftIdx-'0') : Null;
        int Right = (bt.ptrTreeNode[i].RightIdx!='-') ? (int)(bt.ptrTreeNode[i].RightIdx-'0') : Null;
        if(Left!=Null) check[Left] = 1;
        if(Right!=Null) check[Right] = 1;
    }
    for(i=0;i<N;i++){
        if(check[i]==0){
            break;
        }
    }
    if(DEBUG && i==N) printf("error found!");
    if(DEBUG) printf("rootIdx=%d\n",i);
    free(check);
    return i;
}

void FreeBinTree(BinTree bt){
    free(bt.ptrTreeNode);
}

int Isomerism(BinTree bt1, BinTree bt2, int idx1, int idx2){
    if(idx1==Null && idx2==Null) return 1;
    if(idx1==Null && idx2!=Null || idx1!=Null && idx2==Null) return 0;
    
    struct TreeNode node1 = bt1.ptrTreeNode[idx1];
    struct TreeNode node2 = bt2.ptrTreeNode[idx2];
    if(node1.Data != node2.Data) return 0;
    
    int node1_LeftIdx = (node1.LeftIdx!='-') ? (int)(node1.LeftIdx-'0') : Null;
    int node1_RightIdx = (node1.RightIdx!='-') ? (int)(node1.RightIdx-'0') : Null;
    int node2_LeftIdx = (node2.LeftIdx!='-') ? (int)(node2.LeftIdx-'0') : Null;
    int node2_RightIdx = (node2.RightIdx!='-') ? (int)(node2.RightIdx-'0') : Null;
    
    if(DEBUG){
	    printf("%d %d\n",node1_LeftIdx, node1_RightIdx);
	    printf("%d %d\n",node2_LeftIdx, node2_RightIdx);
	}

    if(Isomerism(bt1,bt2,node1_LeftIdx,node2_LeftIdx) && Isomerism(bt1,bt2,node1_RightIdx,node2_RightIdx) ||
       Isomerism(bt1,bt2,node1_LeftIdx,node2_RightIdx) && Isomerism(bt1,bt2,node1_RightIdx,node2_LeftIdx) ){
        return 1;
    }else return 0;
}

