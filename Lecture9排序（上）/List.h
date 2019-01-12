#ifndef LIST_H_
#define LIST_H_

#define ElementType int

typedef struct _node *Node;
struct _node {
    ElementType Data;
    Node Next;
};
typedef Node List;

Node NewListNode(ElementType X);
void FreeListNode(Node n);
List FreeList(List l);
void PrintList(List l);
int GetListLength(List l);
List InsertList(List l, ElementType X);
List DeleteList(List l, ElementType X);
List ReverseList(List l);
List BuildList_fromSeq(ElementType seq[], int N);

#endif //LIST_H_