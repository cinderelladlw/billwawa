#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>


int main()
{
  FILE *fp = NULL;
  if((fp = fopen("a.txt", "r+")) == NULL) {
    printf("error open file\n");
  }
  int fd = fileno(fp);
  printf(".............\n");
  flock(fd, LOCK_EX);
  printf(".............\n");

  char *buf = malloc(sizeof(int)*3);
  fread(buf, sizeof(int), 2, fp);
  fflush(fp);
  printf("buf:%s\n", buf);
  
  flock(fd, LOCK_UN); 
  
  fclose(fp);  
  return 0;
}
