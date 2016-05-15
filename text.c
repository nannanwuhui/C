#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//字符和二进制之间的转换得自己来做了，因为uc的接口只是针对二进制流的
//如果你的文件只是用来存储的，人不会阅读它，那你就用二进制的。
//如果你的文件不仅仅是存储，还需要人来阅读它，那你就用文本的方式。
//但所有文本格式化的工作需要由程序员自己来做，用的是系统调用，不是标c，不能用fprintf
int main(){
    //open unix的函数，unix文件的文本模式和二进制模式已经不区分了
    //fopen（标c库的函数）可能会在windows上用，文本的话，写的时候会把换行变成回车加换行
    //读的话再变回来（字符模式），二进制模式就不做这个转换了，所以fopen会有t和b
    int fd = open("text.txt",O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    char name[256] = "张飞";
    unsigned int age = 38;
    double salary = 20000;
    //如果是标c的话，可以用fprintf(第一个参数是FILE*),格式化，很遗憾这是unix c
    //不能用fprintf在写文件的时候去格式化了，必须自己先用sprintf格式化好，再往文件里写
    char buf[1024];
    sprintf(buf,"%s %u %.2lf\n",name,age,salary);
    if(write(fd,buf,strlen(buf) * sizeof(buf[0])) == -1){
        perror("write");
        return -1;
    }
    struct Employee {
        char name[256];
        unsigned int age;
        double salary;
    } employee = {"赵云",25,8000};
    sprintf(buf,"%s %u %.2lf\n",employee.name,employee.age,employee.salary);
    if(write(fd,buf,strlen(buf) * sizeof(buf[0])) == -1){
        perror("write");
        return -1;
    }
    close(fd);
    if(fd = open("text.txt",O_RDONLY) == -1){
        perror("open");
        return -1;
    }
    memset(buf,0,sizeof(buf));
    if(read(fd,buf,sizeof(buf)) == -1){
        perror("read");
        return -1;
    }
    sscanf(buf,"%s %u %lf %s %u %lf\n",name,&age,&salary,employee.name,&employee.age,&employee.salary);
    printf("姓名:%s\n",name);
    printf("年龄:%u\n",age);
    printf("工资:%.2lf\n",salary);
    printf("员工:%s,%u,%.2lf\n",employee.name,employee.age,employee.salary);
    close(fd);
    return 0;
}
#if 0
非常适合人类来读
zn@zn-OptiPlex-9010:~/demo/051516$ cat text.txt
张飞 38 20000.00
赵云 25 8000.00
#endif
