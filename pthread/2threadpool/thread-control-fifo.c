#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DBGPRINTF_DEBUG printf
#define DBGPRINTF_ERROR printf

#define ASSERT  assert



#include "thread-control.h"

static int path_index = 0;
#define LEN_CMD_PATH    10
struct _fifopipe_control_t
{
    char fifopipe_cmd_path[LEN_CMD_PATH];
};
typedef struct _fifopipe_control_t fifopipe_control_t;


int thread_control_init(THREAD_CONTROL* thread_control)
{
    *thread_control = NULL;

    fifopipe_control_t* fifopipe_control = (fifopipe_control_t*)malloc(sizeof(fifopipe_control_t));
    assert(fifopipe_control != NULL);

    path_index ++;
    snprintf(fifopipe_control->fifopipe_cmd_path, LEN_CMD_PATH, "./xxx%d", path_index);

    int ret = mkfifo(fifopipe_control->fifopipe_cmd_path, 0666/*(O_CREAT | O_RDWR)*/);
    assert(ret == 0);


    *thread_control = fifopipe_control;

    return 0;
}


int thread_control_deinit(THREAD_CONTROL* thread_control)
{
    fifopipe_control_t* fifopipe_control = (fifopipe_control_t*)(*thread_control);
    

    free(fifopipe_control);
    *thread_control = NULL;

    return 0;
}


int thread_control_wait(THREAD_CONTROL thread_control)
{
    fifopipe_control_t* fifopipe_control = (fifopipe_control_t*)(thread_control);
    
    int fd = open(fifopipe_control->fifopipe_cmd_path, O_RDONLY, 0);
    assert(fd>0);

    char tmp = 0;
    read(fd, &tmp, 1);

    return 0;
}


int thread_control_start(THREAD_CONTROL thread_control)
{
    fifopipe_control_t* fifopipe_control = (fifopipe_control_t*)(thread_control);
    
    int fd = open(fifopipe_control->fifopipe_cmd_path, O_WRONLY, 0);
    assert(fd>0);

    char tmp = 0;
    write(fd, &tmp, 1);

    return 0;
}
