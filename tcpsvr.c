#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//SIGCHLD是不可靠信号，假如两个子进程相继死亡，当第一个子进程回收到一半的时候
//第二个子进程也死了，第二个SIGCHLD信号会被阻塞，当处理完第一个信号以后会去处理第二个信号
//但是这个时候第三个子进程也死了，它的信号不会被阻塞，不可靠信号只会被阻塞一次．
//第二个，第三个就会被丢掉，这样这些子进程就没有机会被回收了，这样就还会产生僵尸
#if 0
void sigchld(int signum){
    //回收子进程
    wait(0);
}
#else

void sigchld(int signum){
    //回收子进程，担心回收的过程中又有进程退出，收不到SIGCHLD信号,所以这里使用了循环
    //这样就可以不用担心不可靠信号丢失的问题
    for(;;){
        //这种方式虽然可以回收完子进程，但是wait是阻塞的，如果主进程一直阻塞在
        //wait,就没有办法等待新的连接调用accept了．
//        pid_t pid = wait(0);//wait不能非阻塞，但是waitpid可以
        //以非阻塞的方式来捕获所有你可以捕获的子进程
        pid_t pid = waitpid(-1,0,WNOHANG);
        if(pid == -1){
            //子进程被回收完了
            /*
            if(errno == ECHILD)
                break;
                */
            if(errno != ECHILD){
                //这种情况属于系统错误，直接exit(-1)，进程结束就可以了
                perror("waitpid");
                exit(-1);
            }
            printf("服务器:全部子进程都已退出.\n");
            break;
        }
        if(pid){
            printf("服务器:发现%u子进程退出.\n",pid);
        }
        else{
            printf("服务器:暂时没有子进程退出.\n");
            break;
        }
    }
}
#endif
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法:%s <端口号>\n",argv[0]);
        return -1;
    }
    if(signal(SIGCHLD,sigchld) == SIG_ERR){
        perror("signal");
        return -1;
    }
    printf("服务器:创建网络数据流套接字...\n");
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }
    printf("服务器:准备地址并绑定...\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));//主机字节序转网络字节序
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("bind");
        return -1;
    }
    printf("服务器:监听套接字...\n");
    if(listen(sockfd,1024) == -1){
        perror("listen");
        return -1;
    }
    for(;;){
        printf("服务器:等待连接请求...\n");
        struct sockaddr_in addrcli = {};
        socklen_t addrlen = sizeof(addrcli);
        int connfd = accept(sockfd,(struct sockaddr*)&addrcli,&addrlen);
        if(connfd == -1){
            perror("accept");
            return -1;
        }
        printf("服务器:接受来自%s:%u客户机的连接请求．创建子进程为其提供服务...\n"
               ,inet_ntoa(addrcli.sin_addr),ntohs(addrcli.sin_port));//端口:网络字节序转换成本机字节序，地址:把32位无符号整数网络字节序转换成点分十进制
        pid_t pid = fork();
        if(pid == -1){
            perror("fork");
            return -1;
        }
        if(pid == 0){
            printf("%u子进程:为%s:%u客户机提供服务...\n",getpid(),inet_ntoa(addrcli.sin_addr),ntohs(addrcli.sin_port));
            if(close(sockfd) == -1){
                perror("close");
                return -1;
            }
            for(;;){
                char buf[1024];
                printf("%u子进程:接收请求...\n",getpid());
                ssize_t rb = recv(connfd,buf,sizeof(buf),0);
                if(rb == -1){
                    perror("recv");
                    return 0;
                }
                if(rb == 0){//客户机主动断开，发送了FIN分节，对于服务器来说相当于是读到了文件尾
                    printf("%u子进程:客户机已关闭连接.\n",getpid());
                    break;
                }
                printf("%u子进程:发送响应...\n",getpid());
                if(send(connfd,buf,rb,0) == -1){
                    perror("send");
                    return -1;
                }
            }
            printf("%u子进程:关闭连接套接字...\n",getpid());
            if(close(connfd) == -1){
                perror("close");
                return -1;
            }
            printf("%u子进程:即将退出.\n",getpid());
            return 0;
            //子进程在这里退出，由于父进程还在，所以子进程不会被init进程所收养，这样就会产生僵尸进程
        }
        if(close(connfd) == -1){
            perror("close");
            return -1;
        }
    }

    return 0;
}
