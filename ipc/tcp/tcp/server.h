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

#define USER_NUMBER 10 //���������

extern int SERV_PORT;//����Ա�˿�

/*������*/
int ServerSysError(char *str);
int ServerUserError(char *str);
void NotNetLink(int signo);//����Ͽ����쳣�źŲ�׽

/*
������������socket�ӿ�,���׽��ֵ�������ַ�����ؿ����׽���
int SERV_PORT �� �����˿ں�
��ȷ���ؿ��õ��׽ӿڣ����󷵻أ�1

�󶨷��ǣ�����ʽ
����Э�飺Internet�����ַ��IPV4�����ȶ��ɿ������ӣ�˫��ͨ�ŷ�ʽ��TCPЭ�飩
*/
int SetSocket(int SERV_PORT);
/*
����ͻ������ӵ�sockfd�������Խ���USER_NUMBER���ͻ������ӣ����ߣ�
int sockfd - ���õ��׽ӿڵ�ַ
��ȷ����0�����򷵻�-1
*/
int LanuchServer(int *sockfd);
/*
��ͻ��˷�����Ϣ
const char* msg �� Ҫ���͵���Ϣ
int client_fd �� ���͵�ָ���ͻ�����ַ
���󷵻أ�1����ȷ���ط����ֽ���

*/
int SendMsg(const char* msg, int client_fd);

#endif
