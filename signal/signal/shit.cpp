#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

void sig_handle(int signo){
  cout << "sig_handle:" << getpid() << ":" <<signo << endl;
} 

int main(int args,char *argc[])
{
  signal(SIGUSR1, sig_handle); 
  pid_t pid;
  pid = fork();
  if(pid == 0) {
    cout << "son process:"<< getpid() << endl;
    //pause();
    while (1)
      ;
    cout << "continue" << endl;
  } else {
    cout << "father process:" << getpid()<<endl;
    cout << "pid:" << pid <<endl;
    sleep(1);
    kill(pid, SIGUSR1);
    while(true){
      ;
    }
  }
  printf("........................\n");
  return 0;
}
