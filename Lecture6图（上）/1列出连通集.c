/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1048028714800685056

06-图1 列出连通集 （25 分）
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:
按照"{ v1 v2 ... vk }"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
*/

/*
用邻接矩阵来表示图，邻接矩阵为二维数组，在此不考虑稀疏性
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define DEBUG 1
#define MAXN 10

typedef int Vertex;

typedef struct GMatrix *MGraph;
struct GMatrix{
    int G[MAXN][MAXN];
    int N; //顶点数
    int E; //边数
    int Visited[MAXN]; // 标记某个点是否被访问过
};

MGraph CreateGraph(int N);
void FreeGraph(MGraph g);
void InsertGraph(MGraph g, Vertex V, Vertex W);
MGraph ReadGraph(int N, int E);
void ListComponents(MGraph g, void (*func)(MGraph, Vertex));
void DFS(MGraph g, Vertex V);
void BFS(MGraph g, Vertex V);

int main(int argc, char const *argv[])
{
    int N,E;
    scanf("%d%d",&N,&E);
    MGraph g = ReadGraph(N,E);
    ListComponents(g, DFS);
    ListComponents(g, BFS);
    FreeGraph(g);
    return 0;
}

MGraph CreateGraph(int N){
    Vertex V,W;
    MGraph g = (MGraph)malloc(sizeof(struct GMatrix));
    g->N = N;
    g->E = 0;
    for(V=0;V<N;V++)
        for(W=0;W<N;W++)
            g->G[V][W] = 0;
        g->Visited[V] = 0;
    return g;
}
void FreeGraph(MGraph g){
    free(g);
}
void ResetGraph(MGraph g){
    Vertex V;
    for(V=0;V<g->N;V++){
        g->Visited[V] = 0;
    }
}
void InsertGraph(MGraph g, Vertex V, Vertex W){
    // 无向图
    g->G[V][W] = 1;
    g->G[W][V] = 1;
    g->E++;
}
MGraph ReadGraph(int N, int E){
    Vertex V,W;
    MGraph graph = CreateGraph(N);
    int i;
    for(i=0;i<E;i++){
        scanf("%d%d",&V, &W);
        InsertGraph(graph, V, W);
    }
    return graph;
}
void ListComponents(MGraph g, void (*func)(MGraph, Vertex)){
    /*
    用func指针表示的遍历方式来遍历图并输出图中所有的连通分量
    */
    ResetGraph(g); // 初始化图的Visited都为0

    Vertex V,W;
    for(V=0;V<g->N;V++){
        if(!g->Visited[V]){
            printf("{ ");
            func(g, V);
            printf("}\n");
        }
    }
}
void DFS(MGraph g, Vertex V){ 
    // 递归
    Vertex W;
    printf("%d ",V);
    g->Visited[V] = 1; // 标记V已经读取过了

    for(W=0;W<g->N;W++){
        if(g->G[V][W] && !g->Visited[W]){
            DFS(g, W);
        }
    }
}
void BFS(MGraph g, Vertex V){
    // 非递归，用队列实现
    Vertex W;
    Queue q=CreateQueue();
    EnQueue(q, V);
    printf("%d ", V);
    g->Visited[V] = 1;

    while(!IsEmptyQueue(q)){
        V = DeQueue(q);
        for(W=0;W<g->N;W++){
            if(g->G[V][W] && !g->Visited[W]){
                EnQueue(q, W);
                printf("%d ", W);
                g->Visited[W] = 1;
            }
        }
    }
    FreeQueue(q);
}