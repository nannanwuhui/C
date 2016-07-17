#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
int main(){
    printf("创建消息队列...\n");
    key_t key = ftok(".",100);
    if(key == -1){
        perror("ftok");
        return -1;
    }
    int msqid = msgget(key,0644 | IPC_CREAT | IPC_EXCL);
    if(msqid == -1){
        perror("msgget");
        return -1;
    }
    printf("向消息队列(0x%08x/%d)发送数据...\n",key,msqid);
    for(;;){
        printf("> ");
        struct {
            long mtype;
            char mtext[1024];
        } msgbuf = {1234,""};
        gets(msgbuf.mtext);
        if(!strcmp(msgbuf.mtext,"!")){
            break;
        }
        if(msgsnd(msqid,&msgbuf,
                  (strlen(msgbuf.mtext) + 1) * sizeof(char),0) == -1){
            perror("msgsnd");
            return -1;
        }
    }
    printf("销毁消息队列(0x%08x/%d)...\n",key,msqid);
    if(msgctl(msqid,IPC_RMID,NULL) == -1){
        perror("msgctl");
        return -1;
    }
    printf("大功告成!\n");
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/071716$ ./wmsq
创建消息队列...
向消息队列(0x6406374c/0)发送数据...
> hello
> world
>
zn@zn-OptiPlex-9010:~$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x6406374c 0          zn         644        12           2


#endif

