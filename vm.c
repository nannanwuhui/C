#include <stdio.h>
int g_vm = 0;
int main(){
    printf("&g_vm = %p\n",&g_vm);
    printf("整数:");
    //忽略回车
    scanf("%d%*c",&g_vm);
    printf("启动另一个进程，输入不同的数据，按<回车>继续...");
    getchar();
    printf("g_vm = %d\n",g_vm);

    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/050216$ ./a.out
&g_vm = 0x601054
整数:1234
启动另一个进程，输入不同的数据，按<回车>继续...

zn@zn-OptiPlex-9010:~/demo/050216$ ./a.out
&g_vm = 0x601054（两个进程的虚拟内存是一样的，但是实际映射的物理内存不一样）
整数:6789
启动另一个进程，输入不同的数据，按<回车>继续...
回车以后：
zn@zn-OptiPlex-9010:~/demo/050216$ ./a.out
&g_vm = 0x601054
整数:1234
启动另一个进程，输入不同的数据，按<回车>继续...
g_vm = 1234
#endif
