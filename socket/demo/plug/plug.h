#ifndef  _PLUG_H_
#define  _PLUG_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/select.h>

#define BUFFLEN 1024
#define SERVER_PORT 8888
#define BACKLOG 5
#define CLIENTNUM 1024/*最大支持客户端数量*/

/*可连接客户端的文件描述符数组*/
int connect_host[CLIENTNUM];

static int connect_number =  0;

static void *handle_request(void *argv);

static void *handle_connect(void *argv);

void run();

#endif
