#include <stdio.h>
#include <errno.h>//有全局变量的外部声明(extern)和一些宏
#include <string.h>
int main(){
    FILE* fp = fopen("none","r");
    if(!fp){
        printf("fopen出错了:%d\n",errno);
        printf("fopen出错了:%s\n",strerror(errno));
        perror("fopen出错了");
        printf("fopen出错了:%m\n");//看到%m，就会调用strerror()
        return -1;
    }
    //...
    fclose(fp);
    return 0;
}
