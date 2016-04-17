#include <stdio.h>
#include <arpa/inet.h>


int main (void)
{
    char szip1[20]; //存放点分十进制IP地址
    char szip2[20]; //存放点分十进制IP地址
    struct in_addr s; // IPv4地址结构体

    // 输入IP地址
    printf("Please input IP address: ");
    scanf("%s", szip1);

    // 转换
    inet_pton(AF_INET, szip1, (void *)&s);
    printf("inet_pton: 0x%x\n", s.s_addr); // 注意得到的字节序：小端序

    // 反转换
    inet_ntop(AF_INET, (void *)&s, szip2, sizeof(szip2));
    printf("inet_ntop: %s\n", szip2);

    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/030816$ gcc test.c 
zn@zn-OptiPlex-9010:~/demo/030816$ ./a.out
Please input IP address: 192.168.0.32
inet_pton: 0x2000a8c0
inet_ntop: 192.168.0.32
总结：像192.168.0.32这样的ip地址都是大端序的，转换成整数后是小端序的。
并且用wireshark抓包看二进制的话，也是大端序的。
网络传输，根据收到数据的前后，肯定是先收到的字节放在低地址，后收到的字节放在高地址
#endif
