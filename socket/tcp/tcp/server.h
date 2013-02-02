/*************************************
programme name: cui bo

E-mail: freecunix@gmail.com

date: 20090716

NET-TCP pack

**************************************/
#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define USER_NUMBER 10 //最大连接数

extern int SERV_PORT;//管理员端口

/*错误处理*/
int ServerSysError(char *str);
int ServerUserError(char *str);
void NotNetLink(int signo);//网络断开或异常信号捕捉

/*
建立服务器端socket接口,绑定套接字到本机地址，返回可用套接字
int SERV_PORT － 监听端口号
正确返回可用的套接口，错误返回－1

绑定放是：共享方式
采用协议：Internet网络地址（IPV4），稳定可靠的连接，双向通信方式（TCP协议）
*/
int SetSocket(int SERV_PORT);
/*
允许客户机连接到sockfd，最多可以接受USER_NUMBER个客户机连接（在线）
int sockfd - 可用的套接口地址
正确返回0，否则返回-1
*/
int LanuchServer(int *sockfd);
/*
向客户端发送信息
const char* msg － 要发送的消息
int client_fd － 发送到指定客户机地址
错误返回－1，正确返回发送字节数

*/
int SendMsg(const char* msg, int client_fd);

#endif
