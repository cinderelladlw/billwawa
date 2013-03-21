#include "./log/log.h"

int main ( void )
{
  int num = 10 ;
  char buf[10] = "wangming" ;
  float fnum = 5.2 ;
  WriteLog("%d:%s:%f:",num,buf,fnum);
  return 0;
}
