#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
//求字符串长度
//成功返回字符串长度，失败返回(size_t)-1
size_t slen(const char* s){
    if(!s)
        return -1;
    size_t len;
    for(len = 0;s[len];++len);
    return len;
}
//字符串拷贝
//成功返回目标字符串，失败返回NULL
char* scpy(char* dst,size_t size,const char* src){
    if(!dst || !size || !src)
        return NULL;
    if(dst != src){
        size_t i,count=min(size-1,slen(src));
        if(dst > src)
            for(i = 0;i < count;++i)
                dst[count-1-i] = src[count-1-i];
        else
            for(i = 0;i < count;++i)
                dst[i] = src[i];
        dst[count] = '\0';
    }
    return dst;
}
//求整数最小值，两个数相等视作失败
//成功返回0,失败返回-1
int intmin(int a,int b,int* min){
    if(a == b)
        return -1;
    *min = a < b ? a : b;
    return 0;
}
//求整数平均值
//永远成功，不会失败
int intave(int a,int b){
    return (a & b) + ((a ^ b) >> 1);
}
int main(){
#ifndef ERROR
    size_t len = slen("Hello, World !");
#else
    size_t len = slen(NULL);
#endif
    if(len == -1)
        printf("求字符串长度失败!\n");
    else
        printf("字符串长度:%lu\n",len);
    char dst[5];
#ifndef ERROR
    if(!scpy(dst,sizeof(dst)/sizeof(dst[0]),"0123456789"))
#else
    if(!scpy(NULL,0,"0123456789"))
#endif
        printf("字符串拷贝失败!\n");
    else
        printf("字符串副本:%s\n",dst);
    int min;
#ifndef ERROR
    if(intmin(-1,0,&min) == -1)
#else
    if(intmin(-1,-1,&min) == -1)
#endif
        printf("求整数最小值失败!\n");
    else
        printf("整数最小值:%d\n",min);
    printf("整数平均值:%d\n",intave(1234,5678));
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/050116$ gcc error.c
zn@zn-OptiPlex-9010:~/demo/050116$ ./a.out
字符串长度:14
字符串副本:0123
整数最小值:-1
整数平均值:3456
zn@zn-OptiPlex-9010:~/demo/050116$ gcc error.c -DERROR
zn@zn-OptiPlex-9010:~/demo/050116$ ./a.out
求字符串长度失败!
字符串拷贝失败!
求整数最小值失败!
整数平均值:3456
第二课：内存管理
 一、错误处理
１、通过函数的返回值表示错误
１）返回合法值表示成功，返回非法值表示失败。
范例：bad.c

比如求一个文件的大小，大小肯定是>=0的，如果返回-1那肯定就是失败了。
2）返回有效指针表示成功
返回空指针(NULL/0xFFFFFFFF(－１))表示失败
范例：null.c
３）返回０表示成功，返回-1表示失败，
不输出数据或通过指针／引用型参数输出数据。
范例:fail.c
4)永远成功，如printf().
练习：实现四个函数
slen() 求字符串的长度，若为空指针，则报错。
scpy() 字符串拷贝，考虑缓冲区溢出，成功返回目标缓冲区地址，目标缓冲区无效时报错。
intmin() 求两个整数的最小值，若两者相等，则报错。
intave() 求两个函数的平均值，考虑求和溢出，该函数不会失败。
#endif
