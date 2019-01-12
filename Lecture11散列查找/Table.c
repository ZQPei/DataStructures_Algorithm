/*
哈希表的实现
*/

#include "Table.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int NextPrime(int N){
    int ret=(N%2)?(N+2):(N+1); //对 ret 赋值为ret的下一个奇数
    int i;
    while(ret){
        for(i=(int)sqrt(ret);i>2 && (ret%i!=0);i--); // 判断 ret 是不是素数
        if(i!=2)  // 不是素数
            ret+=2;
        else      // 是素数
            break;
    }
    return ret;
}
HashTable CreateHashTable( int N ){
    HashTable ht = (HashTable)malloc(sizeof(struct _hash_table));
    ht->TableSize = NextPrime(N);
    ht->Cells = (Cell*)malloc(ht->TableSize*sizeof(Cell));
    int i;
    for(i=0;i<ht->TableSize;i++){
        ht->Cells[i].Type = Empty;
    }
    return ht;
}
int Hash( ElementType Key , int TableSize ){
    // 自定义哈希函数
    int ret = Key%TableSize;
    return ret;
}
int FindHashTable_Linear( HashTable ht, ElementType Key){
    // 线性查找函数
    int Position=Hash(Key, ht->TableSize);

    while(ht->Cells[Position].Type==Legitimate){
        if( ht->Cells[Position].Data==Key )
        	break;
        Position++;
        Position = Position % ht->TableSize;
    }
    return Position; //要么返回找到的位置，要么返回新的位置
}
int FindHashTable_Quadratic( HashTable ht, ElementType Key){
    // 平方查找函数
    int Position=Hash(Key, ht->TableSize);
    int NewPos = Position;
    int CNum = 0, tmp;
    int Found = 1;
    while(ht->Cells[NewPos].Type==Legitimate && ht->Cells[NewPos].Data!=Key){
        CNum++;
        tmp = CNum*CNum;
        if(tmp >= ht->TableSize){
            Found=0;
            break;
        }
        NewPos = Position + tmp;
        NewPos = NewPos % ht->TableSize;
    }
    if(!Found) return Null;     //如果未找到，则返回Null
    else       return Position; //要么返回找到的位置，要么返回新的位置
}
int InsertHashTable( HashTable ht, ElementType Key ){
    // 插入函数
    int Position = FindHashTable_Quadratic(ht, Key);
    
    if(ht->Cells[Position].Type==Empty){
        ht->Cells[Position].Type=Legitimate;
        ht->Cells[Position].Data=Key;
    }
    return Position;
}
