#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

sigset_t bset;

void sig_handler(int signum)
{
  printf("receive signal %d\n", signum);
}

void *sigmgr_thread()
{  
  sigset_t oset;
  int sig;
  int rc;
  pthread_t ppid = pthread_self();
  pthread_detach(ppid);
  while (1) {
    rc = sigwait(&bset, &sig);
    if (rc != -1) {
      sig_handler(sig);
    } else {
      printf("sigwaitinfo() return err:%d:%s\n", errno, strerror(errno));
    }
  }
}


int main()
{
  sigset_t oset;
  int i;
  pid_t pid = getpid();
  pthread_t ppid;
  
  sigemptyset(&bset);
  sigaddset(&bset, SIGRTMIN);
  sigaddset(&bset, SIGRTMIN + 2);
  sigaddset(&bset, SIGRTMAX);
  sigaddset(&bset, SIGUSR1);
  sigaddset(&bset, SIGUSR2);

  if (pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0) {
    printf("set pthread_sigmask error.\n");
  }
  kill(pid, SIGRTMAX);
  kill(pid, SIGRTMAX);
  kill(pid, SIGRTMIN + 2);
  kill(pid, SIGRTMIN);
  kill(pid, SIGRTMIN+2);
  kill(pid, SIGRTMIN);
  kill(pid, SIGUSR2);
  kill(pid, SIGUSR2);
  kill(pid, SIGUSR1);
  kill(pid, SIGUSR1);
  // Create the dedicated thread sigmgr_thread() which will handle signals synchronously
  pthread_create(&ppid, NULL, sigmgr_thread, NULL);
  sleep(2);
  kill(pid, SIGRTMIN+2);
  sleep(2);
  kill(pid, SIGRTMIN);
  while(1); 
  return 0; 
}

