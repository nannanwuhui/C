#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
void sigint(int signum){
    printf("%u进程:收到了SIGINT信号!\n",getpid());
}
int main(){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
        if(signal(SIGINT,sigint) == SIG_ERR){
            perror("signal");
            return -1;
        }
        printf("%u进程：我是子进程,小睡10秒...\n",getpid());
        unsigned int left = sleep(10);
        printf("%u进程：我被唤醒了，还剩%u秒没睡，即将退出...\n",getpid(),left);
        return 0;
    }
    sleep(/*3*/15);
    printf("%u进程:我是父进程，向%u进程发送SIGINT信号...\n",getpid(),pid);
    if(kill(pid,SIGINT) == -1){
        perror("kill");
        return -1;
    }
    if((pid = wait(0)) == -1){
        perror("wait");
        return -1;
    }
    printf("%u进程:%u进程已退出。\n",getpid(),pid);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/062616$ ./a.out
20593进程：我是子进程,小睡10秒...
20593进程：我被唤醒了，还剩0秒没睡，即将退出...
20592进程:我是父进程，向20593进程发送SIGINT信号...
20592进程:20593进程已退出。

zn@zn-OptiPlex-9010:~/demo/062616$ gcc sleep.c
zn@zn-OptiPlex-9010:~/demo/062616$ ./a.out
20093进程：我是子进程,小睡10秒...
20092进程:我是父进程，向20093进程发送SIGINT信号...
20093进程:收到了SIGINT信号!
20093进程：我被唤醒了，还剩7秒没睡，即将退出...
20092进程:20093进程已退出。
#endif
