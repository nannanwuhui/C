#include <stdio.h>
#include <calc.h>//不找当前目录
int main(){
    printf("%lf\n",add(10,20));
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/041616$ gcc cpath.c calc.c
cpath.c:2:18: fatal error: calc.h: No such file or directory
 #include <calc.h>
                  ^
compilation terminated.
zn@zn-OptiPlex-9010:~/demo/041616$ gcc cpath.c calc.c -I .
zn@zn-OptiPlex-9010:~/demo/041616$ ./a.out
30.000000
//export这种方式只管当前会话，如果shell退出，重新开一个shell,就无效了。
zn@zn-OptiPlex-9010:~/demo/041616$ export CPATH=$CPATH:.
zn@zn-OptiPlex-9010:~/demo/041616$ gcc cpath.c calc.c
zn@zn-OptiPlex-9010:~/demo/041616$ ./a.out
30.000000
zn@zn-OptiPlex-9010:~/demo/041616$ echo $CPATH
:.
将当前目录作为C头文件附加搜索路径，添加到CPATH环境变量中：
Export CPATH=$CPATH:.//export保证当前shell的子进程继承此环境变量
Echo $CPATH
Env | grep CPATH
也可以在~/.bashrc或~/.bash_profile配置文件中写环境变量，持久有效。
Export CPATH=$CPATH:.
执行：
Source ~/.bashrc或者source ～/.bash_profile
生效，以后每次登录自动生效。
头文件的三种定位方式：
1）#include “目录/xxx.h” 头文件路径发生变化，需要修改源程序
2）可以写在.bashrc里面，但是同样会有下面所说的问题
C_INCLUDE_PATH/CPATH=目录 同时构建多个工程，可能引发冲突
一个工程用的是微软的头文件，一个工程用的是惠普的头文件，这个头文件其中一些头文件的名字还一样，但是分别在不同的目录下。那这两个目录都要放在CPATH里面，你在编译微软的项目的时候没问题，但是在编译惠普的项目的时候就有问题了，因为它还是按照头文件的搜索路径从前往后找，结果找到了微软的头文件，就用微软的头文件了，不往后找了，这肯定就出问题了。
3）gcc -I 目录 既不用改程序，也不会有冲突
可以写在mafile里面，这样每次只用写make就可以了。
所以这种方式是最好的。
#endif
