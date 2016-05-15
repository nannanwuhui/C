#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(void){
    int fd = open("read.txt",O_RDONLY);//标c里面的r模式，文件不存在就会失败
    if(fd == -1){
        perror("open");
        return -1;
    }
    char text[256] = {};//初始化一下，全是\0
    size_t toread = sizeof(text);
    ssize_t readed = read(fd,text,toread);
    if(readed == -1){
        perror("read");
        return -1;
    }
    printf("期望读取%lu字节，实际读取%ld字节\n",toread,readed);
    //从文件里读，文件里有什么，就读出什么，文件里的字符串没有\0结尾
    //我们以前所说的\0结尾那是内存里的。我们去调用c函数，它给我们做字符串处理都补一个\0
    //文件里放字符串可不带\0
//    text[readed] = '\0';//补一个\0
    //补一个\0,第readed/sizeof(text[0])个字符赋成0,知道字符串从哪停了
    text[readed/sizeof(text[0])] = '\0';
    printf("读取内容:%s\n",text);
    close(fd);
    return 0;
}
#if 0
用gvim或者vi编辑的文件，最后保存的时候会自动加上\n
zn@zn-OptiPlex-9010:~/demo/051516$ hexdump -C read.txt
00000000  e4 bb 8a e5 a4 a9 e5 a4  a9 e6 b0 94 e4 b8 8d e9  |................|
00000010  94 99 ef bc 8c e5 a5 bd  e5 87 89 e5 bf ab 21 0a(\n)  |..............!.|
00000020
#endif
