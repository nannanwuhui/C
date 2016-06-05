#include <stdio.h>
#include <unistd.h>
int main(){
    //mkdir: No such file or directory
    //test目录不存在，不能一次性的建立连着的目录，父目录不存在
    /*if(mkdir("test/unixc",0777) == -1){
        perror("mkdir");
        return -1;
    }*/
    if(mkdir("test",0777) == -1){
        perror("mkdir");
        return -1;
    }
    if(mkdir("test/unixc",0777) == -1){
        perror("mkdir");
        return -1;
    }
    //mkdir: File exists
    /*if(rmdir("test") == -1){
        perror("rmdir");
        return -1;
    }*/
    if(rmdir("test/unixc") == -1){
        perror("rmdir");
        return -1;
    }
    if(rmdir("test") == -1){
        perror("rmdir");
        return -1;
    }
    return 0;
}

