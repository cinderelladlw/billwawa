#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<error.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, char **argv)
{
  if(argc < 3) {
    fprintf(stdout, "%s <port> <filename>\n", argv[0]);
    exit(0);
  }
  char buf[2048];
  memset(buf, 0x00, sizeof(buf));
  FILE *file_fd=fopen(argv[2], "a+");  //图片分多次传送，所以  "a+"

  int socket_listen=socket(AF_INET, SOCK_STREAM, 0);
  if(socket_listen<0) {
    perror("creating socket_listen failed!\n");
    exit(1);
  }

  //地址填充
  struct sockaddr_in server_addr,client_addr;
  memset(&server_addr, 0x00, sizeof(struct sockaddr_in));
  memset(&client_addr, 0x00, sizeof(struct sockaddr_in));
  server_addr.sin_family =AF_INET;
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  server_addr.sin_port   = htons(atoi(argv[1]));

  //监听套接字地址与服务端地址关联
  if(bind(socket_listen,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
     perror("Bind error.");
     exit(1);
  }

  //设置最大连接请求数
  if(listen(socket_listen,5)==-1) {
    printf("listen() error!\n");
    exit(1);
  }
  
  socklen_t addr_len = sizeof(client_addr);
  int socket_connect;
  
  printf("lisetn ...\n");
  socket_connect=accept(socket_listen,(struct sockaddr *)&client_addr,&addr_len);
  if(socket_connect<0) {
    printf("can't accept the request!\n");
    exit(1);
  }
  printf("connect success from %s #### %d\n",inet_ntoa(client_addr.sin_addr),socket_connect);
  int recvSequence=0;
  while(1) {
    printf("recv from client ...\n");
    int writeBytes=0;
    int recvBytes=recv(socket_connect,buf,sizeof(buf),0);
    if(recvBytes<0) {
      printf("recv error!\n");
      exit(1);
    } else if(recvBytes>0) {
      recvSequence++;
      printf("%d recv from client: %d bytes\n",recvSequence,recvBytes);
    } else if(recvBytes==0) {
      printf("one picture recv over!\n");
      break;
    }
    writeBytes=fwrite(buf,1,recvBytes,file_fd);
    printf("write to file: %d bytes \n",writeBytes); 
    bzero(buf,sizeof(buf));   
  }
  printf("one picture write to file over!\n");  
  
  if(close(socket_connect)!=0) {
    printf("close() error! \n");
  } else {
    printf("close ##socket_connect## success!\n");
  }
  if(fclose(file_fd)!=0) {
    printf("fclose() error! \n");
  } else {
    printf("fclose ##file_fd## success!\n");
  }
  return 0;
}
