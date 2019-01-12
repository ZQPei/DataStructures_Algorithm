/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1037889290772254723

02-线性结构4 Pop Sequence （25 分）
Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
Sample Output:
YES
NO
NO
YES
NO
*/

/*
思路：
题目是判断一个数字序列是否可能是一组顺序数字通过堆栈弹出的序列，
一个序列要是堆栈弹出的序列，必须满足：
1. 如果当前数比上一个数大，则大出的范围必须满足堆栈不溢出
2. 如果当前数比上一个数小，则当前数必须是堆栈的栈顶！
依据以上规则，可以根据pop出的数来恢复出堆栈当前的内容！

该算法的时间复杂度为O(N)
*/


#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

struct _stack{
    int *Data;
    int top;
    int MAXSIZE;
};
typedef struct _stack Stack;

Stack newStack(int MAXSIZE);
void printStack(Stack S);
int popStack(Stack * pS);
void pushStack(Stack *pS, int val);
void freeStack(Stack S);
int isPossiblePopSequence(int popSeq[], int len, int MAXSIZE);

int main(int argc, char const *argv[])
{
    int M,N,K;
    scanf("%d %d %d", &M, &N, &K);
    int i,j;
    int *result = (int *)malloc(K*sizeof(int));

    for(i=0;i<K;i++){
        int *popSeq = (int*)malloc(N*sizeof(int));
        int j;
        for(j=0;j<N;j++){
            scanf("%d", &popSeq[j]);
        }
        result[i] = isPossiblePopSequence(popSeq, N, M);
    }

    for(i=0;i<K;i++){
        if(result[i]) printf("YES\n");
        else printf("NO\n");
    }
        
    return 0;
}

Stack newStack(int MAXSIZE){
    int *Data=(int*)malloc(MAXSIZE*sizeof(int));
    int i;
    for(i=0;i<MAXSIZE;i++){
        Data[i] = 0;
    }
    Stack S = {.Data=Data, .top=-1, .MAXSIZE=MAXSIZE};
    return S;
}

void printStack(Stack S){
    int i;
    for(i=0;i<=S.top;i++){
        printf("%d ", S.Data[i]);
    }
    printf("\n");
}

int popStack(Stack * pS){
    if(pS->top == -1){
        if(DEBUG) printf("Stack is empty\n");
        return -1;
    }
    int val = pS->Data[pS->top--];
    return val;
}

void pushStack(Stack *pS, int val){
    if(pS->top == pS->MAXSIZE-1){
        if(DEBUG) printf("Stack is FULL\n");
        return ;
    }
    pS->Data[++pS->top] = val;
}

int resconstructStack(Stack *pS, int newVal, int maxPopVal){
    if(newVal < maxPopVal) {
        if(DEBUG) printf("newVal too small\n");
        return 0;
    }
    if((newVal-maxPopVal)+pS->top+1 > pS->MAXSIZE){
        if(DEBUG) {
        	printStack(*pS);
        	printf("Stack Overflow!\n");
		}
        return 0;
    }
    
    int i;
    for(i=maxPopVal+1;i<newVal;i++){
        pushStack(pS, i);
    }
    return 1;
}

int isPossiblePopSequence(int popSeq[], int len, int MAXSIZE){
    if(popSeq[0]>MAXSIZE){
        return 0;
    }

    int res = 1;
    Stack S = newStack(MAXSIZE);
    int maxPopVal=-1;
    int i;
    for(i=0;i<len;i++){
        int curVal = popSeq[i];
        if(i==0){
            int j;
            for(j=1;j<curVal;j++){
                pushStack(&S, j);
            }
            maxPopVal = curVal;
            if(DEBUG){
                printStack(S);
            }
            continue;
        }
        if(curVal > maxPopVal){
            int success = resconstructStack(&S, curVal, maxPopVal);
            if(success == 0){
                res = 0;
                if(DEBUG){
                    printStack(S);
                }
                break;
            }
            maxPopVal = curVal;
        }else if(curVal < maxPopVal){
            if(curVal != popStack(&S)){
                res = 0;
                if(DEBUG){
                    printStack(S);
                }
                break;
            }
        }
        if(DEBUG){
            printStack(S);
        }
    }
    freeStack(S);
    return res;
}

void freeStack(Stack S){
    free(S.Data);
}