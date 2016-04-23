#include <stdio.h>
#include <dlfcn.h>
//不用包含math.h,因为函数指针的类型已经有了。
//如果动态库打开失败的话，我们可以选择打开静态库。这样比操作系统的静态加载更灵活
typedef int (*PFUNC_CALC)(int,int);
typedef void (*PFUNC_SHOW)(int,char,int,int);
int main(void){
//    void* handle = dlopen("./libmath.so",RTLD_NOW);
    //如果只写文件名，则根据LD_LIBRARY_PATH寻找库文件
    void* handle = dlopen("libmath.so",RTLD_NOW);
    if(!handle){
        fprintf(stderr,"dlopen:%s\n",dlerror());
        return -1;
    }
    PFUNC_CALC add = (PFUNC_CALC)dlsym(handle,"add");
    if(!add){
        fprintf(stderr,"dlsym:%s\n",dlerror());
        return -1;
    }
    PFUNC_CALC sub = (PFUNC_CALC)dlsym(handle,"sub");
    if(!sub){
        fprintf(stderr,"dlsym:%s\n",dlerror());
        return -1;
    }
    PFUNC_SHOW show = (PFUNC_SHOW)dlsym(handle,"show");
    if(!show){
        fprintf(stderr,"dlsym:%s\n",dlerror());
        return -1;
    }
    show(30,'+',20,add(30,20));
    show(30,'-',20,sub(30,20));
    if(dlclose(handle)){
        fprintf(stderr,"dlclose:%s\n",dlerror());
        return -1;
    }
    return 0;
}
#if 0
这里不用链接-lmath,因为是在运行的时候动态的加载math库的。
zn@zn-OptiPlex-9010:~/demo/042316$ gcc load.c -ldl
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
30 + 20 = 50
30 - 20 = 10
#endif
#if 0
zn@zn-OptiPlex-9010:~/demo/042316$ gcc load.c -ldl
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
dlopen:libmath.so: cannot open shared object file: No such file or directory
zn@zn-OptiPlex-9010:~/demo/042316$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
zn@zn-OptiPlex-9010:~/demo/042316$ ./a.out
30 + 20 = 50
30 - 20 = 10
#endif
