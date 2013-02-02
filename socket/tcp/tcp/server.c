#include "server.h"

int SERV_PORT = 8888;//�˿ں�

/*������*/
int ServerSysError(char *str)
{
	fprintf(stdout, "server-erro@servertime-%ld:%s \n", time(NULL), str);
	fflush(stdout);
	exit(1);
}
int ServerUserError(char *str)
{
	fprintf(stdout, "server-user@servertime-%ld:%s \n", time(NULL), str);
	fflush(stdout);
	return 0;
}
void NotNetLink(int signo)//�źŴ���
{
	fprintf(stdout, "server-signo@servertime-%ld: :Signal is %d \n", time(NULL), signo);
	fflush(stdout);
        signal(signo, NotNetLink);
}


/*
������������socket�ӿ�,���׽��ֵ�������ַ�����ؿ����׽���
int SERV_PORT �� �����˿ں�
��ȷ���ؿ��õ��׽ӿڣ����󷵻أ�1

�󶨷��ǣ�����ʽ
����Э�飺Internet�����ַ��IPV4�����ȶ��ɿ������ӣ�˫��ͨ�ŷ�ʽ��TCPЭ�飩
*/
int SetSocket(int SERV_PORT)
{
	int sockfd;
	int opt;
	struct sockaddr_in servaddr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		return -1;
	}
	bzero(&servaddr, sizeof(servaddr));//�õ�ַ&servaddr��ǰsizeof(servaddr)���ֽ�Ϊ��
	opt = SO_REUSEADDR;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//ͬһ�׽ӿڿɱ���������
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		close(sockfd);
		return -1;
	}

	return sockfd;
}

/*
����ͻ������ӵ�sockfd�������Խ���USER_NUMBER���ͻ������ӣ����ߣ�
int sockfd - ���õ��׽ӿڵ�ַ
��ȷ����0�����򷵻�-1
*/
int LanuchServer(int *sockfd)
{
	if(listen(*sockfd, USER_NUMBER) == -1)
	{
		return -1;
	}
	fflush(stdout);
	return 0;
}

/*
��ͻ��˷�����Ϣ
const char* msg �� Ҫ���͵���Ϣ
int client_fd �� ���͵�ָ���ͻ�����ַ
���󷵻أ�1����ȷ���ط����ֽ���

*/
int SendMsg(const char* msg, int client_fd)
{
	int len;	

	if((len = send(client_fd, msg, strlen(msg), 0)) == -1)
	{
		return -1;
	}
	return len;
}

