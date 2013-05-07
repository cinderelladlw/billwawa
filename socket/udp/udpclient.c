#include "common.h"

int main(int argc, char **argv)
{
  int sockfd;
  char recvbuf[RECVLEN+1];
  char sendbuf[SENDLEN+1];
  int recvlen, sendlen;
  struct sockaddr_in serveraddr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&serveraddr, 0x00, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(argv[1]?argv[1]:"127.0.0.1");
  serveraddr.sin_port = htons(atoi(argv[2])?atoi(argv[2]):PORT);
  
  while (1) {
    fgets(sendbuf, SENDLEN+1, stdin);  
    printf("get message ok\n");
    sendto(sockfd, sendbuf, SENDLEN+1, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)); 
    printf(".send ok\n"); 
  } 
    
  return 0;
}
