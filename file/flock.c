#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>

FILE * g_lockfile = NULL;

int main(int argc, char ** argv)
{
  char *lockfile = "/mnt/hgfs/GA/git/file/test.txt";
  int ret = -1;
  char rcvbuf[4096];
  char *ptr = NULL;
 
  if (g_lockfile != NULL) {
      return 0;
  }
  g_lockfile = fopen(lockfile, "a+");
  if (g_lockfile == NULL) {
      fprintf(stderr, "fopen() failed:%s!\n", strerror(errno));
      return -1;
  }

  ret = flock(fileno(g_lockfile), LOCK_EX|LOCK_NB);
  if (ret != 0) {
      fprintf(stderr, "flock() failed:%s!\n", strerror(errno));
      return -1;
  }
  printf("Open the file fd = %d\n", fileno(g_lockfile));
  while(1) {
    ptr = fgets(rcvbuf, sizeof(rcvbuf), stdin);
    if (ptr == NULL){
      break;
    }
    ret = fputs(rcvbuf, g_lockfile);
    if (ret < 0) {
        fprintf(stderr, "fputs() failed:%s!\n", strerror(errno));
        return -1;
    }
    fflush(g_lockfile);
  }
  ret = flock(fileno(g_lockfile), LOCK_UN);
  if (ret != 0) {
      fprintf(stderr, "flock() failed:%s!\n", strerror(errno));
      return -1;
  }
  fclose(g_lockfile);
  return 0;
}
