#include <stdio.h>
#include <limits.h>
//获取文件大小
//成功返回文件的字节数，失败返回-1
long fsize(const char* path){
    //这里必须是读模式的，如果是写模式的话，文件不存在就会创建一个，
    //这样永远也不会返回-1了。
    FILE* fp = fopen(path,"r");
    if(!fp){
        return -1;
    }
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}
int main(void){
    printf("文件路径:");
    char path[PATH_MAX + 1];
    scanf("%s",path);
    long size = fsize(path);
    if(size == -1){
        printf("文件大小获取失败!\n");
        return -1;
    }
    printf("文件大小:%ld字节\n",size);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/042416$ ls
bad.c
zn@zn-OptiPlex-9010:~/demo/042416$ gcc bad.c 
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
文件路径:./a.out
文件大小:8954字节
zn@zn-OptiPlex-9010:~/demo/042416$ ./a.out
文件路径:b.out
文件大小获取失败!
zn@zn-OptiPlex-9010:~/demo/042416$ ls a.out -lt
-rwxrwxr-x 1 zn zn 8954  4月 24 17:53 a.out
#endif
