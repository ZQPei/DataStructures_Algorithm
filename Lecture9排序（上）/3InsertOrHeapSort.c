/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1055646802513190914

09-排序3 Insertion or Heap Sort （25 分）
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result. Then run this method for one more iteration and output in the second line the resulting sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9
*/

#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

void PrintArr(int A[], int N);

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    int initialA[N];
    int partiallySortedA[N];
    int i,j;
    // 读取输入
    for(i=0;i<N;i++){
        scanf("%d", initialA+i);
    }
    for(i=0;i<N;i++){
        scanf("%d", partiallySortedA+i);
    }

    // 判断是何种分类方法
    // 若是插入排序，特点是一开始是有序的，一旦无序了，则必定之后和原序列相同
    int tmp=partiallySortedA[0];
    for(i=1;i<N && partiallySortedA[i]>=tmp ; tmp=partiallySortedA[i], i++ );
    for(j=i; j<N && partiallySortedA[j]==initialA[j] ; j++);

    // 计算下一步的结果
    if(j==N){
        // 是插入排序
        printf("Insertion Sort\n");
        
        int k;
        tmp = partiallySortedA[i];
        for(k=i; k>0 && partiallySortedA[k-1]>tmp;k--){
            partiallySortedA[k] = partiallySortedA[k-1];
        }
        partiallySortedA[k] = tmp;
        PrintArr(partiallySortedA, N);
    }else{
        // 是堆排序
        printf("Heap Sort\n");

        
        int k;
        for(k=1;k<=N && partiallySortedA[k-1] <= partiallySortedA[k/2-1];k++);
        MaxHeap h = CreateMaxHeap(k);
        for(i=0;i<k-1;i++){
            h->Data[i+1] = partiallySortedA[i];
            h->Size++;
        }
        partiallySortedA[k-2] = DeleteMaxHeap(h);
        for(i=0;i<k-2;i++){
            partiallySortedA[i] = h->Data[i+1];
        }
        PrintArr(partiallySortedA, N);
    }
 
    return 0;
}
void PrintArr(int A[], int N){
    int i;
    for(i=0;i<N;i++){
        if(i==0) printf("%d", A[i]);
        else     printf(" %d", A[i]);
    }
    printf("\n");
}
