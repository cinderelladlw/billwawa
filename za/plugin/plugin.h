#ifndef __PLUGIN_H__
#define __PLUGIN_H__

// ��������Ľṹ��
typedef struct Dll dll;
struct Dll {
  char dllname[30];
  char *dllfunc[30];
  int  dllfuncnum;
};


// ��Ӧ����Ļ�����
struct new_node {
  dll onedll;
  struct list_head list;
};


#endif


