#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int listdir(char *directory, char **array);

int main(int argc, char *argv[])
{
  int ret;
  char *a[100];
  int sx;
  // initialize the p arr.
  for(sx = 0; sx < 100; sx++) {
    a[sx] = (char *)malloc(100);
    memset(a[sx], 0x00, 100);
  }
  ret = listdir(argv[1], a);
  for(sx = 0; (sx < ret); sx++)
    printf(":::[%s]\n", a[sx]); 
  return 0;
}

int listdir(char *directory, char **array)
{
  DIR *dp;
  struct dirent *dirp;
  
  if((dp = opendir(directory)) == NULL) {
    printf("can't open directory\n");
  }
  int i = 0;
  while((dirp = readdir(dp)) != NULL) {
    if(dirp->d_name[0] == '.')
      continue;
    sprintf(array[i], "%s", dirp->d_name);
    i++;
  }
  closedir(dp);
  return i;
}
  
