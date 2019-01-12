/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1055646802513190913

09-排序2 Insert or Merge （25 分）
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element 
from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Merge sort works as follows: Divide the unsorted list into N sublists, each containing 1 element (a list of 1 element is considered sorted). Then repeatedly 
merge two adjacent sublists to produce new sorted sublists until there is only 1 sublist remaining.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting 
method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers are given as the initial 
sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or "Merge Sort" to indicate the method used to obtain the partial result. Then run this method 
for one more iteration and output in the second line the resuling sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line 
must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Sample Output 2:
Merge Sort
1 2 3 8 4 5 7 9 0 6
*/

#include <stdio.h>
#include <stdlib.h>

void PrintArr(int A[], int N);
void Merge(int A[], int tmpA[], int L, int R, int RightEnd);
void Sort_NonRecursive(int A[], int tmpA[], int N, int Length);

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
        // 是归并排序
        printf("Merge Sort\n");

        int k=0;
        int Length=i;
        while(k<N-1){
            for(j=0;j<Length-1 && k<N-1;j++,k++){
                if(partiallySortedA[k+1] < partiallySortedA[k]){
                    k=0;
                    Length/=2;
                    break;
                }
            }
            k+=1;
        }
        // printf("%d", Length);

        if(Length<N){
            Sort_NonRecursive(partiallySortedA, initialA, N, Length);
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
void Merge(int A[], int tmpA[], int L, int R, int RightEnd){
    int i=L,j=R;
    int tmp=L;
    int LeftEnd = R-1;
    while(i<=LeftEnd && j<=RightEnd){
        if(A[i]<A[j])
            tmpA[tmp++] = A[i++];
        else
            tmpA[tmp++] = A[j++];
    }
    while(i<=LeftEnd){
        tmpA[tmp++] = A[i++];
    }
    while(j<=RightEnd){
        tmpA[tmp++] = A[j++];
    }

    for(i=L;i<=RightEnd;i++){
        A[i] = tmpA[i];
    }
}
void Sort_NonRecursive(int A[], int tmpA[], int N, int Length){
    int i,j;
    int L;
    for(L=0;L+2*Length<N;L+=2*Length){
        Merge(A, tmpA, L, L+Length, L+2*Length-1);
    }
    if(L+Length<N){
        // 还多出一个单元
        Merge(A, tmpA, L, L+Length, N-1);
    }
}