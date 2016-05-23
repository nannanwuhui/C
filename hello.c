#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
    close(1);//关闭标准输出
    open("hello.txt",O_WRONLY | O_CREAT | O_TRUNC,0664);
    //这里没有用到open返回的文件描述符,但是open返回的文件描述符一定是1
    printf("Hello, World !\n");//printf底层调用的系统调用就是write
//    perror("printf");
    //write(1,...);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052316$ echo $PATH > path.txt
shell实现重定向:1、关闭标准输出
               ２、打开path.txt文件
                 ３、执行echo程序(echo里调用printf的地方就会把所有打印的东西写入文件中)
如果是<（输入重定向的话就会关闭0文件描述符，然后打开你的文件，就会从文件中读取数据(scanf)）
如果是2>，就会关闭3，然后打开一个文件，这样标准出错就会跑到这个文件中
#endif
#if 0
zn@zn-OptiPlex-9010:~/demo/052316$ gcc hello.c
zn@zn-OptiPlex-9010:~/demo/052316$ ./a.out
Hello, World !
zn@zn-OptiPlex-9010:~/demo/052316$ gcc hello.c(关闭标准输出)
zn@zn-OptiPlex-9010:~/demo/052316$ ./a.out
zn@zn-OptiPlex-9010:~/demo/052316$ gcc hello.c
zn@zn-OptiPlex-9010:~/demo/052316$ ./a.out
printf: Bad file descriptor
#endif
