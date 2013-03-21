#include <assert.h>
#include <pthread.h>
#include <stdio.h>

// ȡ���̵߳�ID
int GetThreadID()
{
	return (int)pthread_self();
}

// �þ�̬�����������߳�ʹ��
static int s_nThreadResult = 0;

static pthread_once_t once = PTHREAD_ONCE_INIT;

// �ó�ʼ�����������ڶ��߳���ֻ��ִ��һ��
void thread_init()
{
	s_nThreadResult = -1;
	printf("[Child %0.4x] looping i(%0.8x)\n", GetThreadID(), s_nThreadResult);
}

void * theThread(void * param)
{
	// ͨ��once�Ŀ��ƣ�thread_initֻ�ᱻִ��һ��
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

	// �����Ƿ����ߣ��������߳����ն��ᱻ���߳�join��
	// ��Ϊ�������̶߳���Ĭ�ϵ�PTHREAD_CREATE_JOINABLE����
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
