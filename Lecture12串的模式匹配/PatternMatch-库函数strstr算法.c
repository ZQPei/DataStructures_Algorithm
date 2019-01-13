/*
串的模式匹配

串： 默认是字符串
串的模式匹配对字符串而言即是字符串的模式匹配

抽象函数接口
Position PatternMatch( char *string, char*pattern); string 是待匹配字符串， pattern 是模板字符串， 返回pattern第一次出现的位置

TODO：
1.实现strstr算法
2.实现字符串匹配的KMP算法
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NotFound -1
typedef int Position;


// 返回的是相对string头指针的位置
Position My_strstr(char *string, char *pattern){   // 时间复杂度 T=O(mn)
    Position s, p;
    int n,m;
    n = strlen(string);
    m = strlen(pattern);
    s=p=0;
    while(s<n && p<m){
        Position i;
        for(i=s; i<n && string[i]==pattern[p]; i++, p++);
        if(p==m) // 匹配成功
            break;
        else{    // 匹配不成功
            p=0;
            s++;
        }     
    }
    printf("%d\n", s);
    printf("%d\n", p);
    return (p==m) ? s : NotFound;
}


int main(int argc, char const *argv[])
{
    char string[] = "abcabcabcabcacabxy";
    // char pattern[] = "abcabcacab";
    // char pattern[] = "cabcabcd";
    char pattern[] = "abcabcabcabcacabxyz";
    Position p = My_strstr(string, pattern);
    if(p!=NotFound)
        printf("%s\n", string+p);
    else
        printf("NotFound\n");

    return 0;
}
