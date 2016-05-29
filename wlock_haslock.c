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
//大多数系统调用是阻塞的，如果需要非阻塞的模式，需要特殊的设置
//fcntl F_SETLK是非阻塞的，F_SETLKW是阻塞的
//写锁测试
//返回
//1 - 可加写锁
//0 - 不可加写锁
//-1 系统错误
int wtest(int fd,off_t start,off_t len){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    if(fcntl(fd,F_GETLK,&lock) == -1)
        return -1;
    if(lock.l_type == F_UNLCK)
        return 1;
    return 0;
}
//加写锁
int wlock(int fd,off_t start,off_t len,int wait){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd,wait ? F_SETLKW : F_SETLK,&lock);
}
//解锁
int ulock(int fd,off_t start,off_t len){
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd,F_SETLK,&lock);
}
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法:%s <字符串>\n",argv[0]);
        return -1;
    }
    int fd = open("wlock.txt",O_WRONLY | O_CREAT | O_APPEND,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    /**
     * 如果一个进程先加上了写锁，另外一个进程就得死等，不能做别的事情。
     * 两种方案:
     * 1、先试着加写锁（等待模式），如果无法成功，就去做别的事情，定时再试着去加锁，如果可以
     * 加锁成功，就去加锁。
     * ２、不用等待的模式，如果返回EACEES或者EAGAIN,说明别人锁着呢，你就去做别的事情
     * 什么时候成功了，就开始写文件。
     */
    /*int unlock = 0;
    do{
        if((unlock = wtest(fd,0,0)) == -1){
            perror("wtest");
            return -1;
        }
        if(!unlock){
            printf("该文件已被锁定，稍后再试...\n");
            //空闲处理
            //...
        }
    }while(!unlock);
    if(wlock(fd,0,0,0) == -1){
        perror("wlock");
        return -1;
    }
    */
    while(wlock(fd,0,0,0) == -1){
        if(errno != EACCES && errno != EAGAIN){
            perror("wlock");
            return -1;
        }
        printf("该文件已被锁定，稍后再试...\n");
        //空闲处理
        //...
    }
    /*
    if(wlock(fd,0,0,1) == -1){
        perror("wlock");
        return -1;
    }*/
    size_t i,len = strlen(argv[1]);
    for(i = 0;i < len;++i){
        if(write(fd,&argv[1][i],sizeof(argv[1][i])) == -1){
            perror("write");
            return -1;
        }
        sleep(1);
    }
    if(ulock(fd,0,0) == -1){
        perror("ulock");
        return -1;
    }
    close(fd);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052916$ gcc wlock.c -o wlock
zn@zn-OptiPlex-9010:~/demo/052916$ ./wlock 达内科技
zn@zn-OptiPlex-9010:~/demo/052916$
zn@zn-OptiPlex-9010:~/demo/052916$ ./wlock 有限公司
zn@zn-OptiPlex-9010:~/demo/052916$ cat wlock.txt
达内科技有限公司zn@zn-OptiPlex-9010:~/demo/052916$
#endif
