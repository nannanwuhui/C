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
        if(execl("./dead","dead",NULL) == -1){
            perror("execl");
            return -1;
        }
        return 0;
    }
    sleep(1);
    printf("%u进程:我是父进程，即将退出。\n",getpid());
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/062616$ gcc exec.c
zn@zn-OptiPlex-9010:~/demo/062616$ ./a.out
10779进程:我是子进程，正在运行...
10779进程：我在运行，按<Ctrl+C>或<Ctrl+\>终止...
10778进程:我是父进程，即将退出。
zn@zn-OptiPlex-9010:~/demo/062616$ kill -2 10779
zn@zn-OptiPlex-9010:~/demo/062616$ kill -2 10779
bash: kill: (10779) - No such process
#endif
