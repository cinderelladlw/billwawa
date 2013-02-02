#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define PORT 7890 

int main()
{
  // socket 
  int reuseflag = 1;
  int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuseflag, sizeof(int)) == -1) {
    perror("socket reuse addr error:");
    close(server_sockfd);
  }
  // local address
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  // without error control 
  bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_sockfd, 5);

  char ch[20];
  int client_sockfd;
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(client_addr);

  while(1)
  {
    printf("server waiting:\n");
    // accept a connection
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len);
    // receive data
    int n = 0;
    int nread; 
    while((nread = recv(client_sockfd, ch, 19, 0)) > 0) {
      ch[nread + 1] = '\0';
      printf("get char from client: %s\n", ch);
      n += nread; 
      sleep(2);
    }
    if (nread == -1 && errno != EAGAIN) {
       perror("read error:");
    }
    close(client_sockfd);  
  }
  close(server_sockfd);
  return 0;
}
