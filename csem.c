#include <stdio.h>
#include <errno.h>
#include <sys/sem.h>
int pleft(int semid){
    int val = semctl(semid,0,GETVAL);
    if(val == -1){
        perror("semctl");
        return -1;
    }
    printf("还剩%d册.\n",val);
    return 0;
}
int main(){
    printf("创建信号量...\n");
    key_t key = ftok(".",100);
    if(key == -1){
        perror("ftok");
        return -1;
    }
    int semid = semget(key,1,0644 | IPC_CREAT | IPC_EXCL);
    if(semid == -1){
        perror("semget");
        return -1;
    }
    printf("初始化信号量...\n");
    if(semctl(semid,0,SETVAL,5) == -1){
        perror("semctl");
        return -1;
    }
    int quit = 0;
    while(!quit){
        printf("------\n");
        printf("三国演义\n");
        printf("------\n");
        printf("[1]借阅\n");
        printf("[2]归还\n");
        printf("[0]退出\n");
        printf("------\n");
        printf("请选择:");
        int sel = -1;
        scanf("%d",&sel);
        switch(sel){
        case 0:
            quit = 1;
            break;
        case 1:{
            printf("请稍候...\n");
//            struct sembuf sops = {0,-1,0};//阻塞模式
            struct sembuf sops = {0,-1,IPC_NOWAIT};
            if(semop(semid,&sops,1) == -1){
                if(errno == EAGAIN){
                    printf("暂时无书，下回再试.\n");
                    break;
                }
                perror("semop");
                return -1;
            }
            printf("恭喜恭喜，借阅成功.\n");
            pleft(semid);
            break;
        }
        case 2:{
            struct sembuf sops = {0,1,0};//阻塞模式(加资源不可能会阻塞)
            if(semop(semid,&sops,1) == -1){
                perror("semop");
                return -1;
            }
            printf("好借好还，再借不难.\n");
            pleft(semid);
            break;
        }
        default:
            printf("无效选择!\n");
            //清理输入流里的垃圾
            scanf("%*[^\n]");
            scanf("%*c");
            break;
        }
    }
    printf("销毁信号量...\n");
    if(semctl(semid,0,IPC_RMID) == -1){
        perror("semctl");
        return -1;
    }
    printf("下班回家!\n");
    return 0;
}
