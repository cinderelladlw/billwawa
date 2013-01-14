#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc,char* argv[])
{
  int fd;
  struct flock lock;
  int count = 0;
  if (argc != 2) {
    printf("Usage: %s filename.\n",argv[1]);
    return 1;
  }
  fd = open(argv[1],O_RDWR);
  if (fd<0) {
    printf("Open file failed.\n");
    return 1;
  }
  lock.l_type = F_WRLCK;  //设置写锁
  lock.l_whence = 0;    //从文件起始位置开始
  lock.l_start = 0;     //偏移值为0
  lock.l_len = 0;       //整篇加锁
  while (fcntl(fd, F_SETLK, &lock) < 0) {
    if(errno == EAGAIN||errno ==  EACCES)  //被其他进程加锁了
    {
      if(++count<5) {
        sleep(1);  //加锁申请最多持续5s
      }
      else {
        fcntl(fd, F_GETLK, &lock);  //否则放弃之前打印当前文件被那个进程加了锁，F_GETLK为获得加锁信息
        printf("Pid: %ld process find pid %ld process lock the file %s.\n",
        return 1;
      }
    }
    else {
      printf("Error: exec function fcntl failed.\n");
      return 1;
    }
  }
  printf("Pid: %ld process locked the file.\n",(long)getpid());
  sleep(8);   //占用文件的时间，这里可以是对文件的一些操作
  printf("Pid: %ld process release the file.\n",(long)getpid());
  return 0;
}

