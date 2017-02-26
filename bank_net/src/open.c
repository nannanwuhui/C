#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <wait.h>
#include <errno.h>
#include "../inc/bank.h"
#include "../inc/dao.h"
#include "../inc/network.h"
static int g_sockfd = -1;
void sigint(int signum){
    printf("开户服务:即将停止.\n");
    deinit(g_sockfd);
    exit(0);
}
void sigchld(int signum){
    for(;;){
        //-1表示我可以回收任何子进程，WNOHANG表示以非阻塞的方式
        pid_t pid = waitpid(-1,0,WNOHANG);
        if(pid == -1){
            //错误码不是ECHLD，表示是其他的系统错误
            //这种情况下，打印错误信息，结束进程即可
            if(errno != ECHILD){
                perror("waitpid");
                exit(-1);
            }
            //返回值是-1，错误码是ECHLD，说明所有的子进程都已经回收了，没有
            //子进程了
            printf("开户服务:全部子进程都已退出.\n");
            break;
        }
        if(pid){
            printf("开户服务:发现%u子进程退出.\n",pid);
        }
        else{
            //pid = 0表示暂时没有子进程退出，但是这些子进程还运行着。
            printf("开户服务:暂时没有子进程退出.\n");
            break;
        }
    }
}
int main(){
    if(signal(SIGINT,sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
    if(signal(SIGCHLD,sigchld) == SIG_ERR){
        perror("signal");
        return -1;
    }
    if((g_sockfd = init(TYPE_OPEN)) == -1){
        return -1;
    }
    printf("开户服务:启动就绪.\n");
    OPEN_REQUEST req;
    int connfd = rcvreq(g_sockfd,&req,sizeof(req));
    if(connfd == -1){//走到这里的一定是子进程
        return -1;
    }

    OPEN_RESPOND res = {""};

    ACCOUNT acc;
    if((acc.id = genid()) == -1){
        sprintf(res.error,"创立账户失败!");
        goto send_respond;
    }
    strcpy(acc.name,req.name);
    strcpy(acc.passwd,req.passwd);
    acc.balance = req.balance;
    if(save(&acc) == -1){
        sprintf(res.error,"保存账户失败!");
        goto send_respond;
    }
    res.id = acc.id;
send_respond:
    if(sndres(connfd,&res,sizeof(res)) == -1){
        return -1;
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/073016/bank/bin$ hexdump -C id.dat
00000000  ea 03 00 00                                       |....|
00000004
#endif
