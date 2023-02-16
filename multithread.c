#define _GNU_SOURCE
#include<stdlib.h>
#include<sched.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

//struct thread_info {
 
//    pthread_t thread_id; // ID returned by pthread_create()
//    int core_id; // Core ID we want this pthread to set its affinity to
//};
 
int a=0 ;

void *func1(void *arg){
  printf("thread 1 running\n");
  sleep(10);
  //struct thread_info *thread_info = arg;
  //const int core_id = thread_info->core_id;
  //printf("thread1 is runnning on cpu core : %d",core_id);
  const pthread_t pid = pthread_self();
  cpu_set_t cpuset;
  int core = 1;

  //actual affinity of thread
  int result = pthread_getaffinity_np(pid, sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        perror("pthread_getaffinity_np");
        exit(EXIT_FAILURE);
    }
    printf("TOTAL CPU CORE : %d \n",CPU_SETSIZE);
    printf("Thread %lu is running on CPU(s): \n", pid);
    int flag=0;
    
    for (int i = 0; i < CPU_SETSIZE; i++) {
        if (CPU_ISSET(i, &cpuset)) {
            printf("%d ", i);
        }
        else{
          if(flag==0){
            core=i;
            flag=1;
          }
        }
    }
    printf("\n");
    //set affinity
      CPU_ZERO(&cpuset);
      core=25;
      CPU_SET(core,&cpuset);
      pthread_setaffinity_np(pid,sizeof(cpu_set_t),&cpuset);
      sleep(10);
      int v=10000;
      while(1){
      //v--;
      ;
      }
      printf("Thread %lu is set to core: %d\n",pid, core);
      printf("AFFINITY after setting to core : %d\n",core);
    //Now check affinity of thread
    result = pthread_getaffinity_np(pid, sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        perror("pthread_getaffinity_np");
        exit(EXIT_FAILURE);
    }
    printf("Thread %lu is running on CPU(s): \n", pid);
    for (int i = 0; i < CPU_SETSIZE; i++) {
        if (CPU_ISSET(i, &cpuset)) {
            printf("%d ", i);
        }
       
    }
    printf("\n");
    
  a=10;
  printf("thread 1 running\n");
  printf("value of a by thread1: %d\n",a);
  return(NULL);
}

void *func2(void *arg){
  sleep(10);
  printf("thread 2 running\n");
  printf("value of a by thread2: %d\n",a);
  return(NULL);
}

int main(){
    int err;
    pthread_t t1,t2;
    
    pid_t pid = getpid();
    
    
    
    printf("Process ID: %d\n", pid);
    
    err=pthread_create(&t1,NULL,func1,NULL);
    
    
    
    
    
    
    if(err != 0){
      perror("error in creating thread1");
      exit(1);
    }
    
    err=pthread_create(&t2,NULL,func2,NULL);
    
    if(err != 0){
      perror("error in creating thread2");
      exit(1);
    }
    err = pthread_join(t1, NULL);
    err = pthread_join(t2, NULL);
    exit(0); 
    return 0;
}