/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1045492157317296128

05-树7 堆中的路径 （25 分）
将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。

输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，行末不得有多余空格。

输入样例:
5 3
46 23 26 24 10
5 4 3
输出样例:
24 23 10
46 23 10
26 10
*/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0
#define MAXSIZE 1000
#define MINVAL -10001
#define MAXVAL 10001

struct HeapStruct{
    int *Data;
    int Size;
    int MaxSize;
};
typedef struct HeapStruct *MinHeap;
typedef MinHeap Heap;

MinHeap CreateMinHeap();
MinHeap ReadMinHeap(int M);
void InsertMinHeap(MinHeap h, int val);
int IsHeapFull(Heap h);
int IsHeapEmpty(Heap h);
void PrintHeap(Heap h);
void PrintToRoot(Heap h, int idx);
void FreeHeap(Heap h);

int main(int argc, char const *argv[])
{
    int N,M;
    scanf("%d%d", &N, &M);
    MinHeap h = ReadMinHeap(N);
    int i, idx;
    for(i=0;i<M;i++){
        scanf("%d", &idx);
        PrintToRoot(h, idx); printf("\n");
    }
    FreeHeap(h);
    return 0;
}
MinHeap CreateMinHeap(){
    MinHeap h = (MinHeap)malloc(sizeof(struct HeapStruct));
    h->Data = (int*)malloc(MAXSIZE*sizeof(int));
    h->Data[0] = MINVAL;
    h->Size = 0;
    h->MaxSize = MAXSIZE;
    return h;
}
MinHeap ReadMinHeap(int M){
    MinHeap h = CreateMinHeap();
    int i, val;
    for(i=0;i<M;i++){
        scanf("%d", &val);
        InsertMinHeap(h, val);
        if(DEBUG) PrintHeap(h);
    }
    return h;
}
int IsHeapFull(Heap h){
    if(h->Size==h->MaxSize){
        printf("Heap full");
        return 1;
    }else return 0;
}
int IsHeapEmpty(Heap h){
    if(h->Size==0){
        printf("Heap empty");
        return 1;
    }else return 0;
}
void InsertMinHeap(MinHeap h, int val){
    if(IsHeapFull(h)) return;

    int i = ++h->Size;
    while(h->Data[i/2] > val){
        h->Data[i] = h->Data[i/2];
        i/=2;
    }
    h->Data[i] = val;
}
void PrintHeap(Heap h){
    int i;
    for(i=1;i<=h->Size;i++){
        printf("%d ",h->Data[i]);
    }
    printf("\n");
}
void PrintToRoot(Heap h, int idx){
    int i=idx;
    int isFirst = 1;
    while(i){
        if(isFirst){
            printf("%d", h->Data[i]);
            isFirst=0;
        }else printf(" %d",h->Data[i]);
        i/=2;
    }
}
void FreeHeap(Heap h){
    free(h->Data);
    free(h);
}