#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../inc/network.h"

//服务端 返回初始化好的，可以用来侦听连接的套接字描述符，失败返回-1
int init(unsigned short type){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(type);//主机字节序转网络字节序
    addr.sin_addr.s_addr = INADDR_ANY;//可以用任意的ip地址
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("bind");
        close(sockfd);
        return -1;
    }
    if(listen(sockfd,1024) == -1){
        perror("listen");
        close(sockfd);
        return -1;
    }
    return sockfd;
}
void deinit(int sockfd){
    close(sockfd);
}
int accreq(int sockfd){
    struct sockaddr_in addrcli = {};
    socklen_t addrlen = sizeof(addrcli);
    int connfd = accept(sockfd,(struct sockaddr*)&addrcli,&addrlen);
    if(connfd == -1){
        perror("accept");
        return -1;
    }
    printf("用户交易:%s connfd = %d\n",inet_ntoa(addrcli.sin_addr),connfd);//整数转点分十进制串
    return connfd;
}
int rcvreq(int connfd,void* req,size_t len){
    ssize_t rb = recv(connfd,req,len,0);
    if(rb == -1){
        perror("recv");
        close(connfd);
        return -1;
    }
    if(rb == 0){
        printf("客户机宕机!\n");
        close(connfd);
        return -1;
    }
    return 0;
}
int sndres(int connfd,const void* res,size_t len){
    if(send(connfd,res,len,0) == -1){
        perror("send");
        close(connfd);
        return -1;
    }
    close(connfd);//短连接模式，响应发送出去以后，关闭连接
    return 0;
}
//客户端
int sndreq(const char* server,unsigned short type,const void* req,size_t len){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(type);//主机字节序转网络字节序
    addr.sin_addr.s_addr = inet_addr(server);//字符串转32位无符号整数（网络字节序）
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("connect");
        close(sockfd);
        return -1;
    }
    if(send(sockfd,req,len,0) == -1){
        perror("send");
        close(sockfd);
        return -1;
    }
    return sockfd;
}
int rcvres(int sockfd,void* res,size_t len){
    ssize_t rb = recv(sockfd,res,len,0);
    if(rb == -1){
        perror("recv");
        close(sockfd);
        return -1;
    }
    if(rb == 0){
        printf("服务器宕机!\n");
        close(sockfd);
        return -1;
    }
    close(sockfd);//短链接模式，接收到响应以后直接关闭连接
    return 0;
}
