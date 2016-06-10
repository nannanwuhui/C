#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
int tree(const char* dir,int depth){
    DIR* dp = opendir(dir);
    if(!dp){
        perror("opendir");
        return -1;
    }
    //切换当前工作目录，以便递归的时候使用，比如./a.out的最开始的工作目录是x/
    //x/下有empty，empty下还有subdir的时候，当处理empty目录的时候，会先切换当前工作
    //目录到empty，然后再处理subdir。如果没有切换当前工作目录的话，在x/去opendir(subdir);
    //肯定会出错，因为没有带路径，应该是/empty/subdir
    if(chdir(dir) == -1){
        perror("dir");
        return -1;
    }
    errno = 0;
    struct dirent* de;
    for(de = readdir(dp);de;de = readdir(dp)){
        if(de->d_type != DT_DIR){
            printf("%*s%s\n",depth * 2,"",de->d_name);
        }
        else if(strcmp(de->d_name,"..") && strcmp(de->d_name,".")){
            printf("%*s%s/\n",depth * 2,"",de->d_name);
            if(tree(de->d_name,depth + 1) == -1){
                return -1;
            }
        }
    }
    if(errno){
        perror("readdir");
        return -1;
    }
    //处理完当前目录以后要回到上级目录，比如处理完subdir以后，要回到empty目录.
    if(chdir("..") == -1){
        perror("chdir");
        return  -1;
    }
    closedir(dp);
    return 0;
}
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法: %s <目录>\n",argv[0]);
        return -1;
    }
    return tree(argv[1],0);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/060916$ ./a.out /etc/
zn@zn-OptiPlex-9010:~/demo/060916$ ./a.out /tmp/
zn@zn-OptiPlex-9010:~/demo/060916$ ./a.out /usr/include/
#endif
