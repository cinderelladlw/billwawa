#include "flow.h"

#define SHMKEY   0x100001
#define SEMKEY   0x200001
#define SHMSIZE  2048 

FlowRule *shmaddr;
void _shmflush(int arg);

int controlInit(int *shm_id, int *sem_id, int n)
{
  int shmid;
  int semid[N];
  int i;

  // 获得共享内存的ID
  shmid = shmget(SHMKEY, SHMSIZE, 0666);
  if(shmid != -1) {
    if(shmaddr != (FlowRule *)-1) {
      shmdt(shmaddr);
      shmctl(shmid, IPC_RMID, 0);
    }   
  } 
  shmid = shmget(SHMKEY, SHMSIZE, 0666|IPC_CREAT|IPC_EXCL);
  if(shmid == -1)
    return -1;
  shmaddr = (FlowRule *)shmat(shmid, NULL, 0);
  if(shmaddr == (FlowRule *)-1) {
    shmctl(shmid, IPC_RMID, 0);
    return -2; 
  } 
  printf("shmid:[%d]\n", shmid);
  *shm_id = shmid;
  // 获得信号量 
  for(i = 0; i < N; i++) {
    semid[i] = semget(SEMKEY + i, 1, 0666);
    if(semid[i] != -1) {
      semctl(semid[i], 0, IPC_RMID);
    }
    semid[i] = semget(SEMKEY + i, 1, 0666|IPC_CREAT|IPC_EXCL);
    if(semid[i] == -1)
      return -3;
    printf("[%d]\n", semid[i]);
  }
  for(i = 0; i < N; i ++)
    sem_id[i] = semid[i];
  for(i = 0; i < N; i ++)
    shmaddr -> lck_semid[i] = semid[i];
  
  // 信号量赋初值 
  for(i = 0; i < N; i++) {
     _init_sem(semid[i], 1);
  }
  //sleep(1);

  // 设置计数器 
  signal(SIGALRM, _shmflush);
  
  struct itimerval tick;
  tick.it_value.tv_sec = 1; 
  tick.it_value.tv_usec = 0; 
  tick.it_interval.tv_sec = 1; 
  tick.it_interval.tv_usec = 0; 
  if(setitimer(ITIMER_REAL, &tick, 0) != 0)
    return -5;
  return 100;
}

void _shmflush(int arg)
{
  printf("flush begin\n");
  int i;
  for(i = 0; i < N; i ++) {
    shmaddr -> node_rule[i].max     = 5;
    shmaddr -> node_rule[i].min     = 5;
    shmaddr -> node_rule[i].average = 5;
    shmaddr -> enable[i] = 1;
  }
  printf("flush end  \n");
}




int _init_sem(int sem_id, int init_value)
{
  union semun sem_union;
  sem_union.val = init_value;

  if(semctl(sem_id, 0, SETVAL, sem_union) == -1) {
    return -1;
  }
  return 0;
}

int controlLock(int sem_id)
{
  struct sembuf sem_buf;
  sem_buf.sem_num =  0;
  sem_buf.sem_op  = -1;
  sem_buf.sem_flg = SEM_UNDO;
    
  while(semop(sem_id, &sem_buf, 1) == -1)
    ;   
  return 0;
}


int controlUnlock(int sem_id)
{
  struct sembuf sem_buf;
  sem_buf.sem_num =  0;
  sem_buf.sem_op  =  1;
  sem_buf.sem_flg =  SEM_UNDO;
    
  while(semop(sem_id, &sem_buf, 1) == -1)
    ;   
  return 0;
}













