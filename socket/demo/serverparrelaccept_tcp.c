#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#define BUFFLEN 1024
#define SERVER_PORT 8888
#define BACKLOG 5

static void handle_request(int s_c)
{
	time_t now;		             /*ʱ��*/
	char buff[BUFFLEN];                  /*�շ����ݻ�����*/
	int n = 0;
	memset(buff, 0, BUFFLEN);            /*����*/
	n = recv(s_c, buff, BUFFLEN,0);      /*���շ��ͷ�����*/
	if(n > 0 && !strncmp(buff, "TIME", 4))/*�ж��Ƿ�Ϸ���������*/
	{
		memset(buff, 0, BUFFLEN);    /*����*/
		now = time(NULL);            /*��ǰʱ��*/
		sprintf(buff, "%24s\r\n",ctime(&now));/*��ʱ�俽���뻺����*/
		send(s_c, buff, strlen(buff),0);/*��������*/
	}		
	/*�رտͻ���*/
	close(s_c);	
}

static void handle_connect(int s_s)
{
	int s_c;	/*�ͻ����׽����ļ�������*/
	struct sockaddr_in from;	/*�ͻ��˵�ַ*/
	int len = sizeof(from);
	
	/*����������*/
	while(1)
	{
		/*���տͻ�������*/
		s_c = accept(s_s, (struct sockaddr*)&from, &len);
		if(s_c > 0)/*�ͻ��˳ɹ�����*/
		{
			/*�������̽������ݴ���*/
			if(fork() > 0){/*������*/
				close(s_c);/*�رո����̵Ŀͻ��������׽���*/
			}else{
				handle_request(s_c);/*������������*/
				return(0);	
			}
		}
	}
}


int main(int argc, char *argv[])
{
	int s_s;	/*�������׽����ļ�������*/
	struct sockaddr_in local;	/*���ص�ַ*/	
	
	/*����TCP�׽���*/
	s_s = socket(AF_INET, SOCK_STREAM, 0);
	
	/*��ʼ����ַ��Ŷ��*/
	memset(&local, 0, sizeof(local));/*����*/
	local.sin_family = AF_INET;/*AF_INETЭ����*/
	local.sin_addr.s_addr = htonl(INADDR_ANY);/*���Ȿ�ص�ַ*/
	local.sin_port = htons(SERVER_PORT);/*�������˿�*/
	
	/*���׽����ļ��������󶨵����ص�ַ�Ͷ˿�*/
	int err = bind(s_s, (struct sockaddr*)&local, sizeof(local));
	err = listen(s_s, BACKLOG);/*����*/
	
	/*�����ͻ�������*/
	handle_connect(s_s);
	
	close(s_s);
	
	return 0;		
}