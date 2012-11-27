#include <stdio.h>
#include <time.h>
#include <sys/types.h>

static char *NowTime()
{
  static char systime[24];
  struct timeval tv;
  struct tm *tp;
  gettimeofday(&tv, NULL);
  tp = localtime(&tv.tv_sec);
  sprintf(systime, "%04d%02d%02d%02d%02d%02d%03ld",
                   tp -> tm_year + 1900,
                   tp -> tm_mon +1,
                   tp -> tm_mday,
                   tp -> tm_hour,
                   tp -> tm_min, 
                   tp -> tm_sec, 
                   tv.tv_usec/1000);
  return systime;
}

int main()
{
  printf("%s\n", NowTime());
  return 0;
} 






