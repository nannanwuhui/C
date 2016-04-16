#include <stdio.h>
//当前目录下应该有一个文件dep.c，如果dep.c比当前文件新的话会产生警告
//一般用于联合编译，比如你要用别人的头文件，别人的头文件改了，而你不知道，索性
//就加上以下类似的话，说明我依赖于另外一个头文件，这样一旦别人的头文件改了，
//这里就会发出警告
#pragma GCC dependency "dep.c"
int main(){
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/041616$ gcc pragma.c
pragma.c:3:24: fatal error: dep.c: No such file or directory
 #pragma GCC dependency "dep.c"
                        ^
compilation terminated.
zn@zn-OptiPlex-9010:~/demo/041616$ touch dep.c
zn@zn-OptiPlex-9010:~/demo/041616$ ls
a.out  dep.c  error.c  line.c  line.i  pragma.c
zn@zn-OptiPlex-9010:~/demo/041616$ gcc pragma.c
pragma.c:3:24: warning: current file is older than dep.c [enabled by default]
 #pragma GCC dependency "dep.c"
                        ^
zn@zn-OptiPlex-9010:~/demo/041616$ touch pragma.c//更新pragma.c的时间
zn@zn-OptiPlex-9010:~/demo/041616$ gcc pragma.c
#endif
