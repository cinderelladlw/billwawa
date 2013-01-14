#include <unistd.h>
#include <stdio.h>

int main()
{
  FILE *fp = fopen("junk.jnk", "w+");
  int status;
  fprintf(fp, "junk");
  status = access("junk.jnk", 0);
  if (status == 0) {
    printf("file does not easit\n");
  }
  fclose(fp);
  unlink("junk.jnk");
  
  status = access("junk.jnk", 0);
  if(status == 0)
    printf("file exist\n");
  else
    printf("file does not exist\n");
  return 0;
}
