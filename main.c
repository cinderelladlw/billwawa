<<<<<<< HEAD
#include <stdio.h> 
     
int main()  
{  
        // 文件指针和保存输入的字符串  
        FILE *fp = NULL;  
        char str[100] = "";  
           
           
        // 以可写方式打开文件  
        if(NULL==(fp = fopen("test.txt","w")))  
        {   
            printf("cannot open the file.\n");  
            exit(0);  
        }  
     
        // 提示用户输入  
        printf("please input a string:\n");  
        do  
        {  
            // 判断输入是否结束  
            gets(str);  
            if('!'==str[0])  
                break;  
            // 写入文件  
            fputc(str,fp);  
        }while(1);  
           
        // 关闭文件  
        fclose(fp);  
    }  
=======
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char *sp = NULL;
  sp = "hello world";
  printf("%s\n", sp);
  return 0;
}
>>>>>>> 363b59a5b1366c83d801543047c9ca34cffb1166
