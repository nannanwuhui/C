#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sighand(int signum){
    printf("%u进程:收到%d信号!\n",getpid(),signum);
}
void updatedb(){
    int i;
    for(i = 0; i < 5;++i){
        printf("%u进程:更新第%d条记录.\n",getpid(),i+1);
        sleep(1);
    }
}
int main(){
    if(signal(SIGINT,sighand) == SIG_ERR){
        perror("signal");
        return -1;
    }
    if(signal(50,sighand) == SIG_ERR){
        perror("signal");
        return -1;
    }
    printf("%u进程:屏蔽%d信号和%d信号.\n",getpid(),SIGINT,50);
    sigset_t new;
    if(sigemptyset(&new) == -1){
        perror("sigemptyset");
        return -1;
    }
    if(sigaddset(&new,SIGINT) == -1){
        perror("sigaddset");
        return -1;
    }
    if(sigaddset(&new,50) == -1){
        perror("sigaddset");
        return -1;
    }
    sigset_t old;
    if(sigprocmask(SIG_SETMASK,&new,&old) == -1){
        perror("sigprocmask");
        return -1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
        pid_t ppid = getppid();
        int i = 0;
        for(i = 0;i < 5;i++){
            printf("%u进程:向%u进程发送%d信号...\n",getpid(),ppid,50);
            kill(ppid,50);
        }
        return 0;
    }
    updatedb();
    sigset_t pend;
    if(sigpending(&pend) == -1){
        perror("sigpending");
        return -1;
    }
    if(sigismember(&pend,SIGINT)){
        printf("%u进程:发现%d信号未决.\n",getpid(),SIGINT);
    }
    if(sigismember(&pend,50)){
        printf("%u进程:发现%d信号未决.\n",getpid(),50);
    }
    printf("%u进程:取消对%d信号和%d信号的屏蔽.\n",getpid(),SIGINT,50);
    if(sigprocmask(SIG_SETMASK,&old,NULL) == -1){
        perror("sigprocmask");
        return -1;
    }
    for(;;);
    return 0;
}
