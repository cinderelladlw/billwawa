#include <stdio.h>
#include <stdlib.h>


void MyFun1(int x);  
void MyFun2(int x);  
void MyFun3(int x);  
typedef void (*FunType)(int ); 
void CallMyFun(FunType fp,int x);

int main(int argc, char* argv[])
{
    CallMyFun(MyFun1,10);   
    CallMyFun(MyFun2,20);   
    CallMyFun(MyFun3,30);   
}
void CallMyFun(FunType fp,int x) 
{
   fp(x);
}
void MyFun1(int x)
{
printf(“函数MyFun1中输出：%d\n”,x);
}
void MyFun2(int x)  
{
printf(“函数MyFun2中输出：%d\n”,x);
}
void MyFun3(int x)  
{
printf(“函数MyFun3中输出：%d\n”,x);
}
