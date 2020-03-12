/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1010077619738988546

本题要求实现二分查找算法。

函数接口定义：
Position BinarySearch( List L, ElementType X );
其中List结构定义如下：

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; //保存线性表中最后一个元素的位置
};
L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递增有序的。函数BinarySearch要查找X在Data中的位置，即数组下标（注意：元素从下标1开始存储）。找到则返回下标，否则返回一个特殊的失败标记NotFound。


输入样例1：
5
12 31 55 89 101
31
输出样例1：
2
输入样例2：
3
26 78 233
31
输出样例2：
0
*/

/*
算法的时间复杂度为O(logN)

二分查找的前提条件：
1. 存储方式为顺序存储，不能是链式存储！
2. 数据是有序的！
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
void FreeList(List L);
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    FreeList(L);
    return 0;
}

List ReadInput(){
    int N;
    int i;
    ElementType tmp;
    List L = (List)malloc(sizeof(struct LNode));
    scanf("%d",&N);
    L->Last = N;  // Last表示线性表的长度
    for(i=0;i<N;i++){
        scanf("%d", &tmp);
        L->Data[i+1] = tmp;
    }
    // for(i=0;i<L->Last;i++){
    //     printf("%d ",L->Data[i]);
    // }
    return L;
}

void FreeList(List L){
    free(L);
}


/* 你的代码将被嵌在这里 */
Position BinarySearch( List L, ElementType X ){
    Position left = 1, right = L->Last;
    Position pos = NotFound;

    while(right >= left){
        Position mid = (left + right) / 2;
        if(L->Data[mid] == X){
            pos = mid;
            break;
        }
        else if(L->Data[mid] > X){
            right = mid-1;
        }
        else if(L->Data[mid] < X){
            left = mid+1;
        }
    }

    return pos;
}