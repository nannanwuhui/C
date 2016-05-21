#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(void){
    int fd = open("sysio.dat",O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    unsigned int i;
    for(i = 0;i < 100000;++i){
        write(fd,&i,sizeof(i));
    }
    close(fd);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052116$ time ./sysio

real	0m0.128s
user	0m0.025s
sys	0m0.103s
zn@zn-OptiPlex-9010:~/demo/052116$ time ./stdio

real	0m0.006s
user	0m0.004s
sys	0m0.002s
zn@zn-OptiPlex-9010:~/demo/052116$
标准库会考虑优化，其中最典型的优化就是缓冲区优化
#endif
