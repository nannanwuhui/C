#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void presskey(){
    printf("查看/proc/%u/maps,按<回车>继续...",getpid());
    getchar();
}
int main(){
    printf("1页 = %d字节\n",getpagesize());
    char* pc = malloc(sizeof(char));
    printf("pc = %p\n",pc);
    presskey();//maps中有33页的映射
    free(pc);//gnu的free不会解除映射，只会将这块内存标记为不可用。
    printf("free(%p)\n",pc);
    presskey();//maps中仍然有33页的映射存在
//    pc = malloc(sizeof(char));//和上次malloc出来的地址是一样的。只不过将上次的那１个字节的内存标记为可用
    pc = malloc(sizeof(char) * 100);
    printf("pc = %p\n",pc);//分配出来的内存地址和上次的不一样了
    presskey();
    setbuf(stdout,NULL);//关闭输出流缓冲区
    size_t i = 0;
    for(;;){
        printf("向堆内存%p写...",&pc[i]);
        printf("%c\n",pc[i++] = (i%26) + 'A');
    }//看着maps文件，在写３３页的下一个字节的时候出现了段错误
    return 0;
}
#if 0
gvim /proc/25757/maps
024f0000-02511000 rw-p 00000000 00:00 0                                  [heap]
zn@zn-OptiPlex-9010:~/github/C$ wcalc 0x02511000-0x024f0000
= 135168
135168/4096 = 33
#endif
