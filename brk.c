#include <stdio.h>
#include <unistd.h>
void presskey(){
    printf("查看/proc/%u/maps,按<回车>继续...",getpid());
    getchar();
}
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
    return 0;
}
