#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<error.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void sendfile(char *filename, char *buff)
{
  FILE *file_fd = fopen(filename, "a+");  
  char buf[1024*256];
  memset(buf, 0x00, sizeof(buf));
  strcpy(buf, buff);
  fwrite(buf, 1, strlen(buf), file_fd);
  
  if(fclose(file_fd) != 0) {
    printf("fclose() error! \n");
  } else {
    printf("fclose ##file_fd## success!\n");
  }
}
