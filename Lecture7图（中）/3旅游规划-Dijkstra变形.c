/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1050401612970643458

07-图6 旅游规划 （25 分）
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。
如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。
随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "ShortestPath.h"
#include "utils.h"

#define DEBUG 0
#define MAXVERTEXNUM 500
#define MAXWEIGHT 500

int BijkstraWithAssist(Graph gMain, Graph gAssist, int distMain[], int distAssist[], int path[], Vertex s);

int main(int argc, char const *argv[])
{
    // 读取输入
    int N,M;    //N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数
    Vertex S,D; //S是出发地的城市编号；D是目的地的城市编号
    scanf("%d%d%d%d", &N,&M,&S,&D);
    Graph g_mile = CreateGraph(N);  //用于保存距离信息的图
    Graph g_price = CreateGraph(N); //用于保存收费信息的图
    int i;
    int V1,V2, mile, price;
    for(i=0;i<M;i++){
        scanf("%d%d%d%d", &V1,&V2,&mile,&price);
        InsertEdgeFromRaw(g_mile, V1, V2, mile, 0);
        InsertEdgeFromRaw(g_price, V1, V2, price, 0);
    }

    // Bijkstra
    int dist_mile[N];
    int dist_price[N];
    int path[N];
    BijkstraWithAssist(g_mile, g_price, dist_mile, dist_price, path, S);
    if(DEBUG){
        for(i=0;i<N;i++)
            printf("%d ", dist_mile[i]);
        printf("\n");
        for(i=0;i<N;i++)
            printf("%d ", dist_price[i]);
        printf("\n");
        for(i=0;i<N;i++)
            printf("%d ", path[i]);
        printf("\n");
    }
    
    //输出结果
    printf("%d %d", dist_mile[D], dist_price[D]);
    
    return 0;
}
int BijkstraWithAssist(Graph gMain, Graph gAssist, int distMain[], int distAssist[], int path[], Vertex s){
    // 初始化 dist path collected
    // corrected 表示已确定最短路径的顶点
    int collected[gMain->VertexNum];
    Vertex v,w;
    for(v=0;v<gMain->VertexNum;v++){
    	collected[v] = 0;
        distMain[v] = gMain->Weight[s][v];
        distAssist[v] = gAssist->Weight[s][v];
        if(distMain[v] < INFINITY){
        	path[v] = s;
		}else
        	path[v] = Null;
    }
    distMain[s] = 0;
    distAssist[s] = 0;
    collected[s] = 1;

    while(1){
        v = FindMinDist(gMain, distMain, collected);
        if(v==Null)
            break;
            
        collected[v] = 1;
        for(w=0;w<gMain->VertexNum;w++){
            if(collected[w]==0 && gMain->Weight[v][w]<INFINITY){
                if(gMain->Weight[v][w] < 0){ // 如果存在负边，则返回错误
                    return 0;
                }
                if(distMain[v] + gMain->Weight[v][w] < distMain[w]){
                    distMain[w] = distMain[v] + gMain->Weight[v][w];
                    distAssist[w] = distAssist[v] + gAssist->Weight[v][w];
                    path[w] = v;
                }else if(distMain[v] + gMain->Weight[v][w] == distMain[w] && distAssist[v] + gAssist->Weight[v][w] < distAssist[w]){  
                    // 如果判断相等，则依赖distAssist来辅助判断
                    distMain[w] = distMain[v] + gMain->Weight[v][w];
                    distAssist[w] = distAssist[v] + gAssist->Weight[v][w];
                    path[w] = v;
                }
            }
        }
    }
    return 1;
}
