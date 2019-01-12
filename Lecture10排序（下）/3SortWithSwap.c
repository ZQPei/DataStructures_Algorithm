/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1058181230028419074

10-排序6 Sort with Swap(0, i) （25 分）
Given any permutation of the numbers {0, 1, 2,..., N−1}, it is easy to sort them in increasing order. But what if Swap(0, *) is the ONLY operation that is allowed to use? For example, to sort {4, 0, 2, 1, 3} we may apply the swap operations in the following way:

Swap(0, 1) => {4, 1, 2, 0, 3}
Swap(0, 3) => {4, 1, 2, 3, 0}
Swap(0, 4) => {0, 1, 2, 3, 4}
Now you are asked to find the minimum number of swaps need to sort the given permutation of the first N nonnegative integers.

Input Specification:
Each input file contains one test case, which gives a positive N (≤10
​5
​​ ) followed by a permutation sequence of {0, 1, ..., N−1}. All the numbers in a line are separated by a space.

Output Specification:
For each case, simply print in a line the minimum number of swaps need to sort the given permutation.

Sample Input:
10
3 5 7 2 6 4 9 0 8 1
Sample Output:
9
*/

/*
本题其实是 数环的个数
环有包括单元环和多元环两类
*/

#include <stdio.h>

// #define DEBUG

int GetMinSwapTimes(int A[], int N){
    int collected[N];
    int i;
    for(i=0;i<N;i++)
        collected[i]=0;

    int idx=0;
    int SingleRingNum=0;
    int MultiRingNum=0;
    int IsZeroSingleRing = 0;
    for(idx=0;idx<N ;idx++){
        if(collected[idx]==1){
            continue;
        }
        int tmp=A[idx];
        if(tmp==idx){
            if(idx==0) IsZeroSingleRing = 1;
            SingleRingNum++;
        }else{
            while(tmp!=idx){
                collected[tmp] = 1;
                tmp = A[tmp];
            }
            MultiRingNum++;
        }
    }
    #ifdef DEBUG
        printf("%d %d\n", SingleRingNum, MultiRingNum);
    #endif
    if(!IsZeroSingleRing) //如果0不是独自在一个单元环中
        return N-SingleRingNum+MultiRingNum-2;
    else                  //如果0独自在一个单元环中
        return N-SingleRingNum+MultiRingNum;
}

int main(int argc, char const *argv[])
{
    // 读取数据
    int N;
    scanf("%d", &N);
    int A[N];
    int i;
    for(i=0;i<N;i++){
        scanf("%d", A+i);
    }

    // 排序算法，只能与0交换
    int ret = GetMinSwapTimes(A, N);
    printf("%d",ret);

    return 0;
}


