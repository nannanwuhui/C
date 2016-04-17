#include "math.h"
int main(){
    show(30,'+',20,add(30,20));
    show(30,'-',20,add(30,20));
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/041716$ ls
calc.c  calc.h  math.h  show.c  show.h
zn@zn-OptiPlex-9010:~/demo/041716$ gcc -c calc.c（-c只编译不链接）
zn@zn-OptiPlex-9010:~/demo/041716$ ls
calc.c  calc.h  calc.o  math.h  show.c  show.h
zn@zn-OptiPlex-9010:~/demo/041716$ gcc -c show.c
zn@zn-OptiPlex-9010:~/demo/041716$ ls
calc.c  calc.h  calc.o  math.h  show.c  show.h  show.o
zn@zn-OptiPlex-9010:~/demo/041716$ ar -r libmath.a calc.o show.o
ar: creating libmath.a
zn@zn-OptiPlex-9010:~/demo/041716$ nm libmath.a

calc.o:
0000000000000000 T(text 代码段) add
0000000000000014 T sub

show.o:
                 U printf
0000000000000000 T show
zn@zn-OptiPlex-9010:~/demo/041716$ gvim main.c
zn@zn-OptiPlex-9010:~/demo/041716$ gcc main.c
/tmp/ccREu7qH.o: In function `main':
main.c:(.text+0xf): undefined reference to `add'（未定义，定义在库中，包含的头文件中只有声明）
main.c:(.text+0x25): undefined reference to `show'
main.c:(.text+0x34): undefined reference to `add'
main.c:(.text+0x4a): undefined reference to `show'
collect2: error: ld returned 1 exit status（链接错误，编译已经过了）
zn@zn-OptiPlex-9010:~/demo/041716$ gcc main.c -lmath（会自动在math前加上lib，后面加上.so。没有写库的路径，会到系统默认的目录/usr/lib下去找）
/usr/bin/ld: cannot find -lmath
collect2: error: ld returned 1 exit status
zn@zn-OptiPlex-9010:~/demo/041716$ gcc main.c -lmath -L.（先从-L指定的目录下找，如果找不到，再从系统目录/usr/lib下去找,-l告诉链接器链接哪一个库）
zn@zn-OptiPlex-9010:~/demo/041716$ ./a.out
30 + 20 = 50
30 - 20 = 50
#endif
