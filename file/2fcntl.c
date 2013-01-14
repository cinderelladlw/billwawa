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
  lock.l_type = F_WRLCK;  //����д��
  lock.l_whence = 0;    //���ļ���ʼλ�ÿ�ʼ
  lock.l_start = 0;     //ƫ��ֵΪ0
  lock.l_len = 0;       //��ƪ����
  while (fcntl(fd, F_SETLK, &lock) < 0) {
    if(errno == EAGAIN||errno ==  EACCES)  //���������̼�����
    {
      if(++count<5) {
        sleep(1);  //��������������5s
      }
      else {
        fcntl(fd, F_GETLK, &lock);  //�������֮ǰ��ӡ��ǰ�ļ����Ǹ����̼�������F_GETLKΪ��ü�����Ϣ
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
  sleep(8);   //ռ���ļ���ʱ�䣬��������Ƕ��ļ���һЩ����
  printf("Pid: %ld process release the file.\n",(long)getpid());
  return 0;
}

