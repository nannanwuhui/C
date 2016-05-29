#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
/**
 * 用一个程序写没有问题
 * 两个程序同时写的话，就会有问题
 * 一个汉字是多个字节
 */
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法:%s <字符串>\n",argv[0]);
        return -1;
    }
    //这里有O_APPEND,所以两个进程同时写文件的时候不会覆盖，而是搀和在一起了
    //如果没有O_APPEND的话，就会发生覆盖
    int fd = open("wlock.txt",O_WRONLY | O_CREAT | O_APPEND,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    size_t i,len = strlen(argv[1]);
    for(i = 0;i < len;++i){
        if(write(fd,&argv[1][i],sizeof(argv[1][i])) == -1){
            perror("write");
            return -1;
        }
        sleep(1);
    }
    close(fd);
    return 0;
}
#if 0
开两个窗口，同时执行以下操作
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out 有限公司
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out 达内科技
zn@zn-OptiPlex-9010:~/demo/052816$ cat wlock.txt
�澜���醙���姅���劏��zn@zn-OptiPlex-9010:~/demo/052816$
zn@zn-OptiPlex-9010:~/demo/052816$ rm wlock.txt
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out 达内科技有限公司
zn@zn-OptiPlex-9010:~/demo/052816$ cat wlock.txt
达内科技有限公司zn@zn-OptiPlex-9010:~/demo/052816$
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out 123456789
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out abcdefghijk
zn@zn-OptiPlex-9010:~/demo/052816$ cat wlock.txt
1a2b3c4d5e6f7g8h9ijkzn@zn-OptiPlex-9010:~/demo/052816$
#endif
