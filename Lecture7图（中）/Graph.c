/*
图的邻接矩阵实现
*/

#include "Graph.h"

#include <stdio.h>
#include <stdlib.h>


Edge CreateEdge(Vertex V1, Vertex V2, WeightType W){
    Edge e = (Edge)malloc(sizeof(struct _edge));
    e->V1 = V1;
    e->V2 = V2;
    e->Weight = W;
    return e;
}
Edge FreeEdge(Edge e){
    free(e);
    return NULL;
}


Graph CreateGraph(int VertexNum){
    Graph g = (Graph)malloc(sizeof(struct _graph));
    int i,j;
    for(i=0;i<VertexNum;i++){
        for(j=0;j<VertexNum;j++){
            g->Weight[i][j] = INFINITY;
        }
    }
    g->VertexNum = VertexNum;
    g->EdgeNum = 0;

    return g;
}
Graph FreeGraph(Graph g){
    free(g);
    return NULL;
}
void PrintGraph(Graph g){
    int i,j;
    for(i=0;i<g->VertexNum;i++){
        for(j=0;j<g->VertexNum;j++){
            if(g->Weight[i][j]==INFINITY) printf("%4s ", "INF");
            else printf("%4d ", g->Weight[i][j]);
        }
        printf("\n");
    }
}
void InsertEdge(Graph g, Edge e, int isDirected){
    if(!isDirected){                    //如果是无向边
        g->Weight[e->V1][e->V2] = e->Weight;
        g->Weight[e->V2][e->V1] = e->Weight;
    }else{
        g->Weight[e->V1][e->V2] = e->Weight;
    }
    g->EdgeNum++;
}
void InsertEdgeFromRaw(Graph g, Vertex V1, Vertex V2, WeightType W, int isDirected){
    if(!isDirected){                    //如果是无向边
        g->Weight[V1][V2] = W;
        g->Weight[V2][V1] = W;
    }else{
        g->Weight[V1][V2] = W;
    }
    g->EdgeNum++;
}

int gragh_main(int argc, char const *argv[])
{
    Graph g = CreateGraph(10);
    PrintGraph(g);
    return 0;
}
