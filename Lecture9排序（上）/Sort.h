#ifndef SORT_H_
#define SORT_H_

#define ElementType int 

/*
冒泡排序 Bubble_Sort
时间复杂度 O(N^2)
*/
void Bubble_Sort(ElementType A[], int N);


/*
插入排序 Insertion_Sort
时间复杂度 O(N^2)
若一个数组基本有序，则插入排序算法简单高效
*/
void Insertion_Sort(ElementType A[], int N);


/*
希尔排序 Shell_Sort
希尔排序可以看作是插入排序的扩展
时间复杂度 最坏情况O(N^2)
希尔排序时间复杂度不稳定！
*/
// 原始希尔排序
void Shell_Sort(ElementType A[], int N);
// Hibbard 增量序列 希尔排序
void Hibbard_Shell_Sort(ElementType A[], int N);
// Sedgewick增量序列哈希排序 
void Sedgewick_Shell_Sort(ElementType A[], int N);


/*
选择排序 Selection_Sort
时间复杂度 O(N^2)
*/
void Selection_Sort(ElementType A[], int N);


/*
堆排序 Heap_Sort
时间复杂度 最坏情况O(NlogN)
堆排序的时间复杂度不稳定
*/
void Heap_Sort(ElementType A[], int N);


/*
归并排序 Merge_Sort
时间复杂度 O（NlogN)
归并排序非常稳定
*/
// 递归实现
void Merge_Sort_Recursive(ElementType A[], int N);
// 非递归实现
void Merge_Sort_NonRecursive(ElementType A[], int N);


/*
快速排序 Quick_Sort
时间复杂度 最坏 O(N^2)
          平均 O(NlogN)
不稳定
*/
// 递归实现
void Quick_Sort(ElementType A[], int N);
// 调用库函数 qsort
void Quick_Sort_Stdlib(ElementType A[], int N);


/*
桶排序 Bucket_Sort
时间复杂度 O(M+N)
稳定
适用于整形序列，且范围是 0~M
M是序列的最大值，N是序列的长度
当M与N接近时，适合用桶排序
*/
void Bucket_Sort(int A[], int N);


/*
基数排序 Radix_Sort
时间复杂度 O(P(N+B))
          P是整数的最大位数
          N是序列个数
          B是进制
稳定
适用于整数排序
适用于P较少的情况
低位优先 LSD
*/
int GetDigit(int X, int D);



void PrintArr(int A[], int N);

#endif // SORT_H_