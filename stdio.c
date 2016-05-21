#include <stdio.h>
int main(void){
    FILE* fp = fopen("stdio.dat","wb");
    if(! fp){
        perror("fopen");
        return -1;
    }
    unsigned int i;
    for(i = 0;i < 100000;++i){
        //fwrite是先写入标准库的缓冲区中，当缓冲区达到一定量的时候，才会一次性写入内核缓冲区
        //(也就是调用write)，这样可以减少进入内核的次数
        //而如果直接调用write的话，就会频繁的在用户态和内核态之间进行切换
        //调用write的时候进入内核态，返回的时候进入用户态
        //用户态和内核态之间的切换是有开销的
        fwrite(&i,sizeof(i),1,fp);
    }
    fclose(fp);
    return 0;
}
