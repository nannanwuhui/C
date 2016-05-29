#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
const char* mtos(mode_t m){
    static char s[11];
    if(S_ISDIR(m))
        strcpy(s,"d");
    else
    if(S_ISLNK(m))
        strcpy(s,"l");
    else
    if(S_ISBLK(m))
        strcpy(s,"b");
    else
    if(S_ISCHR(m))
        strcpy(s,"c");
    else
    if(S_ISSOCK(m))
        strcpy(s,"s");
    else
    if(S_ISFIFO(m))
        strcpy(s,"p");
    else
        strcpy(s,"-");
    strcat(s,m & S_IRUSR ? "r" : "-");
    strcat(s,m & S_IWUSR ? "w" : "-");
    strcat(s,m & S_IXUSR ? "x" : "-");
    strcat(s,m & S_IRGRP ? "r" : "-");
    strcat(s,m & S_IWGRP ? "w" : "-");
    strcat(s,m & S_IXGRP ? "x" : "-");
    strcat(s,m & S_IROTH ? "r" : "-");
    strcat(s,m & S_IWOTH ? "w" : "-");
    strcat(s,m & S_IXOTH ? "x" : "-");
    if(m & S_ISUID)
        s[3] = (s[3] == 'x' ? 's' : 'S');
    if(m & S_ISGID)
        s[6] = (s[6] == 'x' ? 's' : 'S');
    if(m & S_ISVTX)
        s[9] = (s[9] == 'x' ? 't' : 'T');
    return s;
}
const char* ttos(time_t t){//1970,1,1,0０::00::00
    static char s[20];
    struct tm* lt = localtime(&t);
    sprintf(s,"%04d-%02d-%02d %02d:%02d:%02d",
            lt->tm_year + 1900,
            lt->tm_mon + 1,
            lt->tm_mday,
            lt->tm_hour,
            lt->tm_min,
            lt->tm_sec);
    return s;
}
int main(int argc,char* argv[]){
    if(argc < 2)
        goto usage;
    struct stat st;
    if(argc < 3){
        if(stat(argv[1],&st) == -1){
            perror("stat");
            return -1;
        }
    }else if(!strcmp(argv[2],"-l")){
        if(lstat(argv[1],&st) == -1){
            perror("lstat");
            return -1;
        }
    }else
        goto usage;
    printf("    设备ID:%ld\n",st.st_dev);
    printf("    i节点号:%ld\n",st.st_ino);
    printf("       模式:%s\n",mtos(st.st_mode));
    printf("    硬链接数:%lu\n",st.st_nlink);
    printf("      属主ID:%u\n",st.st_uid);
    printf("      属组ID:%u\n",st.st_gid);
    printf("   特殊设备ID:%ld\n",st.st_rdev);
    printf("     总字节数:%ld\n",st.st_size);
    printf("   I/O块字节数:%ld\n",st.st_blksize);
    printf("占用块(512字节)数:%ld\n",st.st_blocks);
    printf("     最后访问时间:%s\n",ttos(st.st_atime));//最后保存的时间
    printf("    最 后修改时间:%s\n",ttos(st.st_ctime));
    printf("  最后状态改变时间:%s\n",ttos(st.st_mtime));
    return 0;
usage:
    fprintf(stderr,"用法:%s <文件> [-l]\n",argv[0]);
    return -1;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/052916$ ./a.out /usr/bin/passwd
    设备ID:2050
    i节点号:6292305
       模式:-rwsr-xr-x
    硬链接数:1
      属主ID:0
      属组ID:0
   特殊设备ID:0
     总字节数:47032
   I/O块字节数:4096
占用块(512字节)数:96
     最后访问时间:2016-02-17 20:32:10
    最 后修改时间:2015-08-03 20:12:47
  最后状态改变时间:2014-02-17 10:42:52

zn@zn-OptiPlex-9010:~/demo/052916$ ./a.out /tmp/
    设备ID:2050
    i节点号:786433
       模式:drwxrwxrwt
    硬链接数:9
      属主ID:0
      属组ID:0
   特殊设备ID:0
     总字节数:12288
   I/O块字节数:4096
占用块(512字节)数:24
     最后访问时间:2016-05-29 19:20:06
    最 后修改时间:2016-05-29 19:20:06
  最后状态改变时间:2016-05-29 19:20:06

zn@zn-OptiPlex-9010:~/demo/052916$ ls /usr/lib/libchromeXvMCPro.so -lt
lrwxrwxrwx 1 root root 25  8月  3  2015 /usr/lib/libchromeXvMCPro.so -> libchromeXvMCPro.so.1.0.0
zn@zn-OptiPlex-9010:~/demo/052916$ ./a.out /usr/lib/libchromeXvMCPro.so
    设备ID:2050
    i节点号:6294434
       模式:-rw-r--r--
    硬链接数:1
      属主ID:0
      属组ID:0
   特殊设备ID:0
     总字节数:51752
   I/O块字节数:4096
占用块(512字节)数:104
     最后访问时间:2016-04-01 17:20:02
    最 后修改时间:2015-08-03 20:12:50
  最后状态改变时间:2014-02-05 18:41:33
zn@zn-OptiPlex-9010:~/demo/052916$ ./a.out /usr/lib/libchromeXvMCPro.so -l
    设备ID:2050
    i节点号:6294432
       模式:lrwxrwxrwx
    硬链接数:1
      属主ID:0
      属组ID:0
   特殊设备ID:0
     总字节数:25
   I/O块字节数:4096
占用块(512字节)数:0
     最后访问时间:2016-05-29 19:17:48
    最 后修改时间:2015-08-03 20:12:50
  最后状态改变时间:2015-08-03 20:12:50
#endif
