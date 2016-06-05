#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>//最大的路径，最大的整数是多少，浮点数的最高精度类似这样的当前系统的一些最值
int main(int argc,char* argv[]){
    if(argc < 3){
        fprintf(stderr,"用法:%s <文件> <软连接>\n",argv[0]);
        return -1;
    }
    //建立软连接
    if(symlink(argv[1],argv[2]) == -1){
        perror("symlink");
        return -1;
    }
    char slink[PATH_MAX + 1] = {};
    //sizeof(slink) - sizeof(slink[0])防止覆盖slink中的\0
    if(readlink(argv[2],slink,sizeof(slink) - sizeof(slink[0])) == -1){
        perror("readlink");
        return -1;
    }
    printf("%s是%s的软连接。\n",argv[2],slink);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out none123456789 none.link
none.link是none123456789的软连接。
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 24
软连接文件的内容就是目标文件的路径
lrwxrwxrwx 1 zn zn   13  6月  5 14:49 none.link -> none123456789(13个字节)
-rw-rw-r-- 1 zn zn 1887  6月  5 14:47 slink.c
-rwxrwxr-x 1 zn zn 8869  6月  5 14:40 a.out
-rw-rw-r-- 1 zn zn 2602  6月  5 12:24 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c


zn@zn-OptiPlex-9010:~/demo/060516$ ls
a.out  link.c  slink.c  unlink.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out
用法:./a.out <文件> <软连接>
zn@zn-OptiPlex-9010:~/demo/060516$ ls
a.out  link.c  slink.c  unlink.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out none.txt none.link
none.link是none.txt的软连接。
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 24
lrwxrwxrwx 1 zn zn    8  6月  5 14:43 none.link -> none.txt(黑底红字，因为none.txt根本就不存在，这是一个坏链接)
-rw-rw-r-- 1 zn zn  743  6月  5 14:42 slink.c
-rwxrwxr-x 1 zn zn 8869  6月  5 14:40 a.out
-rw-rw-r-- 1 zn zn 2602  6月  5 12:24 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$ touch none.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 24
-rw-rw-r-- 1 zn zn    0  6月  5 14:43 none.txt
lrwxrwxrwx 1 zn zn    8  6月  5 14:43 none.link -> none.txt(八个字节存的就是none.txt)
-rw-rw-r-- 1 zn zn  743  6月  5 14:42 slink.c
-rwxrwxr-x 1 zn zn 8869  6月  5 14:40 a.out
-rw-rw-r-- 1 zn zn 2602  6月  5 12:24 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$
#endif
