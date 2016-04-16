#include <stdio.h>
#pragma GCC poison goto
#pragma GCC poison float
int main(){
    goto escape;
    float f = 3.14;
    return 0;
escape:
    printf("goto到第%d行!\n",__LINE__);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/041616$ gcc pragma1.c
pragma1.c: In function ‘main’:
pragma1.c:5:5: error: attempt to use poisoned "goto"
     goto escape;
     ^
pragma1.c:6:5: error: attempt to use poisoned "float"
     float f = 3.14;
     ^
#endif
