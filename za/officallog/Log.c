#include "Log.h"


static FILE *Log_FP = NULL;
static char LogFileName[128];
static pthread_mutex_t log_mutex_t;
static pthread_once_t  log_once_t = PTHREAD_ONCE_INIT;
static char InitLogFlag = 0;
static int  LogLevel    = 0;
static char InitMonFlag = 0;

static LOGLIST LogList[] = 
{
  {0, 0},
  {1, ERROR},
  {2, ERROR|WARN},
  {3, ERROR|WARN|INFO},
  {4, ERROR|WARN|INFO|DEBUG},
  {0, 0}
};

static char *Label[] = {"", "错误", "警告", "信息", "调试", ""};

static void InitLogFun();
static int  GetLevelSeq(int);
static char *NowFmtSysTime();
static char *NowSystemTime();



