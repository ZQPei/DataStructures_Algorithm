/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1058181230028419072

10-排序4 统计工龄 （20 分）
给定公司N名员工的工龄，要求按工龄增序输出每个工龄段有多少员工。

输入格式:
输入首先给出正整数N（≤10
​5
​​ ），即员工总人数；随后给出N个整数，即每个员工的工龄，范围在[0, 50]。

输出格式:
按工龄的递增顺序输出每个工龄的员工个数，格式为：“工龄:人数”。每项占一行。如果人数为0则不输出该项。

输入样例:
8
10 2 0 5 7 2 5 2
输出样例:
0:1
2:3
5:2
7:1
10:1
*/

/*
考虑用桶排序
因为M=50, N接近10^5， N>>M
所以时间复杂度为 O（N）
*/

#include <stdio.h>

#define MaxVal 51  //最大工龄为 50

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    // 读取数据
    int A[N];
    int i;
    for(i=0;i<N;i++){
        scanf("%d", A+i);
    }

    // 桶排序
    int Bucket[MaxVal];
    for(i=0;i<MaxVal;i++){
        Bucket[i] =0;
    }

    for(i=0;i<N;i++){
        Bucket[A[i]] ++;
    }

    // 输出结果
    for(i=0;i<MaxVal;i++){
        if(Bucket[i]){
            printf("%d:%d\n", i, Bucket[i]);
        }
    }

    return 0;
}
