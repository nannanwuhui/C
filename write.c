#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(){
    //uc不会分是文本的还是二进制的，全部都是以二进制流的方式来看待的
    //c语言的文件就是流（一个字节，一个字节组成的流）文件
    int fd = open("write.txt",O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    const char* text = "Hello, World !";
    printf("写入内容:%s\n",text);
    //如果是二进制文件的话，应该写最后的\0,但是文本文件就不用写了，因为\0不是合法的字符
    //\0不在可显示字符的ascii码区间里，\0是给c函数用的，不是文件里必须的。
    size_t towrite = strlen(text) * sizeof(text[0]);//元素的个数*元素字节长度
    ssize_t written = write(fd,text,towrite);
    if(written == -1){
        perror("write");
        return -1;
    }
    printf("期望写入%lu字节，实际写入%ld个字节.\n",towrite,written);
    close(fd);
    return 0;
}
