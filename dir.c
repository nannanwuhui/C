#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
int main(){
    //如果没有用chdir改变进程的当前工作目录的话，shell的当前目录就是进程的当前工作目录
    //子进程的当前工作目录是从shell里继承过来的。
    char cwd[PATH_MAX + 1];
    //这个函数会在cwd中放置\0，可以当字符串使用
    if(!getcwd(cwd,sizeof(cwd))){
        perror("getcwd");
        return -1;
    }
    printf("当前工作目录:%s\n",cwd);
    if(mkdir("work",0755) == -1){
        perror("mkdir");
        return -1;
    }
    if(chdir("work") == -1){
        perror("chdir");
        return -1;
    }
    if(!getcwd(cwd,sizeof(cwd))){
        perror("getcwd");
        return -1;
    }
    printf("当前工作目录:%s\n",cwd);
//    if(rmdir("work") == -1){
    //相对目录是相对于当前工作目录
    if(rmdir("../work") == -1){
        perror("rmdir");
        return -1;
    }
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060516$ gcc dir.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out
当前工作目录:/home/zn/demo/060516
当前工作目录:/home/zn/demo/060516/work
zn@zn-OptiPlex-9010:~/demo/060516$ pwd(shell的目录依然在原来的地方，没有改变)
/home/zn/demo/060516
#endif
