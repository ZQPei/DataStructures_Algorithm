// 堆栈和队列的定义，以数组实现
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

Queue CreateQueue(){
    Queue q = (Queue)malloc(sizeof(struct _queue));
    q->Front = 0;
    q->Rear = Null;
    q->MaxSize = MAXSIZE;
    return q;
}
void FreeQueue(Queue q){
    free(q);
}
int IsFullQueue(Queue q){
    if(q->Rear==q->MaxSize-1) return 1;
    else return 0;
}
int IsEmptyQueue(Queue q){
    if(q->Rear==Null) return 1;
    else return 0;
}
void EnQueue(Queue q, ElementType X){
    if(IsFullQueue(q)){
        printf("Queue is full");
    }else{
        q->Data[++q->Rear] = X;
    }
}
ElementType DeQueue(Queue q){
    if(IsEmptyQueue(q)){
        printf("Queue is empty");
        return Null;
    }else{
        ElementType ret = q->Data[q->Front];
        int i;
        for(i=0;i<q->Rear;i++){
            q->Data[i] = q->Data[i+1];
        }
        q->Rear--;
        return ret;
    }
}

Stack CreateStack(){
    Stack s=(Stack)malloc(sizeof(struct _stack));
    s->Top = Null;
    s->MaxSize = MAXSIZE;
    return s;
}
void FreeStack(Stack s){
    free(s);
}
int IsFullStack(Stack s){
    if(s->Top==s->MaxSize-1) return 1;
    else return 0;
}
int IsEmptyStack(Stack s){
    if(s->Top==Null) return 1;
    else return 0;
}
void PushStack(Stack s, ElementType X){
    if(IsFullStack(s)){
        printf("Stack is full");
    }else{
        s->Data[++s->Top] = X;
    }
}
ElementType PopStack(Stack s){
    if(IsEmptyStack(s)){
        printf("Stack is empty");
        return Null;
    }else{
        return s->Data[s->Top--];
    }
}

int test_main(int argc, char const *argv[])
{
    Queue q=CreateQueue();
    EnQueue(q, 4);
    printf("%d\n",DeQueue(q));

    Stack s=CreateStack();
    PushStack(s, 5);
    printf("%d\n",PopStack(s));
    return 0;
}

Node CreateNode(ElementType X){
    Node n = (Node)malloc(sizeof(struct _node));
    n->Val = X;
    n->Next = NULL;
    return n;
}
void FreeNode(Node n){
    free(n);
}
void FreeList(List l){
    Node currNode, nextNode;
    currNode = l;
    while(currNode){
        nextNode = currNode->Next;
        FreeNode(currNode);
        currNode = nextNode;
    }
}
void InsertList(List l, ElementType X){
    Node newNode = CreateNode(X);
    Node tmpNode = l;
    while(tmpNode->Next){
        tmpNode = tmpNode->Next;
    }
    tmpNode->Next = newNode;
}
void PrintList(List l){
    Node curr = l;
    while(curr){
        printf("%d ", curr->Val);
        curr = curr->Next;
    }
    printf("\n");
}