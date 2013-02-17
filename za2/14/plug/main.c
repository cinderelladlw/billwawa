#include <dlfcn.h>
#include "plug.h"

int main()
{
  void *handle;
  void (*sb)();
  handle = dlopen("./libplug.so", RTLD_LAZY);
  sb = dlsym(handle, "run");
  (*sb)();
  dlclose(handle);
  return 0;
}
