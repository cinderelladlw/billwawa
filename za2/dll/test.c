#include <dlfcn.h>
#include <stdio.h>

//句柄
void *flib;

//入口函数原型
typedef int (*pfunc)(int a, int b);

//错误信息字符串
char *error_message;

int plugin_test(){
	int a = 1, b = 4;
	int result = 0;
	//加载plugina.so，以RTLD_LAZY方式
	flib = dlopen("/mnt/hgfs/GA/za/dll/plugina.so", RTLD_LAZY);
	error_message = dlerror();
	if(error_message){
		return (-1);
	}
	//找到函数名为func的函数，返回其指针
	pfunc sx = dlsym(flib, "func");
//	*(&pfunc) = dlsym(flib, "func");
	error_message = dlerror();
	if(error_message){
		return (-1);
	}
	//调用pfunc指向的指针，及func函数
	result = (*sx)(a, b);
	//释放
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
