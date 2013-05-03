#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include "listdir.h"
#include "plugin.h"

#define MAXLINE 1024

//int _listSo(char *directory, char **array)

//void configDll(dll *p, char *filename)
//{
//  FILE *fp;
//  char arr[MAXLINE];
//  if((fp = fopen(filename, "r")) == NULL)
//    perror("configDll.fopen:");
//  while((fgets(arr, MAXLINE, fp)) != NULL) { 
//    //fputs(arr, stdout); 
//    int n;  
//    for(n = 0; n < MAXLINE && arr[n] != EOF; n++) {
//      char *tmp = NULL;
//      tmp = arr;
//      if(arr[n] == '\n') {
//        arr[n] = '\0';
//        printf("[%s]\n", tmp);
//      } 
//    } 
//  }
//}


void registerDll(dll *p)
{
  struct list_head head, *plist;
  struct new_node sx;
  sx.onedll.dllname = ;
  sx.onddll.dllfunc = ;
  
  INIT_LIST_HEAD(&head);
  list_add(&sx.list, &head);
}

void unregisterDll(dll *p)
{
  struct list_head head, *plist;
  struct new_node sx;
  sx.onedll.
  
  INIT_LIST_HEAD(&head);
  list_del(&sx.list);  
}

void runDll()
{

}


//int _listSo(char *directory, char **array)
//{
//  DIR *dp;
//  struct dirent *dirp;
//
//  if((dp = opendir(directory)) == NULL) {
//    printf("can't open directory\n");
//  }
//  int i = 0;
//  while((dirp = readdir(dp)) != NULL) {
//    if(dirp->d_name[0] == '.')
//      continue;
//    sprintf(array[i], "%s", dirp->d_name);
//    i++;
//  }
//  closedir(dp);
//  return i;
//}
