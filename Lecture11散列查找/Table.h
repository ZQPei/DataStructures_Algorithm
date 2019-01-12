#ifndef TABLE_H_
#define TABLE_H_


#define MaxSize 100000
#define LENGTH 12
#define Null -1


/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum{Legitimate, Empty, Deleted} CellType;
typedef int ElementType;

typedef struct _cell Cell;
struct _cell{
    ElementType Data;
    CellType Type;
};
struct _hash_table{
    int TableSize;
    Cell *Cells;
};
typedef struct _hash_table *HashTable;

int NextPrime(int N);
HashTable CreateHashTable( int N );
int Hash( ElementType Key , int TableSize );
int FindHashTable_Linear( HashTable ht, ElementType Key);
int FindHashTable_Quadratic( HashTable ht, ElementType Key);
int InsertHashTable( HashTable ht, ElementType Key );


#endif //TABLE_H_