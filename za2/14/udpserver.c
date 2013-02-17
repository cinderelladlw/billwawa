#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  struct sockaddr_in local;
  struct sockaddr_in client;
  int len;
  memset(&local, 0x00, sizeof(local));
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = htonl(INADDR_ANY);
  local.sin_port = htons(8888);
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  char buff[1024]; 
  int err = bind(sockfd, (struct sockaddr *)&local, sizeof(local));
  while(1) {
    int n = recvfrom(sockfd, buff, 1024, 0, (struct sockaddr *)&client, &len);
    printf(":%s\n", buff); 
  }
  close(sockfd); 
  return 0;
}


