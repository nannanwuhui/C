#include <stdio.h>
#include <stdlib.h>
int main(){
    int* p1 = malloc(sizeof(int));
    int* p2 = malloc(sizeof(int));
    printf("%p,%p\n",p1,p2);
    free(p2);
    p1[3] = 0;
    //以上只赋值，下面不free的话，不会有问题，
    //就算是上面赋值，下面也free了也不一定会出问题，因为你赋值
    //的那块信息不一定就会用到，但是这样做是不对的。
    free(p1);
    return 0;
}
