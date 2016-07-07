#include <stdio.h>
#include <pthread.h>
void* thread_proc(void* arg){
    for(;;){
        sleep(1);
        printf("hello niklaus!\n");
    }
}
void* thread_proc2(void* arg){
    for(;;){
        sleep(5);
        printf("hello niklaus2222!\n");
    }
}
int main(){
    pthread_t tid,tid2;
    pthread_create(&tid,NULL,thread_proc,NULL);
    pthread_create(&tid2,NULL,thread_proc2,NULL);
    pthread_join(tid,NULL);
    pthread_join(tid2,NULL);
    return 0;
}
