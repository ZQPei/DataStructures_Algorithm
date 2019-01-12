/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1055646802513190912

09-排序1 排序 （25 分）
给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。

本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：只有1个元素；
数据2：11个不相同的整数，测试基本正确性；
数据3：103个随机整数；
数据4：104个随机整数；
数据5：105个随机整数；
数据6：105个顺序整数；
数据7：105个逆序整数；
数据8：105个基本有序的整数；
数据9：105个随机正整数，每个数字不超过1000。
输入格式:
输入第一行给出正整数N（≤10
​5
​​ ），随后一行给出N个（长整型范围内的）整数，其间以空格分隔。

输出格式:
在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。

输入样例:
11
4 981 10 -17 0 -20 29 50 8 43 -5
输出样例:
-20 -17 -5 0 4 8 10 29 43 50 981
*/

#include <stdio.h>
#include "Sort.h"

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d",&N);
    int A[N];
    int i;
    for(i=0;i<N;i++){
        scanf("%d", A+i);
    }
    // Shell_Sort(A, N);
    // Hibbard_Shell_Sort(A, N);
    // Sedgewick_Shell_Sort(A, N);
    // Selection_Sort(A, N);
    // Heap_Sort(A, N);
    // Merge_Sort_Recursive(A, N);
    Merge_Sort_NonRecursive(A, N);
    PrintArr(A, N);
    return 0;
}
