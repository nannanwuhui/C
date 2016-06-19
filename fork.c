#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sigint(int signum){
    printf("%u进程:收到了SIGINT信号!\n",getpid());
}
int main(){
    if(signal(SIGINT,sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
    if(signal(SIGQUIT,SIG_IGN) == SIG_ERR){
        perror("signal");
        return -1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
        printf("%u进程:我是子进程，正在运行...\n",getpid());
        for(;;);
        return 0;
    }
    sleep(1);
    printf("%u进程:我是父进程，即将退出。\n",getpid());
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/061916$ gcc fork.c
zn@zn-OptiPlex-9010:~/demo/061916$ ./a.out
20977进程:我是子进程，正在运行...
20976进程:我是父进程，即将退出。
zn@zn-OptiPlex-9010:~/demo/061916$
zn@zn-OptiPlex-9010:~/demo/061916$
zn@zn-OptiPlex-9010:~/demo/061916$
zn@zn-OptiPlex-9010:~/demo/061916$
zn@zn-OptiPlex-9010:~/demo/061916$ ps -eaf | grep 20977
zn       20977  1889 99 18:54 pts/0    00:01:14 ./a.out
zn       21281 23297  0 18:55 pts/0    00:00:00 grep --color=auto 20977
zn@zn-OptiPlex-9010:~/demo/061916$ kill -2 20977
20977进程:收到了SIGINT信号!
zn@zn-OptiPlex-9010:~/demo/061916$ kill -2 20977
20977进程:收到了SIGINT信号!
zn@zn-OptiPlex-9010:~/demo/061916$ kill -3 20977
zn@zn-OptiPlex-9010:~/demo/061916$ kill -3 20977
zn@zn-OptiPlex-9010:~/demo/061916$ kill -3 20977
zn@zn-OptiPlex-9010:~/demo/061916$ kill -3 20977
zn@zn-OptiPlex-9010:~/demo/061916$ kill -2 20977
20977进程:收到了SIGINT信号!
zn@zn-OptiPlex-9010:~/demo/061916$ kill -2 20977
20977进程:收到了SIGINT信号!
zn@zn-OptiPlex-9010:~/demo/061916$
#endif
