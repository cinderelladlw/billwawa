#include <dlfcn.h>
#include <stdio.h>

//���
void *flib;

//��ں���ԭ��
typedef int (*pfunc)(int a, int b);

//������Ϣ�ַ���
char *error_message;

int plugin_test(){
	int a = 1, b = 4;
	int result = 0;
	//����plugina.so����RTLD_LAZY��ʽ
	flib = dlopen("/mnt/hgfs/GA/za/dll/plugina.so", RTLD_LAZY);
	error_message = dlerror();
	if(error_message){
		return (-1);
	}
	//�ҵ�������Ϊfunc�ĺ�����������ָ��
	pfunc sx = dlsym(flib, "func");
//	*(&pfunc) = dlsym(flib, "func");
	error_message = dlerror();
	if(error_message){
		return (-1);
	}
	//����pfuncָ���ָ�룬��func����
	result = (*sx)(a, b);
	//�ͷ�
        printf(":::%d\n", result);
	int code = dlclose(flib);
	error_message = dlerror();
	if(error_message){
		return (-1);
	}
	return 0;	
}
int main()
{
  int rc = plugin_test();
  if(rc == 0) {
    printf("u got it \n");
  } else {
    printf("shit.....\n");
  }
  return 0;
}
