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
  int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  
  bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_sockfd, 2);
  char ch[19];
  int client_sockfd;
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(client_addr);
  while(1)
  {
    printf("server waiting:\n");
    /* accept a connection */
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len);
    /* exchange data */
    int j;
    for(j = 0; j < 2; j++) { 
      recv(client_sockfd, ch, 19, 0); 
      printf("get char from client: %s\n", ch);
      printf(":%d\n", j);
      sleep(1);
    } 
    recv(client_sockfd, ch, 19, 0); 
    printf("get char from client: %s\n", ch);
 //   send(client_sockfd, ch, sizeof(ch), 0);
    close(client_sockfd);  
  }
  close(server_sockfd);
  return 0;
}
