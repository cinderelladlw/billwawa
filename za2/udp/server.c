#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#define PORT 8000

int main()
{
  int sockfd;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) {
    perror("socket");
  }
  struct sockaddr_in serv;
  int len;
  memset(&serv, 0x00, sizeof(struct sockaddr_in));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  len = sizeof(serv);
  
  if(bind(sockfd, (struct sockaddr *)&serv, sizeof(struct sockaddr)) < 0) {
    perror("bind");
  }
  int recvnum;
  int sendnum;
  char sendbuf[20] = "i am server";
  char recvbuf[20];
  struct sockaddr_in clie;
  while(1) {
    printf("server wait:\n");
    recvnum = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&clie, (socklen_t *)&len);
    if(recvnum < 0) {
      perror("recvfrom");
    }
    recvbuf[recvnum] = '\0';
    printf("server recv %d bytes: %s\n", recvnum, recvbuf);
    sendnum = sendto(sockfd, sendbuf, recvnum, 0, (struct sockaddr *)&clie, len);
    if(sendnum < 0) {
      perror("sendto");
    }
  }
  close(sockfd);
  return 0;
}
