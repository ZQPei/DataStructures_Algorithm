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

#include <cstdio>

#define DEBUG 0

struct PolyNode
{
public:
    PolyNode(){
        this->coef = 0;
        this->exp = 0;
        this->next = nullptr;
    }
    PolyNode(int coef, int exp){
        this->coef = coef;
        this->exp = exp;
        this->next = nullptr;
    }
    PolyNode(PolyNode *p){
        this->coef = p->coef;
        this->exp = p->exp;
        this->next = nullptr;
    }

    int coef;
    int exp;
    PolyNode *next;
};
typedef PolyNode* Polynomial;

Polynomial Read();
Polynomial Free(Polynomial p);
void Print(Polynomial p);
Polynomial Add(Polynomial p1, Polynomial p2);
Polynomial Mul(Polynomial p1, Polynomial p2);


int main(){
    Polynomial p1 = Read();
    Polynomial p2 = Read();

    if(DEBUG){
        Print(p1);
        Print(p2);
    }

    Polynomial p_add = Add(p1, p2);
    Polynomial p_mul = Mul(p1, p2);

    Print(p_mul);
    Print(p_add);

    p1 = Free(p1);
    p2 = Free(p2);
    p_add = Free(p_add);
    p_mul = Free(p_mul);


    return 0;
}


Polynomial Read(){
    int N=0;
    int coef=0, exp=0;
    scanf("%d",&N);

    Polynomial p=nullptr;
    PolyNode *last=nullptr;
    for(int i=0;i<N;++i){
        scanf("%d %d",&coef, &exp);
        PolyNode* new_node = new PolyNode(coef, exp);
        if(p==nullptr){
            p=new_node;
            last=p;
        }
        else{
            last->next=new_node;
            last=last->next;
        }
    }
    return p;
}
Polynomial Free(Polynomial p){
    PolyNode *tmp = p;
    while(p){
        tmp = p;
        p = p->next;
        delete tmp;
    }
    return nullptr;
}
void Print(Polynomial p){
    if(p==nullptr){
        printf("0 0\n");
        return;
    }


    while(p){
        printf("%d %d", p->coef, p->exp);
        p = p->next;
        if(p)
            printf(" ");
        else
            printf("\n");
    }
}
Polynomial Add(Polynomial p1, Polynomial p2){
    // 其实就是归并排序     
    // 时间复杂度 o(m+n)
    Polynomial p = nullptr;
    PolyNode *tmp = nullptr, *last = nullptr;
    int coef = 0, exp = 0;
    while(p1 && p2){
        if(p1->exp == p2->exp){
            coef = p1->coef+p2->coef;
            exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->exp > p2->exp){
            coef = p1->coef;
            exp = p1->exp;
            p1 = p1->next;
        }
        else if(p1->exp < p2->exp){
            coef = p2->coef;
            exp = p2->exp;
            p2 = p2->next;
        }

        if(coef==0)
            continue;
        else
            tmp = new PolyNode(coef, exp);

        if(p==nullptr){
            p = tmp;
            last = p;
        }
        else{
            last->next = tmp;
            last = last->next;
        }
    }

    while(p1){
        coef = p1->coef;
        exp = p1->exp;
        p1 = p1->next;

        if(coef==0)
            continue;
        else
            tmp = new PolyNode(coef, exp);

        if(p==nullptr){
            p = tmp;
            last = p;
        }
        else{
            last->next = tmp;
            last = last->next;
        }
    }

    while(p2){
        coef = p2->coef;
        exp = p2->exp;
        p2 = p2->next;

        if(coef==0)
            continue;
        else
            tmp = new PolyNode(coef, exp);

        if(p==nullptr){
            p = tmp;
            last = p;
        }
        else{
            last->next = tmp;
            last = last->next;
        }
    }

    return p;
}

Polynomial Mul(Polynomial p1, Polynomial p2){
    // 时间复杂度 o(mn(m+n))
    if(!p1 || !p2)
        return nullptr;


    Polynomial p = nullptr;
    Polynomial p_tmp = nullptr, p_free=nullptr;

    PolyNode *tmp_node = nullptr, *last = nullptr;
    PolyNode *ptr1 = p1, *ptr2 = p2;
    while(ptr2){
        ptr1 = p1;
        while(ptr1){
            tmp_node = new PolyNode(ptr1->coef*ptr2->coef, ptr1->exp+ptr2->exp);
            ptr1 = ptr1->next;

            if(p_tmp==nullptr){
                p_tmp = tmp_node;
                last = p_tmp;
            }
            else{
                last->next = tmp_node;
                last = last->next;
            }
        }

        if(p == nullptr){
            p = p_tmp;
            p_tmp = nullptr;
        }
        else{
            p_free = p;
            p = Add(p, p_tmp);
            p_free = Free(p_free);
            p_tmp = Free(p_tmp);
        }

        ptr2 = ptr2->next;
    }

    return p;
}