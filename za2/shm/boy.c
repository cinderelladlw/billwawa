#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

#define KEY          1234
#define SIZE         1024
 
int main()
{
  int shmid;
  char *shmaddr;
  struct shmid_ds buf;
  shmid = shmget(KEY, SIZE, IPC_CREAT | 0600);        /*���������ڴ�*/

  if (fork() == 0)
  {
    shmaddr = (char *) shmat(shmid, 0, 0);
    strcpy(shmaddr, "Hi! I am Chiled process!\n");
    printf("Child:   write to shared memery: \"Hi! I am Child process!\"\n");
    shmdt(shmaddr);
    return;
  }
  else
  {
    sleep(3);                                         /*�ȴ��ӽ���ִ�����*/
    shmctl(shmid, IPC_STAT, &buf);                    /*ȡ�ù����ڴ��״̬*/
    printf("shm_segsz = %d bytes\n", buf.shm_segsz);
    printf("shm_cpid = %d\n", buf.shm_cpid);
    printf("shm_lpid = %d\n", buf.shm_lpid);
    shmaddr = (char*) shmat(shmid, 0, SHM_RDONLY);
    printf("Father:   %s\n", shmaddr);                /*��ʾ�����ڴ�����*/
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);                    /*ɾ�������ڴ�*/
  }
}

