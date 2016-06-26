#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
//按Ctrl+C，执行pause，进程进入睡眠状态，停止打印随机数，
//按Ctrl+\,执行onsignal，结束以后，进程被唤醒，继续打印随机数
/**
 * 1、信号处理函数是可重入函数，
 * 可重入函数:这个函数还没有执行完的时候，就可以再次执行这个函数
 * ２、信号处理函数是由内核来调用的。
 */
void onsignal(int signum){
    if(signum == SIGINT)
        pause();
}
int main(){
    srand(time(NULL));
    if(signal(SIGINT,onsignal) == SIG_ERR){
        perror("signal");
        return -1;
    }
    /**
     * 1、如果不将SIGQUIT的信号处理函数设置为onsignal,使用默认的处理方式的话
     * 首先会将进程唤醒，然后杀死进程,
     * 2、如果是忽略这个信号的话，内核不会向进程递送这个信号，pause根本就不会
     * 被唤醒
     */
    if(signal(SIGQUIT,onsignal/*SIG_IGN*/) == SIG_ERR){
        perror("signal");
        return -1;
    }
    for(;;)
        printf("%d\n",rand());
    return 0;
}
