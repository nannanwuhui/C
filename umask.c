#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(){
    //这是shell进程的子进程，在子进程中修改文件权限屏蔽字只会影响子进程
    //不会影响shell父进程
    //但是如果在父进程shell命令行中修改的话，会影响子进程
    /*
    mode_t old = umask(S_IWUSR | S_IXUSR |
                       S_IWGRP | S_IXGRP |
                       S_IWOTH | S_IXOTH);
    */
    mode_t old = umask(0333);
    int fd = open("umask.txt",O_RDWR | O_CREAT | O_TRUNC,0777);
    if(fd == -1){
        perror("open");
        return -1;
    }
    close(fd);
    umask(old);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060416$ ls
access.c  a.out  umask.c
zn@zn-OptiPlex-9010:~/demo/060416$ gcc umask.c
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out
zn@zn-OptiPlex-9010:~/demo/060416$ ls -l umask.txt
-r--r--r-- 1 zn zn 0  6月  4 11:02 umask.txt
zn@zn-OptiPlex-9010:~/demo/060416$ umask
0022
#endif
