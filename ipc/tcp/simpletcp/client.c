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
  /* create a socket */
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(PORT);
  /* connect to the server */
  int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
  if(result == -1)
  {
    perror("connect failed: ");
    exit(1);
  }
  /* exchange data */
  char ch[200] = "helloworldhelloworldhelloworldhelloworldhelloworldhelloworld";
  send(sockfd, ch, strlen(ch)+1, 0);
 
    
  close(sockfd);
  return 0;
}
