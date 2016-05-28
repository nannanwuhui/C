#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(){
    int fd1 = open("fdup1.txt",O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd1 == -1){
        perror("open");
        return -1;
    }
    printf("fd1 = %d\n",fd1);
    int fd2 = open("fdup2.txt",O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd2 == -1){
        perror("open");
        return -1;
    }
    printf("fd2 = %d\n",fd2);
    /*
    int fd3 = fcntl(fd1,F_DUPFD,fd2);
    if(fd3 == -1){
        perror("fcntl");
        return -1;
    }
    */
    /**
     * 这样做的话，fd1,fd2,fd3的值肯定是一样的
     * fdup1.txt文件中，会有123,456,789
     * 但是fdup2.txt中，什么也没有
     * dup2关闭fd2，然后在fd2的位置放fd1对应的文件指针的拷贝
     * fd1,fd2,fd3都对应同一个文件
     */
    int fd3 = dup2(fd1,fd2);
    if(fd3 == -1){
        perror("dup2");
        return -1;
    }
    printf("fd3 = %d\n",fd3);//fd1和fd3对应着同一个文件表
    const char* text = "123";
    if(write(fd1,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    text = "456";
    if(write(fd2,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    text = "789";
    if(write(fd3,text,strlen(text) * sizeof(text[0])) == -1){
        perror("write");
        return -1;
    }
    close(fd3);
    close(fd2);
    close(fd1);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052816$ gcc fdup.c
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out
fd1 = 3
fd2 = 4
fd3 = 4
zn@zn-OptiPlex-9010:~/demo/052816$ cat fdup1.txt
123456789zn@zn-OptiPlex-9010:~/demo/052816$ cat fdup2.txt
zn@zn-OptiPlex-9010:~/demo/052816$
#endif
#if 0
zn@zn-OptiPlex-9010:~/demo/052816$ gcc fdup.c
zn@zn-OptiPlex-9010:~/demo/052816$ ./a.out
fd1 = 3
fd2 = 4
fd3 = 5
zn@zn-OptiPlex-9010:~/demo/052816$ cat fdup1.txt
123789zn@zn-OptiPlex-9010:~/demo/052816$ cat fdup2.txt
456zn@zn-OptiPlex-9010:~/demo/052816$
#endif
