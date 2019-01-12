/*
题目链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1010077619738988544

01-复杂度1 最大子列和问题 （20 分）
给定K个整数组成的序列，其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。
现要求你编写程序，计算给定整数序列的最大子列和。

本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：与样例等价，测试基本正确性；
数据2：10^2个随机整数；
数据3：10^3个随机整数；
数据4：10^4个随机整数；
数据5：10^5个随机整数；
输入格式:
输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

输出格式:
在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

输入样例:
6
-2 11 -4 13 -5 -2
输出样例:
20

*/

#include <stdio.h>

#define MAXSIZE 100000

void readList(int List[], int K){
    int i;
    for(i=0;i<K;i++){
        scanf("%d", &List[i]);
    }
}

int getMaxSubSum(int List[], int K){
    /*
    时间复杂度O(N)
    */
    int i;
    int tmpSum=0;
    int maxSum=0;
    for(i=0;i<K;i++){
        tmpSum += List[i];
        if(tmpSum>maxSum){
            maxSum = tmpSum;
        }else if(tmpSum<0){
            tmpSum = 0;
        }
    }
    return maxSum;
}

int main(int argc, char const *argv[])
{
    int K;
    int List[MAXSIZE] = {0,};
    scanf("%d", &K);
    readList(List, K);
    int res = getMaxSubSum(List, K);
    printf("Maximum subsequence sum = %d\n",res);
    return 0;
}
