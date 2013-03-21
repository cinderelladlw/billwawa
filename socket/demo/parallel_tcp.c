#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  //±¾µØµØÖ·
  struct sockaddr_in local;
  memset(&local, 0x00, sizeof(local));
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = htonl(INADDR_ANY);
  local.sin_port = htons(8888);
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  int err = bind(sockfd, (struct sockaddr *)&local, sizeof(local));
  err = listen(sockfd, 5);
  struct sockaddr_in client;
  char buff[1024];
  int newsockfd;
  int len = sizeof(client);
  while(1) {
    
    newsockfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if(newsockfd > 0) {
      if(fork() > 0) {
        close(sockfd);
      } else { 
        memset(&buff, 0x00, 1024);
        err = recv(newsockfd, buff, 1024, 0);
        // buff[strlen(buff)] = '\0';
        printf("recv:[%s]\n", buff);
        close(newsockfd);
      }
    }
  }
  close(sockfd);
  return 0;
}
