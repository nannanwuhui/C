#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
//还有一些，比如原来有１００个字节是空闲的，然后找到了分配了５０个字节，那剩下的5０个字节
//就没办法用了，更好的做法是能把这１００个字节分块，让剩下的50个字节也能够使用
//还有可以把内存碎片尽量的往后移动，然后可以让brk解除映射。
//内存控制块
typedef struct mem_control_block{
    bool free;//自由标志
    struct mem_control_block* prev;//前块指针
    size_t size;//本块大小
}MCB;
MCB* g_top = NULL;//栈顶指针
//分配内存
void* my_malloc(size_t size){
    MCB* mcb;
    //从右往前找,栈的第一个位置为NULL
    for(mcb = g_top;mcb;mcb = mcb->prev){
        if(mcb->free && mcb->size >= size){
            break;
        }
    }
    if(!mcb){
        mcb = sbrk(sizeof(MCB) + size);
        if(mcb == (void*)-1){
            return NULL;
        }
        mcb->prev = g_top;
        mcb->size = size;
        g_top = mcb;
    }
    mcb->free = false;
    //跳过内存控制块
    return (MCB*)mcb + 1;
}
//释放内存
void my_free(void* ptr){
    if(!ptr)
        return ;
    MCB* mcb = (MCB*)ptr - 1;
    mcb->free = true;
    for(mcb = g_top;mcb->prev;mcb = mcb->prev){
        if(!mcb->free)
            break;
    if(mcb->free){
        g_top = mcb->prev;
        brk(mcb);
    }
    else{
        if(mcb != g_top){
            g_top = mcb;
            //把mcb转成void*,后面的+就会以字节为单位，加多少个字节
            brk((void*)mcb + sizeof(mcb) + mcb->size);
        }
    }
    }
}
int main(){
    //用指针数组实现了一个不定长的二维数组
    int* pa[10];
    size_t size = sizeof(pa) / sizeof(pa[0]),i,j;
    for(i = 0;i < size;i++){
        if(!(pa[i] = (int*)my_malloc((i+1) * sizeof(int)))){
            perror("my_malloc");
            return -1;
        }
        for(j = 0;j <= i;j++)
            pa[i][j] = j;
    }
    for(i = 0;i < size;i++){
        for(j = 0;j <= i;j++){
            printf("%d ",pa[i][j]);
        }
        printf("\n");
    }
#if 0
    for(i = 0;i < size;i++)
        my_free(pa[i]);
#endif
    for(;;){
        my_free(pa[--i]);
        if(!i)
            break;
    }
    return 0;
}
