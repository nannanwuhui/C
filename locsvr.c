#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#define SOCK_FILE "/tmp/sock"
int main(void){
    printf("服务器:创建本地数据报套接字...\n");
    //本地通信用udp就可以，本地通信用的其实不是真的udp,只是形式上是，
    //她也用了dgram,其实跟udp没什么关系，根本就不通过网络。不用udp协议，
    //只是在调用接口上，指定一个udp.
    int sockfd = socket(AF_LOCAL,SOCK_DGRAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    printf("服务器：准备地址并绑定...\n");
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path,SOCK_FILE);
    //绑定的时候，会先创建/tmp/sock,如果绑定的时候发现/tmp/sock已经创建了，
    //绑定就会失败。
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("bind");
        return -1;
    }
    printf("服务器:接收数据...\n");
    for(;;){
        char buf[1024];
        ssize_t rb = read(sockfd,buf,sizeof(buf));
        if(rb == -1){
            perror("read");
            return -1;
        }
        /**
          * 客户端输入!,客户端结束了，但是服务器不会结束，这就是它和有名管道的不同。
          * 有名管道当一端把有名管道文件描述符关了以后，另外一端的read一定会返回0，
          * 表示它读到文件尾了。这里如果返回0,一定会break;
          * 事实上这个时候，服务器依然可以工作。客户机虽然已经结束了，但是服务器还是
          * 阻塞在这里。
          * 如果现在重启客户端的话，依然可以和服务器进行通信。
          * 可以再启动第二个客户机，两个客户机可以同时和服务器进行通信。
          * 因为是叫服务器，就可以同时为多个客户机进行服务。
          * 如果只能为一个客户机服务的话，那就不叫服务器了，只能叫做私人助理。
          */
#if 0
        if(rb == 0)
            break;
#endif
        if(!strcmp(buf,"!!"))
            break;
        printf("< %s\n",buf);
    }
    printf("服务器：关闭套接字...\n");
    if(close(sockfd) == -1){
        perror("close");
        return -1;
    }
    printf("服务器:删除套接字文件...\n");
    if(unlink(SOCK_FILE) == -1){
        perror("unlink");
        return -1;
    }
    printf("服务器:结束!\n");
    return 0;
}
/**
  * 如果socket的另一端已经close了，另外一端还往socket里面写的话，就会报
  * write: Connection refused的错误。
  */
#if 0
zn@zn-OptiPlex-9010:~/demo/091516$ ./locsvr
服务器:创建本地数据报套接字...
服务器：准备地址并绑定...
服务器:接收数据...
< hello
< world
< abc
< d
< e
zn@zn-OptiPlex-9010:~/demo/091516$ ls -l /tmp/sock
srwxrwxr-x 1 zn zn 0  9月 15 15:26 /tmp/sock
zn@zn-OptiPlex-9010:~/demo/091516$

#endif

