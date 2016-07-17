#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>
int main(){
    printf("获取消息队列...\n");
    key_t key = ftok(".",100);
    if(key == -1){
        perror("ftok");
        return -1;
    }
    int msqid = msgget(key,0);
    if(msqid == -1){
        perror("msgget");
        return -1;
    }
    printf("从消息队列(0x%08x/%d)接收消息...\n",key,msqid);
    for(;;){
        struct {
            long mtype;
            char mtext[1024];
        }msgbuf = {};
        //返回接收到的字节数也不包括消息类型，长度-sizeof(msgbuf.mtext[0])是为了
        //保留字符串末尾的\0
        ssize_t msgsz = msgrcv(msqid,&msgbuf,sizeof(msgbuf.mtext) -
               sizeof(msgbuf.mtext[0]),1234,MSG_NOERROR | IPC_NOWAIT);
        if(msgsz == -1){
            if(errno == EIDRM){
                printf("消息队列(0x%08x/%d)已销毁!\n",key,msqid);
                break;
            }
            else if(errno == ENOMSG){
                printf("暂时没有消息，干点儿别的吧!\n");
                sleep(1);
            }
            else{
                perror("msgrcv");
                return -1;
            }
        }
        else{
            printf("%04ld< %s\n",msgsz,msgbuf.mtext);
        }
    }
    printf("大功告成!\n");
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/071716$ ./rmsq
获取消息队列...
从消息队列(0x6406374c/0)接收消息...
0006< hello
0006< world
0007< tarena
  zn@zn-OptiPlex-9010:~$ ipcs -q

  ------ Message Queues --------
  key        msqid      owner      perms      used-bytes   messages
  0x6406374c 0          zn         644        0            0
//因为当rmsq在干别的事情的时候，wmsq删除了消息队列，然后rmsq去msgrcv的时候msqid已经失效了。
//只有当rmsq在阻塞的时候，wmsq销毁消息队列，rmsg的msgrcv才会返回-1,errno为EIDRM
  暂时没有消息，干点儿别的吧!
  暂时没有消息，干点儿别的吧!
  msgrcv: Invalid argument
#endif
