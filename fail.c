#include <stdio.h>
//整数取模
//返回０表示成功，返回-1表示失败，
//uc里%99的函数是返回０表示成功，返回-1表示失败
int intmod(int a,int b,int* mod){
    if(b == 0)
        //这里返回-1肯定不行，因为-3%2取模结果也是-1
        return -1;
    *mod = a % b;
    return 0;
}
int main(){
    printf("两个整数:");
    int a,b;
    scanf("%d%d",&a,&b);
    int mod;
    if(intmod(a,b,&mod) == -1){
        printf("整数取模失败!\n");
        return -1;
    }
    printf("整数取模:%d\n",mod);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/042416$ gcc fail.c
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
两个整数:3 2
整数取模:1
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
两个整数:-3 2
整数取模:-1
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
两个整数:3 0
整数取模失败!
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
两个整数:-1 3
整数取模:-1
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
两个整数:-1 0
整数取模失败!
３）返回０表示成功，返回-1表示失败，
不输出数据或通过指针／引用型参数输出数据。
#endif
