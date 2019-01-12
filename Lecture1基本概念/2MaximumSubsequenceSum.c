/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1010077619738988545

01-复杂度2 Maximum Subsequence Sum （25 分）
Given a sequence of K integers  where 1≤i≤j≤K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. 
For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

Input Specification:
Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (≤10000). The second line contains K numbers, 
separated by a space.

Output Specification:
For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. 
The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the 
smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first 
and the last numbers of the whole sequence.

Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21
Sample Output:
10 1 4
*/

#include <stdio.h>

#define MAXSIZE 100000

typedef struct result Result;
struct result{
    int maxSum;
    int first;
    int last;
};

void readList(int List[], int K){
    int i;
    for(i=0;i<K;i++){
        scanf("%d", &List[i]);
    }
}

Result getMaxSubSum(int List[], int K){
    /*
    时间复杂度O(N)
    */
    int i;
    int tmpSum=0;
    int tmpfirst=0;
    Result res = {  .maxSum=0, 
                    .first=0, 
                    .last=K-1};
    for(i=0;i<K;i++){
        tmpSum += List[i];
        if(tmpSum>res.maxSum){
            res.maxSum = tmpSum;
            res.first = tmpfirst;
            res.last = i;
        }else if(tmpSum<0){
            tmpSum = 0;
            tmpfirst = i+1;
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int K;
    int List[MAXSIZE] = {0,};
    scanf("%d", &K);
    readList(List, K);
    Result res = getMaxSubSum(List, K);
    printf("Maximum subsequence sum = %d, in range [%d,%d]\n",res.maxSum, res.first, res.last);
    return 0;
}