#include "math.h"
int main(){
    show(30,'+',20,add(30,20));
    show(30,'-',20,sub(30,20));
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/042316$ ls
calc.c  calc.h  main.c  math.h  show.c  show.h
zn@zn-OptiPlex-9010:~/demo/042316$ gcc -c -fpic calc.c 
lzn@zn-OptiPlex-9010:~/demo/042316$ ls
calc.c  calc.h  calc.o  main.c  math.h  show.c  show.h
zn@zn-OptiPlex-9010:~/demo/042316$ gcc -c -fpic show.c 
zn@zn-OptiPlex-9010:~/demo/042316$ ls
calc.c  calc.h  calc.o  main.c  math.h  show.c  show.h  show.o
zn@zn-OptiPlex-9010:~/demo/042316$ gcc -shared calc.o show.o -o libmath.so
zn@zn-OptiPlex-9010:~/demo/042316$ ls
calc.c  calc.h  calc.o  libmath.so  main.c  math.h  show.c  show.h  show.o
zn@zn-OptiPlex-9010:~/demo/042316$ nm libmath.so 
0000000000000705 T add
0000000000201038 B __bss_start
0000000000201038 b completed.6973
                 w __cxa_finalize@@GLIBC_2.2.5
0000000000000620 t deregister_tm_clones
0000000000000690 t __do_global_dtors_aux
0000000000200e08 t __do_global_dtors_aux_fini_array_entry
0000000000201030 d __dso_handle
0000000000200e18 d _DYNAMIC
0000000000201038 D _edata
0000000000201040 B _end
000000000000076c T _fini
00000000000006d0 t frame_dummy
0000000000200e00 t __frame_dummy_init_array_entry
0000000000000850 r __FRAME_END__
0000000000201000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
00000000000005b8 T _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000200e10 d __JCR_END__
0000000000200e10 d __JCR_LIST__
                 w _Jv_RegisterClasses
                 U printf@@GLIBC_2.2.5
0000000000000650 t register_tm_clones
000000000000072f T show
0000000000000719 T sub
0000000000201038 d __TMC_END__
zn@zn-OptiPlex-9010:~/demo/042316$ gcc -shared -fpic calc.c show.c -o libmath.so
zn@zn-OptiPlex-9010:~/demo/042316$ gcc main.c -lmath -L.
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
./a.out: error while loading shared libraries: libmath.so: cannot open shared object file: No such file or directory
zn@zn-OptiPlex-9010:~/demo/042316$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
zn@zn-OptiPlex-9010:~/demo/042316$ echo $LD_LIBRARY_PATH
:.
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
30 + 20 = 50
30 - 20 = 10
zn@zn-OptiPlex-9010:~/demo/042316$ rm libmath.so 
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
./a.out: error while loading shared libraries: libmath.so: cannot open shared object file: No such file or directory
zn@zn-OptiPlex-9010:~/demo/042316$ gcc -shared -fpic calc.c show.c -o libmath.so
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
30 + 20 = 50
30 - 20 = 10
zn@zn-OptiPlex-9010:~/demo/042316$ vi calc.c(修改calc.c),main.c不用重新编译,易于维护 
zn@zn-OptiPlex-9010:~/demo/042316$ gcc -shared -fpic calc.c show.c -o libmath.so
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
30 + 20 = 600
30 - 20 = 10
使用动态库可以在二进制的级别上把我们的程序模块化。
以前c程序的模块化设计，只是源代码级别上的模块化。一个函数一个函数的，是模块化。
还有物理级别上的模块化。就是分文件。
不过这些东西真正在运行的时候依然是铁板一块，还是一个a.out
只有使用动态库才是真正意义上的模块化。
A.out libmath.so两个模块
#endif
