#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *(*fp) (char *);
  char *sxxx = "HEllo SHit";
  
  printf("..\n");
  void *flib = dlopen("/mnt/hgfs/GA/git/za2/dll/shit/plug.so", RTLD_LAZY);
  printf("..\n");
  fp = dlsym(flib, "upper");
 // fp = dlsym(flib, "upper");
  printf("..\n");
  char *result = (char *)malloc(50);
  printf("..\n");
  result = (*fp)(sxxx);
  printf("..\n");
  printf(":%s\n", result);
 
  dlclose(flib);
  
  return 0;
}
