/*
原题链接:https://pintia.cn/problem-sets/1010070491934568448/problems/1048028714800685058

06-图3 六度空间 （30 分）
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，
最多通过五个人你就能够认识任何一个陌生人。”如图1所示。


图1 六度空间示意图
“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究具有太大的局限性和困难。
随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10^​4，表示人数）、边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号
（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
*/

/*
思路：
广度优先搜索，深度为6

考虑用邻接表实现图，邻接表用链表实现
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define DEBUG 0
#define MAXN 10000     //最大顶点数
#define MAXE 33*MAXN   //最大边数

typedef int Vertex;

typedef struct _graph *LGraph;
struct _graph{
    List *Head; //顶点链表表头
    int VertexNum; //顶点数
    int EdgeNum; //边数
    int *Visited;
};

LGraph CreateGraph( int VertexNum );
void FreeGraph(LGraph g);
void ResetGraph(LGraph g);
void InsertEdge( LGraph g, Vertex A, Vertex B );
LGraph BuildGraph( int VertexNum, int EdgeNum);
void PrintGraph(LGraph g);
int CountNumOfSixDimention(LGraph g, Vertex A);

int main(int argc, char const *argv[])
{
    int N,E;
    scanf("%d %d", &N, &E);
    // 读取并建立图
    LGraph g = BuildGraph(N, E);

    // 计算每个顶点深度为6的点的个数，采用广度优先遍历
    int i;
    for(i=0;i<g->VertexNum;i++){
        Vertex V = i+1;
        // printf("%d\n",CountNumOfSixDimention(g, V));
        printf("%d: %2.02f%%\n", V, 100.0*CountNumOfSixDimention(g, V)/g->VertexNum);
    }
    return 0;
}

LGraph CreateGraph( int VertexNum ){
    LGraph g=(LGraph)malloc(sizeof(struct _graph));
    g->Head = (List *)malloc(VertexNum*sizeof(List));
    g->Visited = (int*)malloc(VertexNum*sizeof(int));
    int i;
    for(i=0;i<VertexNum;i++){
        g->Head[i] = CreateNode(i+1);
        g->Visited[i] = 0;
    }
    g->VertexNum = VertexNum;
    g->EdgeNum = 0;
    return g;
}
void FreeGraph(LGraph g){
    int i;
    for(i=0;i<g->VertexNum;i++){
        FreeList(g->Head[i]);
    }
    free(g->Head);
    free(g->Visited);
    free(g);
}
void ResetGraph(LGraph g){
    int i;
    for(i=0;i<g->VertexNum;i++){
        g->Visited[i] = 0;
    }
}
void InsertEdge( LGraph g, Vertex A, Vertex B ){
    int idxA = A-1;
    int idxB = B-1;
    InsertList(g->Head[idxA], B);
    InsertList(g->Head[idxB], A);
    g->EdgeNum++;
}
LGraph BuildGraph( int VertexNum, int EdgeNum){
    LGraph g = CreateGraph(VertexNum);
    int i;
    Vertex A,B;
    for(i=0;i<EdgeNum;i++){
        scanf("%d %d",&A, &B);
        InsertEdge(g, A, B);
    }
    if(DEBUG) PrintGraph(g);
    return g;
}
void PrintGraph(LGraph g){
    int i;
    for(i=0;i<g->VertexNum;i++){
        PrintList(g->Head[i]);
    }
}
int CountNumOfSixDimention(LGraph g, Vertex A){
    /*
    涉及到如何计算广度优先搜索的层数！！！
    */
    ResetGraph(g);
    int idxA = A-1;
    int cnt = 0;
    int depth = 0;
    Vertex depthFlag=Null;
    Queue q = CreateQueue();
    EnQueue(q, A);
    g->Visited[idxA] = 1;
    cnt++;
    if(DEBUG) printf("%d ",A);
    EnQueue(q, depthFlag);
    while(!IsEmptyQueue(q) && depth < 6){
        Vertex V=DeQueue(q);
        if(V==Null){
            //如果遇到了depthFlag， 则深度加一
            depth ++;
            EnQueue(q, depthFlag);
            continue;
        }

        int idxV = V-1;
        Node curr = g->Head[idxV];
        while(curr){
            Vertex W=curr->Val;
            int idxW = W-1;
            if(!g->Visited[idxW]){
                EnQueue(q, W);
                g->Visited[idxW] = 1;
                cnt++;
                if(DEBUG) printf("%d ",W);
            }
            curr = curr->Next;
        }
    }
    if(DEBUG) printf("\n");
    FreeQueue(q);
    return cnt;
}
