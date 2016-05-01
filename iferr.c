#include <stdio.h>
#include <errno.h>
void foo(void){
    fopen("none","r");
}
//失败与成功还是要用返回值来表示，失败了还想知道什么原因导致的失败，再去看errno
int main(){
    foo();//foo里的fopen执行失败，修改了errno的值．
    FILE* fp = fopen("/etc/passwd","r");//fopen成功，没有修改errno的值
    if(errno){//这里的errno保存的还是foo()函数里fopen失败的错误码
        perror("fopen");
        printf("%p\n",fp);
        return -1;
    }
    //...
    fclose(fp);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/050116$ gcc iferr.c
zn@zn-OptiPlex-9010:~/demo/050116$ ./a.out
fopen: No such file or directory
0xe19010
#endif
