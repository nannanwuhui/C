#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
//谁都可以在/tmp/目录下创建文件，并且只有自己可以删除自己创建的文件
#define FIFO_FILE "/tmp/fifo"
int main(){
    printf("创建管道...\n");
    if(mkfifo(FIFO_FILE,0666) == -1){
        perror("mkfifo");
        return -1;
    }
    printf("打开管道...\n");
    int fd =open(FIFO_FILE,O_WRONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }
    printf("发送数据...\n");
    for(;;){
        printf(">");
        char buf[1024];
        //焦点
        gets(buf);//按行读，遇到\n换成\0
        if(!strcmp(buf,"!")){
            break;
        }
        if(write(fd,buf,(strlen(buf) + 1) * sizeof(buf[0])) == -1){
            perror("write");
            return -1;
        }
    }
    printf("关闭管道...\n");
    if(close(fd) == -1){
        perror("close");
        return -1;
    }
    printf("删除管道...\n");
    if(unlink(FIFO_FILE) == -1){
        perror("unlink");
        return -1;
    }
    printf("大功告成!\n");
    return 0;
}

