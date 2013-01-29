#ifndef __PLUGIN_H__
#define __PLUGIN_H__

// 单个插件的结构体
typedef struct Dll dll;
struct Dll {
  char dllname[30];
  char *dllfunc[30];
  int  dllfuncnum;
};


// 适应链表的机构体
struct new_node {
  dll onedll;
  struct list_head list;
};


#endif


