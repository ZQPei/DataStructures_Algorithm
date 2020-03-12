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

#include <cstdio>

#define DEBUG 0


int* GetInput(int length){
    if(length<=0)
        return nullptr;

    int *data = new int[length];

    for(int i=0;i<length;++i){
        scanf("%d", data+i);
    }

    if(DEBUG){
        printf("%u\n",length);
        for(int i=0;i<length;++i){
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    return data;
}


long GetMaxSubseqSum(int *data, int length, int &seq_left, int &seq_right){
    if(data == nullptr || length<=0){
        return 0;
    }

    long max_sum=0, tmp_sum=0;
    int max_pos_left = 0, max_pos_right = 0;
    int tmp_pos_left = 0, tmp_pos_right = 0;
    bool all_negtive = true;

    for(int i=0;i<length;++i){
        tmp_sum += data[i];
        tmp_pos_right = i;

        if(tmp_sum>max_sum){
            max_sum = tmp_sum;
            max_pos_left = tmp_pos_left;
            max_pos_right = tmp_pos_right;
        }
        else if(tmp_sum<0){
            tmp_sum = 0;
            tmp_pos_left = i+1;
        }

        if(data[i]>=0)
            all_negtive = false;
    }

    if(max_sum>0){
        seq_left = data[max_pos_left];
        seq_right = data[max_pos_right];
    }
    else if(max_sum==0){
        seq_left = 0;
        seq_right = 0;
    }
    
    if(all_negtive){
        seq_left = data[0];
        seq_right = data[length-1];
    }

    return max_sum;
}


int main(){
    int K=0;
    scanf("%d", &K);
    int *data = GetInput(K);
    int seq_left=0, seq_right=0;

    long max_sum = GetMaxSubseqSum(data, K, seq_left, seq_right);
    printf("%ld %d %d",max_sum, seq_left, seq_right);
    
    delete []data;
    return 0;
}
