#include <stdio.h>
#include <unistd.h>
void* g_begin = NULL;
void init(void){
    g_begin = sbrk(0);
}
void deinit(){
    brk(g_begin);
}
void push(int data){
    *(int*)sbrk(sizeof(int)) = data;
}
int pop(){
    int data = *((int*)sbrk(0) - 1);
    sbrk(-sizeof(int));
    return data;
}
int top(){
    return *((int*)sbrk(0) - 1);
}
int empty(){
    return sbrk(0) == g_begin;
}
int main(){
    init();
    int i;
    for(i = 0;i < 10;++i)
        push(i);
    while(!empty())
        printf("%d ",pop());
    printf("\n");
    deinit();
    return 0;
}
