#include <stdio.h>
#include <unistd.h>
#include <signal.h>
//效果是持续的。内核收到SIGINT信号以后调用这个进程空间代码段中sigint这个函数
void sigint(int signum){
    //老式的unix可能是这样做的，在处理信号处理函数之前先恢复默认
    signal(signum,SIG_DFL);
    printf("%u进程:收到%d信号!\n",getpid(),signum);
    signal(signum,sigint/*SIG_DFL*/);//某些unix系统需要加上这一句才能持续生效
}
void sigkill(int signum){
    printf("%u进程:收到SIGKILL信号!\n",getpid());

}
int main(){
    //\\：转义，signal把sigint函数注册到内核。
    if(signal(SIGINT,/*SIG_IGN*/sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
#if 0
    //signal: Invalid argument
    if(signal(SIGKILL,SIG_IGN/*sigkill*/) == SIG_ERR){
        perror("signal");
        return -1;
    }
#endif
    printf("%u进程：我在运行，按<Ctrl+C>或<Ctrl+\\>终止...\n",getpid());
    //进程正在执行for()循环，当收到信号的时候，先去执行信号处理函数，然后
    //再过来执行for()循环
    for(;;);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/061916$ ./a.out
4514进程：我在运行，按<Ctrl+C>或<Ctrl+\>终止...
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!
^C4514进程:收到SIGINT信号!

^\Quit (core dumped)

zn@zn-OptiPlex-9010:~/demo/061916$ gcc signal.c
zn@zn-OptiPlex-9010:~/demo/061916$ ./a.out
2820进程：我在运行，按<Ctrl+C>或<Ctrl+\>终止...
^C^C^C^C^C^C^C^C^\Quit (core dumped)
#endif
