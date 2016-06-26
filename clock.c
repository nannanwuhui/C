#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
void sigalrm(int signum){
    time_t t = time(NULL);
    struct tm* local = localtime(&t);
    //\r回车
    printf("\r%04d年%02d月%02d日 %02d:%02d:%02d",
           local->tm_year + 1900,
           local->tm_mon + 1,
           local->tm_mday,
           local->tm_hour,
           local->tm_min,
           local->tm_sec);
    alarm(1);
}
int main(){
    //关闭输出缓冲区,指定缓冲区，可以malloc一块内存或者把数组的首地址作为
    //setbuf的第二个参数，它就会用你指定的这块内存做输出流缓冲区，不用默认的。
    //但是如果你写了一个NULL，那它就没有输出流缓冲区了。你输出什么，它即刻就会
    //显示出来。
    setbuf(stdout,NULL);
    if(signal(SIGALRM,sigalrm) == SIG_ERR){
        perror("signal");
        return -1;
    }
    sigalrm(SIGALRM);//信号处理函数，内核可以调，我们自己也可以调
    for(;;);
    return 0;
}
