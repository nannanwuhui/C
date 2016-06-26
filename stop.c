#include <stdio.h>
int main(){
    unsigned int i = 0;
    for(;;){
        printf("%u\n",i++);
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/062616$ ps -eaf | grep a.out
zn       31604 31418  0 13:32 pts/9    00:00:00 grep --color=auto a.out
zn@zn-OptiPlex-9010:~/demo/062616$ ps -eaf | grep a.out
zn       17762 17643 15 14:43 pts/0    00:00:00 ./a.out
zn       17772 31418  0 14:43 pts/9    00:00:00 grep --color=auto a.out
zn@zn-OptiPlex-9010:~/demo/062616$ kill -19 17762(暂停)
zn@zn-OptiPlex-9010:~/demo/062616$ kill -18 17762（继续）
zn@zn-OptiPlex-9010:~/demo/062616$ kill -19 17762
zn@zn-OptiPlex-9010:~/demo/062616$ kill -18 17762
zn@zn-OptiPlex-9010:~/demo/062616$ kill -19 17762
zn@zn-OptiPlex-9010:~/demo/062616$ kill -15 17762（终止）但是此时进程处于暂停的状态
已经被移出调度序列了，所以无法终止
如果进程处于运行的状态的话，给进程发送15信号的话，一定是可以将进程终止的
zn@zn-OptiPlex-9010:~/demo/062616$ ps -eaf |grep a.out
zn       17762 17643  4 14:43 pts/0    00:00:04 ./a.out
zn       18256 31418  0 14:45 pts/9    00:00:00 grep --color=auto a.out
zn@zn-OptiPlex-9010:~/demo/062616$ kill -15 17762
zn@zn-OptiPlex-9010:~/demo/062616$ ps -eaf |grep a.out
zn       17762 17643  3 14:43 pts/0    00:00:04 ./a.out
zn       18342 31418  0 14:45 pts/9    00:00:00 grep --color=auto a.out
zn@zn-OptiPlex-9010:~/demo/062616$ kill -9 17762
zn@zn-OptiPlex-9010:~/demo/062616$ ps -eaf |grep a.out
zn       18384 31418  0 14:45 pts/9    00:00:00 grep --color=auto a.out
#endif
