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
    int fd = open("wlock.txt",O_RDONLY,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    char buf[1024];
    ssize_t readed;
    while((readed = read(fd,buf,sizeof(buf))) > 0)
        write(STDOUT_FILENO,buf,readed);
    if(readed == -1){
        perror("read");
        return -1;
    }
    close(fd);
    return 0;
}
