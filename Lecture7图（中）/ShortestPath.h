#ifndef SHORTEST_PATH_H_
#define SHORTEST_PATH_H_

#include "Graph.h"


void UnweightedShortestPath(Graph g, int dist[], int path[], Vertex s);           // 单源无权图
int Bijkstra(Graph g, int dist[], int path[], Vertex s);                          // 单源有权图
Vertex FindMinDist(Graph g, int dist[], int corrected[]);
int Floyd(Graph g, WeightType (*D)[g->VertexNum], Vertex (*path)[g->VertexNum]);  // 多源有权图

#endif //SHORTEST_PATH_H_