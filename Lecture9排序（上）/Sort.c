/*
排序算法
默认排序是从小到大排序

操作对象：
定义了大小关系的变量类型

输入：
数组头指针，以及数组长度
输出：
void

TODO:
实现不同的排序算法并给出算法的时间复杂度
1.冒泡排序
2.插入排序
3.希尔排序
4.选择排序
5.堆排序
6.归并排序
*/

#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

// #define DEBUG

void Swap(ElementType A[], int i, int j);
void PrintArr(ElementType A[], int N);

/*
冒泡排序 Bubble_Sort
时间复杂度 O(N^2)
*/
void Bubble_Sort(ElementType A[], int N){
    int P, i;
    for(P=N-1;P>=0;P--){
        // 从头开始，当下一个元素比当前元素小，就交换两个元素，每次执行完子循环后，最后一个元素一定是最大的
        for(i=0;i<P;i++){
            if(A[i] > A[i+1])
                Swap(A, i, i+1);
        }
    }
}


/*
插入排序 Insertion_Sort
时间复杂度 O(N^2)
若一个数组基本有序，则插入排序算法简单高效
*/
void Insertion_Sort(ElementType A[], int N){
    int P,i;
    for(P=1;P<N;P++){
        // X 是待插入前面P个元素中的元素，每次插入X后，前面P个元素是有序的
        ElementType X = A[P];
        for(i=P;i>=1 && A[i-1]>X;i--){
            A[i] = A[i-1];
        }
        A[i] = X;
    }
}

/*
希尔排序 Shell_Sort
希尔排序可以看作是插入排序的扩展
时间复杂度 最坏情况O(N^2)
希尔排序时间复杂度不稳定！
*/
// 原始希尔排序
void Shell_Sort(ElementType A[], int N){
    int D, P, i;
    for(D=N/2; D>0; D/=2){ //希尔增量序列是  N/2 N/4 N/8 ... 1
        // for循环中就是距离为D的插入排序， 目的是要对A中距离为D的元素分别排序
        for(P=D;P<N;P++){
            ElementType X = A[P];
            for(i=P;i>=D && A[i-D]>X;i-=D){
                A[i] = A[i-D];
            }
            A[i] = X;
        }
    }
}
// Hibbard 增量序列 希尔排序
void Hibbard_Shell_Sort(ElementType A[], int N){
    // 增量序列是 2^k-1;
    int increment[]={32767,16383,8191,4095,2047,1023,511,255,127,63,31,15,7,3,1,0};
    int D, P, i;
    int k;
    for(k=0; increment[k]>0; k++ ){
        D = increment[k];
        if(D>N) continue;
        for(P=D;P<N;P++){
            ElementType X = A[P];
            for(i=P;i>=D && A[i-D]>X; i-=D){
                A[i] = A[i-D];
            }
            A[i] = X;
        }
    }
}
// Sedgewick增量序列哈希排序 
void Sedgewick_Shell_Sort(ElementType A[], int N){
    // 增量序列如下
    int increment[] = {587521,260609,146305,64769,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1,0};
    int D, P, i;
    int k;
    for(k=0; increment[k]>0; k++ ){
        D = increment[k];
        if(D>N) continue;
        for(P=D;P<N;P++){
            ElementType X = A[P];
            for(i=P;i>=D && A[i-D]>X; i-=D){
                A[i] = A[i-D];
            }
            A[i] = X;
        }
    }
}

/*
选择排序 Selection_Sort
时间复杂度 O(N^2)
*/
void Selection_Sort(ElementType A[], int N){
    int i,j;
    for(i=0;i<N;i++){
        // 每次循环都找到 i~N-1 中的最小值放在最前面，其实也可以用递归实现，但是没必要
        for(j=i;j<N;j++){
            if(A[i]>A[j])
                Swap(A, i, j);
        }
    }
}


/*
堆排序 Heap_Sort
时间复杂度 最坏情况O(NlogN)
堆排序的时间复杂度不稳定
*/
#include "Heap.h"
#ifdef DEBUG
#include "Heap.c"
#endif
void Heap_Sort(ElementType A[], int N){
    MinHeap h = CreateMinHeap(N+1);
    int i;
    for(i=0;i<N;i++){
        InsertMinHeap(h, A[i]);
    }
    for(i=0;i<N;i++){
        A[i] = DeleteMinHeap(h);
    }
    FreeHeap(h);
}


