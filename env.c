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
    printenv();
    return 0;
}
