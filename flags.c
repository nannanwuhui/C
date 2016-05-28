#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
void pflags(int flags){
    printf("文件状态标志(%08X):",flags);
    struct {
        int flag;
        const char* desc;
    } flist[] = {
    {O_RDONLY, "O_RDONLY"},
    {O_WRONLY, "O_WRONLY"},
    {O_RDWR, "O_RDWR,"},
    {O_APPEND, "O_APPEND"},
    {O_CREAT, "O_CREAT"},
    {O_EXCL, "O_EXCL"},
    {O_TRUNC, "O_TRUNC"},
    {O_NOCTTY, "O_NOCTTY"},
    {O_NONBLOCK, "O_NONBLOCK"},
    {O_SYNC, "O_SYNC"},
    {O_DSYNC, "O_DSYNC"},
    {O_RSYNC, "O_RSYNC"},
    {O_ASYNC, "O_ASYNC"},
    };
    size_t i;
    int first = 1;
    for(i = 0;i < sizeof(flist) / sizeof(flist[0]);++i){
        if(flags & flist[i].flag){
            printf("%s%s",first ? "" : "|",flist[i].desc);
            first = 0;
        }
    }
    printf("\n");
}
int main(){
    //默认是阻塞的方式
    int fd = open("flags.txt",O_WRONLY | O_CREAT | O_TRUNC | O_ASYNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    //成功返回标志位，失败返回-1
    int flags = fcntl(fd,F_GETFL);
    if(flags == -1){
        perror("fcntl");
        return -1;
    }
    pflags(flags);//不能获取O_CREAT/O_EXCL/O_TRUNC
    //0表示成功，-1表示失败
    if(fcntl(fd,F_SETFL,O_RDWR | O_APPEND | O_NONBLOCK) == -1){
        perror("fcntl");
        return -1;
    }
    //成功返回标志位，失败返回-1
    if((flags = fcntl(fd,F_GETFL)) == -1){
        perror("fcntl");
        return -1;
    }
    pflags(flags);//只能追加O_APPEND/O_NONBLOCK
    close(fd);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out
文件状态标志(0000A001):O_WRONLY|O_ASYNC
文件状态标志(0000AC01):O_WRONLY|O_APPEND|O_NONBLOCK|O_ASYNC
#endif
