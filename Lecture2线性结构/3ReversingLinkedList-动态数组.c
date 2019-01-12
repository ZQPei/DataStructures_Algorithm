/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1037889290772254722

02-线性结构3 Reversing Linked List （25 分）
Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. For example, given L being 1→2→3→4→5→6, if K=3, 
then you must output 3→2→1→6→5→4; if K=4, you must output 4→3→2→1→5→6.

Input Specification:
Each input file contains one test case. For each case, the first line contains the address of the first node, a positive N (≤10^5) which is the total number of nodes, 
and a positive K (≤N) which is the length of the sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next
where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification:
For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/

/*
该算法的时间复杂度为 O(N^2)
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct _node Node;
struct _node{
    int Address;
    int Data;
    int Next;
};
struct _list{
    Node *ptrNode;
    int len;
};
typedef struct _list List;

List readList(int N);
void printList(List L);
void swapList(List L, int, int);
void sortList(List L, int firstAddress);
void freeList(List L);
void reverseList(List L, int K);

int main(int argc, char const *argv[])
{
    int firstAddress, N, K;
    scanf("%d %d %d", &firstAddress, &N, &K);
    List L = readList(N);
    if(DEBUG) printList(L);
    sortList(L, firstAddress);
    if(DEBUG) printList(L);
    reverseList(L, K);
    printList(L);
    freeList(L);
    return 0;
}

List readList(int N){
    Node *ptrNode = (Node *)malloc(N*sizeof(Node));
    int i,Address,Data,Next;
    for(i=0;i<N;i++){
        scanf("%d %d %d", &Address, &Data, &Next);
        ptrNode[i].Address = Address;
        ptrNode[i].Data = Data;
        ptrNode[i].Next =Next;
    }
    List L = {.ptrNode=ptrNode, .len=N};
    return L;
}

void printList(List L){
    if(DEBUG) printf("\nprintList\n");
    int i;
    for(i=0;i<L.len;i++){
        if(L.ptrNode[i].Next==-1){
            printf("%05d %d %d\n", L.ptrNode[i].Address, L.ptrNode[i].Data, L.ptrNode[i].Next);
        }else{
            printf("%05d %d %05d\n", L.ptrNode[i].Address, L.ptrNode[i].Data, L.ptrNode[i].Next);
        }
    }
}

void swapList(List L, int i, int j){
    Node tmp = L.ptrNode[i];
    L.ptrNode[i] = L.ptrNode[j];
    L.ptrNode[j] = tmp;
}

void sortList(List L, int firstAddress){
    int curAddress = firstAddress;
    int N = L.len;
    int curIdx = 0;
    int i;
    while(curAddress!=-1){
        for(i=curIdx;i<N;i++){
            if(L.ptrNode[i].Address == curAddress){
                curAddress = L.ptrNode[i].Next;
                swapList(L, curIdx++, i);
                break;
            }
        }
    }
}

void reverseList(List L, int K){
    int N = L.len;
    int revTimes = (int)(N/K);
    int i;
    for(i=0;i<revTimes;i++){
        int startIdx = K*i;
        int endIdx = startIdx+K-1;
        while(endIdx > startIdx){
            swapList(L, startIdx++, endIdx--);
        }
    }
    // fix .Next 
    for(i=0;i<N-1;i++){
        L.ptrNode[i].Next = L.ptrNode[i+1].Address;
    }
}

void freeList(List L){
    free(L.ptrNode);
}