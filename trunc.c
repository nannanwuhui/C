#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
int main(){
    const char* text = "Hello, World !";
    size_t size = (strlen(text) + 1) * sizeof(text[0]);
    int fd = open("trunc.txt",O_RDWR | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    //修改文件的大小
    if(ftruncate(fd,size) == -1){
        perror("ftruncate");
        return -1;
    }
    //MAP_SHARED两个进程都可以访问，这样的话，进入内核缓冲的数据会同步到磁盘上
    //MAP_PRIVATE数据只会进入内核缓冲，不会进入磁盘,自己可读可写，但是其他进程就没办法读了
    //因为文件里没有数据，其他进程不可能去读你的缓冲区。
    //所以如果要和其他进程进行通信的话，一定要用MAP_SHARED
    //将虚拟内存映射到文件
    void* map = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED/*MAP_PRIVATE*/,fd,0);
    if(map == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    memcpy(map,text,size);//strcpy sprintf
    printf("%s\n",(char*)map);
    munmap(map,size);//解除映射
    close(fd);
    return 0;
}
#if 0
gvim trunc.txt
Hello, World !^@//结尾的\0不是可显示字符
#endif
