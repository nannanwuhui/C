#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(){
    int fd1 = open("same.txt", O_RDWR | O_CREAT | O_TRUNC,0664);
    if(fd1 == -1){
        perror("open");
        return -1;
    }
    printf("fd1 = %d\n",fd1);
    int fd2 = open("same.txt", O_RDWR,0664);
    if(fd2 == -1){
        perror("dup");
        return -1;
    }
    printf("fd2 = %d\n",fd2);
    const char* text = "Hello, World !";
    if(write(fd1,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    text = "Linux";
    if(write(fd2,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    close(fd1);
    close(fd2);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052816$ gcc same.c
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out
fd1 = 3
fd2 = 4
zn@zn-OptiPlex-9010:~/demo/052816$ cat same.txt
Linux, World !zn@zn-OptiPlex-9010:~/demo/052816$
#endif
