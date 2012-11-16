#include <stdio.h>
#include <dlfcn.h>

int main()
{
  void *handle;
  double (*cosine)(double);
  char *error;
  
  handle = dlopen("libm.so", RTLD_LAZY);
  if(!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }
  cosine = dlsym(handle, "cos");
  if((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(1);
  }
  printf("%f\n", (*cosine)(3.14/2));
  dlclose(handle);
  return 0;
}




