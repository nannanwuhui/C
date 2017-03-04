#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include "../inc/bank.h"
typedef struct tag_Service{
    char srv_path[PATH_MAX + 1];
    pid_t srv_pid;
}SERVICE;
static SERVICE g_srv[] = {
    {"./open",-1},
    {"./query",-1}
};

int start(){
    printf("启动业务服务...\n");
    size_t i;
    for(i = 0;i < sizeof(g_srv)/sizeof(g_srv[0]);i++){
        if((g_srv[i].srv_pid = fork()) == -1){
            perror("vfork");
            return -1;
        }
        if(g_srv[i].srv_pid == 0){
            if(execl(g_srv[i].srv_path,g_srv[i].srv_path,NULL) == -1){
                perror("execl");
                //execl执行失败，-1不知道应该放在哪里，可能会破坏某些有效的数据
                //而在执行后续代码的时候刚好又要用到这个地址，就会出现段错误
                //而使用fork就没有这个问题，因为fork整个进程映像都复制过来了，
                //要堆有堆，要栈有栈，总是有地方放返回值，放的一定是一个合理的空间里。
                //但是vfork就有问题，所有存放变量的地方你都没有，没有数据段，没有堆栈
                //然后你放在了父进程的空间当中，把父进程的进程空间中的一部分空间给覆盖了
                //当父进程要从这个地方拿东西的时候，结果拿的东西就不对了，不一定把父进程的
                //什么东西给覆盖了，影响了父进程的返回。
                //fork就没问题，因为子进程直接将父进程的进程空间给复制过来了，我子进程放
                //返回值的地址是我自己的地方，跟父进程没有关系
//                exit(-1);//使用exit()没有存放返回值的问题，也就不会有段错误了
                return -1;
            }
            return 0;
        }
    }
    return 0;
}
int stop(){
    printf("停止业务服务...\n");
    size_t i;
    for(i = 0;i < sizeof(g_srv)/sizeof(g_srv[0]);i++){
        if(kill(g_srv[i].srv_pid,SIGINT) == -1){
            perror("kill");
            return -1;
        }
    }
    for(;;){
        if(wait(0) == -1){
            if(errno != ECHILD){
                perror("wait");
                return -1;
            }
            //如果wait返回-1,并且错误码是ECHLID,说明所有子进程都收集完了。
            break;
        }
    }
    return 0;
}
int main(){
    //使用atexit比在main函数末尾调用deinit的好处是，不管
    //程序在哪里退出都可以调到deinit.在末尾调用deinit只有在主函数执行到
    //末尾的时候才可以执行deinit
    //但是放在最前面，子进程会继承父进程注册的函数，当子进程结束的时候也会调用deinit,
    //这样当父进程结束调用deinit的时候就会失败!
    if(start() == -1){
//        deinit();//子进程返回失败依然会执行deinit()这一句
        return -1;
    }
    //放在这里子进程启动失败退出，不会调用deinit，这样不会因为一个业务启动失败而
    //销毁消息队列导致其他业务无法进行
    sleep(1);
    printf("按<回车>退出...\n");
    getchar();
    if(stop() == -1){
        return -1;
    }
    return 0;
}

