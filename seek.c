#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
    int fd = open("seek.txt",O_RDWR | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    const char* text = "Hello, World !";
    //strlen(text):字符串有多少个字符(多少个元素)，sizeof(text[0]):一个字符多少个字节（一个元素多少个字节）
    if(write(fd,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    //写完Hello,World!之后当前文件的位置是在!之后的下一个位置
    if(lseek(fd,-7,SEEK_CUR) == -1){
        perror("lseek");
        return -1;
    }
    off_t pos = lseek(fd,0,SEEK_CUR);//ftell就是这样获取当前文件的偏移量的
    if(pos == -1){
        perror("lseek");
        return -1;
    }
    printf("当前文件位置:%ld\n",pos);//off_t就是一个long
    text = "Linux";
    if(write(fd,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    if(lseek(fd,8,SEEK_END) == -1){
        perror("lseek");
        return -1;
    }
    text = "<-这里有个漏洞 ! ";
    if(write(fd,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    //vi(gvim)会用^@表示空洞
    //获取文件大小,返回距离文件尾0个字节的位置，就是文件尾了
    off_t size = lseek(fd,0,SEEK_END);//标c需要fseek()到文件尾再调用ftell
    if(size == -1){
        perror("lseek");
        return -1;
    }
    printf("文件大小:%ld字节\n",size);
    close(fd);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052116$ gcc seek.c
zn@zn-OptiPlex-9010:~/demo/052116$ ./a.out
当前文件位置:7
文件大小:45字节
zn@zn-OptiPlex-9010:~/demo/052116$ ls -l seek.txt
-rw-rw-r-- 1 zn zn 45  5月 21 15:28 seek.txt

zn@zn-OptiPlex-9010:~/demo/052116$ hexdump -C seek.txt(00代表一个空洞)
00000000  48 65 6c 6c 6f 2c 20 4c  69 6e 75 78 20 21 00 00  |Hello, Linux !..|
00000010  00 00 00 00 00 00 3c 2d  e8 bf 99 e9 87 8c e6 9c  |......<-........|
00000020  89 e4 b8 aa e6 bc 8f e6  b4 9e 21                 |..........!|
0000002b
#endif
