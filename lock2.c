#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
//打印锁
void plock(struct flock lock){
    if(lock.l_type == F_UNLCK){
        printf("没有锁.\n");
    }else{
        printf("%d进程",lock.l_pid);
        switch(lock.l_whence){
            case SEEK_SET:
            printf("在距文件头");
            break;
        case SEEK_CUR:
            printf("在距当前位置");
            break;
         case SEEK_END:
            printf("在距文件尾");
            break;
        }
        printf("%ld字节处，为%ld字节加了",lock.l_start,lock.l_len);
        switch(lock.l_type){
        case F_RDLCK:
            printf("读锁.\n");
            break;
        case F_WRLCK:
            printf("写锁.\n");
            break;
        }
    }
}
//读锁测试
int rtest(int fd,off_t start,off_t len){
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    if(fcntl(fd,F_GETLK,&lock) == -1)
        return -1;
    plock(lock);
    return 0;
}
//写锁测试
int wtest(int fd,off_t start,off_t len){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    if(fcntl(fd,F_GETLK,&lock) == -1)
        return -1;
    plock(lock);
    return 0;
}
//加读锁
int rlock(int fd,off_t start,off_t len,int wait){
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd,wait ? F_SETLKW : F_SETLK,&lock);
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
int main(){
    int fd = open("lock.txt",O_RDWR);
    if(fd == -1){
        perror("open");
        return -1;
    }
    //对CDEF做读锁测试
    printf("对CDEF做读锁测试。");
    if(rtest(fd,2,4) == -1){
        printf("失败:%m\n");
        return -1;
    }
    //对CDEF加读锁
    printf("对CDEF加读锁");
    if(rlock(fd,2,4,0) == -1){
        printf("失败:%m\n");
    }else{
        printf("成功!\n");
        ulock(fd,2,4);
    }
    //对CDEF做写锁测试
    printf("对CDEF做写锁测试。");
    if(wtest(fd,2,4) == -1){
        printf("失败:%m\n");
        return -1;
    }
    //对CDEF加写锁
    printf("对CDEF加写锁");
    if(wlock(fd,2,4,0) == -1){
        printf("失败:%m\n");
    }else{
        printf("成功!\n");
        ulock(fd,2,4);
    }
    //对KLMN做读锁测试
    printf("对KLMN做读锁测试。");
    if(rtest(fd,10,4) == -1){
        printf("失败:%m\n");
        return -1;
    }
    //对KLMN加读锁
    printf("对KLMN加读锁");
    if(rlock(fd,10,4,0) == -1){
        printf("失败:%m\n");
    }else{
        printf("成功!\n");
        ulock(fd,2,4);
    }
    //对KLMN做写锁测试
    printf("对KLMN做写锁测试。");
    if(wtest(fd,10,4) == -1){
        printf("失败:%m\n");
        return -1;
    }
    //对KLMN加写锁
    printf("对KLMN加写锁");
    if(wlock(fd,10,4,0) == -1){
        printf("失败:%m\n");
    }else{
        printf("成功!\n");
        ulock(fd,2,4);
    }
    printf("等待KLMN上的写锁被解除...\n");
    //对KLMN加写锁
    printf("对KLMN加写锁");
    if(wlock(fd,10,4,1) == -1){
        printf("失败:%m\n");
    }else{
        printf("成功!\n");
        ulock(fd,2,4);
    }
    close(fd);
    return 0;
}
