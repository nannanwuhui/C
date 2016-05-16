#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)

/* For safe condition variable usage, must use a boolean predicate and  */
/* a mutex with the condition.                                          */
int                 workToDo = 0;
pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

#define NTHREADS                2 
#define WAIT_TIME_SECONDS       2 

void *threadfunc(void *parm)
{
  int               rc;
  struct timespec   ts;
  struct timeval    tp;

  rc = pthread_mutex_lock(&mutex);
  printf("[%ld][%s:%d]pthread_mutex_lock():%s\n",gettid(),__func__,__LINE__, strerror(rc));

  /* Usually worker threads will loop on these operations */
  while (1) {
    rc =  gettimeofday(&tp, NULL);
    printf("[%ld][%s:%d]gettimeofday():%d\n",gettid(),__func__,__LINE__, rc);

    /* Convert from timeval to timespec */
    ts.tv_sec  = tp.tv_sec;
    ts.tv_nsec = tp.tv_usec * 1000;
    ts.tv_sec += WAIT_TIME_SECONDS;

    while (!workToDo) {
      printf("[%ld][%s:%d]Thread blocked\n",gettid(),__func__,__LINE__);
      rc = pthread_cond_timedwait(&cond, &mutex, &ts);
      /* If the wait timed out, in this example, the work is complete, and   */
      /* the thread will end.                                                */
      /* In reality, a timeout must be accompanied by some sort of checking  */
      /* to see if the work is REALLY all complete. In the simple example    */
      /* we'll just go belly up when we time out.                            */
      if (rc == ETIMEDOUT) {
        printf("[%ld][%s:%d]Wait timed out!\n",gettid(),__func__,__LINE__);
        rc = pthread_mutex_unlock(&mutex);
        printf("[%ld][%s:%d]pthread_mutex_unlock():%s\n",gettid(),__func__,__LINE__, strerror(rc));
        pthread_exit(NULL);
      }
      printf("[%ld][%s:%d]pthread_cond_timedwait():%s\n",gettid(),__func__,__LINE__, strerror(rc));
    }

    printf("[%ld]Thread consumes work here\n",gettid());
    workToDo = 0;
  }

  rc = pthread_mutex_unlock(&mutex);
  printf("[%s:%d]pthread_mutex_unlock():%s\n",__func__,__LINE__, strerror(rc));
  return NULL;
}

int main(int argc, char **argv)
{
  int                   rc=0;
  int                   i;
  pthread_t             threadid[NTHREADS];

  printf("Enter Testcase - %s\n", argv[0]);

  printf("Create %d threads\n", NTHREADS);
  for(i=0; i<NTHREADS; ++i) {
    rc = pthread_create(&threadid[i], NULL, threadfunc, NULL);
    printf("[%ld][%s:%d]pthread_create():%s\n",gettid(),__func__,__LINE__,strerror(rc));
  }

  rc = pthread_mutex_lock(&mutex);
  printf("[%ld][%s:%d]pthread_mutex_lock():%s\n",gettid(),__func__,__LINE__, strerror(rc));

  printf("[%ld][%s:%d]One work item to give to a thread\n",gettid(),__func__,__LINE__);
  workToDo = 1;
  printf("[%ld][%s:%d]start to sleep!\n",gettid(),__func__,__LINE__);
  //sleep(5);//这里睡觉的话，pthread_cond_timedwait无法返回，因为它没有办法获得锁，这是死锁的问题了
  rc = pthread_cond_signal(&cond);
  printf("[%ld][%s:%d]pthread_cond_signal():%s\n",gettid(),__func__,__LINE__, strerror(rc));

  rc = pthread_mutex_unlock(&mutex);
  printf("[%ld][%s:%d]pthread_mutex_unlock():%s\n",gettid(),__func__,__LINE__, strerror(rc));

  printf("[%ld][%s:%d]Wait for threads and cleanup\n",gettid(),__func__,__LINE__);
  for (i=0; i<NTHREADS; ++i) {
    rc = pthread_join(threadid[i], NULL);
    printf("[%ld][%s:%d]pthread_join():%s\n",gettid(),__func__,__LINE__, strerror(rc));
  }

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
  printf("Main completed\n");
  return 0;
}
