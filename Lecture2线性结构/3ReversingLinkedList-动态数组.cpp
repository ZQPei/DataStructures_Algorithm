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

#include <cstdio>


#define MAXLENGTH 1000002

class Node
{
public:
    Node(): address(0),data(0),next_address(0),next(nullptr){}
    Node(int address, int data, int next_address): 
        address(address),data(data),next_address(next_address),next(nullptr){}

    int address;
    int data;
    int next_address;
    Node *next;
};
typedef Node* List;

List Read(int startid, int length);
List Free(List l);
void Print(List l);
List ReversebyK(List l, int K);

int main(){
    int startid=0, length=0, K=0;
    scanf("%d %d %d", &startid, &length, &K);

    List l = Read(startid, length);
    // Print(l);

    l = ReversebyK(l, K);
    Print(l);
    Free(l);

    return 0;
}

List Read(int startid, int length){
    // 借助空间来减少排序时候的时间复杂度
    int address=0, data=0, next_address=0;
    Node *database = new Node[MAXLENGTH];
    for(int i=0;i<length;++i){
        scanf("%d %d %d", &address, &data, &next_address);
        database[address] = Node(address, data, next_address);
    }

    // 排序
    List l=nullptr, last=nullptr, tmp=nullptr;
    int id = startid;
    for(int i=0;i<length && id!=-1;++i){
        tmp = new Node(database[id]);
        if(i==0){
            l = tmp;
            last = l;
        }
        else{
            last->next = tmp;
            last = last->next;
        }

        id = database[id].next_address;
    }
    return l;
}

List Free(List l){
    Node *tmp=nullptr;
    while(l){
        tmp = l;
        l=l->next;
        delete tmp;
    }
    return nullptr;
}
void Print(List l){
    while(l){
        if(l->next_address != -1)
            printf("%05d %d %05d\n", l->address, l->data, l->next_address);
        else
            printf("%05d %d %d\n", l->address, l->data, l->next_address);
        l=l->next;
    }
}
List ReversebyK(List l, int K){
    // 时间复杂度 o(n)
    if(K<=1)
        return l;


    Node *ahead_k=l, *curr=l, *last=nullptr, *next=nullptr, *tmp=nullptr, *next_last=nullptr;

    while(curr){
        ahead_k = curr;
        int i=0;
        for(i=0;i<K && ahead_k;++i)
            ahead_k = ahead_k->next;
        
        if(i<K)
            break;

        next = ahead_k;
        next_last = curr;
        for(int i=0;i<K;++i){
            tmp = curr->next;  
            curr->next = next;
            if(next) curr->next_address = next->address;
            else curr->next_address = -1;
            next = curr;
            curr = tmp;
        }

        if(last==nullptr){
            last = l;
            l = next;
        }
        else{
            last->next = next;
            if(next) last->next_address = next->address;
            else last->next_address = -1;
            last = next_last;
        }
    }

    return l;
}