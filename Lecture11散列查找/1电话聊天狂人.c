/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1060440632254308352

11-散列1 电话聊天狂人 （25 分）
给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。

输入格式:
输入首先给出正整数N（≤10^5 ），为通话记录条数。随后N行，每行给出一条通话记录。简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

输出格式:
在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。

输入样例:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
输出样例:
13588625832 3
*/

#include <stdio.h>
#include <stdlib.h>

// #define DEBUG
#define MaxSize 100000
#define LENGTH 12
#define Null -1

/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum{Legitimate, Empty, Deleted} CellType;

typedef struct _cell Cell;
struct _cell{
    char Data[LENGTH];
    int Cnt;
    CellType Type;
};

struct _hash_table{
    int TableSize;
    Cell *Cells;

    int MaxCnt;
    int MaxPosition;
};
typedef struct _hash_table *HashTable;

#include <math.h>
int NextPrime(int N);
HashTable CreateHashTable( int N );
int Hash( const char *Key , int TableSize );
#include <string.h>
int FindHashTable( HashTable ht, char *Key);
int InsertHashTable( HashTable ht, char *Key);


int main(int argc, char const *argv[])
{
    // 读取数据
    int N;
    scanf("%d", &N);
    HashTable ht = CreateHashTable(N*2);
    int i;
    char Key[LENGTH]={0,};
    for(i=0;i<N;i++){
        scanf("%s",Key);
        InsertHashTable(ht, Key);
        scanf("%s",Key);
        InsertHashTable(ht, Key);
    }

    // 输出结果
    printf("%s %d",ht->Cells[ht->MaxPosition].Data, ht->MaxCnt);
    return 0; 
}



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
    ht->MaxCnt = 0;
    ht->MaxPosition = Null;
    int i;
    for(i=0;i<ht->TableSize;i++){
        ht->Cells[i].Type = Empty;
        ht->Cells[i].Cnt = 0;
    }
    return ht;
}
int Hash( const char *Key , int TableSize ){
    int START = 6;
    int PhoneNumber = atoi(Key+START);
    int ret = PhoneNumber%TableSize;
    return ret;
}
int FindHashTable( HashTable ht, char *Key){
    // 查找函数
    int Position=Hash(Key, ht->TableSize);

    while(ht->Cells[Position].Type==Legitimate){
        if(strcmp(ht->Cells[Position].Data, Key)==0) // int strcmp(const char *s1,const char *s2); 若 s1 与 s2 相等，则返回0
        	break;
        Position++;
        Position = Position % ht->TableSize;
    }
    return Position; //要么返回找到的位置，要么返回新的位置
}
int InsertHashTable( HashTable ht, char *Key){
    // 插入函数
    int Position = FindHashTable(ht, Key);
    
    if(ht->Cells[Position].Type==Empty){
        ht->Cells[Position].Type=Legitimate;
        ht->Cells[Position].Cnt=1;
        strcpy(ht->Cells[Position].Data, Key); // char *strcpy(char* dest, const char *src);
        #ifdef DEBUG
            printf("%s Inserted\n", ht->Cells[Position].Data);
        #endif
        return 1;
    }else{
        #ifdef DEBUG
            printf("%s Found\n", ht->Cells[Position].Data);
        #endif
        ht->Cells[Position].Cnt++;
        if( ht->Cells[Position].Cnt > ht->MaxCnt ){
            ht->MaxCnt = ht->Cells[Position].Cnt;
            ht->MaxPosition = Position;
        }else if( ht->Cells[Position].Cnt == ht->MaxCnt ){
            ht->MaxPosition = strcmp(ht->Cells[Position].Data, Key)>0 ? Position : ht->MaxPosition;
        }
        return 0;
    }
}