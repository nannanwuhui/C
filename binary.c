#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
//对于文件来说没有二进制和文本之分，存的都是二进制
//以二进制的方式写，指的是内存里是什么就往文件里写什么，文件和内存严格一致
//这个时候，文件是二进制的（因为内存就是二进制的），用vi或者gvim没办法看
//文件和内存一致，读写起来很简单，中间不需要做任何转换，但弊端是这个文件人（一般用户）看不懂
//写的时候严格一致写，读的时候严格一致读，中间不需要做任何转换
int main(){
    int fd = open("binary.dat",O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    char name[256] = "张飞";//不但把结尾的\0写了进去，还把\0后的东西也写了进去
    if(write(fd,name,sizeof(name)) == -1){//以二进制的方式写
        perror("write");
        return -1;
    }
    unsigned int age = 38;
    if(write(fd,&age,sizeof(age)) == -1){
        perror("write");
        return -1;
    }
    double salary = 20000;
    if(write(fd,&salary,sizeof(double)) == -1){
        perror("write");
        return -1;
    }
    struct Employee{
        char name[256];
        unsigned int age;
        double salary;
    }employee = {"赵云",25,8000};
    if(write(fd,&employee,sizeof(employee)) == -1){
        perror("write");
        return -1;
    }
    close(fd);
    if((fd = open("binary.dat",O_RDONLY)) == -1){
        perror("open");
        return -1;
    }
    if(read(fd,name,sizeof(name)) == -1){
        perror("read");
        return -1;
    }
    printf("姓名:%s\n",name);
    if(read(fd,&age,sizeof(age)) == -1){
        perror("read");
        return -1;
    }
    printf("年龄:%u\n",age);
    if(read(fd,&salary,sizeof(salary)) == -1){
        perror("read");
        return -1;
    }
    printf("工资:%.2lf\n",salary);
    if(read(fd,&employee,sizeof(employee)) == -1){
        perror("read");
        return -1;
    }
    printf("员工:%s,%u,%.2lf\n",employee.name,employee.age,employee.salary);
    close(fd);
    return 0;
}
#if 0
可以自己算一下写入了多少个字节看和540一样不一样
zn@zn-OptiPlex-9010:~/demo/051516$ ls -l binary.dat
-rw-rw-r-- 1 zn zn 540  5月 15 16:59 binary.dat
#endif
#if 0
zn@zn-OptiPlex-9010:~/demo/051516$ hexdump -C binary.dat
00000000  e5 bc a0 e9 a3 9e 00 00  00 00 00 00 00 00 00 00  |................|
00000010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000100  26 00 00 00 00 00 00 00  00 88 d3 40 e8 b5 b5 e4  |&..........@....|
00000110  ba 91 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000120  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000200  00 00 00 00 00 00 00 00  00 00 00 00 19 00 00 00  |................|
00000210  00 00 00 00 00 00 00 00  00 40 bf 40              |.........@.@|
0000021c
#endif
