#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

#define BUFFLEN 1024
#define SERVER_PORT 8888
int main(int argc, char *argv[])
{
	int s;	                        /*�������׽����ļ�������*/
	struct sockaddr_in server;	/*���ص�ַ*/
	char buff[BUFFLEN];             /*�շ����ݻ�����*/
	int n = 0;	                /*�����ַ�������*/
	
	/*����TCP�׽���*/
	s = socket(AF_INET, SOCK_STREAM, 0);
	
	/*��ʼ����ַ*/
	memset(&server, 0, sizeof(server));                     /*����*/
	server.sin_family = AF_INET;                            /*AF_INETЭ����*/
//	server.sin_addr.s_addr = htonl(INADDR_ANY);             /*���Ȿ�ص�ַ*/
	server.sin_addr.s_addr = inet_addr("127.0.0.1");             /*���Ȿ�ص�ַ*/
	server.sin_port = htons(SERVER_PORT);                   /*�������˿�*/	
	
	/*���ӷ�����*/
	int err = connect(s, (struct sockaddr*)&server,sizeof(server));
        if(err != 0) {
        	printf("connect error\n");
        }
	memset(buff, 0, BUFFLEN);/*����*/
	strcpy(buff, "TIME");/*���������ַ���*/
	/*��������*/
	send(s, buff, strlen(buff), 0);
	memset(buff, 0, BUFFLEN);/*����*/
	/*��������*/	
        sleep(25);
	n = recv(s, buff, BUFFLEN, 0);
	/*��ӡ��Ϣ*/
	if(n >0){
		printf("TIME:%s",buff);	
	}
	close(s);
	return 0;		
}
