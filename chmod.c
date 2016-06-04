#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(){
    int fd = open("chmod.txt",O_RDWR | O_CREAT | O_TRUNC,0644);
    if(fd == -1){
        perror("open");
        return -1;
    }
    //7 = 4（setuid）+2(setgid)+1(粘滞)
//    if(fchmod(fd,07654) == -1){//rwSr-sr-T,
    if(fchmod(fd,S_ISUID | S_ISGID | S_ISVTX |
              S_IRUSR | S_IWUSR |
              S_IRGRP | S_IXGRP |
              S_IROTH) == -1){
        perror("fchmod");
        return -1;
    }
    close(fd);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060416$ gcc chmod.c
zn@zn-OptiPlex-9010:~/demo/060416$ ./a.out
zn@zn-OptiPlex-9010:~/demo/060416$ ls -l chmod.txt
-rwSr-sr-T 1 zn zn 0  6月  4 11:25 chmod.txt
#endif
