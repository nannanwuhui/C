#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define FIFO_FILE "/tmp/fifo"
int main(){
    printf("打开管道...\n");
    //管道文件的open必须发送端和接收端都open了，两端的open函数才能返回。
    //只有一端open，不会返回，会阻塞等待另一端open。
    int fd = open(FIFO_FILE,O_RDONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }
    printf("接收数据...\n");
    for(;;){
        char buf[1024];
        //焦点在正在阻塞的调用上，阻塞在哪个函数，read就是焦点
        ssize_t rb = read(fd,buf,sizeof(buf));
        if(rb == -1){
            perror("read");
            return -1;
        }
        //发送端关闭管道文件，则read返回０
        if(!rb){
            break;
        }
        printf("< %s\n",buf);
    }
    if(close(fd) == -1){
        perror("close");
        return -1;
    }
    printf("大功告成!\n");
    return 0;
}
#if 0


zn@zn-OptiPlex-9010:~/demo/071016$ ./rfifo
打开管道...
接收数据...
< hello
< wolrd
< 你好@!
< 天气很好
< hello,niklaus!
< 什么时候下课呀？
< 哈哈哈
< 哈哈
< 可以啊
<
< 可以啊
< adfd
< fdkfjd
< jfdkljf
大功告成!

zn@zn-OptiPlex-9010:~/demo/071016$ ./wfifo
创建管道...
打开管道...
发送数据...
>hello
>wolrd
>你好@!
>天气很好
>hello,niklaus!
>什么时候下课呀？
>哈哈哈
>哈哈
>可以啊
>
>可以啊
>adfd
>fdkfjd
>jfdkljf
>!
关闭管道...
删除管道...
大功告成!
zn@zn-OptiPlex-9010:~/demo/071016$
#endif
