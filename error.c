#include <stdio.h>
#if (VERSION < 3)
    #error "版本太低！"
#elif (VERSION > 3)
    #warning "版本太高!"
#endif
int main(){
    printf("版本:%d\n",VERSION);
    return 0;
}
#if 0
这里的gcc error.c -DVERSION=2,-DVERSION=2是预处理宏
zn@zn-OptiPlex-9010:~/demo/041616$ gcc error.c -DVERSION=2
error.c:3:6: error: #error "版本太低！"
     #error "版本太低！"
      ^
zn@zn-OptiPlex-9010:~/demo/041616$ ls
error.c
zn@zn-OptiPlex-9010:~/demo/041616$ gcc error.c -DVERSION=4
error.c:5:6: warning: #warning "版本太高!" [-Wcpp]
     #warning "版本太高!"
      ^
zn@zn-OptiPlex-9010:~/demo/041616$ ls
a.out  error.c
zn@zn-OptiPlex-9010:~/demo/041616$ ./a.out
版本:4
zn@zn-OptiPlex-9010:~/demo/041616$ gcc error.c -DVERSION=3
zn@zn-OptiPlex-9010:~/demo/041616$ ./a.out
版本:3
#error //产生错误，结束预处理
把error后面的错误信息打印出来，然后结束预处理。
#warning //产生警告，继续往下走
#是预处理指令
#endif
