/*
单向链表的实现

TODO：
1.新建结点
2.计算链表长度
3.在链表任意位置插入新结点
4.删除某个指定值的结点
5.链表逆序
6.两个有序链表归并
*/
#include "List.h"

#include <stdio.h>
#include <stdlib.h>



Node NewListNode(ElementType X){
    Node newNode = (Node)malloc(sizeof(struct _node));
    newNode->Data=X;
    newNode->Next=NULL;
    return newNode;
}
void FreeListNode(Node n){
    free(n);
}
List FreeList(List l){
    Node curr;
    while(l){
        curr = l;
        l = l->Next;
        FreeListNode(curr);
    }
    return NULL;
}
void PrintList(List l){
    while(l){
        printf("%d ->", l->Data);
        l=l->Next;
    }
    printf("|\n");
}
int GetListLength(List l){
    int cnt;
    while(l){
        cnt++;
        l=l->Next;
    }
    return cnt;
}
List InsertList(List l, ElementType X){
    Node newNode = NewListNode(X);
    if(l==NULL) return newNode;

    Node tmp=l;
    // 插入到最后一个
    while(tmp->Next){
        tmp=tmp->Next;
    }
    // 此时tmp指向最后一个
    tmp->Next = newNode;
    return l;
}
List DeleteList(List l, ElementType X){
    Node tmp;
    while(l!=NULL && l->Data==X){
        tmp = l;
        l=l->Next;
        FreeListNode(tmp);
    }
    if(l!=NULL){
        Node curr=l, next;
        next = curr->Next;
        while(next){
            if(next->Data==X){
                curr->Next = next->Next;
                FreeListNode(next);
                next = curr->Next;
            }else{
                curr=curr->Next;
                next=next->Next;
            }
        }
    }
    return l;
}
List ReverseList(List l){
    // 若链表长度为0
    if(l==NULL) return NULL;
    // 若链表长度为1
    if(l->Next==NULL) return l;

    // 若链表长度大于等于2
    List retL = l;
    Node curr=l->Next;
    Node next=curr->Next;
    while(next){
        curr->Next=retL;
        retL=curr;

        curr=curr->Next;
        next=next->Next;
    }
    curr->Next = retL;
    retL=curr;
    return retL;
}
List BuildList_fromSeq(ElementType seq[], int N){
    int i;
    List l = NULL;
    for(i=0;i<N;i++){
        l = InsertList(l, seq[i]);
    }
    return l;
}


// 测试主函数
int List_main(int argc, char const *argv[])
{
    int N = 6;
    ElementType A[6] = {34, 8, 64, 51, 32, 31};
    List l=BuildList_fromSeq(A, N);
    PrintList(l);
    l=FreeList(l);
    return 0;
}
