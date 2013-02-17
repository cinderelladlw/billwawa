#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fp;
  int i;
  typedef struct route {
    char up[8+1];
    char down[8+1];
  } Route;
  Route rt;
  if((fp = fopen("route.txt","wb")) == NULL) {
    printf("can not open\n");
  }
  printf("input data:");
  for(i = 0; i < 2; i++) {
    scanf("%s %s", rt.up, rt.down);
    fwrite(&rt, sizeof(rt), 1, fp);
  }
  fclose(fp);
  if((fp = fopen("route.txt","rb")) == NULL) {
    printf("can not open2\n");
  }
  printf("show file:\n");
  for(i = 0; i < 2; i++) {
    fread(&rt, sizeof(rt), 1, fp);
    printf("%s %s\n", rt.up, rt.down);
  }
  fclose(fp);

  return 0;
}
