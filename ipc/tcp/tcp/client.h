#ifndef  _CLIENT_H_
#define  _CLIENT_H_
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h> 

void syserror(char *p);
int client(char *ip, int port);
int Recvmsg(char *msg, int sockfd);

#endif
