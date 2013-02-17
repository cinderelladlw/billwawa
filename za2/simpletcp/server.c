#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT 9734

int main()
{
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  
  int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_sockfd, 2);
 // char *bufff = (char *)malloc(100);
  char *bufff;
  int client_sockfd;
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(client_addr);
  while(1)
  {
    printf("server waiting:\n");
    /* accept a connection */
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len);
    /* exchange data */
    while(1) {
        int j = recv(client_sockfd, bufff, 19, 0); 
        bufff[19] = '\0';
        if(j > 0) { 
            if(bufff[j-1] == '\0')
               j --; 
            printf("get char from client: %s\n", bufff);
            printf(":%d\n", j);
            bufff += j;
        } else {
            break;
        }
    }
    //send(client_sockfd, ch, sizeof(ch), 0);
    close(client_sockfd);  
  }
  close(server_sockfd);
  return 0;
}
