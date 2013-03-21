#include <stdio.h>
#include <time.h>
#include <sys/types.h>

static int NowTime()
{
  static char systime[24];
  struct timeval tv;
  struct tm *tp;
  gettimeofday(&tv, NULL);
  tp = localtime(&tv.tv_sec);
  int sb = 100000000*(tp -> tm_min) 
                   +(tp -> tm_sec)*1000000
                   +(tv.tv_usec);
  return sb;
}

int main()
{
  //printf("%d\n", NowTime()); 
  int time1, time2;
  time1 = NowTime();
  sleep(1); 
  time2 = NowTime();
  printf("time2-time1=%d\n", time2-time1);
  //printf("%d\n", NowTime()); 
  return 0;
} 


