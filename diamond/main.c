#include <stdio.h>
#include "diamond.h"
int main(int argc,char* argv[]){
    if(argc < 5){
        fprintf(stderr,"Usage:%s <H> <D> <S> <C>\n",argv[0]);
        return -1;
    }
    diamond(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),*argv[4]);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ gcc -c diamond.c 
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ ar -r libdiamond_static.a diamond.o
ar: creating libdiamond_static.a
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ gcc main.c -ldiamond_static -L.
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ ./a.out 4 2 1 '#'
        #
      #####
    #########
  #############
#################
  #############
    #########
      #####
        #
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ gcc -shared -fpic diamond.c -o libdiamond_shared.so
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ gcc main.c -ldiamond_shared -L .
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ ./a.out
Usage:./a.out <H> <D> <S> <C>
zn@zn-OptiPlex-9010:~/demo/042316/diamond$ ./a.out 4 2 1 '#'
        #
      #####
    #########
  #############
#################
  #############
    #########
      #####
        #
#endif
#if 0
作业:编写一个函数diamond(),打印一个菱形，其高度，宽度，实心或者空心以及图案字符，
均可通过参数设置，分别封装为静态库libdiamond_static.a和动态库libdiamond_shared.so，并调用之。
#endif
