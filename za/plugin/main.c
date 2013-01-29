#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "list/list.h"

struct plugin {
  char dllname[30];
  char dllfunc[30];
  int funcnum;
};
 
struct new_node {
  //int val;
  struct plugin pin;
  struct list_head list;
};
 
int main()
{
  struct list_head head, *plist;
  struct new_node a, b;
  
  a.pin.funcnum = 2;
  strcpy(a.pin.dllname, "dll 1");
  strcpy(a.pin.dllfunc, "func 1");

  b.pin.funcnum = 3;
  strcpy(b.pin.dllname, "dll 2");
  strcpy(b.pin.dllfunc, "func 2");
  
  INIT_LIST_HEAD(&head);
  list_add(&a.list, &head);
  list_add(&b.list, &head);
  
  list_for_each(plist, &head) {
          struct new_node *node = list_entry(plist, struct new_node, list);
          printf("pin.funcnum = %d\n", node->pin.funcnum);
          printf("pin.dllname = %s\n", node->pin.dllname);
          printf("pin.dllfunc = %s\n", node->pin.dllfunc);
  }
  void *handle[];
  handle[0] = dlopen("./dll1.so", RTLD_LAZY);
  void (*func1)();
  func1 = dlsym(handle[0], "add");
  (*func1)();
  dlclose(handle[0]);
 

  
  
  return 0;
}
