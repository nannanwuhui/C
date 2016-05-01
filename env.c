#include <stdio.h>
#include <stdlib.h>
//打印进程里所有的环境变量
void printenv(){
    printf("---- 环境变量 ----\n");
    extern char ** environ;
    char **env;
    //*env为NULL，表示到了环境表的末尾了，env为空，表示没有环境变量了
    for(env = environ;env && *env;++env){
        printf("%s\n",*env);
    }
    printf("-----------------\n");
}
int main(){
    char env[256];
    const char *name="MYNAME";
    //添加环境变量
    sprintf(env,"%s=minwei",name);
    putenv(env);
    printf("%s=%s\n",name,getenv(name));
    //修改环境变量
    sprintf(env,"%s=bjarne",name);
    putenv(env);
    printf("%s=%s\n",name,getenv(name));
    //不存在就添加，存在不覆盖(0)
    setenv(name,"minwei",0);
    printf("%s=%s\n",name,getenv(name));
    //不存在就添加，存在就覆盖(1)
    setenv(name,"minwei",1);
    printf("%s=%s\n",name,getenv(name));
    printenv();
    //删除环境变量
    unsetenv(name);
    printenv();
    //清空环境变量
    clearenv();//environ变成NULL了
    printenv();
    return 0;
}
#if 0
//每个进程的环境变量是独立的。
在a.out里调用的putenv,所以改的仅仅是a.out进程的环境变量
a.out一旦结束，程序里设置的所有环境变量都会被释放
下面的两种方法看的都是shell的环境变量，shell是a.out的父进程
zn@zn-OptiPlex-9010:~/demo/050116$ echo $MYNAME

zn@zn-OptiPlex-9010:~/demo/050116$ env | grep MYNAME

#endif
