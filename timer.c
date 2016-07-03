#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
int g_hour = 0,g_min = 0,g_sec = 0,g_msec = 0;
void sigalrm(int signum){
    printf("\r%02d:%02d:%02d.%03d",g_hour,g_min,g_sec,g_msec);
    if(++g_msec == 1000){
        g_msec = 0;
        if(++g_sec == 60){
            g_sec = 0;
            if(++g_min == 60){
                g_min = 0;
                if(++g_hour == 24){
                    g_hour = 0;
                }
            }
        }
    }
}
void sigint(int signum){
    //run = 0,由自动启动变为手动启动
    static int run = /*1*/0;
    struct itimerval it = {{0,1000},{0,0}};
    if(run){
        setitimer(ITIMER_REAL,&it,NULL);
    }
    else{
        printf("\n");
        g_hour = g_min = g_sec = g_msec = 0;
        it.it_value.tv_usec = 1;
        setitimer(ITIMER_REAL,&it,NULL);
    }
    run ^= 1;//按位或
}
int main(){
    setbuf(stdout,NULL);
    if(signal(SIGALRM,sigalrm) == SIG_ERR){
        perror("signal");
        return -1;
    }
    if(signal(SIGINT,sigint) == SIG_ERR){
        perror("signal");
        return -1;
    }
    //初始间隔必须是大于０的，不然就会停止计时器，
    //想要获得即刻开始运行的效果，初始计时哪怕是1微秒都行
    //但是就是不能是0,0表示停止当前计时器
    struct itimerval it = {{0,1000},{0/*5*/,0}};
    if(setitimer(ITIMER_REAL,&it,NULL) == -1){
        perror("setitimer");
        return -1;
    }
    for(;;){
        pause();//这样可以防止空耗cpu时间，将进程移出调度序列
    }
    return 0;
}
