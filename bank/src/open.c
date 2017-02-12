#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/msg.h>
#include <string.h>
#include "../inc/bank.h"
#include "../inc/dao.h"
void sigint(int signum){
    printf("开户服务:即将停止.\n");
    exit(0);
}
int main(){
    if(signal(SIGINT,sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
    int reqid = msgget(KEY_REQUEST,0);
    if(reqid == -1){
        perror("msgget");
        return -1;
    }
    int resid = msgget(KEY_RESPOND,0);
    if(resid == -1){
        perror("msgget");
        return -1;
    }
    printf("开户服务:启动就绪.\n");
    for(;;){
        OPEN_REQUEST req;
        if(msgrcv(reqid,&req,sizeof(req) - sizeof(req.type),TYPE_OPEN,0) == -1){
            perror("msgrcv");
            continue;
        }
        OPEN_RESPOND res = {req.pid,""};
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
        if(msgsnd(resid,&res,sizeof(res) - sizeof(res.type),0) == -1){
            perror("msgsnd");
            continue;
        }
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/073016/bank/bin$ hexdump -C id.dat
00000000  ea 03 00 00                                       |....|
00000004
#endif
