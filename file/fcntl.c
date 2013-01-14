#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char ** argv)
{
   
    int ret;
    struct flock f1;
    int fd;

    fd = open("/mnt/hgfs/GA/git/file/fcntl.txt", O_CREAT | O_RDWR, 0777);
    if (fd < 0)
    {
        printf("open failed! msg: %s\n", strerror(errno));
        return -1;
    }

    f1.l_type = F_WRLCK;
    f1.l_start = 0;
    f1.l_whence = SEEK_SET;
    f1.l_len = 0;
    f1.l_pid = -1;

    ret = fcntl(fd, F_GETLK, &f1);
    if (ret < 0)
    {
        printf("fcntl failed msg:%s\n", strerror(errno));
        return -1;

    }

    if (f1.l_type == F_UNLCK)
    {
        printf("file fd = %d, pid = [%d] is unlock!\n", fd, f1.l_pid);
        goto lock;
    }
    if (f1.l_type == F_RDLCK)
    {
        printf("file fd = %d, pid = [%d] had a read locked!\n", fd, f1.l_pid);
        goto unlock;

    }
    if (f1.l_type == F_WRLCK)
    {
        printf("file fd = %d, pid = [%d] had a write locked!\n", fd, f1.l_pid);
        goto unlock;

    }

unlock:   
    f1.l_type = F_UNLCK;
    f1.l_start = 0;
    f1.l_whence = SEEK_SET;
    f1.l_len = 0;
   
    ret = fcntl(fd, F_SETLK, &f1);
    if (ret < 0)
    {
        printf("fcntl failed msg:%s\n", strerror(errno));
        return -1;
    }

    printf("delete file fd = %d lock is  success !\n", fd);
    return 0;

lock:
   

    f1.l_type = F_WRLCK;
    f1.l_start = 0;
    f1.l_whence = SEEK_SET;
    f1.l_len = 0;
   
    ret = fcntl(fd, F_SETLK, &f1);
    if (ret < 0)
    {
        printf("fcntl failed msg:%s\n", strerror(errno));
        return -1;
    }

    printf("lock file fd = %d success!\n", fd);

    sleep(100);

    printf("time out!\n");
   
    return 0;
}
