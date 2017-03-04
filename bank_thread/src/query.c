#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include "../inc/bank.h"
#include "../inc/dao.h"
#include "../inc/network.h"
static int g_sockfd = -1;
void sigint(int signum){
    printf("查询服务:即将停止.\n");
    deinit(g_sockfd);
    exit(0);//exit(0)会关闭所有的文件描述符包括套接字
}
void* thread_proc(void* arg){
    pthread_detach(pthread_self());
    int connfd = (int)arg;
    QUERY_REQUEST req;
    if(rcvreq(connfd,&req,sizeof(req)) == -1){
        return NULL;
    }
    QUERY_RESPOND res = {""};
    ACCOUNT acc;
    if(get(req.id,&acc) == -1){
        sprintf(res.error,"无效账号!");
        goto send_respond;
    }
    if(strcmp(req.name,acc.name)){
        sprintf(res.error,"无效户名!");
        goto send_respond;
    }
    if(strcmp(req.passwd,acc.passwd)){
        sprintf(res.error,"密码错误!");
        goto send_respond;
    }
    res.balance = acc.balance;
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

    if((g_sockfd = init(TYPE_QUERY)) == -1){
        return -1;
    }
    printf("查询服务:启动就绪.\n");
    for(;;){
        int connfd = accreq(g_sockfd);
        if(connfd == -1){
            continue;
        }
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
