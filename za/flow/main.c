#include "flow.h"

int main()
{
  int i;
  int semid_dlw[N];
  int shmid_dlw;

  printf("%d\n", controlInit(&shmid_dlw, semid_dlw, 5));
  printf(":::semid::%d\n", shmid_dlw);
  FlowRule *shmadd;
  shmadd = (FlowRule *)shmat(shmid_dlw, NULL, 0);  
  for(i = 0; i < N; i ++) 
    printf(":::%d\n", semid_dlw[i]); 
  sleep(1);
  pid_t pid;
  if((pid = fork()) < 0) {
    printf("fork error \n");
  }
  else if(pid == 0) {
    for(i = 0; i < 100; i++) {
      usleep(100000);
      printf("\n CHILD:[%d]\n", i);
      controlLock(shmadd -> lck_semid[2]); 
      printf("child:%d\n", ++shmadd -> node_rule[1].max);
      controlUnlock(shmadd -> lck_semid[2]); 
    }
  } 
  else {
    
    for(i = 0; i < 100; i++) {
      usleep(70000);
      printf("\n PARENT:[%d]\n", i);
      controlLock(shmadd -> lck_semid[2]); 
      printf("parent:%d\n", --shmadd -> node_rule[1].max);
      controlUnlock(shmadd -> lck_semid[2]); 
    } 
  }
  while(1)
    ;
  return 0;
}

