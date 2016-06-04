#include <stdio.h>
#include <unistd.h>
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法:%s <文件>\n",argv[0]);
        return -1;
    }
    printf("文件%s",argv[1]);
    if(access(argv[1],F_OK) == -1){
        printf("不存在(%m).\n");
    }else{
        if(access(argv[1],R_OK) == -1)
            printf("不可读(%m),");
        else
            printf("可读，");
        if(access(argv[1],W_OK) == -1)
            printf("不可写(%m),");
        else
            printf("可写，");
        if(access(argv[1],X_OK) == -1)
            printf("不可执行(%m),\n");
        else
            printf("可执行。\n");
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060416$ gcc access.c
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out
用法:./a.out <文件>
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out access.c
文件access.c可读，可写，不可执行(Permission denied),
zn@zn-OptiPlex-9010:~/demo/060416$ ls -l access.c
-rw-rw-r-- 1 zn zn 687  6月  4 10:16 access.c
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out a.out
文件a.out可读，可写，可执行。
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out /etc/passwd
文件/etc/passwd可读，不可写(Permission denied),不可执行(Permission denied),
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out /etc/
文件/etc/可读，不可写(Permission denied),可执行。
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out /usr/bin/strace
文件/usr/bin/strace可读，不可写(Permission denied),可执行。
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out /sbin/strace
文件/sbin/strace不存在(No such file or directory).
zn@zn-OptiPlex-9010:~/demo/060416$
#endif
