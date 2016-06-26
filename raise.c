#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//不是递归而是循环，调用raise函数，raise函数马上就结束了，函数栈也就没有了
void sigint(int signum){
    printf("%u进程:永别了!\n",getpid());
//    exit(0);
    //在这里睡眠是没有用的，还是看不到死循环的执行，因为这不是两个线程，
    //死循环不会被调度
    //在执行信号处理函数的时候，进程会被挂起。
//    sleep(1);
    raise(SIGINT);//raise不等待返回，如果raise等待返回的话，函数栈可能会撑爆
}
int main(){
    if(signal(SIGINT,sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
    printf("%u进程:我要自杀..\n",getpid());
//    if(raise(SIGINT) == -1){
    if(kill(getpid(),SIGINT) == -1){
        perror("raise");
        return -1;
    }
    //在执行信号处理的过程当中，主进程还是在for循环里转
    //信号是一种软中断，不管你现在在做什么，我都可以暂停你现在所做的工作，去处理
    //我的信号处理的工作，就算是你的线程中现在有某种原子性的操作，有信号来了，也会被
    //打断，去执行信号处理的工作
    for(;;){
        printf("死循环...\n");
    }
    return 0;
}
