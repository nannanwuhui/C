#include <stdio.h>
#include <stdlib.h>

void *
my_malloc(int sz, char *s)
{
    void *p = malloc(sz) ;
    if (p != NULL)
	return p ;
    fprintf(stderr, "test: malloc failure for %d bytes in <%s>\n",
	sz, s);
    exit(1);
}
int main(){
    char** d_src = my_malloc(4 * sizeof(void*),"d_src");
    //d_src[]将来存放的是一个指针，&d_src是指针的指针，所以&d_src[0]和&d_src[1]相差8个字节
    printf("%p\n",&d_src[0]);
    printf("%p\n",&d_src[1]);
    return 0;
}
