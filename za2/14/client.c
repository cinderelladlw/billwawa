#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
  struct sockaddr_in server;
  memset(&server, 0x00, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(8888);
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  int err;
  err = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
  
  char buff[1024] = "hello";
  printf("send: %s\n", buff);
  //err = send(sockfd, buff, strlen(buff), 0);
  err = send(sockfd, buff, 1024, 0);
  close(sockfd);
  return 0;
} 




