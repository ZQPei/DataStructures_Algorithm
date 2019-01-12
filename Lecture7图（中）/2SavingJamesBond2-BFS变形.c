/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1050401612970643457

07-图5 Saving James Bond - Hard Version （30 分）
This time let us consider the situation in the movie "Live and Let Die" in which James Bond, the world's most famous spy, was captured by a group of drug dealers. 
He was sent to a small piece of land at the center of a lake filled with crocodiles. There he performed the most daring action to escape -- he jumped onto the head of 
the nearest crocodile! Before the animal realized what was happening, James jumped again onto the next big head... Finally he reached the bank before the last crocodile 
could bite him (actually the stunt man was caught by the big mouth and barely escaped with his extra thick boot).

Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) and the northeast corner at (50,50). The central island is a disk 
centered at (0,0) with the diameter of 15. A number of crocodiles are in the lake at various positions. Given the coordinates of each crocodile and the distance 
that James could jump, you must tell him a shortest path to reach one of the banks. The length of a path is the number of jumps that James has to make.

Input Specification:
Each input file contains one test case. Each case starts with a line containing two positive integers N (≤100), the number of crocodiles, and D, the maximum distance 
that James could jump. Then N lines follow, each containing the (x,y) location of a crocodile. Note that no two crocodiles are staying at the same position.

Output Specification:
For each test case, if James can escape, output in one line the minimum number of jumps he must make. Then starting from the next line, output the position (x,y) 
of each crocodile on the path, each pair in one line, from the island to the bank. If it is impossible for James to escape that way, simply give him 0 as the number 
of jumps. If there are many shortest paths, just output the one with the minimum first jump, which is guaranteed to be unique.

Sample Input 1:
17 15
10 -21
10 21
-40 10
30 -50
20 40
35 10
0 -10
-25 22
40 -40
-30 30
-10 22
0 11
25 21
25 10
10 10
10 35
-30 10
Sample Output 1:
4
0 11
10 21
10 35
Sample Input 2:
4 13
-12 12
12 12
-12 -12
12 -12
Sample Output 2:
0
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define DEBUG 0
#define MAXN 100
#define ASHORE 50
#define RADIUS 7.5

typedef struct _point *Point;
struct _point{
    double x;
    double y;
};

double GetSquareDistance(Point A, Point B); //计算A到B点的距离的平方
int CanJumpToB(Point A, Point B, double MaxDistance); //是否能从A跳到B
double Absolute(double v); // 计算绝对值
int CanJumpToShore(Point A, double MaxDistance); // 是否能跳到岸上

int main(int argc, char const *argv[])
{
    int N;
    double D;
    int i;
    scanf("%d %lf", &N, &D);

    // 读取所有的鳄鱼坐标
    Point pts = (Point)malloc((N+1)*sizeof(struct _point));
    int *dist = (int*)malloc((N+1)*sizeof(int));
    int *path = (int*)malloc((N+1)*sizeof(int));
    pts[0].x = pts[0].y= 0; // i=0 作为起点
    dist[0] = 0;
    path[0] = Null;
    for(i=1;i<=N;i++){
        scanf("%lf %lf", &pts[i].x, &pts[i].y);
        dist[i] = Null;
        path[i] = Null;
    }

    // BFS
    int escapeIdx=Null;
    Queue q = CreateQueue(); // 堆栈用来保存点在pts中的id
    for(i=1;i<=N;i++){
        if(CanJumpToB(pts, pts+i, D+RADIUS)){
            EnQueue(q, i);
            dist[i] = 1;
            path[i] = 0;
        }
    }
    while(!IsEmptyQueue(q)){
        int currIdx = DeQueue(q);
        if(CanJumpToShore(pts+currIdx, D)){  //检查是否可以跳到岸上
            escapeIdx = currIdx;
            break;
        }

        for(i=0;i<N;i++){
            if(dist[i]==Null && CanJumpToB(pts+currIdx, pts+i, D)){
                EnQueue(q, i);
                dist[i] = dist[currIdx]+1;
                path[i] = currIdx;
            }
        }
    }
    FreeQueue(q);
    if(DEBUG){
        for(i=0;i<N;i++){
            printf("%d ", dist[i]);
        }
        printf("\n");
    }

    // 输出结果， 利用 stack 来反向输出
    if(escapeIdx!=Null){ //成功逃出
        printf("%d\n", dist[escapeIdx]+1);
        Stack s = CreateStack();
        int idx = escapeIdx;
        while(idx!=0){
            PushStack(s, idx);
            idx = path[idx];
        }

        while(!IsEmptyStack(s)){
            idx = PopStack(s);
            printf("%.0lf %.0lf\n", pts[idx].x, pts[idx].y);
        }
        FreeStack(s);
    }else{
        printf("0\n");
    }
    return 0;
}


double GetSquareDistance(Point A, Point B){
    return (A->x-B->x)*(A->x-B->x)+(A->y-B->y)*(A->y-B->y);
}
int CanJumpToB(Point A, Point B, double MaxDistance){
    if(GetSquareDistance(A,B) <= MaxDistance*MaxDistance) return 1;
    else return 0;
}
double Absolute(double v){
    return v>=0 ? v : -v;
}
int CanJumpToShore(Point A, double MaxDistance){
    if(ASHORE-Absolute(A->x)<=MaxDistance || ASHORE-Absolute(A->y)<=MaxDistance) return 1;
    else return 0;
}
