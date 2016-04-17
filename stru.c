#include <stdio.h>
#include <stdint.h>
struct st{
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:1;
    unsigned int d:1;
    unsigned int e:1;
    unsigned int f:1;
    unsigned int g:1;
    unsigned int h:1;
};
int main(){
    uint8_t a = 0xff;
    struct st *pb = (struct st *)&a;
    printf("%d %d %d %d %d %d %d %d\n",pb->h,pb->g,pb->f,pb->e,pb->d,pb->c,pb->b,pb->a);
#if 0 
    printf("pb->a = %d ",pb->a);
    printf("pb->b = %d ",pb->b);
    printf("pb->c = %d ",pb->c);
    printf("pb->d = %d ",pb->d);
    printf("pb->e = %d ",pb->e);
    printf("pb->f = %d ",pb->f);
    printf("pb->g = %d ",pb->g);
    printf("\n");
#endif
    return 0;
}

