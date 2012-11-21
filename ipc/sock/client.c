#include "socket.h"

int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);  
  TcpConnect("127.0.0.1", 9998);
  TcpSend(sockfd, "HELLO WORLD", 1024);
  return 0;
}
