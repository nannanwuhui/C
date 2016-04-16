#include <stdio.h>
#if 0
第一条：第一个成员的首地址为0
第二条：每个成员的首地址是自身大小的整数倍
       第二条补充：以4字节对齐为例，如果自身大小大于4字节，都以4字节整数倍为基准对齐。
第三条：最后以结构总体对齐。
        第三条补充：以4字节对齐为例，取结构体中最大成员类型倍数，
如果超过4字节，都以4字节整数倍为基准对齐。（其中这一条还有个名字叫：“补齐”，补齐的目的就是多个结构变量挨着摆放的时候也满足对齐的要求。）
#endif
int main(){
#pragma pack(1)
    struct S1{
        double b;
        char c;
        int i;
        short h;
    };
//    printf("double:%lu字节\n",sizeof(double));
//    printf("short:%lu字节\n",sizeof(short));
    printf("S1:%lu字节\n",sizeof(struct S1));
#pragma pack()
    struct S2{
        double b;
        char c;
        int i;
        short h;
    };
//    printf("double:%lu字节\n",sizeof(double));
//    printf("short:%lu字节\n",sizeof(short));
    printf("S2:%lu字节\n",sizeof(struct S2));
//超过8字节没有用，因为地址总线的宽度就是4字节，指定超过了4个字节也没用，仍然是按4字节对齐
#pragma pack(8)
    struct S3{
        double b;
        char c;
        int i;
        short h;
    };
    printf("S3:%lu字节\n",sizeof(struct S3));
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/041616$ gcc pragma2.c
zn@zn-OptiPlex-9010:~/demo/041616$ ./a.out
S1:15字节
S2:24字节
S3:24字节
#endif
