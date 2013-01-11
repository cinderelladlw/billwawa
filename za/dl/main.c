#include <stdio.h>
#include <dlfcn.h>

int main()
{
  void *handle;
  void (*cosine)();
  char *error;
  
  handle = dlopen("/home/bill/git/billwawa/za/dl/plug.so", RTLD_LAZY);
  if(!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }
  cosine = dlsym(handle, "add");
  if((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(1);
  }

  (*cosine)();
  dlclose(handle);
  return 0;
}




