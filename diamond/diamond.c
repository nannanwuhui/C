#include <stdio.h>
#include "diamond.h"
void diamond(int h,int d,int s,char c){
    int i,j;
    for(i = 0;i <= h;i++){
        printf("%*s",(h-i)*d,"");
        for(j = 0;j < i*d*2;++j)
            printf("%c",j?(s?c:' '):c);
        printf("%c\n",c);
    }
    for(i= 1;i <= h;++i){
        printf("%*s",i*d,"");
        for(j = 0;j < (h-i) * d * 2;++j)
            printf("%c",j?(s?c:' '):c);
        printf("%c\n",c);
    }
}

