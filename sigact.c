#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sigint1(int signum){
    printf("收到%d信号!睡眠中...\n",signum);
    sleep(5);
    printf("睡醒了.\n");
}
//^C收到发自0进程的2信号!
/**
  * 1、按键盘Ctrl+C是硬件中断，硬件中断被驱动捕获，驱动是内核的一部分。
  * ０进程代表内核。所以会收到发自０进程的２信号
  */
void sigint2(int signum,siginfo_t* si,void* pv){
    printf("收到发自%u进程的%d信号!\n",si->si_pid,signum);
}
int main(){
    struct sigaction act = {};
    /*
    printf("睡眠中只屏蔽SIGINT,不屏蔽SIGQUIT.\n");
    act.sa_handler = sigint1;
    *//*
    printf("睡眠中既屏蔽SIGINT,也屏蔽SIGQUIT.\n");
    act.sa_handler = sigint1;
    sigemptyset(&act.sa_mask);
    //信号处理函数被处理的过程中3信号被屏蔽，信号处理函数执行完毕后
    //自动打开屏蔽后，３信号被处理
    sigaddset(&act.sa_mask,SIGQUIT);
    *//*
    printf("睡眠中既不屏蔽SIGINT,也不屏蔽SIGQUIT.\n");
    act.sa_handler = sigint1;
    act.sa_flags = SA_NOMASK;
    *//*
    printf("睡眠中不屏蔽SIGINT,只屏蔽SIGQUIT.\n");
    act.sa_handler = sigint1;
    act.sa_flags = SA_NOMASK;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    *//*
    printf("附带更多信号信息.\n");
    act.sa_sigaction = sigint2;
    act.sa_flags = SA_SIGINFO;
    */
    printf("一次性信号处理.\n");
    act.sa_handler = sigint1;
    act.sa_flags = SA_RESETHAND;
    if(sigaction(SIGINT,&act,NULL) == -1){
        perror("sigaction");
        return -1;
    }
    for(;;){
        pause();
    }
    return 0;
}
