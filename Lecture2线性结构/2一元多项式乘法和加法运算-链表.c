/*
原题链接:https://pintia.cn/problem-sets/1010070491934568448/problems/1037889290772254721

02-线性结构2 一元多项式的乘法与加法运算 （20 分）
设计函数分别求两个一元多项式的乘积与和。

输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct PolyNode *PtrToPolyNode;
struct PolyNode{
    int coef;
    int expo;
    PtrToPolyNode next;
};
typedef struct _polynomial{
    PtrToPolyNode head;
    int len;
}Polynomial;

Polynomial readPoly();
void printPoly(Polynomial P);
PtrToPolyNode attachPolyNode(PtrToPolyNode P, PtrToPolyNode ptrNewNode);
Polynomial mulPoly(Polynomial P1, Polynomial P2);
Polynomial addPoly(Polynomial P1, Polynomial P2);

int main(int argc, char const *argv[])
{
    Polynomial P1,P2,PM,PA;
    P1 = readPoly();
    P2 = readPoly();
    if(DEBUG){
        printPoly(P1);
        printPoly(P2);
    }
    PM = mulPoly(P1, P2);
    PA = addPoly(P1, P2);

    printPoly(PM);
    printPoly(PA);

    return 0;
}

PtrToPolyNode newPolyNode(int coef, int expo){
    PtrToPolyNode ptrNewNode = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
    ptrNewNode->coef = coef;
    ptrNewNode->expo = expo;
    ptrNewNode->next = NULL;
    return ptrNewNode;
}

int getLength(PtrToPolyNode P){
    int len=0;
    PtrToPolyNode ptrThisNode=P;
    while(ptrThisNode){
        len++;
        ptrThisNode = ptrThisNode->next;
    }
    return len;
}

Polynomial readPoly(){
    int N,i;
    int coef, expo;
    Polynomial P={.head=NULL, .len=0};
    PtrToPolyNode last=NULL;
    scanf("%d", &N);
    P.len=N;
    for(i=0;i<N;i++){
        scanf("%d %d", &coef, &expo);
        PtrToPolyNode ptrNewNode = newPolyNode(coef, expo);
        if(i==0){
            P.head=last=ptrNewNode;
        }else{
            last->next=ptrNewNode;
            last=ptrNewNode;
        }
    }
    return P;
}

void printPoly(Polynomial P){
    int i;
    if(DEBUG){
        printf("多项式的长度为%d ", P.len);
    }
    PtrToPolyNode ptrThisNode=P.head;
    int isfirst=1;
    while(ptrThisNode){
        if(!isfirst){
            printf(" ");
        }else{
            isfirst=0;
        }
        printf("%d %d",ptrThisNode->coef, ptrThisNode->expo);
        ptrThisNode = ptrThisNode->next;
    }
    printf("\n");
}

void freePolyNode(PtrToPolyNode p){
    free(p);
}

PtrToPolyNode attachPolyNode(PtrToPolyNode P, PtrToPolyNode ptrNewNode){
    PtrToPolyNode curr = P;
    if(ptrNewNode->expo > P->expo){
        ptrNewNode->next=P;
        return ptrNewNode;
    }else if(ptrNewNode->expo == P->expo){
        P->coef += ptrNewNode->coef;
        freePolyNode(ptrNewNode);
        return P;
    }
    while(1){
        PtrToPolyNode nextNode = curr->next;
        if(nextNode==NULL || ptrNewNode->expo > nextNode->expo){
            curr->next = ptrNewNode;
            ptrNewNode->next = nextNode;
            break;
        }else if(ptrNewNode->expo == nextNode->expo){
            nextNode->coef += ptrNewNode->coef;
            freePolyNode(ptrNewNode);
            break;
        }else if(ptrNewNode->expo < curr->expo){
            curr = curr->next;
        }
    }
    return P;
}

Polynomial mulPoly(Polynomial P1, Polynomial P2){
    int i,j;
    PtrToPolyNode head;
    head=NULL;
    PtrToPolyNode curr1 = P1.head;
    int N1=P1.len;
    PtrToPolyNode curr2 = P2.head;
    int N2=P2.len;
    int coef, expo;

    for(i=0;i<N1;i++){
    	curr2 = P2.head;
        for(j=0;j<N2;j++){
            coef = curr1->coef * curr2->coef;
            expo = curr1->expo + curr2->expo;
            PtrToPolyNode ptrNewNode = newPolyNode(coef, expo);
            if(head==NULL){
                head = ptrNewNode;
            }else{
                head = attachPolyNode(head, ptrNewNode);
            }
            curr2=curr2->next;
        }
        curr1=curr1->next;
    }

    Polynomial P={.head=head, .len=getLength(head)};
    return P;
}

Polynomial addPoly(Polynomial P1, Polynomial P2){
    PtrToPolyNode head = P1.head;
    int j;
    PtrToPolyNode currNode = P2.head;
    for(j=0;j<P2.len;j++){
        PtrToPolyNode nextNode = currNode->next;
        head = attachPolyNode(head, currNode);
        currNode = nextNode;
    }

    Polynomial P={.head=head, .len=getLength(head)};
    return P;
}
