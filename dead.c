#include <stdio.h>
#include <unistd.h>
int main(){
    printf("%u进程：我在运行，按<Ctrl+C>或<Ctrl+\\>终止...\n",getpid());
    for(;;);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/061916$ gcc dead.c
zn@zn-OptiPlex-9010:~/demo/061916$ ./a.out
23414进程：我在运行，按<Ctrl+C>或<Ctrl+\>终止...
^C
zn@zn-OptiPlex-9010:~/demo/061916$ ./a.out
23423进程：我在运行，按<Ctrl+C>或<Ctrl+\>终止...
^\Quit (core dumped)
#endif
