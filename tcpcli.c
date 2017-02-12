#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc,char* argv[]){
    if(argc < 3){
        fprintf(stderr,"用法:%s <服务器IP地址>　<端口号>\n",argv[0]);
        return -1;
    }
    printf("客户机:创建网络数据流套接字...\n");
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    printf("客户机:准备地址并连接...\n");
    //客户机的端口号是随机生成的
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));//主机字节数序转网络字节序
    addr.sin_addr.s_addr = inet_addr(argv[1]);//把点分十进制转换成32位无符号整数
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("connect");
        return -1;
    }
    printf("客户机:发送请求并接收响应...\n");
    //程序走到这里，三次握手还没有完成，只是客户机发出了ACK，协议栈肯定是收到了，但是
    //服务器如果这个时候没有调用accept的话，服务器就没有收到ACK，accept没有返回．
    //三次握手没有建立，当accept返回的时候，三次握手才算建立起来了
    for(;;){
        printf("> ");
        char buf[1024];
        gets(buf);
        if(!strcmp(buf,"!"))
            break;
        if(send(sockfd,buf,(strlen(buf) + 1) * sizeof(buf[0]),0) == -1){
            perror("send");
            return -1;
        }
        ssize_t rb = recv(sockfd,buf,sizeof(buf),0);
        if(rb == -1){
            perror("recv");
            return -1;
        }
        if(rb == 0){
            printf("客户机：服务器已宕机!\n");
            break;
        }
        printf("< %s\n",buf);
    }
    printf("客户机:关闭套接字...\n");
    if(close(sockfd) == -1){
        perror("close");
        return -1;
    }
    printf("客户机:结束!\n");
    return 0;
}
