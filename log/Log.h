#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <sys/errno.h>
#include <sys/stat.h>

#define MAXLOGSZ 32*1024*1024
#define ERROR 0x01
#define WARN 0x02
#define INFO 0x04
#define DEBUG 0x08

typedef struct LogLevelStru LOGLIST;
struct LogLevelStru {
  int LogLevel;
  int LogLevelVal;
};

#define Log(level, ...)
#define HexLog(Buf, Len)

void _Log(int, char *, int ,char *fmt, ...);
void _HexLog(char, const char *,long, const char *);
void OpenLog(const char *);
void SetLogLevel(int);
void CloseLog();




#endif
