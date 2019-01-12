/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1037889290772254720

02-线性结构1 两个有序链表序列的合并 （15 分）
本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。

函数接口定义：
List Merge( List L1, List L2 );
其中List结构定义如下：

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 
    PtrToNode   Next; /* 指向下一个结点的指针 
};
typedef PtrToNode List; /* 定义单链表类型 
L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。

输入样例：
3
1 3 5
5
2 4 6 8 10
输出样例：
1 2 3 4 5 6 8 10 
NULL
NULL
*/

/*
时间复杂度： O(max(N1,N2))
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Read(){
    int N,i;
    ElementType tmp;
    scanf("%d", &N);
    List L=NULL;
    PtrToNode tail=NULL;
    for(i=0;i<N;i++){
        scanf("%d", &tmp);
        PtrToNode pNewNode = (PtrToNode)malloc(sizeof(struct Node));
        pNewNode->Data = tmp;
        pNewNode->Next = NULL;
        if(i==0){
            L=tail=pNewNode;
        }else{
            tail->Next = pNewNode;
            tail = pNewNode;
        }
    }
    return L;
}

void Print( List L ){
    PtrToNode tmp=L;
    int isFirst = 1;
    while(tmp){
        if(!isFirst){
            printf(" "); 
            isFirst=0;
        }
        printf("%d",tmp->Data);
        tmp=tmp->Next;
    }
    printf("\n");
}

List Merge( List L1, List L2 ){
    List L=NULL;
    PtrToNode tail=NULL;
    // 边界条件判断
    if(L1==NULL) {
        L=L2;
        return L;
    }else if(L2==NULL){
        L=L1;
        return L;
    }else{
        if(L1->Data<=L2->Data){
            L=tail=L1;
            L1=L1->Next;
        }else if(L1->Data>L2->Data){
            L=tail=L2;
            L2=L2->Next;
        }
    }
    // Print(L);
    // 主要循环， 时间复杂度为 o(max(N1,N2))
    while(L1 || L2){
        if(L1==NULL){
            tail->Next=L2;
            L2=NULL;
            break;
        }else if(L2==NULL){
            tail->Next=L1;
            L1=NULL;
            break;
        }else{
            if(L1->Data<=L2->Data){
                tail->Next=L1;
                tail=tail->Next;
                L1=L1->Next;
            }else if(L1->Data>L2->Data){
                tail->Next=L2;
                tail=tail->Next;
                L2=L2->Next;
            }
        }
    }
    return L;
}