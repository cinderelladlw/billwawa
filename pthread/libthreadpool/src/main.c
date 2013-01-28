#include <stdio.h>
#include "thread-pool.h"

void slp(tp_work *a, tp_work_desc *b)
{
  printf("...sx .......................\n");
  sleep(1);
}

int main()
{
  tp_thread_pool *sx = (tp_thread_pool *)malloc(sizeof(tp_thread_pool)); 
   
  tp_work *sb = (tp_work *)malloc(sizeof(tp_work));
  tp_work_desc *nc = (tp_work_desc *)malloc(sizeof(tp_work_desc));
  
  nc -> inum = "hello";
  nc -> onum = "world";
  nc -> chnum = 23;
  sb -> process_job = &slp;
  
  sx = creat_thread_pool(3,13);
  (*(sx -> init))(sx);
  sleep(5); 
  printf("..\n..\n..\n");
  (*(sx -> process_job))(sx, sb, nc);
  sleep(5);
  printf("..\n..\n..\n");
  (*(sx -> add_thread))(sx);
  (*(sx -> add_thread))(sx);
  sleep(3);
  printf("..\n..\n..\n");
  (*(sx -> close))(sx);
  sleep(3);
  printf("..\n..\n..\n");
  while(1)
    ;
  return 0;
}
