#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
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
    printf("进程标识(PID): %d\n",getpid());
    int fd = open("lock.txt",O_RDWR | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    const char* text = "ABCDEFGHIJKLMNOPQR";
    if(write(fd,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    //对EFGH加读锁
    printf("对EFGH加读锁");
    //文件头从0开始
    if(rlock(fd,4,4,0) == -1){
        printf("失败:%m\n");
        return -1;
    }
    printf("成功!\n");
    //对MNOP加写锁
    printf("对MNOP加写锁");
    if(wlock(fd,12,4,0) == -1){
        printf("失败:%m\n");
        return -1;
    }
    printf("成功!\n");
    printf("按<回车>，解锁MN...");
    getchar();
    //解锁MN
    ulock(fd,12,2);
    printf("按<回车>，解锁EFGH...");
    getchar();
    //解锁EFGH
    ulock(fd,4,4);
    /**
     * 只要文件描述符一关，什么锁就都没有了。系统内核会自动为你解锁，文件表会被删掉
     * 你加的锁也会从v节点表的锁的链表中删掉
     * 因为只要文件描述符一关，文件描述符和文件指针的对应就会被删掉，
     * 文件表也就没有了，对应v节点表中的锁的链表也就没有了
     */
    close(fd);
    return 0;
}
