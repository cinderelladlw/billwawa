#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 1212
#define SIZE 1024

struct comm {
  char id[10];
  char name[10];
};

int main()
{
  int shmid;
  struct comm *shmaddr;
  struct shmid_ds buf;
  struct comm *com = malloc(sizeof(struct comm));
  strcpy(com->id, "1010123");
  strcpy(com->name, "bill");
   
  shmid = shmget(KEY, SIZE, IPC_CREAT|0600);
  if(fork() == 0) {
    shmaddr = (struct comm *)shmat(shmid, NULL, 0);
    strcpy(shmaddr->id, com->id);
    strcpy(shmaddr->name, com->name);
    printf("child process write in shm:%s\n", com->id);
    printf("child process write in shm:%s\n", com->name);
    shmdt(shmaddr);
  } else {
    sleep(1);
    shmctl(shmid, IPC_STAT, &buf);
    //printf("shm_segsz = %d bytes\n", buf.shm_segsz); 
    //printf("shm_cpid = %d bytes\n", buf.shm_cpid); 
    //printf("shm_lpid = %d bytes\n", buf.shm_lpid); 
    shmaddr = (struct comm *)shmat(shmid, 0, SHM_RDONLY);
    printf("father process: %s\n", shmaddr->id);
    printf("father process: %s\n", shmaddr->name);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
  }
  return 0;
}
