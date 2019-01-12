/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1058181230028419073

10-排序5 PAT Judge （25 分）
The ranklist of PAT is generated from the status list, which shows the scores of the submissions. This time you are supposed to generate the ranklist for PAT.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 positive integers, N (≤10
​4
​​ ), the total number of users, K (≤5), the total number of problems, and M (≤10
​5
​​ ), the total number of submissions. It is then assumed that the user id's are 5-digit numbers from 00001 to N, and the problem id's are from 1 to K. 
The next line contains K positive integers p[i] (i=1, ..., K), where p[i] corresponds to the full mark of the i-th problem. Then M lines follow, each gives the 
information of a submission in the following format:

user_id problem_id partial_score_obtained
where partial_score_obtained is either −1 if the submission cannot even pass the compiler, or is an integer in the range [0, p[problem_id]]. All the numbers in a line 
are separated by a space.

Output Specification:
For each test case, you are supposed to output the ranklist in the following format:

rank user_id total_score s[1] ... s[K]
where rank is calculated according to the total_score, and all the users with the same total_score obtain the same rank; and s[i] is the partial score obtained for the 
i-th problem. If a user has never submitted a solution for a problem, then "-" must be printed at the corresponding position. If a user has submitted several solutions 
to solve one problem, then the highest score will be counted.

The ranklist must be printed in non-decreasing order of the ranks. For those who have the same rank, users must be sorted in nonincreasing order according to the number 
of perfectly solved problems. And if there is still a tie, then they must be printed in increasing order of their id's. For those who has never submitted any solution 
that can pass the compiler, or has never submitted any solution, they must NOT be shown on the ranklist. It is guaranteed that at least one user can be shown on the 
ranklist.

Sample Input:
7 4 20
20 25 25 30
00002 2 12
00007 4 17
00005 1 19
00007 2 25
00005 1 20
00002 2 2
00005 1 15
00001 1 18
00004 3 25
00002 2 25
00005 3 22
00006 4 -1
00001 2 18
00002 1 20
00004 1 15
00002 4 18
00001 3 4
00001 4 2
00005 2 -1
00004 2 0
Sample Output:
1 00002 63 20 25 - 18
2 00005 42 20 0 22 -
2 00007 42 - 25 - 17
2 00001 42 18 18 4 2
5 00004 40 15 0 25 -
*/

/*
该题考查的是 对象或者结构体的 排序
对象或者结构体的排序需要自定义比较函数，再选择一种排序算法
*/

#include <stdio.h>
#include <stdlib.h>

// #define DEBUG
#define MaxProblemNum 5
#define Null -1

typedef struct _status *UserStatus;
struct _status{
    int Id;
    int ProblemNum;
    int FullySolvedProblemNum;
    int SubmitStatus;
    int TotalScore;
    int Score[MaxProblemNum];
};

UserStatus NewUserStatus(int N, int ProblemNum);
void FreeAllUserStatus(UserStatus us);
void ReadOneUserStatus(UserStatus us);
void GetSubmitted(UserStatus us, int N, int MaxScore[], int Submitted[], int *cnt);
int CompareUserStatus(const void * us1, const void * us2);

int main(int argc, char const *argv[])
{
    // 读取数据
    int N,K,M;
    int i,j;
    scanf("%d%d%d", &N,&K,&M);
    int MaxScore[K];
    for(i=0;i<K;i++){
        scanf("%d",MaxScore+i);
    }
    UserStatus us=NewUserStatus(N, K);
    for(i=0;i<M;i++){
        ReadOneUserStatus(us);
    }
    int Submitted[N];
    int cnt=0;
    GetSubmitted(us, N, MaxScore, Submitted, &cnt);

    #ifdef DEBUG
        for(i=0;i<cnt;i++)
            printf("%d ", Submitted[i]);
        printf("\n");
        printf("%d\n", us[4].FullySolvedProblemNum);
    #endif

    // 开始排序，用库自带的快速排序算法
    qsort(us, N, sizeof(struct _status), CompareUserStatus);

    // 输出结果
    int rank=0;
    int rank2=0;
    int lastScore=0;
    for(i=0;i<K;i++)
        lastScore += MaxScore[i];
    for(i=N-1;i>N-1-cnt;i--){
        rank2 ++;
        if(us[i].TotalScore<lastScore){
            lastScore = us[i].TotalScore;
            rank=rank2;
        }
        printf("%d %05d %d", rank, us[i].Id, us[i].TotalScore);
        for(j=0;j<K;j++){
            if(us[i].Score[j]==Null) printf(" -");
            else printf(" %d",us[i].Score[j]);
        }
        printf("\n");
    }

    // 释放内存
    FreeAllUserStatus(us);
    return 0;
}

UserStatus NewUserStatus(int N, int ProblemNum){
    UserStatus us = (UserStatus)malloc(N*sizeof(struct _status));
    int i,j;
    for(i=0;i<N;i++){
        us[i].Id = i+1;
        us[i].ProblemNum = ProblemNum;
        us[i].FullySolvedProblemNum = 0;
        us[i].TotalScore = 0;
        us[i].SubmitStatus=0;
        for(j=0;j<MaxProblemNum;j++){
            us[i].Score[j] = Null;
        }
    }
    return us;
}   
void FreeAllUserStatus(UserStatus us){
    free(us);
}
void ReadOneUserStatus(UserStatus us){
    int user_id,problem_id,partial_score_obtained;
    scanf("%d%d%d", &user_id, &problem_id, &partial_score_obtained);
    if(partial_score_obtained!=Null && partial_score_obtained > us[user_id-1].Score[problem_id-1]){
        us[user_id-1].Score[problem_id-1] = partial_score_obtained;
        us[user_id-1].SubmitStatus = 1;
    }
}
void GetSubmitted(UserStatus us, int N, int MaxScore[], int Submitted[], int *cnt){
    int i,j;
    *cnt = 0;
    for(i=0;i<N;i++){
        if(us[i].SubmitStatus){
            Submitted[(*cnt)++]=i;
            us[i].TotalScore = 0;
            us[i].FullySolvedProblemNum = 0;
            for(j=0;j<us[i].ProblemNum;j++){
                if(us[i].Score[j]>Null)
                    us[i].TotalScore += us[i].Score[j];
                if(us[i].Score[j]==MaxScore[j])
                    us[i].FullySolvedProblemNum ++;
            }
        }
    }
}
int CompareUserStatus(const void * us1, const void * us2){
    int ret;
    if(((UserStatus)us1)->TotalScore>((UserStatus)us2)->TotalScore)
        ret=1;
    else if(((UserStatus)us1)->TotalScore<((UserStatus)us2)->TotalScore)
        ret=-1;
    else{
        if(((UserStatus)us1)->FullySolvedProblemNum>((UserStatus)us2)->FullySolvedProblemNum)
            ret=1;
        else if(((UserStatus)us1)->FullySolvedProblemNum<((UserStatus)us2)->FullySolvedProblemNum)
            ret=-1;
        else{
            if(((UserStatus)us1)->Id<((UserStatus)us2)->Id)
                ret = 1;
            else
                ret = -1;
        }
    }
    return ret;
}