/*
归并排序 Merge_Sort
时间复杂度 O（NlogN)
归并排序非常稳定
*/
// 递归实现
void Merge(ElementType A[], ElementType tmpA[], int L, int R, int RightEnd){
    // 将两个有序序列进行排序，时间复杂度为 O(N)
    // L是左边序列的起点，R是右边序列的起点，RightEnd是右边序列的终点，其中，两个有序序列是连接着的
    int i=L,j=R;
    int tmpIdx=L;
    int LeftEnd = R-1;
    while(i<=LeftEnd && j<=RightEnd){
        if(A[i]<A[j]) 
            tmpA[tmpIdx++] = A[i++];
        else
            tmpA[tmpIdx++] = A[j++];
    }
    while(i<=LeftEnd){
        tmpA[tmpIdx++] = A[i++];
    }
    while(j<=RightEnd){
        tmpA[tmpIdx++] = A[j++];
    }

    // 把 tmpA 拷贝到 A 中
    for(i=L;i<=RightEnd;i++){
        A[i] = tmpA[i];
    }
}
void Sort_Recursive(ElementType A[], ElementType tmpA[], int L, int RightEnd){
    if(RightEnd>L){
        int Mid = (L+RightEnd)/2;
        Sort_Recursive(A, tmpA, L, Mid);
        Sort_Recursive(A, tmpA, Mid+1, RightEnd);
        Merge(A, tmpA, L, Mid+1, RightEnd);
    }
}
void Merge_Sort_Recursive(ElementType A[], int N){
    ElementType tmpA[N];
    Sort_Recursive(A, tmpA, 0, N-1);
}

// 非递归实现
void Merge2(ElementType A[], ElementType tmpA[], int L, int R, int RightEnd){
    // 将两个有序序列进行排序，时间复杂度为 O(N)
    // L是左边序列的起点，R是右边序列的起点，RightEnd是右边序列的终点，其中，两个有序序列是连接着的
    int i=L,j=R;
    int tmpIdx=L;
    int LeftEnd = R-1;
    while(i<=LeftEnd && j<=RightEnd){
        if(A[i]<A[j]) 
            tmpA[tmpIdx++] = A[i++];
        else
            tmpA[tmpIdx++] = A[j++];
    }
    while(i<=LeftEnd){
        tmpA[tmpIdx++] = A[i++];
    }
    while(j<=RightEnd){
        tmpA[tmpIdx++] = A[j++];
    }
    // Merge2 与 Merge的区别在于，Merge2每次执行完后，将结果保存在tmpA中！！！
}
void Sort_NonRecursive(ElementType A[], ElementType tmpA[], int N, int Length){
    // A 中严格按照每 Length 个单元递增！！！
    int L = 0;
    // 每 2*length 两个单元归并 
    for(L=0;L<N-2*Length;L+=2*Length){
        Merge2(A, tmpA, L, L+Length, L+2*Length-1);
    }
    if(L+Length<=N-1){
        // 处理剩余不足两个单元的值 
        Merge2(A, tmpA, L, L+Length, N-1);
    }else{
        // 处理剩余不足一个单元的值 
        int i;
        for(i=L;i<N;i++)
            tmpA[i] = A[i];
    }
}
void Merge_Sort_NonRecursive(ElementType A[], int N){
    ElementType tmpA[N];
    int Length = 1;
    while(Length<N){
        Sort_NonRecursive(A, tmpA, N, Length);
        Length *= 2;
        Sort_NonRecursive(tmpA, A, N, Length);
        Length *= 2;
    }
}


/*
快速排序 Quick_Sort
时间复杂度 最坏 O(N^2)
          平均 O(NlogN)
不稳定
*/
// 递归实现
ElementType GetPivot(ElementType A[], int Left, int Right){
    // 通过取中值的方式找到主元 Pivot
    int Mid = (Left+Right)/2;

    // 通过比较大小，使得  A[Left] <= A[Mid] <= A[Right]
    if(A[Left] > A[Right])
        Swap(A, Left, Right);
    if(A[Left] > A[Mid])
        Swap(A, Left, Mid);
    if(A[Mid] > A[Right])
        Swap(A, Mid, Right);
    
    Swap(A, Mid, Right-1);  // 把主元放在倒数第二个元素的位置，所以只需要考虑 A[Left+1] … A[Right-2]
    return A[Right-1];  
}
void QSort(ElementType A[], int Left, int Right){
    // 核心递归函数
    int Pivot, Cutoff, Low, High;
    Cutoff = 200;
    if(Cutoff <= Right-Left){  /* 如果序列元素充分多，进入快排 */
        Pivot = GetPivot(A, Left, Right);  /* 选基准 */ 
        Low = Left; High = Right-1;
        while(1){  /*将序列中比基准小的移到基准左边，大的移到右边*/
            while(A[--Low] < Pivot);
            while(A[--High]> Pivot);
            if(Low<High)
                Swap(A, Low, High);
            else
                break;
        }
        Swap(A, Low, Right-1);  /* 将基准换到正确的位置 */ 
        QSort(A, Left, Low-1);  /* 递归解决左边 */ 
        QSort(A, Low+1, Right); /* 递归解决右边 */  
    }else{
        /* 元素太少，用简单点的排序算法 */ 
        Insertion_Sort(A+Left, Right-Left+1);
    }
}
void Quick_Sort(ElementType A[], int N){
    /* 统一接口 */
    QSort(A, 0, N-1);
}
// 调用库函数 qsort
int compart2Int(const void *a, const void *b){
    /* 比较两整数。非降序排列 */
    return (*(ElementType*)a - *(ElementType*)b);
}
void Quick_Sort_Stdlib(ElementType A[], int N){
    qsort(A, N, sizeof(ElementType), compart2Int);
}


