#include <stdio.h>
#include <unistd.h>//大部分系统调用定义在这里，宏定义，还有一些类型
#include <fcntl.h>//和文件有关的一些宏
int main(){
    //0（第一个0代表是八进制数）　666第一个6代表属主，第二个6代表属组，第三个6代表其他（和chmod是一样的）
    //0 666 属主，属组，其他用户都拥有读写权限，没有可执行权限
    //zn@zn-OptiPlex-9010:~/demo/051516$ ls -l open.txt
//    -rw-rw-r-- 1 zn zn 0  5月 15 14:50 open.txt
    //但是实际打开这个文件以后，其他用户没有可读的权限
    //每个用户都有一个权限掩码，权限掩码就是用于控制文件权限的。
    //把你给出的权限位和权限掩码的取反做按位与，这样权限掩码有的权限，你就没有了。
    //相当于把你的权限给屏蔽了
//    zn@zn-OptiPlex-9010:~/demo/051516$ umask
//    0002（所有的其他用户都没有可执行权限）

    int fd1 = open("open.txt",O_RDWR | O_CREAT | O_TRUNC,0666);//相当于标c里的w+
    if(fd1 == -1){
        perror("open");
        return -1;
    }
    printf("fd1 = %d\n",fd1);//3
    close(fd1);
    //同一个文件打开两次(同一个文件，在第一次打开没有关闭（close）的情况下,再打开一次(3,4)
    //同一个文件，打开一次(open)，关闭（close），然后再打开(open)，文件描述符是一样的，都是3)，
    //两套结构，但是v-node里的i节点信息是一样的
    int fd2 = open("open.txt",O_RDONLY);
    if(fd2 == -1){
        perror("open");
        return -1;
    }
    printf("fd2 = %d\n",fd2);//4,3
    close(fd2);
//    close(fd1);
    return 0;
}

