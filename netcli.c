#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
//这里是单向的socket
int main(int argc,char* argv[]){
    if(argc < 3){
        fprintf(stderr,"用法:%s <服务器IP地址> <端口号>\n",argv[0]);
        return -1;
    }
    printf("客户机:创建网络数据报套接字...\n");
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
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
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);//把点分十进制转换成网络字节序32位无符号整数
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
    return 0;
}
