#include <stdio.h>
#include <unistd.h>
void presskey(){
    printf("查看/proc/%u/maps,按<回车>继续...",getpid());
    getchar();
}
//用sbrk分配内存，brk释放内存比较方便
int main(){
    void* p1 = sbrk(4);//RXXX
    printf("p1 = %p\n",p1);
    void *p2 = sbrk(4);//XXXX RXXX
    printf("p2 = %p\n",p2);
    void *p3 = sbrk(4);//XXXX XXXX RXXX
    printf("p3 = %p\n",p3);
    void *p4 = sbrk(4);//XXXX XXXX XXXX RXXX
    printf("p4 = %p\n",p4);
    void *p5 = sbrk(0);//XXXX XXXX XXXX XXXX R
    printf("p5 = %p\n",p5);
    int* pn = (int*)p1;
    pn[0] = 0;
    pn[1] = 1;
    pn[2] = 2;
    pn[3] = 3;
    pn[1023] = 1023;//1页的最后一个整型
    printf("%d,%d,%d,%d,%d\n",pn[0],pn[1],pn[2],pn[3],pn[1023]);
//    pn[1024] = 1024;//Segmentation fault (core dumped)
    void* p6 = sbrk(-8);//XXXX XXXX ---- ---- R
    printf("p6 = %p\n",p6);//p5
    void *p7 = sbrk(-8);//---- ---- R--- ---- -
    printf("p7 = %p\n",p7);//p3
    printf("------------\n");
    int page = getpagesize();
    printf("%p\n",sbrk(page));
    presskey();
    printf("%p\n",sbrk(1));
    presskey();
    printf("%p\n",sbrk(-1));
    presskey();
    printf("%p\n",sbrk(-page));
    presskey();
    printf("------------\n");
    p1 = sbrk(0);    //R--- ---- ---- ---- -
    printf("p1 = %p\n",p1);
    brk(p2 = p1 + 4);//XXXX S--- ---- ---- -
    printf("p2 = %p\n",p2);
    brk(p3 = p2 + 4);//XXXX XXXX S--- ---- -
    printf("p3 = %p\n",p3);
    brk(p4 = p3 + 4);//XXXX XXXX XXXX S
    printf("p4 = %p\n",p4);
    brk(p5 = p4 + 4);//XXXX XXXX XXXX XXXX S
    printf("p5 = %p\n",p5);
    pn = (int*)p1;
    pn[0] = 0;
    pn[1] = 1;
    pn[2] = 2;
    pn[3] = 3;
    pn[1023] = 1023;//1页的最后一个整型
    printf("%d,%d,%d,%d,%d\n",pn[0],pn[1],pn[2],pn[3],pn[1023]);
//    pn[1024] = 1024;
    brk(p3);//XXXX XXXX S--- ---- -
    brk(p1);//S--- ---- ---- ---- -
//    pn[0] = 0;//已经解除映射了，不能再给pn[0]赋值了
    printf("------------------\n");
    void * begin = sbrk(sizeof(int));
    if((intptr_t)begin == -1){
        perror("sbrk");
        return -1;
    }
    pn = (int*)begin;
    *pn = 1234;
    double *pd = (double*)sbrk(sizeof(double));
    if((intptr_t)pd == -1){
        perror("sbrk");
        return -1;
    }
    *pd = 3.14;
    char* psz = (char*)sbrk(256 * sizeof(char));
    if((intptr_t)psz == -1){
        perror("sbrk");
        return -1;
    }
    sprintf(psz,"Hello, World !");
    printf("%d,%g,%s\n",*pn,*pd,psz);
    brk(begin);
    return 0;
}
