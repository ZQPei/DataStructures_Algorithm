/*
堆 Heap
最大堆 MaxHeap
最小堆 MinHeap

引入：
优先队列（Prioity Queue)：特殊的队列，取出元素的顺序是依照元素的优先权大小（值的大小），而不是元素进入队列的先后顺序
如何组织优先队列？
1.数组/链表这种线性表，每次插入元素都需要排好序，插入的时间复杂度是o(N)
2.二叉树 --> 堆

特点：
1.任一结点的关键字是其子树所有结点的最大值(或最小值)  --> 最大堆(最小堆)
2.堆是完全二叉树，所以可以考虑用数组进行存储

抽象数据类型描述：
类型名称：最大堆
数据对象集：完全二叉树，每个结点的元素值不小于其子结点的元素值
操作集：  TODO
1.创建空堆
2.插入
3.删除，并返回最大元素
4.最大堆的建立

*/

/*
这里只实现最大堆，最小堆的实现在 1堆中的路径.c 中
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1001
#define MAXVAL 10001
#define Null -1

struct HeapStruct{
    int *Data;
    int Size;
    int MaxSize;
};
typedef struct HeapStruct *MaxHeap;

//TODO
MaxHeap CreateMaxHeap();
int IsFull(MaxHeap h);
int IsEmpty(MaxHeap h);
void InsertMaxHeap(MaxHeap h, int val);
int DeleteMaxHeap(MaxHeap h);
void FreeMaxHeap(MaxHeap h);
void PrintMaxHeap(MaxHeap h);
MaxHeap CreateMaxHeap_fromSeq(int seq[], int N);

int main(int argc, char const *argv[])
{
    int seq[] = {10,18,25,31,44,58};
    int N = 6;
    MaxHeap h = CreateMaxHeap_fromSeq(seq, N);
    PrintMaxHeap(h);
    int i;
    for(i=0;i<N;i++){
        DeleteMaxHeap(h);
        PrintMaxHeap(h);
    }
    DeleteMaxHeap(h);
    return 0;
}

MaxHeap CreateMaxHeap(){
    MaxHeap h = (MaxHeap)malloc(sizeof(struct HeapStruct));
    h->Data = (int*)malloc(MAXSIZE*sizeof(int));
    h->Data[0] = MAXVAL;
    h->Size = 0;
    h->MaxSize = MAXSIZE;
    return h;
}
int IsFull(MaxHeap h){
    if(h->Size==h->MaxSize){
        printf("Heap full");
        return 1;
    }else return 0;
}
int IsEmpty(MaxHeap h){
    if(h->Size==0){
        printf("Heap Empty");
        return 1;
    }else return 0;
}
void InsertMaxHeap(MaxHeap h, int val){
    int i = ++h->Size;
    while(h->Data[i/2] < val){
        h->Data[i] = h->Data[i/2];
        i/=2;
    }
    h->Data[i] = val;
}
int DeleteMaxHeap(MaxHeap h){
    if(IsEmpty(h)) return Null;
    int ret = h->Data[1];
    int last = h->Data[h->Size--];
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
void FreeMaxHeap(MaxHeap h){
    free(h->Data);
    free(h);
}
void PrintMaxHeap(MaxHeap h){
    int i;
    for(i=1;i<=h->Size;i++){
        printf("%d ", h->Data[i]);
    }
    printf("\n");
}
MaxHeap CreateMaxHeap_fromSeq(int seq[], int N){
    MaxHeap h = CreateMaxHeap();
    int i;
    for(i=0;i<N;i++){
        InsertMaxHeap(h, seq[i]);
    }
    return h;
}
