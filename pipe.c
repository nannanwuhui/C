#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    printf("父进程:创建管道...\n");
    int pipefd[2];
    if(pipe(pipefd) == -1){
        perror("pipefd");
        return -1;
    }
    printf("父进程:创建进程...\n");
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
        printf("子进程:关闭写端...\n");
        close(pipefd[1]);
        printf("子进程:接收数据...\n");
        for(;;){
            char buf[1024];
            ssize_t rb = read(pipefd[0],buf,sizeof(buf));//阻塞在这里
            if(rb == -1){
                perror("read");
                return -1;
            }
            if(!rb){
                break;
            }
            puts(buf);
        }
        printf("子进程:关闭读端...\n");
        close(pipefd[0]);
        printf("子进程:大功告成!\n");
        return 0;
    }
    printf("父进程:关闭读端...\n");
    close(pipefd[0]);
    printf("父进程：发送数据...\n");
    for(;;){
        char buf[1024];
        gets(buf);//阻塞在这里
        if(!strcmp(buf,"!")){
            break;
        }
        if(write(pipefd[1],buf,(strlen(buf) + 1) * sizeof(buf[0])) == -1){
            perror("write");
            return -1;
        }
    }
    printf("父进程:关闭写端...\n");
    close(pipefd[1]);
    if(wait(0) == -1){
        perror("wait");
        return -1;
    }
    printf("父进程:大功告成!\n");
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/071016$ gcc pipe.c
pipe.c: In function ‘main’:
pipe.c:44:9: warning: ‘gets’ is deprecated (declared at /usr/include/stdio.h:638) [-Wdeprecated-declarations]
         gets(buf);
         ^
/tmp/ccwyQNzy.o: In function `main':
pipe.c:(.text+0x163): warning: the `gets' function is dangerous and should not be used.
zn@zn-OptiPlex-9010:~/demo/071016$ ./a.out
父进程:创建管道...
父进程:创建进程...
父进程:关闭读端...
父进程：发送数据...
子进程:关闭写端...
子进程:接收数据...
aaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaa
hello world
hello world
cmd
cmd
hello niklaus
hello niklaus
xxxyyyzzz
xxxyyyzzz
lajhfa
lajhfa
fjdkfj
fjdkfj
jfdkfjd
jfdkfjd
fjdkfjdlf
fjdkfjdlf
fjdklfjdklj
fjdklfjdklj
hfdkhfdk
hfdkhfdk
jfdklfjdl
jfdklfjdl
fjdlkjfdl
fjdlkjfdl
jfdlkfjd
jfdlkfjd
jfkdfl
jfkdfl
!
父进程:关闭写端...
子进程:关闭读端...
子进程:大功告成!
父进程:大功告成!
#endif
