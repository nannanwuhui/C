#include <stdio.h>
#include <signal.h>
int main(){
    sigset_t set;
    printf("%lu\n",sizeof(set) * 8);//1024位
    sigfillset(&set);
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    sigdelset(&set,SIGQUIT);
    if(sigismember(&set,SIGINT)){
        printf("有SIGINT信号.\n");
    }
    else{
        printf("没有SIGINT信号.\n");
    }
    if(sigismember(&set,SIGQUIT)){
        printf("有SIGQUIT信号.\n");
    }
    else{
        printf("没有SIGQUIT信号.\n");
    }
    return 0;
}
