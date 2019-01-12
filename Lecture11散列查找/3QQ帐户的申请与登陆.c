/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1060440632254308354

11-散列3 QQ帐户的申请与登陆 （25 分）
实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。

输入格式:
输入首先给出一个正整数N（≤10
​5
​​ ），随后给出N行指令。每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。其中命令符为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；命令符为“L”（代表Login）时
表示是老帐户登陆，后面是登陆信息。QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。密码为不小于6位、不超过16位、且不包含空格的字符串。

输出格式:
针对每条指令，给出相应的信息：

1）若新申请帐户成功，则输出“New: OK”；
2）若新申请的号码已经存在，则输出“ERROR: Exist”；
3）若老帐户登陆成功，则输出“Login: OK”；
4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；
5）若老帐户密码错误，则输出“ERROR: Wrong PW”。

输入样例:
5
L 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
L 1234567890 myQQ@qq
L 1234567890 myQQ@qq.com
输出样例:
ERROR: Not Exist
New: OK
ERROR: Exist
ERROR: Wrong PW
Login: OK
*/


#include <stdio.h>
#include <stdlib.h>

// #define DEBUG
#define MaxSize 100000
#define MAXLENGTH 20
#define Null -1

/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum{Legitimate, Empty, Deleted} CellType;

typedef struct _cell Cell;
struct _cell{
    char QQAccount[MAXLENGTH];
    char PassWord[MAXLENGTH];
    CellType Type;
};
struct _hash_table{
    int TableSize;
    Cell *Cells;
};
typedef struct _hash_table *HashTable;

#include <math.h>
int NextPrime(int N);
HashTable CreateHashTable( int N );
int Hash( char *Key, int TableSize );
#include <string.h>
int FindHashTable( HashTable ht, char *Key1, char *Key2);
int InsertHashTable( HashTable ht, char *Key1, char *Key2);
int GetPosition( HashTable ht, char *Key1, char *Key2);

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d",&N);
    HashTable ht = CreateHashTable(N);
    char cmd;
    char QQAccount[MAXLENGTH]={0,};
    char PassWord[MAXLENGTH]={0,};
    int i;
    int Position;
    for(i=0;i<N;i++){
        scanf("\n%c %s %s", &cmd, QQAccount, PassWord);
        Position = GetPosition(ht, QQAccount, PassWord);
        switch(cmd){
            case 'N':
                if(Position!=Null)
                    printf("ERROR: Exist\n");
                else{
                    InsertHashTable(ht, QQAccount, PassWord);
                    printf("New: OK\n");
                }
                break;
            case 'L':
                if(Position==Null)
                    printf("ERROR: Not Exist\n");
                else if(Position!=Null && strcmp(ht->Cells[Position].PassWord, PassWord)==0){
                    printf("Login: OK\n");
                }else{
                    printf("ERROR: Wrong PW\n");
                }
                break;
        }
    }
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
    int i,j;
    for(i=0;i<ht->TableSize;i++){
        ht->Cells[i].Type = Empty;
        for(j=0;j<MAXLENGTH;j++){
        	ht->Cells[i].QQAccount[j]=0;
            ht->Cells[i].PassWord[j]=0;
		}
    }
    return ht;
}
int Hash( char *Key, int TableSize ){
    int LENGTH=5;
    int i=0;
    while(Key[++i]);
    if(i>LENGTH)
        i-=LENGTH;
    int PhoneNumber = atoi(Key+i);
    // printf("%d\n",PhoneNumber);
    int ret = PhoneNumber%TableSize;
    return ret;
}
int FindHashTable( HashTable ht, char *Key1, char *Key2){
    // 查找函数
    int Position=Hash(Key1, ht->TableSize);

    while(ht->Cells[Position].Type==Legitimate){
        // int strcmp(const char *s1,const char *s2); 若 s1 与 s2 相等，则返回0
        if(strcmp(ht->Cells[Position].QQAccount, Key1)==0) 
        	break;
        Position++;
        Position = Position % ht->TableSize;
    }
    return Position; //要么返回找到的位置，要么返回新的位置
}
int InsertHashTable( HashTable ht, char *Key1, char *Key2){
    // 插入函数
    int Position = FindHashTable(ht, Key1, Key2);
    
    if(ht->Cells[Position].Type==Empty){
        ht->Cells[Position].Type=Legitimate;
        strcpy(ht->Cells[Position].QQAccount, Key1); // char *strcpy(char* dest, const char *src);
        strcpy(ht->Cells[Position].PassWord, Key2);
        return 1;
    }
}
int GetPosition( HashTable ht, char *Key1, char *Key2){
    int Position = FindHashTable(ht, Key1, Key2);
    if(ht->Cells[Position].Type == Empty){
        return Null;
    }
    else{
        return Position;
    }
}
