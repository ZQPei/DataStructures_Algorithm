/*
最大堆和最小堆的实现
*/
#include "Heap.h"

#include <stdio.h>
#include <stdlib.h>


int heap_main(int argc, char const *argv[])
{
    ElementType seq[] = {10,18,25,31,44,58};
    int N = 6;
    MaxHeap h = CreateMinHeap_fromSeq(seq, N);
    PrintHeap(h);
    int i;
    for(i=0;i<N;i++){
        DeleteMinHeap(h);
        PrintHeap(h);
    }
    DeleteMinHeap(h);
    return 0;
}


int IsFull(Heap h){
    if(h->Size==h->MaxSize){
        printf("Heap full");
        return 1;
    }else return 0;
}
int IsEmpty(Heap h){
    if(h->Size==0){
        printf("Heap Empty");
        return 1;
    }else return 0;
}
void FreeHeap(Heap h){
    free(h->Data);
    free(h);
}
void PrintHeap(Heap h){
    int i;
    for(i=1;i<=h->Size;i++){
        printf("%d ", h->Data[i]);
    }
    printf("\n");
}

// MaxHeap
Heap CreateMaxHeap(int N){
    Heap h = (Heap)malloc(sizeof(struct HeapStruct));
    h->Data = (int*)malloc((N+1)*sizeof(int));
    h->Data[0] = MAXVAL;
    h->Size = 0;
    h->MaxSize = N;
    return h;
}
void InsertMaxHeap(MaxHeap h, ElementType val){
    int i = ++h->Size;
    while(h->Data[i/2] < val){
        h->Data[i] = h->Data[i/2];
        i/=2;
    }
    h->Data[i] = val;
}
ElementType DeleteMaxHeap(MaxHeap h){
    if(IsEmpty(h)) return Null;
    ElementType ret = h->Data[1];
    ElementType last = h->Data[h->Size--];
    int parent = 1;
    while(parent*2<=h->Size){
        int child = parent*2;
        if(child!=h->Size && h->Data[child+1] > h->Data[child]) child++;
        if(last >= h->Data[child]) break;
        else h->Data[parent] = h->Data[child];
        parent=child;
    }
    h->Data[parent] = last;
    return ret;
}
MaxHeap CreateMaxHeap_fromSeq(ElementType seq[], int N){
    MaxHeap h = CreateMaxHeap(N);
    int i;
    for(i=0;i<N;i++){
        InsertMaxHeap(h, seq[i]);
    }
    return h;
}


// MinHeap
Heap CreateMinHeap(int N){
    Heap h = (Heap)malloc(sizeof(struct HeapStruct));
    h->Data = (int*)malloc((N+1)*sizeof(int));
    h->Data[0] = MINVAL;
    h->Size = 0;
    h->MaxSize = N;
    return h;
}
void InsertMinHeap(MinHeap h, ElementType val){
    int i = ++h->Size;
    while(h->Data[i/2] > val){
        h->Data[i] = h->Data[i/2];
        i/=2;
    }
    h->Data[i] = val;
}
ElementType DeleteMinHeap(MinHeap h){
    if(IsEmpty(h)) return Null;
    ElementType ret = h->Data[1];
    ElementType last = h->Data[h->Size--];
    int parent = 1;
    while(parent*2<=h->Size){
        int child = parent*2;
        if(child!=h->Size && h->Data[child+1] < h->Data[child]) child++;
        if(last <= h->Data[child]) break;
        else h->Data[parent] = h->Data[child];
        parent=child;
    }
    h->Data[parent] = last;
    return ret;
}
MinHeap CreateMinHeap_fromSeq(ElementType seq[], int N){
    MinHeap h = CreateMinHeap(N);
    int i;
    for(i=0;i<N;i++){
        InsertMinHeap(h, seq[i]);
    }
    return h;
}