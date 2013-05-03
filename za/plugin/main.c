#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dlfcn.h>
#include "list/list.h"
#include "listdir.h"
#include "config.h"

// 配置数据库对应结构体
extern struct mbsconfig sxx[23];
// 函数指针
typedef void (*funcptr)(int);

// 插件结构
struct plugin {
  char dllnam[30];      //动态库名字
  char dllfunc[30];     //动态库中的函数
};
// 转存数据库中插件记录的节点（链表） 
struct new_node {
  struct plugin pin;
  struct list_head list;
};
 
int main()
{
  int recordnum;           //数据库中数据记录条数
  recordnum = readconfig();
  struct list_head head, *plist;
  struct new_node aaa[23];
  int i;             // 计数器
  for (i = 0; i < recordnum; i++) {
    strcpy(aaa[i].pin.dllnam, sxx[i].dllname);
    strcpy(aaa[i].pin.dllfunc, sxx[i].funcname);
  } 
  // 把数据库中读取的配置写入链表中 
  INIT_LIST_HEAD(&head);
  for (i = 0; i < recordnum; i++) {
    list_add(&aaa[i].list, &head);
  } 
  struct handleptr { 
    void *handle;
    char dpname[30];  
  };
  struct handleptr hp[23];
  memset(hp, 0x00, sizeof(struct handleptr)*23);
  char *ldd[100];
  int count;
  for(i = 0; i < 100; i++) { 
    ldd[i] = (char *)malloc(100);
    memset(ldd[i], 0x00, 100);
  }   
  count = listdir("/mnt/hgfs/GA/git/za/plugin/lib/", ldd);

  funcptr fptr;
  for(i = 0; i < count; i++) {
    printf("指定路径下的动态库：[%s], 并获得相应的数据库句柄\n", ldd[i]); 
    char tmp[20];
    memset(tmp, 0x00, 20);
    strcat(tmp, ldd[i]);
    char dll[100];
    strcpy(dll, "/mnt/hgfs/GA/git/za/plugin/lib/"); 
    strcat(dll, tmp);
    hp[i].handle = dlopen(dll, RTLD_LAZY);
    strcpy(hp[i].dpname, tmp);
    printf("dlopen:[%s]\n", dlerror()); 
  }
  usleep(200000);
  //读取配置，运行动态库函数。 
  list_for_each(plist, &head) {
    struct new_node *node = list_entry(plist, struct new_node, list);
    printf("pin.dllnam = %s\n", node->pin.dllnam);
    printf("pin.dllfunc = %s\n", node->pin.dllfunc);
    int j;
    char tmp[30];
    sprintf(tmp, "%s", node->pin.dllfunc);
    for (j = 0; j < count; j++) {
      if (strcmp(hp[j].dpname, node->pin.dllnam) == 0) { 
        printf("bingo\n");
        fptr = dlsym(hp[j].handle, tmp);
        char *err_mes = dlerror();
        printf("err_mes:%s\n", err_mes);
        (*fptr)(10);
      }
    }
  }
  while(1);
  return 0;
}
