#ifndef _FLOW_H_
#define _FLOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <signal.h>


#define N 5

typedef struct noderule NodeRule;  
struct noderule {
  int max;
  int min;
  int average;
};

typedef struct flowrule FlowRule;
struct flowrule {
  short enable[N];
  int lck_semid[N];
  struct noderule node_rule[N];
};


union semun {
  int              val;           /* Value for SETVAL */
  struct semid_ds *buf;           /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;         /* Array for GETALL, SETALL */
  struct seminfo  *__buf;         /* Buffer for IPC_INFO  */
};

int controlInit(int *shm_id, int *sem_id, int n);
int controlLock(int sem_id);
int controlUnlock(int sem_id);

#endif
