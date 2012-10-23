#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>


int main()
{
  FILE *fp = NULL;
  if((fp = fopen("a.txt", "a+")) == NULL) {
    printf("error open file\n");
  }
  int fd = fileno(fp);
  flock(fd, LOCK_EX);
  char *buff = "hey kit";
  fwrite(buff, sizeof(int), 2, fp);
  fflush(fp);
  printf("buff:%s\n", buff);
  sleep(1000);  
  
  flock(fd, LOCK_UN); 
  
  fclose(fp);  
  return 0;
}
