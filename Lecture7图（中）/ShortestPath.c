/*
几种最短路径算法的实现

不管是有向图和无向图，算法都相同，区别在于有权和无权
以下有权图均不考虑负边的情况！！！
以下图均用邻接矩阵来实现！！！
邻接矩阵中，不存在通路用 INFINITY 表示！！！

单源表示已知起点求到任意终点的最短路径，源是Source的意思
多源表示任意起点求到任意终点的最短路径

TODO：
1.单源无权图最短路径-->BFS
2.单源有权图最短路径-->Dijkstra
3.多源有权图最短路径-->Floyd
*/

#include <stdio.h>
#include <stdlib.h>

#include "ShortestPath.h"
#include "Graph.h"
#include "utils.h"

/* 邻接矩阵存储 - 无权图的单源最短路算法 */
//采用BFS算法，利用dist和path两个数组来记录距离和中间点，算法的时间复杂度为 O(V+E)
// dist[w] = s到w的最短距离
// dist[s] = 0
// path[w] = s到w路上经过的某顶点
void UnweightedShortestPath(Graph g, int dist[], int path[], Vertex s){
    // 初始化dist 和 path
    Vertex v,w;
    for(v=0;v<g->VertexNum;v++){
        dist[v] = path[v] = Null;
    }
    dist[s] = 0;
    path[s] = Null;
    
    // BFS
    Queue q = CreateQueue();
    EnQueue(q, s);
    while(!IsEmptyQueue(q)){
        v = DeQueue(q);
        for(w=0;w<g->VertexNum;w++){
            if(dist[w]==Null && g->Weight[v][w]!=INFINITY){
                // dist[w]为Null 表示该点未被访问过
                dist[w] = dist[v]+1;
                path[w] = v;
                EnQueue(q, w);
            }
        }
    }
    FreeQueue(q);
}

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
// Bijkstra算法，时间复杂度为 O(V^2+E)
Vertex FindMinDist(Graph g, int dist[], int corrected[]){
    /* 返回未被收录顶点中dist最小者 */
    Vertex v, minV;
    int minDist = INFINITY;
    for(v=0;v<g->VertexNum;v++){
        if(corrected[v]==0 && dist[v]<minDist){
            minDist = dist[v];
            minV = v;
        }
    }
    if(minDist < INFINITY) return minV;
    else return Null;
}
int Bijkstra(Graph g, int dist[], int path[], Vertex s){
    // 初始化 dist path collected
    // corrected 表示已确定最短路径的顶点
    int collected[g->VertexNum];
    Vertex v,w;
    for(v=0;v<g->VertexNum;v++){
        collected[v] = 0;
        dist[v] = INFINITY;
        path[v] = Null;
    }
    dist[s] = 0;
    collected[s] = 1;

    while(1){
        v = FindMinDist(g, dist, collected);
        if(v==Null)
            break;
        for(w=0;w<g->VertexNum;w++){
            if(collected[w]==0 && g->Weight[v][w]<INFINITY){
                if(g->Weight[v][w] < 0){ // 如果存在负边，则返回错误
                    return 0;
                }
                if(dist[v] + g->Weight[v][w] < dist[w]){
                    dist[w] = dist[v] + g->Weight[v][w];
                    path[w] = v;
                }
            }
        }
    }
    return 1;
}

/* 邻接矩阵存储 - 多源最短路算法 */
// Floyd算法， 时间复杂度为 O(V^3)
// 默认图中不存在负值圈！！！
int Floyd(Graph g, WeightType (*D)[g->VertexNum], Vertex (*path)[g->VertexNum]){
    Vertex i,j,k;
    // 初始化
    for(i=0;i<g->VertexNum;i++){
        for(j=0;j<g->VertexNum;j++){
            D[i][j] = g->Weight[i][j];
            path[i][j] = Null;
        }
    }

    // Floyd
    for(k=0;k<g->VertexNum;k++){
        for(i=0;i<g->VertexNum;i++){
            for(j=0;j<g->VertexNum;j++){
                if(D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = k;
                    if(i==j && D[i][j]<0) // 存在负值圈
                        return 0;     // 则不能正确解决
                }
            }
        }
    }
    return 1;
}

int ShortestPath_main(int argc, char const *argv[])
{
    // 读入图
    int N,E;
    scanf("%d%d",&N,&E);
    int i;
    Vertex V1,V2;
    WeightType W;
    Graph g = CreateGraph(N);
    for(i=0;i<E;i++){
        scanf("%d %d %d", &V1, &V2, &W);
        InsertEdgeFromRaw(g, V1-1, V2-1, W, 0);
    }
    PrintGraph(g);

    // 多源最短路径算法
    WeightType D[N][N];
    Vertex path[N][N];
    Floyd(g, D, path);
    for(V1=0;V1<g->VertexNum;V1++){
        for(V2=0;V2<g->VertexNum;V2++){
        	if(V1==V2) printf(" INF ");
            else printf("%4d ", D[V1][V2]);
        }
        printf("\n");
    }

    FreeGraph(g);
    
    return 0;
}
