#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEST_PORT 8000
#define DSET_IP_ADDRESS  "127.0.0.1"

int main()
{
  int sockfd;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) {
    perror("socket");
  }
  
  struct sockaddr_in addr_serv;
  int len;
  memset(&addr_serv, 0, sizeof(addr_serv));
  addr_serv.sin_family = AF_INET;
  addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
  addr_serv.sin_port = htons(DEST_PORT);
  len = sizeof(addr_serv);

  
  int sendnum;
  int recvnum;
  char sendbuf[20] = "hey, who are you?";
  char recvbuf[20];
    
  printf("client send: %s\n", sendbuf);
  
  sendnum = sendto(sockfd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&addr_serv, len);
  if(sendnum < 0) {
    perror("sendto error:");
  }
  
  recvnum = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&addr_serv, (socklen_t *)&len);
  if(recvnum < 0) {
    perror("recvfrom error:");
  }
  
  recvbuf[recvnum] = '\0';
  printf("client receive %d bytes: %s\n", recvnum, recvbuf);
  close(sockfd);
  return 0;
}
