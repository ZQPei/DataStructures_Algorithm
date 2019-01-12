#ifndef HEAP_H_
#define HEAP_H_

#define MAXVAL 10001
#define MINVAL -10001
#define Null -1

#define ElementType int

struct HeapStruct{
    ElementType *Data;
    int Size;
    int MaxSize;
};
typedef struct HeapStruct *Heap;
typedef struct HeapStruct *MaxHeap;
typedef struct HeapStruct *MinHeap;

int IsFull(Heap h);
int IsEmpty(Heap h);
void FreeHeap(Heap h);
void PrintHeap(Heap h);
// MaxHeap
Heap CreateMaxHeap(int N);
void InsertMaxHeap(MaxHeap h, ElementType val);
ElementType DeleteMaxHeap(MaxHeap h);
MaxHeap CreateMaxHeap_fromSeq(ElementType seq[], int N);
// MinHeap
Heap CreateMinHeap(int N);
void InsertMinHeap(MinHeap h, ElementType val);
ElementType DeleteMinHeap(MinHeap h);
MinHeap CreateMinHeap_fromSeq(ElementType seq[], int N);

#endif // HEAP_H_