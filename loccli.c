#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#define SOCK_FILE "/tmp/sock" //相当于是ip地址和端口号
//这里是单向的socket
int main(void){
    printf("客户机:创建本地数据套接字...\n");
    int sockfd = socket(AF_LOCAL,SOCK_DGRAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    /**
      * 客户机可以绑定，也可以不绑定，它的绑定不是必须的。
      * 什么时候需要绑定？
      * 服务器能够感知客户机的信息以后，还想知道客户机的ip和端口。
      * 客户机可能想以一个特定的什么和服务器相连。让服务器可以对客户机做检查。
      * 这个时候需要绑定。
      * 理论上来说，客户机只要知道服务器地址，客户机的socket就可以跟服务器相连了。
      * 至于要不要携带上客户机自己的地址不是必须的。
      */
    printf("客户机：准备地址并建立连接...\n");
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path,SOCK_FILE);
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("connect");
        return -1;
    }
    printf("客户机:发送数据...\n");
    for(;;){
        printf("> ");
        char buf[1024];
        gets(buf);
        if(!strcmp(buf,"!"))
            break;
        if(write(sockfd,buf,(strlen(buf) + 1) * sizeof(buf[0])) == -1){
            perror("write");
            return -1;
        }
        if(!strcmp(buf,"!!"))
            break;
    }
    printf("客户机：关闭套接字...\n");
    if(close(sockfd) == -1){
        perror("close");
        return -1;
    }
    printf("客户机:结束!\n");
    //sock文件，服务器建立的，由服务器来删除就可以了。
    return 0;
}
