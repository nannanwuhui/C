#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
void siginfo(int signum,siginfo_t* si,void* pv){
    printf("%u进程:收到发自%u进程的%d信号，(附加值=%s)!\n",
           getpid(),si->si_pid,signum,/*si->si_value.sival_int*/
           (char*)si->si_value.sival_ptr);
}
int main(){
    char text[256] = "hello";
    //如果是２,子进程发送10个，父进程只处理了两个。
    //因为发送的太密集，第一个收到了，在执行处理函数的时候
    //第二个过来了，被屏蔽了。从第三个开始就都丢弃了。
    //可靠信号支持排队，不可靠信号不支持排队，收到的比发送的少
    int signum = /*50*/2;//子进程发送１０个，父进程收到１０个。
    struct sigaction act = {};
    act.sa_sigaction = siginfo;
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    if(sigaction(signum,&act,NULL) == -1){
        perror("sigaction");
        return -1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
        /**
         * 子进程给父进程发送的东西可以是在代码段里，因为父子进程共享代码段。
         * 但是某个进程发送的信号所附加的东西是某个值，另外一个进程发送同样
         * 的信号往往是一个不同的值，如果两个值是一样的，那就不用传了，直接
         * 访问不就行了。不一样的东西肯定不能放在代码段里。要么放在数据段里，
         * 要么放在堆里，要么放在栈里。不管放在哪（数据段，堆栈），两个进程
         * 空间都是独立的。
         * 但是可以使用共享内存，两个进程之间可以共享访问。
         * 如果你在子进程的堆里malloc一块内存，然后把指针传给父进程，
         * 那这个指针在父进程里就是一个野指针。
         * 传递的指针所指向的内存，在父子进程中必须都是有意义的，并且
         * 父子进程都可以看到这块内存才可以。
         * 跨越进程的时候，传递整数更加多见。
         * 如果是多线程的话，数据段，堆内存都是可以传递的。
         */
        pid_t ppid = getppid();
        int i = 0;
        for(i = 0;i < 10; i++){
            sigval_t sv;
            strcpy(text,"world");
            //如果是子进程向父进程发送的数据是一个指针，没有意义。
            //两个进程的进程空间是独立的。
//            sv.sival_int = i;
            sv.sival_ptr = text;
            printf("%u进程:向%u进程发送%d信号,(附加值=%s)...\n",
                   getpid(),ppid,signum,/*sv.sival_int*/(char*)sv.sival_ptr);
            if(sigqueue(ppid,signum,sv) == -1){
                perror("sigqueue");
                return -1;
            }
        }
        printf("%u进程:我即将退出.\n",getpid());
        return 0;
    }
    if((pid = wait(0)) == -1){
        perror("wait");
        return -1;
    }
    printf("%u进程:%u进程已退出.\n",getpid(),pid);
    return 0;
}
