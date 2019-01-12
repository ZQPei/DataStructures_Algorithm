/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1045492157317296129

05-树8 File Transfer （25 分）
We have a network of computers and a list of bi-directional connections. Each of these connections allows a file transfer from one computer to another. 
Is it possible to send a file from any computer on the network to any other?

Input Specification:
Each input file contains one test case. For each test case, the first line contains N (2≤N≤10
​4
​​ ), the total number of computers in a network. Each computer in the network is then represented by a positive integer between 1 and N. 
Then in the following lines, the input is given in the format:

I c1 c2  
where I stands for inputting a connection between c1 and c2; or

C c1 c2    
where C stands for checking if it is possible to transfer files between c1 and c2; or

S
where S stands for stopping this case.

Output Specification:
For each C case, print in one line the word "yes" or "no" if it is possible or impossible to transfer files between c1 and c2, respectively. 
At the end of each case, print in one line "The network is connected." if there is a path between any pair of computers; or "There are k components." 
where k is the number of connected components in this network.

Sample Input 1:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S
Sample Output 1:
no
no
yes
There are 2 components.
Sample Input 2:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
I 1 3
C 1 5
S
Sample Output 2:
no
no
yes
yes
The network is connected.
*/

/*
本题需要用集合来做
下面用数组来实现集合， 并查集，本质上是集合树
集合的操作集：
1.查找某个元素所在的集合
2.集合的并运算
*/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1
#define Null -1

typedef struct {
    int Val;
    int Parent;
} SetType;
typedef struct {
    SetType *Data;
    int MaxSize;
} Set;
Set CreateSet(int MaxSize);
int Find(Set s, int X); // 查找元素所在的集合树的根节点
void Union(Set s, int X1, int X2); // 将X1和X2所在的集合并起来
int IsConnected(Set s, int X1, int X2);
void PrintNumberOfSets(Set s);

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    Set s = CreateSet(N);
    char cmd;
    int c1, c2;
    while(1){
        scanf("\n%c", &cmd);
        if(cmd=='S') break;
        else if(cmd=='C'){
            scanf("%d%d",&c1,&c2);
            if(IsConnected(s, c1, c2)) printf("yes\n");
            else printf("no\n");
        }else if(cmd=='I'){
            scanf("%d%d",&c1,&c2);
            Union(s, c1, c2);
        }
    }
    PrintNumberOfSets(s);
    return 0;
}
Set CreateSet(int MaxSize){
    int N = MaxSize+1;
    Set s = {
        .Data = (SetType*)malloc(N*sizeof(SetType)),
        .MaxSize = MaxSize,
    };
    int i;
    for(i=0;i<N;i++){
        s.Data[i].Val = i;
        s.Data[i].Parent = Null;
    }
    return s;
}
int Find(Set s, int X){
    int idx=X;
    while(s.Data[idx].Parent!=Null){
        idx = s.Data[idx].Parent;
    }
    return idx;
}
void Union(Set s, int X1, int X2){
    int root1 = Find(s, X1);
    int root2 = Find(s, X2);
    if(root1!=root2) s.Data[root2].Parent = root1;
}
int IsConnected(Set s, int X1, int X2){
    int root1 = Find(s, X1);
    int root2 = Find(s, X2);
    if(root1 == root2) return 1;
    else return 0;
}
void PrintNumberOfSets(Set s){
    int i;
    int cnt=0;
    for(i=1;i<=s.MaxSize;i++){
        if(s.Data[i].Parent==Null) cnt++;
    }

    switch(cnt){
        case 1: printf("The network is connected.\n"); break;
        default: printf("There are %d components.",cnt);
    }
}