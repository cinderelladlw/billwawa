#include <assert.h>
#include <pthread.h>
#include <stdio.h>

// 取出线程的ID
int GetThreadID()
{
	return (int)pthread_self();
}

// 该静态变量被所有线程使用
static int s_nThreadResult = 0;

static pthread_once_t once = PTHREAD_ONCE_INIT;

// 该初始化函数，我在多线程下只想执行一次
void thread_init()
{
	s_nThreadResult = -1;
	printf("[Child %0.4x] looping i(%0.8x)\n", GetThreadID(), s_nThreadResult);
}

void * theThread(void * param)
{
	// 通过once的控制，thread_init只会被执行一次
	pthread_once(&once, &thread_init);
	printf("[Child %0.4x] looping i(%0.8x)\n", GetThreadID(), s_nThreadResult);

	s_nThreadResult ++;
	pthread_exit(&s_nThreadResult);

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, &theThread, NULL);
	pthread_create(&tid2, NULL, &theThread, NULL);

	// 无论是否休眠，两个子线程最终都会被主线程join到
	// 因为两个子线程都是默认的PTHREAD_CREATE_JOINABLE类型
	//SLEEP(3);

	void * status = NULL;
	int rc = pthread_join(tid1, &status);
	if (status != PTHREAD_CANCELED && status != NULL)
	{
		printf("Returned value from thread: %d\n", *(int *)status);
	}

	rc = pthread_join(tid2, &status);
	if (status != PTHREAD_CANCELED && status != NULL)
	{
		printf("Returned value from thread: %d\n", *(int *)status);
	}

	return 0;
}
