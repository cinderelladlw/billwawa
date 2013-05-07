#include "common.h"

int main(int argc, char **argv)
{
  int sockfd, newsockfd;
  int reuseflag = 1;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
  socklen_t clientaddrlen;
  char recvbuf[RECVLEN+1], sendbuf[SENDLEN+1];
  int recvlen, sendlen;
  
  memset(&serveraddr, 0x00, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //serveraddr.sin_port = htons((atoi(argv[1]))?atoi(argv[1]):PORT);
  serveraddr.sin_port = htons(PORT);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseflag, sizeof(reuseflag)); 
  bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  listen(sockfd, 10);
  
  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
    recvlen = recv(newsockfd, recvbuf, sizeof(recvbuf), 0);
    recvbuf[recvlen] = '\0';
  
    fprintf(stdout, "%s\n", recvbuf); 
    close(newsockfd); 
  }
  return 0;
}
