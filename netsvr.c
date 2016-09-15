#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法:%s <端口号>\n",argv[0]);
        return -1;
    }
    printf("服务器:创建网络数据报套接字...\n");
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    printf("服务器：准备地址并绑定...\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    //如果你的机器只有一个ip地址的话，填INADDR_ANY,内核会把它换成
    //具体的ip地址。如果你有两个以上的ip地址的话，
    //你就需要具体写上比如"192.168.0.32"这样了
    //或者有两个ip的话，你用任何一个ip都无所谓的话，用INADDR_ANY也可以
    addr.sin_addr.s_addr = INADDR_ANY;//当然可以使用实际的ip地址"192.168.0.32"
    //在bind函数的内部，它会根据addr第一个成员的类型，把结构体地址反向强转成具体的类型
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
    printf("服务器:结束!\n");
    return 0;
}
/**
  * 如果socket的另一端已经close了，另外一端还往socket里面写的话，就会报
  * write: Connection refused的错误。
  */

