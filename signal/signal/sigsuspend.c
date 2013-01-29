#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
volatile sig_atomic_t quitflag = 0; /* set nonzero by signal handler */

 /* one signal handler for SIGINT and SIGQUIT */
static void sig_handler(int signo)
{
    if (signo == SIGINT)
                printf("\ninterrupt\n");
        else if (signo == SIGQUIT)
                quitflag = 1; /* set flag for main loop */
}
int main(int argc, char *argv[])
{
        sigset_t newmask, oldmask, zeromask;
        if (signal(SIGINT, sig_handler) == SIG_ERR)
                perror("signal(SIGINT) error");
        if (signal(SIGQUIT, sig_handler) == SIG_ERR)
                perror("signal(SIGQUIT) error");
        sigemptyset(&newmask);
        sigemptyset(&zeromask);
        sigaddset(&newmask, SIGQUIT);
        /* Block SIGQUIT and save current signal mask */
        if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) != 0)
                perror("sigprocmask SIG_BLOCK error");
        //while(1); 
        while (quitflag == 0)
                sigsuspend(&zeromask);
        quitflag = 0;
        /* Reset signal mask which unblocks SIGQUIT */
        if (sigprocmask(SIG_SETMASK, &oldmask, NULL) != 0)
                perror("sigprocmask SIG_SETMASK error");
        exit(0);
}
