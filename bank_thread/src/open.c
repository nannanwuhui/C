#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include "../inc/bank.h"
#include "../inc/dao.h"
#include "../inc/network.h"
static int g_sockfd = -1;
void sigint(int signum){
    printf("开户服务:即将停止.\n");
    deinit(g_sockfd);
    exit(0);
}
void* thread_proc(void* arg){
    pthread_detach(pthread_self());//不回收，也不等待
    int connfd = (int)arg;
    OPEN_REQUEST req;
    if(rcvreq(connfd,&req,sizeof(req)) == -1){
        return NULL;//走到这里的一定是子进程
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
        return NULL;
    }
    return NULL;
}
int main(){
    if(signal(SIGINT,sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
    if((g_sockfd = init(TYPE_OPEN)) == -1){
        printf("init失败!\n,g_sockfd = %d",g_sockfd);
        return -1;
    }
    printf("开户服务:启动就绪.\n");
    for(;;){
        int connfd = accreq(g_sockfd);
        if(connfd == -1)
            continue;
        pthread_t tid;
        pthread_create(&tid,NULL,thread_proc,(void*)connfd);
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/073016/bank/bin$ hexdump -C id.dat
00000000  ea 03 00 00                                       |....|
00000004
#endif
