#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sigalrm(int signum){
    printf("收到SIGALRM信号!即将退出.\n");
    exit(0);
}
int main(){
    if(signal(SIGALRM,sigalrm) == SIG_ERR){
        perror("signal");
        return -1;
    }
    unsigned int remain = alarm(10);
    printf("定时10秒.\n");
    printf("睡眠2秒...\n");
    sleep(2);
    /*
    remain = alarm(5);
    printf("定时5秒,剩余%u秒.\n",remain);
    */
    remain = alarm(0);
    printf("取消定时，剩余%u秒.\n",remain);
    for(;;);
    return 0;
}
