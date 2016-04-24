#include <stdio.h>
#include <string.h>
//求字符串的最大值
//成功返回参数字符串中的最大值，失败返回NULL
//函数应该具有一定的容错性，当函数的调用者出错的时候，你应该指出错误，而不是崩溃
const char* strmax(const char* a,const char* b){
    return a && b ?(strcmp(a,b) > 0 ? a : b):NULL;
}
int main(){
//    const char* max = strmax("hello","world");
//    const char* max = strmax("hello",NULL);
    const char* max = strmax("hello","hello");
    if(!max){
        printf("求字符串最大值失败!\n");
        return -1;
    }
    printf("字符串最大值：%s\n",max);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/042416$ ls
a.out  bad.c  null.c
zn@zn-OptiPlex-9010:~/demo/042416$ gcc null.c
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
字符串最大值：world
zn@zn-OptiPlex-9010:~/demo/042416$ gcc null.c
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
求字符串最大值失败!
zn@zn-OptiPlex-9010:~/demo/042416$ gcc null.c
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
字符串最大值：hello
2）返回有效指针表示成功
返回空指针(NULL/0xFFFFFFFF(－１))表示失败
#endif
