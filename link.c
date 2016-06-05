#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
    if(argc < 3){
        fprintf(stderr,"用法:%s <文件路径> <链接路径>\n",argv[0]);
        return -1;
    }
    if(link(argv[1],argv[2]) == -1){
        perror("link");
        return -1;
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out link.txt link2.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -l link.txt
-rw-rw-r-- 2 zn zn 0  6月  5 12:02 link.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt(link.txt,link2.txt的硬链接数都是2)
total 16
-rw-rw-r-- 2 zn zn    0  6月  5 12:02 link2.txt
-rw-rw-r-- 2 zn zn    0  6月  5 12:02 link.txt
-rwxrwxr-x 1 zn zn 8699  6月  5 12:01 a.out
-rw-rw-r-- 1 zn zn  313  6月  5 12:01 link.c
zn@zn-OptiPlex-9010:~/demo/060516$ gvim link.txt
zn@zn-OptiPlex-9010:~/demo/060516$ echo "Hello,Link!" > link.txt
zn@zn-OptiPlex-9010:~/demo/060516$ cat link2.txt
Hello,Link!
#endif
