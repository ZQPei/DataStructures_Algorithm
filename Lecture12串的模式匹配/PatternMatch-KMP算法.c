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

void BuildMatch( char *pattern, int *match){
    int i,j;
    int m=strlen(pattern);
    match[0] = -1;
    for(j=1;j<m;j++){
        i=match[j-1];
        while(i>=0 && pattern[i+1]!=pattern[j]){
            i = match[i];
        }
        if(pattern[i+1]==pattern[j])
            match[j] = i+1;
        else
            match[j] = -1;
    }
}

Position KMP( char *string, char *pattern){  //时间复杂度 T=O(m+n)
    int n=strlen(string); //O(n)
    int m=strlen(pattern);//O(m)
    int s,p;
    int *match;
    match = (int*)malloc(m*sizeof(int));
    BuildMatch(pattern, match); //O(m)

    s=p=0;
    while(s<n && p<m){    //O(n)
        if(string[s]==pattern[p]) {
            s++; p++;
        }else if(p>0){
            p = match[p-1]+1;
        }else
            s++;
    }
    free(match);
    return (p==m) ? (s-m) : NotFound;
}

int main(int argc, char const *argv[])
{
    char string[] = "abcabcabcabcacabxy";
    char pattern[] = "abcabcacab";
    // char pattern[] = "cabcabcd";
    // char pattern[] = "abcabcabcabcacabxyz";
    Position p = KMP(string, pattern);
    if(p!=NotFound)
        printf("%s\n", string+p);
    else
        printf("NotFound\n");

    return 0;
}