/*
桶排序 Bucket_Sort
时间复杂度 O(M+N)
稳定
适用于整形序列，且范围是 0~M
M是序列的最大值，N是序列的长度
当M与N接近时，适合用桶排序
*/
void Bucket_Sort(int A[], int N){
    // 找到最大值 M， 认为序列取值范围在 0~M
    int M=0;
    int i,j,k;
    for(i=0;i<N;i++){
        if(A[i]>M)
            M = A[i];
    }

    // 建立一个桶序列
    int Bucket[M+1];
    for(i=0;i<=M;i++){
        Bucket[i] = 0;
    }
    for(i=0;i<N;i++){
        Bucket[A[i]] ++;
    }

    //最后对A进行赋值
    k=0;
    for(i=0;i<=M;i++){
        if(Bucket[i]>0){
            for(j=0;j<Bucket[i];j++)
                A[k++] = i;
        }
    }
}


/*
基数排序 Radix_Sort
时间复杂度 O(P(N+B))
          P是整数的最大位数
          N是序列个数
          B是进制
稳定
适用于整数排序
适用于P较少的情况
低位优先 LSD
*/
#include "List.h"
#ifdef DEBUG
#include "List.c"
#endif
#define Radix 10
int GetDigit(int X, int D){
    /* 默认最低位D=1 */
    int i, d;
    for(i=1;i<=D;i++){
        d = X%Radix;
        X/=Radix;
    }
    return d;
}
int GetMaxDigit(int X){
    // 得到X的位数
    int cnt=0;
    while(X){
        X/=Radix;
        cnt++;
    }
    return cnt;
}
void Radix_Sort_LSD( int A[], int N){
    int MaxDigit=0;
    // 循环一遍得到最高的位数，当然也可以自己设置
    int i, j, P;
    for(i=0;i<N;i++){
        P = GetMaxDigit(A[i]);
        if(P>MaxDigit) MaxDigit = P;
    }

    /* 基数排序 - 次位优先 */
    int D, Di;
    List Bucket[MaxDigit+1][Radix];
    List l=NULL;
    for(i=0;i<=MaxDigit;i++)
        for(j=0;j<Radix;j++)
            Bucket[i][j] = NULL;

    D=1;
    for(i=0;i<N;i++){
        Di = GetDigit(A[i],D);
        Bucket[D][Di] = InsertList(Bucket[D][Di], A[i]);
    }
    for(D=2;D<=MaxDigit;D++){
        List *bd = Bucket[D-1];
        for(i=0;i<Radix;i++){
            List tmpList = bd[i];
            int tmp;
            while(tmpList){
                tmp = tmpList->Data;
                Di = GetDigit(tmp, D);
                Bucket[D][Di] = InsertList( Bucket[D][Di], tmp);
                tmpList=tmpList->Next;
            }
        }
    }
    #ifdef DEBUG // 用于调试输出
		for(D=1;D<=MaxDigit;D++){
			for(i=0;i<Radix;i++){
		        List tmpList = Bucket[D][i];
		        while(tmpList){
		            printf("%d ",tmpList->Data);
		            tmpList=tmpList->Next;
		        }
		        printf("\n");
		    }	
		}	
	}
    #endif
    
    // 把结果拷回A中
    D=MaxDigit;
    int k=0;
    for(i=0;i<Radix;i++){
        List tmpList = Bucket[D][i];
        while(tmpList){
            A[k++] = tmpList->Data;
            tmpList=tmpList->Next;
        }
    }
}



// 用于测试的主函数
int main(int argc, char const *argv[])
{
    int N = 20;
    ElementType A[] = {96, 61, 83, 34, 57, 52,  3,  3, 72, 53,\
                          5, 80, 11, 28, 82, 49, 50, 49, 89,  1};
    // Merge_Sort_NonRecursive(A, N);
    // Quick_Sort(A, N);
    // Quick_Sort_Stdlib(A, N);
    // Bucket_Sort(A, N);
    Radix_Sort_LSD(A, N);
    PrintArr(A, N);
    return 0;
}
void Swap(ElementType A[], int i, int j){
    // 交换A中两个元素，没有安全性检查
    ElementType tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
void PrintArr(ElementType A[], int N){
    int i;
    for(i=0;i<N;i++){
        if(i==0) printf("%d", A[i]);
        else     printf(" %d", A[i]);
    }
    printf("\n");
}
