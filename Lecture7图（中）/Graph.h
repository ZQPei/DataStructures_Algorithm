/*
邻接矩阵图的定义及基本操作的实现
实现在 Graph.c中
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#define MaxVertexNum 10001 //不能太大，不然会栈溢出！！！
#define INFINITY 10001     // 不存在的边用 INFINITY 表示
#define Null -1 

#define WeightType int
#define DataType int
#define Vertex int

typedef struct _edge *Edge;
struct _edge{
    Vertex V1, V2;    //代表图中顶点的下标，可以代表有向边，也可以代表无向边
    WeightType Weight;
};
Edge CreateEdge(Vertex V1, Vertex V2, WeightType W);
Edge FreeEdge(Edge e);

typedef struct _graph *Graph;
struct _graph{
    WeightType Weight[MaxVertexNum][MaxVertexNum];
    int VertexNum;
    int EdgeNum;
    // DataType Data[MaxVertexNum]; // 存储N个顶点的数据
};
Graph CreateGraph(int VertexNum);
Graph FreeGraph(Graph g);
void PrintGraph(Graph g);
void InsertEdge(Graph g, Edge e, int isDirected);                                       //isDirected 表示是否无向边
void InsertEdgeFromRaw(Graph g, Vertex V1, Vertex V2, WeightType W, int isDirected);    //isDirected 表示是否无向边


#endif //GRAPH_H_
