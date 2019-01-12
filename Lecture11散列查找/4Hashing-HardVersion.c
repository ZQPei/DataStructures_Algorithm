/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1060440632254308355

11-散列4 Hashing - Hard Version （30 分）
Given a hash table of size N, we can define a hash function H(x)=x%N. Suppose that the linear probing is used to solve collisions, we can easily obtain the status of 
the hash table with a given sequence of input numbers.

However, now you are asked to solve the reversed problem: reconstruct the input sequence from the given status of the hash table. Whenever there are multiple choices, 
the smallest number is always taken.

Input Specification:
Each input file contains one test case. For each test case, the first line contains a positive integer N (≤1000), which is the size of the hash table. The next line 
contains N integers, separated by a space. A negative integer represents an empty cell in the hash table. It is guaranteed that all the non-negative integers are distinct 
in the table.

Output Specification:
For each test case, print a line that contains the input sequence, with the numbers separated by a space. Notice that there must be no extra space at the end of each line.

Sample Input:
11
33 1 13 12 34 38 27 22 32 -1 21
Sample Output:
1 13 12 21 33 34 38 27 22 32
*/

/*
以下代码有误，应该用到拓扑排序来做
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _cell Cell;
struct _cell{
    int Data;
    int Step;
};

int Hash(int Key, int TableSize){
    return Key%TableSize;
}
int CompareCell( const void *p1, const void *p2){
    int ret=0;
    if(((Cell*)p1)->Step>((Cell*)p2)->Step){
        ret = 1;
    }else if(((Cell*)p1)->Step<((Cell*)p2)->Step){
        ret = -1;
    }else if(((Cell*)p1)->Step==((Cell*)p2)->Step){
        if(((Cell*)p1)->Data>((Cell*)p2)->Data){
            ret = 1;
        }else if(((Cell*)p1)->Data<((Cell*)p2)->Data){
            ret = -1;
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int TableSize;
    scanf("%d", &TableSize);
    Cell c[TableSize];
    int i, tmp;
    for(i=0;i<TableSize;i++){
        scanf("%d",&tmp);
        if(tmp!=-1){
            c[i].Data = tmp;
            int step = (i-Hash(tmp, TableSize));
            if(step<0) step+=TableSize;
            else if(step>=TableSize) step-=TableSize;
            c[i].Step = step;
        }else{
            c[i].Data = tmp;
            c[i].Step = TableSize;
        }
    }
    qsort(c, TableSize, sizeof(Cell), CompareCell);

    for(i=0;i<TableSize;i++){
        if(i==0)
            printf("%d",c[i].Data);
        else if(c[i].Data!=-1)
            printf(" %d",c[i].Data);
    }
    return 0;
}



