#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
//使用信号可以做到进程间的通信
void sigchld(int signum){
    pid_t pid = wait(0);//回收子进程
    printf("%u进程:%u进程已死，吼吼!\n",getpid(),pid);
}
void sigint(int signum){
    printf("%u进程:我要死了,5555～～～～\n",getpid());
    //有的函数本身具有发送信号的功能，比如说abort()，exit()
    exit(0);//自动向父进程发送SIGCHLD信号
}
int main(void){
    //子进程要死掉的时候，在退出（exit）之前，会给父进程发送SIGCHLD信号
    if(signal(SIGCHLD,sigchld) == SIG_ERR){
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
        if(signal(SIGINT,sigint) == SIG_ERR){
            perror("signal");
            return -1;
        }
        for(;;);
        return 0;
    }
    sleep(1);
    printf("%u进程:我是父进程，我要杀死%u进程...\n",getpid(),pid);
    //kill只是发送信号，不会等到信号处理完才返回，它只是把信号给内核，然后内核
    //把信号放到进程控制块里就完了，放在进程的信号队列里
    //kill返回并不能保证信号已经被处理了，发送信号和信号处理之间是异步的
    //就像送信一样，我把信放在你家门口的信箱里就完了，至于你什么时候看信，怎么处理，
    //我不管
    if(kill(pid,SIGINT) == -1){
        perror("kill");
        return -1;
    }
    sleep(1);
    return 0;
}
