#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stderr,"用法:%s <链接路径>\n",argv[0]);
        return -1;
    }
    if(/*unlink*/remove(argv[1]) == -1){
        perror(/*"unlink"*/"remove");
        return -1;
    }
    return 0;
}
#if 0
(remove)
zn@zn-OptiPlex-9010:~/demo/060516$ touch link.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 20
-rw-rw-r-- 1 zn zn    0  6月  5 12:21 link.txt
-rwxrwxr-x 1 zn zn 8703  6月  5 12:20 a.out
-rw-rw-r-- 1 zn zn 1028  6月  5 12:20 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$ gcc unlink.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out link.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 20
-rwxrwxr-x 1 zn zn 8703  6月  5 12:21 a.out
-rw-rw-r-- 1 zn zn 1028  6月  5 12:20 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$ mkdir empty
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 24
drwxrwxr-x 2 zn zn 4096  6月  5 12:22 empty
-rwxrwxr-x 1 zn zn 8703  6月  5 12:21 a.out
-rw-rw-r-- 1 zn zn 1028  6月  5 12:20 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out empty/
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 20
-rwxrwxr-x 1 zn zn 8703  6月  5 12:21 a.out
-rw-rw-r-- 1 zn zn 1028  6月  5 12:20 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$ mkdir subdir
zn@zn-OptiPlex-9010:~/demo/060516$ ls
a.out  link.c  subdir  unlink.c
zn@zn-OptiPlex-9010:~/demo/060516$ cd subdir/
zn@zn-OptiPlex-9010:~/demo/060516/subdir$ ls
zn@zn-OptiPlex-9010:~/demo/060516/subdir$ touch a.txt
zn@zn-OptiPlex-9010:~/demo/060516/subdir$ s
zn@zn-OptiPlex-9010:~/demo/060516$ ls
a.out  link.c  subdir  unlink.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out subdir/
remove: Directory not empty
(unlink)
zn@zn-OptiPlex-9010:~/demo/060516$ gcc unlink.c
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out link.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 24
-rwxrwxr-x 1 zn zn 8703  6月  5 12:08 a.out
-rw-rw-r-- 1 zn zn  295  6月  5 12:08 unlink.c(硬链接数变为1)
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
-rw-rw-r-- 1 zn zn   12  6月  5 12:03 link2.txt
zn@zn-OptiPlex-9010:~/demo/060516$ cat link2.txt
Hello,Link!
zn@zn-OptiPlex-9010:~/demo/060516$ ./a.out link2.txt
zn@zn-OptiPlex-9010:~/demo/060516$ ls -lt
total 20
-rwxrwxr-x 1 zn zn 8703  6月  5 12:08 a.out
-rw-rw-r-- 1 zn zn  295  6月  5 12:08 unlink.c
-rw-rw-r-- 1 zn zn  939  6月  5 12:05 link.c
zn@zn-OptiPlex-9010:~/demo/060516$
#endif
