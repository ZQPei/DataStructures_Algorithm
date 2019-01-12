#ifndef UTILS_H_
#define UTILS_H_

#define MAXSIZE 1000
#define Null -1
#define ElementType int

typedef struct _queue *Queue;
struct _queue{
    ElementType Data[MAXSIZE];
    int Front;
    int Rear;
    int MaxSize;
};

Queue CreateQueue();
void FreeQueue(Queue q);
int IsFullQueue(Queue q);
int IsEmptyQueue(Queue q);
void EnQueue(Queue q, ElementType X);
ElementType DeQueue(Queue q);

typedef struct _stack *Stack;
struct _stack{
    ElementType Data[MAXSIZE];
    int Top;
    int MaxSize;
};

Stack CreateStack();
void FreeStack(Stack s);
void PrintStack(Stack s);
int IsFullStack(Stack s);
int IsEmptyStack(Stack s);
void PushStack(Stack s, ElementType X);
ElementType PopStack(Stack s);

typedef struct _node *Node;
struct _node{
    ElementType Val;
    Node Next;
};
typedef Node List;

Node CreateNode(ElementType X);
void FreeNode(Node n);
void FreeList(List l);
void InsertList(List l, ElementType X);
void PrintList(List l);

#endif // UTILS_H_