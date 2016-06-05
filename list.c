#include <stdio.h>
#include <dirent.h>
#include <errno.h>
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法: %s <目录>\n",argv[0]);
        return -1;
    }
    DIR* dp = opendir(argv[1]);
    if(!dp){
        perror("opendir");
        return -1;
    }
    errno = 0;
    struct dirent* de;//每一个条目对应着一个文件的信息，当然也可能是一个目录
    for(de = readdir(dp);de;de = readdir(dp)){
        switch (de->d_type) {
        case DT_DIR:
            printf("        目录:");
            break;
        case DT_REG:
            printf("     普通文件:");
            break;
        case DT_LNK:
            printf("       软链接:");
            break;
        case DT_BLK:
            printf("       块设备:");
            break;
        case DT_CHR:
            printf("      字符设备:");
            break;
        case DT_SOCK://socket 插座的意思
            printf("     Unix域套接字:");
            break;
        //unix里有有名管道和无名管道，无名管道不会出现在文件系统里，所以你也不可能看得见
        //只有有名管道才会以文件的形式存在，你才能在文件系统里看得见
        case DT_FIFO:
            printf("        有名管道:");
            break;
        default:
            //在这种操作系统中不会出现未知的文件类型，用虚拟机的话，可能会有未知的，
            //用winwire或者fedora里的vxbox,虚拟机可以和宿主机有共享目录。
            //宿主机里的文件系统可能是ntfs的，或者是fat32的，然后做文件共享，共享到
            //linux底下，是作为一个windows设备mount上去的。类型就是未知，因为它不是合理的
            //unix文件系统。会处理成未知。装在硬盘上的这种系统一般不太会出现未知
            printf("        未知:");
            break;
        }
        printf("%s\n",de->d_name);
        if(errno){
            perror("readdir");
            return -1;
        }
    }
    closedir(dp);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out .
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out /usr/lib
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out /dev/
#endif
