#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dlfcn.h>
#include "list/list.h"
#include "listdir.h"
#include "config.h"

// �������ݿ��Ӧ�ṹ��
extern struct mbsconfig sxx[23];
// ����ָ��
typedef void (*funcptr)(int);

// ����ṹ
struct plugin {
  char dllnam[30];      //��̬������
  char dllfunc[30];     //��̬���еĺ���
};
// ת�����ݿ��в����¼�Ľڵ㣨���� 
struct new_node {
  struct plugin pin;
  struct list_head list;
};
 
int main()
{
  int recordnum;           //���ݿ������ݼ�¼����
  recordnum = readconfig();
  struct list_head head, *plist;
  struct new_node aaa[23];
  int i;             // ������
  for (i = 0; i < recordnum; i++) {
    strcpy(aaa[i].pin.dllnam, sxx[i].dllname);
    strcpy(aaa[i].pin.dllfunc, sxx[i].funcname);
  } 
  // �����ݿ��ж�ȡ������д�������� 
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
    printf("ָ��·���µĶ�̬�⣺[%s], �������Ӧ�����ݿ���\n", ldd[i]); 
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
  //��ȡ���ã����ж�̬�⺯���� 
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
