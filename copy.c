#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
int main(int argc,char* argv[]){
    if(argc < 3){
        fprintf(stderr,"用法:%s <源文件> <目的文件>\n",argv[0]);
        return -1;
    }
    int src = open(argv[1],O_RDONLY);
    if(src == -1){
        perror("打开源文件失败");
        return -1;
    }
    struct stat st;
    //获取源文件属性信息
    if(fstat(src,&st) == -1){
        perror("获取源文件属性失败");
        return -1;
    }
    //让目标文件的读写模式和源文件一样
    int dst = open(argv[2],O_WRONLY | O_CREAT | O_EXCL,st.st_mode);
    if(dst == -1){
        //man 2 open看errors
        if(errno != EEXIST)
        {
            perror("创建目的文件失败");
            return -1;
        }
        printf("文件%s已存在，是否覆盖?(y/n)",argv[2]);
        int ch = getchar();
        if(ch != 'Y' && ch != 'y')
            return 0;
        if((dst = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,st.st_mode)) == -1){
            perror("打开目的文件失败!");
            return -1;
        }
    }
    //1024一页
    unsigned char buf[1024];
    ssize_t bytes;
    while((bytes = read(src,buf,sizeof(buf))) > 0)
        //读多少写多少
        if(write(dst,buf,bytes) == -1){
            perror("写入目的文件失败!");
            return -1;
        }
    if(bytes == -1){
        perror("读取源文件失败!");
        return -1;
    }
    //如果bytes == 0表示读完了，不用处理
    close(dst);
    close(src);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052116$ ls
a.out  copy.c  text.bak  text.txt
zn@zn-OptiPlex-9010:~/demo/052116$ ./a.out text.txt text.bak
文件text.bak已存在，是否覆盖?(y/n)y
zn@zn-OptiPlex-9010:~/demo/052116$ diff text.txt  text.bak
zn@zn-OptiPlex-9010:~/demo/052116$ ./a.out text.c text.bak
打开源文件失败: No such file or directory
zn@zn-OptiPlex-9010:~/demo/052116$ echo a > text.c
zn@zn-OptiPlex-9010:~/demo/052116$ ls
a.out  copy.c  text.bak  text.c  text.txt
zn@zn-OptiPlex-9010:~/demo/052116$ ./a.out text.c text.bak
文件text.bak已存在，是否覆盖?(y/n)n
zn@zn-OptiPlex-9010:~/demo/052116$ gvim text.bak
zn@zn-OptiPlex-9010:~/demo/052116$ ./a.out text.c text.bak
文件text.bak已存在，是否覆盖?(y/n)y
zn@zn-OptiPlex-9010:~/demo/052116$ gvim text.bak
zn@zn-OptiPlex-9010:~/demo/052116$ ./a.out a.out b.out
zn@zn-OptiPlex-9010:~/demo/052116$ gvim b.out
zn@zn-OptiPlex-9010:~/demo/052116$ b.out
b.out: command not found
zn@zn-OptiPlex-9010:~/demo/052116$ ./b.out（可执行）
用法:./b.out <源文件> <目的文件>
zn@zn-OptiPlex-9010:~/demo/052116$ diff a.out b.out
zn@zn-OptiPlex-9010:~/demo/052116$
#endif
