#include <stdio.h>
//一般情况下都是自然行号，就是在哪一行就是那一行的行号
//系统管理员在查询日志的时候可能会以哪一个文件然后第几行作为关键字来查询，
//如果代码修改了，以前的关键字就不好使了，这个时候可以用#line来指定行号
int main(void){
    printf("%d\n",__LINE__);
#line 100//指定下一行的行号，也就是下一行从100行开始算
    printf("%d\n",__LINE__);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/041616$ gcc line.c
zn@zn-OptiPlex-9010:~/demo/041616$ ./a.out
4
100
zn@zn-OptiPlex-9010:~/demo/041616$ gcc -E line.c -o line.i
zn@zn-OptiPlex-9010:~/demo/041616$ tail -6 line.i
int main(void){
    printf("%d\n",4);
# 100 "line.c"
    printf("%d\n",100);
    return 0;
}
#endif
