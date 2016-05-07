#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h> //memory manage
//所有的动态内存都是在堆里面的
#define MAX_TEXT 256
int main(){
    char* psz = (char*)mmap(NULL,
                             MAX_TEXT * sizeof(char),
                             PROT_READ | PROT_WRITE,//比如第一个bit为1,表示可读，第二个bit位为1表示可写。按位或以后，就是可读可写了
                             MAP_PRIVATE | MAP_ANONYMOUS,
                             0,
                             0);
    if(psz == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    sprintf(psz,"Hello,Memory!");
    printf("%s\n",psz);
    printf("psz = %p\n",psz);
    printf("查看/proc/%u/maps,按<回车>退出...",getpid());
    getchar();
    if(munmap(psz,MAX_TEXT * sizeof(char)) == -1){
        perror("munmap");
        return -1;
    }
    return 0;
}
