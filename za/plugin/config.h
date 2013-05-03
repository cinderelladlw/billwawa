#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

typedef struct mbsconfig mbsconf;
struct mbsconfig {
  char dllname[30]; 
  char funcname[30];
};

// 全局变量
static sqlite3 *db;
static char *zErrMsg = 0;
static int rc;
static int i;

struct mbsconfig sxx[23];

static int callback(void *NotUsed, int a, char **ar, char **azColName);
static int committransaction(char *commitsql, int commitnumber);

#endif
