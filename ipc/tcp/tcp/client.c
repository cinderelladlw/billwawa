#include "client.h"


int client(char *ip, int port)
{
	struct sockaddr_in servaddr;
        int sockfd; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(port);
	inet_pton(AF_INET, ip, &servaddr.sin_addr);
	
        connect(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        return sockfd;
}

int Recvmsg(char *msg, int sockfd)
{
	int len;
	if((len = recv(sockfd, msg, 99, 0)) == -1)
	{
		syserror("link server error.");
	}
	msg[len]='\0';
        return -1;
}

void syserror(char *p)
{
	puts(p);
	exit(1);
}

