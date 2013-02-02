#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
  if(argc < 4) {
    fprintf(stdout, "%s <ip> <port> <filename>\n", argv[0]);
    exit(0);
  }
  struct hostent *h;
  printf("client start ...\n");
  
  FILE *file_fd=fopen(argv[3], "r+");
  
  char buf[2048];
  int socket_connect=socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  //µÿ÷∑ÃÓ≥‰ 
  memset(&server_addr, 0x00, sizeof(server_addr));
  server_addr.sin_family  = AF_INET;
  server_addr.sin_port  =htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr=inet_addr(argv[1]);
  
  printf("connect ...\n");
  if(connect(socket_connect,(struct sockaddr *)&server_addr,sizeof(server_addr))==-1) {
    printf("connect error!\n");
    exit(1);
  }
  printf("connect success!\n");
  printf("send ...\n");
  int sendSequence=0;
  while(1)
  {
    int readBytes=fread(buf, 1, sizeof(buf), file_fd);
    if(readBytes == 0) {
      printf("one picture transmit over!\n");
      break;
    } 
    else {
      printf(" read from file to buf ##%d## bytes\n",readBytes);
    }
    int sendBytes = send(socket_connect,buf,readBytes,0);
 
    if(sendBytes<0) {
      printf("send error! \n");
      exit(1);
    } else {
      sendSequence++;
      printf("%d send to server:%d bytes\n",sendSequence,sendBytes);
    }
    memset(buf, 0x00, sizeof(buf));
  }

  if(close(socket_connect) != 0) {
    printf("close() error! \n");
  } 
  else {
    printf("close ##socket_connect## success!\n");
  }
        
  if(fclose(file_fd)!=0) {
    printf("fclose() error! \n");
  } 
  else {
    printf("fclose ##file_fd## success!\n");
  }
  return 0;
}
