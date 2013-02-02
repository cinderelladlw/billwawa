#include "server.h"

int SERV_PORT = 8888;//端口号

/*错误处理*/
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
void NotNetLink(int signo)//信号处理
{
	fprintf(stdout, "server-signo@servertime-%ld: :Signal is %d \n", time(NULL), signo);
	fflush(stdout);
        signal(signo, NotNetLink);
}


/*
建立服务器端socket接口,绑定套接字到本机地址，返回可用套接字
int SERV_PORT － 监听端口号
正确返回可用的套接口，错误返回－1

绑定放是：共享方式
采用协议：Internet网络地址（IPV4），稳定可靠的连接，双向通信方式（TCP协议）
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
	bzero(&servaddr, sizeof(servaddr));//置地址&servaddr的前sizeof(servaddr)个字节为零
	opt = SO_REUSEADDR;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//同一套接口可被多个程序绑定
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
允许客户机连接到sockfd，最多可以接受USER_NUMBER个客户机连接（在线）
int sockfd - 可用的套接口地址
正确返回0，否则返回-1
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
向客户端发送信息
const char* msg － 要发送的消息
int client_fd － 发送到指定客户机地址
错误返回－1，正确返回发送字节数

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

